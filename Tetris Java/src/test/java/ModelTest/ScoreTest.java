package ModelTest;

import tetris.Model.Score;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class ScoreTest {

    Score testScore;

    @BeforeEach
    public void setUp(){
        testScore = new Score();
    }

    @Test
    public void getSetTest(){
        testScore.setPontos(100);
        Assertions.assertEquals(testScore.getPontos(), 100);
    }

    @Test
    public void linhasProcessadasTest(){
        testScore.linhasProcessadas(1);
        Assertions.assertEquals(testScore.getPontos(), 40);
    }

    @Test
    public void processoNivelandgetTempoTest1(){
        testScore.linhasProcessadas(29);
        testScore.processoNivel();
        Assertions.assertEquals(testScore.getNivel(), 3);
        Assertions.assertEquals(testScore.getTempo(), 1600/3);
    }

    @Test
    public void processoNivelandgetTempoTest2() {
        testScore.linhasProcessadas(100);
        testScore.processoNivel();
        Assertions.assertEquals(testScore.getNivel(), 8);
        Assertions.assertEquals(testScore.getTempo(), 1600/8);
    }
}
