package ControllerTest;

import com.googlecode.lanterna.screen.TerminalScreen;
import com.googlecode.lanterna.input.KeyStroke;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import tetris.Controller.Menus.Menu;
import tetris.Controller.Menus.MenuControlos;
import tetris.Controller.Menus.MenuFinal;
import tetris.Model.Score;

import javax.swing.*;
import java.io.IOException;

public class MenuTest {

    @Test
    public void verificarImputTest1() throws IOException {
        TerminalScreen screen = (TerminalScreen) Mockito.mock(TerminalScreen.class);
        Painter painter = (Painter) Mockito.mock(Painter.class);

        Mockito.when(screen.readInput()).thenReturn(KeyStroke.fromString("s"));
        Menu menu2 = new MenuControlos(screen);
        menu2.verificarInput();
        try {
            Mockito.verify(screen, Mockito.times(1)).readInput();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    @Test
    public void verificarImputTest2() throws IOException {
        TerminalScreen screen = (TerminalScreen) Mockito.mock(TerminalScreen.class);
        Painter painter = (Painter) Mockito.mock(Painter.class);

        Mockito.when(screen.readInput()).thenReturn(KeyStroke.fromString("s"));
        Menu menu3 = new MenuFinal(screen);
        menu3.verificarInput();
        try {
            Mockito.verify(screen, Mockito.times(1)).readInput();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void atualizarFimJogoTest(){
        TerminalScreen screen = (TerminalScreen) Mockito.mock(TerminalScreen.class);
        Score score = (Score) Mockito.mock(Score.class);
        MenuFinal gameOverTest = new MenuFinal(screen);
        gameOverTest.atualizarNivelPontos(score);
        Mockito.verify(score, Mockito.times(1)).getPontos();
        Mockito.verify(score    , Mockito.times(1)).getNivel();
    }
}
