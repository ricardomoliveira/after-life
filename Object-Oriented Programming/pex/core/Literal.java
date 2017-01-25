package pex.core;

public abstract class Literal extends Expression {

    public Literal evaluate() {
        return this;
    }

    public abstract String getAsText();

    public abstract String getValue();

}
