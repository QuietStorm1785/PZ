package zombie.iso.objects;

import zombie.characters.IsoZombie;

class IsoDeadBody$1 extends ThreadLocal<IsoZombie> {
   public IsoZombie initialValue() {
      return new IsoZombie(null);
   }
}
