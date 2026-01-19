package zombie.debug.options;

import zombie.debug.BooleanDebugOption;
import zombie.debug.options.Character.DebugOG;

public class Character extends OptionGroup {
   public final BooleanDebugOption CreateAllOutfits = newOption(this.Group, "Create.AllOutfits", false);
   public final DebugOG Debug = new DebugOG(this.Group);

   public Character() {
      super("Character");
   }
}
