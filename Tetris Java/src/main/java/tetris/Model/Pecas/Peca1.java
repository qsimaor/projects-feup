package tetris.Model.Pecas;

import tetris.Model.Grid;

import java.util.List;
import java.util.Vector;

public class Peca1 extends Peca {
    public Peca1(){
        this.setAltura(4);
        this.setCor("#00FFFF");
        this.setFormas(this.criarFormas());
    }

    @Override
    List<List<String>> criarFormas() {
        formas = new Vector<>();
        List <String> form = new Vector<>();
        form.add("..0..");
        form.add("..0..");
        form.add("..0..");
        form.add("..0..");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add("0000.");
        form.add(".....");
        form.add(".....");
        form.add(".....");
        formas.add(form);
        return formas;
    }

    @Override
    public void verificar(Grid playGrid) {
        int testes = 0;
        while (testes<this.altura){
            if(verificarDireita(playGrid)) return;
            if(verificarEsquerda(playGrid)) return;
            if(verificarDireita2(playGrid)) return;
            if (testes == 0)
                if(verificarBaixo(playGrid)) return;
            this.y-=1;
            if (playGrid.valido(this)) return;
            testes+=1;
        }
        this.y += testes;
        this.reRotacao();
    }

    public boolean verificarDireita2(Grid playGrid){
        this.x += 2;
        if (playGrid.valido(this)){
            return true;
        }
        else
            this.x -= 2;
        return false;
    }
}
