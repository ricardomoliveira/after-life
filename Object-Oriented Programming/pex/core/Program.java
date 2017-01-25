package pex.core;

import pex.core.*;

import java.util.List;
import java.util.ArrayList;

import java.io.Serializable;

/**
* Um programa é formado por um conjunto de expressões, tem um nome e pode ser executado.
* A execução de um programa corresponde a avaliar todas as suas expressoes sequencialmente.
*
* @author Grupo 23 | 84759 & 84761 |
* @version 1.0
*/
public class Program implements Serializable {

    /**
    * Nome do Programa
    */
    private String _name;

    /**
	* Contém a lista de expressões que constituem o programa.
	*/
    private List<Expression> _program;

    /**
     * Interpretador guardado
     */
    private Interpreter _interpreter;

    /**
	 * Construtor: Atribui o nome e cria a lista.
     *
     * @param programName nome do programa
	 */
    public Program(String programName, Interpreter interpreter) {
        _program = new ArrayList<Expression>();
        _name = programName;
        _interpreter = interpreter;
    }

    /**
     * Retorna o programa cujo nome foi indicado.
     *
     * @param name nome do programa
     * @return Programa com o nome indicado.
     */
    public Program getProgram(String name) {
        if (this.getName().equals(name)) {
            return this;
        }
        return null;
    }

    /**
     * Retorna o interpretador associado
     *
     * @return Interpretador
     */
    public Interpreter getInterpreter() {
        return _interpreter;
    }

    /**
	 * Devolve o valor de um identificador.
	 *
	 * @param id identificador
	 * @return Valor do identificador
	 */
    public Literal getIdentifierValue(Identifier id) {
        return id.evaluate();
    }

    /**
	 * Devolve o nome de um programa.
     * Útil para verificar a existência de programas.
	 *
	 * @return Nome
	 */
    public String getName() {
        return _name;
    }

    /**
	 * Define a lista de expressões de um certo programa.
	 * É a parte fulcral de um programa.
     *
	 * @param expressions Conjunto de expressões
	 */
    public void set(List<Expression> expressions){
        _program = expressions;
    }

    /**
	 * Devolve o conjunto de expressões de um programa.
	 * Útil para verificar a existência de certas expressões,
	 * a quantidade de expressões que tem ou mesmo se está vazio.
     *
	 * @return Conjunto de expressões do programa
	 */
    public List<Expression> getExpressions() {
        return _program;
    }


    /**
	 * Adiciona uma expressão à lista de expressões do programa.
	 * Nomeadamente, no final da lista.
     *
	 * @param e1 expressão a adicionar
	 */
    public void addExpression(Expression e1) {
        _program.add(e1);
    }

    /**
	 * Adicionar uma expressão à lista de expressões do programa.
	 * Coloca a expressão numa posição especifica.
     *
	 * @param index posicão da lista
	 * @param e1 expressão a adicionar
	 * @return Description text
	 */
    public void addExpression(int index, Expression e1) {
        _program.add(index, e1);
    }

    /**
	 * Substitui uma expressão de uma certa posição da lista.
	 *
     * @param index posicão da lista da expressao a substituir
	 * @param e1 expressão a adicionar
	 */
    public void replaceExpression(int index, Expression e1) {
        _program.set(index, e1);
    }

    /**
     * Limpa o conteudo do programa, reiniciando
     */
    public void resetLista() {
        _program.clear();
    }

    /**
	 * Executa o programa.
	 * Corresponde a avaliar todas as suas expressoes sequencialmente.
	 *
	 * @return Valor do programa
	 */
    public Literal execute() {
        Literal res = new IntegerLiteral(0);
        for (Expression e: getExpressions()) {
            res = e.evaluate();
        }
        return res;
    }

    /**
     * Acede ao interpretador associado, procura o programa com o nome dado e retorna
     *
     * @param String programName Nome do programa
     *
     * @return Programa
     */
    public Program getAtualProgram(String programName) {
        return _interpreter.getProgram(programName);
    }

    /**
	 * Obtém o programa como texto.
	 *
	 * @return Versão em texto do programa
	 */
    public String getAsText() {
        String s = "";

        for (Expression e : getExpressions()) {
            s += e.getAsText() + "\n";
        }

        return s;
    }
}
