package tetris.Controller.Menus;

import com.googlecode.lanterna.screen.TerminalScreen;
import tetris.Model.Grid;
import tetris.Model.Score;

import java.util.List;
import java.util.Vector;

import static tetris.Controller.Jogo.refreshScreen;

public class MenuFinal extends Menu {
    int nivel;
    int score;

    public MenuFinal(TerminalScreen screen) {
        super(screen);
        inputOpcoes = "s";
        nivel = 1;
        score = 0;
    }

    @Override
    public void mostrarMenu() {
        gridDesign.pintarTexto("Nivel: " + Integer.toString(nivel), 20, 20);
        gridDesign.pintarTexto("Score: " + Integer.toString(score), 20, 22);
        gridDesign.pintarTexto("Pressione S para Recomecar", 20, 25);
        gridDesign.pintarTexto("Pressione Q para Sair", 20, 27);
        Grid menuFinalGrid = new Grid(23,11,14,5, 1);
        menuFinalGrid.setMatriz(getGraficosMatriz());
        gridDesign.pintarGrid(menuFinalGrid);
        refreshScreen(screen);
    }

    @Override
    public List<List<String>> getGraficosMatriz() {
        List<String> referencia = new Vector<>();
        referencia.add("-RRRR---O---Y---Y-GGGGG");
        referencia.add("R------O-O--YY-YY-G----");
        referencia.add("R-RRR-O---O-Y-Y-Y-GGGGG");
        referencia.add("R---R-OOOOO-Y---Y-G----");
        referencia.add("-RRRR-O---O-Y---Y-GGGGG");
        referencia.add("-----------------------");
        referencia.add("-BBB--P---P-RRRRR-OOOO-");
        referencia.add("B---B-P---P-R-----O---O");
        referencia.add("B---B-P---P-RRRRR-OOOO-");
        referencia.add("B---B--P-P--R-----O--O-");
        referencia.add("-BBB----P---RRRRR-O---O");
        return getMatrizCores(referencia);
    }

    public void atualizarNivelPontos(Score contarPontos){
        nivel = contarPontos.getNivel();
        score = contarPontos.getPontos();
    }
}
