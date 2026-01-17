#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Color.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoPushableObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoSurvivor : public IsoLivingCharacter {
public:
  bool NoGoreDeath = false;
  bool Draggable = false;
  IsoGameCharacter following = null;
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

  std::string getObjectName() { return "Survivor"; }

public
  IsoSurvivor(IsoCell cell) {
    super(cell, 0.0F, 0.0F, 0.0F);
    this.OutlineOnMouseover = true;
    this.getCell().getSurvivorList().add(this);
    LuaEventManager.triggerEvent("OnCreateSurvivor", this);
    this.initWornItems("Human");
    this.initAttachedItems("Human");
  }

public
  IsoSurvivor(IsoCell cell, int x, int y, int z) {
    super(cell, x, y, z);
    this.getCell().getSurvivorList().add(this);
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
    this.SpeakColour = new Color(204, 100, 100);
    this.dir = IsoDirections.S;
    this.OutlineOnMouseover = true;
    this.finder.maxSearchDistance = 120;
    LuaEventManager.triggerEvent("OnCreateSurvivor", this);
    LuaEventManager.triggerEvent("OnCreateLivingCharacter", this,
                                 this.descriptor);
    this.initWornItems("Human");
    this.initAttachedItems("Human");
  }

public
  IsoSurvivor(SurvivorDesc desc, IsoCell cell, int x, int y, int z) {
    super(cell, x, y, z);
    this.setFemale(desc.isFemale());
    this.descriptor = desc;
    desc.setInstance(this);
    this.OutlineOnMouseover = true;
    std::string string = "Zombie_palette";
    string = string + "01";
    this.InitSpriteParts(desc);
    this.SpeakColour = new Color(Rand.Next(200) + 55, Rand.Next(200) + 55,
                                 Rand.Next(200) + 55, 255);
    this.finder.maxSearchDistance = 120;
    this.NeightbourUpdate = Rand.Next(this.NeightbourUpdateMax);
    this.Dressup(desc);
    LuaEventManager.triggerEventGarbage("OnCreateSurvivor", this);
    LuaEventManager.triggerEventGarbage("OnCreateLivingCharacter", this,
                                        this.descriptor);
    this.initWornItems("Human");
    this.initAttachedItems("Human");
  }

  void reloadSpritePart() {}

public
  IsoSurvivor(SurvivorDesc desc, IsoCell cell, int x, int y, int z,
              bool bSetInstance) {
    super(cell, x, y, z);
    this.setFemale(desc.isFemale());
    this.descriptor = desc;
    if (bSetInstance) {
      desc.setInstance(this);
    }

    this.OutlineOnMouseover = true;
    this.InitSpriteParts(desc);
    this.SpeakColour = new Color(Rand.Next(200) + 55, Rand.Next(200) + 55,
                                 Rand.Next(200) + 55, 255);
    this.finder.maxSearchDistance = 120;
    this.NeightbourUpdate = Rand.Next(this.NeightbourUpdateMax);
    this.Dressup(desc);
    LuaEventManager.triggerEvent("OnCreateSurvivor", this);
  }
}
} // namespace characters
} // namespace zombie
