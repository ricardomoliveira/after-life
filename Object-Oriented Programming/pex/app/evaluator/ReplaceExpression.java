package pex.app.evaluator;

import pex.parser.*;
import pex.core.*;

import pex.app.evaluator.*;
import pex.app.main.*;

import pex.app.BadExpressionException;
import pex.app.BadPositionException;

import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InputInteger;

/**
 * Replace expression in program.
 */
public class ReplaceExpression extends ProgramCommand {

    /**
     * @param receiver
     */
    public ReplaceExpression(Program receiver) {
        super(Label.REPLACE_EXPRESSION, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws BadExpressionException, BadPositionException {

        Form f = new Form(title());
        InputInteger index = new InputInteger(f, Message.requestPosition());
        InputString expression = new InputString(f, Message.requestExpression());
        f.parse();

        NewParser par = new NewParser();

        if ((entity().getExpressions().size() <= index.value()) || (0 > index.value())) {
            throw new BadPositionException(index.value());
        }

        try {
            Expression e = par.parseString(expression.value(), entity());
            entity().replaceExpression(index.value(), e);
        }
        catch (ParserException bee) {
            throw new BadExpressionException(expression.value());
        }
    }
}
