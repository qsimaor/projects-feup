package tetris.Model.Pecas;

import java.util.List;
import java.util.Vector;

public class Peca2 extends Peca {
    public Peca2(){
        this.setAltura(3);
        this.setCor("#0000FF");
        this.setFormas(this.criarFormas());
    }

    @Override
    List<List<String>> criarFormas() {
        formas = new Vector<>();
        List <String> form = new Vector<>();
        form.add(".....");
        form.add(".0...");
        form.add(".000.");
        form.add(".....");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add("..00.");
        form.add("..0..");
        form.add("..0..");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add(".....");
        form.add(".000.");
        form.add("...0.");
        form.add(".....");
        formas.add(form);
        form = new Vector<>();
        form.add(".....");
        form.add("..0..");
        form.add("..0..");
        form.add(".00..");
        form.add(".....");
        formas.add(form);
        return formas;
    }
}