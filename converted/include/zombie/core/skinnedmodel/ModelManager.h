#pragma once
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
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/Util.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameWindow.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedModels.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/SoftwareSkinnedModelAnim.h"
#include "zombie/core/skinnedmodel/animation/StaticAnimation.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/AnimationAssetManager.h"
#include "zombie/core/skinnedmodel/model/MeshAssetManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureInitializer.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
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
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMYATI on 05/01/14.
 */
class ModelManager {
public:
 static bool NoOpenGL = false;
 static const ModelManager instance = new ModelManager();
 private HashMap<String, Model> m_modelMap = std::make_unique<HashMap<>>();
 Model m_maleModel;
 Model m_femaleModel;
 Model m_skeletonMaleModel;
 Model m_skeletonFemaleModel;
 TextureFBO bitmap;
 bool m_bCreated = false;
 bool bDebugEnableModels = true;
 bool bCreateSoftwareMeshes = false;
 public HashMap<String, SoftwareSkinnedModelAnim> SoftwareMeshAnims = std::make_unique<HashMap<>>();
 private ArrayList<ModelManager.ModelSlot> m_modelSlots = std::make_unique<ArrayList<>>();
 private ObjectPool<ModelInstance> m_modelInstancePool = new ObjectPool<>(ModelInstance::new);
 private ArrayList<WeaponPart> m_tempWeaponPartList = std::make_unique<ArrayList<>>();
 ModelMesh m_animModel;
 private HashMap<String, AnimationAsset> m_animationAssets = std::make_unique<HashMap<>>();
 private ModelManager.ModAnimations m_gameAnimations = new ModelManager.ModAnimations("game");
 private HashMap<String, ModelManager.ModAnimations> m_modAnimations = std::make_unique<HashMap<>>();
 private ArrayList<StaticAnimation> m_cachedAnims = std::make_unique<ArrayList<>>();
 private HashSet<IsoGameCharacter> m_contains = std::make_unique<HashSet<>>();
 private ArrayList<IsoGameCharacter.TorchInfo> m_torches = std::make_unique<ArrayList<>>();
 private Stack<IsoLightSource> m_freeLights = std::make_unique<Stack<>>();
 private ArrayList<IsoLightSource> m_torchLights = std::make_unique<ArrayList<>>();
 private ArrayList<IsoGameCharacter> ToRemove = std::make_unique<ArrayList<>>();
 private ArrayList<IsoGameCharacter> ToResetNextFrame = std::make_unique<ArrayList<>>();
 private ArrayList<IsoGameCharacter> ToResetEquippedNextFrame = std::make_unique<ArrayList<>>();
 private ArrayList<ModelManager.ModelSlot> m_resetAfterRender = std::make_unique<ArrayList<>>();
 private Stack<IsoLightSource> m_lights = std::make_unique<Stack<>>();
 private Stack<IsoLightSource> m_lightsTemp = std::make_unique<Stack<>>();
 const Vector2 m_tempVec2 = new Vector2();
 const Vector2 m_tempVec2_2 = new Vector2();
 private static TreeMap<String, ModelManager.ModelMetaData> modelMetaData = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
 static std::string basicEffect = "basicEffect";
 static std::string isStaticTrue = ";
 static std::string shaderEquals = "shader=";
 static std::string texA = ";
 static std::string amp = "&";
 static HashMap<String, String> toLower = std::make_unique<HashMap<>>();
 static HashMap<String, String> toLowerTex = std::make_unique<HashMap<>>();
 static HashMap<String, String> toLowerKeyRoot = std::make_unique<HashMap<>>();
 static StringBuilder builder = std::make_unique<StringBuilder>();

 bool isCreated() {
 return this->m_bCreated;
 }

 void create() {
 if (!this->m_bCreated) {
 if (!GameServer.bServer || ServerGUI.isCreated()) {
 Texture texture = new Texture(1024, 1024, 16);
 PerformanceSettings.UseFBOs = false;

 try {
 this->bitmap = new TextureFBO(texture, false);
 } catch (Exception exception) {
 exception.printStackTrace();
 PerformanceSettings.UseFBOs = false;
 DebugLog.Animation.error("FBO not compatible with gfx card at this time.");
 return;
 }
 }

 DebugLog.Animation.println("Loading 3D models");
 this->initAnimationMeshes(false);
 this->m_modAnimations.put(this->m_gameAnimations.m_modID, this->m_gameAnimations);
 AnimationsMesh animationsMesh = ScriptManager.instance.getAnimationsMesh("Human");
 ModelMesh modelMesh = animationsMesh.modelMesh;
 if (!NoOpenGL && this->bCreateSoftwareMeshes) {
 SoftwareSkinnedModelAnim softwareSkinnedModelAnim = new SoftwareSkinnedModelAnim(
 this->m_cachedAnims.toArray(new StaticAnimation[0]), modelMesh.softwareMesh, modelMesh.skinningData
 );
 this->SoftwareMeshAnims.put(modelMesh.getPath().getPath(), softwareSkinnedModelAnim);
 }

 Model model0 = this->loadModel("skinned/malebody", nullptr, modelMesh);
 Model model1 = this->loadModel("skinned/femalebody", nullptr, modelMesh);
 Model model2 = this->loadModel("skinned/Male_Skeleton", nullptr, modelMesh);
 Model model3 = this->loadModel("skinned/Female_Skeleton", nullptr, modelMesh);
 this->m_animModel = modelMesh;
 this->loadModAnimations();
 model0.addDependency(this->getAnimationAssetRequired("bob/bob_idle"));
 model0.addDependency(this->getAnimationAssetRequired("bob/bob_walk"));
 model0.addDependency(this->getAnimationAssetRequired("bob/bob_run"));
 model1.addDependency(this->getAnimationAssetRequired("bob/bob_idle"));
 model1.addDependency(this->getAnimationAssetRequired("bob/bob_walk"));
 model1.addDependency(this->getAnimationAssetRequired("bob/bob_run"));
 this->m_maleModel = model0;
 this->m_femaleModel = model1;
 this->m_skeletonMaleModel = model2;
 this->m_skeletonFemaleModel = model3;
 this->m_bCreated = true;
 AdvancedAnimator.systemInit();
 PopTemplateManager.instance.init();
 }
 }

 void loadAdditionalModel(const std::string& meshName, const std::string& tex, bool bStatic, const std::string& shaderName) {
 bool boolean0 = this->bCreateSoftwareMeshes;
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln("createSoftwareMesh: %B, model: %s", boolean0, meshName);
 }

