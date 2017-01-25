package pex.core;
import pex.AppIO;

import java.lang.StringBuilder;
import java.util.List;
import java.util.ArrayList;

public class Print extends VariadicExpression {

    private StringBuilder _res;
    private AppIO _app;

    public Print(List<Expression> args, AppIO app) {
        super(args);
        _app = app;
    }

    public Literal evaluate() {
        _res = new StringBuilder();
        Literal res = new IntegerLiteral(0);
        for (Expression e : getArguments()) {
            res = new StringLiteral(e.evaluate().getValue());
            _res.append(res.getValue());
        }
        _app.println(_res.toString());
        return res;
    }

    public String getName() { return "print"; }

    protected void visitArguments(Visitor visitor){
        for (Expression args : getArguments()){
            args.accept(visitor);
        }
    }

    public void accept(Visitor visitor) {
        visitor.visitPrint(this);
        visitArguments(visitor);
    }


}
