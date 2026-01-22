#pragma once
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "org/lwjgl/opengl/ARBFramebufferObject.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/EXTFramebufferObject.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL30.h"
// Use new SDL2/GLUS Display implementation
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/Util.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/ModelManager/AnimDirReloader.h"
#include "zombie/core/skinnedmodel/ModelManager/ModAnimations.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelMetaData.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/SoftwareSkinnedModelAnim.h"
#include "zombie/core/skinnedmodel/animation/StaticAnimation.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset/AnimationAssetParams.h"
#include "zombie/core/skinnedmodel/model/AnimationAssetManager.h"
#include "zombie/core/skinnedmodel/model/MeshAssetManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/Model/ModelAssetParams.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureInitializer.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/core/skinnedmodel/model/ModelMesh/MeshAssetParams.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VehicleModelInstance.h"
#include "zombie/core/skinnedmodel/model/VehicleSubModelInstance.h"
#include "zombie/core/skinnedmodel/population/PopTemplateManager.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/FireShader.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/ParticlesFire.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/PuddlesShader.h"
#include "zombie/iso/SmokeShader.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/WaterShader.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/AnimationsMesh.h"
#include "zombie/scripting/objects/ItemReplacement.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Skin.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/ModelInfo.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {


class ModelManager {
public:
    static bool NoOpenGL = false;
    static const ModelManager instance = std::make_shared<ModelManager>();
   private const std::unordered_map<std::string, Model> m_modelMap = std::make_unique<std::unordered_map<>>();
    Model m_maleModel;
    Model m_femaleModel;
    Model m_skeletonMaleModel;
    Model m_skeletonFemaleModel;
    TextureFBO bitmap;
    bool m_bCreated = false;
    bool bDebugEnableModels = true;
    bool bCreateSoftwareMeshes = false;
   public const std::unordered_map<std::string, SoftwareSkinnedModelAnim> SoftwareMeshAnims = std::make_unique<std::unordered_map<>>();
   private const std::vector<ModelSlot> m_modelSlots = std::make_unique<std::vector<>>();
   private const ObjectPool<ModelInstance> m_modelInstancePool = std::make_shared<ObjectPool>(ModelInstance::new);
   private const std::vector<WeaponPart> m_tempWeaponPartList = std::make_unique<std::vector<>>();
    ModelMesh m_animModel;
   private const std::unordered_map<std::string, AnimationAsset> m_animationAssets = std::make_unique<std::unordered_map<>>();
    const ModAnimations m_gameAnimations = std::make_shared<ModAnimations>("game");
   private const std::unordered_map<std::string, ModAnimations> m_modAnimations = std::make_unique<std::unordered_map<>>();
   private const std::vector<StaticAnimation> m_cachedAnims = std::make_unique<std::vector<>>();
   private const std::unordered_set<IsoGameCharacter> m_contains = std::make_unique<std::unordered_set<>>();
   private const std::vector<TorchInfo> m_torches = std::make_unique<std::vector<>>();
   private const std::stack<IsoLightSource> m_freeLights = std::make_unique<std::stack<>>();
   private const std::vector<IsoLightSource> m_torchLights = std::make_unique<std::vector<>>();
   private const std::vector<IsoGameCharacter> ToRemove = std::make_unique<std::vector<>>();
   private const std::vector<IsoGameCharacter> ToResetNextFrame = std::make_unique<std::vector<>>();
   private const std::vector<IsoGameCharacter> ToResetEquippedNextFrame = std::make_unique<std::vector<>>();
   private const std::vector<ModelSlot> m_resetAfterRender = std::make_unique<std::vector<>>();
   private const std::stack<IsoLightSource> m_lights = std::make_unique<std::stack<>>();
   private const std::stack<IsoLightSource> m_lightsTemp = std::make_unique<std::stack<>>();
    const Vector2 m_tempVec2 = std::make_shared<Vector2>();
    const Vector2 m_tempVec2_2 = std::make_shared<Vector2>();
   private static const std::map<std::string, ModelMetaData> modelMetaData = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
    static std::string basicEffect = "basicEffect";
    static std::string isStaticTrue = ";
    static std::string shaderEquals = "shader=";
    static std::string texA = ";
    static std::string amp = "&";
   static std::unordered_map<std::string, std::string> toLower = std::make_unique<std::unordered_map<>>();
   static std::unordered_map<std::string, std::string> toLowerTex = std::make_unique<std::unordered_map<>>();
   static std::unordered_map<std::string, std::string> toLowerKeyRoot = std::make_unique<std::unordered_map<>>();
    static std::stringstream builder = new std::stringstream();

    bool isCreated() {
      return this.m_bCreated;
   }

    void create() {
      if (!this.m_bCreated) {
         if (!GameServer.bServer || ServerGUI.isCreated()) {
    Texture var1 = std::make_shared<Texture>(1024, 1024, 16);
            PerformanceSettings.UseFBOs = false;

            try {
               this.bitmap = std::make_shared<TextureFBO>(var1, false);
            } catch (Exception var7) {
               var7.printStackTrace();
               PerformanceSettings.UseFBOs = false;
               DebugLog.Animation.error("FBO not compatible with gfx card at this time.");
               return;
            }
         }

         DebugLog.Animation.println("Loading 3D models");
         this.initAnimationMeshes(false);
         this.m_modAnimations.put(this.m_gameAnimations.m_modID, this.m_gameAnimations);
    AnimationsMesh var8 = ScriptManager.instance.getAnimationsMesh("Human");
    ModelMesh var2 = var8.modelMesh;
         if (!NoOpenGL && this.bCreateSoftwareMeshes) {
            SoftwareSkinnedModelAnim var3 = std::make_shared<SoftwareSkinnedModelAnim>(
               this.m_cachedAnims.toArray(new StaticAnimation[0]), var2.softwareMesh, var2.skinningData
            );
            this.SoftwareMeshAnims.put(var2.getPath().getPath(), var3);
         }

    Model var9 = this.loadModel("skinned/malebody", nullptr, var2);
    Model var4 = this.loadModel("skinned/femalebody", nullptr, var2);
    Model var5 = this.loadModel("skinned/Male_Skeleton", nullptr, var2);
    Model var6 = this.loadModel("skinned/Female_Skeleton", nullptr, var2);
         this.m_animModel = var2;
         this.loadModAnimations();
         var9.addDependency(this.getAnimationAssetRequired("bob/bob_idle"));
         var9.addDependency(this.getAnimationAssetRequired("bob/bob_walk"));
         var9.addDependency(this.getAnimationAssetRequired("bob/bob_run"));
         var4.addDependency(this.getAnimationAssetRequired("bob/bob_idle"));
         var4.addDependency(this.getAnimationAssetRequired("bob/bob_walk"));
         var4.addDependency(this.getAnimationAssetRequired("bob/bob_run"));
         this.m_maleModel = var9;
         this.m_femaleModel = var4;
         this.m_skeletonMaleModel = var5;
         this.m_skeletonFemaleModel = var6;
         this.m_bCreated = true;
         AdvancedAnimator.systemInit();
         PopTemplateManager.instance.init();
      }
   }

    void loadAdditionalModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
    bool var5 = this.bCreateSoftwareMeshes;
      if (DebugLog.isEnabled(DebugType.Animation)) {
         DebugLog.Animation.debugln("createSoftwareMesh: %B, model: %s", var5, var1);
      }

