package zombie.radio.globals;

import zombie.radio.globals.RadioGlobalString.1;

public final class RadioGlobalString extends RadioGlobal<String> {
   public RadioGlobalString(String var1) {
      super(var1, RadioGlobalType.String);
   }

   public RadioGlobalString(String var1, String var2) {
      super(var1, var2, RadioGlobalType.String);
   }

   public String getValue() {
      return (String)this.value;
   }

   public void setValue(String var1) {
      this.value = var1;
   }

   public String getString() {
      return (String)this.value;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public CompareResult compare(RadioGlobal var1, CompareMethod var2) {
      if (var1 instanceof RadioGlobalString var3) {
         switch (1.$SwitchMap$zombie$radio$globals$CompareMethod[var2.ordinal()]) {
            case 1:
               return ((String)this.value).equals(var3.getValue()) ? CompareResult.True : CompareResult.False;
            case 2:
               return !((String)this.value).equals(var3.getValue()) ? CompareResult.True : CompareResult.False;
            default:
               return CompareResult.Invalid;
         }
      } else {
         return CompareResult.Invalid;
      }
   }

   public boolean setValue(RadioGlobal var1, EditGlobalOps var2) {
      if (var2.equals(EditGlobalOps.set) && var1 instanceof RadioGlobalString) {
         this.value = ((RadioGlobalString)var1).getValue();
         return true;
      } else {
         return false;
      }
   }
}
