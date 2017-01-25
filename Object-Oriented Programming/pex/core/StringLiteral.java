package pex.core;

public class StringLiteral extends Literal {

    private String _value;

    public StringLiteral(String value) {
        _value = value;
    }

    public String getAsText() {
        return  "\"" + _value + "\"";
    }

    public String getValue() {
        return _value;
    }

    public void accept(Visitor visitor){
        return;
    }

    public void visitArguments(Visitor visitor){
        return;
    }
}
