package tetris.Model.Pecas;

import java.util.List;
import java.util.Vector;

public class Peca4 extends Peca {
    public Peca4(){
        this.setAltura(2);
        this.setCor("#FFFF00");
        this.setFormas(this.criarFormas());
    }

    @Override
    List<List<String>> criarFormas() {
        formas = new Vector<>();
        List <String> form = new Vector<>();
        form.add(".....");
        form.add(".00..");
        form.add(".00..");
        form.add(".....");
        form.add(".....");
        formas.add(form);
        return formas;
    }
}
