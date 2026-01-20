#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL14.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
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
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel/AnimatedModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel/StateInfo.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel/UIModelCamera.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel/WorldModelCamera.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureInitializer.h"
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
#include "zombie/iso/IsoGridSquare/ResultLight.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimatedModel : public AnimationVariableSource {
public:
    std::string animSetName = "player-avatar";
    std::string outfitName;
    IsoGameCharacter character;
    HumanVisual baseVisual = nullptr;
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    std::string primaryHandModelName;
    std::string secondaryHandModelName;
    const AttachedModelNames attachedModelNames = std::make_shared<AttachedModelNames>();
    ModelInstance modelInstance;
    bool bFemale = false;
    bool bZombie = false;
    bool bSkeleton = false;
    std::string state;
    const Vector2 angle = std::make_shared<Vector2>();
    const Vector3f offset = std::make_shared<Vector3f>(0.0F, -0.45F, 0.0F);
    bool bIsometric = true;
    bool flipY = false;
    float m_alpha = 1.0F;
    AnimationPlayer animPlayer = nullptr;
    const ActionContext actionContext = std::make_shared<ActionContext>(this);
    const AdvancedAnimator advancedAnimator = std::make_shared<AdvancedAnimator>();
    float trackTime = 0.0F;
    const std::string m_UID;
    float lightsOriginX;
    float lightsOriginY;
    float lightsOriginZ;
   private const ResultLight[] lights = new ResultLight[5];
    const ColorInfo ambient = std::make_shared<ColorInfo>();
    bool bOutside = true;
    bool bRoom = false;
    bool bUpdateTextures;
    bool bClothingChanged;
    bool bAnimate = true;
    ModelInstanceTextureCreator textureCreator;
   private const StateInfo[] stateInfos = new StateInfo[3];
    bool bReady;
   private static const ObjectPool<AnimatedModelInstanceRenderData> instDataPool = std::make_shared<ObjectPool>(AnimatedModelInstanceRenderData::new);
    const UIModelCamera uiModelCamera = std::make_shared<UIModelCamera>(this);
    static const WorldModelCamera worldModelCamera = std::make_shared<WorldModelCamera>();

    public AnimatedModel() {
      this.m_UID = std::string.format("%s-%s", this.getClass().getSimpleName(), UUID.randomUUID());
      this.advancedAnimator.init(this);
      this.advancedAnimator.animCallbackHandlers.push_back(this);
      this.actionContext.onStateChanged.push_back(this);

      for (int var1 = 0; var1 < this.lights.length; var1++) {
         this.lights[var1] = std::make_unique<ResultLight>();
      }

      for (int var2 = 0; var2 < this.stateInfos.length; var2++) {
         this.stateInfos[var2] = std::make_unique<StateInfo>();
      }
   }

    void setVisual(HumanVisual var1) {
      this.baseVisual = var1;
   }

    BaseVisual getVisual() {
      return this.baseVisual;
   }

    HumanVisual getHumanVisual() {
      return (HumanVisual)Type.tryCastTo(this.baseVisual, HumanVisual.class);
   }

    void getItemVisuals(ItemVisuals var1) {
      var1.clear();
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
      return this.bZombie;
   }

    bool isSkeleton() {
      return this.bSkeleton;
   }

    void setAnimSetName(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         throw IllegalArgumentException("invalid AnimSet \"" + var1 + "\"");
      } else {
         this.animSetName = var1;
      }
   }

    void setOutfitName(const std::string& var1, bool var2, bool var3) {
      this.outfitName = var1;
      this.bFemale = var2;
      this.bZombie = var3;
   }

    void setCharacter(IsoGameCharacter var1) {
      this.outfitName = nullptr;
      if (this.baseVisual != nullptr) {
         this.baseVisual.clear();
      }

      this.itemVisuals.clear();
      if (dynamic_cast<IHumanVisual*>(var1) != nullptr) {
         var1.getItemVisuals(this.itemVisuals);
         this.character = var1;
         if (var1.getAttachedItems() != nullptr) {
            this.attachedModelNames.initFrom(var1.getAttachedItems());
         }

         this.setModelData(((IHumanVisual)var1).getHumanVisual(), this.itemVisuals);
      }
   }

    void setSurvivorDesc(SurvivorDesc var1) {
      this.outfitName = nullptr;
      if (this.baseVisual != nullptr) {
         this.baseVisual.clear();
      }

      this.itemVisuals.clear();
      var1.getWornItems().getItemVisuals(this.itemVisuals);
      this.attachedModelNames.clear();
      this.setModelData(var1.getHumanVisual(), this.itemVisuals);
   }

    void setPrimaryHandModelName(const std::string& var1) {
      this.primaryHandModelName = var1;
   }

    void setSecondaryHandModelName(const std::string& var1) {
      this.secondaryHandModelName = var1;
   }

    void setAttachedModelNames(AttachedModelNames var1) {
      this.attachedModelNames.copyFrom(var1);
   }

    void setModelData(HumanVisual var1, ItemVisuals var2) {
    AnimationPlayer var3 = this.animPlayer;
    Model var4 = this.animPlayer == nullptr ? nullptr : var3.getModel();
      if (this.baseVisual != var1) {
         if (this.baseVisual == nullptr) {
            this.baseVisual = std::make_shared<HumanVisual>(this);
         }

         this.baseVisual.copyFrom(var1);
      }

      if (this.itemVisuals != var2) {
         this.itemVisuals.clear();
         this.itemVisuals.addAll(var2);
      }

      if (this.baseVisual != var1) {
         this.bFemale = false;
         this.bZombie = false;
         this.bSkeleton = false;
         if (var1 != nullptr) {
            this.bFemale = var1.isFemale();
            this.bZombie = var1.isZombie();
            this.bSkeleton = var1.isSkeleton();
         }
      }

      if (this.modelInstance != nullptr) {
         ModelManager.instance.resetModelInstanceRecurse(this.modelInstance, this);
      }

    Model var5 = var1.getModel();
      this.getAnimationPlayer().setModel(var5);
      this.modelInstance = ModelManager.instance.newInstance(var5, nullptr, this.getAnimationPlayer());
      this.modelInstance.m_modelScript = var1.getModelScript();
      this.modelInstance.setOwner(this);
      this.populateCharacterModelSlot();
      this.DoCharacterModelEquipped();
    bool var6 = false;
      if (this.bAnimate) {
    AnimationSet var7 = AnimationSet.GetAnimationSet(this.GetAnimSetName(), false);
         if (var7 != this.advancedAnimator.animSet || var3 != this.getAnimationPlayer() || var4 != var5) {
            var6 = true;
         }
      } else {
         var6 = true;
      }

      if (var6) {
         this.advancedAnimator.OnAnimDataChanged(false);
      }

      if (this.bAnimate) {
    ActionGroup var11 = ActionGroup.getActionGroup(this.GetAnimSetName());
         if (var11 != this.actionContext.getGroup()) {
            this.actionContext.setGroup(var11);
         }

         this.advancedAnimator
            .SetState(this.actionContext.getCurrentStateName(), PZArrayUtil.listConvert(this.actionContext.getChildStates(), var0 -> var0.name));
      } else if (!StringUtils.isNullOrWhitespace(this.state)) {
         this.advancedAnimator.SetState(this.state);
      }

      if (var6) {
    float var12 = GameTime.getInstance().FPSMultiplier;
         GameTime.getInstance().FPSMultiplier = 100.0F;

         try {
            this.advancedAnimator.update();
         } finally {
            GameTime.getInstance().FPSMultiplier = var12;
         }
      }

      if (Core.bDebug && !this.bAnimate && this.stateInfoMain().readyData.empty()) {
         this.getAnimationPlayer().resetBoneModelTransforms();
      }

      this.trackTime = 0.0F;
      this.stateInfoMain().bModelsReady = this.isReadyToRender();
   }

    void setAmbient(ColorInfo var1, bool var2, bool var3) {
      this.ambient.set(var1.r, var1.g, var1.b, 1.0F);
      this.bOutside = var2;
      this.bRoom = var3;
   }

    void setLights(ResultLight[] var1, float var2, float var3, float var4) {
      this.lightsOriginX = var2;
      this.lightsOriginY = var3;
      this.lightsOriginZ = var4;

      for (int var5 = 0; var5 < var1.length; var5++) {
         this.lights[var5].copyFrom(var1[var5]);
      }
   }

    void setState(const std::string& var1) {
      this.state = var1;
   }

    std::string getState() {
      return this.state;
   }

    void setAngle(Vector2 var1) {
      this.angle.set(var1);
   }

    void setOffset(float var1, float var2, float var3) {
      this.offset.set(var1, var2, var3);
   }

    void setIsometric(bool var1) {
      this.bIsometric = var1;
   }

    bool isIsometric() {
      return this.bIsometric;
   }

    void setFlipY(bool var1) {
      this.flipY = var1;
   }

    void setAlpha(float var1) {
      this.m_alpha = var1;
   }

    void setTrackTime(float var1) {
      this.trackTime = var1;
   }

    void clothingItemChanged(const std::string& var1) {
      this.bClothingChanged = true;
   }

    void setAnimate(bool var1) {
      this.bAnimate = var1;
   }

    void initOutfit() {
    std::string var1 = this.outfitName;
      this.outfitName = nullptr;
      if (!StringUtils.isNullOrWhitespace(var1)) {
         ModelManager.instance.create();
         this.baseVisual.dressInNamedOutfit(var1, this.itemVisuals);
         this.setModelData(this.baseVisual, this.itemVisuals);
      }
   }

    void populateCharacterModelSlot() {
    HumanVisual var1 = this.getHumanVisual();
      if (var1 == nullptr) {
         this.bUpdateTextures = true;
      } else {
    CharacterMask var2 = HumanVisual.GetMask(this.itemVisuals);
         if (var2.isPartVisible(Part.Head)) {
            this.addHeadHair(this.itemVisuals.findHat());
         }

         for (int var3 = this.itemVisuals.size() - 1; var3 >= 0; var3--) {
    ItemVisual var4 = (ItemVisual)this.itemVisuals.get(var3);
    ClothingItem var5 = var4.getClothingItem();
            if (var5 != nullptr && var5.isReady() && !this.isItemModelHidden(this.itemVisuals, var4)) {
               this.addClothingItem(var4, var5);
            }
         }

         for (int var6 = var1.getBodyVisuals().size() - 1; var6 >= 0; var6--) {
    ItemVisual var7 = (ItemVisual)var1.getBodyVisuals().get(var6);
    ClothingItem var8 = var7.getClothingItem();
            if (var8 != nullptr && var8.isReady()) {
               this.addClothingItem(var7, var8);
            }
         }

         this.bUpdateTextures = true;
         Lambda.forEachFrom(PZArrayUtil::forEach, this.modelInstance.sub, this.modelInstance, (var0, var1x) -> var0.AnimPlayer = var1x.AnimPlayer);
      }
   }

    void addHeadHair(ItemVisual var1) {
    HumanVisual var2 = this.getHumanVisual();
    ImmutableColor var3 = var2.getHairColor();
    ImmutableColor var4 = var2.getBeardColor();
      if (this.isFemale()) {
    HairStyle var5 = HairStyles.instance.FindFemaleStyle(var2.getHairModel());
         if (var5 != nullptr && var1 != nullptr && var1.getClothingItem() != nullptr) {
            var5 = HairStyles.instance.getAlternateForHat(var5, var1.getClothingItem().m_HatCategory);
         }

         if (var5 != nullptr && var5.isValid()) {
            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.debugln("  Adding female hair: " + var5.name);
            }

            this.addHeadHairItem(var5.model, var5.texture, var3);
         }
      } else {
    HairStyle var7 = HairStyles.instance.FindMaleStyle(var2.getHairModel());
         if (var7 != nullptr && var1 != nullptr && var1.getClothingItem() != nullptr) {
            var7 = HairStyles.instance.getAlternateForHat(var7, var1.getClothingItem().m_HatCategory);
         }

         if (var7 != nullptr && var7.isValid()) {
            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.debugln("  Adding male hair: " + var7.name);
            }

            this.addHeadHairItem(var7.model, var7.texture, var3);
         }

    BeardStyle var6 = BeardStyles.instance.FindStyle(var2.getBeardModel());
         if (var6 != nullptr && var6.isValid()) {
            if (var1 != nullptr
               && var1.getClothingItem() != nullptr
               && !StringUtils.isNullOrEmpty(var1.getClothingItem().m_HatCategory)
               && var1.getClothingItem().m_HatCategory.contains("nobeard")) {
               return;
            }

            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.debugln("  Adding beard: " + var6.name);
            }

            this.addHeadHairItem(var6.model, var6.texture, var4);
         }
      }
   }

    void addHeadHairItem(const std::string& var1, const std::string& var2, ImmutableColor var3) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         if (DebugLog.isEnabled(DebugType.Clothing)) {
            DebugLog.Clothing.warn("No model specified.");
         }
      } else {
         var1 = this.processModelFileName(var1);
    ModelInstance var4 = ModelManager.instance.newAdditionalModelInstance(var1, var2, nullptr, this.modelInstance.AnimPlayer, nullptr);
         if (var4 != nullptr) {
            this.postProcessNewItemInstance(this.modelInstance, var4, var3);
         }
      }
   }

    void addClothingItem(ItemVisual var1, ClothingItem var2) {
    std::string var3 = var2.getModel(this.bFemale);
      if (StringUtils.isNullOrWhitespace(var3)) {
         if (DebugLog.isEnabled(DebugType.Clothing)) {
            DebugLog.Clothing.debugln("No model specified by item: " + var2.m_Name);
         }
      } else {
         var3 = this.processModelFileName(var3);
    std::string var4 = var1.getTextureChoice(var2);
    ImmutableColor var5 = var1.getTint(var2);
    std::string var6 = var2.m_AttachBone;
    std::string var7 = var2.m_Shader;
    ModelInstance var8;
         if (var6 != nullptr && var6.length() > 0) {
            var8 = this.addStatic(var3, var4, var6, var7);
         } else {
            var8 = ModelManager.instance.newAdditionalModelInstance(var3, var4, nullptr, this.modelInstance.AnimPlayer, var7);
         }

         if (var8 != nullptr) {
            this.postProcessNewItemInstance(this.modelInstance, var8, var5);
            var8.setItemVisual(var1);
         }
      }
   }

    bool isItemModelHidden(ItemVisuals var1, ItemVisual var2) {
    BodyLocationGroup var3 = BodyLocations.getGroup("Human");
      return PopTemplateManager.instance.isItemModelHidden(var3, var1, var2);
   }

    std::string processModelFileName(const std::string& var1) {
      var1 = var1.replaceAll("\\\\", "/");
      return var1.toLowerCase(Locale.ENGLISH);
   }

    void postProcessNewItemInstance(ModelInstance var1, ModelInstance var2, ImmutableColor var3) {
      var2.depthBias = 0.0F;
      var2.matrixModel = this.modelInstance;
      var2.tintR = var3.r;
      var2.tintG = var3.g;
      var2.tintB = var3.b;
      var2.AnimPlayer = this.modelInstance.AnimPlayer;
      var1.sub.push_back(var2);
      var2.setOwner(this);
   }

    void DoCharacterModelEquipped() {
      if (!StringUtils.isNullOrWhitespace(this.primaryHandModelName)) {
    ModelInstance var1 = this.addStatic(this.primaryHandModelName, "Bip01_Prop1");
         this.postProcessNewItemInstance(this.modelInstance, var1, ImmutableColor.white);
      }

      if (!StringUtils.isNullOrWhitespace(this.secondaryHandModelName)) {
    ModelInstance var7 = this.addStatic(this.secondaryHandModelName, "Bip01_Prop2");
         this.postProcessNewItemInstance(this.modelInstance, var7, ImmutableColor.white);
      }

      for (int var8 = 0; var8 < this.attachedModelNames.size(); var8++) {
    AttachedModelName var2 = this.attachedModelNames.get(var8);
    ModelInstance var3 = ModelManager.instance.addStatic(nullptr, var2.modelName, var2.attachmentNameSelf, var2.attachmentNameParent);
         this.postProcessNewItemInstance(this.modelInstance, var3, ImmutableColor.white);
         if (var2.bloodLevel > 0.0F && !Core.getInstance().getOptionSimpleWeaponTextures()) {
    ModelInstanceTextureInitializer var4 = ModelInstanceTextureInitializer.alloc();
            var4.init(var3, var2.bloodLevel);
            var3.setTextureInitializer(var4);
         }

         for (int var9 = 0; var9 < var2.getChildCount(); var9++) {
    AttachedModelName var5 = var2.getChildByIndex(var9);
    ModelInstance var6 = ModelManager.instance.addStatic(var3, var5.modelName, var5.attachmentNameSelf, var5.attachmentNameParent);
            var3.sub.remove(var6);
            this.postProcessNewItemInstance(var3, var6, ImmutableColor.white);
         }
      }
   }

    ModelInstance addStatic(const std::string& var1, const std::string& var2) {
    std::string var3 = var1;
    std::string var4 = var1;
    std::string var5 = nullptr;
    ModelScript var6 = ScriptManager.instance.getModelScript(var1);
      if (var6 != nullptr) {
         var3 = var6.getMeshName();
         var4 = var6.getTextureName();
         var5 = var6.getShaderName();
      }

      return this.addStatic(var3, var4, var2, var5);
   }

    ModelInstance addStatic(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      if (DebugLog.isEnabled(DebugType.Animation)) {
         DebugLog.Animation.debugln("Adding Static Model:" + var1);
      }

    Model var5 = ModelManager.instance.tryGetLoadedModel(var1, var2, true, var4, false);
      if (var5 == nullptr) {
         ModelManager.instance.loadStaticModel(var1.toLowerCase(), var2, var4);
         var5 = ModelManager.instance.getLoadedModel(var1, var2, true, var4);
         if (var5 == nullptr) {
            DebugLog.General.error("ModelManager.addStatic> Model not found. model:" + var1 + " tex:" + var2);
    return nullptr;
         }
      }

    ModelInstance var6 = ModelManager.instance.newInstance(var5, nullptr, this.modelInstance.AnimPlayer);
      var6.parent = this.modelInstance;
      if (this.modelInstance.AnimPlayer != nullptr) {
         var6.parentBone = this.modelInstance.AnimPlayer.getSkinningBoneIndex(var3, var6.parentBone);
         var6.parentBoneName = var3;
      }

    return var6;
   }

    StateInfo stateInfoMain() {
    int var1 = SpriteRenderer.instance.getMainStateIndex();
      return this.stateInfos[var1];
   }

    StateInfo stateInfoRender() {
    int var1 = SpriteRenderer.instance.getRenderStateIndex();
      return this.stateInfos[var1];
   }

    void update() {
      GameProfiler.getInstance().invokeAndMeasure("AnimatedModel.Update", this, AnimatedModel::updateInternal);
   }

    void updateInternal() {
      this.initOutfit();
      if (this.bClothingChanged) {
         this.bClothingChanged = false;
         this.setModelData(this.baseVisual, this.itemVisuals);
      }

      this.modelInstance.SetForceDir(this.angle);
    GameTime var1 = GameTime.getInstance();
    float var2 = var1.FPSMultiplier;
      if (this.bAnimate) {
         if (UIManager.useUIFBO) {
            var1.FPSMultiplier = var1.FPSMultiplier * (GameWindow.averageFPS / Core.OptionUIRenderFPS);
         }

         this.actionContext.update();
         this.advancedAnimator.update();
         this.animPlayer.Update();
    int var3 = SpriteRenderer.instance.getMainStateIndex();
    StateInfo var4 = this.stateInfos[var3];
         if (!var4.readyData.empty()) {
    ModelInstance var5 = ((AnimatedModelInstanceRenderData)var4.readyData.get(0)).modelInstance;
            if (var5 != this.modelInstance && var5.AnimPlayer != this.modelInstance.AnimPlayer) {
               var5.Update();
            }
         }

         var1.FPSMultiplier = var2;
      } else {
         var1.FPSMultiplier = 100.0F;

         try {
            this.advancedAnimator.update();
         } finally {
            var1.FPSMultiplier = var2;
         }

         if (this.trackTime > 0.0F && this.animPlayer.getMultiTrack().getTrackCount() > 0) {
            ((AnimationTrack)this.animPlayer.getMultiTrack().getTracks().get(0)).setCurrentTimeValue(this.trackTime);
         }

         this.animPlayer.Update(0.0F);
      }
   }

    bool isModelInstanceReady(ModelInstance var1) {
      if (var1.model != nullptr && var1.model.isReady()) {
         if (var1.model.Mesh.isReady() && var1.model.Mesh.vb != nullptr) {
            for (int var2 = 0; var2 < var1.sub.size(); var2++) {
    ModelInstance var3 = (ModelInstance)var1.sub.get(var2);
               if (!this.isModelInstanceReady(var3)) {
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

    void incrementRefCount(ModelInstance var1) {
      var1.renderRefCount++;

      for (int var2 = 0; var2 < var1.sub.size(); var2++) {
    ModelInstance var3 = (ModelInstance)var1.sub.get(var2);
         this.incrementRefCount(var3);
      }
   }

    void initRenderData(StateInfo var1, AnimatedModelInstanceRenderData var2, ModelInstance var3) {
    AnimatedModelInstanceRenderData var4 = ((AnimatedModelInstanceRenderData)instDataPool.alloc()).init(var3);
      var1.instData.push_back(var4);
      var4.transformToParent(var2);

      for (int var5 = 0; var5 < var3.sub.size(); var5++) {
    ModelInstance var6 = (ModelInstance)var3.sub.get(var5);
         this.initRenderData(var1, var4, var6);
      }
   }

    bool isReadyToRender() {
      return !this.animPlayer.isReady() ? false : this.isModelInstanceReady(this.modelInstance);
   }

    int renderMain() {
    StateInfo var1 = this.stateInfoMain();
      if (this.modelInstance != nullptr) {
         if (this.bUpdateTextures) {
            this.bUpdateTextures = false;
            this.textureCreator = ModelInstanceTextureCreator.alloc();
            this.textureCreator.init(this.getVisual(), this.itemVisuals, this.modelInstance);
         }

         this.incrementRefCount(this.modelInstance);
         instDataPool.release(var1.instData);
         var1.instData.clear();
         if (!var1.bModelsReady && this.isReadyToRender()) {
    float var2 = GameTime.getInstance().FPSMultiplier;
            GameTime.getInstance().FPSMultiplier = 100.0F;

            try {
               this.advancedAnimator.update();
            } finally {
               GameTime.getInstance().FPSMultiplier = var2;
            }

            this.animPlayer.Update(0.0F);
            var1.bModelsReady = true;
         }

         this.initRenderData(var1, nullptr, this.modelInstance);
      }

      var1.modelInstance = this.modelInstance;
      var1.textureCreator = this.textureCreator != nullptr && !this.textureCreator.isRendered() ? this.textureCreator : nullptr;

      for (int var6 = 0; var6 < var1.readyData.size(); var6++) {
    AnimatedModelInstanceRenderData var3 = (AnimatedModelInstanceRenderData)var1.readyData.get(var6);
         var3.init(var3.modelInstance);
         var3.transformToParent(var1.getParentData(var3.modelInstance));
      }

      var1.bRendered = false;
      return SpriteRenderer.instance.getMainStateIndex();
   }

    bool isRendered() {
      return this.stateInfoRender().bRendered;
   }

    void doneWithTextureCreator(ModelInstanceTextureCreator var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < this.stateInfos.length; var2++) {
            if (this.stateInfos[var2].textureCreator == var1) {
               return;
            }
         }

         if (var1.isRendered()) {
            var1.postRender();
            if (var1 == this.textureCreator) {
               this.textureCreator = nullptr;
            }
         } else if (var1 != this.textureCreator) {
            var1.postRender();
         }
      }
   }

    void release(std::vector<AnimatedModelInstanceRenderData> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
    AnimatedModelInstanceRenderData var3 = (AnimatedModelInstanceRenderData)var1.get(var2);
         if (var3.modelInstance.getTextureInitializer() != nullptr) {
            var3.modelInstance.getTextureInitializer().postRender();
         }

         ModelManager.instance.derefModelInstance(var3.modelInstance);
      }

      instDataPool.release(var1);
   }

    void postRender(bool var1) {
    int var2 = SpriteRenderer.instance.getMainStateIndex();
    StateInfo var3 = this.stateInfos[var2];
    ModelInstanceTextureCreator var4 = var3.textureCreator;
      var3.textureCreator = nullptr;
      this.doneWithTextureCreator(var4);
      var3.modelInstance = nullptr;
      if (this.bAnimate && var3.bRendered) {
         this.release(var3.readyData);
         var3.readyData.clear();
         var3.readyData.addAll(var3.instData);
         var3.instData.clear();
      } else if (!this.bAnimate) {
      }

      this.release(var3.instData);
      var3.instData.clear();
   }

    void DoRender(ModelCamera var1) {
    int var2 = SpriteRenderer.instance.getRenderStateIndex();
    StateInfo var3 = this.stateInfos[var2];
      this.bReady = true;
    ModelInstanceTextureCreator var4 = var3.textureCreator;
      if (var4 != nullptr && !var4.isRendered()) {
         var4.render();
         if (!var4.isRendered()) {
            this.bReady = false;
         }
      }

      if (!this.isModelInstanceReady(this.modelInstance)) {
         this.bReady = false;
      }

      for (int var5 = 0; var5 < var3.instData.size(); var5++) {
    AnimatedModelInstanceRenderData var6 = (AnimatedModelInstanceRenderData)var3.instData.get(var5);
    ModelInstanceTextureInitializer var7 = var6.modelInstance.getTextureInitializer();
         if (var7 != nullptr && !var7.isRendered()) {
            var7.render();
            if (!var7.isRendered()) {
               this.bReady = false;
            }
         }
      }

      if (this.bReady && !var3.bModelsReady) {
         this.bReady = false;
      }

      if (this.bReady || !var3.readyData.empty()) {
         GL11.glPushClientAttrib(-1);
         GL11.glPushAttrib(1048575);
         GL11.glEnable(3042);
         GL11.glBlendFunc(770, 771);
         GL11.glEnable(3008);
         GL11.glAlphaFunc(516, 0.0F);
         var1.Begin();
         this.StartCharacter();
         this.Render();
         this.EndCharacter();
         var1.End();
         GL11.glDepthFunc(519);
         GL11.glPopAttrib();
         GL11.glPopClientAttrib();
         Texture.lastTextureID = -1;
         SpriteRenderer.ringBuffer.restoreVBOs = true;
         var3.bRendered = this.bReady;
      }
   }

    void DoRender(int var1, int var2, int var3, int var4, float var5, float var6) {
      GL11.glClear(256);
      this.uiModelCamera.x = var1;
      this.uiModelCamera.y = var2;
      this.uiModelCamera.w = var3;
      this.uiModelCamera.h = var4;
      this.uiModelCamera.sizeV = var5;
      this.uiModelCamera.m_animPlayerAngle = var6;
      this.DoRender(this.uiModelCamera);
   }

    void DoRenderToWorld(float var1, float var2, float var3, float var4) {
      worldModelCamera.x = var1;
      worldModelCamera.y = var2;
      worldModelCamera.z = var3;
      worldModelCamera.angle = var4;
      this.DoRender(worldModelCamera);
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
    int var1 = SpriteRenderer.instance.getRenderStateIndex();
    StateInfo var2 = this.stateInfos[var1];
    ModelInstance var3 = var2.modelInstance;
      if (var3 == nullptr) {
    bool var4 = true;
      } else {
    std::vector var7 = this.bReady ? var2.instData : var2.readyData;

         for (int var5 = 0; var5 < var7.size(); var5++) {
    AnimatedModelInstanceRenderData var6 = (AnimatedModelInstanceRenderData)var7.get(var5);
            this.DrawChar(var6);
         }
      }

      this.debugDrawAxes();
   }

    void DrawChar(AnimatedModelInstanceRenderData var1) {
    ModelInstance var2 = var1.modelInstance;
    FloatBuffer var3 = var1.matrixPalette;
      if (var2 != nullptr) {
         if (var2.AnimPlayer != nullptr) {
            if (var2.AnimPlayer.hasSkinningData()) {
               if (var2.model != nullptr) {
                  if (var2.model.isReady()) {
                     if (var2.tex != nullptr || var2.model.tex != nullptr) {
                        GL11.glEnable(2884);
                        GL11.glCullFace(1028);
                        GL11.glEnable(2929);
                        GL11.glEnable(3008);
                        GL11.glDepthFunc(513);
                        GL11.glDepthRange(0.0, 1.0);
                        GL11.glAlphaFunc(516, 0.01F);
                        if (var2.model.Effect == nullptr) {
                           var2.model.CreateShader("basicEffect");
                        }

    Shader var4 = var2.model.Effect;
                        if (var4 != nullptr) {
                           var4.Start();
                           if (var2.model.bStatic) {
                              var4.setTransformMatrix(var1.xfrm, true);
                           } else {
                              var4.setMatrixPalette(var3, true);
                           }

                           var4.setLight(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, var2);
                           var4.setLight(1, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, var2);
                           var4.setLight(2, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, var2);
                           var4.setLight(3, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, var2);
                           var4.setLight(4, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, float.NaN, var2);
    float var5 = 0.7F;

                           for (int var6 = 0; var6 < this.lights.length; var6++) {
    ResultLight var7 = this.lights[var6];
                              if (var7.radius > 0) {
                                 var4.setLight(
                                    var6,
                                    var7.x + 0.5F,
                                    var7.y + 0.5F,
                                    var7.z + 0.5F,
                                    var7.r * var5,
                                    var7.g * var5,
                                    var7.b * var5,
                                    var7.radius,
                                    var1.m_animPlayerAngle,
                                    this.lightsOriginX,
                                    this.lightsOriginY,
                                    this.lightsOriginZ,
                                    nullptr
                                 );
                              }
                           }

                           if (var2.tex != nullptr) {
                              var4.setTexture(var2.tex, "Texture", 0);
                           } else if (var2.model.tex != nullptr) {
                              var4.setTexture(var2.model.tex, "Texture", 0);
                           }

                           if (this.bOutside) {
    float var10 = ModelInstance.MODEL_LIGHT_MULT_OUTSIDE;
                              var4.setLight(
                                 3,
                                 this.lightsOriginX - 2.0F,
                                 this.lightsOriginY - 2.0F,
                                 this.lightsOriginZ + 1.0F,
                                 this.ambient.r * var10 / 4.0F,
                                 this.ambient.g * var10 / 4.0F,
                                 this.ambient.b * var10 / 4.0F,
                                 5000.0F,
                                 var1.m_animPlayerAngle,
                                 this.lightsOriginX,
                                 this.lightsOriginY,
                                 this.lightsOriginZ,
                                 nullptr
                              );
                              var4.setLight(
                                 4,
                                 this.lightsOriginX + 2.0F,
                                 this.lightsOriginY + 2.0F,
                                 this.lightsOriginZ + 1.0F,
                                 this.ambient.r * var10 / 4.0F,
                                 this.ambient.g * var10 / 4.0F,
                                 this.ambient.b * var10 / 4.0F,
                                 5000.0F,
                                 var1.m_animPlayerAngle,
                                 this.lightsOriginX,
                                 this.lightsOriginY,
                                 this.lightsOriginZ,
                                 nullptr
                              );
                           } else if (this.bRoom) {
    float var11 = ModelInstance.MODEL_LIGHT_MULT_ROOM;
                              var4.setLight(
                                 4,
                                 this.lightsOriginX + 2.0F,
                                 this.lightsOriginY + 2.0F,
                                 this.lightsOriginZ + 1.0F,
                                 this.ambient.r * var11 / 4.0F,
                                 this.ambient.g * var11 / 4.0F,
                                 this.ambient.b * var11 / 4.0F,
                                 5000.0F,
                                 var1.m_animPlayerAngle,
                                 this.lightsOriginX,
                                 this.lightsOriginY,
                                 this.lightsOriginZ,
                                 nullptr
                              );
                           }

                           var4.setDepthBias(var2.depthBias / 50.0F);
                           var4.setAmbient(this.ambient.r * 0.45F, this.ambient.g * 0.45F, this.ambient.b * 0.45F);
                           var4.setLightingAmount(1.0F);
                           var4.setHueShift(var2.hue);
                           var4.setTint(var2.tintR, var2.tintG, var2.tintB);
                           var4.setAlpha(this.m_alpha);
                        }

                        var2.model.Mesh.Draw(var4);
                        if (var4 != nullptr) {
                           var4.End();
                        }

                        if (Core.bDebug && DebugOptions.instance.ModelRenderLights.getValue() && var2.parent == nullptr) {
                           if (this.lights[0].radius > 0) {
                              Model.debugDrawLightSource(this.lights[0].x, this.lights[0].y, this.lights[0].z, 0.0F, 0.0F, 0.0F, -var1.m_animPlayerAngle);
                           }

                           if (this.lights[1].radius > 0) {
                              Model.debugDrawLightSource(this.lights[1].x, this.lights[1].y, this.lights[1].z, 0.0F, 0.0F, 0.0F, -var1.m_animPlayerAngle);
                           }

                           if (this.lights[2].radius > 0) {
                              Model.debugDrawLightSource(this.lights[2].x, this.lights[2].y, this.lights[2].z, 0.0F, 0.0F, 0.0F, -var1.m_animPlayerAngle);
                           }
                        }

                        if (Core.bDebug && DebugOptions.instance.ModelRenderBones.getValue()) {
                           GL11.glDisable(2929);
                           GL11.glDisable(3553);
                           GL11.glLineWidth(1.0F);
                           GL11.glBegin(1);

                           for (int var9 = 0; var9 < var2.AnimPlayer.modelTransforms.length; var9++) {
    int var12 = (int)var2.AnimPlayer.getSkinningData().SkeletonHierarchy.get(var9);
                              if (var12 >= 0) {
    Color var13 = Model.debugDrawColours[var9 % Model.debugDrawColours.length];
                                 GL11.glColor3f(var13.r, var13.g, var13.b);
    Matrix4f var8 = var2.AnimPlayer.modelTransforms[var9];
                                 GL11.glVertex3f(var8.m03, var8.m13, var8.m23);
                                 var8 = var2.AnimPlayer.modelTransforms[var12];
                                 GL11.glVertex3f(var8.m03, var8.m13, var8.m23);
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
      if (this.animPlayer != nullptr) {
         this.animPlayer = (AnimationPlayer)Pool.tryRelease(this.animPlayer);
      }
   }

    void OnAnimEvent(AnimLayer var1, AnimEvent var2) {
      if (!StringUtils.isNullOrWhitespace(var2.m_EventName)) {
    int var3 = var1.getDepth();
         this.actionContext.reportEvent(var3, var2.m_EventName);
      }
   }

    AnimationPlayer getAnimationPlayer() {
    Model var1 = this.getVisual().getModel();
      if (this.animPlayer != nullptr && this.animPlayer.getModel() != var1) {
         this.animPlayer = (AnimationPlayer)Pool.tryRelease(this.animPlayer);
      }

      if (this.animPlayer == nullptr) {
         this.animPlayer = AnimationPlayer.alloc(var1);
      }

      return this.animPlayer;
   }

    void actionStateChanged(ActionContext var1) {
      this.advancedAnimator.SetState(var1.getCurrentStateName(), PZArrayUtil.listConvert(var1.getChildStates(), var0 -> var0.name));
   }

    AnimationPlayerRecorder getAnimationPlayerRecorder() {
    return nullptr;
   }

    bool isAnimationRecorderActive() {
    return false;
   }

    ActionContext getActionContext() {
      return this.actionContext;
   }

    AdvancedAnimator getAdvancedAnimator() {
      return this.advancedAnimator;
   }

    ModelInstance getModelInstance() {
      return this.modelInstance;
   }

    std::string GetAnimSetName() {
      return this.animSetName;
   }

    std::string getUID() {
      return this.m_UID;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
