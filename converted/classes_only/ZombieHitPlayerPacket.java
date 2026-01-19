package zombie.network.packets.hit;

import java.nio.ByteBuffer;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.network.PacketValidator;
import zombie.network.packets.INetworkPacket;
import zombie.network.packets.hit.HitCharacterPacket.HitType;

public class ZombieHitPlayerPacket extends HitCharacterPacket implements INetworkPacket {
   protected final Zombie wielder = new Zombie();
   protected final Player target = new Player();
   protected final Bite bite = new Bite();

   public ZombieHitPlayerPacket() {
      super(HitType.ZombieHitPlayer);
   }

   public void set(IsoZombie var1, IsoPlayer var2) {
      this.wielder.set(var1, false);
      this.target.set(var2, false);
      this.bite.set(var1);
   }

   public void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(var2);
      this.bite.parse(var1, var2);
   }

   public void write(ByteBufferWriter var1) {
      super.write(var1);
      this.wielder.write(var1);
      this.target.write(var1);
      this.bite.write(var1);
   }

   public boolean isRelevant(UdpConnection var1) {
      return this.target.isRelevant(var1);
   }

   public boolean isConsistent() {
      return super.isConsistent() && this.target.isConsistent() && this.wielder.isConsistent();
   }

   public String getDescription() {
      return super.getDescription()
         + "\n\tWielder "
         + this.wielder.getDescription()
         + "\n\tTarget "
         + this.target.getDescription()
         + "\n\tBite "
         + this.bite.getDescription();
   }

   protected void preProcess() {
      this.wielder.process();
      this.target.process();
   }

   protected void process() {
      this.bite.process((IsoZombie)this.wielder.getCharacter(), this.target.getCharacter());
   }

   protected void postProcess() {
      this.wielder.process();
      this.target.process();
   }

   protected void attack() {
   }

   protected void react() {
      this.wielder.react();
      this.target.react();
   }

   public boolean validate(UdpConnection var1) {
      if (!PacketValidator.checkShortDistance(var1, this.wielder, this.target, ZombieHitPlayerPacket.class.getSimpleName())) {
         return false;
      } else {
         return !PacketValidator.checkOwner(var1, this.wielder, ZombieHitPlayerPacket.class.getSimpleName())
            ? false
            : PacketValidator.checkTarget(var1, this.target, ZombieHitPlayerPacket.class.getSimpleName());
      }
   }
}
