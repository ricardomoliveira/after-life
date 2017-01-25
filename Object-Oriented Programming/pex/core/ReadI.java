package pex.core;

import pex.AppIO;

public class ReadI extends CompositeExpression{

    AppIO _app;

    public ReadI(AppIO app) {
        _app = app;
    }

    public String getAsText() {
        return "(readi)";
    }

    public Literal evaluate() {
        int num = _app.readInteger();
        return new IntegerLiteral(num);
    }

    public String getName(){
        return "readi";
    }

    public void accept(Visitor visitor){
        return;
    }

    public void visitArguments(Visitor visitor){
        return;
    }
}
