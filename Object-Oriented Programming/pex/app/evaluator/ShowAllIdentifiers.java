package pex.app.evaluator;

//FIXME import core classes
import pex.core.Program;
import pex.core.Expression;
import pex.core.Visitor;
import pex.core.ConcretizeVisitor;
import pex.AppIO;

import java.util.Iterator;
import java.util.TreeSet;
import java.util.List;
import pt.utl.ist.po.ui.Display;

/**
 * Show all program identifiers.
 */
public class ShowAllIdentifiers extends ProgramCommand {

    /**
     * @param receiver
     */
    public ShowAllIdentifiers(Program receiver) {
        super(Label.SHOW_ALL_IDENTIFIERS, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {

        AppIO app = entity().getInterpreter().getAppIO();
        Visitor v = new ConcretizeVisitor();
        List<Expression> program = entity().getExpressions();

        for (Expression exp : program) {
            exp.accept(v);
        }

        TreeSet keys = v.getIdKeys();

        // Get an iterator
        Iterator i = keys.iterator();

        // Display elements
        while(i.hasNext()) {
            Object str = i.next();
            app.println((String)str);
        }
    }
}
