// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.radio.script;

import zombie.radio.globals.CompareResult;

public interface ConditionIter {
    CompareResult Evaluate();

    OperatorType getNextOperator();

    void setNextOperator(OperatorType var1);
}
