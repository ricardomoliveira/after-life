package pex.core;

public class Add extends BinaryExpression {

    public Add(Expression e1, Expression e2) {
	       super(e1, e2);
    }

    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument1().evaluate()).intValue();
        int e2 = ((IntegerLiteral)getArgument2().evaluate()).intValue();

        Literal res = new IntegerLiteral(e1 + e2);

        return res;
    }

    public String getName() { return "add"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitAdd(this);
        visitArguments(visitor);
    }

}
