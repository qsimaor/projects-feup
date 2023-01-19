package tetris;

import tetris.Controller.Jogo;

import java.io.IOException;

public class Application {
    public static void main(String[] args) throws IOException {
        Jogo jogo = new Jogo();
        jogo.run();
    }
}