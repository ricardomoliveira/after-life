package pex.core;

public class IntegerLiteral extends Literal {

    private int _value;

    public IntegerLiteral(int value) {
        _value = value;
    }

    public String getAsText() {
        return String.valueOf(_value);
    }

    public String getValue() {
        return String.valueOf(_value);
    }

    public int intValue() {
        return _value;
    }

    public void accept(Visitor visitor){
        return;
    }

    public void visitArguments(Visitor visitor){
        return;
    }

}
