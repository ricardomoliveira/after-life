package pex.app;

import java.io.*;

import pex.core.Program;
import pex.core.Interpreter;

import java.io.Serializable;

import java.util.List;
import java.util.ArrayList;

import pex.AppIO;
import pex.parser.ParserException;
import pex.parser.NewParser;

import pex.app.main.MainMenu;
import pex.app.main.Message;

import pt.utl.ist.po.ui.Command;
import pt.utl.ist.po.ui.InputString;
import pt.utl.ist.po.ui.InputInteger;
import pt.utl.ist.po.ui.Menu;
import pt.utl.ist.po.ui.Display;
import pt.utl.ist.po.ui.Form;

/**
 * This is a sample client for the expression evaluator.
 * It uses a text-based user interface.
 */
public class App implements AppIO, Serializable {
    private Interpreter _inter;

    public App() {
    	_inter = new Interpreter(this);
    }

    public Interpreter getInterpreter() {
        return _inter;
    }

    public void setInterpreter(Interpreter interpreter) {
        _inter = interpreter;
    }

    /**
     * Writes a string to be presented to the user.
     *
     * @param str the string to write
     **/
    public void println(String str) {
        Display d = new Display();
        d.addNewLine(str);
        d.display();
    }

    /**
     * Reads a string inputed by the user.
     *
     * @return the string written by the user.
     **/
    public String readString() {
        Form f = new Form();
        InputString nome = new InputString(f, "");
        f.parse();
        return nome.value();
    }

    /**
     * Reads an integer inputed by the user.
     *
     * @return the number written by the user.
     **/
    public int readInteger() {
        Form f = new Form();
        InputInteger num = new InputInteger(f, "");
        f.parse();
        return num.value();
    }


    /**
     * @param args
     */
    public static void main(String[] args) {
        App app = new App();
        NewParser parser = new NewParser();

        String datafile = System.getProperty("import"); //$NON-NLS-1$

        if (datafile != null) {
            try {
                Program program = parser.parseFile(datafile, "import", app.getInterpreter());
                app.getInterpreter().addProgram(program);
            } catch (ParserException e) {
                e.printStackTrace();
            }
        }

        MainMenu menu = new MainMenu(app);
        menu.open();
    }
}
