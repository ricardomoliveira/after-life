package pex.core;

public class Mul extends BinaryExpression {

    public Mul(Expression e1, Expression e2) {
	     super(e1, e2);
    }

    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument1().evaluate()).intValue();
        int e2 = ((IntegerLiteral)getArgument2().evaluate()).intValue();


        Literal res = new IntegerLiteral(e1 * e2);

        return res;
    }

    public String getName() { return "mul"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitMul(this);
        visitArguments(visitor);
    }


}
