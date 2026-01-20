#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class PopTemplateManager {
public:
    static const PopTemplateManager instance = std::make_shared<PopTemplateManager>();
   public const std::vector<std::string> m_MaleSkins = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_FemaleSkins = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_MaleSkins_Zombie1 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_FemaleSkins_Zombie1 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_MaleSkins_Zombie2 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_FemaleSkins_Zombie2 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_MaleSkins_Zombie3 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_FemaleSkins_Zombie3 = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_SkeletonMaleSkins_Zombie = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_SkeletonFemaleSkins_Zombie = std::make_unique<std::vector<>>();
    static const int SKELETON_BURNED_SKIN_INDEX = 0;
    static const int SKELETON_NORMAL_SKIN_INDEX = 1;
    static const int SKELETON_MUSCLE_SKIN_INDEX = 2;

    void init() {
      ItemManager.init();

      for (int var1 = 1; var1 <= 5; var1++) {
         this.m_MaleSkins.push_back("MaleBody0" + var1);
      }

      for (int var2 = 1; var2 <= 5; var2++) {
         this.m_FemaleSkins.push_back("FemaleBody0" + var2);
      }

      for (int var3 = 1; var3 <= 4; var3++) {
         this.m_MaleSkins_Zombie1.push_back("M_ZedBody0" + var3 + "_level1");
         this.m_FemaleSkins_Zombie1.push_back("F_ZedBody0" + var3 + "_level1");
         this.m_MaleSkins_Zombie2.push_back("M_ZedBody0" + var3 + "_level2");
         this.m_FemaleSkins_Zombie2.push_back("F_ZedBody0" + var3 + "_level2");
         this.m_MaleSkins_Zombie3.push_back("M_ZedBody0" + var3 + "_level3");
         this.m_FemaleSkins_Zombie3.push_back("F_ZedBody0" + var3 + "_level3");
      }

      this.m_SkeletonMaleSkins_Zombie.push_back("SkeletonBurned");
      this.m_SkeletonMaleSkins_Zombie.push_back("Skeleton");
      this.m_SkeletonMaleSkins_Zombie.push_back("SkeletonMuscle");
      this.m_SkeletonFemaleSkins_Zombie.push_back("SkeletonBurned");
      this.m_SkeletonFemaleSkins_Zombie.push_back("Skeleton");
      this.m_SkeletonFemaleSkins_Zombie.push_back("SkeletonMuscle");
   }

    ModelInstance addClothingItem(IsoGameCharacter var1, ModelSlot var2, ItemVisual var3, ClothingItem var4) {
    std::string var5 = var4.getModel(var1.isFemale());
      if (StringUtils.isNullOrWhitespace(var5)) {
         if (DebugLog.isEnabled(DebugType.Clothing)) {
            DebugLog.Clothing.debugln("No model specified by item: " + var4.m_Name);
         }

    return nullptr;
      } else {
         var5 = this.processModelFileName(var5);
    std::string var6 = var3.getTextureChoice(var4);
    ImmutableColor var7 = var3.getTint(var4);
    float var8 = var3.getHue(var4);
    std::string var9 = var4.m_AttachBone;
    std::string var10 = var4.m_Shader;
    ModelInstance var11;
         if (var9 != nullptr && var9.length() > 0) {
            var11 = ModelManager.instance.newStaticInstance(var2, var5, var6, var9, var10);
         } else {
            var11 = ModelManager.instance.newAdditionalModelInstance(var5, var6, var1, var2.model.AnimPlayer, var10);
         }

         if (var11 == nullptr) {
    return nullptr;
         } else {
            this.postProcessNewItemInstance(var11, var2, var7);
            var11.setItemVisual(var3);
    return var11;
         }
      }
   }

    void addHeadHairItem(IsoGameCharacter var1, ModelSlot var2, const std::string& var3, const std::string& var4, ImmutableColor var5) {
      if (StringUtils.isNullOrWhitespace(var3)) {
         if (DebugLog.isEnabled(DebugType.Clothing)) {
            DebugLog.Clothing.warn("No model specified.");
         }
      } else {
         var3 = this.processModelFileName(var3);
    ModelInstance var6 = ModelManager.instance.newAdditionalModelInstance(var3, var4, var1, var2.model.AnimPlayer, nullptr);
         if (var6 != nullptr) {
            this.postProcessNewItemInstance(var6, var2, var5);
         }
      }
   }

    void addHeadHair(IsoGameCharacter var1, ModelSlot var2, HumanVisual var3, ItemVisual var4, bool var5) {
    ImmutableColor var6 = var3.getHairColor();
      if (var5) {
         var6 = var3.getBeardColor();
      }

      if (var1.isFemale()) {
         if (!var5) {
    HairStyle var7 = HairStyles.instance.FindFemaleStyle(var3.getHairModel());
            if (var7 != nullptr && var4 != nullptr && var4.getClothingItem() != nullptr) {
               var7 = HairStyles.instance.getAlternateForHat(var7, var4.getClothingItem().m_HatCategory);
            }

            if (var7 != nullptr && var7.isValid()) {
               if (DebugLog.isEnabled(DebugType.Clothing)) {
                  DebugLog.Clothing.debugln("  Adding female hair: " + var7.name);
               }

               this.addHeadHairItem(var1, var2, var7.model, var7.texture, var6);
            }
         }
      } else if (!var5) {
    HairStyle var8 = HairStyles.instance.FindMaleStyle(var3.getHairModel());
         if (var8 != nullptr && var4 != nullptr && var4.getClothingItem() != nullptr) {
            var8 = HairStyles.instance.getAlternateForHat(var8, var4.getClothingItem().m_HatCategory);
         }

         if (var8 != nullptr && var8.isValid()) {
            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.debugln("  Adding male hair: " + var8.name);
            }

            this.addHeadHairItem(var1, var2, var8.model, var8.texture, var6);
         }
      } else {
    BeardStyle var9 = BeardStyles.instance.FindStyle(var3.getBeardModel());
         if (var9 != nullptr && var9.isValid()) {
            if (var4 != nullptr
               && var4.getClothingItem() != nullptr
               && !StringUtils.isNullOrEmpty(var4.getClothingItem().m_HatCategory)
               && var4.getClothingItem().m_HatCategory.contains("nobeard")) {
               return;
            }

            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.debugln("  Adding beard: " + var9.name);
            }

            this.addHeadHairItem(var1, var2, var9.model, var9.texture, var6);
         }
      }
   }

    void populateCharacterModelSlot(IsoGameCharacter var1, ModelSlot var2) {
      if (!(dynamic_cast<IHumanVisual*>(var1) != nullptr)) {
         DebugLog.Clothing.warn("Supplied character is not an IHumanVisual. Ignored. " + var1);
      } else {
    HumanVisual var3 = ((IHumanVisual)var1).getHumanVisual();
    ItemVisuals var4 = std::make_shared<ItemVisuals>();
         var1.getItemVisuals(var4);
    CharacterMask var5 = HumanVisual.GetMask(var4);
         if (DebugLog.isEnabled(DebugType.Clothing)) {
            DebugLog.Clothing.debugln("characterType:" + var1.getClass().getName() + ", name:" + var1.getName());
         }

         if (var5.isPartVisible(Part.Head)) {
            this.addHeadHair(var1, var2, var3, var4.findHat(), false);
            this.addHeadHair(var1, var2, var3, var4.findMask(), true);
         }

         for (int var6 = var4.size() - 1; var6 >= 0; var6--) {
    ItemVisual var7 = (ItemVisual)var4.get(var6);
    ClothingItem var8 = var7.getClothingItem();
            if (var8 == nullptr) {
               if (DebugLog.isEnabled(DebugType.Clothing)) {
                  DebugLog.Clothing.warn("ClothingItem not found for ItemVisual:" + var7);
               }
            } else if (!this.isItemModelHidden(var1.getBodyLocationGroup(), var4, var7)) {
               this.addClothingItem(var1, var2, var7, var8);
            }
         }

         for (int var9 = var3.getBodyVisuals().size() - 1; var9 >= 0; var9--) {
    ItemVisual var10 = (ItemVisual)var3.getBodyVisuals().get(var9);
    ClothingItem var11 = var10.getClothingItem();
            if (var11 == nullptr) {
               if (DebugLog.isEnabled(DebugType.Clothing)) {
                  DebugLog.Clothing.warn("ClothingItem not found for ItemVisual:" + var10);
               }
            } else {
               this.addClothingItem(var1, var2, var10, var11);
            }
         }

         var1.postUpdateModelTextures();
         var1.updateSpeedModifiers();
      }
   }

    bool isItemModelHidden(BodyLocationGroup var1, ItemVisuals var2, ItemVisual var3) {
    Item var4 = var3.getScriptItem();
      if (var4 != nullptr && var1.getLocation(var4.getBodyLocation()) != nullptr) {
         for (int var5 = 0; var5 < var2.size(); var5++) {
            if (var2.get(var5) != var3) {
    Item var6 = ((ItemVisual)var2.get(var5)).getScriptItem();
               if (var6 != nullptr && var1.getLocation(var6.getBodyLocation()) != nullptr && var1.isHideModel(var6.getBodyLocation(), var4.getBodyLocation())) {
    return true;
               }
            }
         }

    return false;
      } else {
    return false;
      }
   }

    std::string processModelFileName(const std::string& var1) {
      var1 = var1.replaceAll("\\\\", "/");
      return var1.toLowerCase(Locale.ENGLISH);
   }

    void postProcessNewItemInstance(ModelInstance var1, ModelSlot var2, ImmutableColor var3) {
      var1.depthBias = 0.0F;
      var1.matrixModel = var2.model;
      var1.tintR = var3.r;
      var1.tintG = var3.g;
      var1.tintB = var3.b;
      var1.parent = var2.model;
      var1.AnimPlayer = var2.model.AnimPlayer;
      var2.model.sub.push_back(0, var1);
      var2.sub.push_back(0, var1);
      var1.setOwner(var2);
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
