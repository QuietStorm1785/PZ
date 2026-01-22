#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Thermoregulator/ThermalNode.h"
#include "zombie/characters/ClothingWetness/ItemList.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Clothing.h"

namespace zombie {
namespace characters {


class ClothingWetness {
public:
    static const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
   private static const std::vector<BloodBodyPartType> coveredParts = std::make_unique<std::vector<>>();
    const IsoGameCharacter character;
   public const ItemList[] clothing = new ItemList[BloodBodyPartType.MAX.index()];
   public const int[] perspiringParts = new int[BloodBodyPartType.MAX.index()];
    bool changed = true;

    public ClothingWetness(IsoGameCharacter var1) {
      this.character = var1;

      for (int var2 = 0; var2 < this.clothing.length; var2++) {
         this.clothing[var2] = std::make_unique<ItemList>();
      }
   }

    void calculateExposedItems() {
      for (int var1 = 0; var1 < this.clothing.length; var1++) {
         this.clothing[var1].clear();
      }

      this.character.getItemVisuals(itemVisuals);

      for (int var7 = itemVisuals.size() - 1; var7 >= 0; var7--) {
    ItemVisual var2 = (ItemVisual)itemVisuals.get(var7);
    InventoryItem var3 = var2.getInventoryItem();
    std::vector var4 = var3.getBloodClothingType();
         if (var4 != nullptr) {
            coveredParts.clear();
            BloodClothingType.getCoveredParts(var4, coveredParts);

            for (int var5 = 0; var5 < coveredParts.size(); var5++) {
    BloodBodyPartType var6 = coveredParts.get(var5);
               this.clothing[var6.index()].push_back(var3);
            }
         }
      }
   }

