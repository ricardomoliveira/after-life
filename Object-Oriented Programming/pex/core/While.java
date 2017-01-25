package pex.core;

public class While extends BinaryExpression {

    public While(Expression e1, Expression e2) {
	     super(e1, e2);
    }
    public Literal evaluate() {
        while (((IntegerLiteral)(getArgument1().evaluate())).intValue() != 0) {
            getArgument2().evaluate();
        }
        return new IntegerLiteral(0);
    }
    public String getName() { return "while"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitWhile(this);
        visitArguments(visitor);
    }


}
