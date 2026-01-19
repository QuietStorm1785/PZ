package zombie.radio.globals;

public abstract class RadioGlobal<T> {
   protected String name;
   protected T value;
   protected RadioGlobalType type = RadioGlobalType.Invalid;

   protected RadioGlobal(T var1, RadioGlobalType var2) {
      this(null, (T)var1, var2);
   }

   protected RadioGlobal(String var1, T var2, RadioGlobalType var3) {
      this.name = var1;
      this.value = (T)var2;
      this.type = var3;
   }

   public final RadioGlobalType getType() {
      return this.type;
   }

   public final String getName() {
      return this.name;
   }

   public abstract String getString();

   public abstract CompareResult compare(RadioGlobal var1, CompareMethod var2);

   public abstract boolean setValue(RadioGlobal var1, EditGlobalOps var2);
}
