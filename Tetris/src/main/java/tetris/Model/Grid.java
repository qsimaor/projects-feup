package tetris.Model;

import tetris.Model.Pecas.Peca;

import java.util.List;
import java.util.Vector;

public class Grid {
    private List<List<String>> matriz;
    private int comprimento;
    private int altura;
    private int x;
    private int y;
    private int tamanhoBloco;
    public final static String defaultGridColor = "#505050";

    public Grid(int comprimento, int altura, int x, int y, int tamanhoBloco){
        this.altura = altura;
        this.comprimento = comprimento;
        this.tamanhoBloco = tamanhoBloco;
        this.x = x;
        this.y = y;
        this.matriz = criarMatriz(comprimento, altura);
    }

    public List<List<String>> criarMatriz(int comprimento, int altura){
        matriz = new Vector<>();
        for (int i = 0; i < altura; i++){
            List <String> linhas = new Vector<>();
            for(int j = 0; j < comprimento; j++){
                linhas.add(defaultGridColor);
            }
            matriz.add(linhas);
        }
        return matriz;
    }

    public Grid(Peca piece, int x, int y, int tamanhoBloco){
        this.altura = 5;
        this.comprimento = 5;
        this.tamanhoBloco = tamanhoBloco;
        this.x = x;
        this.y = y;
        this.matriz=criarMatrizPiece(piece,comprimento,comprimento);
    }

    public List<List<String>> criarMatrizPiece(Peca piece, int comprimento, int altura){
        matriz = new Vector<>();
        for (int i = 0; i < altura; i++){
            List <String> linhas = new Vector<>();
            for(int j = 0; j < comprimento; j++){
                if (piece.getForma().get(i).charAt(j) == '.')
                    linhas.add(defaultGridColor);
                else
                    linhas.add(piece.getCor());
            }
            matriz.add(linhas);
        }
        return matriz;
    }

    public int getAltura() {return altura;}
    public int getComprimento() {return comprimento;}
    public int getX() {return x;}
    public int getY() {return y;}
    public int getTamanhoBloco() {return tamanhoBloco;}
    public List<List<String>> getMatriz() {return matriz;}

    public boolean setMatriz(List<List<String>> newMatriz){
        if(newMatriz.size() == altura && newMatriz.get(0).size() == comprimento){
            matriz = newMatriz;
            return true;
        }
        return false;
    }

    public boolean valido(Peca piece) {
        for (int j = 0; j<5; j++){
            for (int i = 0; i<5; i++) {
                if (piece.getForma().get(i).charAt(j) == '0' &&  !(piece.getY() + i - 2 < 0)) {
                    if ((piece.getX() + j - 3)<0 || (piece.getX() + j - 3) >= comprimento)
                        return false;
                    if ((piece.getY() + i - 2) >= altura)
                        return false;
                    if (!matriz.get(piece.getY() + i - 2).get(piece.getX() + j - 3).equals(defaultGridColor))
                        return false;
                }
                if (piece.getForma().get(i).charAt(j) == '0' &&  piece.getY() + i - 2 < 0)
                    if ((piece.getX() + j - 3)<0 || (piece.getX() + j - 3) >= 10)
                        return false;
            }
        }
        return true;
    }

    public void adicionarPeca(Peca piece){
        for (int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if (piece.getForma().get(i).charAt(j) == '0')
                    this.matriz.get(piece.getY() + i - 2).set(piece.getX() + j - 3, piece.getCor());
            }
        }
    }

    public int removerLinhas(){
        int removerLinhas = 0;
        boolean buraco;
        int i = 0;
        while (i < altura){
            buraco = verificarLinhas(i);
            if (!buraco){
                removerLinha(i);
                removerLinhas ++;
            }
            i++;
        }
        return removerLinhas;
    }

    public boolean verificarLinhas(int i){
        boolean buraco= false;
        for(String color : matriz.get(i))
            if(color.equals(defaultGridColor)){
                buraco = true;
                break;
            }
        return buraco;
    }

    public void removerLinha(int i){
        matriz.remove(i);
        List <String> linhas = new Vector<>();
        for (int j = 0; j < comprimento; j++){
            linhas.add(defaultGridColor);
        }
        matriz.add(0, linhas);
    }
}

