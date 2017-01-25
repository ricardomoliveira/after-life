package pex.app.main;

import java.io.*;
import pex.core.*;

import pex.app.App;
import pex.app.main.Message;
import pex.parser.NewParser;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;

/**
 * Open existing interpreter.
 */
public class Open extends Command<App> {
    /**
     * @param receiver
     */
    public Open(App receiver) {
        super(Label.OPEN, receiver);
    }

    /** @see pt.tecnico.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation {
        Form f = new Form(title());
        InputString nome = new InputString(f, Message.openFile());
        f.parse();

        entity().getInterpreter().setFileName(nome.value());

        String fileName = nome.value();

        try {
            ObjectInputStream in = new ObjectInputStream(new FileInputStream(fileName));
            Interpreter inter = (Interpreter)in.readObject();

            in.close();

            entity().setInterpreter(inter);
        }
        catch (FileNotFoundException e) {
            Display d = new Display();
            d.addNewLine(Message.fileNotFound());
            d.display();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
