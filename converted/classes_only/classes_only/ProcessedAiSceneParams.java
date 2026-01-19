package zombie.core.skinnedmodel.model.jassimp;

import jassimp.AiScene;
import org.lwjgl.util.vector.Quaternion;
import zombie.core.skinnedmodel.model.SkinningData;
import zombie.core.skinnedmodel.model.jassimp.JAssImpImporter.LoadMode;

public class ProcessedAiSceneParams {
   public AiScene scene = null;
   public LoadMode mode = LoadMode.Normal;
   public SkinningData skinnedTo = null;
   public String meshName = null;
   public float animBonesScaleModifier = 1.0F;
   public Quaternion animBonesRotateModifier = null;

   ProcessedAiSceneParams() {
   }

   public static ProcessedAiSceneParams create() {
      return new ProcessedAiSceneParams();
   }

   protected void set(ProcessedAiSceneParams var1) {
      this.scene = var1.scene;
      this.mode = var1.mode;
      this.skinnedTo = var1.skinnedTo;
      this.meshName = var1.meshName;
      this.animBonesScaleModifier = var1.animBonesScaleModifier;
      this.animBonesRotateModifier = var1.animBonesRotateModifier;
   }
}