    void updateWetness(float var1, float var2) {
    bool var3 = false;
    InventoryItem var4 = this.character.getPrimaryHandItem();
      if (var4 != nullptr && var4.isProtectFromRainWhileEquipped()) {
         var3 = true;
      }

      var4 = this.character.getSecondaryHandItem();
      if (var4 != nullptr && var4.isProtectFromRainWhileEquipped()) {
         var3 = true;
      }

      if (this.changed) {
         this.changed = false;
         this.calculateExposedItems();
      }

      this.character.getItemVisuals(itemVisuals);

      for (int var5 = 0; var5 < itemVisuals.size(); var5++) {
    InventoryItem var6 = ((ItemVisual)itemVisuals.get(var5)).getInventoryItem();
         if (dynamic_cast<Clothing*>(var6) != nullptr) {
            if (var6.getBloodClothingType() == nullptr) {
               ((Clothing)var6).updateWetness(true);
            } else {
               ((Clothing)var6).flushWetness();
            }
         }
      }

    float var27 = (float)ZomboidGlobals.WetnessIncrease * GameTime.instance.getMultiplier();
    float var28 = (float)ZomboidGlobals.WetnessDecrease * GameTime.instance.getMultiplier();

      label282:
      for (int var7 = 0; var7 < this.clothing.length; var7++) {
    BloodBodyPartType var8 = BloodBodyPartType.FromIndex(var7);
    BodyPartType var9 = BodyPartType.FromIndex(var7);
         if (var9 != BodyPartType.MAX) {
    BodyPart var10 = this.character.getBodyDamage().getBodyPart(var9);
    ThermalNode var11 = this.character.getBodyDamage().getThermoregulator().getNodeForBloodType(var8);
            if (var10 != nullptr && var11 != nullptr) {
    float var12 = 0.0F;
    float var13 = PZMath.clamp(var11.getSecondaryDelta(), 0.0F, 1.0F);
               var13 *= var13;
               var13 *= 0.2F + 0.8F * (1.0F - var11.getDistToCore());
               if (var13 > 0.1F) {
                  var12 += var13;
               } else {
    float var14 = (var11.getSkinCelcius() - 20.0F) / 22.0F;
                  var14 *= var14;
                  var14 -= var1;
                  var14 = Math.max(0.0F, var14);
                  var12 -= var14;
                  if (var1 > 0.0F) {
                     var12 = 0.0F;
                  }
               }

               this.perspiringParts[var7] = var12 > 0.0F ? 1 : 0;
               if (var12 != 0.0F) {
                  if (var12 > 0.0F) {
                     var12 *= var27;
                  } else {
                     var12 *= var28;
                  }

                  var10.setWetness(var10.getWetness() + var12);
                  if ((!(var12 > 0.0F) || !(var10.getWetness() < 25.0F)) && (!(var12 < 0.0F) || !(var10.getWetness() > 50.0F))) {
                     if (var12 > 0.0F) {
    float var44 = this.character.getBodyDamage().getThermoregulator().getExternalAirTemperature();
                        var44 += 10.0F;
                        var44 = PZMath.clamp(var44, 0.0F, 20.0F) / 20.0F;
                        var12 *= 0.4F + 0.6F * var44;
                     }

    bool var47 = false;
    bool var15 = false;
    bool var16 = false;
    float var17 = 1.0F;
    int var18 = this.clothing[var7].size() - 1;

    InventoryItem var19;
    Clothing var20;
                     while (true) {
                        if (var18 < 0) {
    continue label282;
                        }

                        if (var12 > 0.0F) {
                           this.perspiringParts[var7]++;
                        }

                        var19 = (InventoryItem)this.clothing[var7].get(var18);
                        if (dynamic_cast<Clothing*>(var19) != nullptr) {
                           var17 = 1.0F;
                           var20 = (Clothing)var19;
    ItemVisual var21 = var20.getVisual();
                           if (var21 == nullptr) {
                              break;
                           }

                           if (var21.getHole(var8) > 0.0F) {
                              var47 = true;
                           } else if (var12 > 0.0F && var20.getWetness() >= 100.0F) {
                              var15 = true;
                           } else {
                              if (!(var12 < 0.0F) || !(var20.getWetness() <= 0.0F)) {
                                 if (var12 > 0.0F && var20.getWaterResistance() > 0.0F) {
                                    var17 = PZMath.max(0.0F, 1.0F - var20.getWaterResistance());
                                    if (var17 <= 0.0F) {
                                       this.perspiringParts[var7]--;
    continue label282;
                                    }
                                 }
                                 break;
                              }

                              var16 = true;
                           }
                        }

                        var18--;
                     }

                     coveredParts.clear();
                     BloodClothingType.getCoveredParts(var19.getBloodClothingType(), coveredParts);
    int var22 = coveredParts.size();
    float var23 = var12;
                     if (var12 > 0.0F) {
                        var23 = var12 * var17;
                     }

                     if (var47 || var15 || var16) {
                        var23 /= 2.0F;
                     }

                     var20.setWetness(var20.getWetness() + var23);
                  }
               }
            }
         }
      }

      for (int var29 = 0; var29 < this.clothing.length; var29++) {
    BloodBodyPartType var30 = BloodBodyPartType.FromIndex(var29);
    BodyPartType var31 = BodyPartType.FromIndex(var29);
         if (var31 != BodyPartType.MAX) {
    BodyPart var32 = this.character.getBodyDamage().getBodyPart(var31);
    ThermalNode var33 = this.character.getBodyDamage().getThermoregulator().getNodeForBloodType(var30);
            if (var32 != nullptr && var33 != nullptr) {
    float var36 = 100.0F;
               if (var3) {
                  var36 = 100.0F * BodyPartType.GetUmbrellaMod(var31);
               }

    float var39 = 0.0F;
               if (var1 > 0.0F) {
                  var39 = var1 * var27;
               } else {
                  var39 -= var2 * var28;
               }

    bool var48 = false;
    bool var49 = false;
    bool var50 = false;
    float var52 = 1.0F;
    float var54 = 2.0F;

               for (int var56 = 0; var56 < this.clothing[var29].size(); var56++) {
    int var55 = 1 + (this.clothing[var29].size() - var56);
                  var52 = 1.0F;
    InventoryItem var58 = (InventoryItem)this.clothing[var29].get(var56);
                  if (dynamic_cast<Clothing*>(var58) != nullptr var60) {
    ItemVisual var61 = var60.getVisual();
                     if (var61 != nullptr) {
                        if (var61.getHole(var30) > 0.0F) {
                           var48 = true;
                           continue;
                        }

                        if (var39 > 0.0F && var60.getWetness() >= 100.0F) {
                           var49 = true;
                           continue;
                        }

                        if (var39 < 0.0F && var60.getWetness() <= 0.0F) {
                           var50 = true;
                           continue;
                        }

                        if (var39 > 0.0F && var60.getWaterResistance() > 0.0F) {
                           var52 = PZMath.max(0.0F, 1.0F - var60.getWaterResistance());
                           if (var52 <= 0.0F) {
                              break;
                           }
                        }
                     }

                     coveredParts.clear();
                     BloodClothingType.getCoveredParts(var58.getBloodClothingType(), coveredParts);
    int var24 = coveredParts.size();
    float var25 = var39;
                     if (var39 > 0.0F) {
                        var25 = var39 * var52;
                     }

                     var25 /= var24;
                     if (var48 || var49 || var50) {
                        var25 /= var54;
                     }

                     if (var39 < 0.0F && var55 > this.perspiringParts[var29] || var39 > 0.0F && var60.getWetness() <= var36) {
                        var60.setWetness(var60.getWetness() + var25);
                     }

                     if (var39 > 0.0F) {
                        break;
                     }

                     if (var50) {
                        var54 *= 2.0F;
                     }
                  }
               }

               if (!this.clothing[var29].empty()) {
    InventoryItem var57 = (InventoryItem)this.clothing[var29].get(this.clothing[var29].size() - 1);
                  if (dynamic_cast<Clothing*>(var57) != nullptr var59) {
                     if (var39 > 0.0F && this.perspiringParts[var29] == 0 && var59.getWetness() >= 50.0F && var32.getWetness() <= var36) {
                        var32.setWetness(var32.getWetness() + var39 / 2.0F);
                     }

                     if (var39 < 0.0F && this.perspiringParts[var29] == 0 && var59.getWetness() <= 50.0F) {
                        var32.setWetness(var32.getWetness() + var39 / 2.0F);
                     }
                  }
               } else if (var39 < 0.0F && this.perspiringParts[var29] == 0 || var32.getWetness() <= var36) {
                  var32.setWetness(var32.getWetness() + var39);
               }
            }
         }
      }
   }

