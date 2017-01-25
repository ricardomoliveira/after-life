package pex.app.main;

import java.io.*;

import pex.core.*;

import pex.app.App;
import pex.app.main.Message;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InvalidOperation;

/**
 * Write (save) program to file.
 */
public class WriteProgram extends Command<App> {
    /**
     * @param receiver
     */
    public WriteProgram(App receiver) {
        super(Label.WRITE_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws InvalidOperation {

        Form f = new Form(title());
        InputString pid = new InputString(f, Message.requestProgramId());
        InputString nome = new InputString(f, Message.programFileName());
        f.parse();

        String fileName = nome.value();

        if (entity().getInterpreter().getProgram(pid.value()) == null) {
            Display d = new Display();
            d.addNewLine(Message.noSuchProgram(pid.value()));
            d.display();
        }
        else {
            try {
                PrintWriter p = new PrintWriter(new BufferedWriter(new FileWriter(fileName)));
                p.println(entity().getInterpreter().getProgram(pid.value()).getAsText());
                p.close();
            }

            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
