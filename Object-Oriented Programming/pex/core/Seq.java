package pex.core;

import java.util.List;
import java.util.ArrayList;

public class Seq extends VariadicExpression {

    public Seq(List<Expression> args) {
        super(args);
    }

    public Literal evaluate() {
        Literal res = new IntegerLiteral(0);
        for (Expression e : getArguments()) {
            res = e.evaluate();
        }
        return res;
    }

    public String getName() { return "seq"; }

    protected void visitArguments(Visitor visitor){
        for (Expression args : getArguments()){
            args.accept(visitor);
        }
    }

    public void accept(Visitor visitor) {
        visitor.visitSeq(this);
        visitArguments(visitor);
    }


}
