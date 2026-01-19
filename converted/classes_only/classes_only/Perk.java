package zombie.network.packets.hit;

import java.nio.ByteBuffer;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.network.packets.INetworkPacket;

public class Perk implements INetworkPacket {
   protected zombie.characters.skills.PerkFactory.Perk perk;
   protected byte perkIndex;

   public void set(zombie.characters.skills.PerkFactory.Perk var1) {
      this.perk = var1;
      if (this.perk == null) {
         this.perkIndex = -1;
      } else {
         this.perkIndex = (byte)this.perk.index();
      }
   }

   public void parse(ByteBuffer var1, UdpConnection var2) {
      this.perkIndex = var1.get();
      if (this.perkIndex >= 0 && this.perkIndex <= Perks.getMaxIndex()) {
         this.perk = Perks.fromIndex(this.perkIndex);
      }
   }

   public void write(ByteBufferWriter var1) {
      var1.putByte(this.perkIndex);
   }

   public String getDescription() {
      return "\n\t" + this.getClass().getSimpleName() + " [ perk=( " + this.perkIndex + " )" + (this.perk == null ? "null" : this.perk.name) + " ]";
   }

   public boolean isConsistent() {
      return this.perk != null;
   }

   public zombie.characters.skills.PerkFactory.Perk getPerk() {
      return this.perk;
   }
}
