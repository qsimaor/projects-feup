package tetris.Model.Pecas;

import java.util.List;
import java.util.Vector;

public class Peca3 extends Peca {
    public Peca3(){
        this.setAltura(3);
        this.setCor("#FF7F00");
        this.setFormas(this.criarFormas());
    }

    @Override
    List<List<String>> criarFormas() {
        formas = new Vector<>();
        List <String> form = new Vector<>();
        form.add(".....");
        form.add("...0.");
        form.add(".000.");
        form.add(".....");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add("..0..");
        form.add("..0..");
        form.add("..00.");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add(".....");
        form.add(".000.");
        form.add(".0...");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add(".00..");
        form.add("..0..");
        form.add("..0..");
        form.add(".....");
        formas.add(form);
        return formas;
    }
}
