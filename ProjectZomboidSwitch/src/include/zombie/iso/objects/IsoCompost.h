#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoCompost : public IsoObject {
public:
    float compost = 0.0F;
    float LastUpdated = -1.0F;

    public IsoCompost(IsoCell var1) {
      super(var1);
   }

    public IsoCompost(IsoCell var1, IsoGridSquare var2) {
      super(var1, var2, IsoSpriteManager.instance.getSprite("camping_01_19"));
      this.sprite = IsoSpriteManager.instance.getSprite("camping_01_19");
      this.square = var2;
      this.container = std::make_unique<ItemContainer>();
      this.container.setType("composter");
      this.container.setParent(this);
      this.container.bExplored = true;
   }

    void update() {
      if (!GameClient.bClient && this.container != nullptr) {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours();
         if (this.LastUpdated < 0.0F) {
            this.LastUpdated = var1;
         } else if (this.LastUpdated > var1) {
            this.LastUpdated = var1;
         }

    float var2 = var1 - this.LastUpdated;
         if (!(var2 <= 0.0F)) {
            this.LastUpdated = var1;
    int var3 = SandboxOptions.instance.getCompostHours();

            for (int var4 = 0; var4 < this.container.getItems().size(); var4++) {
    InventoryItem var5 = (InventoryItem)this.container.getItems().get(var4);
               if (dynamic_cast<Food*>(var5) != nullptr var6) {
                  if (GameServer.bServer) {
                     var6.updateAge();
                  }

                  if (var6.isRotten()) {
                     if (this.getCompost() < 100.0F) {
                        var6.setRottenTime(0.0F);
                        var6.setCompostTime(var6.getCompostTime() + var2);
                     }

                     if (var6.getCompostTime() >= var3) {
                        this.setCompost(this.getCompost() + Math.abs(var6.getHungChange()) * 2.0F);
                        if (this.getCompost() > 100.0F) {
                           this.setCompost(100.0F);
                        }

                        if (GameServer.bServer) {
                           GameServer.sendCompost(this, nullptr);
                           GameServer.sendRemoveItemFromContainer(this.container, var5);
                        }

                        if (Rand.Next(10) == 0) {
    InventoryItem var7 = this.container.AddItem("Base.Worm");
                           if (GameServer.bServer && var7 != nullptr) {
                              GameServer.sendAddItemToContainer(this.container, var7);
                           }
                        }

                        var5.Use();
                        IsoWorld.instance.CurrentCell.addToProcessItemsRemove(var5);
                     }
                  }
               }
            }

            this.updateSprite();
         }
      }
   }

    void updateSprite() {
      if (this.getCompost() >= 10.0F && this.sprite.getName() == "camping_01_19")) {
         this.sprite = IsoSpriteManager.instance.getSprite("camping_01_20");
         this.transmitUpdatedSpriteToClients();
      } else if (this.getCompost() < 10.0F && this.sprite.getName() == "camping_01_20")) {
         this.sprite = IsoSpriteManager.instance.getSprite("camping_01_19");
         this.transmitUpdatedSpriteToClients();
      }
   }

    void syncCompost() {
      if (GameClient.bClient) {
         GameClient.sendCompost(this);
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (this.container != nullptr) {
         this.container.setType("composter");
      }

      this.compost = var1.getFloat();
      if (var2 >= 130) {
         this.LastUpdated = var1.getFloat();
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putFloat(this.compost);
      var1.putFloat(this.LastUpdated);
   }

    std::string getObjectName() {
      return "IsoCompost";
   }

    float getCompost() {
      return this.compost;
   }

    void setCompost(float var1) {
      this.compost = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    void remove() {
      if (this.getSquare() != nullptr) {
         this.getSquare().transmitRemoveItemFromSquare(this);
      }
   }

    void addToWorld() {
      this.getCell().addToProcessIsoObject(this);
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
      return this.isDestroyed() ? nullptr : this;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
