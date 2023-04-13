package ModelTest;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import tetris.Model.Grid;
import tetris.Model.Pecas.Peca;
import tetris.Model.Pecas.Peca1;

import java.util.List;
import java.util.Vector;

public class GridTest {

    Grid grid1 =  new Grid(5, 5, 4, 3, 1);
    List<List<String>> matrix1 = new Vector<>();
    public void criarmatriz1(int height,int width){
        for (int i = 0; i < height; i++){
            List<String> line = new Vector<>();
            for(int j = 0; j < width; j++){
                line.add("#505050");
            }
            matrix1.add(line);
        }
    }

    Peca peca1 = new Peca1();
    Grid grid2 =  new Grid(peca1, 7, 6, 1);
    List<List<String>> matrix2 = new Vector<>();
    public void criarmatriz2(int height,int width){
        for (int i = 0; i < height; i++){
            List <String> line = new Vector<>();
            for(int j = 0; j < width; j++){
                if (peca1.getForma().get(i).charAt(j) == '.')
                    line.add("#505050");
                else
                    line.add(peca1.getCor());
            }
            matrix2.add(line);
        }
    }

    @Test
    public void gets() {
        Assertions.assertEquals(5, grid2.getAltura());
        Assertions.assertEquals(5, grid2.getComprimento());
        Assertions.assertEquals(7, grid2.getX());
        Assertions.assertEquals(6, grid2.getY());
        Assertions.assertEquals(1, grid2.getTamanhoBloco());
        criarmatriz2(5,5);
        Assertions.assertEquals(matrix2, grid2.getMatriz());

        Assertions.assertEquals(5, grid1.getAltura());
        Assertions.assertEquals(5, grid1.getComprimento());
        Assertions.assertEquals(4, grid1.getX());
        Assertions.assertEquals(3, grid1.getY());
        Assertions.assertEquals(1, grid1.getTamanhoBloco());
        criarmatriz1(5,5);
        Assertions.assertEquals(matrix1, grid1.getMatriz());
    }

    List<List<String>> matrix3 = new Vector<>();
    public void criarmatriz3(int height,int width){
        matrix3.clear();
        for (int i = 0; i < height; i++){
            List<String> line = new Vector<>();
            for(int j = 0; j < width; j++){
                line.add("#505050");
            }
            matrix1.add(line);
        }
    }

    @Test
    public void setmatriz() {
        criarmatriz3(6,6);
        Assertions.assertFalse(grid1.setMatriz(matrix3));
        criarmatriz2(5,5);
        Assertions.assertTrue(grid1.setMatriz(matrix2));
    }

    @Test
    public void valido() {
        int playWidth = 10;
        int playHeight = 20;
        int screenWidth = playWidth*4 + 32;
        int screenHeight = playHeight*2 + 6;
        Grid playGrid1 = new Grid(playWidth, playHeight, (screenWidth - playWidth*4)/2,
                (screenHeight - playHeight*2)/2, 2);
        Assertions.assertTrue(playGrid1.valido(peca1));
        peca1.setX(80);
        Assertions.assertFalse(playGrid1.valido(peca1));
        peca1.setX(6);
        peca1.setY(20);
        Assertions.assertFalse(playGrid1.valido(peca1));
        peca1.setY(6);
        Assertions.assertTrue(playGrid1.valido(peca1));

        List<List<String>> matrix = new Vector<>();
        for (int i = 0; i < playHeight; i++){
            List <String> line = new Vector<>();
            for(int j = 0; j < playWidth; j++){
                line.add("#00FFFF");
            }
            matrix.add(line);
        }
        playGrid1.setMatriz(matrix);
        Assertions.assertFalse(playGrid1.valido(peca1));

    }

    @Test
    public void adicionaPeca() {
        int playWidth = 10;
        int playHeight = 20;
        int screenWidth = playWidth*4 + 32;
        int screenHeight = playHeight*2 + 6;
        Grid playGrid1 = new Grid(playWidth, playHeight, (screenWidth - playWidth*4)/2,
                (screenHeight - playHeight*2)/2, 2);
        peca1.setY(7);
        peca1.setX(8);
        playGrid1.adicionarPeca(peca1);
        Assertions.assertEquals("#00FFFF",playGrid1.getMatriz().get(peca1.getY()+0-2).get(peca1.getX()+2-3));
        Assertions.assertEquals("#00FFFF",playGrid1.getMatriz().get(peca1.getY()+1-2).get(peca1.getX()+2-3));
        Assertions.assertEquals("#00FFFF",playGrid1.getMatriz().get(peca1.getY()+2-2).get(peca1.getX()+2-3));
        Assertions.assertEquals("#00FFFF",playGrid1.getMatriz().get(peca1.getY()+3-2).get(peca1.getX()+2-3));

        Grid playGrid2 = new Grid(playWidth, playHeight, (screenWidth - playWidth*4)/2,
                (screenHeight - playHeight*2)/2, 2);
        peca1.setY(7);
        peca1.setX(8);
        peca1.rotacao(playGrid2);
        playGrid2.adicionarPeca(peca1);
        Assertions.assertEquals("#00FFFF",playGrid2.getMatriz().get(peca1.getY()+1-2).get(peca1.getX()+0-3));
        Assertions.assertEquals("#00FFFF",playGrid2.getMatriz().get(peca1.getY()+1-2).get(peca1.getX()+1-3));
        Assertions.assertEquals("#00FFFF",playGrid2.getMatriz().get(peca1.getY()+1-2).get(peca1.getX()+2-3));
        Assertions.assertEquals("#00FFFF",playGrid2.getMatriz().get(peca1.getY()+1-2).get(peca1.getX()+3-3));

    }

    @Test
    public void removerLinhas() {
        List<List<String>> matrix = new Vector<>();
        for (int i = 0; i < 5; i++){
            List <String> line = new Vector<>();
            for(int j = 0; j < 5; j++){
                if (i<3)
                    line.add("#505050");
                else
                    line.add(peca1.getCor());
            }
            matrix.add(line);
        }
        Grid grid =  new Grid(5, 5, 4, 3, 1);
        Assertions.assertEquals(0, grid.removerLinhas());
        grid.setMatriz(matrix);
        Assertions.assertEquals(2, grid.removerLinhas());
    }
}