import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.net.Socket;
import org.json.JSONObject;
import org.json.JSONArray;
import java.io.IOException;
import java.text.ParseException;

import org.jasypt.util.password.StrongPasswordEncryptor;

public class Database {

    private File file;
    private final JSONObject database;

    // Constructor: initializes the database from a specified file
    public Database(String filename)throws IOException, ParseException {

        this.file = new File(filename);
        if(!this.file.exists()){
            System.out.println("File not found, creating default database");
            this.file = new File("credentials.json");
        }

        StringBuilder builder = new StringBuilder();
        BufferedReader reader = new BufferedReader(new FileReader(this.file));
        String line;
        while ((line = reader.readLine()) != null) {
            builder.append(line);
        }
        reader.close();
        this.database = new JSONObject(builder.toString());
    }

    // Updates the rank of a player in the database
    public void updatePlayerRank(Player player){
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            String storedUsername = (String) user.get("username");
            if (storedUsername.equals(player.getUsername())) {
                user.put("rank", player.getRank());
            }
        }
    }

    // Writes the updated data back to the JSON file
    public void updateDatabase() throws IOException {
        FileWriter fileWriter = new FileWriter(this.file);
        fileWriter.write(this.database.toString());
        fileWriter.close();
    }

    // Resets the session tokens for all users in the database
    public void resetTokens() {
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            user.put("token", "");
        }
    }

    // Resets the session token for a specific player
    public void resetPlayerToken(Player player) {
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            String storedUsername = (String) user.get("username");
            if (storedUsername.equals(player.getUsername())) {
                user.put("token", "");
            }
        }
    }

    // Authenticates a user and returns a Player object if successful
    public Player login(String inputUsername, String inputPassword, String token, Socket socket) {
        System.out.println("Login attempt");
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            String storedUsername = (String) user.get("username");
            String storedPassword = (String) user.get("password");
            StrongPasswordEncryptor passwordEncryptor = new StrongPasswordEncryptor();

            if (storedUsername.equals(inputUsername) && passwordEncryptor.checkPassword(inputPassword, storedPassword)) {
                System.out.println("Login successful");
                user.put("token", token);
                Long rank = ((Number) user.get("rank")).longValue();
                return (new Player(inputUsername, storedPassword,rank, socket,token));
            }
        }
        return null;
    }

    // Registers a new user and returns a Player object if successful
    public Player register(String inputUsername, String inputPassword,String token, Socket socket){
        System.out.println("Register attempt");
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            String storedUsername = (String) user.get("username");

            if (storedUsername.equals(inputUsername)) {
                return null;
            }
        }

        JSONObject newUser = new JSONObject();
        newUser.put("username", inputUsername);
        String hashedPassword = new StrongPasswordEncryptor().encryptPassword(inputPassword);
        newUser.put("password", hashedPassword);
        newUser.put("rank", 0);
        newUser.put("token", token);
        databaseArray.put(newUser);
        this.database.put("database", databaseArray);

        return new Player(inputUsername, hashedPassword, 0L, socket, token);
    }

    // Allows a user to reconnect using a session token
    public Player reconnect(String token,Socket socket){
        JSONArray databaseArray = (JSONArray) this.database.get("database");
        for (Object obj : databaseArray) {
            JSONObject user = (JSONObject) obj;
            String storedToken = (String) user.get("token");
            if (storedToken.equals(token)) {
                String storedUsername = (String) user.get("username");
                String storedPassword = (String) user.get("password");
                Long rank = ((Number) user.get("rank")).longValue();
                return (new Player(storedUsername, storedPassword,rank, socket,token));
            }
        }
        return null;
    }

}
