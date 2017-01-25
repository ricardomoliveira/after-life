package pex.app.main;

import java.io.*;

import pex.app.App;
import pex.parser.NewParser;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;

/**
 * Save to file under current name (if unnamed, query for name).
 */
public class Save extends Command<App> {
    /**
     * @param receiver
     */
    public Save(App receiver) {
        super(Label.SAVE, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation {

        String fileName = entity().getInterpreter().getFileName();

        if (fileName.equals("null")) {
            Form f = new Form(title());
            InputString nome = new InputString(f, Message.newSaveAs());
            f.parse();

            entity().getInterpreter().setFileName(nome.value());
            fileName = nome.value();
        }

        try {
            ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileName));

            oos.writeObject(entity().getInterpreter());
            oos.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
