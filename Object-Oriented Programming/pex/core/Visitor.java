package pex.core;

import java.util.TreeSet;

public interface Visitor {

    void visitAdd(Add add);
    void visitAnd(And and);
    void visitCall(Call call);
    void visitDiv(Div div);
    void visitEq(Eq eq);
    void visitGe(Ge ge);
    void visitGt(Gt gt);
    void visitIdentifier(Identifier identifier);
    void visitIf(If condIf);
    void visitLe(Le le);
    void visitLt(Lt lt);
    void visitMod(Mod mod);
    void visitMul(Mul mul);
    void visitNe(Ne ne);
    void visitNeg(Neg neg);
    void visitNot(Not not);
    void visitOr(Or or);
    void visitPrint(Print print);
    void visitReadI(ReadI readi);
    void visitReadS(ReadS reads);
    void visitSub(Sub sub);
    void visitSeq(Seq seq);
    void visitSet(Set set);
    void visitWhile(While condWhile);
    TreeSet<String> getIdKeys();

}
