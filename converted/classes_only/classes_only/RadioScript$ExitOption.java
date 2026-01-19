package zombie.radio.scripting;

public final class RadioScript$ExitOption {
   private String scriptname = "";
   private int chance = 0;
   private int startDelay = 0;

   public RadioScript$ExitOption(String var1, int var2, int var3) {
      this.scriptname = var1;
      this.chance = var2;
      this.startDelay = var3;
   }

   public String getScriptname() {
      return this.scriptname;
   }

   public int getChance() {
      return this.chance;
   }

   public int getStartDelay() {
      return this.startDelay;
   }
}
