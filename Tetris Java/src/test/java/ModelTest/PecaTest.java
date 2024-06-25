package ModelTest;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import tetris.Model.Grid;
import tetris.Model.Pecas.*;

public class PecaTest {
    int valor = 1;
    Grid grid = new Grid(10, 10, 10, 10, 10);
    Peca1 Peca1 = new Peca1();
    Peca2 Peca2 = new Peca2();
    Peca3 Peca3 = new Peca3();
    Peca4 Peca4 = new Peca4();
    Peca5 Peca5 = new Peca5();
    Peca6 Peca6 = new Peca6();
    Peca7 Peca7 = new Peca7();

    @Test
    public void rotacaoTest() {
        this.Peca6.rotacao(this.grid);
        Peca6.verificar(grid);
        this.Peca5.rotacao(this.grid);
        Peca5.verificar(grid);
        this.Peca7.rotacao(this.grid);
        Peca7.verificar(grid);
        this.Peca2.rotacao(this.grid);
        Peca2.verificar(grid);
        Assertions.assertEquals(this.valor, this.Peca6.getRotacao());
        this.Peca4.rotacao(this.grid);
        Assertions.assertEquals(0, this.Peca4.getRotacao());
    }

    @Test
    public void moverRightTest() {
        this.Peca3.moverRight(this.grid);
        Assertions.assertEquals(6 + this.valor, this.Peca3.getX());
        Assertions.assertNotEquals(6 , this.Peca3.getX());
        this.Peca3.setX(12);
        this.Peca3.setY(18);
        this.Peca3.moverRight(this.grid);
        Assertions.assertEquals(12, this.Peca3.getX());
        Assertions.assertNotEquals(14,this.Peca3.getX());
    }

    @Test
    public void moverLeftTest() {
        this.Peca1.moverLeft(this.grid);
        Assertions.assertEquals(6 - this.valor, this.Peca1.getX());
        this.Peca1.setX(12);
        this.Peca1.setY(18);
        this.Peca1.moverLeft(this.grid);
        Assertions.assertEquals(12, this.Peca1.getX());
    }

    @Test
    public void moverDownTest() {
        this.Peca4.moverDown();
        Assertions.assertEquals(-1+this.valor, this.Peca4.getY());
    }

    @Test
    public void moverUpTest() {
        this.Peca5.moverUp();
        Assertions.assertEquals(-1-this.valor, this.Peca5.getY());
    }

    @Test
    public void getFormatest() {
        Assertions.assertNotNull(this.Peca1.getForma());
    }

    @Test
    public void getAltura() {
        Assertions.assertEquals(4, this.Peca1.getAltura());
        Assertions.assertEquals(3, this.Peca2.getAltura());
        Assertions.assertEquals(3, this.Peca3.getAltura());
        Assertions.assertEquals(2, this.Peca4.getAltura());
        Assertions.assertEquals(3, this.Peca5.getAltura());
        Assertions.assertEquals(3, this.Peca6.getAltura());
        Assertions.assertEquals(3, this.Peca7.getAltura());
    }

    @Test
    public void rerotacaotest() {
        this.Peca2.reRotacao();
        Peca2.verificar(grid);
        Assertions.assertEquals(this.Peca2.getForma().size() - 2, this.Peca2.getRotacao());
        Assertions.assertNotEquals(this.Peca2.getForma().size()-1, this.Peca2.getRotacao());
        this.Peca5.setRotacao(1);
        Peca5.verificar(grid);
        Assertions.assertNotEquals(this.Peca5.getForma().size()-2, this.Peca5.getRotacao());

    }

    @Test
    public void setXTest() {
        this.Peca1.setX(2);
        Assertions.assertEquals(2, this.Peca1.getX());
        Assertions.assertNotEquals(4, this.Peca1.getX());
    }

    @Test
    public void setYTest() {
        this.Peca1.setY(3);
        Assertions.assertEquals(3, this.Peca1.getY());
        Assertions.assertNotEquals(5, this.Peca1.getY());
    }

    @Test
    public void setrotacaoTest() {
        this.Peca1.setRotacao(3);
        Assertions.assertEquals(3, this.Peca1.getRotacao());
        Assertions.assertNotEquals(5, this.Peca1.getRotacao());
    }

    @Test
    public void verificarTest() {
        this.Peca3.setX(1);
        this.Peca3.setY(18);
        Peca3.verificar(grid);
    }

    @Test
    public void checkTest() {
        Assertions.assertTrue(Peca3.verificarDireita(grid));
        Assertions.assertTrue(Peca3.verificarEsquerda(grid));
        Assertions.assertTrue(Peca3.verificarBaixo(grid));
        Peca1.setX(-2);
        Peca1.setY(0);
        Assertions.assertFalse(Peca1.verificarDireita(grid));
        Assertions.assertFalse(Peca1.verificarEsquerda(grid));
        Assertions.assertFalse(Peca1.verificarBaixo(grid));
    }

    @Test
    public void SetCorTest() {
        Peca7.setCor("#1111111");
        Assertions.assertNotEquals(Peca7.getCor(), "#OOOOFF");
        Peca2.setCor("#1111111");
        Assertions.assertNotEquals(Peca2.getCor(), "#910091");
        Peca4.setCor("#1111111");
        Assertions.assertNotEquals(Peca4.getCor(), "#FF7F00");
        Peca6.setCor("#1111111");
        Assertions.assertNotEquals(Peca6.getCor(), "#FF0000");
    }

    @Test
    public void Peca1verificar() {
        Assertions.assertTrue(Peca1.verificarDireita2(grid));
        this.Peca1.setX(-3);
        this.Peca1.setY(0);
        Peca1.verificar(grid);
        Assertions.assertFalse(Peca1.verificarDireita2(grid));
    }
}