import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;
import java.io.BufferedReader;
import java.io.FileReader;
import org.jasypt.util.password.StrongPasswordEncryptor;
import java.util.concurrent.locks.ReentrantLock;
import java.util.Iterator;

public class Server {

    private final int port;
    private ServerSocket serverSocket;
    private List<String> possibleWords;
    private final int TIMEOUT = 10000;
    private String mode;

    // Database
    private Database database;
    private final ReentrantLock databaselock;

    // Tokens
    private int tokenIndex;
    private final ReentrantLock tokenLock;

    // Players
    private List<Player> waitingQueue;
    private List<Player> rankedWaitingQueue;
    private final ReentrantLock waitingQueueLock;
    private final ReentrantLock rankedWaitingQueueLock;

    // Pings
    private final int PING_INTERVAL = 10000;
    private long lastPing;
    private long lastRankedPing;

    // Constructor: initializes the server with the specified port
    Server(int port) throws IOException, ParseException {
        this.port = port;
        this.serverSocket = new ServerSocket(port);
        this.possibleWords = readWords();
        this.database = new Database("credentials.json");
        this.databaselock = new ReentrantLock();
        this.tokenIndex = 0;
        this.tokenLock = new ReentrantLock();
        this.waitingQueue = new ArrayList<Player>();
        this.rankedWaitingQueue = new ArrayList<Player>();
        this.waitingQueueLock = new ReentrantLock();
        this.rankedWaitingQueueLock = new ReentrantLock();
        this.lastPing = System.currentTimeMillis();
        this.lastRankedPing = System.currentTimeMillis();
        System.out.println("Server is listening on port " + this.port);
    }

    // Generates a token for a player based on their username
    public String generateToken(String username) {
        this.tokenLock.lock();
        int token = this.tokenIndex;
        this.tokenIndex++;
        this.tokenLock.unlock();
        return new StrongPasswordEncryptor().encryptPassword(username + token);
    }

    // Authenticates a user with the server
    public Player login(String username, String password, Socket socket) {
        String token = generateToken(username);

        try {
            this.databaselock.lock();
            Player player = this.database.login(username, password, token, socket);
            this.database.updateDatabase();
            this.databaselock.unlock();
            return player;
        } catch (Exception e) {
            System.out.println("Error logging in: " + e.getMessage());
        }
        return null;
    }

    // Registers a new user
    public Player register(String username, String password, Socket socket) {
        Player player;
        String token = generateToken(username);

        try {
            this.databaselock.lock();
            player = this.database.register(username, password, token, socket);
            this.database.updateDatabase();
            this.databaselock.unlock();
            return player;
        } catch (Exception e) {
            System.out.println("Error registering: " + e.getMessage());
        }
        return null;
    }

    // Allows a user to reconnect using a session token
    public Player reconnect(String token, Socket socket) {
        try {
            this.databaselock.lock();
            Player player = this.database.reconnect(token, socket);
            this.database.updateDatabase();
            this.databaselock.unlock();
            return player;
        } catch (Exception e) {
            System.out.println("Error reconnecting: " + e.getMessage());
        }
        return null;
    }

