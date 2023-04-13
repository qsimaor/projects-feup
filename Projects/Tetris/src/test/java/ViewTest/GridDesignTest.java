package ViewTest;

import tetris.Model.Grid;
import tetris.Model.Pecas.Peca3;
import tetris.View.GridDesign;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;

public class GridDesignTest {

    @Test
    void pintarGrid() {
        TextGraphics board= Mockito.mock(TextGraphics.class);
        GridDesign gridDesign = new GridDesign(board);
        Grid grid1 = new Grid(1,1,10,10,10);
        gridDesign.pintarGrid(grid1);
        Mockito.verify(board, Mockito.times(1)).setBackgroundColor(TextColor.Factory.fromString("#505050"));

        TextGraphics board2= Mockito.mock(TextGraphics.class);
        GridDesign gridDesign2 = new GridDesign(board2);
        Grid grid2 = new Grid(2,2,10,10,10);
        gridDesign2.pintarGrid(grid2);
        Mockito.verify(board2, Mockito.times(4)).setBackgroundColor(TextColor.Factory.fromString("#505050"));
    }

    @Test
    void pintarListaGrid() {
        TextGraphics board= Mockito.mock(TextGraphics.class);
        GridDesign gridDesign = new GridDesign(board);
        Grid grid1 = new Grid(1,1,10,10,10);
        Grid grid2 = new Grid(2,2,10,10,10);
        List<Grid> grids = new ArrayList<>();
        grids.add(grid1);
        grids.add(grid2);
        gridDesign.pintarListaGrid(grids);
        Mockito.verify(board, Mockito.times(5)).setBackgroundColor(TextColor.Factory.fromString("#505050"));
    }

    @Test
    void pintarPeca() {
        Peca3 peca3 = new Peca3();
        TextGraphics board= Mockito.mock(TextGraphics.class);
        GridDesign gridDesign = new GridDesign(board);
        String lPieceColor = "#FF7F00";
        Grid grid1 = new Grid(1,1,10,10,10);
        gridDesign.pintarPeca(peca3,grid1);
        Mockito.verify(board, Mockito.times(1)).setBackgroundColor(TextColor.Factory.fromString(lPieceColor));
    }

    @Test
    void pintarTexto(){
        TextGraphics board= Mockito.mock(TextGraphics.class);
        GridDesign gridDesign = new GridDesign(board);
        gridDesign.pintarTexto("Welcome", 10, 10);
        Mockito.verify(board, Mockito.times(1)).setForegroundColor(TextColor.Factory.fromString("#FFFFFF"));
    }
}
