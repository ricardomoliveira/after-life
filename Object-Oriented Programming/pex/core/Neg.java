package pex.core;

public class Neg extends UnaryExpression {

    public Neg(Expression e1) {
	     super(e1);
    }

    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument().evaluate()).intValue();
        int tmp = e1 * -1;
        Literal res = new IntegerLiteral(tmp);
        return res;
    }

    public String getName() { return "neg"; }

    protected void visitArguments(Visitor visitor){
        getArgument().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitNeg(this);
        visitArguments(visitor);
    }

}
