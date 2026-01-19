package zombie.network.packets;

import zombie.characters.IsoPlayer;
import zombie.network.packets.PlayerVariables.NetworkPlayerVariableIDs;

class PlayerVariables$NetworkPlayerVariable {
   NetworkPlayerVariableIDs id;
   float value;

   private PlayerVariables$NetworkPlayerVariable(PlayerVariables var1) {
      this.this$0 = var1;
   }

   public void set(IsoPlayer var1, NetworkPlayerVariableIDs var2) {
      this.id = var2;
      this.value = var1.getVariableFloat(var2.name(), 0.0F);
   }
}
