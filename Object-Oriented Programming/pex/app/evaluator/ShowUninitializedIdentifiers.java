package pex.app.evaluator;

//FIXME import core classes
import pex.core.Program;
import pex.core.Expression;
import pex.core.Visitor;
import pex.core.ConcretizeVisitor2;
import pex.core.Literal;
import pex.AppIO;

//import java.util.Set;
import java.util.Iterator;
import java.util.TreeSet;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import pt.utl.ist.po.ui.Display;

/**
 * Show uninitialized identifiers.
 */
public class ShowUninitializedIdentifiers extends ProgramCommand {

    /**
     * @param receiver
     */
    public ShowUninitializedIdentifiers(Program receiver) {
        super(Label.SHOW_UNINITIALIZED_IDENTIFIERS, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() {
        AppIO app = entity().getInterpreter().getAppIO();

        Map<String, Literal> map = entity().getInterpreter().getIdentifiers();
        List<Expression> program = entity().getExpressions();
        Visitor v = new ConcretizeVisitor2();

        for (Expression exp : program){
            exp.accept(v);
        }

        TreeSet keys = v.getIdKeys();

        // Get an iterator
        Iterator i = keys.iterator();

        // Display elements
        while(i.hasNext()) {
            Object str = i.next();
            if (!map.containsKey(str.toString())){
                app.println((String)str);
            }
        }
    }

}
