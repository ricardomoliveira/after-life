package pex.app.main;

import java.io.*;

import pex.core.*;

import pex.app.App;
import pex.parser.NewParser;

import java.util.List;
import java.util.ArrayList;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;

/**
 * Read existing program.
 */
public class ReadProgram extends Command<App> {
    /**
     * @param receiver
     */
    public ReadProgram(App receiver) {
        super(Label.READ_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {

        Form f = new Form(title());
        InputString nome = new InputString(f, Message.programFileName());
        f.parse();

        NewParser par = new NewParser();
        String fileName = nome.value();

        try {
            Program program = par.parseFile(fileName, fileName, entity().getInterpreter());
            entity().getInterpreter().addProgram(program);
        }
        catch (Exception e) {
            e.printStackTrace();
            Display d = new Display();
            d.add(Message.fileNotFound(fileName));
            d.display();
        }

    }
}
