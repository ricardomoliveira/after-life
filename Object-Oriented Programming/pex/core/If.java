package pex.core;

public class If extends TrenaryExpression {

    public If(Expression e1, Expression e2, Expression e3) {
	     super(e1, e2, e3);
    }

    public Literal evaluate() {
        if (((IntegerLiteral)(getArgument1().evaluate())).intValue() != 0) {
            return getArgument2().evaluate();
        }
        else {
            return getArgument3().evaluate();
        }
    }
    public String getName() { return "if"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
        getArgument3().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitIf(this);
        visitArguments(visitor);
    }

}
