package pex.core;

public abstract class TrenaryExpression extends CompositeExpression {
    private Expression _e1;
    private Expression _e2;
    private Expression _e3;

    public TrenaryExpression(Expression e1, Expression e2, Expression e3) {
        _e1 = e1;
	      _e2 = e2;
        _e3 = e3;
    }

    public Expression getArgument1(){
        return _e1;
    }

    public Expression getArgument2(){
        return _e2;
    }

    public Expression getArgument3(){
        return _e3;
    }

    public String getAsText() {
        return "(" + getName() + " " + _e1.getAsText() + " " + _e2.getAsText() + " " + _e3.getAsText() + ")"; }

    public abstract void accept(Visitor visitor);


}
