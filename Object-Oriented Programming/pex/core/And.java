package pex.core;

public class And extends BinaryExpression {

    public And(Expression e1, Expression e2) {
	     super(e1, e2);
    }
    public Literal evaluate() {
        int e1 = ((IntegerLiteral)getArgument1().evaluate()).intValue();

        if (e1 != 0) {
            int e2 = ((IntegerLiteral)getArgument2().evaluate()).intValue();
            if (e2 != 0) {
                Literal res = new IntegerLiteral(1);
                return res;
            }
        }

        Literal res = new IntegerLiteral(0);
        return res;
    }

    public String getName() { return "and"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitAnd(this);
        visitArguments(visitor);
    }


}
