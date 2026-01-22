#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemParams/FoodState.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/WeaponPartParams.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    float worldScale = 1.0F;
    float worldZRotation = 0.0F;
    FoodState m_foodState = FoodState.Normal;
    Model m_model;
   private std::vector<WeaponPartParams> m_weaponParts;
    float m_hue;
    float m_tintR;
    float m_tintG;
    float m_tintB;
    const Vector3f m_angle = std::make_shared<Vector3f>();
    const Matrix4f m_transform = std::make_shared<Matrix4f>();
    float m_ambientR = 1.0F;
    float m_ambientG = 1.0F;
    float m_ambientB = 1.0F;
    float alpha = 1.0F;

    void copyFrom(WorldItemAtlas$ItemParams var1) {
      this.worldScale = var1.worldScale;
      this.worldZRotation = var1.worldZRotation;
      this.m_foodState = var1.m_foodState;
      this.m_model = var1.m_model;
      if (this.m_weaponParts != nullptr) {
         WorldItemAtlas.instance.weaponPartParamPool.release(this.m_weaponParts);
         this.m_weaponParts.clear();
      }

      if (var1.m_weaponParts != nullptr) {
         if (this.m_weaponParts == nullptr) {
            this.m_weaponParts = std::make_unique<std::vector<>>();
         }

         for (int var2 = 0; var2 < var1.m_weaponParts.size(); var2++) {
    WeaponPartParams var3 = var1.m_weaponParts.get(var2);
            this.m_weaponParts.push_back(((WeaponPartParams)WorldItemAtlas.instance.weaponPartParamPool.alloc()).init(var3));
         }
      }

      this.m_hue = var1.m_hue;
      this.m_tintR = var1.m_tintR;
      this.m_tintG = var1.m_tintG;
      this.m_tintB = var1.m_tintB;
      this.m_angle.set(var1.m_angle);
      this.m_transform.set(var1.m_transform);
   }

    bool init(InventoryItem var1) {
      this.Reset();
      this.worldScale = var1.worldScale;
      this.worldZRotation = var1.worldZRotation;
    float var2 = 0.0F;
    std::string var3 = StringUtils.discardNullOrWhitespace(var1.getWorldStaticItem());
      if (var3 != nullptr) {
    ModelScript var16 = ScriptManager.instance.getModelScript(var3);
         if (var16 == nullptr) {
    return false;
         } else {
    std::string var18 = var16.getMeshName();
    std::string var20 = var16.getTextureName();
    std::string var22 = var16.getShaderName();
    ImmutableColor var24 = ImmutableColor.white;
    float var26 = 1.0F;
    Food var28 = (Food)Type.tryCastTo(var1, Food.class);
            if (var28 != nullptr) {
               this.m_foodState = this.getFoodState(var28);
               if (var28.isCooked()) {
    ModelScript var30 = ScriptManager.instance.getModelScript(var1.getWorldStaticItem() + "Cooked");
                  if (var30 != nullptr) {
                     var20 = var30.getTextureName();
                     var18 = var30.getMeshName();
                     var22 = var30.getShaderName();
                     var16 = var30;
                  }
               }

               if (var28.isBurnt()) {
    ModelScript var31 = ScriptManager.instance.getModelScript(var1.getWorldStaticItem() + "Burnt");
                  if (var31 != nullptr) {
                     var20 = var31.getTextureName();
                     var18 = var31.getMeshName();
                     var22 = var31.getShaderName();
                     var16 = var31;
                  }
               }

               if (var28.isRotten()) {
    ModelScript var32 = ScriptManager.instance.getModelScript(var1.getWorldStaticItem() + "Rotten");
                  if (var32 != nullptr) {
                     var20 = var32.getTextureName();
                     var18 = var32.getMeshName();
                     var22 = var32.getShaderName();
                     var16 = var32;
                  } else {
                     var24 = WorldItemAtlas.ROTTEN_FOOD_COLOR;
                  }
               }
            }

    Clothing var33 = (Clothing)Type.tryCastTo(var1, Clothing.class);
            if (var33 != nullptr || var1.getClothingItem() != nullptr) {
    std::string var37 = var16.getTextureName(true);
    ItemVisual var40 = var1.getVisual();
    ClothingItem var44 = var1.getClothingItem();
    ImmutableColor var15 = var40.getTint(var44);
               if (var37 == nullptr) {
                  if (var44.textureChoices.empty()) {
                     var37 = var40.getBaseTexture(var44);
                  } else {
                     var37 = var40.getTextureChoice(var44);
                  }
               }

               if (var37 != nullptr) {
                  var20 = var37;
                  var24 = var15;
               }
            }

    bool var38 = var16.bStatic;
    Model var41 = ModelManager.instance.tryGetLoadedModel(var18, var20, var38, var22, true);
            if (var41 == nullptr) {
               ModelManager.instance.loadAdditionalModel(var18, var20, var38, var22);
            }

            var41 = ModelManager.instance.getLoadedModel(var18, var20, var38, var22);
            if (var41 != nullptr && var41.isReady() && var41.Mesh != nullptr && var41.Mesh.isReady()) {
               this.init(var1, var41, var16, var26, var24, var2, false);
               if (this.worldScale != 1.0F) {
                  this.m_transform.scale(var16.scale * this.worldScale);
               } else if (var16.scale != 1.0F) {
                  this.m_transform.scale(var16.scale);
               }

               this.m_angle.x = 0.0F;
               this.m_angle.y = this.worldZRotation;
               this.m_angle.z = 0.0F;
    return true;
            } else {
    return false;
            }
         }
      } else {
    Clothing var4 = (Clothing)Type.tryCastTo(var1, Clothing.class);
         if (var4 == nullptr) {
    HandWeapon var17 = (HandWeapon)Type.tryCastTo(var1, HandWeapon.class);
            if (var17 != nullptr) {
    std::string var19 = StringUtils.discardNullOrWhitespace(var17.getStaticModel());
               if (var19 == nullptr) {
    return false;
               } else {
    ModelScript var21 = ScriptManager.instance.getModelScript(var19);
                  if (var21 == nullptr) {
    return false;
                  } else {
    std::string var23 = var21.getMeshName();
    std::string var25 = var21.getTextureName();
    std::string var27 = var21.getShaderName();
    bool var29 = var21.bStatic;
    Model var35 = ModelManager.instance.tryGetLoadedModel(var23, var25, var29, var27, false);
                     if (var35 == nullptr) {
                        ModelManager.instance.loadAdditionalModel(var23, var25, var29, var27);
                     }

                     var35 = ModelManager.instance.getLoadedModel(var23, var25, var29, var27);
                     if (var35 != nullptr && var35.isReady() && var35.Mesh != nullptr && var35.Mesh.isReady()) {
    float var39 = 1.0F;
    ImmutableColor var43 = ImmutableColor.white;
                        this.init(var1, var35, var21, var39, var43, var2, true);
                        if (this.worldScale != 1.0F) {
                           this.m_transform.scale(var21.scale * this.worldScale);
                        } else if (var21.scale != 1.0F) {
                           this.m_transform.scale(var21.scale);
                        }

                        this.m_angle.x = 0.0F;
                        this.m_angle.y = this.worldZRotation;
                        return this.initWeaponParts(var17, var21);
                     } else {
    return false;
                     }
                  }
               }
            } else {
    return false;
            }
         } else {
    ClothingItem var5 = var1.getClothingItem();
    ItemVisual var6 = var1.getVisual();
    bool var7 = false;
    std::string var8 = var5.getModel(var7);
            if (var5 != nullptr
               && var6 != nullptr
               && !StringUtils.isNullOrWhitespace(var8)
               && "Bip01_Head".equalsIgnoreCase(var5.m_AttachBone)
               && (!var4.isCosmetic() || "Eyes" == var1.getBodyLocation()))) {
    std::string var9 = var6.getTextureChoice(var5);
    bool var10 = var5.m_Static;
    std::string var11 = var5.m_Shader;
    Model var12 = ModelManager.instance.tryGetLoadedModel(var8, var9, var10, var11, false);
               if (var12 == nullptr) {
                  ModelManager.instance.loadAdditionalModel(var8, var9, var10, var11);
               }

               var12 = ModelManager.instance.getLoadedModel(var8, var9, var10, var11);
               if (var12 != nullptr && var12.isReady() && var12.Mesh != nullptr && var12.Mesh.isReady()) {
    float var13 = var6.getHue(var5);
    ImmutableColor var14 = var6.getTint(var5);
                  this.init(var1, var12, nullptr, var13, var14, var2, false);
                  this.m_angle.x = 180.0F + var2;
                  this.m_angle.y = this.worldZRotation;
                  this.m_angle.z = -90.0F;
                  this.m_transform.translate(-0.08F, 0.0F, 0.05F);
    return true;
               } else {
    return false;
               }
            } else {
    return false;
            }
         }
      }
   }

    bool initWeaponParts(HandWeapon var1, ModelScript var2) {
    std::vector var3 = var1.getModelWeaponPart();
      if (var3 == nullptr) {
    return true;
      } else {
    std::vector var4 = var1.getAllWeaponParts(WorldItemAtlas.instance.m_tempWeaponPartList);

         for (int var5 = 0; var5 < var4.size(); var5++) {
    WeaponPart var6 = (WeaponPart)var4.get(var5);

            for (int var7 = 0; var7 < var3.size(); var7++) {
    ModelWeaponPart var8 = (ModelWeaponPart)var3.get(var7);
               if (var6.getFullType() == var8.partType)) {
                  if (!this.initWeaponPart(var8, var2)) {
    return false;
                  }
                  break;
               }
            }
         }

    return true;
      }
   }

    bool initWeaponPart(ModelWeaponPart var1, ModelScript var2) {
    std::string var3 = StringUtils.discardNullOrWhitespace(var1.modelName);
      if (var3 == nullptr) {
    return false;
      } else {
    ModelScript var4 = ScriptManager.instance.getModelScript(var3);
         if (var4 == nullptr) {
    return false;
         } else {
    std::string var5 = var4.getMeshName();
    std::string var6 = var4.getTextureName();
    std::string var7 = var4.getShaderName();
    bool var8 = var4.bStatic;
    Model var9 = ModelManager.instance.tryGetLoadedModel(var5, var6, var8, var7, false);
            if (var9 == nullptr) {
               ModelManager.instance.loadAdditionalModel(var5, var6, var8, var7);
            }

            var9 = ModelManager.instance.getLoadedModel(var5, var6, var8, var7);
            if (var9 != nullptr && var9.isReady() && var9.Mesh != nullptr && var9.Mesh.isReady()) {
    WeaponPartParams var10 = (WeaponPartParams)WorldItemAtlas.instance.weaponPartParamPool.alloc();
               var10.m_model = var9;
               var10.m_attachmentNameSelf = var1.attachmentNameSelf;
               var10.m_attachmentNameParent = var1.attachmentParent;
               var10.initTransform(var2, var4);
               if (this.m_weaponParts == nullptr) {
                  this.m_weaponParts = std::make_unique<std::vector<>>();
               }

               this.m_weaponParts.push_back(var10);
    return true;
            } else {
    return false;
            }
         }
      }
   }

    void init(InventoryItem var1, Model var2, ModelScript var3, float var4, ImmutableColor var5, float var6, bool var7) {
      this.m_model = var2;
      this.m_tintR = var5.r;
      this.m_tintG = var5.g;
      this.m_tintB = var5.b;
      this.m_hue = var4;
      this.m_angle.set(0.0F);
      this.m_transform.identity();
      this.m_ambientR = this.m_ambientG = this.m_ambientB = 1.0F;
      if (var7) {
         this.m_transform.rotateXYZ(0.0F, (float) Math.PI, (float) (Math.PI / 2));
      }

      if (var3 != nullptr) {
    ModelAttachment var8 = var3.getAttachmentById("world");
         if (var8 != nullptr) {
            ModelInstanceRenderData.makeAttachmentTransform(var8, WorldItemAtlas.s_attachmentXfrm);
            WorldItemAtlas.s_attachmentXfrm.invert();
            this.m_transform.mul(WorldItemAtlas.s_attachmentXfrm);
         }
      }

      if (var2.Mesh != nullptr && var2.Mesh.isReady() && var2.Mesh.m_transform != nullptr) {
         var2.Mesh.m_transform.transpose();
         this.m_transform.mul(var2.Mesh.m_transform);
         var2.Mesh.m_transform.transpose();
      }
   }

    FoodState getFoodState(Food var1) {
    FoodState var2 = FoodState.Normal;
      if (var1.isCooked()) {
         var2 = FoodState.Cooked;
      }

      if (var1.isBurnt()) {
         var2 = FoodState.Burnt;
      }

      if (var1.isRotten()) {
         var2 = FoodState.Rotten;
      }

    return var2;
   }

    bool isStillValid(InventoryItem var1) {
      if (var1.worldScale == this.worldScale && var1.worldZRotation == this.worldZRotation) {
    Food var2 = (Food)Type.tryCastTo(var1, Food.class);
    return var2 = = nullptr || this.getFoodState(var2) == this.m_foodState;
      } else {
    return false;
      }
   }

    void Reset() {
      this.m_model = nullptr;
      this.m_foodState = FoodState.Normal;
      if (this.m_weaponParts != nullptr) {
         WorldItemAtlas.instance.weaponPartParamPool.release(this.m_weaponParts);
         this.m_weaponParts.clear();
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
