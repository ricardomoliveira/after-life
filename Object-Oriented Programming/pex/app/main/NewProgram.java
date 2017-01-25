package pex.app.main;

import pex.core.*;
import pex.app.*;

import java.util.List;
import java.util.ArrayList;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;

/**
 * Create new program.
 */
public class NewProgram extends Command<App> {

    /**
     * @param receiver
     */
    public NewProgram(App receiver) {
        super(Label.NEW_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {

        Form f = new Form(title());
        InputString nome = new InputString(f, Message.requestProgramId());
        f.parse();

        if (entity().getInterpreter().getProgram(nome.value()) != null) {
            entity().getInterpreter().getProgram(nome.value()).resetLista();
        }
        else {
            Program _program = new Program(nome.value(), entity().getInterpreter());
            entity().getInterpreter().addProgram(_program);
        }
    }
}
