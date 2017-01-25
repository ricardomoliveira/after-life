package pex.core;

public class Not extends UnaryExpression {

    public Not(Expression e1) {
	     super(e1);
    }

    public Literal evaluate() {

        if (((IntegerLiteral)getArgument().evaluate()).intValue() != 0) {
            Literal res = new IntegerLiteral(0);
            return res;
        }
        else {
            Literal res = new IntegerLiteral(1);
            return res;
        }

    }
    public String getName() { return "not"; }

    protected void visitArguments(Visitor visitor){
        getArgument().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitNot(this);
        visitArguments(visitor);
    }

}