    Model var6 = this.loadModelInternal(var1, var2, var4, this.m_animModel, var3);
      if (var5) {
         SoftwareSkinnedModelAnim var7 = std::make_shared<SoftwareSkinnedModelAnim>(
            this.m_cachedAnims.toArray(new StaticAnimation[0]), var6.softwareMesh, (SkinningData)var6.Tag
         );
         this.SoftwareMeshAnims.put(var1.toLowerCase(), var7);
      }
   }

    ModelInstance newAdditionalModelInstance(const std::string& var1, const std::string& var2, IsoGameCharacter var3, AnimationPlayer var4, const std::string& var5) {
    Model var6 = this.tryGetLoadedModel(var1, var2, false, var5, false);
      if (var6 == nullptr) {
    bool var7 = false;
         instance.loadAdditionalModel(var1, var2, var7, var5);
      }

      var6 = this.getLoadedModel(var1, var2, false, var5);
      return this.newInstance(var6, var3, var4);
   }

    void loadAnimsFromDir(const std::string& var1, ModelMesh var2) {
    File var3 = std::make_shared<File>(ZomboidFileSystem.instance.base, var1);
      this.loadAnimsFromDir(ZomboidFileSystem.instance.baseURI, ZomboidFileSystem.instance.getMediaRootFile().toURI(), var3, var2, this.m_gameAnimations);
   }

    void loadAnimsFromDir(URI var1, URI var2, File var3, ModelMesh var4, ModAnimations var5) {
      if (!var3.exists()) {
         DebugLog.General.error("ERROR: %s", new Object[]{var3.getPath()});

         for (File var6 = var3.getParentFile(); var6 != nullptr; var6 = var6.getParentFile()) {
            DebugLog.General.error(" - Parent exists: %B, %s", new Object[]{var6.exists(), var6.getPath()});
         }
      }

      if (var3.isDirectory()) {
         File[] var13 = var3.listFiles();
         if (var13 != nullptr) {
    bool var7 = false;

    for (auto& var11 : var13)               if (var11.isDirectory()) {
                  this.loadAnimsFromDir(var1, var2, var11, var4, var5);
               } else {
    std::string var12 = ZomboidFileSystem.instance.getAnimName(var2, var11);
                  this.loadAnim(var12, var4, var5);
                  var7 = true;
                  if (!NoOpenGL && RenderThread.RenderThread == nullptr) {
                     lwjglx::opengl::Display::processMessages();
                  }
               }
            }

            if (var7) {
               DebugFileWatcher.instance.push_back(std::make_shared<AnimDirReloader>(this, var1, var2, var3.getPath(), var4, var5).GetFileWatcher());
            }
         }
      }
   }

    void RenderSkyBox(TextureDraw var1, int var2, int var3, int var4, int var5) {
    int var6 = TextureFBO.getCurrentID();
      switch (var4) {
         case 1:
            GL30.glBindFramebuffer(36160, var5);
            break;
         case 2:
            ARBFramebufferObject.glBindFramebuffer(36160, var5);
            break;
         case 3:
            EXTFramebufferObject.glBindFramebufferEXT(36160, var5);
      }

      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glOrtho(0.0, 1.0, 1.0, 0.0, -1.0, 1.0);
      GL11.glViewport(0, 0, 512, 512);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      ARBShaderObjects.glUseProgramObjectARB(var2);
      if (Shader.ShaderMap.containsKey(var2)) {
         ((Shader)Shader.ShaderMap.get(var2)).startRenderThread(var1);
      }

      GL11.glColor4f(0.13F, 0.96F, 0.13F, 1.0F);
      GL11.glBegin(7);
      GL11.glTexCoord2f(0.0F, 1.0F);
      GL11.glVertex2f(0.0F, 0.0F);
      GL11.glTexCoord2f(1.0F, 1.0F);
      GL11.glVertex2f(0.0F, 1.0F);
      GL11.glTexCoord2f(1.0F, 0.0F);
      GL11.glVertex2f(1.0F, 1.0F);
      GL11.glTexCoord2f(0.0F, 0.0F);
      GL11.glVertex2f(1.0F, 0.0F);
      GL11.glEnd();
      ARBShaderObjects.glUseProgramObjectARB(0);
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
    PlayerCamera var7 = SpriteRenderer.instance.getRenderingPlayerCamera(var3);
      GL11.glViewport(0, 0, var7.OffscreenWidth, var7.OffscreenHeight);
      switch (var4) {
         case 1:
            GL30.glBindFramebuffer(36160, var6);
            break;
         case 2:
            ARBFramebufferObject.glBindFramebuffer(36160, var6);
            break;
         case 3:
            EXTFramebufferObject.glBindFramebufferEXT(36160, var6);
      }

      SkyBox.getInstance().swapTextureFBO();
   }

    void RenderWater(TextureDraw var1, int var2, int var3, bool var4) {
      try {
         Util.checkGLError();
      } catch (Throwable var7) {
      }

      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      IsoWater.getInstance().waterProjection();
    PlayerCamera var5 = SpriteRenderer.instance.getRenderingPlayerCamera(var3);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      ARBShaderObjects.glUseProgramObjectARB(var2);
    Shader var6 = (Shader)Shader.ShaderMap.get(var2);
      if (dynamic_cast<WaterShader*>(var6) != nullptr) {
         ((WaterShader)var6).updateWaterParams(var1, var3);
      }

      IsoWater.getInstance().waterGeometry(var4);
      ARBShaderObjects.glUseProgramObjectARB(0);
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      if (!PZGLUtil.checkGLError(true)) {
         DebugLog.General.println("DEBUG: EXCEPTION RenderWater");
         PZGLUtil.printGLState(DebugLog.General);
      }
   }

    void RenderPuddles(int var1, int var2, int var3) {
      PZGLUtil.checkGLError(true);
      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      IsoPuddles.getInstance().puddlesProjection();
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      ARBShaderObjects.glUseProgramObjectARB(var1);
    Shader var4 = (Shader)Shader.ShaderMap.get(var1);
      if (dynamic_cast<PuddlesShader*>(var4) != nullptr) {
         ((PuddlesShader)var4).updatePuddlesParams(var2, var3);
      }

      IsoPuddles.getInstance().puddlesGeometry(var3);
      ARBShaderObjects.glUseProgramObjectARB(0);
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      if (!PZGLUtil.checkGLError(true)) {
         DebugLog.General.println("DEBUG: EXCEPTION RenderPuddles");
         PZGLUtil.printGLState(DebugLog.General);
      }
   }

    void RenderParticles(TextureDraw var1, int var2, int var3) {
    int var4 = ParticlesFire.getInstance().getFireShaderID();
    int var5 = ParticlesFire.getInstance().getSmokeShaderID();
    int var6 = ParticlesFire.getInstance().getVapeShaderID();

      try {
         Util.checkGLError();
      } catch (Throwable var9) {
      }

      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glViewport(
         0, 0, SpriteRenderer.instance.getRenderingPlayerCamera(var2).OffscreenWidth, SpriteRenderer.instance.getRenderingPlayerCamera(var2).OffscreenHeight
      );
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
    float var7 = ParticlesFire.getInstance().getShaderTime();
      GL11.glBlendFunc(770, 1);
      ARBShaderObjects.glUseProgramObjectARB(var4);
    Shader var8 = (Shader)Shader.ShaderMap.get(var4);
      if (dynamic_cast<FireShader*>(var8) != nullptr) {
         ((FireShader)var8).updateFireParams(var1, var2, var7);
      }

      ParticlesFire.getInstance().getGeometryFire(var3);
      GL11.glBlendFunc(770, 771);
      ARBShaderObjects.glUseProgramObjectARB(var5);
      var8 = (Shader)Shader.ShaderMap.get(var5);
      if (dynamic_cast<SmokeShader*>(var8) != nullptr) {
         ((SmokeShader)var8).updateSmokeParams(var1, var2, var7);
      }

      ParticlesFire.getInstance().getGeometry(var3);
      ARBShaderObjects.glUseProgramObjectARB(0);
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      GL11.glViewport(
         0, 0, SpriteRenderer.instance.getRenderingPlayerCamera(var2).OffscreenWidth, SpriteRenderer.instance.getRenderingPlayerCamera(var2).OffscreenHeight
      );
      if (!PZGLUtil.checkGLError(true)) {
         DebugLog.General.println("DEBUG: EXCEPTION RenderParticles");
         PZGLUtil.printGLState(DebugLog.General);
      }
   }

    void Reset(IsoGameCharacter var1) {
      if (var1.legsSprite != nullptr && var1.legsSprite.modelSlot != nullptr) {
    ModelSlot var2 = var1.legsSprite.modelSlot;
         this.resetModelInstance(var2.model, var2);

         for (int var3 = 0; var3 < var2.sub.size(); var3++) {
    ModelInstance var4 = (ModelInstance)var2.sub.get(var3);
            if (var4 != var1.primaryHandModel && var4 != var1.secondaryHandModel && !var2.attachedModels.contains(var4)) {
               this.resetModelInstanceRecurse(var4, var2);
            }
         }

         this.derefModelInstances(var1.getReadyModelData());
         var1.getReadyModelData().clear();
         this.dressInRandomOutfit(var1);
    Model var5 = this.getBodyModel(var1);
         var2.model = this.newInstance(var5, var1, var1.getAnimationPlayer());
         var2.model.setOwner(var2);
         var2.model.m_modelScript = ScriptManager.instance.getModelScript(var1.isFemale() ? "FemaleBody" : "MaleBody");
         this.DoCharacterModelParts(var1, var2);
      }
   }

    void reloadAllOutfits() {
      for (IsoGameCharacter var2 : this.m_contains) {
         var2.reloadOutfit();
      }
   }

    void Add(IsoGameCharacter var1) {
      if (this.m_bCreated) {
         if (var1.isSceneCulled()) {
            if (this.ToRemove.contains(var1)) {
               this.ToRemove.remove(var1);
               var1.legsSprite.modelSlot.bRemove = false;
            } else {
    ModelSlot var2 = this.getSlot(var1);
               var2.framesSinceStart = 0;
               if (var2.model != nullptr) {
                  RenderThread.invokeOnRenderContext(var2.model::destroySmartTextures);
               }

               this.dressInRandomOutfit(var1);
    Model var3 = this.getBodyModel(var1);
               var2.model = this.newInstance(var3, var1, var1.getAnimationPlayer());
               var2.model.setOwner(var2);
               var2.model.m_modelScript = ScriptManager.instance.getModelScript(var1.isFemale() ? "FemaleBody" : "MaleBody");
               this.DoCharacterModelParts(var1, var2);
               var2.active = true;
               var2.character = var1;
               var2.model.character = var1;
               var2.model.object = var1;
               var2.model.SetForceDir(var2.model.character.getForwardDirection());

               for (int var4 = 0; var4 < var2.sub.size(); var4++) {
    ModelInstance var5 = (ModelInstance)var2.sub.get(var4);
                  var5.character = var1;
                  var5.object = var1;
               }

               var1.legsSprite.modelSlot = var2;
               this.m_contains.push_back(var1);
               var1.onCullStateChanged(this, false);
               if (var2.model.AnimPlayer != nullptr && var2.model.AnimPlayer.isBoneTransformsNeedFirstFrame()) {
                  try {
                     var2.Update();
                  } catch (Throwable var6) {
                     ExceptionLogger.logException(var6);
                  }
               }
            }
         }
      }
   }

    void dressInRandomOutfit(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var2 != nullptr && !var2.isReanimatedPlayer() && !var2.wasFakeDead()) {
         if (DebugOptions.instance.ZombieOutfitRandom.getValue() && !var1.isPersistentOutfitInit()) {
            var2.bDressInRandomOutfit = true;
         }

         if (var2.bDressInRandomOutfit) {
            var2.bDressInRandomOutfit = false;
            var2.dressInRandomOutfit();
         }

         if (!var1.isPersistentOutfitInit()) {
            var2.dressInPersistentOutfitID(var1.getPersistentOutfitID());
         }
      } else {
         if (GameClient.bClient && var2 != nullptr && !var1.isPersistentOutfitInit() && var1.getPersistentOutfitID() != 0) {
            var2.dressInPersistentOutfitID(var1.getPersistentOutfitID());
         }
      }
   }

    Model getBodyModel(IsoGameCharacter var1) {
      if (var1.isZombie() && ((IsoZombie)var1).isSkeleton()) {
         return var1.isFemale() ? this.m_skeletonFemaleModel : this.m_skeletonMaleModel;
      } else {
         return var1.isFemale() ? this.m_femaleModel : this.m_maleModel;
      }
   }

    bool ContainsChar(IsoGameCharacter var1) {
      return this.m_contains.contains(var1) && !this.ToRemove.contains(var1);
   }

    void ResetCharacterEquippedHands(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.legsSprite != nullptr && var1.legsSprite.modelSlot != nullptr) {
         this.DoCharacterModelEquipped(var1, var1.legsSprite.modelSlot);
      }
   }

    void DoCharacterModelEquipped(IsoGameCharacter var1, ModelSlot var2) {
      if (var1.primaryHandModel != nullptr) {
         var1.clearVariable("RightHandMask");
         var1.primaryHandModel.maskVariableValue = nullptr;
         this.resetModelInstanceRecurse(var1.primaryHandModel, var2);
         var2.sub.remove(var1.primaryHandModel);
         var2.model.sub.remove(var1.primaryHandModel);
         var1.primaryHandModel = nullptr;
      }

      if (var1.secondaryHandModel != nullptr) {
         var1.clearVariable("LeftHandMask");
         var1.secondaryHandModel.maskVariableValue = nullptr;
         this.resetModelInstanceRecurse(var1.secondaryHandModel, var2);
         var2.sub.remove(var1.secondaryHandModel);
         var2.model.sub.remove(var1.secondaryHandModel);
         var1.secondaryHandModel = nullptr;
      }

      for (int var3 = 0; var3 < var2.attachedModels.size(); var3++) {
    ModelInstance var4 = (ModelInstance)var2.attachedModels.get(var3);
         this.resetModelInstanceRecurse(var4, var2);
         var2.sub.remove(var4);
         var2.model.sub.remove(var4);
      }

      var2.attachedModels.clear();

      for (int var10 = 0; var10 < var1.getAttachedItems().size(); var10++) {
    AttachedItem var12 = var1.getAttachedItems().get(var10);
    std::string var5 = var12.getItem().getStaticModel();
         if (!StringUtils.isNullOrWhitespace(var5)) {
    std::string var6 = var1.getAttachedItems().getGroup().getLocation(var12.getLocation()).getAttachmentName();
    ModelInstance var7 = this.addStatic(var2.model, var5, var6, var6);
            if (var7 != nullptr) {
               var7.setOwner(var2);
               var2.sub.push_back(var7);
    HandWeapon var8 = (HandWeapon)Type.tryCastTo(var12.getItem(), HandWeapon.class);
               if (var8 != nullptr) {
                  this.addWeaponPartModels(var2, var8, var7);
                  if (!Core.getInstance().getOptionSimpleWeaponTextures()) {
    ModelInstanceTextureInitializer var9 = ModelInstanceTextureInitializer.alloc();
                     var9.init(var7, var8);
                     var7.setTextureInitializer(var9);
                  }
               }

               var2.attachedModels.push_back(var7);
            }
         }
      }

      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
      }

    InventoryItem var11 = var1.getPrimaryHandItem();
    InventoryItem var13 = var1.getSecondaryHandItem();
      if (var1.isHideWeaponModel()) {
         var11 = nullptr;
         var13 = nullptr;
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.forceNullOverride) {
         var11 = nullptr;
         var13 = nullptr;
         var1.forceNullOverride = false;
      }

    bool var14 = false;
    BaseAction var15 = var1.getCharacterActions().empty() ? nullptr : (BaseAction)var1.getCharacterActions().get(0);
      if (var15 != nullptr && var15.overrideHandModels) {
         var14 = true;
         var11 = nullptr;
         if (var15.getPrimaryHandItem() != nullptr) {
            var11 = var15.getPrimaryHandItem();
         } else if (var15.getPrimaryHandMdl() != nullptr) {
            var1.primaryHandModel = this.addStatic(var2, var15.getPrimaryHandMdl(), "Bip01_Prop1");
         }

         var13 = nullptr;
         if (var15.getSecondaryHandItem() != nullptr) {
            var13 = var15.getSecondaryHandItem();
         } else if (var15.getSecondaryHandMdl() != nullptr) {
            var1.secondaryHandModel = this.addStatic(var2, var15.getSecondaryHandMdl(), "Bip01_Prop2");
         }
      }

      if (!StringUtils.isNullOrEmpty(var1.overridePrimaryHandModel)) {
         var14 = true;
         var1.primaryHandModel = this.addStatic(var2, var1.overridePrimaryHandModel, "Bip01_Prop1");
      }

      if (!StringUtils.isNullOrEmpty(var1.overrideSecondaryHandModel)) {
         var14 = true;
         var1.secondaryHandModel = this.addStatic(var2, var1.overrideSecondaryHandModel, "Bip01_Prop2");
      }

      if (var11 != nullptr) {
    ItemReplacement var16 = var11.getItemReplacementPrimaryHand();
         var1.primaryHandModel = this.addEquippedModelInstance(var1, var2, var11, "Bip01_Prop1", var16, var14);
      }

      if (var13 != nullptr && var11 != var13) {
    ItemReplacement var17 = var13.getItemReplacementSecondHand();
         var1.secondaryHandModel = this.addEquippedModelInstance(var1, var2, var13, "Bip01_Prop2", var17, var14);
      }
   }

    ModelInstance addEquippedModelInstance(IsoGameCharacter var1, ModelSlot var2, InventoryItem var3, const std::string& var4, ItemReplacement var5, bool var6) {
    HandWeapon var8 = (HandWeapon)Type.tryCastTo(var3, HandWeapon.class);
      if (var8 != nullptr) {
    std::string var9 = var8.getStaticModel();
    ModelInstance var7 = this.addStatic(var2, var9, var4);
         this.addWeaponPartModels(var2, var8, var7);
         if (Core.getInstance().getOptionSimpleWeaponTextures()) {
    return var7;
         } else {
    ModelInstanceTextureInitializer var10 = ModelInstanceTextureInitializer.alloc();
            var10.init(var7, var8);
            var7.setTextureInitializer(var10);
    return var7;
         }
      } else {
         if (var3 != nullptr) {
            if (var5 != nullptr
               && !StringUtils.isNullOrEmpty(var5.maskVariableValue)
               && (var5.clothingItem != nullptr || !StringUtils.isNullOrWhitespace(var3.getStaticModel()))) {
               return this.addMaskingModel(var2, var1, var3, var5, var5.maskVariableValue, var5.attachment, var4);
            }

            if (var6 && !StringUtils.isNullOrWhitespace(var3.getStaticModel())) {
               return this.addStatic(var2, var3.getStaticModel(), var4);
            }
         }

    return nullptr;
      }
   }

    ModelInstance addMaskingModel(ModelSlot var1, IsoGameCharacter var2, InventoryItem var3, ItemReplacement var4, const std::string& var5, const std::string& var6, const std::string& var7) {
    ModelInstance var8 = nullptr;
    ItemVisual var9 = var3.getVisual();
      if (var4.clothingItem != nullptr && var9 != nullptr) {
         var8 = PopTemplateManager.instance.addClothingItem(var2, var1, var9, var4.clothingItem);
      } else {
         if (StringUtils.isNullOrWhitespace(var3.getStaticModel())) {
    return nullptr;
         }

    std::string var10 = nullptr;
         if (var9 != nullptr && var3.getClothingItem() != nullptr) {
            var10 = (std::string)var3.getClothingItem().getTextureChoices().get(var9.getTextureChoice());
         }

         if (!StringUtils.isNullOrEmpty(var6)) {
            var8 = this.addStaticForcedTex(var1.model, var3.getStaticModel(), var6, var6, var10);
         } else {
            var8 = this.addStaticForcedTex(var1, var3.getStaticModel(), var7, var10);
         }

         var8.maskVariableValue = var5;
         if (var9 != nullptr) {
            var8.tintR = var9.m_Tint.r;
            var8.tintG = var9.m_Tint.g;
            var8.tintB = var9.m_Tint.b;
         }
      }

      if (!StringUtils.isNullOrEmpty(var5)) {
         var2.setVariable(var4.maskVariableName, var5);
         var2.bUpdateEquippedTextures = true;
      }

    return var8;
   }

    void addWeaponPartModels(ModelSlot var1, HandWeapon var2, ModelInstance var3) {
    std::vector var4 = var2.getModelWeaponPart();
      if (var4 != nullptr) {
    std::vector var5 = var2.getAllWeaponParts(this.m_tempWeaponPartList);

         for (int var6 = 0; var6 < var5.size(); var6++) {
    WeaponPart var7 = (WeaponPart)var5.get(var6);

            for (int var8 = 0; var8 < var4.size(); var8++) {
    ModelWeaponPart var9 = (ModelWeaponPart)var4.get(var8);
               if (var7.getFullType() == var9.partType)) {
    ModelInstance var10 = this.addStatic(var3, var9.modelName, var9.attachmentNameSelf, var9.attachmentParent);
                  var10.setOwner(var1);
               }
            }
         }
      }
   }

    void resetModelInstance(ModelInstance var1, void* var2) {
      if (var1 != nullptr) {
         var1.clearOwner(var2);
         if (var1.isRendering()) {
            var1.bResetAfterRender = true;
         } else {
            if (dynamic_cast<VehicleModelInstance*>(var1) != nullptr) {
               return;
            }

            if (dynamic_cast<VehicleSubModelInstance*>(var1) != nullptr) {
               return;
            }

            var1.reset();
            this.m_modelInstancePool.release(var1);
         }
      }
   }

    void resetModelInstanceRecurse(ModelInstance var1, void* var2) {
      if (var1 != nullptr) {
         this.resetModelInstancesRecurse(var1.sub, var2);
         this.resetModelInstance(var1, var2);
      }
   }

    void resetModelInstancesRecurse(std::vector<ModelInstance> var1, void* var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    ModelInstance var4 = (ModelInstance)var1.get(var3);
         this.resetModelInstance(var4, var2);
      }
   }

    void derefModelInstance(ModelInstance var1) {
      if (var1 != nullptr) {
         assert var1.renderRefCount > 0;

         var1.renderRefCount--;
         if (var1.bResetAfterRender && !var1.isRendering()) {
            assert var1.getOwner() == nullptr;

            if (dynamic_cast<VehicleModelInstance*>(var1) != nullptr) {
               return;
            }

            if (dynamic_cast<VehicleSubModelInstance*>(var1) != nullptr) {
               return;
            }

            var1.reset();
            this.m_modelInstancePool.release(var1);
         }
      }
   }

    void derefModelInstances(std::vector<ModelInstance> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
    ModelInstance var3 = (ModelInstance)var1.get(var2);
         this.derefModelInstance(var3);
      }
   }

    void DoCharacterModelParts(IsoGameCharacter var1, ModelSlot var2) {
      if (var2.isRendering()) {
    bool var3 = false;
      }

      if (DebugLog.isEnabled(DebugType.Clothing)) {
         DebugLog.Clothing.debugln("Char: " + var1 + " Slot: " + var2);
      }

      var2.sub.clear();
      PopTemplateManager.instance.populateCharacterModelSlot(var1, var2);
      this.DoCharacterModelEquipped(var1, var2);
   }

    void update() {
      for (int var1 = 0; var1 < this.ToResetNextFrame.size(); var1++) {
    IsoGameCharacter var2 = this.ToResetNextFrame.get(var1);
         this.Reset(var2);
      }

      this.ToResetNextFrame.clear();

      for (int var4 = 0; var4 < this.ToResetEquippedNextFrame.size(); var4++) {
    IsoGameCharacter var9 = this.ToResetEquippedNextFrame.get(var4);
         this.ResetCharacterEquippedHands(var9);
      }

      this.ToResetEquippedNextFrame.clear();

      for (int var5 = 0; var5 < this.ToRemove.size(); var5++) {
    IsoGameCharacter var10 = this.ToRemove.get(var5);
         this.DoRemove(var10);
      }

      this.ToRemove.clear();

      for (int var6 = 0; var6 < this.m_resetAfterRender.size(); var6++) {
    ModelSlot var11 = this.m_resetAfterRender.get(var6);
         if (!var11.isRendering()) {
            var11.reset();
            this.m_resetAfterRender.remove(var6--);
         }
      }

      this.m_lights.clear();
      if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
         this.m_lights.addAll(IsoWorld.instance.CurrentCell.getLamppostPositions());
    std::vector var7 = IsoWorld.instance.CurrentCell.getVehicles();

         for (int var12 = 0; var12 < var7.size(); var12++) {
    BaseVehicle var3 = (BaseVehicle)var7.get(var12);
            if (var3.sprite != nullptr && var3.sprite.hasActiveModel()) {
               ((VehicleModelInstance)var3.sprite.modelSlot.model).UpdateLights();
            }
         }
      }

      this.m_freeLights.addAll(this.m_torchLights);
      this.m_torchLights.clear();
      this.m_torches.clear();
      LightingJNI.getTorches(this.m_torches);

      for (int var8 = 0; var8 < this.m_torches.size(); var8++) {
    TorchInfo var13 = this.m_torches.get(var8);
    IsoLightSource var14 = this.m_freeLights.empty() ? std::make_shared<IsoLightSource>(0, 0, 0, 1.0F, 1.0F, 1.0F, 1) : this.m_freeLights.pop();
         var14.x = (int)var13.x;
         var14.y = (int)var13.y;
         var14.z = (int)var13.z;
         var14.r = 1.0F;
         var14.g = 0.85F;
         var14.b = 0.6F;
         var14.radius = (int)Math.ceil(var13.dist);
         this.m_torchLights.push_back(var14);
      }
   }

    ModelSlot addNewSlot(IsoGameCharacter var1) {
    ModelSlot var2 = std::make_shared<ModelSlot>(this.m_modelSlots.size(), nullptr, var1);
      this.m_modelSlots.push_back(var2);
    return var2;
   }

    ModelSlot getSlot(IsoGameCharacter var1) {
      for (int var2 = 0; var2 < this.m_modelSlots.size(); var2++) {
    ModelSlot var3 = this.m_modelSlots.get(var2);
         if (!var3.bRemove && !var3.isRendering() && !var3.active) {
    return var3;
         }
      }

      return this.addNewSlot(var1);
   }

    bool DoRemove(IsoGameCharacter var1) {
      if (!this.m_contains.contains(var1)) {
    return false;
      } else {
    bool var2 = false;

         for (int var3 = 0; var3 < this.m_modelSlots.size(); var3++) {
    ModelSlot var4 = this.m_modelSlots.get(var3);
            if (var4.character == var1) {
               var1.legsSprite.modelSlot = nullptr;
               this.m_contains.remove(var1);
               if (!var1.isSceneCulled()) {
                  var1.onCullStateChanged(this, true);
               }

               if (!this.m_resetAfterRender.contains(var4)) {
                  this.m_resetAfterRender.push_back(var4);
               }

               var2 = true;
            }
         }

    return var2;
      }
   }

    void Remove(IsoGameCharacter var1) {
      if (!var1.isSceneCulled()) {
         if (!this.ToRemove.contains(var1)) {
            var1.legsSprite.modelSlot.bRemove = true;
            this.ToRemove.push_back(var1);
            var1.onCullStateChanged(this, true);
         } else if (this.ContainsChar(var1)) {
            throw IllegalStateException("IsoGameCharacter.isSceneCulled() = true inconsistent with ModelManager.ContainsChar() = true");
         }
      }
   }

    void Remove(BaseVehicle var1) {
      if (var1.sprite != nullptr && var1.sprite.modelSlot != nullptr) {
    ModelSlot var2 = var1.sprite.modelSlot;
         if (!this.m_resetAfterRender.contains(var2)) {
            this.m_resetAfterRender.push_back(var2);
         }

         var1.sprite.modelSlot = nullptr;
      }
   }

    void ResetNextFrame(IsoGameCharacter var1) {
      if (!this.ToResetNextFrame.contains(var1)) {
         this.ToResetNextFrame.push_back(var1);
      }
   }

    void ResetEquippedNextFrame(IsoGameCharacter var1) {
      if (!this.ToResetEquippedNextFrame.contains(var1)) {
         this.ToResetEquippedNextFrame.push_back(var1);
      }
   }

    void Reset() {
      RenderThread.invokeOnRenderContext(() -> {
         for (IsoGameCharacter var2 : this.ToRemove) {
            this.DoRemove(var2);
         }

         this.ToRemove.clear();

         try {
            if (!this.m_contains.empty()) {
               IsoGameCharacter[] var7 = this.m_contains.toArray(new IsoGameCharacter[0]);

    for (auto& var5 : var7)                  this.DoRemove(var5);
               }
            }

            this.m_modelSlots.clear();
         } catch (Exception var6) {
            DebugLog.Animation.error("Exception thrown removing Models.");
            var6.printStackTrace();
         }
      });
      this.m_lights.clear();
      this.m_lightsTemp.clear();
   }

    void getClosestThreeLights(IsoMovingObject var1, IsoLightSource[] var2) {
      this.m_lightsTemp.clear();

      for (IsoLightSource var4 : this.m_lights) {
         if (var4.bActive
            && var4.life != 0
            && (var4.localToBuilding == nullptr || var1.getCurrentBuilding() == var4.localToBuilding)
            && !(IsoUtils.DistanceTo(var1.x, var1.y, var4.x + 0.5F, var4.y + 0.5F) >= var4.radius)
            && LosUtil.lineClear(IsoWorld.instance.CurrentCell, (int)var1.x, (int)var1.y, (int)var1.z, var4.x, var4.y, var4.z, false) != TestResults.Blocked) {
            this.m_lightsTemp.push_back(var4);
         }
      }

      if (dynamic_cast<BaseVehicle*>(var1) != nullptr) {
         for (int var8 = 0; var8 < this.m_torches.size(); var8++) {
    TorchInfo var9 = this.m_torches.get(var8);
            if (!(IsoUtils.DistanceTo(var1.x, var1.y, var9.x, var9.y) >= var9.dist)
               && LosUtil.lineClear(IsoWorld.instance.CurrentCell, (int)var1.x, (int)var1.y, (int)var1.z, (int)var9.x, (int)var9.y, (int)var9.z, false)
                  != TestResults.Blocked) {
               if (var9.bCone) {
    Vector2 var5 = this.m_tempVec2;
                  var5.x = var9.x - var1.x;
                  var5.y = var9.y - var1.y;
                  var5.normalize();
    Vector2 var6 = this.m_tempVec2_2;
                  var6.x = var9.angleX;
                  var6.y = var9.angleY;
                  var6.normalize();
    float var7 = var5.dot(var6);
                  if (var7 >= -0.92F) {
                     continue;
                  }
               }

               this.m_lightsTemp.push_back(this.m_torchLights.get(var8));
            }
         }
      }

      PZArrayUtil.sort(this.m_lightsTemp, Lambda.comparator(var1, (var0, var1x, var2x) -> {
    float var3 = var2x.DistTo(var0.x, var0.y);
    float var4x = var2x.DistTo(var1x.x, var1x.y);
         if (var3 > var4x) {
    return 1;
         } else {
            return var3 < var4x ? -1 : 0;
         }
      }));
      var2[0] = var2[1] = var2[2] = nullptr;
      if (this.m_lightsTemp.size() > 0) {
         var2[0] = this.m_lightsTemp.get(0);
      }

      if (this.m_lightsTemp.size() > 1) {
         var2[1] = this.m_lightsTemp.get(1);
      }

      if (this.m_lightsTemp.size() > 2) {
         var2[2] = this.m_lightsTemp.get(2);
      }
   }

    void addVehicle(BaseVehicle var1) {
      if (this.m_bCreated) {
         if (!GameServer.bServer || ServerGUI.isCreated()) {
            if (var1 != nullptr && var1.getScript() != nullptr) {
    VehicleScript var2 = var1.getScript();
    std::string var3 = var1.getScript().getModel().file;
    Model var4 = this.getLoadedModel(var3);
               if (var4 == nullptr) {
                  DebugLog.Animation.error("Failed to find vehicle model: %s", new Object[]{var3});
               } else {
                  if (DebugLog.isEnabled(DebugType.Animation)) {
                     DebugLog.Animation.debugln("%s", var3);
                  }

    VehicleModelInstance var5 = std::make_shared<VehicleModelInstance>();
                  var5.init(var4, nullptr, var1.getAnimationPlayer());
                  var5.applyModelScriptScale(var3);
                  var1.getSkin();
    Skin var6 = var2.getTextures();
                  if (var1.getSkinIndex() >= 0 && var1.getSkinIndex() < var2.getSkinCount()) {
                     var6 = var2.getSkin(var1.getSkinIndex());
                  }

                  var5.LoadTexture(var6.texture);
                  var5.tex = var6.textureData;
                  var5.textureMask = var6.textureDataMask;
                  var5.textureDamage1Overlay = var6.textureDataDamage1Overlay;
                  var5.textureDamage1Shell = var6.textureDataDamage1Shell;
                  var5.textureDamage2Overlay = var6.textureDataDamage2Overlay;
                  var5.textureDamage2Shell = var6.textureDataDamage2Shell;
                  var5.textureLights = var6.textureDataLights;
                  var5.textureRust = var6.textureDataRust;
                  if (var5.tex != nullptr) {
                     var5.tex.bindAlways = true;
                  } else {
                     DebugLog.Animation.error("texture not found:", new Object[]{var1.getSkin()});
                  }

    ModelSlot var7 = this.getSlot(nullptr);
                  var7.model = var5;
                  var5.setOwner(var7);
                  var5.object = var1;
                  var7.sub.clear();

                  for (int var8 = 0; var8 < var1.models.size(); var8++) {
    ModelInfo var9 = (ModelInfo)var1.models.get(var8);
    Model var10 = this.getLoadedModel(var9.scriptModel.file);
                     if (var10 == nullptr) {
                        DebugLog.Animation.error("vehicle.models[%d] not found: %s", new Object[]{var8, var9.scriptModel.file});
                     } else {
    VehicleSubModelInstance var11 = std::make_shared<VehicleSubModelInstance>();
                        var11.init(var10, nullptr, var9.getAnimationPlayer());
                        var11.setOwner(var7);
                        var11.applyModelScriptScale(var9.scriptModel.file);
                        var11.object = var1;
                        var11.parent = var5;
                        var5.sub.push_back(var11);
                        var11.modelInfo = var9;
                        if (var11.tex == nullptr) {
                           var11.tex = var5.tex;
                        }

                        var7.sub.push_back(var11);
                        var9.modelInstance = var11;
                     }
                  }

                  var7.active = true;
                  var1.sprite.modelSlot = var7;
               }
            }
         }
      }
   }

    ModelInstance addStatic(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    ModelInstance var6 = this.newStaticInstance(var1, var2, var3, var4, var5);
      if (var6 == nullptr) {
    return nullptr;
      } else {
         var1.sub.push_back(var6);
         var6.setOwner(var1);
         var1.model.sub.push_back(var6);
    return var6;
      }
   }

    ModelInstance newStaticInstance(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
      if (DebugLog.isEnabled(DebugType.Animation)) {
         DebugLog.Animation.debugln("Adding Static Model:" + var2);
      }

    Model var6 = this.tryGetLoadedModel(var2, var3, true, var5, false);
      if (var6 == nullptr && var2 != nullptr) {
         this.loadStaticModel(var2, var3, var5);
         var6 = this.getLoadedModel(var2, var3, true, var5);
         if (var6 == nullptr) {
            if (DebugLog.isEnabled(DebugType.Animation)) {
               DebugLog.Animation.error("Model not found. model:" + var2 + " tex:" + var3);
            }

    return nullptr;
         }
      }

      if (var2 == nullptr) {
         var6 = this.tryGetLoadedModel("vehicles_wheel02", "vehicles/vehicle_wheel02", true, "vehiclewheel", false);
      }

    ModelInstance var7 = this.newInstance(var6, var1.character, var1.model.AnimPlayer);
      var7.parent = var1.model;
      if (var1.model.AnimPlayer != nullptr) {
         var7.parentBone = var1.model.AnimPlayer.getSkinningBoneIndex(var4, var7.parentBone);
         var7.parentBoneName = var4;
      }

      var7.AnimPlayer = var1.model.AnimPlayer;
    return var7;
   }

    ModelInstance addStatic(ModelSlot var1, const std::string& var2, const std::string& var3) {
      return this.addStaticForcedTex(var1, var2, var3, nullptr);
   }

    ModelInstance addStaticForcedTex(ModelSlot var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    std::string var5 = ScriptManager.getItemName(var2);
    std::string var6 = ScriptManager.getItemName(var2);
    std::string var7 = nullptr;
    ModelMetaData var8 = modelMetaData.get(var2);
      if (var8 != nullptr) {
         if (!StringUtils.isNullOrWhitespace(var8.meshName)) {
            var5 = var8.meshName;
         }

         if (!StringUtils.isNullOrWhitespace(var8.textureName)) {
            var6 = var8.textureName;
         }

         if (!StringUtils.isNullOrWhitespace(var8.shaderName)) {
            var7 = var8.shaderName;
         }
      }

      if (!StringUtils.isNullOrEmpty(var4)) {
         var6 = var4;
      }

    ModelScript var9 = ScriptManager.instance.getModelScript(var2);
      if (var9 != nullptr) {
         var5 = var9.getMeshName();
         var6 = var9.getTextureName();
         var7 = var9.getShaderName();
    ModelInstance var10 = this.addStatic(var1, var5, var6, var3, var7);
         if (var10 != nullptr) {
            var10.applyModelScriptScale(var2);
         }

    return var10;
      } else {
         return this.addStatic(var1, var5, var6, var3, var7);
      }
   }

    ModelInstance addStatic(ModelInstance var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      return this.addStaticForcedTex(var1, var2, var3, var4, nullptr);
   }

    ModelInstance addStaticForcedTex(ModelInstance var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    std::string var6 = ScriptManager.getItemName(var2);
    std::string var7 = ScriptManager.getItemName(var2);
    std::string var8 = nullptr;
    ModelScript var9 = ScriptManager.instance.getModelScript(var2);
      if (var9 != nullptr) {
         var6 = var9.getMeshName();
         var7 = var9.getTextureName();
         var8 = var9.getShaderName();
      }

      if (!StringUtils.isNullOrEmpty(var5)) {
         var7 = var5;
      }

    Model var10 = this.tryGetLoadedModel(var6, var7, true, var8, false);
      if (var10 == nullptr && var6 != nullptr) {
         this.loadStaticModel(var6, var7, var8);
         var10 = this.getLoadedModel(var6, var7, true, var8);
         if (var10 == nullptr) {
            if (DebugLog.isEnabled(DebugType.Animation)) {
               DebugLog.Animation.error("Model not found. model:" + var6 + " tex:" + var7);
            }

    return nullptr;
         }
      }

      if (var6 == nullptr) {
         var10 = this.tryGetLoadedModel("vehicles_wheel02", "vehicles/vehicle_wheel02", true, "vehiclewheel", false);
      }

      if (var10 == nullptr) {
    return nullptr;
      } else {
    ModelInstance var11 = (ModelInstance)this.m_modelInstancePool.alloc();
         if (var1 != nullptr) {
            var11.init(var10, var1.character, var1.AnimPlayer);
            var11.parent = var1;
            var1.sub.push_back(var11);
         } else {
            var11.init(var10, nullptr, nullptr);
         }

         if (var9 != nullptr) {
            var11.applyModelScriptScale(var2);
         }

         var11.attachmentNameSelf = var3;
         var11.attachmentNameParent = var4;
    return var11;
      }
   }

    std::string modifyShaderName(const std::string& var1) {
      if ((StringUtils == var1, "vehicle") || StringUtils == var1, "vehicle_multiuv") || StringUtils == var1, "vehicle_norandom_multiuv"))
         && !Core.getInstance().getPerfReflectionsOnLoad()) {
         var1 = var1 + "_noreflect";
      }

    return var1;
   }

    Model loadModelInternal(const std::string& var1, const std::string& var2, const std::string& var3, ModelMesh var4, bool var5) {
      var3 = this.modifyShaderName(var3);
    ModelAssetParams var6 = std::make_shared<ModelAssetParams>();
      var6.animationsModel = var4;
      var6.bStatic = var5;
      var6.meshName = var1;
      var6.shaderName = var3;
      var6.textureName = var2;
      if (var3 != nullptr && StringUtils.startsWithIgnoreCase(var3, "vehicle")) {
         var6.textureFlags = TextureID.bUseCompression ? 4 : 0;
         var6.textureFlags |= 256;
      } else {
         var6.textureFlags = this.getTextureFlags();
      }

    std::string var7 = this.createModelKey(var1, var2, var5, var3);
    Model var8 = (Model)ModelAssetManager.instance.load(std::make_shared<AssetPath>(var7), var6);
      if (var8 != nullptr) {
         this.putLoadedModel(var1, var2, var5, var3, var8);
      }

    return var8;
   }

    int getTextureFlags() {
    int var1 = TextureID.bUseCompression ? 4 : 0;
      if (Core.OptionModelTextureMipmaps) {
      }

      return var1 | 128;
   }

    void setModelMetaData(const std::string& var1, const std::string& var2, const std::string& var3, bool var4) {
      this.setModelMetaData(var1, var1, var2, var3, var4);
   }

    void setModelMetaData(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, bool var5) {
    ModelMetaData var6 = std::make_shared<ModelMetaData>();
      var6.meshName = var2;
      var6.textureName = var3;
      var6.shaderName = var4;
      var6.bStatic = var5;
      modelMetaData.put(var1, var6);
   }

    Model loadStaticModel(const std::string& var1, const std::string& var2, const std::string& var3) {
    std::string var4 = this.modifyShaderName(var3);
      return this.loadModelInternal(var1, var2, var4, nullptr, true);
   }

    Model loadModel(const std::string& var1, const std::string& var2, ModelMesh var3) {
      return this.loadModelInternal(var1, var2, "basicEffect", var3, false);
   }

    Model getLoadedModel(const std::string& var1) {
    ModelScript var2 = ScriptManager.instance.getModelScript(var1);
      if (var2 != nullptr) {
         if (var2.loadedModel != nullptr) {
            return var2.loadedModel;
         } else {
            var2.shaderName = this.modifyShaderName(var2.shaderName);
    Model var10 = this.tryGetLoadedModel(var2.getMeshName(), var2.getTextureName(), var2.bStatic, var2.getShaderName(), false);
            if (var10 != nullptr) {
               var2.loadedModel = var10;
    return var10;
            } else {
    AnimationsMesh var13 = var2.animationsMesh == nullptr ? nullptr : ScriptManager.instance.getAnimationsMesh(var2.animationsMesh);
    ModelMesh var14 = var13 == nullptr ? nullptr : var13.modelMesh;
               var10 = var2.bStatic
                  ? this.loadModelInternal(var2.getMeshName(), var2.getTextureName(), var2.getShaderName(), nullptr, true)
                  : this.loadModelInternal(var2.getMeshName(), var2.getTextureName(), var2.getShaderName(), var14, false);
               var2.loadedModel = var10;
    return var10;
            }
         }
      } else {
    ModelMetaData var3 = modelMetaData.get(var1);
         if (var3 != nullptr) {
            var3.shaderName = this.modifyShaderName(var3.shaderName);
    Model var12 = this.tryGetLoadedModel(var3.meshName, var3.textureName, var3.bStatic, var3.shaderName, false);
            if (var12 != nullptr) {
    return var12;
            } else {
               return var3.bStatic
                  ? this.loadStaticModel(var3.meshName, var3.textureName, var3.shaderName)
                  : this.loadModel(var3.meshName, var3.textureName, this.m_animModel);
            }
         } else {
    Model var4 = this.tryGetLoadedModel(var1, nullptr, false, nullptr, false);
            if (var4 != nullptr) {
    return var4;
            } else {
    std::string var5 = var1.toLowerCase().trim();

               for (Entry var7 : this.m_modelMap.entrySet()) {
    std::string var8 = (std::string)var7.getKey();
                  if (var8.startsWith(var5)) {
    Model var9 = (Model)var7.getValue();
                     if (var9 != nullptr && (var8.length() == var5.length() || var8.charAt(var5.length()) == '&')) {
                        var4 = var9;
                        break;
                     }
                  }
               }

               if (var4 == nullptr && DebugLog.isEnabled(DebugType.Animation)) {
                  DebugLog.Animation.error("ModelManager.getLoadedModel> Model missing for key=\"" + var5 + "\"");
               }

    return var4;
            }
         }
      }
   }

    Model getLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
      return this.tryGetLoadedModel(var1, var2, var3, var4, true);
   }

    Model tryGetLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4, bool var5) {
    std::string var6 = this.createModelKey(var1, var2, var3, var4);
      if (var6 == nullptr) {
    return nullptr;
      } else {
    Model var7 = this.m_modelMap.get(var6);
         if (var7 == nullptr && var5 && DebugLog.isEnabled(DebugType.Animation)) {
            DebugLog.Animation.error("ModelManager.getLoadedModel> Model missing for key=\"" + var6 + "\"");
         }

    return var7;
      }
   }

    void putLoadedModel(const std::string& var1, const std::string& var2, bool var3, const std::string& var4, Model var5) {
    std::string var6 = this.createModelKey(var1, var2, var3, var4);
      if (var6 != nullptr) {
    Model var7 = this.m_modelMap.get(var6);
         if (var7 != var5) {
            if (var7 != nullptr) {
               DebugLog.Animation.debugln("Override key=\"%s\" old=%s new=%s", var6, var7, var5);
            } else {
               DebugLog.Animation.debugln("key=\"%s\" model=%s", var6, var5);
            }

            this.m_modelMap.put(var6, var5);
            var5.Name = var6;
         }
      }
   }

    std::string createModelKey(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
      builder.delete(0, builder.length());
      if (var1 == nullptr) {
    return nullptr;
      } else {
         if (!toLowerKeyRoot.containsKey(var1)) {
            toLowerKeyRoot.put(var1, var1.toLowerCase(Locale.ENGLISH).trim());
         }

         builder.append(toLowerKeyRoot.get(var1));
         builder.append(amp);
         if (StringUtils.isNullOrWhitespace(var4)) {
            var4 = basicEffect;
         }

         builder.append(shaderEquals);
         if (!toLower.containsKey(var4)) {
            toLower.put(var4, var4.toLowerCase().trim());
         }

         builder.append(toLower.get(var4));
         if (!StringUtils.isNullOrWhitespace(var2)) {
            builder.append(texA);
            if (!toLowerTex.containsKey(var2)) {
               toLowerTex.put(var2, var2.toLowerCase().trim());
            }

            builder.append(toLowerTex.get(var2));
         }

         if (var3) {
            builder.append(isStaticTrue);
         }

         return builder;
      }
   }

    std::string createModelKey2(const std::string& var1, const std::string& var2, bool var3, const std::string& var4) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         if (StringUtils.isNullOrWhitespace(var4)) {
            var4 = "basicEffect";
         }

    std::string var5 = "shader=" + var4.toLowerCase().trim();
         if (!StringUtils.isNullOrWhitespace(var2)) {
            var5 = var5 + ";tex=" + var2.toLowerCase().trim();
         }

         if (var3) {
            var5 = var5 + ";isStatic=true";
         }

    std::string var6 = var1.toLowerCase(Locale.ENGLISH).trim();
         return var6 + "&" + var5;
      }
   }

    AnimationAsset loadAnim(const std::string& var1, ModelMesh var2, ModAnimations var3) {
      DebugLog.Animation.debugln("Adding asset to queue: %s", var1);
    AnimationAssetParams var4 = std::make_shared<AnimationAssetParams>();
      var4.animationsMesh = var2;
    AnimationAsset var5 = (AnimationAsset)AnimationAssetManager.instance.load(std::make_shared<AssetPath>(var1), var4);
      var5.skinningData = var2.skinningData;
      this.putAnimationAsset(var1, var5, var3);
    return var5;
   }

    void putAnimationAsset(const std::string& var1, AnimationAsset var2, ModAnimations var3) {
    std::string var4 = var1.toLowerCase();
    AnimationAsset var5 = (AnimationAsset)var3.m_animationAssetMap.getOrDefault(var4, nullptr);
      if (var5 != nullptr) {
         DebugLog.Animation.debugln("Overwriting asset: %s", this.animAssetToString(var5));
         DebugLog.Animation.debugln("New asset        : %s", this.animAssetToString(var2));
         var3.m_animationAssetList.remove(var5);
      }

      var2.modelManagerKey = var4;
      var2.modAnimations = var3;
      var3.m_animationAssetMap.put(var4, var2);
      var3.m_animationAssetList.push_back(var2);
   }

    std::string animAssetToString(AnimationAsset var1) {
      if (var1 == nullptr) {
         return "nullptr";
      } else {
    AssetPath var2 = var1.getPath();
    return var2 = = nullptr ? "nullptr-path" : std::string.valueOf(var2.getPath());
      }
   }

    AnimationAsset getAnimationAsset(const std::string& var1) {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
      return this.m_animationAssets.get(var2);
   }

    AnimationAsset getAnimationAssetRequired(const std::string& var1) {
    AnimationAsset var2 = this.getAnimationAsset(var1);
      if (var2 == nullptr) {
         throw NullPointerException("Required Animation Asset not found: " + var1);
      } else {
    return var2;
      }
   }

    void addAnimationClip(const std::string& var1, AnimationClip var2) {
      this.m_animModel.skinningData.AnimationClips.put(var1, var2);
   }

    AnimationClip getAnimationClip(const std::string& var1) {
      return (AnimationClip)this.m_animModel.skinningData.AnimationClips.get(var1);
   }

   public Collection<AnimationClip> getAllAnimationClips() {
      return this.m_animModel.skinningData.AnimationClips.values();
   }

    ModelInstance newInstance(Model var1, IsoGameCharacter var2, AnimationPlayer var3) {
      if (var1 == nullptr) {
         System.err.println("ModelManager.newInstance> Model is nullptr.");
    return nullptr;
      } else {
    ModelInstance var4 = (ModelInstance)this.m_modelInstancePool.alloc();
         var4.init(var1, var2, var3);
    return var4;
      }
   }

    bool isLoadingAnimations() {
      for (AnimationAsset var2 : this.m_animationAssets.values()) {
         if (var2.empty()) {
    return true;
         }
      }

    return false;
   }

    void reloadModelsMatching(const std::string& var1) {
      var1 = var1.toLowerCase(Locale.ENGLISH);

      for (std::string var4 : this.m_modelMap.keySet()) {
         if (var4.contains(var1)) {
    Model var5 = this.m_modelMap.get(var4);
            if (!var5.empty()) {
               DebugLog.General.printf("reloading model %s\n", new Object[]{var4});
    MeshAssetParams var6 = std::make_shared<MeshAssetParams>();
               var6.animationsMesh = nullptr;
               if (var5.Mesh.vb == nullptr) {
                  var6.bStatic = var4.contains(";isStatic=true");
               } else {
                  var6.bStatic = var5.Mesh.vb.bStatic;
               }

               MeshAssetManager.instance.reload(var5.Mesh, var6);
            }
         }
      }
   }

    void loadModAnimations() {
      for (ModAnimations var2 : this.m_modAnimations.values()) {
         var2.setPriority(var2 == this.m_gameAnimations ? 0 : -1);
      }

    std::vector var12 = ScriptManager.instance.getAllAnimationsMeshes();
    std::vector var13 = ZomboidFileSystem.instance.getModIDs();

      for (int var3 = 0; var3 < var13.size(); var3++) {
    std::string var4 = (std::string)var13.get(var3);
    Mod var5 = ChooseGameInfo.getAvailableModDetails(var4);
         if (var5 != nullptr && var5.animsXFile.isDirectory()) {
    ModAnimations var6 = this.m_modAnimations.get(var4);
            if (var6 != nullptr) {
               var6.setPriority(var3 + 1);
            } else {
               var6 = std::make_shared<ModAnimations>(var4);
               var6.setPriority(var3 + 1);
               this.m_modAnimations.put(var4, var6);

    for (auto& var8 : var12)                  for (std::string var10 : var8.animationDirectories) {
                     if (var8.modelMesh.isReady()) {
    File var11 = std::make_shared<File>(var5.animsXFile, var10);
                        if (var11.exists()) {
                           this.loadAnimsFromDir(var5.baseFile.toURI(), var5.mediaFile.toURI(), var11, var8.modelMesh, var6);
                        }
                     }
                  }
               }

               this.loadHumanAnimations(var5, var6);
            }
         }
      }

      this.setActiveAnimations();
   }

    void setActiveAnimations() {
      this.m_animationAssets.clear();

      for (AnimationsMesh var3 : ScriptManager.instance.getAllAnimationsMeshes()) {
         if (var3.modelMesh.isReady()) {
            var3.modelMesh.skinningData.AnimationClips.clear();
         }
      }

      for (ModAnimations var8 : this.m_modAnimations.values()) {
         if (var8.isActive()) {
            for (AnimationAsset var5 : var8.m_animationAssetList) {
    AnimationAsset var6 = this.m_animationAssets.get(var5.modelManagerKey);
               if (var6 == nullptr || var6 == var5 || var6.modAnimations.m_priority <= var8.m_priority) {
                  this.m_animationAssets.put(var5.modelManagerKey, var5);
                  if (var5.isReady()) {
                     var5.skinningData.AnimationClips.putAll(var5.AnimationClips);
                  }
               }
            }
         }
      }
   }

    void animationAssetLoaded(AnimationAsset var1) {
      if (var1.modAnimations.isActive()) {
    AnimationAsset var2 = this.m_animationAssets.get(var1.modelManagerKey);
         if (var2 == nullptr || var2 == var1 || var2.modAnimations.m_priority <= var1.modAnimations.m_priority) {
            this.m_animationAssets.put(var1.modelManagerKey, var1);
            var1.skinningData.AnimationClips.putAll(var1.AnimationClips);
         }
      }
   }

    void initAnimationMeshes(bool var1) {
    std::vector var2 = ScriptManager.instance.getAllAnimationsMeshes();

    for (auto& var4 : var2)    MeshAssetParams var5 = std::make_shared<MeshAssetParams>();
         var5.bStatic = false;
         var5.animationsMesh = nullptr;
         var4.modelMesh = (ModelMesh)MeshAssetManager.instance.getAssetTable().get(var4.meshFile);
         if (var4.modelMesh == nullptr) {
            var4.modelMesh = (ModelMesh)MeshAssetManager.instance.load(std::make_shared<AssetPath>(var4.meshFile), var5);
         }

         var4.modelMesh.m_animationsMesh = var4.modelMesh;
      }

      if (!var1) {
         while (this.isLoadingAnimationMeshes()) {
            GameWindow.fileSystem.updateAsyncTransactions();

            try {
               Thread.sleep(10L);
            } catch (InterruptedException var8) {
            }

            if (!GameServer.bServer) {
               Core.getInstance().StartFrame();
               Core.getInstance().EndFrame();
               Core.getInstance().StartFrameUI();
               Core.getInstance().EndFrameUI();
            }
         }

    for (auto& var10 : var2)            for (std::string var6 : var10.animationDirectories) {
               if (var10.modelMesh.isReady()) {
    File var7 = std::make_shared<File>(ZomboidFileSystem.instance.base, "media/anims_X/" + var6);
                  if (var7.exists()) {
                     this.loadAnimsFromDir("media/anims_X/" + var6, var10.modelMesh);
                  }
               }
            }
         }
      }
   }

    bool isLoadingAnimationMeshes() {
      for (AnimationsMesh var3 : ScriptManager.instance.getAllAnimationsMeshes()) {
         if (!var3.modelMesh.isFailure() && !var3.modelMesh.isReady()) {
    return true;
         }
      }

    return false;
   }

    void loadHumanAnimations(Mod var1, ModAnimations var2) {
    AnimationsMesh var3 = ScriptManager.instance.getAnimationsMesh("Human");
      if (var3 != nullptr && var3.modelMesh != nullptr && var3.modelMesh.isReady()) {
         File[] var4 = var1.animsXFile.listFiles();
         if (var4 != nullptr) {
    URI var5 = var1.animsXFile.toURI();

    for (auto& var9 : var4)               if (var9.isDirectory()) {
                  if (!this.isAnimationsMeshDirectory(var9.getName())) {
                     this.loadAnimsFromDir(var1.baseFile.toURI(), var1.mediaFile.toURI(), var9, var3.modelMesh, var2);
                  }
               } else {
    std::string var10 = ZomboidFileSystem.instance.getAnimName(var5, var9);
                  this.loadAnim(var10, var3.modelMesh, var2);
               }
            }
         }
      }
   }

    bool isAnimationsMeshDirectory(const std::string& var1) {
      for (AnimationsMesh var4 : ScriptManager.instance.getAllAnimationsMeshes()) {
         if (var4.animationDirectories.contains(var1)) {
    return true;
         }
      }

    return false;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