 Model model = this->loadModelInternal(meshName, tex, shaderName, this->m_animModel, bStatic);
 if (boolean0) {
 SoftwareSkinnedModelAnim softwareSkinnedModelAnim = new SoftwareSkinnedModelAnim(
 this->m_cachedAnims.toArray(new StaticAnimation[0]), model.softwareMesh, (SkinningData)model.Tag
 );
 this->SoftwareMeshAnims.put(meshName.toLowerCase(), softwareSkinnedModelAnim);
 }
 }

 ModelInstance newAdditionalModelInstance(const std::string& meshName, const std::string& tex, IsoGameCharacter chr, AnimationPlayer animPlayer, const std::string& shaderName) {
 Model model = this->tryGetLoadedModel(meshName, tex, false, shaderName, false);
 if (model.empty()) {
 bool boolean0 = false;
 instance.loadAdditionalModel(meshName, tex, boolean0, shaderName);
 }

 model = this->getLoadedModel(meshName, tex, false, shaderName);
 return this->newInstance(model, chr, animPlayer);
 }

 void loadAnimsFromDir(const std::string& string, ModelMesh modelMesh) {
 File file = new File(ZomboidFileSystem.instance.base, string);
 this->loadAnimsFromDir(ZomboidFileSystem.instance.baseURI, ZomboidFileSystem.instance.getMediaRootFile().toURI(), file, modelMesh, this->m_gameAnimations);
 }

 void loadAnimsFromDir(URI uri0, URI uri1, File file0, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 if (!file0.exists()) {
 DebugLog.General.error("ERROR: %s", file0.getPath());

 for (File file1 = file0.getParentFile(); file1 != nullptr; file1 = file1.getParentFile()) {
 DebugLog.General.error(" - Parent exists: %B, %s", file1.exists(), file1.getPath());
 }
 }

 if (file0.isDirectory()) {
 File[] files = file0.listFiles();
 if (files != nullptr) {
 bool boolean0 = false;

 for (auto& file2 : files) if (file2.isDirectory()) {
 this->loadAnimsFromDir(uri0, uri1, file2, modelMesh, modAnimations);
 } else {
 std::string string = ZomboidFileSystem.instance.getAnimName(uri1, file2);
 this->loadAnim(string, modelMesh, modAnimations);
 boolean0 = true;
 if (!NoOpenGL && RenderThread.RenderThread.empty()) {
 Display.processMessages();
 }
 }
 }

 if (boolean0) {
 DebugFileWatcher.instance.add(new ModelManager.AnimDirReloader(uri0, uri1, file0.getPath(), modelMesh, modAnimations).GetFileWatcher());
 }
 }
 }
 }

 void RenderSkyBox(TextureDraw texd, int shaderID, int userId, int apiId, int bufferId) {
 int int0 = TextureFBO.getCurrentID();
 switch (apiId) {
 case 1:
 GL30.glBindFramebuffer(36160, bufferId);
 break;
 case 2:
 ARBFramebufferObject.glBindFramebuffer(36160, bufferId);
 break;
 case 3:
 EXTFramebufferObject.glBindFramebufferEXT(36160, bufferId);
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
 ARBShaderObjects.glUseProgramObjectARB(shaderID);
 if (Shader.ShaderMap.containsKey(shaderID) {
 Shader.ShaderMap.get(shaderID).startRenderThread(texd);
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
 PlayerCamera playerCamera = SpriteRenderer.instance.getRenderingPlayerCamera(userId);
 GL11.glViewport(0, 0, playerCamera.OffscreenWidth, playerCamera.OffscreenHeight);
 switch (apiId) {
 case 1:
 GL30.glBindFramebuffer(36160, int0);
 break;
 case 2:
 ARBFramebufferObject.glBindFramebuffer(36160, int0);
 break;
 case 3:
 EXTFramebufferObject.glBindFramebufferEXT(36160, int0);
 }

 SkyBox.getInstance().swapTextureFBO();
 }

 void RenderWater(TextureDraw texd, int shaderID, int userId, bool bShore) {
 try {
 Util.checkGLError();
 } catch (Throwable throwable) {
 }

 GL11.glPushClientAttrib(-1);
 GL11.glPushAttrib(1048575);
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 IsoWater.getInstance().waterProjection();
 PlayerCamera playerCamera = SpriteRenderer.instance.getRenderingPlayerCamera(userId);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 ARBShaderObjects.glUseProgramObjectARB(shaderID);
 Shader shader = Shader.ShaderMap.get(shaderID);
 if (shader instanceof WaterShader) {
 ((WaterShader)shader).updateWaterParams(texd, userId);
 }

 IsoWater.getInstance().waterGeometry(bShore);
 ARBShaderObjects.glUseProgramObjectARB(0);
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glPopAttrib();
 GL11.glPopClientAttrib();
 Texture.lastTextureID = -1;
 if (!PZGLUtil.checkGLError(true) {
 DebugLog.General.println("DEBUG: EXCEPTION RenderWater");
 PZGLUtil.printGLState(DebugLog.General);
 }
 }

 void RenderPuddles(int shaderID, int userId, int z) {
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
 ARBShaderObjects.glUseProgramObjectARB(shaderID);
 Shader shader = Shader.ShaderMap.get(shaderID);
 if (shader instanceof PuddlesShader) {
 ((PuddlesShader)shader).updatePuddlesParams(userId, z);
 }

 IsoPuddles.getInstance().puddlesGeometry(z);
 ARBShaderObjects.glUseProgramObjectARB(0);
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glPopAttrib();
 GL11.glPopClientAttrib();
 Texture.lastTextureID = -1;
 if (!PZGLUtil.checkGLError(true) {
 DebugLog.General.println("DEBUG: EXCEPTION RenderPuddles");
 PZGLUtil.printGLState(DebugLog.General);
 }
 }

 void RenderParticles(TextureDraw texd, int userId, int va11) {
 int int0 = ParticlesFire.getInstance().getFireShaderID();
 int int1 = ParticlesFire.getInstance().getSmokeShaderID();
 int int2 = ParticlesFire.getInstance().getVapeShaderID();

 try {
 Util.checkGLError();
 } catch (Throwable throwable) {
 }

 GL11.glPushClientAttrib(-1);
 GL11.glPushAttrib(1048575);
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 GL11.glViewport(
 0,
 0,
 SpriteRenderer.instance.getRenderingPlayerCamera(userId).OffscreenWidth,
 SpriteRenderer.instance.getRenderingPlayerCamera(userId).OffscreenHeight
 );
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 float float0 = ParticlesFire.getInstance().getShaderTime();
 GL11.glBlendFunc(770, 1);
 ARBShaderObjects.glUseProgramObjectARB(int0);
 Shader shader = Shader.ShaderMap.get(int0);
 if (shader instanceof FireShader) {
 ((FireShader)shader).updateFireParams(texd, userId, float0);
 }

 ParticlesFire.getInstance().getGeometryFire(va11);
 GL11.glBlendFunc(770, 771);
 ARBShaderObjects.glUseProgramObjectARB(int1);
 shader = Shader.ShaderMap.get(int1);
 if (shader instanceof SmokeShader) {
 ((SmokeShader)shader).updateSmokeParams(texd, userId, float0);
 }

 ParticlesFire.getInstance().getGeometry(va11);
 ARBShaderObjects.glUseProgramObjectARB(0);
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glPopAttrib();
 GL11.glPopClientAttrib();
 Texture.lastTextureID = -1;
 GL11.glViewport(
 0,
 0,
 SpriteRenderer.instance.getRenderingPlayerCamera(userId).OffscreenWidth,
 SpriteRenderer.instance.getRenderingPlayerCamera(userId).OffscreenHeight
 );
 if (!PZGLUtil.checkGLError(true) {
 DebugLog.General.println("DEBUG: EXCEPTION RenderParticles");
 PZGLUtil.printGLState(DebugLog.General);
 }
 }

 /**
 * Reset Resets the specified character.
 * 
 * @param chr the character to reset
 */
 void Reset(IsoGameCharacter chr) {
 if (chr.legsSprite != nullptr && chr.legsSprite.modelSlot != nullptr) {
 ModelManager.ModelSlot modelSlot = chr.legsSprite.modelSlot;
 this->resetModelInstance(modelSlot.model, modelSlot);

 for (int int0 = 0; int0 < modelSlot.sub.size(); int0++) {
 ModelInstance modelInstance = modelSlot.sub.get(int0);
 if (modelInstance != chr.primaryHandModel && modelInstance != chr.secondaryHandModel && !modelSlot.attachedModels.contains(modelInstance) {
 this->resetModelInstanceRecurse(modelInstance, modelSlot);
 }
 }

 this->derefModelInstances(chr.getReadyModelData());
 chr.getReadyModelData().clear();
 this->dressInRandomOutfit(chr);
 Model model = this->getBodyModel(chr);
 modelSlot.model = this->newInstance(model, chr, chr.getAnimationPlayer());
 modelSlot.model.setOwner(modelSlot);
 modelSlot.model.m_modelScript = ScriptManager.instance.getModelScript(chr.isFemale() ? "FemaleBody" : "MaleBody");
 this->DoCharacterModelParts(chr, modelSlot);
 }
 }

 void reloadAllOutfits() {
 for (IsoGameCharacter character : this->m_contains) {
 character.reloadOutfit();
 }
 }

 /**
 * Add the supplied character to the visible render list.
 */
 void Add(IsoGameCharacter chr) {
 if (this->m_bCreated) {
 if (chr.isSceneCulled()) {
 if (this->ToRemove.contains(chr) {
 this->ToRemove.remove(chr);
 chr.legsSprite.modelSlot.bRemove = false;
 } else {
 ModelManager.ModelSlot modelSlot = this->getSlot(chr);
 modelSlot.framesSinceStart = 0;
 if (modelSlot.model != nullptr) {
 RenderThread.invokeOnRenderContext(modelSlot.model::destroySmartTextures);
 }

 this->dressInRandomOutfit(chr);
 Model model = this->getBodyModel(chr);
 modelSlot.model = this->newInstance(model, chr, chr.getAnimationPlayer());
 modelSlot.model.setOwner(modelSlot);
 modelSlot.model.m_modelScript = ScriptManager.instance.getModelScript(chr.isFemale() ? "FemaleBody" : "MaleBody");
 this->DoCharacterModelParts(chr, modelSlot);
 modelSlot.active = true;
 modelSlot.character = chr;
 modelSlot.model.character = chr;
 modelSlot.model.object = chr;
 modelSlot.model.SetForceDir(modelSlot.model.character.getForwardDirection());

 for (int int0 = 0; int0 < modelSlot.sub.size(); int0++) {
 ModelInstance modelInstance = modelSlot.sub.get(int0);
 modelInstance.character = chr;
 modelInstance.object = chr;
 }

 chr.legsSprite.modelSlot = modelSlot;
 this->m_contains.add(chr);
 chr.onCullStateChanged(this, false);
 if (modelSlot.model.AnimPlayer != nullptr && modelSlot.model.AnimPlayer.isBoneTransformsNeedFirstFrame()) {
 try {
 modelSlot.Update();
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }
 }
 }

 void dressInRandomOutfit(IsoGameCharacter chr) {
 IsoZombie zombie0 = Type.tryCastTo(chr, IsoZombie.class);
 if (zombie0 != nullptr && !zombie0.isReanimatedPlayer() && !zombie0.wasFakeDead()) {
 if (DebugOptions.instance.ZombieOutfitRandom.getValue() && !chr.isPersistentOutfitInit()) {
 zombie0.bDressInRandomOutfit = true;
 }

 if (zombie0.bDressInRandomOutfit) {
 zombie0.bDressInRandomOutfit = false;
 zombie0.dressInRandomOutfit();
 }

 if (!chr.isPersistentOutfitInit()) {
 zombie0.dressInPersistentOutfitID(chr.getPersistentOutfitID());
 }
 } else {
 if (GameClient.bClient && zombie0 != nullptr && !chr.isPersistentOutfitInit() && chr.getPersistentOutfitID() != 0) {
 zombie0.dressInPersistentOutfitID(chr.getPersistentOutfitID());
 }
 }
 }

 Model getBodyModel(IsoGameCharacter chr) {
 if (chr.isZombie() && ((IsoZombie)chr).isSkeleton()) {
 return chr.isFemale() ? this->m_skeletonFemaleModel : this->m_skeletonMaleModel;
 } else {
 return chr.isFemale() ? this->m_femaleModel : this->m_maleModel;
 }
 }

 /**
 * Returns TRUE if the character is currently in the visible render list, and has not been flagged for removal.
 */
 bool ContainsChar(IsoGameCharacter chr) {
 return this->m_contains.contains(chr) && !this->ToRemove.contains(chr);
 }

 void ResetCharacterEquippedHands(IsoGameCharacter chr) {
 if (chr != nullptr && chr.legsSprite != nullptr && chr.legsSprite.modelSlot != nullptr) {
 this->DoCharacterModelEquipped(chr, chr.legsSprite.modelSlot);
 }
 }

 void DoCharacterModelEquipped(IsoGameCharacter character, ModelManager.ModelSlot modelSlot) {
 if (character.primaryHandModel != nullptr) {
 character.clearVariable("RightHandMask");
 character.primaryHandModel.maskVariableValue = nullptr;
 this->resetModelInstanceRecurse(character.primaryHandModel, modelSlot);
 modelSlot.sub.remove(character.primaryHandModel);
 modelSlot.model.sub.remove(character.primaryHandModel);
 character.primaryHandModel = nullptr;
 }

 if (character.secondaryHandModel != nullptr) {
 character.clearVariable("LeftHandMask");
 character.secondaryHandModel.maskVariableValue = nullptr;
 this->resetModelInstanceRecurse(character.secondaryHandModel, modelSlot);
 modelSlot.sub.remove(character.secondaryHandModel);
 modelSlot.model.sub.remove(character.secondaryHandModel);
 character.secondaryHandModel = nullptr;
 }

 for (int int0 = 0; int0 < modelSlot.attachedModels.size(); int0++) {
 ModelInstance modelInstance0 = modelSlot.attachedModels.get(int0);
 this->resetModelInstanceRecurse(modelInstance0, modelSlot);
 modelSlot.sub.remove(modelInstance0);
 modelSlot.model.sub.remove(modelInstance0);
 }

 modelSlot.attachedModels.clear();

 for (int int1 = 0; int1 < character.getAttachedItems().size(); int1++) {
 AttachedItem attachedItem = character.getAttachedItems().get(int1);
 std::string string0 = attachedItem.getItem().getStaticModel();
 if (!StringUtils.isNullOrWhitespace(string0) {
 std::string string1 = character.getAttachedItems().getGroup().getLocation(attachedItem.getLocation()).getAttachmentName();
 ModelInstance modelInstance1 = this->addStatic(modelSlot.model, string0, string1, string1);
 if (modelInstance1 != nullptr) {
 modelInstance1.setOwner(modelSlot);
 modelSlot.sub.add(modelInstance1);
 HandWeapon weapon = Type.tryCastTo(attachedItem.getItem(), HandWeapon.class);
 if (weapon != nullptr) {
 this->addWeaponPartModels(modelSlot, weapon, modelInstance1);
 if (!Core.getInstance().getOptionSimpleWeaponTextures()) {
 ModelInstanceTextureInitializer modelInstanceTextureInitializer = ModelInstanceTextureInitializer.alloc();
 modelInstanceTextureInitializer.init(modelInstance1, weapon);
 modelInstance1.setTextureInitializer(modelInstanceTextureInitializer);
 }
 }

 modelSlot.attachedModels.add(modelInstance1);
 }
 }
 }

 if (character instanceof IsoZombie) {
 }

 InventoryItem item0 = character.getPrimaryHandItem();
 InventoryItem item1 = character.getSecondaryHandItem();
 if (character.isHideWeaponModel()) {
 item0 = nullptr;
 item1 = nullptr;
 }

 if (character instanceof IsoPlayer && character.forceNullOverride) {
 item0 = nullptr;
 item1 = nullptr;
 character.forceNullOverride = false;
 }

 bool boolean0 = false;
 BaseAction baseAction = character.getCharacterActions().empty() ? nullptr : character.getCharacterActions().get(0);
 if (baseAction != nullptr && baseAction.overrideHandModels) {
 boolean0 = true;
 item0 = nullptr;
 if (baseAction.getPrimaryHandItem() != nullptr) {
 item0 = baseAction.getPrimaryHandItem();
 } else if (baseAction.getPrimaryHandMdl() != nullptr) {
 character.primaryHandModel = this->addStatic(modelSlot, baseAction.getPrimaryHandMdl(), "Bip01_Prop1");
 }

 item1 = nullptr;
 if (baseAction.getSecondaryHandItem() != nullptr) {
 item1 = baseAction.getSecondaryHandItem();
 } else if (baseAction.getSecondaryHandMdl() != nullptr) {
 character.secondaryHandModel = this->addStatic(modelSlot, baseAction.getSecondaryHandMdl(), "Bip01_Prop2");
 }
 }

 if (!StringUtils.isNullOrEmpty(character.overridePrimaryHandModel) {
 boolean0 = true;
 character.primaryHandModel = this->addStatic(modelSlot, character.overridePrimaryHandModel, "Bip01_Prop1");
 }

 if (!StringUtils.isNullOrEmpty(character.overrideSecondaryHandModel) {
 boolean0 = true;
 character.secondaryHandModel = this->addStatic(modelSlot, character.overrideSecondaryHandModel, "Bip01_Prop2");
 }

 if (item0 != nullptr) {
 ItemReplacement itemReplacement0 = item0.getItemReplacementPrimaryHand();
 character.primaryHandModel = this->addEquippedModelInstance(character, modelSlot, item0, "Bip01_Prop1", itemReplacement0, boolean0);
 }

 if (item1 != nullptr && item0 != item1) {
 ItemReplacement itemReplacement1 = item1.getItemReplacementSecondHand();
 character.secondaryHandModel = this->addEquippedModelInstance(character, modelSlot, item1, "Bip01_Prop2", itemReplacement1, boolean0);
 }
 }

 private ModelInstance addEquippedModelInstance(
 IsoGameCharacter character, ModelManager.ModelSlot modelSlot, InventoryItem item, String string1, ItemReplacement itemReplacement, boolean boolean0
 ) {
 HandWeapon weapon = Type.tryCastTo(item, HandWeapon.class);
 if (weapon != nullptr) {
 std::string string0 = weapon.getStaticModel();
 ModelInstance modelInstance = this->addStatic(modelSlot, string0, string1);
 this->addWeaponPartModels(modelSlot, weapon, modelInstance);
 if (Core.getInstance().getOptionSimpleWeaponTextures()) {
 return modelInstance;
 } else {
 ModelInstanceTextureInitializer modelInstanceTextureInitializer = ModelInstanceTextureInitializer.alloc();
 modelInstanceTextureInitializer.init(modelInstance, weapon);
 modelInstance.setTextureInitializer(modelInstanceTextureInitializer);
 return modelInstance;
 }
 } else {
 if (item != nullptr) {
 if (itemReplacement != nullptr
 && !StringUtils.isNullOrEmpty(itemReplacement.maskVariableValue)
 && (itemReplacement.clothingItem != nullptr || !StringUtils.isNullOrWhitespace(item.getStaticModel()))) {
 return this->addMaskingModel(
 modelSlot, character, item, itemReplacement, itemReplacement.maskVariableValue, itemReplacement.attachment, string1
 );
 }

 if (boolean0 && !StringUtils.isNullOrWhitespace(item.getStaticModel())) {
 return this->addStatic(modelSlot, item.getStaticModel(), string1);
 }
 }

 return nullptr;
 }
 }

 private ModelInstance addMaskingModel(
 ModelManager.ModelSlot modelSlot,
 IsoGameCharacter character,
 InventoryItem item,
 ItemReplacement itemReplacement,
 String string3,
 String string1,
 String string2
 ) {
 ModelInstance modelInstance = nullptr;
 ItemVisual itemVisual = item.getVisual();
 if (itemReplacement.clothingItem != nullptr && itemVisual != nullptr) {
 modelInstance = PopTemplateManager.instance.addClothingItem(character, modelSlot, itemVisual, itemReplacement.clothingItem);
 } else {
 if (StringUtils.isNullOrWhitespace(item.getStaticModel())) {
 return nullptr;
 }

 std::string string0 = nullptr;
 if (itemVisual != nullptr && item.getClothingItem() != nullptr) {
 string0 = item.getClothingItem().getTextureChoices().get(itemVisual.getTextureChoice());
 }

 if (!StringUtils.isNullOrEmpty(string1) {
 modelInstance = this->addStaticForcedTex(modelSlot.model, item.getStaticModel(), string1, string1, string0);
 } else {
 modelInstance = this->addStaticForcedTex(modelSlot, item.getStaticModel(), string2, string0);
 }

 modelInstance.maskVariableValue = string3;
 if (itemVisual != nullptr) {
 modelInstance.tintR = itemVisual.m_Tint.r;
 modelInstance.tintG = itemVisual.m_Tint.g;
 modelInstance.tintB = itemVisual.m_Tint.b;
 }
 }

 if (!StringUtils.isNullOrEmpty(string3) {
 character.setVariable(itemReplacement.maskVariableName, string3);
 character.bUpdateEquippedTextures = true;
 }

 return modelInstance;
 }

 void addWeaponPartModels(ModelManager.ModelSlot modelSlot, HandWeapon weapon, ModelInstance modelInstance1) {
 std::vector arrayList0 = weapon.getModelWeaponPart();
 if (arrayList0 != nullptr) {
 std::vector arrayList1 = weapon.getAllWeaponParts(this->m_tempWeaponPartList);

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 WeaponPart weaponPart = (WeaponPart)arrayList1.get(int0);

 for (int int1 = 0; int1 < arrayList0.size(); int1++) {
 ModelWeaponPart modelWeaponPart = (ModelWeaponPart)arrayList0.get(int1);
 if (weaponPart.getFullType() == modelWeaponPart.partType) {
 ModelInstance modelInstance0 = this->addStatic(
 modelInstance1, modelWeaponPart.modelName, modelWeaponPart.attachmentNameSelf, modelWeaponPart.attachmentParent
 );
 modelInstance0.setOwner(modelSlot);
 }
 }
 }
 }
 }

 void resetModelInstance(ModelInstance modelInstance, void* expectedOwner) {
 if (modelInstance != nullptr) {
 modelInstance.clearOwner(expectedOwner);
 if (modelInstance.isRendering()) {
 modelInstance.bResetAfterRender = true;
 } else {
 if (modelInstance instanceof VehicleModelInstance) {
 return;
 }

 if (modelInstance instanceof VehicleSubModelInstance) {
 return;
 }

 modelInstance.reset();
 this->m_modelInstancePool.release(modelInstance);
 }
 }
 }

 void resetModelInstanceRecurse(ModelInstance modelInstance, void* expectedOwner) {
 if (modelInstance != nullptr) {
 this->resetModelInstancesRecurse(modelInstance.sub, expectedOwner);
 this->resetModelInstance(modelInstance, expectedOwner);
 }
 }

 void resetModelInstancesRecurse(ArrayList<ModelInstance> modelInstances, void* expectedOwner) {
 for (int int0 = 0; int0 < modelInstances.size(); int0++) {
 ModelInstance modelInstance = (ModelInstance)modelInstances.get(int0);
 this->resetModelInstance(modelInstance, expectedOwner);
 }
 }

 void derefModelInstance(ModelInstance modelInstance) {
 if (modelInstance != nullptr) {
 assert modelInstance.renderRefCount > 0;

 modelInstance.renderRefCount--;
 if (modelInstance.bResetAfterRender && !modelInstance.isRendering()) {
 assert modelInstance.getOwner() == nullptr;

 if (modelInstance instanceof VehicleModelInstance) {
 return;
 }

 if (modelInstance instanceof VehicleSubModelInstance) {
 return;
 }

 modelInstance.reset();
 this->m_modelInstancePool.release(modelInstance);
 }
 }
 }

 void derefModelInstances(ArrayList<ModelInstance> modelInstances) {
 for (int int0 = 0; int0 < modelInstances.size(); int0++) {
 ModelInstance modelInstance = (ModelInstance)modelInstances.get(int0);
 this->derefModelInstance(modelInstance);
 }
 }

 void DoCharacterModelParts(IsoGameCharacter character, ModelManager.ModelSlot modelSlot) {
 if (modelSlot.isRendering()) {
 bool boolean0 = false;
 }

 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.debugln("Char: " + character + " Slot: " + modelSlot);
 }

 modelSlot.sub.clear();
 PopTemplateManager.instance.populateCharacterModelSlot(character, modelSlot);
 this->DoCharacterModelEquipped(character, modelSlot);
 }

 void update() {
 for (int int0 = 0; int0 < this->ToResetNextFrame.size(); int0++) {
 IsoGameCharacter character0 = this->ToResetNextFrame.get(int0);
 this->Reset(character0);
 }

 this->ToResetNextFrame.clear();

 for (int int1 = 0; int1 < this->ToResetEquippedNextFrame.size(); int1++) {
 IsoGameCharacter character1 = this->ToResetEquippedNextFrame.get(int1);
 this->ResetCharacterEquippedHands(character1);
 }

 this->ToResetEquippedNextFrame.clear();

 for (int int2 = 0; int2 < this->ToRemove.size(); int2++) {
 IsoGameCharacter character2 = this->ToRemove.get(int2);
 this->DoRemove(character2);
 }

 this->ToRemove.clear();

 for (int int3 = 0; int3 < this->m_resetAfterRender.size(); int3++) {
 ModelManager.ModelSlot modelSlot = this->m_resetAfterRender.get(int3);
 if (!modelSlot.isRendering()) {
 modelSlot.reset();
 this->m_resetAfterRender.remove(int3--);
 }
 }

 this->m_lights.clear();
 if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
 this->m_lights.addAll(IsoWorld.instance.CurrentCell.getLamppostPositions());
 std::vector arrayList = IsoWorld.instance.CurrentCell.getVehicles();

 for (int int4 = 0; int4 < arrayList.size(); int4++) {
 BaseVehicle vehicle = (BaseVehicle)arrayList.get(int4);
 if (vehicle.sprite != nullptr && vehicle.sprite.hasActiveModel()) {
 ((VehicleModelInstance)vehicle.sprite.modelSlot.model).UpdateLights();
 }
 }
 }

 this->m_freeLights.addAll(this->m_torchLights);
 this->m_torchLights.clear();
 this->m_torches.clear();
 LightingJNI.getTorches(this->m_torches);

 for (int int5 = 0; int5 < this->m_torches.size(); int5++) {
 IsoGameCharacter.TorchInfo torchInfo = this->m_torches.get(int5);
 IsoLightSource lightSource = this->m_freeLights.empty() ? new IsoLightSource(0, 0, 0, 1.0F, 1.0F, 1.0F, 1) : this->m_freeLights.pop();
 lightSource.x = (int)torchInfo.x;
 lightSource.y = (int)torchInfo.y;
 lightSource.z = (int)torchInfo.z;
 lightSource.r = 1.0F;
 lightSource.g = 0.85F;
 lightSource.b = 0.6F;
 lightSource.radius = (int)Math.ceil(torchInfo.dist);
 this->m_torchLights.add(lightSource);
 }
 }

 private ModelManager.ModelSlot addNewSlot(IsoGameCharacter character) {
 ModelManager.ModelSlot modelSlot = new ModelManager.ModelSlot(this->m_modelSlots.size(), nullptr, character);
 this->m_modelSlots.add(modelSlot);
 return modelSlot;
 }

 public ModelManager.ModelSlot getSlot(IsoGameCharacter chr) {
 for (int int0 = 0; int0 < this->m_modelSlots.size(); int0++) {
 ModelManager.ModelSlot modelSlot = this->m_modelSlots.get(int0);
 if (!modelSlot.bRemove && !modelSlot.isRendering() && !modelSlot.active) {
 return modelSlot;
 }
 }

 return this->addNewSlot(chr);
 }

 bool DoRemove(IsoGameCharacter character) {
 if (!this->m_contains.contains(character) {
 return false;
 } else {
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->m_modelSlots.size(); int0++) {
 ModelManager.ModelSlot modelSlot = this->m_modelSlots.get(int0);
 if (modelSlot.character == character) {
 character.legsSprite.modelSlot = nullptr;
 this->m_contains.remove(character);
 if (!character.isSceneCulled()) {
 character.onCullStateChanged(this, true);
 }

 if (!this->m_resetAfterRender.contains(modelSlot) {
 this->m_resetAfterRender.add(modelSlot);
 }

 boolean0 = true;
 }
 }

 return boolean0;
 }
 }

 void Remove(IsoGameCharacter chr) {
 if (!chr.isSceneCulled()) {
 if (!this->ToRemove.contains(chr) {
 chr.legsSprite.modelSlot.bRemove = true;
 this->ToRemove.add(chr);
 chr.onCullStateChanged(this, true);
 } else if (this->ContainsChar(chr) {
 throw IllegalStateException("IsoGameCharacter.isSceneCulled() = true inconsistent with ModelManager.ContainsChar() = true");
 }
 }
 }

 void Remove(BaseVehicle vehicle) {
 if (vehicle.sprite != nullptr && vehicle.sprite.modelSlot != nullptr) {
 ModelManager.ModelSlot modelSlot = vehicle.sprite.modelSlot;
 if (!this->m_resetAfterRender.contains(modelSlot) {
 this->m_resetAfterRender.add(modelSlot);
 }

 vehicle.sprite.modelSlot = nullptr;
 }
 }

 void ResetNextFrame(IsoGameCharacter isoGameCharacter) {
 if (!this->ToResetNextFrame.contains(isoGameCharacter) {
 this->ToResetNextFrame.add(isoGameCharacter);
 }
 }

 void ResetEquippedNextFrame(IsoGameCharacter isoGameCharacter) {
 if (!this->ToResetEquippedNextFrame.contains(isoGameCharacter) {
 this->ToResetEquippedNextFrame.add(isoGameCharacter);
 }
 }

 void Reset() {
 RenderThread.invokeOnRenderContext(() -> {
 for (IsoGameCharacter character0 : this->ToRemove) {
 this->DoRemove(character0);
 }

 this->ToRemove.clear();

 try {
 if (!this->m_contains.empty()) {
 IsoGameCharacter[] characters = this->m_contains.toArray(new IsoGameCharacter[0]);

 for (auto& character1 : characters) this->DoRemove(character1);
 }
 }

 this->m_modelSlots.clear();
 } catch (Exception exception) {
 DebugLog.Animation.error("Exception thrown removing Models.");
 exception.printStackTrace();
 }
 });
 this->m_lights.clear();
 this->m_lightsTemp.clear();
 }

 void getClosestThreeLights(IsoMovingObject movingObject, IsoLightSource[] lightSources) {
 this->m_lightsTemp.clear();

 for (IsoLightSource lightSource : this->m_lights) {
 if (lightSource.bActive
 && lightSource.life != 0
 && (lightSource.localToBuilding.empty() || movingObject.getCurrentBuilding() == lightSource.localToBuilding)
 && !(IsoUtils.DistanceTo(movingObject.x, movingObject.y, lightSource.x + 0.5F, lightSource.y + 0.5F) >= lightSource.radius)
 && LosUtil.lineClear(
 IsoWorld.instance.CurrentCell,
 (int)movingObject.x,
 (int)movingObject.y,
 (int)movingObject.z,
 lightSource.x,
 lightSource.y,
 lightSource.z,
 false
 )
 != LosUtil.TestResults.Blocked) {
 this->m_lightsTemp.add(lightSource);
 }
 }

 if (movingObject instanceof BaseVehicle) {
 for (int int0 = 0; int0 < this->m_torches.size(); int0++) {
 IsoGameCharacter.TorchInfo torchInfo = this->m_torches.get(int0);
 if (!(IsoUtils.DistanceTo(movingObject.x, movingObject.y, torchInfo.x, torchInfo.y) >= torchInfo.dist)
 && LosUtil.lineClear(
 IsoWorld.instance.CurrentCell,
 (int)movingObject.x,
 (int)movingObject.y,
 (int)movingObject.z,
 (int)torchInfo.x,
 (int)torchInfo.y,
 (int)torchInfo.z,
 false
 )
 != LosUtil.TestResults.Blocked) {
 if (torchInfo.bCone) {
 Vector2 vector0 = this->m_tempVec2;
 vector0.x = torchInfo.x - movingObject.x;
 vector0.y = torchInfo.y - movingObject.y;
 vector0.normalize();
 Vector2 vector1 = this->m_tempVec2_2;
 vector1.x = torchInfo.angleX;
 vector1.y = torchInfo.angleY;
 vector1.normalize();
 float float0 = vector0.dot(vector1);
 if (float0 >= -0.92F) {
 continue;
 }
 }

 this->m_lightsTemp.add(this->m_torchLights.get(int0);
 }
 }
 }

 PZArrayUtil.sort(this->m_lightsTemp, Lambda.comparator(movingObject, (lightSource0, lightSource1, movingObjectx) -> {
 float float0x = movingObjectx.DistTo(lightSource0.x, lightSource0.y);
 float float1 = movingObjectx.DistTo(lightSource1.x, lightSource1.y);
 if (float0x > float1) {
 return 1;
 } else {
 return float0x < float1 ? -1 : 0;
 }
 }));
 lightSources[0] = lightSources[1] = lightSources[2] = nullptr;
 if (this->m_lightsTemp.size() > 0) {
 lightSources[0] = this->m_lightsTemp.get(0);
 }

 if (this->m_lightsTemp.size() > 1) {
 lightSources[1] = this->m_lightsTemp.get(1);
 }

 if (this->m_lightsTemp.size() > 2) {
 lightSources[2] = this->m_lightsTemp.get(2);
 }
 }

 void addVehicle(BaseVehicle vehicle) {
 if (this->m_bCreated) {
 if (!GameServer.bServer || ServerGUI.isCreated()) {
 if (vehicle != nullptr && vehicle.getScript() != nullptr) {
 VehicleScript vehicleScript = vehicle.getScript();
 std::string string = vehicle.getScript().getModel().file;
 Model model0 = this->getLoadedModel(string);
 if (model0.empty()) {
 DebugLog.Animation.error("Failed to find vehicle model: %s", string);
 } else {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln("%s", string);
 }

 VehicleModelInstance vehicleModelInstance = new VehicleModelInstance();
 vehicleModelInstance.init(model0, nullptr, vehicle.getAnimationPlayer());
 vehicleModelInstance.applyModelScriptScale(string);
 vehicle.getSkin();
 VehicleScript.Skin skin = vehicleScript.getTextures();
 if (vehicle.getSkinIndex() >= 0 && vehicle.getSkinIndex() < vehicleScript.getSkinCount()) {
 skin = vehicleScript.getSkin(vehicle.getSkinIndex());
 }

 vehicleModelInstance.LoadTexture(skin.texture);
 vehicleModelInstance.tex = skin.textureData;
 vehicleModelInstance.textureMask = skin.textureDataMask;
 vehicleModelInstance.textureDamage1Overlay = skin.textureDataDamage1Overlay;
 vehicleModelInstance.textureDamage1Shell = skin.textureDataDamage1Shell;
 vehicleModelInstance.textureDamage2Overlay = skin.textureDataDamage2Overlay;
 vehicleModelInstance.textureDamage2Shell = skin.textureDataDamage2Shell;
 vehicleModelInstance.textureLights = skin.textureDataLights;
 vehicleModelInstance.textureRust = skin.textureDataRust;
 if (vehicleModelInstance.tex != nullptr) {
 vehicleModelInstance.tex.bindAlways = true;
 } else {
 DebugLog.Animation.error("texture not found:", vehicle.getSkin());
 }

 ModelManager.ModelSlot modelSlot = this->getSlot(nullptr);
 modelSlot.model = vehicleModelInstance;
 vehicleModelInstance.setOwner(modelSlot);
 vehicleModelInstance.object = vehicle;
 modelSlot.sub.clear();

 for (int int0 = 0; int0 < vehicle.models.size(); int0++) {
 BaseVehicle.ModelInfo modelInfo = vehicle.models.get(int0);
 Model model1 = this->getLoadedModel(modelInfo.scriptModel.file);
 if (model1.empty()) {
 DebugLog.Animation.error("vehicle.models[%d] not found: %s", int0, modelInfo.scriptModel.file);
 } else {
 VehicleSubModelInstance vehicleSubModelInstance = new VehicleSubModelInstance();
 vehicleSubModelInstance.init(model1, nullptr, modelInfo.getAnimationPlayer());
 vehicleSubModelInstance.setOwner(modelSlot);
 vehicleSubModelInstance.applyModelScriptScale(modelInfo.scriptModel.file);
 vehicleSubModelInstance.object = vehicle;
 vehicleSubModelInstance.parent = vehicleModelInstance;
 vehicleModelInstance.sub.add(vehicleSubModelInstance);
 vehicleSubModelInstance.modelInfo = modelInfo;
 if (vehicleSubModelInstance.tex.empty()) {
 vehicleSubModelInstance.tex = vehicleModelInstance.tex;
 }

 modelSlot.sub.add(vehicleSubModelInstance);
 modelInfo.modelInstance = vehicleSubModelInstance;
 }
 }

 modelSlot.active = true;
 vehicle.sprite.modelSlot = modelSlot;
 }
 }
 }
 }
 }

 ModelInstance addStatic(ModelManager.ModelSlot slot, const std::string& meshName, const std::string& texName, const std::string& boneName, const std::string& shaderName) {
 ModelInstance modelInstance = this->newStaticInstance(slot, meshName, texName, boneName, shaderName);
 if (modelInstance.empty()) {
 return nullptr;
 } else {
 slot.sub.add(modelInstance);
 modelInstance.setOwner(slot);
 slot.model.sub.add(modelInstance);
 return modelInstance;
 }
 }

 ModelInstance newStaticInstance(ModelManager.ModelSlot slot, const std::string& meshName, const std::string& texName, const std::string& boneName, const std::string& shaderName) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln("Adding Static Model:" + meshName);
 }

 Model model = this->tryGetLoadedModel(meshName, texName, true, shaderName, false);
 if (model.empty() && meshName != nullptr) {
 this->loadStaticModel(meshName, texName, shaderName);
 model = this->getLoadedModel(meshName, texName, true, shaderName);
 if (model.empty()) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.error("Model not found. model:" + meshName + " tex:" + texName);
 }

 return nullptr;
 }
 }

 if (meshName.empty()) {
 model = this->tryGetLoadedModel("vehicles_wheel02", "vehicles/vehicle_wheel02", true, "vehiclewheel", false);
 }

 ModelInstance modelInstance = this->newInstance(model, slot.character, slot.model.AnimPlayer);
 modelInstance.parent = slot.model;
 if (slot.model.AnimPlayer != nullptr) {
 modelInstance.parentBone = slot.model.AnimPlayer.getSkinningBoneIndex(boneName, modelInstance.parentBone);
 modelInstance.parentBoneName = boneName;
 }

 modelInstance.AnimPlayer = slot.model.AnimPlayer;
 return modelInstance;
 }

 ModelInstance addStatic(ModelManager.ModelSlot modelSlot, const std::string& string0, const std::string& string1) {
 return this->addStaticForcedTex(modelSlot, string0, string1, nullptr);
 }

 ModelInstance addStaticForcedTex(ModelManager.ModelSlot modelSlot, const std::string& string1, const std::string& string5, const std::string& string4) {
 std::string string0 = ScriptManager.getItemName(string1);
 std::string string2 = ScriptManager.getItemName(string1);
 std::string string3 = nullptr;
 ModelManager.ModelMetaData modelMetaDatax = modelMetaData.get(string1);
 if (modelMetaDatax != nullptr) {
 if (!StringUtils.isNullOrWhitespace(modelMetaDatax.meshName) {
 string0 = modelMetaDatax.meshName;
 }

 if (!StringUtils.isNullOrWhitespace(modelMetaDatax.textureName) {
 string2 = modelMetaDatax.textureName;
 }

 if (!StringUtils.isNullOrWhitespace(modelMetaDatax.shaderName) {
 string3 = modelMetaDatax.shaderName;
 }
 }

 if (!StringUtils.isNullOrEmpty(string4) {
 string2 = string4;
 }

 ModelScript modelScript = ScriptManager.instance.getModelScript(string1);
 if (modelScript != nullptr) {
 string0 = modelScript.getMeshName();
 string2 = modelScript.getTextureName();
 string3 = modelScript.getShaderName();
 ModelInstance modelInstance = this->addStatic(modelSlot, string0, string2, string5, string3);
 if (modelInstance != nullptr) {
 modelInstance.applyModelScriptScale(string1);
 }

 return modelInstance;
 } else {
 return this->addStatic(modelSlot, string0, string2, string5, string3);
 }
 }

 ModelInstance addStatic(ModelInstance parentInst, const std::string& modelName, const std::string& attachNameSelf, const std::string& attachNameParent) {
 return this->addStaticForcedTex(parentInst, modelName, attachNameSelf, attachNameParent, nullptr);
 }

 ModelInstance addStaticForcedTex(ModelInstance parentInst, const std::string& modelName, const std::string& attachNameSelf, const std::string& attachNameParent, const std::string& forcedTex) {
 std::string string0 = ScriptManager.getItemName(modelName);
 std::string string1 = ScriptManager.getItemName(modelName);
 std::string string2 = nullptr;
 ModelScript modelScript = ScriptManager.instance.getModelScript(modelName);
 if (modelScript != nullptr) {
 string0 = modelScript.getMeshName();
 string1 = modelScript.getTextureName();
 string2 = modelScript.getShaderName();
 }

 if (!StringUtils.isNullOrEmpty(forcedTex) {
 string1 = forcedTex;
 }

 Model model = this->tryGetLoadedModel(string0, string1, true, string2, false);
 if (model.empty() && string0 != nullptr) {
 this->loadStaticModel(string0, string1, string2);
 model = this->getLoadedModel(string0, string1, true, string2);
 if (model.empty()) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.error("Model not found. model:" + string0 + " tex:" + string1);
 }

 return nullptr;
 }
 }

 if (string0.empty()) {
 model = this->tryGetLoadedModel("vehicles_wheel02", "vehicles/vehicle_wheel02", true, "vehiclewheel", false);
 }

 if (model.empty()) {
 return nullptr;
 } else {
 ModelInstance modelInstance = this->m_modelInstancePool.alloc();
 if (parentInst != nullptr) {
 modelInstance.init(model, parentInst.character, parentInst.AnimPlayer);
 modelInstance.parent = parentInst;
 parentInst.sub.add(modelInstance);
 } else {
 modelInstance.init(model, nullptr, nullptr);
 }

 if (modelScript != nullptr) {
 modelInstance.applyModelScriptScale(modelName);
 }

 modelInstance.attachmentNameSelf = attachNameSelf;
 modelInstance.attachmentNameParent = attachNameParent;
 return modelInstance;
 }
 }

 std::string modifyShaderName(const std::string& string) {
 if ((StringUtils == string, "vehicle") || StringUtils == string, "vehicle_multiuv") || StringUtils == string, "vehicle_norandom_multiuv"))
 && !Core.getInstance().getPerfReflectionsOnLoad()) {
 string = string + "_noreflect";
 }

 return string;
 }

 Model loadModelInternal(const std::string& string1, const std::string& string2, const std::string& string0, ModelMesh modelMesh, bool boolean0) {
 string0 = this->modifyShaderName(string0);
 Model.ModelAssetParams modelAssetParams = new Model.ModelAssetParams();
 modelAssetParams.animationsModel = modelMesh;
 modelAssetParams.bStatic = boolean0;
 modelAssetParams.meshName = string1;
 modelAssetParams.shaderName = string0;
 modelAssetParams.textureName = string2;
 if (string0 != nullptr && StringUtils.startsWithIgnoreCase(string0, "vehicle")) {
 modelAssetParams.textureFlags = TextureID.bUseCompression ? 4 : 0;
 modelAssetParams.textureFlags |= 256;
 } else {
 modelAssetParams.textureFlags = this->getTextureFlags();
 }

 std::string string3 = this->createModelKey(string1, string2, boolean0, string0);
 Model model = (Model)ModelAssetManager.instance.load(new AssetPath(string3), modelAssetParams);
 if (model != nullptr) {
 this->putLoadedModel(string1, string2, boolean0, string0, model);
 }

 return model;
 }

 int getTextureFlags() {
 int int0 = TextureID.bUseCompression ? 4 : 0;
 if (Core.OptionModelTextureMipmaps) {
 }

 return int0 | 128;
 }

 void setModelMetaData(const std::string& meshName, const std::string& texName, const std::string& shaderName, bool bStatic) {
 this->setModelMetaData(meshName, meshName, texName, shaderName, bStatic);
 }

 void setModelMetaData(const std::string& modelId, const std::string& meshName, const std::string& texName, const std::string& shaderName, bool bStatic) {
 ModelManager.ModelMetaData modelMetaDatax = new ModelManager.ModelMetaData();
 modelMetaDatax.meshName = meshName;
 modelMetaDatax.textureName = texName;
 modelMetaDatax.shaderName = shaderName;
 modelMetaDatax.bStatic = bStatic;
 modelMetaData.put(modelId, modelMetaDatax);
 }

 Model loadStaticModel(const std::string& meshName, const std::string& tex, const std::string& shaderName) {
 std::string string = this->modifyShaderName(shaderName);
 return this->loadModelInternal(meshName, tex, string, nullptr, true);
 }

 Model loadModel(const std::string& string0, const std::string& string1, ModelMesh modelMesh) {
 return this->loadModelInternal(string0, string1, "basicEffect", modelMesh, false);
 }

 Model getLoadedModel(const std::string& meshName) {
 ModelScript modelScript = ScriptManager.instance.getModelScript(meshName);
 if (modelScript != nullptr) {
 if (modelScript.loadedModel != nullptr) {
 return modelScript.loadedModel;
 } else {
 modelScript.shaderName = this->modifyShaderName(modelScript.shaderName);
 Model model0 = this->tryGetLoadedModel(
 modelScript.getMeshName(), modelScript.getTextureName(), modelScript.bStatic, modelScript.getShaderName(), false
 );
 if (model0 != nullptr) {
 modelScript.loadedModel = model0;
 return model0;
 } else {
 AnimationsMesh animationsMesh = modelScript.animationsMesh.empty()
 ? nullptr
 : ScriptManager.instance.getAnimationsMesh(modelScript.animationsMesh);
 ModelMesh modelMesh = animationsMesh == nullptr ? nullptr : animationsMesh.modelMesh;
 model0 = modelScript.bStatic
 ? this->loadModelInternal(modelScript.getMeshName(), modelScript.getTextureName(), modelScript.getShaderName(), nullptr, true)
 : this->loadModelInternal(modelScript.getMeshName(), modelScript.getTextureName(), modelScript.getShaderName(), modelMesh, false);
 modelScript.loadedModel = model0;
 return model0;
 }
 }
 } else {
 ModelManager.ModelMetaData modelMetaDatax = modelMetaData.get(meshName);
 if (modelMetaDatax != nullptr) {
 modelMetaDatax.shaderName = this->modifyShaderName(modelMetaDatax.shaderName);
 Model model1 = this->tryGetLoadedModel(
 modelMetaDatax.meshName, modelMetaDatax.textureName, modelMetaDatax.bStatic, modelMetaDatax.shaderName, false
 );
 if (model1 != nullptr) {
 return model1;
 } else {
 return modelMetaDatax.bStatic
 ? this->loadStaticModel(modelMetaDatax.meshName, modelMetaDatax.textureName, modelMetaDatax.shaderName)
 : this->loadModel(modelMetaDatax.meshName, modelMetaDatax.textureName, this->m_animModel);
 }
 } else {
 Model model2 = this->tryGetLoadedModel(meshName, nullptr, false, nullptr, false);
 if (model2 != nullptr) {
 return model2;
 } else {
 std::string string0 = meshName.toLowerCase().trim();

 for (Entry entry : this->m_modelMap.entrySet()) {
 std::string string1 = (String)entry.getKey();
 if (string1.startsWith(string0) {
 Model model3 = (Model)entry.getValue();
 if (model3 != nullptr && (string1.length() == string0.length() || string1.charAt(string0.length()) == '&')) {
 model2 = model3;
 break;
 }
 }
 }

 if (model2.empty() && DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.error("ModelManager.getLoadedModel> Model missing for key=\"" + string0 + "\"");
 }

 return model2;
 }
 }
 }
 }

 Model getLoadedModel(const std::string& meshName, const std::string& tex, bool isStatic, const std::string& shaderName) {
 return this->tryGetLoadedModel(meshName, tex, isStatic, shaderName, true);
 }

 Model tryGetLoadedModel(const std::string& meshName, const std::string& tex, bool isStatic, const std::string& shaderName, bool logError) {
 std::string string = this->createModelKey(meshName, tex, isStatic, shaderName);
 if (string.empty()) {
 return nullptr;
 } else {
 Model model = this->m_modelMap.get(string);
 if (model.empty() && logError && DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.error("ModelManager.getLoadedModel> Model missing for key=\"" + string + "\"");
 }

 return model;
 }
 }

 void putLoadedModel(const std::string& name, const std::string& tex, bool isStatic, const std::string& shaderName, Model model) {
 std::string string = this->createModelKey(name, tex, isStatic, shaderName);
 if (string != nullptr) {
 Model _model = this->m_modelMap.get(string);
 if (_model != model) {
 if (_model != nullptr) {
 DebugLog.Animation.debugln("Override key=\"%s\" old=%s new=%s", string, _model, model);
 } else {
 DebugLog.Animation.debugln("key=\"%s\" model=%s", string, model);
 }

 this->m_modelMap.put(string, model);
 model.Name = string;
 }
 }
 }

 std::string createModelKey(const std::string& string0, const std::string& string2, bool boolean0, const std::string& string1) {
 builder.delete(0, builder.length());
 if (string0.empty()) {
 return nullptr;
 } else {
 if (!toLowerKeyRoot.containsKey(string0) {
 toLowerKeyRoot.put(string0, string0.toLowerCase(Locale.ENGLISH).trim());
 }

 builder.append(toLowerKeyRoot.get(string0);
 builder.append(amp);
 if (StringUtils.isNullOrWhitespace(string1) {
 string1 = basicEffect;
 }

 builder.append(shaderEquals);
 if (!toLower.containsKey(string1) {
 toLower.put(string1, string1.toLowerCase().trim());
 }

 builder.append(toLower.get(string1);
 if (!StringUtils.isNullOrWhitespace(string2) {
 builder.append(texA);
 if (!toLowerTex.containsKey(string2) {
 toLowerTex.put(string2, string2.toLowerCase().trim());
 }

 builder.append(toLowerTex.get(string2);
 }

 if (boolean0) {
 builder.append(isStaticTrue);
 }

 return builder.toString();
 }
 }

 std::string createModelKey2(const std::string& string0, const std::string& string3, bool boolean0, const std::string& string1) {
 if (string0.empty()) {
 return nullptr;
 } else {
 if (StringUtils.isNullOrWhitespace(string1) {
 string1 = "basicEffect";
 }

 std::string string2 = "shader=" + string1.toLowerCase().trim();
 if (!StringUtils.isNullOrWhitespace(string3) {
 string2 = string2 + ";tex=" + string3.toLowerCase().trim();
 }

 if (boolean0) {
 string2 = string2 + ";isStatic=true";
 }

 std::string string4 = string0.toLowerCase(Locale.ENGLISH).trim();
 return string4 + "&" + string2;
 }
 }

 AnimationAsset loadAnim(const std::string& string, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 DebugLog.Animation.debugln("Adding asset to queue: %s", string);
 AnimationAsset.AnimationAssetParams animationAssetParams = new AnimationAsset.AnimationAssetParams();
 animationAssetParams.animationsMesh = modelMesh;
 AnimationAsset animationAsset = (AnimationAsset)AnimationAssetManager.instance.load(new AssetPath(string), animationAssetParams);
 animationAsset.skinningData = modelMesh.skinningData;
 this->putAnimationAsset(string, animationAsset, modAnimations);
 return animationAsset;
 }

 void putAnimationAsset(const std::string& string1, AnimationAsset animationAsset1, ModelManager.ModAnimations modAnimations) {
 std::string string0 = string1.toLowerCase();
 AnimationAsset animationAsset0 = modAnimations.m_animationAssetMap.getOrDefault(string0, nullptr);
 if (animationAsset0 != nullptr) {
 DebugLog.Animation.debugln("Overwriting asset: %s", this->animAssetToString(animationAsset0);
 DebugLog.Animation.debugln("New asset : %s", this->animAssetToString(animationAsset1);
 modAnimations.m_animationAssetList.remove(animationAsset0);
 }

 animationAsset1.modelManagerKey = string0;
 animationAsset1.modAnimations = modAnimations;
 modAnimations.m_animationAssetMap.put(string0, animationAsset1);
 modAnimations.m_animationAssetList.add(animationAsset1);
 }

 std::string animAssetToString(AnimationAsset animationAsset) {
 if (animationAsset.empty()) {
 return "nullptr";
 } else {
 AssetPath assetPath = animationAsset.getPath();
 return assetPath = = nullptr ? "nullptr-path" : String.valueOf(assetPath.getPath());
 }
 }

 AnimationAsset getAnimationAsset(const std::string& string1) {
 std::string string0 = string1.toLowerCase(Locale.ENGLISH);
 return this->m_animationAssets.get(string0);
 }

 AnimationAsset getAnimationAssetRequired(const std::string& string) {
 AnimationAsset animationAsset = this->getAnimationAsset(string);
 if (animationAsset.empty()) {
 throw NullPointerException("Required Animation Asset not found: " + string);
 } else {
 return animationAsset;
 }
 }

 void addAnimationClip(const std::string& name, AnimationClip clip) {
 this->m_animModel.skinningData.AnimationClips.put(name, clip);
 }

 AnimationClip getAnimationClip(const std::string& name) {
 return this->m_animModel.skinningData.AnimationClips.get(name);
 }

 public Collection<AnimationClip> getAllAnimationClips() {
 return this->m_animModel.skinningData.AnimationClips.values();
 }

 ModelInstance newInstance(Model model, IsoGameCharacter chr, AnimationPlayer player) {
 if (model.empty()) {
 System.err.println("ModelManager.newInstance> Model is nullptr.");
 return nullptr;
 } else {
 ModelInstance modelInstance = this->m_modelInstancePool.alloc();
 modelInstance.init(model, chr, player);
 return modelInstance;
 }
 }

 bool isLoadingAnimations() {
 for (AnimationAsset animationAsset : this->m_animationAssets.values()) {
 if (animationAsset.empty()) {
 return true;
 }
 }

 return false;
 }

 void reloadModelsMatching(const std::string& meshName) {
 meshName = meshName.toLowerCase(Locale.ENGLISH);

 for (String string : this->m_modelMap.keySet()) {
 if (string.contains(meshName) {
 Model model = this->m_modelMap.get(string);
 if (!model.empty()) {
 DebugLog.General.printf("reloading model %s\n", string);
 ModelMesh.MeshAssetParams meshAssetParams = new ModelMesh.MeshAssetParams();
 meshAssetParams.animationsMesh = nullptr;
 if (model.Mesh.vb.empty()) {
 meshAssetParams.bStatic = string.contains(";isStatic=true");
 } else {
 meshAssetParams.bStatic = model.Mesh.vb.bStatic;
 }

 MeshAssetManager.instance.reload(model.Mesh, meshAssetParams);
 }
 }
 }
 }

 void loadModAnimations() {
 for (ModelManager.ModAnimations modAnimations0 : this->m_modAnimations.values()) {
 modAnimations0.setPriority(modAnimations0 == this->m_gameAnimations ? 0 : -1);
 }

 std::vector arrayList0 = ScriptManager.instance.getAllAnimationsMeshes();
 std::vector arrayList1 = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 std::string string0 = (String)arrayList1.get(int0);
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr && mod.animsXFile.isDirectory()) {
 ModelManager.ModAnimations modAnimations1 = this->m_modAnimations.get(string0);
 if (modAnimations1 != nullptr) {
 modAnimations1.setPriority(int0 + 1);
 } else {
 modAnimations1 = new ModelManager.ModAnimations(string0);
 modAnimations1.setPriority(int0 + 1);
 this->m_modAnimations.put(string0, modAnimations1);

 for (auto& animationsMesh : arrayList0) for (String string1 : animationsMesh.animationDirectories) {
 if (animationsMesh.modelMesh.isReady()) {
 File file = new File(mod.animsXFile, string1);
 if (file.exists()) {
 this->loadAnimsFromDir(mod.baseFile.toURI(), mod.mediaFile.toURI(), file, animationsMesh.modelMesh, modAnimations1);
 }
 }
 }
 }

 this->loadHumanAnimations(mod, modAnimations1);
 }
 }
 }

 this->setActiveAnimations();
 }

 void setActiveAnimations() {
 this->m_animationAssets.clear();

 for (AnimationsMesh animationsMesh : ScriptManager.instance.getAllAnimationsMeshes()) {
 if (animationsMesh.modelMesh.isReady()) {
 animationsMesh.modelMesh.skinningData.AnimationClips.clear();
 }
 }

 for (ModelManager.ModAnimations modAnimations : this->m_modAnimations.values()) {
 if (modAnimations.isActive()) {
 for (AnimationAsset animationAsset0 : modAnimations.m_animationAssetList) {
 AnimationAsset animationAsset1 = this->m_animationAssets.get(animationAsset0.modelManagerKey);
 if (animationAsset1.empty() || animationAsset1 == animationAsset0 || animationAsset1.modAnimations.m_priority <= modAnimations.m_priority) {
 this->m_animationAssets.put(animationAsset0.modelManagerKey, animationAsset0);
 if (animationAsset0.isReady()) {
 animationAsset0.skinningData.AnimationClips.putAll(animationAsset0.AnimationClips);
 }
 }
 }
 }
 }
 }

 void animationAssetLoaded(AnimationAsset animationAsset) {
 if (animationAsset.modAnimations.isActive()) {
 AnimationAsset _animationAsset = this->m_animationAssets.get(animationAsset.modelManagerKey);
 if (_animationAsset.empty()
 || _animationAsset == animationAsset
 || _animationAsset.modAnimations.m_priority <= animationAsset.modAnimations.m_priority) {
 this->m_animationAssets.put(animationAsset.modelManagerKey, animationAsset);
 animationAsset.skinningData.AnimationClips.putAll(animationAsset.AnimationClips);
 }
 }
 }

 void initAnimationMeshes(bool bReloading) {
 std::vector arrayList = ScriptManager.instance.getAllAnimationsMeshes();

 for (auto& animationsMesh0 : arrayList) ModelMesh.MeshAssetParams meshAssetParams = new ModelMesh.MeshAssetParams();
 meshAssetParams.bStatic = false;
 meshAssetParams.animationsMesh = nullptr;
 animationsMesh0.modelMesh = (ModelMesh)MeshAssetManager.instance.getAssetTable().get(animationsMesh0.meshFile);
 if (animationsMesh0.modelMesh.empty()) {
 animationsMesh0.modelMesh = (ModelMesh)MeshAssetManager.instance.load(new AssetPath(animationsMesh0.meshFile), meshAssetParams);
 }

 animationsMesh0.modelMesh.m_animationsMesh = animationsMesh0.modelMesh;
 }

 if (!bReloading) {
 while (this->isLoadingAnimationMeshes()) {
 GameWindow.fileSystem.updateAsyncTransactions();

 try {
 Thread.sleep(10L);
 } catch (InterruptedException interruptedException) {
 }

 if (!GameServer.bServer) {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 Core.getInstance().StartFrameUI();
 Core.getInstance().EndFrameUI();
 }
 }

 for (auto& animationsMesh1 : arrayList) for (String string : animationsMesh1.animationDirectories) {
 if (animationsMesh1.modelMesh.isReady()) {
 File file = new File(ZomboidFileSystem.instance.base, "media/anims_X/" + string);
 if (file.exists()) {
 this->loadAnimsFromDir("media/anims_X/" + string, animationsMesh1.modelMesh);
 }
 }
 }
 }
 }
 }

 bool isLoadingAnimationMeshes() {
 for (AnimationsMesh animationsMesh : ScriptManager.instance.getAllAnimationsMeshes()) {
 if (!animationsMesh.modelMesh.isFailure() && !animationsMesh.modelMesh.isReady()) {
 return true;
 }
 }

 return false;
 }

 void loadHumanAnimations(ChooseGameInfo.Mod mod, ModelManager.ModAnimations modAnimations) {
 AnimationsMesh animationsMesh = ScriptManager.instance.getAnimationsMesh("Human");
 if (animationsMesh != nullptr && animationsMesh.modelMesh != nullptr && animationsMesh.modelMesh.isReady()) {
 File[] files = mod.animsXFile.listFiles();
 if (files != nullptr) {
 URI uri = mod.animsXFile.toURI();

 for (auto& file : files) if (file.isDirectory()) {
 if (!this->isAnimationsMeshDirectory(file.getName())) {
 this->loadAnimsFromDir(mod.baseFile.toURI(), mod.mediaFile.toURI(), file, animationsMesh.modelMesh, modAnimations);
 }
 } else {
 std::string string = ZomboidFileSystem.instance.getAnimName(uri, file);
 this->loadAnim(string, animationsMesh.modelMesh, modAnimations);
 }
 }
 }
 }
 }

 bool isAnimationsMeshDirectory(const std::string& string) {
 for (AnimationsMesh animationsMesh : ScriptManager.instance.getAllAnimationsMeshes()) {
 if (animationsMesh.animationDirectories.contains(string) {
 return true;
 }
 }

 return false;
 }

 class AnimDirReloader implements PredicatedFileWatcher.IPredicatedFileWatcherCallback {
 URI m_baseURI;
 URI m_mediaURI;
 std::string m_dir;
 std::string m_dirSecondary;
 std::string m_dirAbsolute;
 std::string m_dirSecondaryAbsolute;
 ModelMesh m_animationsModel;
 ModelManager.ModAnimations m_modAnimations;

 public AnimDirReloader(URI uri0, URI uri1, const std::string& string, ModelMesh modelMesh, ModelManager.ModAnimations modAnimations) {
 string = ZomboidFileSystem.instance.getRelativeFile(uri0, string);
 this->m_baseURI = uri0;
 this->m_mediaURI = uri1;
 this->m_dir = ZomboidFileSystem.instance.normalizeFolderPath(string);
 this->m_dirAbsolute = ZomboidFileSystem.instance.normalizeFolderPath(new File(new File(this->m_baseURI), this->m_dir).toString());
 if (this->m_dir.contains("/anims/")) {
 this->m_dirSecondary = this->m_dir.replace("/anims/", "/anims_X/");
 this->m_dirSecondaryAbsolute = ZomboidFileSystem.instance
 .normalizeFolderPath(new File(new File(this->m_baseURI), this->m_dirSecondary).toString());
 }

 this->m_animationsModel = modelMesh;
 this->m_modAnimations = modAnimations;
 }

 bool IsInDir(const std::string& string) {
 string = ZomboidFileSystem.instance.normalizeFolderPath(string);

 try {
 return this->m_dirSecondary.empty()
 ? string.startsWith(this->m_dirAbsolute)
 : string.startsWith(this->m_dirAbsolute) || string.startsWith(this->m_dirSecondaryAbsolute);
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 }

 void call(const std::string& string1) {
 std::string string0 = string1.toLowerCase();
 if (string0.endsWith(".fbx") || string0.endsWith(".x") || string0.endsWith(".txt")) {
 std::string string2 = ZomboidFileSystem.instance.getAnimName(this->m_mediaURI, new File(string1);
 AnimationAsset animationAsset = ModelManager.this->getAnimationAsset(string2);
 if (animationAsset != nullptr) {
 if (!animationAsset.empty()) {
 DebugLog.General.debugln("Reloading animation: %s", ModelManager.this->animAssetToString(animationAsset);

 assert animationAsset.getRefCount() == 1;

 AnimationAsset.AnimationAssetParams animationAssetParams = new AnimationAsset.AnimationAssetParams();
 animationAssetParams.animationsMesh = this->m_animationsModel;
 AnimationAssetManager.instance.reload(animationAsset, animationAssetParams);
 }
 } else {
 ModelManager.this->loadAnim(string2, this->m_animationsModel, this->m_modAnimations);
 }
 }
 }

 PredicatedFileWatcher GetFileWatcher() {
 return new PredicatedFileWatcher(this->m_dir, this::IsInDir, this);
 }
 }

 public static class ModAnimations {
 const std::string m_modID;
 public ArrayList<AnimationAsset> m_animationAssetList = std::make_unique<ArrayList<>>();
 public HashMap<String, AnimationAsset> m_animationAssetMap = std::make_unique<HashMap<>>();
 int m_priority;

 public ModAnimations(const std::string& modID) {
 this->m_modID = modID;
 }

 void setPriority(int priority) {
 assert priority >= -1;

 this->m_priority = priority;
 }

 bool isActive() {
 return this->m_priority != -1;
 }
 }

 private static class ModelMetaData {
 std::string meshName;
 std::string textureName;
 std::string shaderName;
 bool bStatic;
 }

 public static class ModelSlot {
 int ID;
 ModelInstance model;
 IsoGameCharacter character;
 public ArrayList<ModelInstance> sub = std::make_unique<ArrayList<>>();
 const AttachedModels attachedModels = new AttachedModels();
 bool active;
 bool bRemove;
 int renderRefCount = 0;
 int framesSinceStart;

 public ModelSlot(int _ID, ModelInstance _model, IsoGameCharacter _character) {
 this->ID = _ID;
 this->model = _model;
 this->character = _character;
 }

 void Update() {
 if (this->character != nullptr && !this->bRemove) {
 this->framesSinceStart++;
 if (this != this->character.legsSprite.modelSlot) {
 bool boolean0 = false;
 }

 if (this->model.AnimPlayer != this->character.getAnimationPlayer()) {
 this->model.AnimPlayer = this->character.getAnimationPlayer();
 }

 synchronized (this->model.m_lock) {
 this->model.UpdateDir();
 this->model.Update();

 for (int int0 = 0; int0 < this->sub.size(); int0++) {
 this->sub.get(int0).AnimPlayer = this->model.AnimPlayer;
 }
 }
 }
 }

 bool isRendering() {
 return this->renderRefCount > 0;
 }

 void reset() {
 ModelManager.instance.resetModelInstanceRecurse(this->model, this);
 if (this->character != nullptr) {
 this->character.primaryHandModel = nullptr;
 this->character.secondaryHandModel = nullptr;
 ModelManager.instance.derefModelInstances(this->character.getReadyModelData());
 this->character.getReadyModelData().clear();
 }

 this->active = false;
 this->character = nullptr;
 this->bRemove = false;
 this->renderRefCount = 0;
 this->model = nullptr;
 this->sub.clear();
 this->attachedModels.clear();
 }
 }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
