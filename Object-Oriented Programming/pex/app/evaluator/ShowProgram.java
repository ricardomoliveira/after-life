package pex.app.evaluator;

import pex.core.*;

import pex.app.App;
import pex.app.evaluator.EvaluatorMenu;

import pt.utl.ist.po.ui.Display;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * Show program (present code).
 */
public class ShowProgram extends ProgramCommand {

    /**
     * @param receiver
     */
    public ShowProgram(Program receiver) {
        super(Label.SHOW_PROGRAM, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {

        Display d = new Display(title());

        if (!entity().getExpressions().isEmpty()) {
            d.add(entity().getAsText());
            d.display();
        }

    }
}
