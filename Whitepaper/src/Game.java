import java.util.*;

public class Game implements Runnable {

    private List<Player> players;
    private int whitepaper;
    private List<String> wordPool;
    private String chosenWord;
    private List<AbstractMap.SimpleEntry<String, String>> players_words;
    private int num_words_said_in_round;
    private int turn;
    private int round;
    private boolean game_over;
    private boolean isRanked;

    // Constructor: initializes the game with players, word pool, and ranked mode
    public Game(List<Player> players, List<String> wordPool, boolean isRanked) {
        this.players = players;
        this.wordPool = wordPool;
        this.turn = 0;
        this.round = 0;
        this.num_words_said_in_round = 0;
        this.players_words = new ArrayList<AbstractMap.SimpleEntry<String, String>>();
        this.game_over = false;
        this.isRanked = isRanked;
    }

    // Updates the ranks of players based on their performance
    private void updateRanks() {
        for (Player player : players) {
            if (player.isWhitepaper()) {
                player.changeRank(-1 + this.round);
            } else {
                player.changeRank(2 - this.round);
            }
        }
    }

    // Voting system for the players to vote for who they think the whitepaper is
    // Returns the index of the player that has been kicked out of the game
    private int vote_for_whitepaper() {
        Map<Integer, Integer> voteCount = new HashMap<>();

        // Initialize vote count for each player
        for (int i = 0; i < players.size(); i++) {
            if (players.get(i).isPlaying()) {
                voteCount.put(i, 0);
            }
        }

        broadcast("Voting for the whitepaper has started, please wait fo your turn");

        for (int i = 0; i < players.size(); i++) {
            if (players.get(i).isPlaying()) {
                players.get(i).sendMessage("Vote for the player you think is the whitepaper (enter the number):");

                int index = 0;
                for (Player player : players) {
                    if (player.isPlaying()) {
                        players.get(i).sendMessage(index + " - " + player.getUsername());
                    }
                    index++;
                }

                String vote = "";
                int voteIndex = -1;

                // Check if the vote is valid
                while (voteIndex == -1) {
                    vote = players.get(i).receiveMessage();
                    try {
                        voteIndex = Integer.parseInt(vote);
                        if (players.get(i).isPlaying() && voteIndex >= 0 && voteIndex < players.size()
                                && players.get(voteIndex).isPlaying() && voteIndex != i) {
                            voteCount.put(voteIndex, voteCount.get(voteIndex) + 1);

                        } else {
                            players.get(i).sendMessage("Invalid vote. Please vote again.");
                            voteIndex = -1;
                        }
                    } catch (NumberFormatException | IndexOutOfBoundsException e) {
                        voteIndex = -1;
                        players.get(i).sendMessage("Invalid vote. Please vote again.");
                    }
                }

                broadcast("Player " + players.get(i).getUsername() + " voted for player "
                        + players.get(voteIndex).getUsername());
            }
        }

        // Find the player with the most votes
        int maxVotes = 0;
        int playerToKick = -1;
        boolean tie = false;

        for (Map.Entry<Integer, Integer> entry : voteCount.entrySet()) {
            if (entry.getValue() > maxVotes) {
                maxVotes = entry.getValue();
                playerToKick = entry.getKey();
                tie = false;
            } else if (entry.getValue() == maxVotes) {
                tie = true;
            }
        }

        // Check if there is a tie
        if (tie) {
            return -1;
        }

        return playerToKick;
    }

    // Broadcasts a message to all players in the game
    private void broadcast(String message) {

        for (Player player : players)
            player.sendMessage(message);
    }

    // Starts the game by choosing a random whitepaper and a random word from the word pool
    private void start() {
        broadcast("Starting game with " + players.size() + " players");

        for (Player player : this.players) {
            System.out.println("Player " + player.getUsername() + " is playing");
            player.setPlaying(true);
        }

        broadcast("Whitepaper will now be chosen");

        // Choose a random player to be the whitepaper
        this.whitepaper = (int) (Math.random() * players.size());

        players.get(this.whitepaper).setWhitePaper(true);

        // Pick a random word from the word pool
        this.chosenWord = this.wordPool.get((int) (Math.random() * wordPool.size()));

        // Send the chosen word to the players and the word "whitepaper" to the chosen player
        for (int i = 0; i < players.size(); i++) {
            Player player = players.get(i);
            String word = (i == this.whitepaper) ? "whitepaper" : this.chosenWord;
            player.sendMessage("Your word is " + word);
        }

        this.turn = 0;
    }

    // Proceeds to the next turn of the game
    // If all players have played, end the round
    private void nextTurn() {

        if (this.turn == players.size()) {
            endRound();
            return;
        }

        Player player = players.get(this.turn);
        this.turn += 1;

        if (player.isPlaying()) {
            broadcast("It is now " + player.getUsername() + "'s turn.");

            player.sendMessage("Please say your word:");

            String word = player.receiveMessage();

            players_words.add(new AbstractMap.SimpleEntry<String, String>(player.getUsername(), word));

            broadcast("Player " + player.getUsername() + " said the word: " + word);

            this.num_words_said_in_round += 1;
        }
    }

    // Broadcasts the words said by the players in the round
    // Ends the round by kicking out the player with the most votes
    // If there is a tie, no player is kicked out
    private void endRound() {
        this.round += 1;
        this.turn = 0;

        broadcast("Round " + this.round + " has ended");

        for (int i = this.num_words_said_in_round - 1; i >= 0; i--) {
            String player = this.players_words.get(i).getKey();
            String word = this.players_words.get(i).getValue();
            broadcast("Player " + player + " said the word: " + word);
        }

        players_words.clear();

        // Reset number of words said in the round
        this.num_words_said_in_round = 0;

        int kicked_player = vote_for_whitepaper();

        if (kicked_player != -1) {
            broadcast("Player " + players.get(kicked_player).getUsername() + " has been kicked out of the game");
            players.get(kicked_player).setPlaying(false);
            check_game_over();
        } else {
            broadcast("No player has been kicked out of the game");
        }

        if (!this.game_over) {
            broadcast("Starting round " + this.round + "!");
        }
    }

    // Counts the number of players that are still playing
    private int count_playing_players() {
        int count = 0;

        for (Player player : this.players) {
            if (player.isPlaying()) {
                count += 1;
            }
        }

        return count;
    }

    // Checks if the game is over
    // If there are only two players left and the whitepaper is still playing, the whitepaper has won
    // If the whitepaper is not playing, the game is over and whitepaper has lost
    private void check_game_over() {
        if (count_playing_players() == 2 && players.get(this.whitepaper).isPlaying()) {
            this.game_over = true;
            broadcast("Whitepaper has won the game");
        } else if (!players.get(this.whitepaper).isPlaying()) {
            this.game_over = true;
            if (isRanked) {
                updateRanks();
            }
            broadcast("Game has ended. Whitepaper has been kicked out of the game");
        } else {
            broadcast("Game is not over yet");
            broadcast(count_playing_players() + " players are still playing");
        }
    }

    // Ends the game by setting all players to not playing
    private void endGame() {
        broadcast("Game has ended");

        for (Player player : this.players) {
            player.setPlaying(false);
            player.setWhitePaper(false);
        }
    }

    // Runs the game
    // Starts the game, proceeds to the next turn until the game is over, and then ends the game
    @Override
    public void run() {
        System.out.println("Game has started");
        broadcast("You have entered a game!");
        // Start the game
        this.start();

        while (!this.game_over) {
            this.nextTurn();
        }
        this.endGame();

        return;
    }

}
