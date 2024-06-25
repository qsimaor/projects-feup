package ControllerTest;

import tetris.Controller.Jogo;
import tetris.Model.Pecas.*;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.TerminalScreen;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentMatchers;
import org.mockito.Mockito;

import java.io.IOException;

public class JogoTest {

    Jogo jogo = new Jogo();
    Peca1 Peca1 = new Peca1();
    Peca2 Peca2 = new Peca2();
    Peca3 Peca3 = new Peca3();
    Peca4 Peca4 = new Peca4();
    Peca5 Peca5 = new Peca5();
    Peca6 Peca6 = new Peca6();
    Peca7 Peca7 = new Peca7();

    @Test
    public void JogoTest()  {
        try {
            TerminalScreen screen = (TerminalScreen) Mockito.mock(TerminalScreen.class);
            TextGraphics graphics = (TextGraphics) Mockito.mock(TextGraphics.class);
            Mockito.when(screen.newTextGraphics()).thenReturn(graphics);
            Mockito.when(graphics.putString(ArgumentMatchers.anyInt(), ArgumentMatchers.anyInt(), ArgumentMatchers.anyString())).thenReturn(graphics);
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    @Test
    public void getPecaAleatoriaTest() {
        boolean random = true;
        if (jogo.getPecaAleatoria() == Peca1 || jogo.getPecaAleatoria() == Peca2 || jogo.getPecaAleatoria() == Peca3 || jogo.getPecaAleatoria() == Peca4 || jogo.getPecaAleatoria() == Peca5 || jogo.getPecaAleatoria() == Peca6 || jogo.getPecaAleatoria() == Peca7) {
            random = false;
        }
        Assertions.assertTrue(random);
        Assertions.assertNotNull(this.jogo.getPecaAleatoria());
    }

    @Test
    public void getKeyTest() {
        Assertions.assertNull(jogo.getKey());
    }
}