package tetris.Controller;

import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.terminal.DefaultTerminalFactory;
import com.googlecode.lanterna.terminal.Terminal;
import tetris.Controller.Menus.MenuFinal;
import tetris.Controller.Menus.MenuControlos;
import tetris.Controller.Menus.Menu;
import tetris.Controller.Menus.MenuInicial;
import tetris.Model.Grid;
import tetris.Model.Pecas.*;
import tetris.Model.Score;
import tetris.View.GridDesign;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Jogo {
    private final int jogoLargura = 10;
    private final int jogoComprimento = 20;
    private final int ecraLargura = jogoLargura * 4 + 32;
    private final int ecraComprimento = jogoComprimento * 2 + 6;
    private boolean fimJogo;
    private boolean emRotacao;
    private GridDesign gridDesign;
    private Menu menuInicial;
    private Menu menuControlos;
    private MenuFinal menuFinal;
    private Grid jogarGrid;
    private List<Grid> listaEsperaGrid;
    private List<Peca> listaEsperaPecas;
    private Terminal terminal;
    private TerminalScreen screen;
    private Peca principalPeca;
    private long contarTempo;
    private long tempoQueda;
    private long tempoRotacao;
    private Score score;

    public Jogo() {
        TerminalSize terminalSize = new TerminalSize(ecraLargura, ecraComprimento);
        DefaultTerminalFactory terminalFactory = new DefaultTerminalFactory().setInitialTerminalSize(terminalSize);
        try {
            terminal = terminalFactory.createTerminal();
            screen = new TerminalScreen(terminal);
            screen.setCursorPosition(null);
            screen.startScreen();
        } catch (IOException e) {
            e.printStackTrace();
        }
        gridDesign = new GridDesign(screen.newTextGraphics());
        menuInicial = new MenuInicial(screen);
        menuControlos = new MenuControlos(screen);
        menuFinal = new MenuFinal(screen);
    }

    public void run() {
        char option = menuInicial.run();
        if(option == 'c')
            menuControlos.run();
        jogarGrid = new Grid(jogoLargura, jogoComprimento,
                (ecraLargura - jogoLargura * 4) / 2, (ecraComprimento - jogoComprimento * 2) / 2, 2);
        principalPeca = getPecaAleatoria();
        criarGridListaEsperaPecas();
        score = new Score();
        contarTempo = System.currentTimeMillis();
        tempoQueda = score.getTempo();
        tempoRotacao = 0;
        fimJogo = false;
        loopJogo();
    }

    public void loopJogo() {
        screen.clear();
        gridDesign.pintarTexto("Score: ", 4, 9);
        gridDesign.pintarTexto("Nivel: ", 4, 3);
        while (!fimJogo) {
            gridDesign.pintarTexto(Integer.toString(score.getPontos()), 4, 10);
            gridDesign.pintarTexto(Integer.toString(score.getNivel()),4,4);
            gridDesign.pintarGrid(jogarGrid);
            gridDesign.pintarListaGrid(listaEsperaGrid);
            gridDesign.pintarPeca(principalPeca, jogarGrid);
            refreshScreen(screen);
            verificarInput();
            if (System.currentTimeMillis() - contarTempo >= tempoQueda)
                moverPecaDown();
        }
        menuFinal.atualizarNivelPontos(score);
        menuFinal.run();
        run();
    }

    public void criarGridListaEsperaPecas() {
        listaEsperaGrid = new LinkedList<>();
        listaEsperaPecas = new LinkedList<>();
        for (int i = 0; i < 4; i++) {
            Peca wPiece = getPecaAleatoria();
            listaEsperaGrid.add(new Grid(wPiece,
                    ecraLargura - jogarGrid.getX() + 2, jogarGrid.getY() + 6 * i, 1));
            listaEsperaPecas.add(wPiece);
        }
    }

    public void moverPecaDown() {
        principalPeca.moverDown();
        if (!jogarGrid.valido(principalPeca)) {
            principalPeca.moverUp();
            if(System.currentTimeMillis() - contarTempo >= tempoQueda){
                if(emRotacao && tempoRotacao == 0)
                    tempoRotacao = System.currentTimeMillis();
                if(emRotacao && System.currentTimeMillis() - tempoRotacao < 2000)
                    return;
            }
            emRotacao = false;
            tempoRotacao = 0;
            lockprincipalPeca();
        }
        contarTempo = System.currentTimeMillis();
    }

    private void dropInstantaneo() {
        while (jogarGrid.valido(principalPeca))
            principalPeca.moverDown();
        principalPeca.moverUp();
        lockprincipalPeca();
    }

    private void lockprincipalPeca(){
        if(perder()){
            fimJogo = true;
            return;
        }
        jogarGrid.adicionarPeca(principalPeca);
        score.linhasProcessadas(jogarGrid.removerLinhas());
        score.processoNivel();
        tempoQueda = score.getTempo();
        atualizarListaEspera();
    }

    private boolean perder(){
        for(int j = 0; j< 5; j++)
            for (int i = 0; i < 5; i++)
                if(principalPeca.getForma().get(i).charAt(j)== '0' && principalPeca.getY()+i-2<0)
                    return true;
        return false;
    }

    private void atualizarListaEspera() {
        principalPeca = listaEsperaPecas.remove(0);
        listaEsperaPecas.add(getPecaAleatoria());
        listaEsperaGrid.clear();
        for (int i = 0; i < 4; i++) {
            listaEsperaGrid.add(new Grid(listaEsperaPecas.get(i),
                    ecraLargura - jogarGrid.getX() + 2, jogarGrid.getY() + 6 * i, 1));
        }
    }

    public void verificarInput() {
        KeyStroke key = getKey();
        if (key == null)
            return;
        switch (key.getKeyType()) {
            case ArrowUp -> rodarPeca();
            case ArrowRight -> principalPeca.moverRight(jogarGrid);
            case ArrowLeft -> principalPeca.moverLeft(jogarGrid);
            case ArrowDown -> moverPecaDown();
            case Character -> {
                switch (key.getCharacter()) {
                    case 'q', 'Q' -> quitGame(screen);
                    case ' ' -> dropInstantaneo();
                }
            }
        }
    }

    private void rodarPeca() {
        principalPeca.rotacao(jogarGrid);
        if(!emRotacao)
            emRotacao = true;
    }

    static public void quitGame(TerminalScreen screen) {
        try {
            screen.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.exit(0);
    }

    public Peca getPecaAleatoria() {
        int randomInt = (int) ((Math.random() * (8 - 1)) + 1);
        return switch (randomInt) {
            case 1 -> new Peca3();
            case 2 -> new Peca2();
            case 3 -> new Peca1();
            case 4 -> new Peca7();
            case 5 -> new Peca5();
            case 6 -> new Peca6();
            case 7 -> new Peca4();
            default -> throw new IllegalStateException("Unexpected value: " + randomInt);
        };
    }

    static public void refreshScreen(TerminalScreen screen) {
        try {
            screen.refresh();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public KeyStroke getKey() {
        try {
            return terminal.pollInput();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}