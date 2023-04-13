package tetris.View;

import tetris.Model.Grid;
import tetris.Model.Pecas.Peca;
import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;

import java.util.List;

public class GridDesign {
    private TextGraphics board;
    public GridDesign(TextGraphics board) {this.board = board;}

    public void pintarGrid(Grid grid){
        int x;
        int y = grid.getY();
        for (List<String> linha : grid.getMatriz()) {
            x = grid.getX();
            for (String cor : linha){
                board.setBackgroundColor(TextColor.Factory.fromString(cor));
                board.fillRectangle(new TerminalPosition(x,y),
                        new TerminalSize(grid.getTamanhoBloco() * 2, grid.getTamanhoBloco()), ' ');
                x += grid.getTamanhoBloco() * 2;
            }
            y += grid.getTamanhoBloco();
        }
    }

    public void pintarListaGrid(List<Grid> grids){
        for (Grid grid : grids) {
            pintarGrid(grid);
        }
    }

    public void pintarPeca(Peca peca, Grid grid){
        int x;
        int y = grid.getY() - 4 + peca.getY() * grid.getTamanhoBloco();
        board.setBackgroundColor(TextColor.Factory.fromString(peca.getCor()));

        for (String linha : peca.getForma()){
            x = grid.getX() + peca.getX() * grid.getTamanhoBloco() * 2 - 8;
            for(int i = 0; i < linha.length(); i++){
                if(linha.charAt(i) == '0' && y >= grid.getY())
                    board.fillRectangle(new TerminalPosition(x - 4 + i * 2, y),
                            new TerminalSize(grid.getTamanhoBloco() * 2, grid.getTamanhoBloco()), ' ');
                x += grid.getTamanhoBloco();
            }
            y += grid.getTamanhoBloco();
        }
    }

    public void pintarTexto(String text, int x, int y){
        board.setBackgroundColor(TextColor.Factory.fromString("#000000"));
        board.setForegroundColor(TextColor.Factory.fromString("#FFFFFF"));
        board.putString(new TerminalPosition(x, y), text);
    }
}
