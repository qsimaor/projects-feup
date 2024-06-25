package tetris.Controller.Menus;

import com.googlecode.lanterna.screen.TerminalScreen;
import tetris.Model.Grid;

import java.util.List;
import java.util.Vector;

import static tetris.Controller.Jogo.refreshScreen;

public class MenuInicial extends Menu {
    public MenuInicial(TerminalScreen screen) {
        super(screen);
        inputOpcoes = "sc";
    }

    @Override
    public void mostrarMenu(){
        gridDesign.pintarTexto("Pressione S para Comecar", 20, 20);
        gridDesign.pintarTexto("Pressione C para Controlos", 20, 22);
        gridDesign.pintarTexto("Pressione Q para Sair", 20, 24);
        Grid tetrisGrid = new Grid(23,5,13,10, 1);
        tetrisGrid.setMatriz(getGraficosMatriz());
        gridDesign.pintarGrid(tetrisGrid);
        refreshScreen(screen);
    }

    @Override
    public List<List<String>> getGraficosMatriz() {
        List<String> referencia = new Vector<>();
        referencia.add("RRR-OOO-YYY-GGG-BBB-PPP");
        referencia.add("-R--O----Y--G-G--B--P--");
        referencia.add("-R--OOO--Y--GG---B--PPP");
        referencia.add("-R--O----Y--G-G--B----P");
        referencia.add("-R--OOO--Y--G-G-BBB-PPP");
        return getMatrizCores(referencia);
    }
}
