package pex.app.main;

import pex.core.*;

import pex.app.App;
import pex.app.evaluator.*;
import pex.app.main.Message;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.Menu;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;

/**
 * Open menu for managing programs.
 */
public class EditProgram extends Command<App> {

    /**
     * @param receiver
     */
    public EditProgram(App receiver) {
        super(Label.MANAGE_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {

        Form f = new Form(title());
        InputString nome = new InputString(f, Message.requestProgramId());
        f.parse();

        Display d = new Display(title());
        Interpreter inter = entity().getInterpreter();

        if (inter.getProgram(nome.value()) == null) {
            d.add(Message.noSuchProgram(nome.value()));
            d.display();
        }
        else {
            Program _program = entity().getInterpreter().getProgram(nome.value());

            EvaluatorMenu EditMenu = new EvaluatorMenu(_program);
            EditMenu.open();
        }
    }
}
