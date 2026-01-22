#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/AttachedItems/AttachedModelNames.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    HumanVisual humanVisual;
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    IsoDirections dir;
    float angle;
    bool bFemale;
    bool bZombie;
    bool bSkeleton;
    std::string animSetName;
    std::string stateName;
   const std::unordered_map<std::string, std::string> variables = std::make_unique<std::unordered_map<>>();
    bool bStanding;
    std::string primaryHandItem;
    std::string secondaryHandItem;
    const AttachedModelNames attachedModelNames = std::make_shared<AttachedModelNames>();
    float x;
    float y;
    float z;
    float trackTime;
    bool bOutside;
    bool bRoom;
    const ColorInfo ambient = std::make_shared<ColorInfo>();
    bool fallOnFront = false;
   const ResultLight[] lights = new ResultLight[5];

   DeadBodyAtlas$BodyParams() {
      for (int var1 = 0; var1 < this.lights.length; var1++) {
         this.lights[var1] = std::make_unique<ResultLight>();
      }
   }

    void init(DeadBodyAtlas$BodyParams var1) {
      this.humanVisual = var1.humanVisual;
      this.itemVisuals.clear();
      this.itemVisuals.addAll(var1.itemVisuals);
      this.dir = var1.dir;
      this.angle = var1.angle;
      this.bFemale = var1.bFemale;
      this.bZombie = var1.bZombie;
      this.bSkeleton = var1.bSkeleton;
      this.animSetName = var1.animSetName;
      this.stateName = var1.stateName;
      this.variables.clear();
      this.variables.putAll(var1.variables);
      this.bStanding = var1.bStanding;
      this.primaryHandItem = var1.primaryHandItem;
      this.secondaryHandItem = var1.secondaryHandItem;
      this.attachedModelNames.copyFrom(var1.attachedModelNames);
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.trackTime = var1.trackTime;
      this.fallOnFront = var1.fallOnFront;
      this.bOutside = var1.bOutside;
      this.bRoom = var1.bRoom;
      this.ambient.set(var1.ambient.r, var1.ambient.g, var1.ambient.b, 1.0F);

      for (int var2 = 0; var2 < this.lights.length; var2++) {
         this.lights[var2].copyFrom(var1.lights[var2]);
      }
   }

    void init(IsoDeadBody var1) {
      this.humanVisual = var1.getHumanVisual();
      var1.getItemVisuals(this.itemVisuals);
      this.dir = var1.dir;
      this.angle = var1.getAngle();
      this.bFemale = var1.isFemale();
      this.bZombie = var1.isZombie();
      this.bSkeleton = var1.isSkeleton();
      this.primaryHandItem = nullptr;
      this.secondaryHandItem = nullptr;
      this.attachedModelNames.initFrom(var1.getAttachedItems());
      this.animSetName = "zombie";
      this.stateName = "onground";
      this.variables.clear();
      this.bStanding = false;
      if (var1.getPrimaryHandItem() != nullptr || var1.getSecondaryHandItem() != nullptr) {
         if (var1.getPrimaryHandItem() != nullptr && !StringUtils.isNullOrEmpty(var1.getPrimaryHandItem().getStaticModel())) {
            this.primaryHandItem = var1.getPrimaryHandItem().getStaticModel();
         }

         if (var1.getSecondaryHandItem() != nullptr && !StringUtils.isNullOrEmpty(var1.getSecondaryHandItem().getStaticModel())) {
            this.secondaryHandItem = var1.getSecondaryHandItem().getStaticModel();
         }

         this.animSetName = "player";
         this.stateName = "deadbody";
      }

      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.trackTime = 0.0F;
      this.fallOnFront = var1.isFallOnFront();
      this.bOutside = var1.square != nullptr && var1.square.isOutside();
      this.bRoom = var1.square != nullptr && var1.square.getRoom() != nullptr;
      this.initAmbient(var1.square);
      this.initLights(var1.square);
   }

    void init(IsoZombie var1) {
      this.humanVisual = var1.getHumanVisual();
      var1.getItemVisuals(this.itemVisuals);
      this.dir = var1.dir;
      this.angle = var1.getAnimAngleRadians();
      this.bFemale = var1.isFemale();
      this.bZombie = true;
      this.bSkeleton = var1.isSkeleton();
      this.primaryHandItem = nullptr;
      this.secondaryHandItem = nullptr;
      this.attachedModelNames.initFrom(var1.getAttachedItems());
      this.animSetName = "zombie";
      this.stateName = "onground";
      this.variables.clear();
      this.bStanding = false;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.trackTime = 0.0F;
      this.fallOnFront = var1.isFallOnFront();
      this.bOutside = var1.getCurrentSquare() != nullptr && var1.getCurrentSquare().isOutside();
      this.bRoom = var1.getCurrentSquare() != nullptr && var1.getCurrentSquare().getRoom() != nullptr;
      this.initAmbient(var1.getCurrentSquare());
      this.initLights(var1.getCurrentSquare());
   }

    void init(IsoMannequin var1) {
      this.humanVisual = var1.getHumanVisual();
      var1.getItemVisuals(this.itemVisuals);
      this.dir = var1.dir;
      this.angle = this.dir.ToVector().getDirection();
      this.bFemale = var1.isFemale();
      this.bZombie = var1.isZombie();
      this.bSkeleton = var1.isSkeleton();
      this.primaryHandItem = nullptr;
      this.secondaryHandItem = nullptr;
      this.attachedModelNames.clear();
      this.animSetName = var1.getAnimSetName();
      this.stateName = var1.getAnimStateName();
      this.variables.clear();
      var1.getVariables(this.variables);
      this.bStanding = true;
      this.x = var1.getX();
      this.y = var1.getY();
      this.z = var1.getZ();
      this.trackTime = 0.0F;
      this.fallOnFront = false;
      this.bOutside = var1.square != nullptr && var1.square.isOutside();
      this.bRoom = var1.square != nullptr && var1.square.getRoom() != nullptr;
      this.initAmbient(var1.square);
      this.initLights(nullptr);
   }

    void init(IHumanVisual var1, IsoDirections var2, const std::string& var3, const std::string& var4, float var5) {
      this.humanVisual = var1.getHumanVisual();
      var1.getItemVisuals(this.itemVisuals);
      this.dir = var2;
      this.angle = var2.ToVector().getDirection();
      this.bFemale = var1.isFemale();
      this.bZombie = var1.isZombie();
      this.bSkeleton = var1.isSkeleton();
      this.primaryHandItem = nullptr;
      this.secondaryHandItem = nullptr;
      this.attachedModelNames.clear();
      this.animSetName = var3;
      this.stateName = var4;
      this.variables.clear();
      this.bStanding = true;
      this.x = 0.0F;
      this.y = 0.0F;
      this.z = 0.0F;
      this.trackTime = var5;
      this.fallOnFront = false;
      this.bOutside = true;
      this.bRoom = false;
      this.ambient.set(1.0F, 1.0F, 1.0F, 1.0F);
      this.initLights(nullptr);
   }

    void initAmbient(IsoGridSquare var1) {
      this.ambient.set(1.0F, 1.0F, 1.0F, 1.0F);
   }

    void initLights(IsoGridSquare var1) {
      for (int var2 = 0; var2 < this.lights.length; var2++) {
         this.lights[var2].radius = 0;
      }

      if (var1 != nullptr) {
    ILighting var5 = var1.lighting[0];
    int var3 = var5.resultLightCount();

         for (int var4 = 0; var4 < var3; var4++) {
            this.lights[var4].copyFrom(var5.getResultLight(var4));
         }
      }
   }

    void Reset() {
      this.humanVisual = nullptr;
      this.itemVisuals.clear();
      Arrays.fill(this.lights, nullptr);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
