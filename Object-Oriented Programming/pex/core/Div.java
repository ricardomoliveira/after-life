package pex.core;

public class Div extends BinaryExpression {

    public Div(Expression e1, Expression e2) {
	     super(e1, e2);
    }

    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument1().evaluate()).intValue();
        int e2 = ((IntegerLiteral)getArgument2().evaluate()).intValue();

        return new IntegerLiteral(e1 / e2);
    }

    public String getName() { return "div"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitDiv(this);
        visitArguments(visitor);
    }

}
