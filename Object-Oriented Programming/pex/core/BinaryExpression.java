package pex.core;

public abstract class BinaryExpression extends CompositeExpression {
    private Expression _e1;
    private Expression _e2;

    public BinaryExpression(Expression e1, Expression e2) {
	      _e1 = e1;
	      _e2 = e2;
    }

    public Expression getArgument1(){
      return _e1;
    }

    public Expression getArgument2(){
      return _e2;
    }

    public String getAsText() { return "(" + getName() + " " + _e1.getAsText() + " " + _e2.getAsText() + ")"; }

    public abstract void accept(Visitor visitor);

}
