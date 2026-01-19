package zombie.radio.globals;

import zombie.radio.globals.RadioGlobalFloat.1;

public final class RadioGlobalFloat extends RadioGlobal<Float> {
   public RadioGlobalFloat(float var1) {
      super(var1, RadioGlobalType.Float);
   }

   public RadioGlobalFloat(String var1, float var2) {
      super(var1, var2, RadioGlobalType.Float);
   }

   public float getValue() {
      return (Float)this.value;
   }

   public void setValue(float var1) {
      this.value = var1;
   }

   public String getString() {
      return ((Float)this.value).toString();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public CompareResult compare(RadioGlobal var1, CompareMethod var2) {
      if (var1 instanceof RadioGlobalFloat var3) {
         switch (1.$SwitchMap$zombie$radio$globals$CompareMethod[var2.ordinal()]) {
            case 1:
               return (Float)this.value == var3.getValue() ? CompareResult.True : CompareResult.False;
            case 2:
               return (Float)this.value != var3.getValue() ? CompareResult.True : CompareResult.False;
            case 3:
               return (Float)this.value < var3.getValue() ? CompareResult.True : CompareResult.False;
            case 4:
               return (Float)this.value > var3.getValue() ? CompareResult.True : CompareResult.False;
            case 5:
               return (Float)this.value <= var3.getValue() ? CompareResult.True : CompareResult.False;
            case 6:
               return (Float)this.value >= var3.getValue() ? CompareResult.True : CompareResult.False;
            default:
               return CompareResult.Invalid;
         }
      } else {
         return CompareResult.Invalid;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public boolean setValue(RadioGlobal var1, EditGlobalOps var2) {
      if (var1 instanceof RadioGlobalFloat var3) {
         switch (1.$SwitchMap$zombie$radio$globals$EditGlobalOps[var2.ordinal()]) {
            case 1:
               this.value = var3.getValue();
               return true;
            case 2:
               this.value = (Float)this.value + var3.getValue();
               return true;
            case 3:
               this.value = (Float)this.value - var3.getValue();
               return true;
         }
      }

      return false;
   }
}