    void increaseWetness(float var1) {
      if (!(var1 <= 0.0F)) {
         if (this.changed) {
            this.changed = false;
            this.calculateExposedItems();
         }

         this.character.getItemVisuals(itemVisuals);

         for (int var2 = 0; var2 < itemVisuals.size(); var2++) {
    InventoryItem var3 = ((ItemVisual)itemVisuals.get(var2)).getInventoryItem();
            if (dynamic_cast<Clothing*>(var3) != nullptr) {
               ((Clothing)var3).flushWetness();
            }
         }

    int var13 = 0;

         for (int var14 = 0; var14 < this.clothing.length; var14++) {
    BloodBodyPartType var4 = BloodBodyPartType.FromIndex(var14);
    bool var5 = false;
    bool var6 = false;
    int var7 = 0;

            label85: {
    InventoryItem var8;
               while (true) {
                  if (var7 >= this.clothing[var14].size()) {
    break label85;
                  }

                  var8 = (InventoryItem)this.clothing[var14].get(var7);
                  if (dynamic_cast<Clothing*>(var8) != nullptr var9) {
    ItemVisual var10 = var9.getVisual();
                     if (var10 == nullptr) {
                        break;
                     }

                     if (var10.getHole(var4) > 0.0F) {
                        var5 = true;
                     } else {
                        if (!(var9.getWetness() >= 100.0F)) {
                           break;
                        }

                        var6 = true;
                     }
                  }

                  var7++;
               }

               coveredParts.clear();
               BloodClothingType.getCoveredParts(var8.getBloodClothingType(), coveredParts);
    int var11 = coveredParts.size();
    float var12 = var1 / var11;
               if (var5 || var6) {
                  var12 /= 2.0F;
               }

               var9.setWetness(var9.getWetness() + var12);
            }

            if (this.clothing[var14].empty()) {
               var13++;
            } else {
    InventoryItem var17 = (InventoryItem)this.clothing[var14].get(this.clothing[var14].size() - 1);
               if (dynamic_cast<Clothing*>(var17) != nullptr var18 && var18.getWetness() >= 100.0F) {
                  var13++;
               }
            }
         }

         if (var13 > 0) {
    float var15 = this.character.getBodyDamage().getWetness();
    float var16 = var1 * ((float)var13 / this.clothing.length);
            this.character.getBodyDamage().setWetness(var15 + var16);
         }
      }
   }

    void decreaseWetness(float var1) {
      if (!(var1 <= 0.0F)) {
         if (this.changed) {
            this.changed = false;
            this.calculateExposedItems();
         }

         this.character.getItemVisuals(itemVisuals);

         for (int var2 = itemVisuals.size() - 1; var2 >= 0; var2--) {
    ItemVisual var3 = (ItemVisual)itemVisuals.get(var2);
            if (var3.getInventoryItem() instanceof Clothing var5 && var5.getWetness() > 0.0F) {
               var5.setWetness(var5.getWetness() - var1);
            }
         }
      }
   }
}
} // namespace characters
} // namespace zombie
