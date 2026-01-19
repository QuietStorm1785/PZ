package zombie.radio.script;

import java.util.ArrayList;
import java.util.List;
import zombie.radio.globals.CompareMethod;
import zombie.radio.globals.CompareResult;
import zombie.radio.globals.RadioGlobal;
import zombie.radio.script.ConditionContainer.Condition;

public final class ConditionContainer implements ConditionIter {
   private List<ConditionIter> conditions = new ArrayList<>();
   private OperatorType operatorType = OperatorType.NONE;

   public ConditionContainer() {
      this(OperatorType.NONE);
   }

   public ConditionContainer(OperatorType var1) {
      this.operatorType = var1;
   }

   public CompareResult Evaluate() {
      boolean var2 = false;

      for (int var3 = 0; var3 < this.conditions.size(); var3++) {
         ConditionIter var4 = this.conditions.get(var3);
         CompareResult var1 = var4 != null ? var4.Evaluate() : CompareResult.Invalid;
         if (var1.equals(CompareResult.Invalid)) {
            return var1;
         }

         OperatorType var5 = var4.getNextOperator();
         if (var3 == this.conditions.size() - 1) {
            return !var5.equals(OperatorType.NONE) ? CompareResult.Invalid : (!var2 ? var1 : CompareResult.False);
         }

         if (var5.equals(OperatorType.OR)) {
            if (!var2 && var1.equals(CompareResult.True)) {
               return var1;
            }

            var2 = false;
         } else if (var5.equals(OperatorType.AND)) {
            var2 = var2 || var1.equals(CompareResult.False);
         } else if (var5.equals(OperatorType.NONE)) {
            return CompareResult.Invalid;
         }
      }

      return CompareResult.Invalid;
   }

   public OperatorType getNextOperator() {
      return this.operatorType;
   }

   public void setNextOperator(OperatorType var1) {
      this.operatorType = var1;
   }

   public void Add(ConditionContainer var1) {
      this.conditions.add(var1);
   }

   public void Add(RadioGlobal var1, RadioGlobal var2, CompareMethod var3, OperatorType var4) {
      Condition var5 = new Condition(var1, var2, var3, var4);
      this.conditions.add(var5);
   }
}
