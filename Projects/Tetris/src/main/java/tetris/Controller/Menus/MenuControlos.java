package tetris.Controller.Menus;

import com.googlecode.lanterna.screen.TerminalScreen;
import tetris.Model.Grid;

import java.util.List;
import java.util.Vector;

import static tetris.Controller.Jogo.refreshScreen;
public class MenuControlos extends Menu {
    public MenuControlos(TerminalScreen screen) {
        super(screen);
        inputOpcoes = "s";
    }

    @Override
    public void mostrarMenu() {
        gridDesign.pintarTexto("UP      Rodar Peca", 20, 20);
        gridDesign.pintarTexto("RIGHT   Mover Direita", 20, 22);
        gridDesign.pintarTexto("LEFT    Mover Esquerda", 20, 24);
        gridDesign.pintarTexto("DOWN    Mover para Baixo", 20, 26);
        gridDesign.pintarTexto("SPACE   Drop Instantaneo", 20, 28);
        gridDesign.pintarTexto("S       Comecar", 20, 32);
        gridDesign.pintarTexto("Q       Sair", 20, 34);
        Grid controlosGrid = new Grid(29,5,7,10, 1);
        controlosGrid.setMatriz(getGraficosMatriz());
        gridDesign.pintarGrid(controlosGrid);
        refreshScreen(screen);
    }

    @Override
    public List<List<String>> getGraficosMatriz() {
        List<String> referencia = new Vector<>();
        referencia.add("RRROOOYY--YGGGBBBPPPR--OOOYYY");
        referencia.add("R--O-OYY--Y-G-B-BP-PR--O-OY--");
        referencia.add("R--O-OY-Y-Y-G-BB-P-PR--O-OYYY");
        referencia.add("R--O-OY--YY-G-B-BP-PR--O-O--Y");
        referencia.add("RRROOOY--YY-G-B-BPPPRRROOOYYY");
        return getMatrizCores(referencia);
    }
}
