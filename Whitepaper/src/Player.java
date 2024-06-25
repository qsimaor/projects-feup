import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Player {

    private String username;
    private String password;
    private String token;
    private boolean isPlaying;
    private boolean isWhitepaper;
    private Long rank;
    private Socket socket;
    private BufferedReader reader;
    private PrintWriter writer;

    // Constructor: initializes a player with a username, password, rank, socket, and token
    public Player(String username, String password, Long rank, Socket socket, String token) {
        this.username = username;
        this.password = password;
        this.rank = rank;
        this.socket = socket;
        this.token = token;
        this.isPlaying = false;
        this.isWhitepaper = false;
    }

    // Returns whether the player is playing
    public boolean isPlaying() {
        return this.isPlaying;
    }

    // Updates the player's buffered reader
    public void setReader(BufferedReader reader) {
        this.reader = reader;
    }

    // Returns the player's buffered reader
    public BufferedReader getReader() {
        return this.reader;
    }

    // Updates the player's print writer
    public void setWriter(PrintWriter writer) {
        this.writer = writer;
    }

    // Returns the player's print writer
    public PrintWriter getWriter() {
        return this.writer;
    }

    // Returns whether the player is the whitepaper
    public boolean isWhitepaper() {
        return this.isWhitepaper;
    }

    // Updates the player's playing status
    public void setPlaying(boolean playing) {
        this.isPlaying = playing;
    }

    // Updates the player's whitepaper status
    public void setWhitePaper(boolean whitepaper) {
        this.isWhitepaper = whitepaper;
    }

    // Returns the player's username
    public String getUsername() {
        return this.username;
    }

    // Returns the player's rank
    public Long getRank() {
        return this.rank;
    }

    // Returns the player's socket
    public Socket getSocket() {
        return this.socket;
    }

    // Returns the player's token
    public String getToken() {
        return this.token;
    }

    // Updates the player's socket
    public void setSocket(Socket newSocket){
        this.socket = newSocket;
    }

    // Updates the player's rank
    public void changeRank(int value) {
        if(this.rank + value >= 0){
            this.rank += value;
        }
    }

    // Returns whether the player is equal to another player
    public boolean equals(Player player) {
        return this.username.equals(player.getUsername());
    }

    // Responsible for sending a message
    public void sendMessage(String message) {
        this.writer.println("MSG_RECEIVE" + "/space" + message);
    }

    // Responsible for receiving a message
    public String receiveMessage() {
        try {
            this.writer.println("MSG_SEND");
            return this.reader.readLine();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    // Shows the player's information
    public void showInfo() {
        System.out.println("Username: " + this.username);
        System.out.println("Rank: " + this.rank);
        System.out.println("Socket: " + this.socket);
        System.out.println("Token: " + this.token);
        System.out.println("Password: " + this.password);
    }

}
