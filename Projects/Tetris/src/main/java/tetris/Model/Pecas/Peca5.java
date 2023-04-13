package tetris.Model.Pecas;

import java.util.List;
import java.util.Vector;

public class Peca5 extends Peca {
    public Peca5(){
        this.setAltura(3);
        this.setCor("#00FF00");
        this.setFormas(this.criarFormas());
    }

    @Override
    List<List<String>> criarFormas() {
        formas = new Vector<>();
        List <String> form = new Vector<>();
        form.add(".....");
        form.add("..00.");
        form.add(".00..");
        form.add(".....");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add("..0..");
        form.add("..00.");
        form.add("...0.");
        form.add(".....");
        formas.add(form);
        return formas;
    }
}
