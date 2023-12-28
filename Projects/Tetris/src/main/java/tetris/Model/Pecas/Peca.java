package tetris.Model.Pecas;

import tetris.Model.Grid;

import java.util.List;

public abstract class Peca {
    protected List<List<String>> formas;
    protected int rotacao = 0;
    protected int x = 6;
    protected int y = -1;
    protected String cor;
    protected int altura;

    abstract List<List<String>> criarFormas();

    public int getX() {return x;}
    public int getY() {return y;}
    public int getAltura() {return altura;}
    public String getCor() {return cor;}
    public int getRotacao() {return rotacao;}
    public List<String> getForma() {return formas.get(rotacao);}

    public void setX(int x) {this.x = x;}
    public void setY(int y) {this.y = y;}
    public void setAltura(int altura) {this.altura = altura;}
    public void setCor(String cor) {this.cor = cor;}
    public void setRotacao(int rotacao) {this.rotacao = rotacao;}
    public void setFormas(List<List<String>> formas) {this.formas = formas;}

    public void rotacao(Grid playGrid){
        rotacao++;
        if(rotacao >= formas.size())
            rotacao = 0;
        if(playGrid.valido(this))
            return;
        verificar(playGrid);
    }
    public void reRotacao(){
        rotacao--;
        if(rotacao < 0)
            rotacao = formas.size()-1;
    };

    public void verificar(Grid playGrid) {
        int testes = 0;
        while (testes < this.altura){
            if(verificarDireita(playGrid)) return;
            if(verificarEsquerda(playGrid)) return;
            if (testes == 0)
                if(verificarBaixo(playGrid)) return;
            this.y -= 1 ;
            if (playGrid.valido(this)) return;
            testes += 1;
        }
        this.y += testes;
        this.reRotacao();
    }

    public boolean verificarDireita(Grid playGrid){
        this.x += 1;
        if (playGrid.valido(this)) {
            return true;
        }
        else
            this.x -= 1;
        return false;
    }

    public boolean verificarEsquerda(Grid playGrid){
        this.x -= 1;
        if (playGrid.valido(this)) {return true;}
        else this.x += 1;
        return false;
    }

    public boolean verificarBaixo(Grid playGrid){
        this.y += 1;
        if (playGrid.valido(this)) return true;
        if (verificarDireita(playGrid)) return true;
        if (verificarEsquerda(playGrid)) return true;
        this.y -= 1;
        return false;
    }

    public void moverDown() {y++;}
    public void moverUp() {y--;}
    public void moverRight(Grid playGrid){
        x++;
        if(!playGrid.valido(this))
            x--;
    }
    public void moverLeft(Grid playGrid){
        x--;
        if(!playGrid.valido(this))
            x++;
    }
}
