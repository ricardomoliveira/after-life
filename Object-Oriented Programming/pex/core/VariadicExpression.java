package pex.core;

import java.util.List;
import java.util.ArrayList;

public abstract class VariadicExpression extends CompositeExpression {

    private List<Expression> _expression;

    public VariadicExpression(List<Expression> args) {
        _expression = args;
    }

    public List<Expression> getArguments() {
      return _expression;
    }

    public String getAsText() {
      String list = "(" + getName() + " ";
        for (Expression e: _expression) {
            list += e.getAsText() + " ";
        }
      list += ")";
      return list;
    }

    public abstract void accept(Visitor visitor);



}
