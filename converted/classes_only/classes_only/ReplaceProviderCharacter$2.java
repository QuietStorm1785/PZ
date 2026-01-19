package zombie.text.templating;

import zombie.characters.IsoGameCharacter;

class ReplaceProviderCharacter$2 implements IReplace {
   ReplaceProviderCharacter$2(ReplaceProviderCharacter var1, IsoGameCharacter var2) {
      this.this$0 = var1;
      this.val$character = var2;
   }

   public String getString() {
      return this.val$character != null && this.val$character.getDescriptor() != null && this.val$character.getDescriptor().getSurname() != null
         ? this.val$character.getDescriptor().getSurname()
         : "Smith";
   }
}
