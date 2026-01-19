package zombie.scripting.objects;

import org.joml.Vector3f;

public final class VehicleScript$Anim {
   public String id;
   public String anim;
   public float rate = 1.0F;
   public boolean bAnimate = true;
   public boolean bLoop = false;
   public boolean bReverse = false;
   public final Vector3f offset = new Vector3f();
   public final Vector3f angle = new Vector3f();
   public String sound;

   VehicleScript$Anim makeCopy() {
      VehicleScript$Anim var1 = new VehicleScript$Anim();
      var1.id = this.id;
      var1.anim = this.anim;
      var1.rate = this.rate;
      var1.bAnimate = this.bAnimate;
      var1.bLoop = this.bLoop;
      var1.bReverse = this.bReverse;
      var1.offset.set(this.offset);
      var1.angle.set(this.angle);
      var1.sound = this.sound;
      return var1;
   }
}
