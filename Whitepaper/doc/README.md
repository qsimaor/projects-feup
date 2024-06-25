# CPD Project 2

## Project Description

This is a project focused on Distributed Systems to consolidate the theoretical lectures of Parallel and Distributed Computing. We implemented a client-server system capable of handling the authentication of different users and allocating them to the desired game mode. To provide the best experience to our players, we implemented the necessary measures to ensure fault tolerance(each player is assigned a token so it doesn't lose its queue position) and to handle concurrency(usage of locks and JAVA virtual threads).


## Game Rules

The implemented game is called Whitepaper. It consists of a turn-based game involving 5 players where 1 of them is randomly chosen at the beginning to be the whitepaper. Given your role, your objective changes:

- Regular player: At the start of the game each regular player is given the same word. Each round the player must tell a word related to the given word and try to discover who the whitepaper is based on the other player's answer.

- Whitepaper player: Since the whitepaper doesn't know the given word, its objective is to hide its identity for as long as possible by giving words each round that are close enough.

After each round, a voting is done to decide who is the whitepaper and eliminate. The game ends when the whitepaper is found or when the only players remaining are the whitepaper and 1 regular player.

## How to compile and run

### Server
- Compile(on Ubuntu): javac -cp .:../lib/* Server.java
- Run(on Ubuntu): java -cp .:../lib/* Server \<port>
- Compile(on Windows): javac -cp .;..\lib\\* Server.java
- Run(on Windows): java -cp .;..\lib\\* Server \<port>

### Player
- Compile(on Ubuntu): javac -cp .:../lib/* PlayerConnection.java
- Run(on Ubuntu): java -cp .:../lib/* PlayerConnection localhost \<port>
- Compile(on Windows): javac -cp .;..\lib\\* PlayerConnection.java
- Run(on Windows): java -cp .;..\lib\\* PlayerConnection localhost \<port>

### Script

- Script(Ubuntu): chmod +x run_game.sh; ./run_game.sh

If you wish for a faster way to start a game, we recommend using the given script that will automatically open a terminal running the server and 5 other terminals on the menu waiting for your input. Note: to run the script you must be in the 'src' directory.

## Credentials

| Username   | Password   |
|------------|------------|
| player1    | player1    |
| player2    | player2    |
| player3    | player3    |
| player4    | player4    |
| JOAO       | JOAO       |
| JOAO2      | JOAO2      |
| RODRI      | RODRI      |
| RODRI2     | RODRI2     |