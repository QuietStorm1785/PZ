#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"
#include "zombie/vehicles/UI3DScene/SceneVehicle.h"
#include "zombie/vehicles/UI3DScene/VehicleDrawer.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
   const std::vector<Model> m_models = std::make_unique<std::vector<>>();
   const std::vector<Matrix4f> m_transforms = std::make_unique<std::vector<>>();
    const VehicleDrawer m_drawer = std::make_shared<VehicleDrawer>();
   private static const ObjectPool<UI3DScene$VehicleRenderData> s_pool = std::make_shared<ObjectPool>(UI3DScene$VehicleRenderData::new);

   private UI3DScene$VehicleRenderData() {
   }

    SceneObjectRenderData initVehicle(SceneVehicle var1) {
      super.init(var1);
      this.m_models.clear();
    Matrix4fObjectPool var2 = (Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get();
      var2.release(this.m_transforms);
      this.m_transforms.clear();
    VehicleScript var3 = var1.m_script;
      if (var3.getModel() == nullptr) {
    return nullptr;
      } else {
         this.initVehicleModel(var1);
    float var4 = var3.getModelScale();
    Vector3f var5 = var3.getModel().getOffset();
    Matrix4f var6 = UI3DScene.allocMatrix4f();
         var6.translationRotateScale(var5.x * 1.0F, var5.y, var5.z, 0.0F, 0.0F, 0.0F, 1.0F, var4);
         this.m_transform.mul(var6, var6);

         for (int var7 = 0; var7 < var3.getPartCount(); var7++) {
    Part var8 = var3.getPart(var7);
            if (var8.wheel != nullptr) {
               this.initWheelModel(var1, var8, var6);
            }
         }

         UI3DScene.releaseMatrix4f(var6);
         this.m_drawer.init(var1, this);
    return this;
      }
   }

    void initVehicleModel(SceneVehicle var1) {
    VehicleScript var2 = var1.m_script;
    float var3 = var2.getModelScale();
    float var4 = 1.0F;
    ModelScript var5 = ScriptManager.instance.getModelScript(var2.getModel().file);
      if (var5 != nullptr && var5.scale != 1.0F) {
         var4 = var5.scale;
      }

    float var6 = 1.0F;
      if (var5 != nullptr) {
         var6 = var5.invertX ? -1.0F : 1.0F;
      }

      var6 *= -1.0F;
    Quaternionf var7 = UI3DScene.allocQuaternionf();
    Matrix4f var8 = UI3DScene.allocMatrix4f();
    Vector3f var9 = var2.getModel().getRotate();
      var7.rotationXYZ(var9.x * (float) (Math.PI / 180.0), var9.y * (float) (Math.PI / 180.0), var9.z * (float) (Math.PI / 180.0));
    Vector3f var10 = var2.getModel().getOffset();
      var8.translationRotateScale(var10.x * 1.0F, var10.y, var10.z, var7.x, var7.y, var7.z, var7.w, var3 * var4 * var6, var3 * var4, var3 * var4);
      if (var1.m_model.Mesh != nullptr && var1.m_model.Mesh.isReady() && var1.m_model.Mesh.m_transform != nullptr) {
         var1.m_model.Mesh.m_transform.transpose();
         var8.mul(var1.m_model.Mesh.m_transform);
         var1.m_model.Mesh.m_transform.transpose();
      }

      this.m_transform.mul(var8, var8);
      UI3DScene.releaseQuaternionf(var7);
      this.m_models.push_back(var1.m_model);
      this.m_transforms.push_back(var8);
   }

    void initWheelModel(SceneVehicle var1, Part var2, Matrix4f var3) {
    VehicleScript var4 = var1.m_script;
    float var5 = var4.getModelScale();
    Wheel var6 = var4.getWheelById(var2.wheel);
      if (var6 != nullptr && !var2.models.empty()) {
         zombie.scripting.objects.VehicleScript.Model var7 = (zombie.scripting.objects.VehicleScript.Model)var2.models.get(0);
    Vector3f var8 = var7.getOffset();
    Vector3f var9 = var7.getRotate();
    Model var10 = ModelManager.instance.getLoadedModel(var7.file);
         if (var10 != nullptr) {
    float var11 = var7.scale;
    float var12 = 1.0F;
    float var13 = 1.0F;
    ModelScript var14 = ScriptManager.instance.getModelScript(var7.file);
            if (var14 != nullptr) {
               var12 = var14.scale;
               var13 = var14.invertX ? -1.0F : 1.0F;
            }

    Quaternionf var15 = UI3DScene.allocQuaternionf();
            var15.rotationXYZ(var9.x * (float) (Math.PI / 180.0), var9.y * (float) (Math.PI / 180.0), var9.z * (float) (Math.PI / 180.0));
    Matrix4f var16 = UI3DScene.allocMatrix4f();
            var16.translation(var6.offset.x / var5 * 1.0F, var6.offset.y / var5, var6.offset.z / var5);
    Matrix4f var17 = UI3DScene.allocMatrix4f();
            var17.translationRotateScale(var8.x * 1.0F, var8.y, var8.z, var15.x, var15.y, var15.z, var15.w, var11 * var12 * var13, var11 * var12, var11 * var12);
            var16.mul(var17);
            UI3DScene.releaseMatrix4f(var17);
            var3.mul(var16, var16);
            if (var10.Mesh != nullptr && var10.Mesh.isReady() && var10.Mesh.m_transform != nullptr) {
               var10.Mesh.m_transform.transpose();
               var16.mul(var10.Mesh.m_transform);
               var10.Mesh.m_transform.transpose();
            }

            UI3DScene.releaseQuaternionf(var15);
            this.m_models.push_back(var10);
            this.m_transforms.push_back(var16);
         }
      }
   }

    void release() {
      s_pool.release(this);
   }
}
} // namespace vehicles
} // namespace zombie
