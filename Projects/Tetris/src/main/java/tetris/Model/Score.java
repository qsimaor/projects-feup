package tetris.Model;

public class Score {
    int pontos;
    int nivel;
    int linhasApagadas;
    boolean combo;

    public Score(){
        nivel = 1;
        pontos = 0;
        linhasApagadas = 0;
        combo = false;
    }

    public int getPontos() {return pontos;}
    public int getNivel() {return nivel;}
    public void setPontos(int pontos) {this.pontos = pontos;}

    public void linhasProcessadas(int n){
        if (n == 0) {
            combo = false;
            return;
        }

        float multiplicador = nivel;

        if (combo) multiplicador *= 1.5;
        else combo = true;

        switch (n){
            case 1-> pontos += 40 * multiplicador;
            case 2-> pontos += 100 * multiplicador;
            case 3-> pontos += 300 * multiplicador;
            case 4-> pontos += 1200 * multiplicador;
        }
        linhasApagadas += n;
    }

    public void processoNivel(){
        if (linhasApagadas <= 50) nivel = linhasApagadas / 10 + 1;
        else if (linhasApagadas <= 70) nivel = 7;
        else if (linhasApagadas <= 100) nivel = 8;
        else if (linhasApagadas <= 140) nivel = 9;
        else if (linhasApagadas <= 190) nivel = 10;
        else nivel = 11 + (linhasApagadas-190)/50;
    }

    public long getTempo(){
        return (1600 / nivel);
    }
}
