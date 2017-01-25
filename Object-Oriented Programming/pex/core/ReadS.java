package pex.core;

import pex.AppIO;

public class ReadS extends CompositeExpression {

    AppIO _app;

    public ReadS(AppIO app) {
        _app = app;
    }

    public String getAsText() {
        return "(reads)";
    }

    public Literal evaluate() {
        return new StringLiteral(_app.readString());
    }

    public String getName(){
        return "reads";
    }

    public void accept(Visitor visitor){
        return;
    }

    public void visitArguments(Visitor visitor){
        return;
    }
}
