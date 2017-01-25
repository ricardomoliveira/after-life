package pex.core;

public class Eq extends BinaryExpression {

    public Eq(Expression e1, Expression e2) {
	     super(e1, e2);
    }

    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument1().evaluate()).intValue();
        int e2 = ((IntegerLiteral)getArgument2().evaluate()).intValue();

        if (e1 == e2) {
            Literal res = new IntegerLiteral(1);
            return res;
        }
        else {
            Literal res = new IntegerLiteral(0);
            return res;
        }
    }

    public String getName() { return "eq"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitEq(this);
        visitArguments(visitor);
    }

}
