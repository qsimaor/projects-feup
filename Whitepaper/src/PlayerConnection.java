import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.Connection;
import java.util.Scanner;

public class PlayerConnection {
    private final int port;
    private final String hostname;
    private static Socket socket;

    // Constructor: initializes the connection with the server's hostname and port
    PlayerConnection(String hostname, int port) {
        this.hostname = hostname;
        this.port = port;
    }

    // Updates the player's token in a specified file
    public void updateToken(String filename, String token) {
        File file = new File("./tokens/" + filename);
        try {
            if (file.getParentFile() != null && !file.getParentFile().exists()) {
                file.getParentFile().mkdirs(); // Create directories if they don't exist
            }
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                writer.write(token);
            }
        } catch (IOException e) {
            System.err.println("Error while updating token: " + e.getMessage());
            e.printStackTrace(); // Print the stack trace for more detailed debugging
        }
    }

    // Establishes a connection to the server
    public void connect() throws UnknownHostException, IOException {
        try {
            this.socket = new Socket(this.hostname, this.port);
            System.out.println("Connected to the server");
        } catch (IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
        }
    }

    // Authenticates the player with the server
    public boolean authentication() throws IOException {
        String[] serverResponse;
        String requestType;
        OutputStream output = this.socket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);
        InputStream input = this.socket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        Scanner scanner;
        String option;

        do {
            serverResponse = reader.readLine().split("/space");
            requestType = serverResponse[0];
            switch (requestType) {
                case "MNU":
                    System.out.println(serverResponse[1]);
                    System.out.println(serverResponse[2]);
                    System.out.println(serverResponse[3]);
                    System.out.println(serverResponse[4]);
                    scanner = new Scanner(System.in);
                    option = scanner.nextLine();
                    writer.println(option);
                    break;
                case "USR":
                    System.out.println("Enter your username: ");
                    scanner = new Scanner(System.in);
                    String username = scanner.nextLine();
                    writer.println(username);
                    break;
                case "PWD":
                    System.out.println("Enter your password: ");
                    scanner = new Scanner(System.in);
                    String password = scanner.nextLine();
                    writer.println(password);
                    break;
                case "TOK":
                    System.out.println(serverResponse[1]);
                    scanner = new Scanner(System.in);
                    String token = scanner.nextLine();
                    writer.println(token);
                    break;
                case "ERR":
                    System.out.println("Error: " + serverResponse[1]);
                    writer.println("ACK");
                    break;
                case "AUTH":
                    writer.println("ACK");
                    updateToken(serverResponse[1],serverResponse[2]);
                    break;
                case "FIN":
                    System.out.println(serverResponse[1]);
                    break;
                default:
                    System.out.println("Invalid request type:" + requestType + " received from server");
                    break;
            }
        } while (!requestType.equals("AUTH") && !requestType.equals("FIN"));
        return requestType.equals("AUTH");
    }

    // Handles the game mode selection and communication with the server during matchmaking
    public void searching() throws IOException {
        String[] serverResponse;
        String mode;
        String requestType;
        Scanner scanner;
        OutputStream output = this.socket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);
        InputStream input = this.socket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));

        do {
            serverResponse = reader.readLine().split("/space");
            requestType = serverResponse[0];
            switch (requestType) {
                case "QUE":
                    System.out.println(serverResponse[1]);
                    writer.println("ACK");
                    break;
                case "MOD":
                    System.out.println("Choose the mode you wish to play: ");
                    System.out.println("1 - Normal");
                    System.out.println("2 - Ranked");
                    System.out.println("3 - Exit Game");
                    scanner = new Scanner(System.in);
                    mode = scanner.nextLine();
                    writer.println(mode);
                    break;
                case "FIN":
                    System.out.println(serverResponse[1]);
                    break;
                case "PING":
                    break;
                case "MSG_RECEIVE":
                    System.out.println(serverResponse[1]);
                    break;
                case "MSG_SEND":
                    scanner = new Scanner(System.in);
                    String message = scanner.nextLine();
                    writer.println(message);
                    break;
                case "ERR":
                    System.out.println("Error: " + serverResponse[1]);
                    break;
                default:
                    System.out.println("Invalid request type:" + requestType + " received from server");
                    break;
            }
        } while (!requestType.equals("FIN"));
    }

    // Main method: handles the initialization and connection process
    public static void main(String[] args) {
        boolean connected = false;
        if (args.length < 2) {
            System.out.println("Usage: java PlayerConnection <hostname> <port>");
            return;
        }

        try {
            String hostname = args[0];
            int port = Integer.parseInt(args[1]);
            PlayerConnection playerConnection = new PlayerConnection(hostname, port);
            playerConnection.connect();
            if (playerConnection.authentication()) {
                System.out.println("Authentication successful. Welcome!");
                connected = true;
                playerConnection.searching();
            } else {
                System.out.println("Authentication failed");
                socket.close();
            }
        } catch (UnknownHostException ex) {
            System.out.println("Server not found: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
        } finally {
            if (connected) {
                try {
                    System.out.println("Thanks for playing, see you next time!");
                    socket.close();
                } catch (IOException e) {
                    System.out.println("Error while closing connection: " + e.getMessage());
                }
            }
        }
    }

}
