package pex.core;

public abstract class UnaryExpression extends CompositeExpression {
    private Expression _e1;

    public UnaryExpression(Expression e1) {
	      _e1 = e1;
    }

    public Expression getArgument(){
        return _e1;
    }

    public String getAsText() {
        return "(" + getName() + " " + _e1.getAsText() + ")"; }

    public abstract void accept(Visitor visitor);

}
