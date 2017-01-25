package pex.core;

import java.util.TreeSet;
import java.io.Serializable;


public class ConcretizeVisitor implements Visitor, Serializable {

    private TreeSet<String> _idKey;

    public ConcretizeVisitor() {
        _idKey = new TreeSet<String>();
    }

    public void visitIdentifier(Identifier identifier) {
        _idKey.add(identifier.getName());
    }

    public TreeSet<String> getIdKeys() {
        return _idKey;
    }

    public void visitAdd(Add add) {
    }

    public void visitAnd(And and) {
    }

    public void visitCall(Call call) {
    }

    public void visitDiv(Div div) {
    }

    public void visitEq(Eq eq) {
    }

    public void visitGe(Ge ge) {
    }

    public void visitGt(Gt gt) {
    }

    public void visitIf(If condIf) {
    }

    public void visitLe(Le le) {
    }

    public void visitLt(Lt lt) {
    }

    public void visitMod(Mod mod) {
    }

    public void visitMul(Mul mul) {
    }

    public void visitNe(Ne ne) {
    }

    public void visitNeg(Neg neg) {
    }

    public void visitNot(Not not) {
    }

    public void visitOr(Or or) {
    }

    public void visitPrint(Print print) {
    }

    public void visitReadI(ReadI readi) {
    }

    public void visitReadS(ReadS reads) {
    }

    public void visitSub(Sub sub) {
    }

    public void visitSeq(Seq seq) {
    }

    public void visitSet(Set set) {
    }

    public void visitWhile(While condWhile) {
    }
}
