package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.core.skinnedmodel.ModelManager;
import zombie.core.skinnedmodel.animation.AnimationPlayer;
import zombie.core.skinnedmodel.animation.AnimationTrack;
import zombie.core.skinnedmodel.model.VehicleSubModelInstance;
import zombie.scripting.objects.ModelScript;
import zombie.scripting.objects.VehicleScript.Model;
import zombie.util.Pool;

public final class BaseVehicle$ModelInfo {
   public VehiclePart part;
   public Model scriptModel;
   public ModelScript modelScript;
   public int wheelIndex;
   public final Matrix4f renderTransform = new Matrix4f();
   public VehicleSubModelInstance modelInstance;
   public AnimationPlayer m_animPlayer;
   public AnimationTrack m_track;

   public AnimationPlayer getAnimationPlayer() {
      if (this.part != null && this.part.getParent() != null) {
         BaseVehicle$ModelInfo var1 = this.part.getVehicle().getModelInfoForPart(this.part.getParent());
         if (var1 != null) {
            return var1.getAnimationPlayer();
         }
      }

      String var3 = this.scriptModel.file;
      zombie.core.skinnedmodel.model.Model var2 = ModelManager.instance.getLoadedModel(var3);
      if (var2 != null && !var2.bStatic) {
         if (this.m_animPlayer != null && this.m_animPlayer.getModel() != var2) {
            this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
         }

         if (this.m_animPlayer == null) {
            this.m_animPlayer = AnimationPlayer.alloc(var2);
         }

         return this.m_animPlayer;
      } else {
         return null;
      }
   }

   public void releaseAnimationPlayer() {
      this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
   }
}
