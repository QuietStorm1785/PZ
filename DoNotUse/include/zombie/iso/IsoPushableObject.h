#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/objects/IsoWheelieBin.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace iso {


class IsoPushableObject : public IsoMovingObject {
public:
    int carryCapacity = 100;
    float emptyWeight = 4.5F;
   public std::vector<IsoPushableObject> connectList = nullptr;
    float ox = 0.0F;
    float oy = 0.0F;

    public IsoPushableObject(IsoCell var1) {
      super(var1);
      this.getCell().getPushableObjectList().push_back(this);
   }

    public IsoPushableObject(IsoCell var1, int var2, int var3, int var4) {
      super(var1, true);
      this.getCell().getPushableObjectList().push_back(this);
   }

    public IsoPushableObject(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3, true);
      this.setX(var2.getX() + 0.5F);
      this.setY(var2.getY() + 0.5F);
      this.setZ(var2.getZ());
      this.ox = this.getX();
      this.oy = this.getY();
      this.setNx(this.getX());
      this.setNy(this.getNy());
      this.offsetX = 6 * Core.TileScale;
      this.offsetY = -30 * Core.TileScale;
      this.setWeight(6.0F);
      this.square = var2;
      this.setCurrent(var2);
      this.getCurrentSquare().getMovingObjects().push_back(this);
      this.Collidable = true;
      this.solid = true;
      this.shootable = false;
      this.width = 0.5F;
      this.setAlphaAndTarget(0.0F);
      this.getCell().getPushableObjectList().push_back(this);
   }

    std::string getObjectName() {
      return "Pushable";
   }

    void update() {
      if (this.connectList != nullptr) {
    Iterator var1 = this.connectList.iterator();
    float var2 = 0.0F;

         while (var1.hasNext()) {
    IsoPushableObject var3 = (IsoPushableObject)var1.next();
    float var4 = var3.getAlpha();
            if (var4 > var2) {
               var2 = var4;
            }
         }

         this.setAlphaAndTarget(var2);
      }

      super.update();
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (!(dynamic_cast<IsoWheelieBin*>(this) != nullptr)) {
         this.sprite = IsoSpriteManager.instance.getSprite(var1.getInt());
      }

      if (var1.get() == 1) {
         this.container = std::make_unique<ItemContainer>();
         this.container.load(var1, var2);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      if (!(dynamic_cast<IsoWheelieBin*>(this) != nullptr)) {
         var1.putInt(this.sprite.ID);
      }

      if (this.container != nullptr) {
         var1.put((byte)1);
         this.container.save(var1);
      } else {
         var1.put((byte)0);
      }
   }

    float getWeight(float var1, float var2) {
      if (this.container == nullptr) {
         return this.emptyWeight;
      } else {
    float var3 = this.container.getContentsWeight() / this.carryCapacity;
         if (var3 < 0.0F) {
            var3 = 0.0F;
         }

         return var3 > 1.0F ? this.getWeight() * 8.0F : this.getWeight() * var3 + this.emptyWeight;
      }
   }

    bool Serialize() {
    return true;
   }

    void DoCollideNorS() {
      if (this.connectList == nullptr) {
         super.DoCollideNorS();
      } else {
         for (IsoPushableObject var2 : this.connectList) {
            if (var2 != this) {
               if (var2.ox < this.ox) {
                  var2.setNx(this.getNx() - 1.0F);
                  var2.setX(this.getX() - 1.0F);
               } else if (var2.ox > this.ox) {
                  var2.setNx(this.getNx() + 1.0F);
                  var2.setX(this.getX() + 1.0F);
               } else {
                  var2.setNx(this.getNx());
                  var2.setX(this.getX());
               }

               if (var2.oy < this.oy) {
                  var2.setNy(this.getNy() - 1.0F);
                  var2.setY(this.getY() - 1.0F);
               } else if (var2.oy > this.oy) {
                  var2.setNy(this.getNy() + 1.0F);
                  var2.setY(this.getY() + 1.0F);
               } else {
                  var2.setNy(this.getNy());
                  var2.setY(this.getY());
               }

               var2.setImpulsex(this.getImpulsex());
               var2.setImpulsey(this.getImpulsey());
            }
         }
      }
   }

    void DoCollideWorE() {
      if (this.connectList == nullptr) {
         super.DoCollideWorE();
      } else {
         for (IsoPushableObject var2 : this.connectList) {
            if (var2 != this) {
               if (var2.ox < this.ox) {
                  var2.setNx(this.getNx() - 1.0F);
                  var2.setX(this.getX() - 1.0F);
               } else if (var2.ox > this.ox) {
                  var2.setNx(this.getNx() + 1.0F);
                  var2.setX(this.getX() + 1.0F);
               } else {
                  var2.setNx(this.getNx());
                  var2.setX(this.getX());
               }

               if (var2.oy < this.oy) {
                  var2.setNy(this.getNy() - 1.0F);
                  var2.setY(this.getY() - 1.0F);
               } else if (var2.oy > this.oy) {
                  var2.setNy(this.getNy() + 1.0F);
                  var2.setY(this.getY() + 1.0F);
               } else {
                  var2.setNy(this.getNy());
                  var2.setY(this.getY());
               }

               var2.setImpulsex(this.getImpulsex());
               var2.setImpulsey(this.getImpulsey());
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
