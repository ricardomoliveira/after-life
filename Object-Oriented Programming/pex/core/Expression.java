package pex.core;

import java.io.Serializable;

/**
* Uma expressao e uma representacao algebrica de uma quantidade.
* Todas as expressoes podem ser avaliadas para obtencao de um valor.
*
* @author Grupo 23 | 84759 & 84761 |
* @version 1.0
*/
public abstract class Expression implements Serializable {

    public abstract String getAsText();
    public abstract Literal evaluate();
    public abstract void accept(Visitor visitor);
    protected abstract void visitArguments(Visitor visitor);

}
