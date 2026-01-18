#pragma once
#include "org/joml/Math.h"
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL14.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/GameProfiler.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/AttachedItems/AttachedModelName.h"
#include "zombie/characters/AttachedItems/AttachedModelNames.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/action/IActionStateChanged.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureInitializer.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VehicleModelInstance.h"
#include "zombie/core/skinnedmodel/model/VehicleSubModelInstance.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/PopTemplateManager.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimatedModel : public AnimationVariableSource {
public:
 std::string animSetName = "player-avatar";
 std::string outfitName;
 IsoGameCharacter character;
 HumanVisual baseVisual = nullptr;
 const ItemVisuals itemVisuals = new ItemVisuals();
 std::string primaryHandModelName;
 std::string secondaryHandModelName;
 const AttachedModelNames attachedModelNames = new AttachedModelNames();
 ModelInstance modelInstance;
 bool bFemale = false;
 bool bZombie = false;
 bool bSkeleton = false;
 std::string state;
 const Vector2 angle = new Vector2();
 const Vector3f offset = new Vector3f(0.0F, -0.45F, 0.0F);
 bool bIsometric = true;
 bool flipY = false;
 float m_alpha = 1.0F;
 AnimationPlayer animPlayer = nullptr;
 const ActionContext actionContext = new ActionContext(this);
 const AdvancedAnimator advancedAnimator = new AdvancedAnimator();
 float trackTime = 0.0F;
 const std::string m_UID;
 float lightsOriginX;
 float lightsOriginY;
 float lightsOriginZ;
private
 IsoGridSquare.ResultLight[] lights = new IsoGridSquare.ResultLight[5];
 const ColorInfo ambient = new ColorInfo();
 bool bOutside = true;
 bool bRoom = false;
 bool bUpdateTextures;
 bool bClothingChanged;
 bool bAnimate = true;
 ModelInstanceTextureCreator textureCreator;
private
 AnimatedModel.StateInfo[] stateInfos = new AnimatedModel.StateInfo[3];
 bool bReady;
private
 static ObjectPool<AnimatedModel.AnimatedModelInstanceRenderData>
 instDataPool =
 new ObjectPool<>(AnimatedModel.AnimatedModelInstanceRenderData::new);
private
 AnimatedModel.UIModelCamera uiModelCamera =
 new AnimatedModel.UIModelCamera();
private
 static AnimatedModel.WorldModelCamera worldModelCamera =
 new AnimatedModel.WorldModelCamera();

