package zombie.radio.script;

import zombie.radio.globals.CompareMethod;
import zombie.radio.globals.CompareResult;
import zombie.radio.globals.RadioGlobal;

final class ConditionContainer$Condition implements ConditionIter {
   private OperatorType operatorType = OperatorType.NONE;
   private CompareMethod compareMethod;
   private RadioGlobal valueA;
   private RadioGlobal valueB;

   public ConditionContainer$Condition(RadioGlobal var1, RadioGlobal var2, CompareMethod var3) {
      this(var1, var2, var3, OperatorType.NONE);
   }

   public ConditionContainer$Condition(RadioGlobal var1, RadioGlobal var2, CompareMethod var3, OperatorType var4) {
      this.valueA = var1;
      this.valueB = var2;
      this.operatorType = var4;
      this.compareMethod = var3;
   }

   public CompareResult Evaluate() {
      return this.valueA != null && this.valueB != null ? this.valueA.compare(this.valueB, this.compareMethod) : CompareResult.Invalid;
   }

   public OperatorType getNextOperator() {
      return this.operatorType;
   }

   public void setNextOperator(OperatorType var1) {
      this.operatorType = var1;
   }
}
