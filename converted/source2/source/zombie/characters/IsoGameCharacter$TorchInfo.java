package zombie.characters;

import org.joml.Vector3f;
import zombie.inventory.InventoryItem;
import zombie.iso.Vector2;
import zombie.popman.ObjectPool;
import zombie.scripting.objects.VehicleScript;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehicleLight;
import zombie.vehicles.VehiclePart;

public class IsoGameCharacter$TorchInfo {
   private static final ObjectPool<IsoGameCharacter$TorchInfo> TorchInfoPool = new ObjectPool(IsoGameCharacter$TorchInfo::new);
   private static final Vector3f tempVector3f = new Vector3f();
   public int id;
   public float x;
   public float y;
   public float z;
   public float angleX;
   public float angleY;
   public float dist;
   public float strength;
   public boolean bCone;
   public float dot;
   public int focusing;

   public static IsoGameCharacter$TorchInfo alloc() {
      return (IsoGameCharacter$TorchInfo)TorchInfoPool.alloc();
   }

   public static void release(IsoGameCharacter$TorchInfo var0) {
      TorchInfoPool.release(var0);
   }

   public IsoGameCharacter$TorchInfo set(IsoPlayer var1, InventoryItem var2) {
      this.x = var1.getX();
      this.y = var1.getY();
      this.z = var1.getZ();
      Vector2 var3 = var1.getLookVector(IsoGameCharacter.tempVector2);
      this.angleX = var3.x;
      this.angleY = var3.y;
      this.dist = var2.getLightDistance();
      this.strength = var2.getLightStrength();
      this.bCone = var2.isTorchCone();
      this.dot = var2.getTorchDot();
      this.focusing = 0;
      return this;
   }

   public IsoGameCharacter$TorchInfo set(VehiclePart var1) {
      BaseVehicle var2 = var1.getVehicle();
      VehicleLight var3 = var1.getLight();
      VehicleScript var4 = var2.getScript();
      Vector3f var5 = tempVector3f;
      var5.set(var3.offset.x * var4.getExtents().x / 2.0F, 0.0F, var3.offset.y * var4.getExtents().z / 2.0F);
      var2.getWorldPos(var5, var5);
      this.x = var5.x;
      this.y = var5.y;
      this.z = var5.z;
      var5 = var2.getForwardVector(var5);
      this.angleX = var5.x;
      this.angleY = var5.z;
      this.dist = var1.getLightDistance();
      this.strength = var1.getLightIntensity();
      this.bCone = true;
      this.dot = var3.dot;
      this.focusing = (int)var1.getLightFocusing();
      return this;
   }
}
