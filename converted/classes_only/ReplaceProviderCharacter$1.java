package zombie.text.templating;

import zombie.characters.IsoGameCharacter;

class ReplaceProviderCharacter$1 implements IReplace {
   ReplaceProviderCharacter$1(ReplaceProviderCharacter var1, IsoGameCharacter var2) {
      this.this$0 = var1;
      this.val$character = var2;
   }

   public String getString() {
      return this.val$character != null && this.val$character.getDescriptor() != null && this.val$character.getDescriptor().getForename() != null
         ? this.val$character.getDescriptor().getForename()
         : "Bob";
   }
}
