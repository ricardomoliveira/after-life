package pex.core;

import pex.AppIO;

import java.util.TreeMap;
import java.io.Serializable;
import java.util.Map;
import java.util.HashMap;

/**
* O interpretador permite interpretar (representar o texto como objectos) e avaliar expressoes (calcular os seus valores).
* Possui tambem varias formas de preservar o seu estado.
*
* @author Grupo 23 | 84759 & 84761 |
* @version 1.0
*/
public class Interpreter implements Serializable {

    private AppIO _app;
    private Map<String, Program> _interpreter;
    private Map<String, Literal> _identificadores;
    private String _fileName;

    public Interpreter(AppIO app) {
        _interpreter = new HashMap<String, Program>();
        _identificadores = new TreeMap<String, Literal>();
        _fileName = "null";
        _app = app;
    }

    public void addIdentifier(Identifier id, Literal value) {
        _identificadores.put(id.getName(), value);
    }

    public void setFileName(String file) {
        _fileName = file;
    }

    public String getFileName() {
        return _fileName;
    }

    public Map <String, Literal> getIdentifiers() {
        return _identificadores;
    }

    public Literal getIdentifierValue(Identifier id) {
        return _identificadores.get(id.getName());
    }

    public void addProgram(Program programa) {
        _interpreter.put(programa.getName(), programa);
    }

    public Map<String, Program> getPrograms() {
        return _interpreter;
    }

    public Program getProgram(String nome) {
        return _interpreter.get(nome);
    }

    public AppIO getAppIO () {
        return _app;
    }
}
