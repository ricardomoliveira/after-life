package pex.core;

import pex.parser.BadSourceException;

public class Call extends UnaryExpression {
    Program _program;

    public Call(Expression e1, Program program) {
	     super(e1);
         _program = program;
    }

    public Literal evaluate() {
        String fileName = ((StringLiteral)getArgument()).getValue();
        return _program.getAtualProgram(fileName).execute();
    }

    public String getName() { return "call"; }

    protected void visitArguments(Visitor visitor){
        getArgument().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitCall(this);
        visitArguments(visitor);
    }

}
