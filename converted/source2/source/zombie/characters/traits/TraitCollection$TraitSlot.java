package zombie.characters.traits;

import zombie.util.StringUtils;

public class TraitCollection$TraitSlot {
   public final String Name;
   private boolean m_isSet;

   private TraitCollection$TraitSlot(TraitCollection var1, String var2) {
      this.this$0 = var1;
      this.Name = var2;
      this.m_isSet = false;
   }

   public boolean isName(String var1) {
      return StringUtils.equalsIgnoreCase(this.Name, var1);
   }

   public boolean isSet() {
      return this.m_isSet;
   }

   public void set(boolean var1) {
      if (this.m_isSet != var1) {
         this.this$0.set(this.Name, var1);
      }
   }

   @Override
   public String toString() {
      return "TraitSlot(" + this.Name + ":" + this.m_isSet + ")";
   }
}
