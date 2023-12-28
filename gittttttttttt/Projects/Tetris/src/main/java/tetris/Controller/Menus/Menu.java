package tetris.Controller.Menus;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.googlecode.lanterna.screen.TerminalScreen;
import tetris.View.GridDesign;

import java.io.IOException;
import java.util.List;
import java.util.Vector;

import static tetris.Controller.Jogo.quitGame;

public abstract class Menu {

    protected GridDesign gridDesign;
    protected TerminalScreen screen;
    protected String inputOpcoes;

    public Menu(TerminalScreen screen) {
        this.screen = screen;
        this.gridDesign = new GridDesign(screen.newTextGraphics());
    }

    public Character run(){
        screen.clear();
        mostrarMenu();
        return Character.toLowerCase(verificarInput());
    }

    public abstract void mostrarMenu();
    public abstract List<List<String>> getGraficosMatriz();

    public List<List <String>> getMatrizCores(List<String> reference){
        List<List <String>> matriz = new Vector<>();
        for (int j = 0; j<reference.size(); j++){
            matriz.add(new Vector<>());
            for(int i = 0; i<reference.get(j).length(); i++)
                switch (reference.get(j).charAt(i)){
                    case 'P' -> matriz.get(j).add("#910091");
                    case 'O' -> matriz.get(j).add("#FF7F00");
                    case 'G' -> matriz.get(j).add("#00FF00");
                    case 'B' -> matriz.get(j).add("#0000FF");
                    case 'Y' -> matriz.get(j).add("#FFFF00");
                    case 'R' -> matriz.get(j).add("#FF0000");
                    case '-' -> matriz.get(j).add("#000000");
                }
        }
        return matriz;
    }

    public Character verificarInput(){
        KeyStroke key = lerInput();
        if(key == null || key.getKeyType()!= KeyType.Character)
            return verificarInput();
        if (key.getCharacter() == 'q' || key.getCharacter() == 'Q')
            quitGame(screen);
        if(inputOpcoes.indexOf(key.getCharacter()) != -1 ||
                inputOpcoes.indexOf(Character.toLowerCase(key.getCharacter())) != -1)
            return key.getCharacter();
        return verificarInput();
    }

    public KeyStroke lerInput(){
        try {
            return screen.readInput();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
