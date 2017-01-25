package pex.core;

public class Set extends BinaryExpression {

    private Program _program;
    Visitor v = new ConcretizeVisitor2();

    public Set(Expression e1, Expression e2, Program program) {
        super(e1, e2);
        _program = program;
    }

    public Literal evaluate() {
        Identifier id = new Identifier(getArgument1().getAsText(), _program);
        Literal e2 = getArgument2().evaluate();

        _program.getInterpreter().addIdentifier(id, e2);

        return e2;
    }

    public String getName() { return "set"; }

    protected void visitArguments(Visitor visitor){
        getArgument1().accept(visitor);
        getArgument2().accept(visitor);
    }

    public void accept(Visitor visitor) {
        visitor.visitSet(this);
        visitArguments(visitor);
    }


}