    // Handles the connection of a player, including login, registration, and reconnection
    public void handlePlayerConnection(Socket playerSocket) throws IOException {
        String playerResponse = "";
        Player player = null;
        boolean alreadyInQueue = false;
        long initialTime = System.currentTimeMillis();

        InputStream input = playerSocket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));

        OutputStream output = playerSocket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);

        do {
            alreadyInQueue = false;
            if (System.currentTimeMillis() - initialTime > TIMEOUT) {
                System.out.println("Connection timeout");
                writer.println("FIN" + "/space" + "Closing connection due to timeout");
                return;
            }

            writer.println("MNU" + "/space" + "1 - Login" + "/space" + "2 - Register" + "/space" + "3 - Reconnect"
                    + "/space" + "4 - Exit");
            playerResponse = reader.readLine();

            if (playerResponse.equals("4")) {
                writer.println("FIN" + "/space" + "Closing connection due to player request");
                playerSocket.close();
                return;
            }

            else if (!playerResponse.equals("1") && !playerResponse.equals("2") && !playerResponse.equals("3")) {
                writer.println("ERR" + "/space" + "Invalid option");
                reader.readLine();
                continue;
            }

            if (playerResponse.equals("1")) {
                writer.println("USR" + "/space" + "Enter your username: ");
                String username = reader.readLine();

                for (Player p : this.waitingQueue) {
                    if (p.getUsername().equals(username)) {
                        alreadyInQueue = true;
                        writer.println("ERR" + "/space" + "User already logged in,try to reconnect");
                        reader.readLine();
                        break;
                    }
                }

                for (Player p : this.rankedWaitingQueue) {
                    if (p.getUsername().equals(username)) {
                        alreadyInQueue = true;
                        writer.println("ERR" + "/space" + "User already logged in,try to reconnect");
                        reader.readLine();
                        break;
                    }
                }

                if (alreadyInQueue) {
                    continue;
                }

                writer.println("PWD" + "/space" + "Enter your password: ");
                String password = reader.readLine();

                player = login(username, password, playerSocket);
                if (player != null) {
                    writer.println("AUTH" + "/space" + player.getUsername() + ".txt" + "/space" + player.getToken());
                    reader.readLine();
                } else {
                    System.out.println("Player gave invalid credentials");
                    writer.println("ERR" + "/space" + "Invalid credentials");
                    reader.readLine();
                }

            } else if (playerResponse.equals("2")) {
                writer.println("USR" + "/space" + "Enter your username: ");
                String username = reader.readLine();
                writer.println("PWD" + "/space" + "Enter your password: ");
                String password = reader.readLine();

                player = register(username, password, playerSocket);
                if (player != null) {
                    System.out.println("Player registered successfully");
                    writer.println("AUTH" + "/space" + player.getUsername() + ".txt" + "/space" + player.getToken());
                    reader.readLine();
                } else {
                    System.out.println("Player tried to register with an existing username");
                    writer.println("ERR" + "/space" + "Username already exists");
                    reader.readLine();
                }
            } else if (playerResponse.equals("3")) {
                writer.println("TOK" + "/space" + "Enter your token: ");
                String token = reader.readLine();
                System.out.println("Reconnecting player with token: " + token);
                player = reconnect(token, playerSocket);
                if (player != null) {
                    System.out.println("Player reconnected successfully");
                    writer.println("AUTH" + "/space" + player.getUsername() + ".txt" + "/space" + player.getToken());
                    reader.readLine();
                    player.setReader(reader);
                    player.setWriter(writer);
                    addPlayerToQueue(player, true);
                    return;
                } else {
                    System.out.println("Player tried to reconnect with an invalid token");
                    writer.println("ERR" + "/space" + "Invalid token");
                    reader.readLine();
                }
            }

        } while (player == null);

        player.setReader(reader);
        player.setWriter(writer);

        addPlayerToQueue(player, false);
    }

    // Adds a player to the appropriate queue (normal or ranked)
    public void addPlayerToQueue(Player player, boolean reconnected) {
        System.out.println("Adding player to waiting queue: " + player.getUsername());
        String mode = "";
        try {
            BufferedReader reader = player.getReader();
            PrintWriter writer = player.getWriter();

            if (!reconnected) {
                writer.println("MOD" + "/space");
                mode = reader.readLine();
                while (!mode.equals("1") && !mode.equals("2") && !mode.equals("3")) {
                    writer.println("ERR" + "/space" + "Invalid mode");
                    writer.println("MOD" + "/space");
                    mode = reader.readLine();
                }
            }

            if(mode.equals("3")){
                writer.println("FIN" + "/space" + "Closing connection due to player request");
                player.getSocket().close();
                return;
            }

            if (reconnected) {
                this.waitingQueueLock.lock();
                for (Player p : this.waitingQueue) {
                    if (p.equals(player)) {
                        p.getSocket().close();
                        p.setSocket(player.getSocket());
                        p.setReader(player.getReader());
                        p.setWriter(player.getWriter());
                        System.out.println("Player " + player.getUsername() + " reconnected. Queue size: "
                                + this.waitingQueue.size());
                        writer.println("QUE" + "/space" + "You were reconnected to the waiting queue");
                        reader.readLine();
                        this.waitingQueueLock.unlock();
                        return;
                    }
                }
                this.waitingQueueLock.unlock();

                this.rankedWaitingQueueLock.lock();
                for (Player p : this.rankedWaitingQueue) {
                    if (p.equals(player)) {
                        p.getSocket().close();
                        p.setSocket(player.getSocket());
                        p.setReader(player.getReader());
                        p.setWriter(player.getWriter());
                        System.out.println("Player " + player.getUsername() + " reconnected. Ranked Queue size: "
                                + this.rankedWaitingQueue.size());
                        writer.println("QUE" + "/space" + "You were reconnected to the ranked waiting queue");
                        reader.readLine();
                        this.rankedWaitingQueueLock.unlock();
                        return;
                    }
                }
                this.rankedWaitingQueueLock.unlock();
            }

            if (mode.equals("1")) {
                this.waitingQueueLock.lock();
                waitingQueue.add(player);
                this.waitingQueueLock.unlock();
                writer.println("QUE" + "/space" + "You were added to the waiting queue");
                reader.readLine();
                System.out.println("Player " + player.getUsername() + " is now in waiting queue. Queue size: "
                        + this.waitingQueue.size());
            } else {
                this.rankedWaitingQueueLock.lock();
                rankedWaitingQueue.add(player);
                this.rankedWaitingQueueLock.unlock();
                rankedWaitingQueue.sort(Comparator.comparingLong(Player::getRank));
                writer.println("QUE" + "/space" + "You were added to the ranked waiting queue");
                reader.readLine();
                System.out.println("Player " + player.getUsername()
                        + " is now in ranked waiting queue. Ranked Queue size: "
                        + this.rankedWaitingQueue.size());
            }
        } catch (Exception exception) {
            System.out.println("Error during insert in waiting queue. Info: " + exception.getMessage());
        }
    }

    // Starts a normal game with 5 players from the waiting queue
    public void startNormalGame() {
        if (this.waitingQueue.size() >= 5) {
            this.waitingQueueLock.lock();
            System.out.println("Getting players for normal game");
            List<Player> playersForGame = new ArrayList<Player>();
            for (int i = 0; i < 5; i++) {
                playersForGame.add(this.waitingQueue.remove(0));
                System.out.println("Player " + playersForGame.get(i).getUsername() + " removed from waiting queue");
                System.out.println("Queue size: " + this.waitingQueue.size());
            }
            this.waitingQueueLock.unlock();
            Runnable GameRunnable = new Game(playersForGame, this.possibleWords,false);
            Thread thread = new Thread(GameRunnable);
            thread.start();
            try {
                thread.join();
                if(thread.getState() == Thread.State.TERMINATED){
                    thread = null;
                    for(Player player : playersForGame){
                        Runnable addToQueueRunnable = () -> {
                            addPlayerToQueue(player, false);
                        };
                        Thread addToQueueThread = new Thread(addToQueueRunnable);
                        addToQueueThread.start();
                    }
                }
            } catch (InterruptedException e) {
                System.out.println("Error joining thread: " + e.getMessage());
            }
        }
    }

    // Starts a ranked game with 5 players from the ranked waiting queue
    public void startRankedGame() {
        if (rankedWaitingQueue.size() >= 5) {
            rankedWaitingQueueLock.lock();
            long diff = (System.currentTimeMillis() - lastRankedPing) / 1000;
            List<Player> playersForRankedGame = new ArrayList<>();
            for (int i = 0; i <= rankedWaitingQueue.size() - 5; i++) {
                if (rankedWaitingQueue.get(i + 4).getRank() - rankedWaitingQueue.get(i).getRank() <= (10L + diff)) {
                    System.out.println("Getting players for ranked game");
                    for (int j = 0; j < 5; j++) {
                        playersForRankedGame.add(rankedWaitingQueue.remove(i));
                    }
                    System.out.println("Players removed from ranked waiting queue");
                    System.out.println("Ranked Queue size: " + rankedWaitingQueue.size());
                    lastRankedPing = System.currentTimeMillis();
                    break;
                }
            }
            rankedWaitingQueueLock.unlock();
            if (playersForRankedGame.size() == 5){
                Runnable gameRunnable = new Game(playersForRankedGame, possibleWords, true);

                Thread thread = new Thread(gameRunnable);
                thread.start();
                try {
                    thread.join();
                    if(thread.getState() == Thread.State.TERMINATED){
                        thread = null;
                        for(Player player : playersForRankedGame){
                            Runnable addToQueueRunnable = () -> {
                                try{
                                    this.databaselock.lock();
                                    this.database.updatePlayerRank(player);
                                    this.database.updateDatabase();
                                    this.databaselock.unlock();
                                    addPlayerToQueue(player, false);
                                }catch(Exception e){
                                    System.out.println("Error updating player rank: " + e.getMessage());
                                }
                            };
                            Thread addToQueueThread = new Thread(addToQueueRunnable);
                            addToQueueThread.start();
                        }
                    }
                } catch (InterruptedException e) {
                    System.out.println("Error joining thread: " + e.getMessage());
                }
            }
        }
        else{
            this.lastRankedPing = System.currentTimeMillis();
        }
    }

    // Pings players in the waiting queues
    public void pingPlayers() {
        if (System.currentTimeMillis() - this.lastPing > this.PING_INTERVAL) {
            this.lastPing = System.currentTimeMillis();

            if (waitingQueue.size() > 0) {
                this.waitingQueueLock.lock();
                System.out.println("Pinging players in waiting queue");
                for (Player player : this.waitingQueue) {
                    try {
                        OutputStream output = player.getSocket().getOutputStream();
                        PrintWriter writer = new PrintWriter(output, true);
                        writer.println("PING" + "/space" + "Ping");
                    } catch (IOException e) {
                        System.out.println("Error pinging player: " + e.getMessage());
                        waitingQueue.remove(player);
                    } catch (Exception e) {
                        this.waitingQueueLock.unlock();
                        throw new RuntimeException(e);

                    }
                }
                this.waitingQueueLock.unlock();
            }

            if (rankedWaitingQueue.size() > 0) {
                this.rankedWaitingQueueLock.lock();
                System.out.println("Pinging players in ranked waiting queue");
                for (Player player : this.rankedWaitingQueue) {
                    try {
                        OutputStream output = player.getSocket().getOutputStream();
                        PrintWriter writer = new PrintWriter(output, true);
                        writer.println("PING" + "/space" + "Ping");
                    } catch (IOException e) {
                        System.out.println("Error pinging player: " + e.getMessage());
                        rankedWaitingQueue.remove(player);
                    } catch (Exception e) {
                        this.rankedWaitingQueueLock.unlock();
                        throw new RuntimeException(e);
                    }
                }
                this.rankedWaitingQueueLock.unlock();
            }
        }
    }

    // Checks for new player connections
    public void checkNewConnections() {
        while (true) {
            try {
                Socket playerSocket = serverSocket.accept();
                System.out.println("New player requesting to connect");
                Runnable newConnection = () -> {
                    try {
                        handlePlayerConnection(playerSocket);
                    } catch (IOException e) {
                        System.out.println("Error handling new player connection: " + e.getMessage());
                    }
                };
                new Thread(newConnection).start();
            } catch (Exception e) {
                System.out.println("Error accepting new player connection: " + e.getMessage());
            }
        }
    }

    // Reads the possible words for the game from a file
    public List<String> readWords() throws IOException {
        String filePath = "words.txt";
        List<String> content = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                content.add(line);
            }
        } catch (FileNotFoundException e) {
            // Handle file not found exception
            System.err.println("Error: File not found - " + e.getMessage());
            throw e; // Propagate the exception
        } catch (IOException e) {
            // Handle other IO exceptions
            System.err.println("Error while reading words file: " + e.getMessage());
            throw e; // Propagate the exception
        }

        return content;
    }

    // Main server loop: handles player connections and manages games
    public void run() throws IOException {

        Thread waitingQueueThread = new Thread(() -> {
            while (true) {
                pingPlayers();
                startNormalGame();
            }
        });

        Thread rankedWaitingQueuThread = new Thread(() -> {
            while (true) {
                pingPlayers();
                startRankedGame();
            }
        });

        Thread connectionThread = new Thread(() -> {
            while (true) {
                checkNewConnections();
            }
        });

        this.databaselock.lock();
        this.database.resetTokens();
        this.databaselock.unlock();

        waitingQueueThread.start();
        rankedWaitingQueuThread.start();
        connectionThread.start();
    }

    // Main method: starts the server
    public static void main(String[] args) {

        if (args.length < 1) {
            System.out.println("Usage: java Server <port>");
            return;
        }

        // Start server
        try {
            int port = Integer.parseInt(args[0]);
            Server server = new Server(port);
            server.run();

        } catch (IOException | ParseException e) {
            System.out.println("Error starting server: " + e.getMessage());
        }
    }

}
