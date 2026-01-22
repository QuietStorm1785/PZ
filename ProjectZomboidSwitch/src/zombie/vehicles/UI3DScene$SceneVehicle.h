#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"
#include "zombie/vehicles/UI3DScene/SetModelCamera.h"
#include "zombie/vehicles/UI3DScene/VehicleRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    std::string m_scriptName = "Base.ModernCar";
    VehicleScript m_script;
    Model m_model;

   UI3DScene$SceneVehicle(UI3DScene var1, std::string var2) {
      super(var1, var2);
      this.setScriptName("Base.ModernCar");
   }

    SceneObjectRenderData renderMain() {
      if (this.m_script == nullptr) {
         this.m_model = nullptr;
    return nullptr;
      } else {
    std::string var1 = this.m_script.getModel().file;
         this.m_model = ModelManager.instance.getLoadedModel(var1);
         if (this.m_model == nullptr) {
    return nullptr;
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

    void setScriptName(const std::string& var1) {
      this.m_scriptName = var1;
      this.m_script = ScriptManager.instance.getVehicle(var1);
   }
}
} // namespace vehicles
} // namespace zombie
