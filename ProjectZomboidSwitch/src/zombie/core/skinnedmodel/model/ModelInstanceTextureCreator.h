#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/CharacterSmartTexture.h"
#include "zombie/characterTextures/ItemSmartTexture.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/core/Core.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator/CharacterData.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator/ItemData.h"
#include "zombie/core/skinnedmodel/population/ClothingDecal.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/PopTemplateManager.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureCombiner.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstanceTextureCreator : public GenericDrawer {
public:
    bool bZombie;
    int renderRefCount;
    const CharacterMask mask = std::make_shared<CharacterMask>();
   private const boolean[] holeMask = new boolean[BloodBodyPartType.MAX.index()];
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    const CharacterData chrData = std::make_shared<CharacterData>();
   private const std::vector<ItemData> itemData = std::make_unique<std::vector<>>();
    const CharacterSmartTexture characterSmartTexture = std::make_shared<CharacterSmartTexture>();
    const ItemSmartTexture itemSmartTexture = std::make_shared<ItemSmartTexture>(nullptr);
   private const std::vector<Texture> tempTextures = std::make_unique<std::vector<>>();
    bool bRendered = false;
   private const std::vector<Texture> texturesNotReady = std::make_unique<std::vector<>>();
    int testNotReady = -1;
   private static const ObjectPool<ModelInstanceTextureCreator> pool = std::make_shared<ObjectPool>(ModelInstanceTextureCreator::new);

    void init(IsoGameCharacter var1) {
    ModelSlot var2 = var1.legsSprite.modelSlot;
    HumanVisual var3 = ((IHumanVisual)var1).getHumanVisual();
      var1.getItemVisuals(this.itemVisuals);
      this.init(var3, this.itemVisuals, var2.model);
      this.itemVisuals.clear();
   }

    void init(BaseVisual var1, ItemVisuals var2, ModelInstance var3) {
      if (dynamic_cast<HumanVisual*>(var1) != nullptr) {
         this.init((HumanVisual)var1, var2, var3);
      } else {
         throw IllegalArgumentException("unhandled BaseVisual " + var1);
      }
   }

    void init(HumanVisual var1, ItemVisuals var2, ModelInstance var3) {
    bool var4 = DebugLog.isEnabled(DebugType.Clothing);
      this.bRendered = false;
      this.bZombie = var1.isZombie();
    CharacterMask var5 = this.mask;
      var5.setAllVisible(true);
    std::string var6 = "media/textures/Body/Masks";
      Arrays.fill(this.holeMask, false);
      ItemData.pool.release(this.itemData);
      this.itemData.clear();
      this.texturesNotReady.clear();
    BodyLocationGroup var7 = BodyLocations.getGroup("Human");

      for (int var8 = var2.size() - 1; var8 >= 0; var8--) {
    ItemVisual var9 = (ItemVisual)var2.get(var8);
    ClothingItem var10 = var9.getClothingItem();
         if (var10 == nullptr) {
            if (var4) {
               DebugLog.Clothing.warn("ClothingItem not found for ItemVisual:" + var9);
            }
         } else if (!var10.isReady()) {
            if (var4) {
               DebugLog.Clothing.warn("ClothingItem not ready for ItemVisual:" + var9);
            }
         } else if (!PopTemplateManager.instance.isItemModelHidden(var7, var2, var9)) {
    ModelInstance var11 = this.findModelInstance(var3.sub, var9);
            if (var11 == nullptr) {
    std::string var12 = var10.getModel(var1.isFemale());
               if (!StringUtils.isNullOrWhitespace(var12)) {
                  if (var4) {
                     DebugLog.Clothing.warn("ModelInstance not found for ItemVisual:" + var9);
                  }
                  continue;
               }
            }

            this.addClothingItem(var11, var9, var10, var5, var6);

            for (int var38 = 0; var38 < BloodBodyPartType.MAX.index(); var38++) {
    BloodBodyPartType var13 = BloodBodyPartType.FromIndex(var38);
               if (var9.getHole(var13) > 0.0F && var5.isBloodBodyPartVisible(var13)) {
                  this.holeMask[var38] = true;
               }
            }

            for (int var39 = 0; var39 < var10.m_Masks.size(); var39++) {
    Part var42 = Part.fromInt((int)var10.m_Masks.get(var39));

               for (BloodBodyPartType var17 : var42.getBloodBodyPartTypes()) {
                  if (var9.getHole(var17) <= 0.0F) {
                     this.holeMask[var17.index()] = false;
                  }
               }
            }

            var9.getClothingItemCombinedMask(var5);
            if (!StringUtils.equalsIgnoreCase(var10.m_UnderlayMasksFolder, "media/textures/Body/Masks")) {
               var6 = var10.m_UnderlayMasksFolder;
            }
         }
      }

      this.chrData.modelInstance = var3;
      this.chrData.mask.copyFrom(var5);
      this.chrData.maskFolder = var6;
      this.chrData.baseTexture = "media/textures/Body/" + var1.getSkinTexture() + ".png";
      Arrays.fill(this.chrData.blood, 0.0F);

      for (int var19 = 0; var19 < BloodBodyPartType.MAX.index(); var19++) {
    BloodBodyPartType var29 = BloodBodyPartType.FromIndex(var19);
         this.chrData.blood[var19] = var1.getBlood(var29);
         this.chrData.dirt[var19] = var1.getDirt(var29);
      }

    Texture var20 = getTextureWithFlags(this.chrData.baseTexture);
      if (var20 != nullptr && !var20.isReady()) {
         this.texturesNotReady.push_back(var20);
      }

      if (!this.chrData.mask.isAllVisible() && !this.chrData.mask.isNothingVisible()) {
    std::string var30 = this.chrData.maskFolder;
         Consumer var33 = Lambda.consumer(var30, this.texturesNotReady, (var0, var1x, var2x) -> {
    Texture var3x = getTextureWithFlags(var1x + "/" + var0 + ".png");
            if (var3x != nullptr && !var3x.isReady()) {
               var2x.push_back(var3x);
            }
         });
         this.chrData.mask.forEachVisible(var33);
      }

      var20 = getTextureWithFlags("media/textures/BloodTextures/BloodOverlay.png");
      if (var20 != nullptr && !var20.isReady()) {
         this.texturesNotReady.push_back(var20);
      }

      var20 = getTextureWithFlags("media/textures/BloodTextures/GrimeOverlay.png");
      if (var20 != nullptr && !var20.isReady()) {
         this.texturesNotReady.push_back(var20);
      }

      var20 = getTextureWithFlags("media/textures/patches/patchesmask.png");
      if (var20 != nullptr && !var20.isReady()) {
         this.texturesNotReady.push_back(var20);
      }

      for (int var31 = 0; var31 < BloodBodyPartType.MAX.index(); var31++) {
    BloodBodyPartType var34 = BloodBodyPartType.FromIndex(var31);
    std::string var36 = "media/textures/BloodTextures/" + CharacterSmartTexture.MaskFiles[var34.index()] + ".png";
         var20 = getTextureWithFlags(var36);
         if (var20 != nullptr && !var20.isReady()) {
            this.texturesNotReady.push_back(var20);
         }

    std::string var40 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[var34.index()] + ".png";
         var20 = getTextureWithFlags(var40);
         if (var20 != nullptr && !var20.isReady()) {
            this.texturesNotReady.push_back(var20);
         }

    std::string var43 = "media/textures/patches/" + CharacterSmartTexture.BasicPatchesMaskFiles[var34.index()] + ".png";
         var20 = getTextureWithFlags(var43);
         if (var20 != nullptr && !var20.isReady()) {
            this.texturesNotReady.push_back(var20);
         }

    std::string var45 = "media/textures/patches/" + CharacterSmartTexture.DenimPatchesMaskFiles[var34.index()] + ".png";
         var20 = getTextureWithFlags(var45);
         if (var20 != nullptr && !var20.isReady()) {
            this.texturesNotReady.push_back(var20);
         }

    std::string var46 = "media/textures/patches/" + CharacterSmartTexture.LeatherPatchesMaskFiles[var34.index()] + ".png";
         var20 = getTextureWithFlags(var46);
         if (var20 != nullptr && !var20.isReady()) {
            this.texturesNotReady.push_back(var20);
         }
      }

      var5.setAllVisible(true);
      var6 = "media/textures/Body/Masks";

      for (int var32 = var1.getBodyVisuals().size() - 1; var32 >= 0; var32--) {
    ItemVisual var35 = (ItemVisual)var1.getBodyVisuals().get(var32);
    ClothingItem var37 = var35.getClothingItem();
         if (var37 == nullptr) {
            if (var4) {
               DebugLog.Clothing.warn("ClothingItem not found for ItemVisual:" + var35);
            }
         } else if (!var37.isReady()) {
            if (var4) {
               DebugLog.Clothing.warn("ClothingItem not ready for ItemVisual:" + var35);
            }
         } else {
    ModelInstance var41 = this.findModelInstance(var3.sub, var35);
            if (var41 == nullptr) {
    std::string var44 = var37.getModel(var1.isFemale());
               if (!StringUtils.isNullOrWhitespace(var44)) {
                  if (var4) {
                     DebugLog.Clothing.warn("ModelInstance not found for ItemVisual:" + var35);
                  }
                  continue;
               }
            }

            this.addClothingItem(var41, var35, var37, var5, var6);
         }
      }
   }

    ModelInstance findModelInstance(std::vector<ModelInstance> var1, ItemVisual var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    ModelInstance var4 = (ModelInstance)var1.get(var3);
    ItemVisual var5 = var4.getItemVisual();
         if (var5 != nullptr && var5.getClothingItem() == var2.getClothingItem()) {
    return var4;
         }
      }

    return nullptr;
   }

    void addClothingItem(ModelInstance var1, ItemVisual var2, ClothingItem var3, CharacterMask var4, const std::string& var5) {
    std::string var6 = var1 == nullptr ? var2.getBaseTexture(var3) : var2.getTextureChoice(var3);
    ImmutableColor var7 = var2.getTint(var3);
    float var8 = var2.getHue(var3);
    ItemData var9 = (ItemData)ItemData.pool.alloc();
      var9.modelInstance = var1;
      var9.category = CharacterSmartTexture.ClothingItemCategory;
      var9.mask.copyFrom(var4);
      var9.maskFolder = var3.m_MasksFolder;
      if (StringUtils.equalsIgnoreCase(var9.maskFolder, "media/textures/Body/Masks")) {
         var9.maskFolder = var5;
      }

      if (StringUtils.equalsIgnoreCase(var9.maskFolder, "none")) {
         var9.mask.setAllVisible(true);
      }

      if (var9.maskFolder.contains("Clothes/Hat/Masks")) {
         var9.mask.setAllVisible(true);
      }

      var9.baseTexture = "media/textures/" + var6 + ".png";
      var9.tint = var7;
      var9.hue = var8;
      var9.decalTexture = nullptr;
      Arrays.fill(var9.basicPatches, 0.0F);
      Arrays.fill(var9.denimPatches, 0.0F);
      Arrays.fill(var9.leatherPatches, 0.0F);
      Arrays.fill(var9.blood, 0.0F);
      Arrays.fill(var9.dirt, 0.0F);
      Arrays.fill(var9.hole, 0.0F);
    int var10 = ModelManager.instance.getTextureFlags();
    Texture var11 = Texture.getSharedTexture(var9.baseTexture, var10);
      if (var11 != nullptr && !var11.isReady()) {
         this.texturesNotReady.push_back(var11);
      }

      if (!var9.mask.isAllVisible() && !var9.mask.isNothingVisible()) {
    std::string var12 = var9.maskFolder;
         Consumer var13 = Lambda.consumer(var12, this.texturesNotReady, (var0, var1x, var2x) -> {
    Texture var3x = getTextureWithFlags(var1x + "/" + var0 + ".png");
            if (var3x != nullptr && !var3x.isReady()) {
               var2x.push_back(var3x);
            }
         });
         var9.mask.forEachVisible(var13);
      }

      if (Core.getInstance().isOptionSimpleClothingTextures(this.bZombie)) {
         this.itemData.push_back(var9);
      } else {
    std::string var18 = var2.getDecal(var3);
         if (!StringUtils.isNullOrWhitespace(var18)) {
    ClothingDecal var19 = ClothingDecals.instance.getDecal(var18);
            if (var19 != nullptr && var19.isValid()) {
               var9.decalTexture = var19.texture;
               var9.decalX = var19.x;
               var9.decalY = var19.y;
               var9.decalWidth = var19.width;
               var9.decalHeight = var19.height;
               var11 = getTextureWithFlags("media/textures/" + var9.decalTexture + ".png");
               if (var11 != nullptr && !var11.isReady()) {
                  this.texturesNotReady.push_back(var11);
               }
            }
         }

         for (int var20 = 0; var20 < BloodBodyPartType.MAX.index(); var20++) {
    BloodBodyPartType var14 = BloodBodyPartType.FromIndex(var20);
            var9.blood[var20] = var2.getBlood(var14);
            var9.dirt[var20] = var2.getDirt(var14);
            var9.basicPatches[var20] = var2.getBasicPatch(var14);
            var9.denimPatches[var20] = var2.getDenimPatch(var14);
            var9.leatherPatches[var20] = var2.getLeatherPatch(var14);
            var9.hole[var20] = var2.getHole(var14);
            if (var9.hole[var20] > 0.0F) {
    std::string var15 = "media/textures/HoleTextures/" + CharacterSmartTexture.MaskFiles[var14.index()] + ".png";
               var11 = getTextureWithFlags(var15);
               if (var11 != nullptr && !var11.isReady()) {
                  this.texturesNotReady.push_back(var11);
               }
            }

            if (var9.hole[var20] == 0.0F && this.holeMask[var20]) {
               var9.hole[var20] = -1.0F;
               if (var9.mask.isBloodBodyPartVisible(var14)) {
               }
            }
         }

         this.itemData.push_back(var9);
      }
   }

    void render() {
      if (!this.bRendered) {
         for (int var1 = 0; var1 < this.texturesNotReady.size(); var1++) {
    Texture var2 = this.texturesNotReady.get(var1);
            if (!var2.isReady()) {
               return;
            }
         }

         GL11.glPushAttrib(2048);

         try {
            this.tempTextures.clear();
    CharacterSmartTexture var9 = this.createFullCharacterTexture();

    assert var9 = = this.characterSmartTexture;

            if (!(this.chrData.modelInstance.dynamic_cast<CharacterSmartTexture*>(tex) != nullptr)) {
               this.chrData.modelInstance.tex = std::make_unique<CharacterSmartTexture>();
            }

            ((CharacterSmartTexture)this.chrData.modelInstance.tex).clear();
            this.applyCharacterTexture(var9.result, (CharacterSmartTexture)this.chrData.modelInstance.tex);
            var9.clear();
            this.tempTextures.push_back(var9.result);
            var9.result = nullptr;
            var9 = (CharacterSmartTexture)this.chrData.modelInstance.tex;

            for (int var11 = this.itemData.size() - 1; var11 >= 0; var11--) {
    ItemData var3 = this.itemData.get(var11);
    Texture var4;
               if (this.isSimpleTexture(var3)) {
    int var5 = ModelManager.instance.getTextureFlags();
                  var4 = Texture.getSharedTexture(var3.baseTexture, var5);
                  if (!this.isItemSmartTextureRequired(var3)) {
                     var3.modelInstance.tex = var4;
                     continue;
                  }
               } else {
    ItemSmartTexture var15 = this.createFullItemTexture(var3);

    assert var15 = = this.itemSmartTexture;

                  var4 = var15.result;
                  this.tempTextures.push_back(var15.result);
                  var15.result = nullptr;
               }

               if (var3.modelInstance == nullptr) {
                  this.applyItemTexture(var3, var4, var9);
               } else {
                  if (!(var3.modelInstance.dynamic_cast<ItemSmartTexture*>(tex) != nullptr)) {
                     var3.modelInstance.tex = std::make_shared<ItemSmartTexture>(nullptr);
                  }

                  ((ItemSmartTexture)var3.modelInstance.tex).clear();
                  this.applyItemTexture(var3, var4, (ItemSmartTexture)var3.modelInstance.tex);
                  ((ItemSmartTexture)var3.modelInstance.tex).calculate();
                  ((ItemSmartTexture)var3.modelInstance.tex).clear();
               }
            }

            var9.calculate();
            var9.clear();
            this.itemSmartTexture.clear();

            for (int var12 = 0; var12 < this.tempTextures.size(); var12++) {
               for (int var13 = 0; var13 < this.itemData.size(); var13++) {
    ModelInstance var14 = this.itemData.get(var13).modelInstance;

    assert var14 = = nullptr || this.tempTextures.get(var12) != var14.tex;
               }

               TextureCombiner.instance.releaseTexture(this.tempTextures.get(var12));
            }

            this.tempTextures.clear();
         } finally {
            GL11.glPopAttrib();
         }

         this.bRendered = true;
      }
   }

    CharacterSmartTexture createFullCharacterTexture() {
    CharacterSmartTexture var1 = this.characterSmartTexture;
      var1.clear();
      var1.addTexture(this.chrData.baseTexture, CharacterSmartTexture.BodyCategory, ImmutableColor.white, 0.0F);

      for (int var2 = 0; var2 < BloodBodyPartType.MAX.index(); var2++) {
    BloodBodyPartType var3 = BloodBodyPartType.FromIndex(var2);
         if (this.chrData.dirt[var2] > 0.0F) {
            var1.addDirt(var3, this.chrData.dirt[var2], nullptr);
         }

         if (this.chrData.blood[var2] > 0.0F) {
            var1.addBlood(var3, this.chrData.blood[var2], nullptr);
         }
      }

      var1.calculate();
    return var1;
   }

    void applyCharacterTexture(Texture var1, CharacterSmartTexture var2) {
      var2.addMaskedTexture(this.chrData.mask, this.chrData.maskFolder, var1, CharacterSmartTexture.BodyCategory, ImmutableColor.white, 0.0F);

      for (int var3 = 0; var3 < BloodBodyPartType.MAX.index(); var3++) {
    BloodBodyPartType var4 = BloodBodyPartType.FromIndex(var3);
         if (this.holeMask[var3]) {
            var2.removeHole(var1, var4);
         }
      }
   }

    bool isSimpleTexture(ItemData var1) {
      if (var1.hue != 0.0F) {
    return false;
      } else {
    ImmutableColor var2 = var1.tint;
         if (var1.modelInstance != nullptr) {
            var2 = ImmutableColor.white;
         }

         if (!var2 == ImmutableColor.white)) {
    return false;
         } else if (var1.decalTexture != nullptr) {
    return false;
         } else {
            for (int var3 = 0; var3 < BloodBodyPartType.MAX.index(); var3++) {
               if (var1.blood[var3] > 0.0F) {
    return false;
               }

               if (var1.dirt[var3] > 0.0F) {
    return false;
               }

               if (var1.hole[var3] > 0.0F) {
    return false;
               }

               if (var1.basicPatches[var3] > 0.0F) {
    return false;
               }

               if (var1.denimPatches[var3] > 0.0F) {
    return false;
               }

               if (var1.leatherPatches[var3] > 0.0F) {
    return false;
               }
            }

    return true;
         }
      }
   }

    ItemSmartTexture createFullItemTexture(ItemData var1) {
    ItemSmartTexture var2 = this.itemSmartTexture;
      var2.clear();
    ImmutableColor var3 = var1.tint;
      if (var1.modelInstance != nullptr) {
         var1.modelInstance.tintR = var1.modelInstance.tintG = var1.modelInstance.tintB = 1.0F;
      }

      var2.addTexture(var1.baseTexture, var1.category, var3, var1.hue);
      if (var1.decalTexture != nullptr) {
         var2.addRect("media/textures/" + var1.decalTexture + ".png", var1.decalX, var1.decalY, var1.decalWidth, var1.decalHeight);
      }

      for (int var4 = 0; var4 < BloodBodyPartType.MAX.index(); var4++) {
         if (var1.blood[var4] > 0.0F) {
    BloodBodyPartType var5 = BloodBodyPartType.FromIndex(var4);
            var2.addBlood("media/textures/BloodTextures/BloodOverlay.png", var5, var1.blood[var4]);
         }

         if (var1.dirt[var4] > 0.0F) {
    BloodBodyPartType var8 = BloodBodyPartType.FromIndex(var4);
            var2.addDirt("media/textures/BloodTextures/GrimeOverlay.png", var8, var1.dirt[var4]);
         }

         if (var1.basicPatches[var4] > 0.0F) {
    BloodBodyPartType var9 = BloodBodyPartType.FromIndex(var4);
            var2.setBasicPatches(var9);
         }

         if (var1.denimPatches[var4] > 0.0F) {
    BloodBodyPartType var10 = BloodBodyPartType.FromIndex(var4);
            var2.setDenimPatches(var10);
         }

         if (var1.leatherPatches[var4] > 0.0F) {
    BloodBodyPartType var11 = BloodBodyPartType.FromIndex(var4);
            var2.setLeatherPatches(var11);
         }
      }

      for (int var7 = 0; var7 < BloodBodyPartType.MAX.index(); var7++) {
         if (var1.hole[var7] > 0.0F) {
    BloodBodyPartType var12 = BloodBodyPartType.FromIndex(var7);
    Texture var6 = var2.addHole(var12);

            assert var6 != var2.result;

            this.tempTextures.push_back(var6);
         }
      }

      var2.calculate();
    return var2;
   }

    bool isItemSmartTextureRequired(ItemData var1) {
      if (var1.modelInstance == nullptr) {
    return true;
      } else if (var1.modelInstance.dynamic_cast<ItemSmartTexture*>(tex) != nullptr) {
    return true;
      } else {
         for (int var2 = 0; var2 < BloodBodyPartType.MAX.index(); var2++) {
            if (var1.hole[var2] < 0.0F) {
    return true;
            }
         }

         return !var1.mask.isAllVisible();
      }
   }

    void applyItemTexture(ItemData var1, Texture var2, SmartTexture var3) {
      var3.addMaskedTexture(var1.mask, var1.maskFolder, var2, var1.category, ImmutableColor.white, 0.0F);

      for (int var4 = 0; var4 < BloodBodyPartType.MAX.index(); var4++) {
         if (var1.hole[var4] < 0.0F) {
    BloodBodyPartType var5 = BloodBodyPartType.FromIndex(var4);
            var3.removeHole(var2, var5);
         }
      }
   }

    void postRender() {
      if (!this.bRendered) {
         if (this.chrData.modelInstance.character == nullptr) {
    bool var1 = true;
         } else {
    bool var2 = true;
         }
      }

      for (int var3 = 0; var3 < this.itemData.size(); var3++) {
         this.itemData.get(var3).modelInstance = nullptr;
      }

      this.chrData.modelInstance = nullptr;
      this.texturesNotReady.clear();
      ItemData.pool.release(this.itemData);
      this.itemData.clear();
      pool.release(this);
   }

    bool isRendered() {
      return this.testNotReady > 0 ? false : this.bRendered;
   }

    static Texture getTextureWithFlags(const std::string& var0) {
      return Texture.getSharedTexture(var0, ModelManager.instance.getTextureFlags());
   }

    static ModelInstanceTextureCreator alloc() {
      return (ModelInstanceTextureCreator)pool.alloc();
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
