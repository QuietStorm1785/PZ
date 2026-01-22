#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Color.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoPushableObject.h"

namespace zombie {
namespace characters {


class IsoSurvivor : public IsoLivingCharacter {
public:
    bool NoGoreDeath = false;
    bool Draggable = false;
    IsoGameCharacter following = nullptr;
    bool Dragging;
    int repathDelay = 0;
    int nightsSurvived = 0;
    int ping = 0;
    IsoPushableObject collidePushable;
    bool tryToTeamUp = true;
    int NeightbourUpdate = 20;
    int NeightbourUpdateMax = 20;

    void Despawn() {
      if (this.descriptor != nullptr) {
         this.descriptor.Instance = nullptr;
      }
   }

    std::string getObjectName() {
      return "Survivor";
   }

    public IsoSurvivor(IsoCell var1) {
      super(var1, 0.0F, 0.0F, 0.0F);
      this.OutlineOnMouseover = true;
      this.getCell().getSurvivorList().push_back(this);
      LuaEventManager.triggerEvent("OnCreateSurvivor", this);
      this.initWornItems("Human");
      this.initAttachedItems("Human");
   }

    public IsoSurvivor(IsoCell var1, int var2, int var3, int var4) {
      super(var1, var2, var3, var4);
      this.getCell().getSurvivorList().push_back(this);
      this.OutlineOnMouseover = true;
      this.descriptor = std::make_unique<SurvivorDesc>();
      this.NeightbourUpdate = Rand.Next(this.NeightbourUpdateMax);
      this.sprite.LoadFramesPcx("Wife", "death", 1);
      this.sprite.LoadFramesPcx("Wife", "dragged", 1);
      this.sprite.LoadFramesPcx("Wife", "asleep_normal", 1);
      this.sprite.LoadFramesPcx("Wife", "asleep_bandaged", 1);
      this.sprite.LoadFramesPcx("Wife", "asleep_bleeding", 1);
      this.name = "Kate";
      this.solid = false;
      this.IgnoreStaggerBack = true;
      this.SpeakColour = std::make_shared<Color>(204, 100, 100);
      this.dir = IsoDirections.S;
      this.OutlineOnMouseover = true;
      this.finder.maxSearchDistance = 120;
      LuaEventManager.triggerEvent("OnCreateSurvivor", this);
      LuaEventManager.triggerEvent("OnCreateLivingCharacter", this, this.descriptor);
      this.initWornItems("Human");
      this.initAttachedItems("Human");
   }

    public IsoSurvivor(SurvivorDesc var1, IsoCell var2, int var3, int var4, int var5) {
      super(var2, var3, var4, var5);
      this.setFemale(var1.isFemale());
      this.descriptor = var1;
      var1.setInstance(this);
      this.OutlineOnMouseover = true;
    std::string var6 = "Zombie_palette";
      var6 = var6 + "01";
      this.InitSpriteParts(var1);
      this.SpeakColour = std::make_shared<Color>(Rand.Next(200) + 55, Rand.Next(200) + 55, Rand.Next(200) + 55, 255);
      this.finder.maxSearchDistance = 120;
      this.NeightbourUpdate = Rand.Next(this.NeightbourUpdateMax);
      this.Dressup(var1);
      LuaEventManager.triggerEventGarbage("OnCreateSurvivor", this);
      LuaEventManager.triggerEventGarbage("OnCreateLivingCharacter", this, this.descriptor);
      this.initWornItems("Human");
      this.initAttachedItems("Human");
   }

    void reloadSpritePart() {
   }

    public IsoSurvivor(SurvivorDesc var1, IsoCell var2, int var3, int var4, int var5, bool var6) {
      super(var2, var3, var4, var5);
      this.setFemale(var1.isFemale());
      this.descriptor = var1;
      if (var6) {
         var1.setInstance(this);
      }

      this.OutlineOnMouseover = true;
      this.InitSpriteParts(var1);
      this.SpeakColour = std::make_shared<Color>(Rand.Next(200) + 55, Rand.Next(200) + 55, Rand.Next(200) + 55, 255);
      this.finder.maxSearchDistance = 120;
      this.NeightbourUpdate = Rand.Next(this.NeightbourUpdateMax);
      this.Dressup(var1);
      LuaEventManager.triggerEvent("OnCreateSurvivor", this);
   }
}
} // namespace characters
} // namespace zombie