public
 AnimatedModel() {
 this->m_UID = String.format("%s-%s", this->getClass().getSimpleName(),
 UUID.randomUUID().toString());
 this->advancedAnimator.init(this);
 this->advancedAnimator.animCallbackHandlers.add(this);
 this->actionContext.onStateChanged.add(this);

 for (int int0 = 0; int0 < this->lights.length; int0++) {
 this->lights[int0] = new IsoGridSquare.ResultLight();
 }

 for (int int1 = 0; int1 < this->stateInfos.length; int1++) {
 this->stateInfos[int1] = new AnimatedModel.StateInfo();
 }
 }

 void setVisual(HumanVisual _baseVisual) { this->baseVisual = _baseVisual; }

 BaseVisual getVisual() { return this->baseVisual; }

 HumanVisual getHumanVisual() {
 return Type.tryCastTo(this->baseVisual, HumanVisual.class);
 }

 void getItemVisuals(ItemVisuals _itemVisuals) { _itemVisuals.clear(); }

 bool isFemale() { return this->bFemale; }

 bool isZombie() { return this->bZombie; }

 bool isSkeleton() { return this->bSkeleton; }

 void setAnimSetName(const std::string &name) {
 if (StringUtils.isNullOrWhitespace(name) {
 throw IllegalArgumentException("invalid AnimSet \"" + name + "\"");
 } else {
 this->animSetName = name;
 }
 }

 void setOutfitName(const std::string &name, bool female, bool zombie) {
 this->outfitName = name;
 this->bFemale = female;
 this->bZombie = zombie;
 }

 void setCharacter(IsoGameCharacter _character) {
 this->outfitName = nullptr;
 if (this->baseVisual != nullptr) {
 this->baseVisual.clear();
 }

 this->itemVisuals.clear();
 if (_character instanceof IHumanVisual) {
 _character.getItemVisuals(this->itemVisuals);
 this->character = _character;
 if (_character.getAttachedItems() != nullptr) {
 this->attachedModelNames.initFrom(_character.getAttachedItems());
 }

 this->setModelData(((IHumanVisual)_character).getHumanVisual(),
 this->itemVisuals);
 }
 }

 void setSurvivorDesc(SurvivorDesc survivorDesc) {
 this->outfitName = nullptr;
 if (this->baseVisual != nullptr) {
 this->baseVisual.clear();
 }

 this->itemVisuals.clear();
 survivorDesc.getWornItems().getItemVisuals(this->itemVisuals);
 this->attachedModelNames.clear();
 this->setModelData(survivorDesc.getHumanVisual(), this->itemVisuals);
 }

 void setPrimaryHandModelName(const std::string &name) {
 this->primaryHandModelName = name;
 }

 void setSecondaryHandModelName(const std::string &name) {
 this->secondaryHandModelName = name;
 }

 void setAttachedModelNames(AttachedModelNames _attachedModelNames) {
 this->attachedModelNames.copyFrom(_attachedModelNames);
 }

 void setModelData(HumanVisual _baseVisual, ItemVisuals _itemVisuals) {
 AnimationPlayer animationPlayer = this->animPlayer;
 Model model0 = this->animPlayer == nullptr ? nullptr : animationPlayer.getModel();
 if (this->baseVisual != _baseVisual) {
 if (this->baseVisual.empty()) {
 this->baseVisual = new HumanVisual(this);
 }

 this->baseVisual.copyFrom(_baseVisual);
 }

 if (this->itemVisuals != _itemVisuals) {
 this->itemVisuals.clear();
 this->itemVisuals.addAll(_itemVisuals);
 }

 if (this->baseVisual != _baseVisual) {
 this->bFemale = false;
 this->bZombie = false;
 this->bSkeleton = false;
 if (_baseVisual != nullptr) {
 this->bFemale = _baseVisual.isFemale();
 this->bZombie = _baseVisual.isZombie();
 this->bSkeleton = _baseVisual.isSkeleton();
 }
 }

 if (this->modelInstance != nullptr) {
 ModelManager.instance.resetModelInstanceRecurse(this->modelInstance, this);
 }

 Model model1 = _baseVisual.getModel();
 this->getAnimationPlayer().setModel(model1);
 this->modelInstance = ModelManager.instance.newInstance(
 model1, nullptr, this->getAnimationPlayer());
 this->modelInstance.m_modelScript = _baseVisual.getModelScript();
 this->modelInstance.setOwner(this);
 this->populateCharacterModelSlot();
 this->DoCharacterModelEquipped();
 bool boolean0 = false;
 if (this->bAnimate) {
 AnimationSet animationSet =
 AnimationSet.GetAnimationSet(this->GetAnimSetName(), false);
 if (animationSet != this->advancedAnimator.animSet ||
 animationPlayer != this->getAnimationPlayer() || model0 != model1) {
 boolean0 = true;
 }
 } else {
 boolean0 = true;
 }

 if (boolean0) {
 this->advancedAnimator.OnAnimDataChanged(false);
 }

 if (this->bAnimate) {
 ActionGroup actionGroup =
 ActionGroup.getActionGroup(this->GetAnimSetName());
 if (actionGroup != this->actionContext.getGroup()) {
 this->actionContext.setGroup(actionGroup);
 }

 this->advancedAnimator.SetState(
 this->actionContext.getCurrentStateName(),
 PZArrayUtil.listConvert(this->actionContext.getChildStates(),
 actionState->actionState.name);
 } else if (!StringUtils.isNullOrWhitespace(this->state) {
 this->advancedAnimator.SetState(this->state);
 }

 if (boolean0) {
 float float0 = GameTime.getInstance().FPSMultiplier;
 GameTime.getInstance().FPSMultiplier = 100.0F;

 try {
 this->advancedAnimator.update();
 } finally {
 GameTime.getInstance().FPSMultiplier = float0;
 }
 }

 if (Core.bDebug && !this->bAnimate &&
 this->stateInfoMain().readyData.empty()) {
 this->getAnimationPlayer().resetBoneModelTransforms();
 }

 this->trackTime = 0.0F;
 this->stateInfoMain().bModelsReady = this->isReadyToRender();
 }

 void setAmbient(ColorInfo _ambient, bool outside, bool room) {
 this->ambient.set(_ambient.r, _ambient.g, _ambient.b, 1.0F);
 this->bOutside = outside;
 this->bRoom = room;
 }

 void setLights(IsoGridSquare.ResultLight[] resultLights, float float0,
 float float1, float float2) {
 this->lightsOriginX = float0;
 this->lightsOriginY = float1;
 this->lightsOriginZ = float2;

 for (int int0 = 0; int0 < resultLights.length; int0++) {
 this->lights[int0].copyFrom(resultLights[int0]);
 }
 }

 void setState(const std::string &_state) { this->state = _state; }

 std::string getState() { return this->state; }

 void setAngle(Vector2 _angle) { this->angle.set(_angle); }

 void setOffset(float x, float y, float z) { this->offset.set(x, y, z); }

 void setIsometric(bool iso) { this->bIsometric = iso; }

 bool isIsometric() { return this->bIsometric; }

 void setFlipY(bool flip) { this->flipY = flip; }

 void setAlpha(float alpha) { this->m_alpha = alpha; }

 void setTrackTime(float _trackTime) { this->trackTime = _trackTime; }

 void clothingItemChanged(const std::string &itemGuid) {
 this->bClothingChanged = true;
 }

 void setAnimate(bool animate) { this->bAnimate = animate; }

 void initOutfit() {
 std::string string = this->outfitName;
 this->outfitName = nullptr;
 if (!StringUtils.isNullOrWhitespace(string) {
 ModelManager.instance.create();
 this->baseVisual.dressInNamedOutfit(string, this->itemVisuals);
 this->setModelData(this->baseVisual, this->itemVisuals);
 }
 }

 void populateCharacterModelSlot() {
 HumanVisual humanVisual = this->getHumanVisual();
 if (humanVisual.empty()) {
 this->bUpdateTextures = true;
 } else {
 CharacterMask characterMask = HumanVisual.GetMask(this->itemVisuals);
 if (characterMask.isPartVisible(CharacterMask.Part.Head) {
 this->addHeadHair(this->itemVisuals.findHat());
 }

 for (int int0 = this->itemVisuals.size() - 1; int0 >= 0; int0--) {
 ItemVisual itemVisual0 = this->itemVisuals.get(int0);
 ClothingItem clothingItem0 = itemVisual0.getClothingItem();
 if (clothingItem0 != nullptr && clothingItem0.isReady() &&
 !this->isItemModelHidden(this->itemVisuals, itemVisual0) {
 this->addClothingItem(itemVisual0, clothingItem0);
 }
 }

 for (int int1 = humanVisual.getBodyVisuals().size() - 1; int1 >= 0;
 int1--) {
 ItemVisual itemVisual1 = humanVisual.getBodyVisuals().get(int1);
 ClothingItem clothingItem1 = itemVisual1.getClothingItem();
 if (clothingItem1 != nullptr && clothingItem1.isReady()) {
 this->addClothingItem(itemVisual1, clothingItem1);
 }
 }

 this->bUpdateTextures = true;
 Lambda.forEachFrom(
 PZArrayUtil::forEach, this->modelInstance.sub, this->modelInstance,
 (modelInstance1, modelInstance0)->modelInstance1.AnimPlayer =
 modelInstance0.AnimPlayer);
 }
 }

 void addHeadHair(ItemVisual itemVisual) {
 HumanVisual humanVisual = this->getHumanVisual();
 ImmutableColor immutableColor0 = humanVisual.getHairColor();
 ImmutableColor immutableColor1 = humanVisual.getBeardColor();
 if (this->isFemale()) {
 HairStyle hairStyle0 =
 HairStyles.instance.FindFemaleStyle(humanVisual.getHairModel());
 if (hairStyle0 != nullptr && itemVisual != nullptr &&
 itemVisual.getClothingItem() != nullptr) {
 hairStyle0 = HairStyles.instance.getAlternateForHat(
 hairStyle0, itemVisual.getClothingItem().m_HatCategory);
 }

 if (hairStyle0 != nullptr && hairStyle0.isValid()) {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.debugln(" Adding female hair: " + hairStyle0.name);
 }

 this->addHeadHairItem(hairStyle0.model, hairStyle0.texture,
 immutableColor0);
 }
 } else {
 HairStyle hairStyle1 =
 HairStyles.instance.FindMaleStyle(humanVisual.getHairModel());
 if (hairStyle1 != nullptr && itemVisual != nullptr &&
 itemVisual.getClothingItem() != nullptr) {
 hairStyle1 = HairStyles.instance.getAlternateForHat(
 hairStyle1, itemVisual.getClothingItem().m_HatCategory);
 }

 if (hairStyle1 != nullptr && hairStyle1.isValid()) {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.debugln(" Adding male hair: " + hairStyle1.name);
 }

 this->addHeadHairItem(hairStyle1.model, hairStyle1.texture,
 immutableColor0);
 }

 BeardStyle beardStyle =
 BeardStyles.instance.FindStyle(humanVisual.getBeardModel());
 if (beardStyle != nullptr && beardStyle.isValid()) {
 if (itemVisual != nullptr && itemVisual.getClothingItem() != nullptr &&
 !StringUtils.isNullOrEmpty(
 itemVisual.getClothingItem().m_HatCategory) &&
 itemVisual.getClothingItem().m_HatCategory.contains("nobeard")) {
 return;
 }

 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.debugln(" Adding beard: " + beardStyle.name);
 }

 this->addHeadHairItem(beardStyle.model, beardStyle.texture,
 immutableColor1);
 }
 }
 }

 void addHeadHairItem(const std::string &string0, const std::string &string1,
 ImmutableColor immutableColor) {
 if (StringUtils.isNullOrWhitespace(string0) {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.warn("No model specified.");
 }
 } else {
 string0 = this->processModelFileName(string0);
 ModelInstance modelInstancex =
 ModelManager.instance.newAdditionalModelInstance(
 string0, string1, nullptr, this->modelInstance.AnimPlayer, nullptr);
 if (modelInstancex != nullptr) {
 this->postProcessNewItemInstance(this->modelInstance, modelInstancex,
 immutableColor);
 }
 }
 }

 void addClothingItem(ItemVisual itemVisual, ClothingItem clothingItem) {
 std::string string0 = clothingItem.getModel(this->bFemale);
 if (StringUtils.isNullOrWhitespace(string0) {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.debugln("No model specified by item: " +
 clothingItem.m_Name);
 }
 } else {
 string0 = this->processModelFileName(string0);
 std::string string1 = itemVisual.getTextureChoice(clothingItem);
 ImmutableColor immutableColor = itemVisual.getTint(clothingItem);
 std::string string2 = clothingItem.m_AttachBone;
 std::string string3 = clothingItem.m_Shader;
 ModelInstance modelInstancex;
 if (string2 != nullptr && string2.length() > 0) {
 modelInstancex = this->addStatic(string0, string1, string2, string3);
 } else {
 modelInstancex = ModelManager.instance.newAdditionalModelInstance(
 string0, string1, nullptr, this->modelInstance.AnimPlayer, string3);
 }

 if (modelInstancex != nullptr) {
 this->postProcessNewItemInstance(this->modelInstance, modelInstancex,
 immutableColor);
 modelInstancex.setItemVisual(itemVisual);
 }
 }
 }

 bool isItemModelHidden(ItemVisuals itemVisualsx, ItemVisual itemVisual) {
 BodyLocationGroup bodyLocationGroup = BodyLocations.getGroup("Human");
 return PopTemplateManager.instance.isItemModelHidden(
 bodyLocationGroup, itemVisualsx, itemVisual);
 }

 std::string processModelFileName(const std::string &string) {
 string = string.replaceAll("\\\\", "/");
 return string.toLowerCase(Locale.ENGLISH);
 }

 void postProcessNewItemInstance(ModelInstance modelInstance1,
 ModelInstance modelInstance0,
 ImmutableColor immutableColor) {
 modelInstance0.depthBias = 0.0F;
 modelInstance0.matrixModel = this->modelInstance;
 modelInstance0.tintR = immutableColor.r;
 modelInstance0.tintG = immutableColor.g;
 modelInstance0.tintB = immutableColor.b;
 modelInstance0.AnimPlayer = this->modelInstance.AnimPlayer;
 modelInstance1.sub.add(modelInstance0);
 modelInstance0.setOwner(this);
 }

 void DoCharacterModelEquipped() {
 if (!StringUtils.isNullOrWhitespace(this->primaryHandModelName) {
 ModelInstance modelInstance0 =
 this->addStatic(this->primaryHandModelName, "Bip01_Prop1");
 this->postProcessNewItemInstance(this->modelInstance, modelInstance0,
 ImmutableColor.white);
 }

 if (!StringUtils.isNullOrWhitespace(this->secondaryHandModelName) {
 ModelInstance modelInstance1 =
 this->addStatic(this->secondaryHandModelName, "Bip01_Prop2");
 this->postProcessNewItemInstance(this->modelInstance, modelInstance1,
 ImmutableColor.white);
 }

 for (int int0 = 0; int0 < this->attachedModelNames.size(); int0++) {
 AttachedModelName attachedModelName0 = this->attachedModelNames.get(int0);
 ModelInstance modelInstance2 = ModelManager.instance.addStatic(
 nullptr, attachedModelName0.modelName,
 attachedModelName0.attachmentNameSelf,
 attachedModelName0.attachmentNameParent);
 this->postProcessNewItemInstance(this->modelInstance, modelInstance2,
 ImmutableColor.white);
 if (attachedModelName0.bloodLevel > 0.0F &&
 !Core.getInstance().getOptionSimpleWeaponTextures()) {
 ModelInstanceTextureInitializer modelInstanceTextureInitializer =
 ModelInstanceTextureInitializer.alloc();
 modelInstanceTextureInitializer.init(modelInstance2,
 attachedModelName0.bloodLevel);
 modelInstance2.setTextureInitializer(modelInstanceTextureInitializer);
 }

 for (int int1 = 0; int1 < attachedModelName0.getChildCount(); int1++) {
 AttachedModelName attachedModelName1 =
 attachedModelName0.getChildByIndex(int1);
 ModelInstance modelInstance3 = ModelManager.instance.addStatic(
 modelInstance2, attachedModelName1.modelName,
 attachedModelName1.attachmentNameSelf,
 attachedModelName1.attachmentNameParent);
 modelInstance2.sub.remove(modelInstance3);
 this->postProcessNewItemInstance(modelInstance2, modelInstance3,
 ImmutableColor.white);
 }
 }
 }

 ModelInstance addStatic(const std::string &string1,
 const std::string &string4) {
 std::string string0 = string1;
 std::string string2 = string1;
 std::string string3 = nullptr;
 ModelScript modelScript = ScriptManager.instance.getModelScript(string1);
 if (modelScript != nullptr) {
 string0 = modelScript.getMeshName();
 string2 = modelScript.getTextureName();
 string3 = modelScript.getShaderName();
 }

 return this->addStatic(string0, string2, string4, string3);
 }

 ModelInstance addStatic(const std::string &string0,
 const std::string &string1,
 const std::string &string3,
 const std::string &string2) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln("Adding Static Model:" + string0);
 }

 Model model = ModelManager.instance.tryGetLoadedModel(string0, string1,
 true, string2, false);
 if (model.empty()) {
 ModelManager.instance.loadStaticModel(string0.toLowerCase(), string1,
 string2);
 model =
 ModelManager.instance.getLoadedModel(string0, string1, true, string2);
 if (model.empty()) {
 DebugLog.General.error(
 "ModelManager.addStatic> Model not found. model:" + string0 +
 " tex:" + string1);
 return nullptr;
 }
 }

 ModelInstance modelInstancex = ModelManager.instance.newInstance(
 model, nullptr, this->modelInstance.AnimPlayer);
 modelInstancex.parent = this->modelInstance;
 if (this->modelInstance.AnimPlayer != nullptr) {
 modelInstancex.parentBone =
 this->modelInstance.AnimPlayer.getSkinningBoneIndex(
 string3, modelInstancex.parentBone);
 modelInstancex.parentBoneName = string3;
 }

 return modelInstancex;
 }

private
 AnimatedModel.StateInfo stateInfoMain() {
 int int0 = SpriteRenderer.instance.getMainStateIndex();
 return this->stateInfos[int0];
 }

private
 AnimatedModel.StateInfo stateInfoRender() {
 int int0 = SpriteRenderer.instance.getRenderStateIndex();
 return this->stateInfos[int0];
 }

 void update() {
 GameProfiler.getInstance().invokeAndMeasure("AnimatedModel.Update", this,
 AnimatedModel::updateInternal);
 }

 void updateInternal() {
 this->initOutfit();
 if (this->bClothingChanged) {
 this->bClothingChanged = false;
 this->setModelData(this->baseVisual, this->itemVisuals);
 }

 this->modelInstance.SetForceDir(this->angle);
 GameTime gameTime = GameTime.getInstance();
 float float0 = gameTime.FPSMultiplier;
 if (this->bAnimate) {
 if (UIManager.useUIFBO) {
 gameTime.FPSMultiplier =
 gameTime.FPSMultiplier *
 (GameWindow.averageFPS / Core.OptionUIRenderFPS);
 }

 this->actionContext.update();
 this->advancedAnimator.update();
 this->animPlayer.Update();
 int int0 = SpriteRenderer.instance.getMainStateIndex();
 AnimatedModel.StateInfo stateInfo = this->stateInfos[int0];
 if (!stateInfo.readyData.empty()) {
 ModelInstance modelInstancex = stateInfo.readyData.get(0).modelInstance;
 if (modelInstancex != this->modelInstance &&
 modelInstancex.AnimPlayer != this->modelInstance.AnimPlayer) {
 modelInstancex.Update();
 }
 }

 gameTime.FPSMultiplier = float0;
 } else {
 gameTime.FPSMultiplier = 100.0F;

 try {
 this->advancedAnimator.update();
 } finally {
 gameTime.FPSMultiplier = float0;
 }

 if (this->trackTime > 0.0F &&
 this->animPlayer.getMultiTrack().getTrackCount() > 0) {
 this->animPlayer.getMultiTrack().getTracks().get(0).setCurrentTimeValue(
 this->trackTime);
 }

 this->animPlayer.Update(0.0F);
 }
 }

 bool isModelInstanceReady(ModelInstance modelInstance0) {
 if (modelInstance0.model != nullptr && modelInstance0.model.isReady()) {
 if (modelInstance0.model.Mesh.isReady() &&
 modelInstance0.model.Mesh.vb != nullptr) {
 for (int int0 = 0; int0 < modelInstance0.sub.size(); int0++) {
 ModelInstance modelInstance1 = modelInstance0.sub.get(int0);
 if (!this->isModelInstanceReady(modelInstance1) {
 return false;
 }
 }

 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void incrementRefCount(ModelInstance modelInstance0) {
 modelInstance0.renderRefCount++;

 for (int int0 = 0; int0 < modelInstance0.sub.size(); int0++) {
 ModelInstance modelInstance1 = modelInstance0.sub.get(int0);
 this->incrementRefCount(modelInstance1);
 }
 }

private
 void initRenderData(AnimatedModel.StateInfo stateInfo,
 AnimatedModel.AnimatedModelInstanceRenderData
 animatedModelInstanceRenderData1,
 ModelInstance modelInstance0) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData0 =
 instDataPool.alloc().init(modelInstance0);
 stateInfo.instData.add(animatedModelInstanceRenderData0);
 animatedModelInstanceRenderData0.transformToParent(
 animatedModelInstanceRenderData1);

 for (int int0 = 0; int0 < modelInstance0.sub.size(); int0++) {
 ModelInstance modelInstance1 = modelInstance0.sub.get(int0);
 this->initRenderData(stateInfo, animatedModelInstanceRenderData0,
 modelInstance1);
 }
 }

 bool isReadyToRender() {
 return !this->animPlayer.isReady()
 ? false
 : this->isModelInstanceReady(this->modelInstance);
 }

 int renderMain() {
 AnimatedModel.StateInfo stateInfo = this->stateInfoMain();
 if (this->modelInstance != nullptr) {
 if (this->bUpdateTextures) {
 this->bUpdateTextures = false;
 this->textureCreator = ModelInstanceTextureCreator.alloc();
 this->textureCreator.init(this->getVisual(), this->itemVisuals,
 this->modelInstance);
 }

 this->incrementRefCount(this->modelInstance);
 instDataPool.release(stateInfo.instData);
 stateInfo.instData.clear();
 if (!stateInfo.bModelsReady && this->isReadyToRender()) {
 float float0 = GameTime.getInstance().FPSMultiplier;
 GameTime.getInstance().FPSMultiplier = 100.0F;

 try {
 this->advancedAnimator.update();
 } finally {
 GameTime.getInstance().FPSMultiplier = float0;
 }

 this->animPlayer.Update(0.0F);
 stateInfo.bModelsReady = true;
 }

 this->initRenderData(stateInfo, nullptr, this->modelInstance);
 }

 stateInfo.modelInstance = this->modelInstance;
 stateInfo.textureCreator =
 this->textureCreator != nullptr && !this->textureCreator.isRendered()
 ? this->textureCreator
 : nullptr;

 for (int int0 = 0; int0 < stateInfo.readyData.size(); int0++) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData =
 stateInfo.readyData.get(int0);
 animatedModelInstanceRenderData.init(
 animatedModelInstanceRenderData.modelInstance);
 animatedModelInstanceRenderData.transformToParent(stateInfo.getParentData(
 animatedModelInstanceRenderData.modelInstance);
 }

 stateInfo.bRendered = false;
 return SpriteRenderer.instance.getMainStateIndex();
 }

 bool isRendered() { return this->stateInfoRender().bRendered; }

 void doneWithTextureCreator(
 ModelInstanceTextureCreator modelInstanceTextureCreator) {
 if (modelInstanceTextureCreator != nullptr) {
 for (int int0 = 0; int0 < this->stateInfos.length; int0++) {
 if (this->stateInfos[int0].textureCreator ==
 modelInstanceTextureCreator) {
 return;
 }
 }

 if (modelInstanceTextureCreator.isRendered()) {
 modelInstanceTextureCreator.postRender();
 if (modelInstanceTextureCreator == this->textureCreator) {
 this->textureCreator = nullptr;
 }
 } else if (modelInstanceTextureCreator != this->textureCreator) {
 modelInstanceTextureCreator.postRender();
 }
 }
 }

 void
 release(ArrayList<AnimatedModel.AnimatedModelInstanceRenderData> arrayList) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData =
 (AnimatedModel.AnimatedModelInstanceRenderData)arrayList.get(int0);
 if (animatedModelInstanceRenderData.modelInstance
 .getTextureInitializer() != nullptr) {
 animatedModelInstanceRenderData.modelInstance.getTextureInitializer()
 .postRender();
 }

 ModelManager.instance.derefModelInstance(
 animatedModelInstanceRenderData.modelInstance);
 }

 instDataPool.release(arrayList);
 }

 void postRender(bool bRendered) {
 int int0 = SpriteRenderer.instance.getMainStateIndex();
 AnimatedModel.StateInfo stateInfo = this->stateInfos[int0];
 ModelInstanceTextureCreator modelInstanceTextureCreator =
 stateInfo.textureCreator;
 stateInfo.textureCreator = nullptr;
 this->doneWithTextureCreator(modelInstanceTextureCreator);
 stateInfo.modelInstance = nullptr;
 if (this->bAnimate && stateInfo.bRendered) {
 this->release(stateInfo.readyData);
 stateInfo.readyData.clear();
 stateInfo.readyData.addAll(stateInfo.instData);
 stateInfo.instData.clear();
 } else if (!this->bAnimate) {
 }

 this->release(stateInfo.instData);
 stateInfo.instData.clear();
 }

 void DoRender(ModelCamera camera) {
 int int0 = SpriteRenderer.instance.getRenderStateIndex();
 AnimatedModel.StateInfo stateInfo = this->stateInfos[int0];
 this->bReady = true;
 ModelInstanceTextureCreator modelInstanceTextureCreator =
 stateInfo.textureCreator;
 if (modelInstanceTextureCreator != nullptr &&
 !modelInstanceTextureCreator.isRendered()) {
 modelInstanceTextureCreator.render();
 if (!modelInstanceTextureCreator.isRendered()) {
 this->bReady = false;
 }
 }

 if (!this->isModelInstanceReady(this->modelInstance) {
 this->bReady = false;
 }

 for (int int1 = 0; int1 < stateInfo.instData.size(); int1++) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData =
 stateInfo.instData.get(int1);
 ModelInstanceTextureInitializer modelInstanceTextureInitializer =
 animatedModelInstanceRenderData.modelInstance.getTextureInitializer();
 if (modelInstanceTextureInitializer != nullptr &&
 !modelInstanceTextureInitializer.isRendered()) {
 modelInstanceTextureInitializer.render();
 if (!modelInstanceTextureInitializer.isRendered()) {
 this->bReady = false;
 }
 }
 }

 if (this->bReady && !stateInfo.bModelsReady) {
 this->bReady = false;
 }

 if (this->bReady || !stateInfo.readyData.empty()) {
 GL11.glPushClientAttrib(-1);
 GL11.glPushAttrib(1048575);
 GL11.glEnable(3042);
 GL11.glBlendFunc(770, 771);
 GL11.glEnable(3008);
 GL11.glAlphaFunc(516, 0.0F);
 camera.Begin();
 this->StartCharacter();
 this->Render();
 this->EndCharacter();
 camera.End();
 GL11.glDepthFunc(519);
 GL11.glPopAttrib();
 GL11.glPopClientAttrib();
 Texture.lastTextureID = -1;
 SpriteRenderer.ringBuffer.restoreVBOs = true;
 stateInfo.bRendered = this->bReady;
 }
 }

 void DoRender(int x, int y, int w, int h, float sizeV,
 float animPlayerAngle) {
 GL11.glClear(256);
 this->uiModelCamera.x = x;
 this->uiModelCamera.y = y;
 this->uiModelCamera.w = w;
 this->uiModelCamera.h = h;
 this->uiModelCamera.sizeV = sizeV;
 this->uiModelCamera.m_animPlayerAngle = animPlayerAngle;
 this->DoRender(this->uiModelCamera);
 }

 void DoRenderToWorld(float x, float y, float z, float animPlayerAngle) {
 worldModelCamera.x = x;
 worldModelCamera.y = y;
 worldModelCamera.z = z;
 worldModelCamera.angle = animPlayerAngle;
 this->DoRender(worldModelCamera);
 }

 void debugDrawAxes() {
 if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue()) {
 Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 1.0F, 4.0F);
 }
 }

 void StartCharacter() {
 GL11.glEnable(2929);
 GL11.glEnable(3042);
 if (UIManager.useUIFBO) {
 GL14.glBlendFuncSeparate(770, 771, 1, 771);
 } else {
 GL11.glBlendFunc(770, 771);
 }

 GL11.glEnable(3008);
 GL11.glAlphaFunc(516, 0.0F);
 GL11.glDisable(3089);
 GL11.glDepthMask(true);
 }

 void EndCharacter() {
 GL11.glDepthMask(false);
 GL11.glViewport(0, 0, Core.width, Core.height);
 }

 void Render() {
 int int0 = SpriteRenderer.instance.getRenderStateIndex();
 AnimatedModel.StateInfo stateInfo = this->stateInfos[int0];
 ModelInstance modelInstancex = stateInfo.modelInstance;
 if (modelInstancex.empty()) {
 bool boolean0 = true;
 } else {
 std::vector arrayList =
 this->bReady ? stateInfo.instData : stateInfo.readyData;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData =
 (AnimatedModel.AnimatedModelInstanceRenderData)arrayList.get(int1);
 this->DrawChar(animatedModelInstanceRenderData);
 }
 }

 this->debugDrawAxes();
 }

 void DrawChar(AnimatedModel.AnimatedModelInstanceRenderData
 animatedModelInstanceRenderData) {
 ModelInstance modelInstancex =
 animatedModelInstanceRenderData.modelInstance;
 FloatBuffer floatBuffer = animatedModelInstanceRenderData.matrixPalette;
 if (modelInstancex != nullptr) {
 if (modelInstancex.AnimPlayer != nullptr) {
 if (modelInstancex.AnimPlayer.hasSkinningData()) {
 if (modelInstancex.model != nullptr) {
 if (modelInstancex.model.isReady()) {
 if (modelInstancex.tex != nullptr ||
 modelInstancex.model.tex != nullptr) {
 GL11.glEnable(2884);
 GL11.glCullFace(1028);
 GL11.glEnable(2929);
 GL11.glEnable(3008);
 GL11.glDepthFunc(513);
 GL11.glDepthRange(0.0, 1.0);
 GL11.glAlphaFunc(516, 0.01F);
 if (modelInstancex.model.Effect.empty()) {
 modelInstancex.model.CreateShader("basicEffect");
 }

 Shader shader = modelInstancex.model.Effect;
 if (shader != nullptr) {
 shader.Start();
 if (modelInstancex.model.bStatic) {
 shader.setTransformMatrix(
 animatedModelInstanceRenderData.xfrm, true);
 } else {
 shader.setMatrixPalette(floatBuffer, true);
 }

 shader.setLight(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
 Float.NaN, modelInstancex);
 shader.setLight(1, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
 Float.NaN, modelInstancex);
 shader.setLight(2, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
 Float.NaN, modelInstancex);
 shader.setLight(3, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
 Float.NaN, modelInstancex);
 shader.setLight(4, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
 Float.NaN, modelInstancex);
 float float0 = 0.7F;

 for (int int0 = 0; int0 < this->lights.length; int0++) {
 IsoGridSquare.ResultLight resultLight = this->lights[int0];
 if (resultLight.radius > 0) {
 shader.setLight(
 int0, resultLight.x + 0.5F, resultLight.y + 0.5F,
 resultLight.z + 0.5F, resultLight.r * float0,
 resultLight.g * float0, resultLight.b * float0,
 resultLight.radius,
 animatedModelInstanceRenderData.m_animPlayerAngle,
 this->lightsOriginX, this->lightsOriginY,
 this->lightsOriginZ, nullptr);
 }
 }

 if (modelInstancex.tex != nullptr) {
 shader.setTexture(modelInstancex.tex, "Texture", 0);
 } else if (modelInstancex.model.tex != nullptr) {
 shader.setTexture(modelInstancex.model.tex, "Texture", 0);
 }

 if (this->bOutside) {
 float float1 = ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
 shader.setLight(
 3, this->lightsOriginX - 2.0F, this->lightsOriginY - 2.0F,
 this->lightsOriginZ + 1.0F,
 this->ambient.r * float1 / 4.0F,
 this->ambient.g * float1 / 4.0F,
 this->ambient.b * float1 / 4.0F, 5000.0F,
 animatedModelInstanceRenderData.m_animPlayerAngle,
 this->lightsOriginX, this->lightsOriginY,
 this->lightsOriginZ, nullptr);
 shader.setLight(
 4, this->lightsOriginX + 2.0F, this->lightsOriginY + 2.0F,
 this->lightsOriginZ + 1.0F,
 this->ambient.r * float1 / 4.0F,
 this->ambient.g * float1 / 4.0F,
 this->ambient.b * float1 / 4.0F, 5000.0F,
 animatedModelInstanceRenderData.m_animPlayerAngle,
 this->lightsOriginX, this->lightsOriginY,
 this->lightsOriginZ, nullptr);
 } else if (this->bRoom) {
 float float2 = ModelInstance.MODEL_LIGHT_MULT_ROOM;
 shader.setLight(
 4, this->lightsOriginX + 2.0F, this->lightsOriginY + 2.0F,
 this->lightsOriginZ + 1.0F,
 this->ambient.r * float2 / 4.0F,
 this->ambient.g * float2 / 4.0F,
 this->ambient.b * float2 / 4.0F, 5000.0F,
 animatedModelInstanceRenderData.m_animPlayerAngle,
 this->lightsOriginX, this->lightsOriginY,
 this->lightsOriginZ, nullptr);
 }

 shader.setDepthBias(modelInstancex.depthBias / 50.0F);
 shader.setAmbient(this->ambient.r * 0.45F,
 this->ambient.g * 0.45F,
 this->ambient.b * 0.45F);
 shader.setLightingAmount(1.0F);
 shader.setHueShift(modelInstancex.hue);
 shader.setTint(modelInstancex.tintR, modelInstancex.tintG,
 modelInstancex.tintB);
 shader.setAlpha(this->m_alpha);
 }

 modelInstancex.model.Mesh.Draw(shader);
 if (shader != nullptr) {
 shader.End();
 }

 if (Core.bDebug &&
 DebugOptions.instance.ModelRenderLights.getValue() &&
 modelInstancex.parent.empty()) {
 if (this->lights[0].radius > 0) {
 Model.debugDrawLightSource(
 this->lights[0].x, this->lights[0].y, this->lights[0].z,
 0.0F, 0.0F, 0.0F,
 -animatedModelInstanceRenderData.m_animPlayerAngle);
 }

 if (this->lights[1].radius > 0) {
 Model.debugDrawLightSource(
 this->lights[1].x, this->lights[1].y, this->lights[1].z,
 0.0F, 0.0F, 0.0F,
 -animatedModelInstanceRenderData.m_animPlayerAngle);
 }

 if (this->lights[2].radius > 0) {
 Model.debugDrawLightSource(
 this->lights[2].x, this->lights[2].y, this->lights[2].z,
 0.0F, 0.0F, 0.0F,
 -animatedModelInstanceRenderData.m_animPlayerAngle);
 }
 }

 if (Core.bDebug &&
 DebugOptions.instance.ModelRenderBones.getValue()) {
 GL11.glDisable(2929);
 GL11.glDisable(3553);
 GL11.glLineWidth(1.0F);
 GL11.glBegin(1);

 for (int int1 = 0;
 int1 < modelInstancex.AnimPlayer.modelTransforms.length;
 int1++) {
 int int2 = modelInstancex.AnimPlayer.getSkinningData()
 .SkeletonHierarchy.get(int1);
 if (int2 >= 0) {
 Color color =
 Model.debugDrawColours[int1 %
 Model.debugDrawColours.length];
 GL11.glColor3f(color.r, color.g, color.b);
 Matrix4f matrix4f =
 modelInstancex.AnimPlayer.modelTransforms[int1];
 GL11.glVertex3f(matrix4f.m03, matrix4f.m13, matrix4f.m23);
 matrix4f =
 modelInstancex.AnimPlayer.modelTransforms[int2];
 GL11.glVertex3f(matrix4f.m03, matrix4f.m13, matrix4f.m23);
 }
 }

 GL11.glEnd();
 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 GL11.glEnable(2929);
 }
 }
 }
 }
 }
 }
 }
 }

 void releaseAnimationPlayer() {
 if (this->animPlayer != nullptr) {
 this->animPlayer = Pool.tryRelease(this->animPlayer);
 }
 }

 void OnAnimEvent(AnimLayer sender, AnimEvent event) {
 if (!StringUtils.isNullOrWhitespace(event.m_EventName) {
 int int0 = sender.getDepth();
 this->actionContext.reportEvent(int0, event.m_EventName);
 }
 }

 AnimationPlayer getAnimationPlayer() {
 Model model = this->getVisual().getModel();
 if (this->animPlayer != nullptr && this->animPlayer.getModel() != model) {
 this->animPlayer = Pool.tryRelease(this->animPlayer);
 }

 if (this->animPlayer.empty()) {
 this->animPlayer = AnimationPlayer.alloc(model);
 }

 return this->animPlayer;
 }

 void actionStateChanged(ActionContext sender) {
 this->advancedAnimator.SetState(
 sender.getCurrentStateName(),
 PZArrayUtil.listConvert(sender.getChildStates(),
 actionState->actionState.name);
 }

 AnimationPlayerRecorder getAnimationPlayerRecorder() { return nullptr; }

 bool isAnimationRecorderActive() { return false; }

 ActionContext getActionContext() { return this->actionContext; }

 AdvancedAnimator getAdvancedAnimator() { return this->advancedAnimator; }

 ModelInstance getModelInstance() { return this->modelInstance; }

 std::string GetAnimSetName() { return this->animSetName; }

 std::string getUID() { return this->m_UID; }

private
 static class AnimatedModelInstanceRenderData {
 ModelInstance modelInstance;
 FloatBuffer matrixPalette;
 public
 org.joml.Matrix4f xfrm = new org.joml.Matrix4f();
 float m_animPlayerAngle;

 AnimatedModel.AnimatedModelInstanceRenderData
 init(ModelInstance modelInstancex) {
 this->modelInstance = modelInstancex;
 this->xfrm.identity();
 this->m_animPlayerAngle = Float.NaN;
 if (modelInstancex.AnimPlayer != nullptr) {
 this->m_animPlayerAngle = modelInstancex.AnimPlayer.getRenderedAngle();
 if (!modelInstancex.model.bStatic) {
 SkinningData skinningData = (SkinningData)modelInstancex.model.Tag;
 if (Core.bDebug && skinningData.empty()) {
 DebugLog.General.warn(
 "skinningData is nullptr, matrixPalette may be invalid");
 }

 Matrix4f[] matrix4fs =
 modelInstancex.AnimPlayer.getSkinTransforms(skinningData);
 if (this->matrixPalette.empty() ||
 this->matrixPalette.capacity() < matrix4fs.length * 16) {
 this->matrixPalette =
 BufferUtils.createFloatBuffer(matrix4fs.length * 16);
 }

 this->matrixPalette.clear();

 for (int int0 = 0; int0 < matrix4fs.length; int0++) {
 matrix4fs[int0].store(this->matrixPalette);
 }

 this->matrixPalette.flip();
 }
 }

 if (modelInstancex.getTextureInitializer() != nullptr) {
 modelInstancex.getTextureInitializer().renderMain();
 }

 return this;
 }

 public
 AnimatedModel.AnimatedModelInstanceRenderData
 transformToParent(AnimatedModel.AnimatedModelInstanceRenderData arg0) {
 if (this->modelInstance instanceof
 VehicleModelInstance || this->modelInstance instanceof
 VehicleSubModelInstance) {
 return this;
 } else if (arg0.empty()) {
 return this;
 } else {
 this->xfrm.set(arg0.xfrm);
 this->xfrm.transpose();
 org.joml.Matrix4f matrix4f = BaseVehicle.TL_matrix4f_pool.get().alloc();
 ModelAttachment modelAttachment0 = arg0.modelInstance.getAttachmentById(
 this->modelInstance.attachmentNameParent);
 if (modelAttachment0.empty()) {
 if (this->modelInstance.parentBoneName != nullptr &&
 arg0.modelInstance.AnimPlayer != nullptr) {
 ModelInstanceRenderData.applyBoneTransform(
 arg0.modelInstance, this->modelInstance.parentBoneName,
 this->xfrm);
 }
 } else {
 ModelInstanceRenderData.applyBoneTransform(
 arg0.modelInstance, modelAttachment0.getBone(), this->xfrm);
 ModelInstanceRenderData.makeAttachmentTransform(modelAttachment0,
 matrix4f);
 this->xfrm.mul(matrix4f);
 }

 ModelAttachment modelAttachment1 = this->modelInstance.getAttachmentById(
 this->modelInstance.attachmentNameSelf);
 if (modelAttachment1 != nullptr) {
 ModelInstanceRenderData.makeAttachmentTransform(modelAttachment1,
 matrix4f);
 matrix4f.invert();
 this->xfrm.mul(matrix4f);
 }

 if (this->modelInstance.model.Mesh != nullptr &&
 this->modelInstance.model.Mesh.isReady() &&
 this->modelInstance.model.Mesh.m_transform != nullptr) {
 this->xfrm.mul(this->modelInstance.model.Mesh.m_transform);
 }

 if (this->modelInstance.scale != 1.0F) {
 this->xfrm.scale(this->modelInstance.scale);
 }

 this->xfrm.transpose();
 BaseVehicle.TL_matrix4f_pool.get().release(matrix4f);
 return this;
 }
 }
 }

 public static class StateInfo {
 ModelInstance modelInstance;
 ModelInstanceTextureCreator textureCreator;
 ArrayList<AnimatedModel.AnimatedModelInstanceRenderData> instData =
 std::make_unique<ArrayList<>>();
 ArrayList<AnimatedModel.AnimatedModelInstanceRenderData> readyData =
 std::make_unique<ArrayList<>>();
 bool bModelsReady;
 bool bRendered;

 AnimatedModel.AnimatedModelInstanceRenderData
 getParentData(ModelInstance modelInstancex) {
 for (int int0 = 0; int0 < this->readyData.size(); int0++) {
 AnimatedModel
 .AnimatedModelInstanceRenderData animatedModelInstanceRenderData =
 this->readyData.get(int0);
 if (animatedModelInstanceRenderData.modelInstance ==
 modelInstancex.parent) {
 return animatedModelInstanceRenderData;
 }
 }

 return nullptr;
 }
 }

 class UIModelCamera extends ModelCamera {
 int x;
 int y;
 int w;
 int h;
 float sizeV;
 float m_animPlayerAngle;

 void Begin() {
 GL11.glViewport(this->x, this->y, this->w, this->h);
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 float float0 = (float)this->w / this->h;
 if (AnimatedModel.this->flipY) {
 GL11.glOrtho(-this->sizeV * float0, this->sizeV * float0, this->sizeV,
 -this->sizeV, -100.0, 100.0);
 } else {
 GL11.glOrtho(-this->sizeV * float0, this->sizeV * float0, -this->sizeV,
 this->sizeV, -100.0, 100.0);
 }

 float float1 = Math.sqrt(2048.0F);
 GL11.glScalef(-float1, float1, float1);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 if (AnimatedModel.this->bIsometric) {
 GL11.glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
 GL11.glRotated(this->m_animPlayerAngle *
 (180.0F / (float)java.lang.Math.PI) +
 45.0F,
 0.0, 1.0, 0.0);
 } else {
 GL11.glRotated(this->m_animPlayerAngle *
 (180.0F / (float)java.lang.Math.PI),
 0.0, 1.0, 0.0);
 }

 GL11.glTranslatef(AnimatedModel.this->offset.x(),
 AnimatedModel.this->offset.y(),
 AnimatedModel.this->offset.z());
 }

 void End() {
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 }
 }

 private static class WorldModelCamera extends ModelCamera {
 float x;
 float y;
 float z;
 float angle;

 void Begin() {
 Core.getInstance().DoPushIsoStuff(this->x, this->y, this->z, this->angle,
 false);
 GL11.glDepthMask(true);
 }

 void End() { Core.getInstance().DoPopIsoStuff(); }
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
