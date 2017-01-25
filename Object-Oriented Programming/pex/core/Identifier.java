package pex.core;

public class Identifier extends Expression {
    private String _name;
    private Program _program;

    public Identifier(String name, Program prog) {
        _name = name;
        _program = prog;
    }

    public String getAsText() {
        return _name;
    }

    public Literal evaluate() {
        if (_program.getInterpreter().getIdentifiers().containsKey(getName()))
            return _program.getInterpreter().getIdentifierValue(this);
        else
            return new IntegerLiteral(0);
    }

    public String getName() {
        return _name;
    }

    public void visitArguments(Visitor visitor){
    }

    public void accept(Visitor visitor){
        visitor.visitIdentifier(this);
    }

}
