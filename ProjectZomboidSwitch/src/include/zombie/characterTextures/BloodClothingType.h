#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace characterTextures {


enum class BloodClothingType {
   Jacket,
   LongJacket,
   Trousers,
   ShortsShort,
   Shirt,
   ShirtLongSleeves,
   ShirtNoSleeves,
   Jumper,
   JumperNoSleeves,
   Shoes,
   FullHelmet,
   Apron,
   Bag,
   Hands,
   Head,
   Neck,
   UpperBody,
   LowerBody,
   LowerLegs,
   UpperLegs,
   LowerArms,
   UpperArms,
   Groin;

   private static std::unordered_map<BloodClothingType, std::vector<BloodBodyPartType>> coveredParts = nullptr;
   private static const std::vector<BloodBodyPartType> bodyParts = std::make_unique<std::vector<>>();

    static BloodClothingType fromString(const std::string& var0) {
      if (Jacket == var0)) {
    return Jacket;
      } else if (LongJacket == var0)) {
    return LongJacket;
      } else if (Trousers == var0)) {
    return Trousers;
      } else if (ShortsShort == var0)) {
    return ShortsShort;
      } else if (Shirt == var0)) {
    return Shirt;
      } else if (ShirtLongSleeves == var0)) {
    return ShirtLongSleeves;
      } else if (ShirtNoSleeves == var0)) {
    return ShirtNoSleeves;
      } else if (Jumper == var0)) {
    return Jumper;
      } else if (JumperNoSleeves == var0)) {
    return JumperNoSleeves;
      } else if (Shoes == var0)) {
    return Shoes;
      } else if (FullHelmet == var0)) {
    return FullHelmet;
      } else if (Bag == var0)) {
    return Bag;
      } else if (Hands == var0)) {
    return Hands;
      } else if (Head == var0)) {
    return Head;
      } else if (Neck == var0)) {
    return Neck;
      } else if (Apron == var0)) {
    return Apron;
      } else if (Bag == var0)) {
    return Bag;
      } else if (Hands == var0)) {
    return Hands;
      } else if (Head == var0)) {
    return Head;
      } else if (Neck == var0)) {
    return Neck;
      } else if (UpperBody == var0)) {
    return UpperBody;
      } else if (LowerBody == var0)) {
    return LowerBody;
      } else if (LowerLegs == var0)) {
    return LowerLegs;
      } else if (UpperLegs == var0)) {
    return UpperLegs;
      } else if (LowerArms == var0)) {
    return LowerArms;
      } else if (UpperArms == var0)) {
    return UpperArms;
      } else {
         return Groin == var0) ? Groin : nullptr;
      }
   }

    static void init() {
      if (coveredParts == nullptr) {
         coveredParts = std::make_unique<std::unordered_map<>>();
    std::vector var0 = new std::vector();
         var0.push_back(BloodBodyPartType.Torso_Upper);
         var0.push_back(BloodBodyPartType.Torso_Lower);
         var0.push_back(BloodBodyPartType.UpperLeg_L);
         var0.push_back(BloodBodyPartType.UpperLeg_R);
         coveredParts.put(Apron, var0);
    std::vector var1 = new std::vector();
         var1.push_back(BloodBodyPartType.Torso_Upper);
         var1.push_back(BloodBodyPartType.Torso_Lower);
         var1.push_back(BloodBodyPartType.Back);
         coveredParts.put(ShirtNoSleeves, var1);
         coveredParts.put(JumperNoSleeves, var1);
    std::vector var2 = new std::vector();
         var2.addAll(var1);
         var2.push_back(BloodBodyPartType.UpperArm_L);
         var2.push_back(BloodBodyPartType.UpperArm_R);
         coveredParts.put(Shirt, var2);
    std::vector var3 = new std::vector();
         var3.addAll(var2);
         var3.push_back(BloodBodyPartType.ForeArm_L);
         var3.push_back(BloodBodyPartType.ForeArm_R);
         coveredParts.put(ShirtLongSleeves, var3);
         coveredParts.put(Jumper, var3);
    std::vector var4 = new std::vector();
         var4.addAll(var3);
         var4.push_back(BloodBodyPartType.Neck);
         coveredParts.put(Jacket, var4);
    std::vector var5 = new std::vector();
         var5.addAll(var3);
         var5.push_back(BloodBodyPartType.Neck);
         var5.push_back(BloodBodyPartType.Groin);
         var5.push_back(BloodBodyPartType.UpperLeg_L);
         var5.push_back(BloodBodyPartType.UpperLeg_R);
         coveredParts.put(LongJacket, var5);
    std::vector var6 = new std::vector();
         var6.push_back(BloodBodyPartType.Groin);
         var6.push_back(BloodBodyPartType.UpperLeg_L);
         var6.push_back(BloodBodyPartType.UpperLeg_R);
         coveredParts.put(ShortsShort, var6);
    std::vector var7 = new std::vector();
         var7.addAll(var6);
         var7.push_back(BloodBodyPartType.LowerLeg_L);
         var7.push_back(BloodBodyPartType.LowerLeg_R);
         coveredParts.put(Trousers, var7);
    std::vector var8 = new std::vector();
         var8.push_back(BloodBodyPartType.Foot_L);
         var8.push_back(BloodBodyPartType.Foot_R);
         coveredParts.put(Shoes, var8);
    std::vector var9 = new std::vector();
         var9.push_back(BloodBodyPartType.Head);
         coveredParts.put(FullHelmet, var9);
    std::vector var10 = new std::vector();
         var10.push_back(BloodBodyPartType.Back);
         coveredParts.put(Bag, var10);
    std::vector var11 = new std::vector();
         var11.push_back(BloodBodyPartType.Hand_L);
         var11.push_back(BloodBodyPartType.Hand_R);
         coveredParts.put(Hands, var11);
    std::vector var12 = new std::vector();
         var12.push_back(BloodBodyPartType.Head);
         coveredParts.put(Head, var12);
    std::vector var13 = new std::vector();
         var13.push_back(BloodBodyPartType.Neck);
         coveredParts.put(Neck, var13);
    std::vector var14 = new std::vector();
         var14.push_back(BloodBodyPartType.Groin);
         coveredParts.put(Groin, var14);
    std::vector var15 = new std::vector();
         var15.push_back(BloodBodyPartType.Torso_Upper);
         coveredParts.put(UpperBody, var15);
    std::vector var16 = new std::vector();
         var16.push_back(BloodBodyPartType.Torso_Lower);
         coveredParts.put(LowerBody, var16);
    std::vector var17 = new std::vector();
         var17.push_back(BloodBodyPartType.LowerLeg_L);
         var17.push_back(BloodBodyPartType.LowerLeg_R);
         coveredParts.put(LowerLegs, var17);
    std::vector var18 = new std::vector();
         var18.push_back(BloodBodyPartType.UpperLeg_L);
         var18.push_back(BloodBodyPartType.UpperLeg_R);
         coveredParts.put(UpperLegs, var18);
    std::vector var19 = new std::vector();
         var19.push_back(BloodBodyPartType.UpperArm_L);
         var19.push_back(BloodBodyPartType.UpperArm_R);
         coveredParts.put(UpperArms, var19);
    std::vector var20 = new std::vector();
         var20.push_back(BloodBodyPartType.ForeArm_L);
         var20.push_back(BloodBodyPartType.ForeArm_R);
         coveredParts.put(LowerArms, var20);
      }
   }

   public static std::vector<BloodBodyPartType> getCoveredParts(std::vector<BloodClothingType> var0) {
    return getCoveredParts(new std::vector<>();
   }

   public static std::vector<BloodBodyPartType> getCoveredParts(std::vector<BloodClothingType> var0, std::vector<BloodBodyPartType> var1) {
      if (var0 == nullptr) {
    return var1;
      } else {
         init();

         for (int var2 = 0; var2 < var0.size(); var2++) {
    BloodClothingType var3 = (BloodClothingType)var0.get(var2);
            var1.addAll(coveredParts.get(var3));
         }

    return var1;
      }
   }

    static int getCoveredPartCount(std::vector<BloodClothingType> var0) {
      if (var0 == nullptr) {
    return 0;
      } else {
         init();
    int var1 = 0;

         for (int var2 = 0; var2 < var0.size(); var2++) {
    BloodClothingType var3 = (BloodClothingType)var0.get(var2);
            var1 += coveredParts.get(var3).size();
         }

    return var1;
      }
   }

    static void addBlood(int var0, HumanVisual var1, std::vector<ItemVisual> var2, bool var3) {
      for (int var4 = 0; var4 < var0; var4++) {
    BloodBodyPartType var5 = BloodBodyPartType.FromIndex(Rand.Next(0, BloodBodyPartType.MAX.index()));
         addBlood(var5, var1, var2, var3);
      }
   }

    static void addBlood(BloodBodyPartType var0, HumanVisual var1, std::vector<ItemVisual> var2, bool var3) {
      init();
    float var4 = 0.0F;
      if (SandboxOptions.instance.ClothingDegradation.getValue() > 1) {
    float var5 = 0.01F;
    float var6 = 0.05F;
         if (SandboxOptions.instance.ClothingDegradation.getValue() == 2) {
            var5 = 0.001F;
            var6 = 0.01F;
         }

         if (SandboxOptions.instance.ClothingDegradation.getValue() == 3) {
            var5 = 0.05F;
            var6 = 0.1F;
         }

         var4 = OutfitRNG.Next(var5, var6);
      }

      addBlood(var0, var4, var1, var2, var3);
   }

    static void addDirt(BloodBodyPartType var0, HumanVisual var1, std::vector<ItemVisual> var2, bool var3) {
      init();
    float var4 = 0.0F;
      if (SandboxOptions.instance.ClothingDegradation.getValue() > 1) {
    float var5 = 0.01F;
    float var6 = 0.05F;
         if (SandboxOptions.instance.ClothingDegradation.getValue() == 2) {
            var5 = 0.001F;
            var6 = 0.01F;
         }

         if (SandboxOptions.instance.ClothingDegradation.getValue() == 3) {
            var5 = 0.05F;
            var6 = 0.1F;
         }

         var4 = OutfitRNG.Next(var5, var6);
      }

      addDirt(var0, var4, var1, var2, var3);
   }

    static void addHole(BloodBodyPartType var0, HumanVisual var1, std::vector<ItemVisual> var2) {
      addHole(var0, var1, var2, false);
   }

    static bool addHole(BloodBodyPartType var0, HumanVisual var1, std::vector<ItemVisual> var2, bool var3) {
      init();
    ItemVisual var4 = nullptr;
    bool var5 = false;

      for (int var6 = var2.size() - 1; var6 >= 0; var6--) {
    ItemVisual var7 = (ItemVisual)var2.get(var6);
    Item var8 = var7.getScriptItem();
         if (var8 != nullptr && (var7.getInventoryItem() == nullptr || !var7.getInventoryItem().isBroken())) {
    std::vector var9 = var8.getBloodClothingType();
            if (var9 != nullptr) {
               for (int var10 = 0; var10 < var9.size(); var10++) {
    BloodClothingType var11 = (BloodClothingType)var8.getBloodClothingType().get(var10);
                  if (coveredParts.get(var11).contains(var0) && var8.canHaveHoles && var7.getHole(var0) == 0.0F) {
                     var4 = var7;
                     break;
                  }
               }

               if (var4 != nullptr) {
                  var4.setHole(var0);
    Clothing var12 = (Clothing)Type.tryCastTo(var4.getInventoryItem(), Clothing.class);
                  if (var12 != nullptr) {
                     var12.removePatch(var0);
                     var12.setCondition(var12.getCondition() - var12.getCondLossPerHole());
                  }

                  var5 = true;
                  if (!var3) {
                     break;
                  }

                  var4 = nullptr;
               }
            }
         }
      }

      if (var4 == nullptr || var3) {
         var1.setHole(var0);
      }

    return var5;
   }

    static void addBasicPatch(BloodBodyPartType var0, HumanVisual var1, std::vector<ItemVisual> var2) {
      init();
    ItemVisual var3 = nullptr;

      for (int var4 = var2.size() - 1; var4 >= 0; var4--) {
    ItemVisual var5 = (ItemVisual)var2.get(var4);
    Item var6 = var5.getScriptItem();
         if (var6 != nullptr) {
    std::vector var7 = var6.getBloodClothingType();
            if (var7 != nullptr) {
               for (int var8 = 0; var8 < var7.size(); var8++) {
    BloodClothingType var9 = (BloodClothingType)var7.get(var8);
                  if (coveredParts.get(var9).contains(var0) && var5.getBasicPatch(var0) == 0.0F) {
                     var3 = var5;
                     break;
                  }
               }

               if (var3 != nullptr) {
                  break;
               }
            }
         }
      }

      if (var3 != nullptr) {
         var3.removeHole(BloodBodyPartType.ToIndex(var0));
         var3.setBasicPatch(var0);
      }
   }

    static void addDirt(BloodBodyPartType var0, float var1, HumanVisual var2, std::vector<ItemVisual> var3, bool var4) {
      init();
    ItemVisual var5 = nullptr;
      if (!var4) {
         for (int var6 = var3.size() - 1; var6 >= 0; var6--) {
    ItemVisual var7 = (ItemVisual)var3.get(var6);
    Item var8 = var7.getScriptItem();
            if (var8 != nullptr) {
    std::vector var9 = var8.getBloodClothingType();
               if (var9 != nullptr) {
                  for (int var10 = 0; var10 < var9.size(); var10++) {
    BloodClothingType var11 = (BloodClothingType)var9.get(var10);
                     if (coveredParts.get(var11).contains(var0) && var7.getHole(var0) == 0.0F) {
                        var5 = var7;
                        break;
                     }
                  }

                  if (var5 != nullptr) {
                     break;
                  }
               }
            }
         }

         if (var5 != nullptr) {
            if (var1 > 0.0F) {
               var5.setDirt(var0, var5.getDirt(var0) + var1);
               if (var5.getInventoryItem() instanceof Clothing) {
                  calcTotalDirtLevel((Clothing)var5.getInventoryItem());
               }
            }
         } else {
    float var15 = var2.getDirt(var0);
            var2.setDirt(var0, var15 + 0.05F);
         }
      } else {
    float var16 = var2.getDirt(var0);
         var2.setDirt(var0, var16 + 0.05F);
    float var17 = var2.getDirt(var0);
         if (Rand.NextBool(Math.abs(std::make_shared<float>(var17 * 100.0F).intValue() - 100))) {
            return;
         }

         for (int var18 = 0; var18 < var3.size(); var18++) {
            var5 = nullptr;
    ItemVisual var19 = (ItemVisual)var3.get(var18);
    Item var20 = var19.getScriptItem();
            if (var20 != nullptr) {
    std::vector var21 = var20.getBloodClothingType();
               if (var21 != nullptr) {
                  for (int var12 = 0; var12 < var21.size(); var12++) {
    BloodClothingType var13 = (BloodClothingType)var21.get(var12);
                     if (coveredParts.get(var13).contains(var0) && var19.getHole(var0) == 0.0F) {
                        var5 = var19;
                        break;
                     }
                  }

                  if (var5 != nullptr) {
                     if (var1 > 0.0F) {
                        var5.setDirt(var0, var5.getDirt(var0) + var1);
                        if (var5.getInventoryItem() instanceof Clothing) {
                           calcTotalDirtLevel((Clothing)var5.getInventoryItem());
                        }

                        var17 = var5.getDirt(var0);
                     }

                     if (Rand.NextBool(Math.abs(std::make_shared<float>(var17 * 100.0F).intValue() - 100))) {
                        break;
                     }
                  }
               }
            }
         }
      }
   }

    static void addBlood(BloodBodyPartType var0, float var1, HumanVisual var2, std::vector<ItemVisual> var3, bool var4) {
      init();
    ItemVisual var5 = nullptr;
      if (!var4) {
         for (int var6 = var3.size() - 1; var6 >= 0; var6--) {
    ItemVisual var7 = (ItemVisual)var3.get(var6);
    Item var8 = var7.getScriptItem();
            if (var8 != nullptr) {
    std::vector var9 = var8.getBloodClothingType();
               if (var9 != nullptr) {
                  for (int var10 = 0; var10 < var9.size(); var10++) {
    BloodClothingType var11 = (BloodClothingType)var9.get(var10);
                     if (coveredParts.get(var11).contains(var0) && var7.getHole(var0) == 0.0F) {
                        var5 = var7;
                        break;
                     }
                  }

                  if (var5 != nullptr) {
                     break;
                  }
               }
            }
         }

         if (var5 != nullptr) {
            if (var1 > 0.0F) {
               var5.setBlood(var0, var5.getBlood(var0) + var1);
               if (var5.getInventoryItem() instanceof Clothing) {
                  calcTotalBloodLevel((Clothing)var5.getInventoryItem());
               }
            }
         } else {
    float var15 = var2.getBlood(var0);
            var2.setBlood(var0, var15 + 0.05F);
         }
      } else {
    float var16 = var2.getBlood(var0);
         var2.setBlood(var0, var16 + 0.05F);
    float var17 = var2.getBlood(var0);
         if (OutfitRNG.NextBool(Math.abs(std::make_shared<float>(var17 * 100.0F).intValue() - 100))) {
            return;
         }

         for (int var18 = 0; var18 < var3.size(); var18++) {
            var5 = nullptr;
    ItemVisual var19 = (ItemVisual)var3.get(var18);
    Item var20 = var19.getScriptItem();
            if (var20 != nullptr) {
    std::vector var21 = var20.getBloodClothingType();
               if (var21 != nullptr) {
                  for (int var12 = 0; var12 < var21.size(); var12++) {
    BloodClothingType var13 = (BloodClothingType)var21.get(var12);
                     if (coveredParts.get(var13).contains(var0) && var19.getHole(var0) == 0.0F) {
                        var5 = var19;
                        break;
                     }
                  }

                  if (var5 != nullptr) {
                     if (var1 > 0.0F) {
                        var5.setBlood(var0, var5.getBlood(var0) + var1);
                        if (var5.getInventoryItem() instanceof Clothing) {
                           calcTotalBloodLevel((Clothing)var5.getInventoryItem());
                        }

                        var17 = var5.getBlood(var0);
                     }

                     if (OutfitRNG.NextBool(Math.abs(std::make_shared<float>(var17 * 100.0F).intValue() - 100))) {
                        break;
                     }
                  }
               }
            }
         }
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void calcTotalBloodLevel(Clothing var0) {
    ItemVisual var1 = var0.getVisual();
      if (var1 == nullptr) {
         var0.setBloodLevel(0.0F);
      } else {
    std::vector var2 = var0.getBloodClothingType();
         if (var2 == nullptr) {
            var0.setBloodLevel(0.0F);
         } else {
            bodyParts.clear();
            getCoveredParts(var2, bodyParts);
            if (bodyParts.empty()) {
               var0.setBloodLevel(0.0F);
            } else {
    float var3 = 0.0F;

               for (int var4 = 0; var4 < bodyParts.size(); var4++) {
                  var3 += var1.getBlood(bodyParts.get(var4)) * 100.0F;
               }

               var0.setBloodLevel(var3 / bodyParts.size());
            }
         }
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void calcTotalDirtLevel(Clothing var0) {
    ItemVisual var1 = var0.getVisual();
      if (var1 == nullptr) {
         var0.setDirtyness(0.0F);
      } else {
    std::vector var2 = var0.getBloodClothingType();
         if (var2 == nullptr) {
            var0.setDirtyness(0.0F);
         } else {
            bodyParts.clear();
            getCoveredParts(var2, bodyParts);
            if (bodyParts.empty()) {
               var0.setDirtyness(0.0F);
            } else {
    float var3 = 0.0F;

               for (int var4 = 0; var4 < bodyParts.size(); var4++) {
                  var3 += var1.getDirt(bodyParts.get(var4)) * 100.0F;
               }

               var0.setDirtyness(var3 / bodyParts.size());
            }
         }
      }
   }
}
} // namespace characterTextures
} // namespace zombie
