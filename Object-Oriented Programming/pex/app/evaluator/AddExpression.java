package pex.app.evaluator;

import pex.app.BadPositionException;
import pex.app.BadExpressionException;

import pex.core.*;
import pex.parser.*;

import java.util.List;
import java.util.ArrayList;

import pt.utl.ist.po.ui.Form;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InputInteger;

/**
 * Add expression.
 */
public class AddExpression extends ProgramCommand {
    /**
     * @param receiver
     */
    public AddExpression(Program receiver) {
        super(Label.ADD_EXPRESSION, receiver);
    }

    /** @see pt.utl.ist.po.ui.Command#execute() */
    @Override
    public final void execute() throws BadExpressionException, BadPositionException {

        Form f = new Form(title());
        InputInteger index = new InputInteger(f, Message.requestPosition());
        InputString expression = new InputString(f, Message.requestExpression());
        f.parse();
        NewParser par = new NewParser();

        try {
            Expression e = par.parseString(expression.value(), entity());

            if (entity().getExpressions().size() > index.value()) {
                entity().addExpression(index.value(), e);
            }
            else if (entity().getExpressions().size() == index.value()){
                entity().addExpression(e);
            }
            else {
                throw new BadPositionException(index.value());
            }
        }
        catch(ParserException bee) {
            throw new BadExpressionException(expression.value());
        }

    }
}
