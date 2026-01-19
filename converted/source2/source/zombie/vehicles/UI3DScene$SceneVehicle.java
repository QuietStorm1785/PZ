package zombie.vehicles;

import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.ModelManager;
import zombie.core.skinnedmodel.model.Model;
import zombie.core.textures.Texture;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.VehicleScript;
import zombie.vehicles.UI3DScene.SceneObject;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;
import zombie.vehicles.UI3DScene.SetModelCamera;
import zombie.vehicles.UI3DScene.VehicleRenderData;

final class UI3DScene$SceneVehicle extends SceneObject {
   String m_scriptName = "Base.ModernCar";
   VehicleScript m_script;
   Model m_model;

   UI3DScene$SceneVehicle(UI3DScene var1, String var2) {
      super(var1, var2);
      this.setScriptName("Base.ModernCar");
   }

   SceneObjectRenderData renderMain() {
      if (this.m_script == null) {
         this.m_model = null;
         return null;
      } else {
         String var1 = this.m_script.getModel().file;
         this.m_model = ModelManager.instance.getLoadedModel(var1);
         if (this.m_model == null) {
            return null;
         } else {
            if (this.m_script.getSkinCount() > 0) {
               this.m_model.tex = Texture.getSharedTexture("media/textures/" + this.m_script.getSkin(0).texture + ".png");
            }

            VehicleRenderData var2 = (VehicleRenderData)VehicleRenderData.s_pool.alloc();
            var2.initVehicle(this);
            SetModelCamera var3 = (SetModelCamera)UI3DScene.s_SetModelCameraPool.alloc();
            SpriteRenderer.instance.drawGeneric(var3.init(this.m_scene.m_VehicleSceneModelCamera, var2));
            SpriteRenderer.instance.drawGeneric(var2.m_drawer);
            return var2;
         }
      }
   }

   void setScriptName(String var1) {
      this.m_scriptName = var1;
      this.m_script = ScriptManager.instance.getVehicle(var1);
   }
}
