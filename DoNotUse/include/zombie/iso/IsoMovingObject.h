#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/CollisionManager.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MovingObjectUpdateScheduler.h"
#include "zombie/ai/State.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/ai/states/AttackState.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/CollideWithWallState.h"
#include "zombie/ai/states/CrawlingZombieTurnState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject/1.h"
#include "zombie/iso/IsoMovingObject/L_postUpdate.h"
#include "zombie/iso/IsoMovingObject/L_slideAwayFromWalls.h"
#include "zombie/iso/IsoMovingObject/TreeSoundManager.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/isoregion/regions/IWorldRegion.h"
#include "zombie/iso/objects/IsoMolotovCocktail.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/RenderEffectType.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoMovingObject : public IsoObject {
public:
    static TreeSoundManager treeSoundMgr = std::make_shared<TreeSoundManager>();
    static const int MAX_ZOMBIES_EATING = 3;
    static int IDCount = 0;
    static const Vector2 tempo = std::make_shared<Vector2>();
    bool noDamage = false;
    IsoGridSquare last = nullptr;
    float lx;
    float ly;
    float lz;
    float nx;
    float ny;
    float x;
    float y;
    float z;
    IsoSpriteInstance def = nullptr;
    IsoGridSquare current = nullptr;
    Vector2 hitDir = std::make_shared<Vector2>();
    int ID = 0;
    IsoGridSquare movingSq = nullptr;
    bool solid = true;
    float width = 0.24F;
    bool shootable = true;
    bool Collidable = true;
    float scriptnx = 0.0F;
    float scriptny = 0.0F;
    std::string ScriptModule = "none";
    Vector2 movementLastFrame = std::make_shared<Vector2>();
    float weight = 1.0F;
    bool bOnFloor = false;
    bool closeKilled = false;
    std::string collideType = nullptr;
    float lastCollideTime = 0.0F;
    int TimeSinceZombieAttack = 1000000;
    bool collidedE = false;
    bool collidedN = false;
    IsoObject CollidedObject = nullptr;
    bool collidedS = false;
    bool collidedThisFrame = false;
    bool collidedW = false;
    bool CollidedWithDoor = false;
    bool collidedWithVehicle = false;
    bool destroyed = false;
    bool firstUpdate = true;
    float impulsex = 0.0F;
    float impulsey = 0.0F;
    float limpulsex = 0.0F;
    float limpulsey = 0.0F;
    float hitForce = 0.0F;
    float hitFromAngle;
    int PathFindIndex = -1;
    float StateEventDelayTimer = 0.0F;
    Thumpable thumpTarget = nullptr;
    bool bAltCollide = false;
    IsoZombie lastTargettedBy = nullptr;
    float feelersize = 0.5F;
   public const boolean[] bOutline = new boolean[4];
   public const ColorInfo[] outlineColor = new ColorInfo[4];
   private const std::vector<IsoZombie> eatingZombies = std::make_unique<std::vector<>>();
    bool zombiesDontAttack = false;

    public IsoMovingObject(IsoCell var1) {
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      if (var1 != nullptr) {
         this.ID = IDCount++;
         if (this.getCell().isSafeToAdd()) {
            this.getCell().getObjectList().push_back(this);
         } else {
            this.getCell().getAddList().push_back(this);
         }
      }
   }

    public IsoMovingObject(IsoCell var1, bool var2) {
      this.ID = IDCount++;
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      if (var2) {
         if (this.getCell().isSafeToAdd()) {
            this.getCell().getObjectList().push_back(this);
         } else {
            this.getCell().getAddList().push_back(this);
         }
      }
   }

    public IsoMovingObject(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4) {
      this.ID = IDCount++;
      this.sprite = var3;
      if (var4) {
         if (this.getCell().isSafeToAdd()) {
            this.getCell().getObjectList().push_back(this);
         } else {
            this.getCell().getAddList().push_back(this);
         }
      }
   }

    public IsoMovingObject() {
      this.ID = IDCount++;
      this.getCell().getAddList().push_back(this);
   }

    static int getIDCount() {
    return IDCount;
   }

    static void setIDCount(int var0) {
      IDCount = var0;
   }

    IsoBuilding getBuilding() {
      if (this.current == nullptr) {
    return nullptr;
      } else {
    IsoRoom var1 = this.current.getRoom();
    return var1 = = nullptr ? nullptr : var1.building;
      }
   }

    IWorldRegion getMasterRegion() {
      return this.current != nullptr ? this.current.getIsoWorldRegion() : nullptr;
   }

    float getWeight() {
      return this.weight;
   }

    void setWeight(float var1) {
      this.weight = var1;
   }

    float getWeight(float var1, float var2) {
      return this.weight;
   }

    void onMouseRightClick(int var1, int var2) {
      if (this.square.getZ() == (int)IsoPlayer.getInstance().getZ() && this.DistToProper(IsoPlayer.getInstance()) <= 2.0F) {
         IsoPlayer.getInstance().setDragObject(this);
      }
   }

    std::string getObjectName() {
      return "IsoMovingObject";
   }

    void onMouseRightReleased() {
   }

    void collideWith(IsoObject var1) {
      if (dynamic_cast<IsoGameCharacter*>(this) != nullptr && dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
         LuaEventManager.triggerEvent("OnCharacterCollide", this, var1);
      } else {
         LuaEventManager.triggerEvent("OnObjectCollide", this, var1);
      }
   }

    void doStairs() {
      if (this.current != nullptr) {
         if (this.last != nullptr) {
            if (!(dynamic_cast<IsoPhysicsObject*>(this) != nullptr)) {
    IsoGridSquare var1 = this.current;
               if (var1.z > 0 && (var1.Has(IsoObjectType.stairsTN) || var1.Has(IsoObjectType.stairsTW)) && this.z - (int)this.z < 0.1F) {
    IsoGridSquare var2 = IsoWorld.instance.CurrentCell.getGridSquare(var1.x, var1.y, var1.z - 1);
                  if (var2 != nullptr && (var2.Has(IsoObjectType.stairsTN) || var2.Has(IsoObjectType.stairsTW))) {
                     var1 = var2;
                  }
               }

               if (dynamic_cast<IsoGameCharacter*>(this) != nullptr && (this.last.Has(IsoObjectType.stairsTN) || this.last.Has(IsoObjectType.stairsTW))) {
                  this.z = Math.round(this.z);
               }

    float var4 = this.z;
               if (var1.HasStairs()) {
                  var4 = var1.getApparentZ(this.x - var1.getX(), this.y - var1.getY());
               }

               if (dynamic_cast<IsoGameCharacter*>(this) != nullptr) {
    State var3 = ((IsoGameCharacter)this).getCurrentState();
                  if (var3 == ClimbOverFenceState.instance() || var3 == ClimbThroughWindowState.instance()) {
                     if (var1.HasStairs() && this.z > var4) {
                        this.z = Math.max(var4, this.z - 0.075F * GameTime.getInstance().getMultiplier());
                     }

                     return;
                  }
               }

               if (Math.abs(var4 - this.z) < 0.95F) {
                  this.z = var4;
               }
            }
         }
      }
   }

    int getID() {
      return this.ID;
   }

    void setID(int var1) {
      this.ID = var1;
   }

    int getPathFindIndex() {
      return this.PathFindIndex;
   }

    void setPathFindIndex(int var1) {
      this.PathFindIndex = var1;
   }

    float getScreenX() {
      return IsoUtils.XToScreen(this.x, this.y, this.z, 0);
   }

    float getScreenY() {
      return IsoUtils.YToScreen(this.x, this.y, this.z, 0);
   }

    Thumpable getThumpTarget() {
      return this.thumpTarget;
   }

    void setThumpTarget(Thumpable var1) {
      this.thumpTarget = var1;
   }

    Vector2 getVectorFromDirection(Vector2 var1) {
    return getVectorFromDirection();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static Vector2 getVectorFromDirection(Vector2 var0, IsoDirections var1) {
      if (var0 == nullptr) {
         DebugLog.General.warn("Supplied vector2 is nullptr. Cannot be processed. Using fail-safe fallback.");
         var0 = std::make_unique<Vector2>();
      }

      var0.x = 0.0F;
      var0.y = 0.0F;
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var1.ordinal()]) {
         case 1:
            var0.x = 0.0F;
            var0.y = 1.0F;
            break;
         case 2:
            var0.x = 0.0F;
            var0.y = -1.0F;
            break;
         case 3:
            var0.x = 1.0F;
            var0.y = 0.0F;
            break;
         case 4:
            var0.x = -1.0F;
            var0.y = 0.0F;
            break;
         case 5:
            var0.x = -1.0F;
            var0.y = -1.0F;
            break;
         case 6:
            var0.x = 1.0F;
            var0.y = -1.0F;
            break;
         case 7:
            var0.x = -1.0F;
            var0.y = 1.0F;
            break;
         case 8:
            var0.x = 1.0F;
            var0.y = 1.0F;
      }

      var0.normalize();
    return var0;
   }

    Vector3 getPosition(Vector3 var1) {
      var1.set(this.getX(), this.getY(), this.getZ());
    return var1;
   }

    float getX() {
      return this.x;
   }

    void setX(float var1) {
      this.x = var1;
      this.nx = var1;
      this.scriptnx = var1;
   }

    float getY() {
      return this.y;
   }

    void setY(float var1) {
      this.y = var1;
      this.ny = var1;
      this.scriptny = var1;
   }

    float getZ() {
      return this.z;
   }

    void setZ(float var1) {
      this.z = var1;
      this.lz = var1;
   }

    IsoGridSquare getSquare() {
      return this.current != nullptr ? this.current : this.square;
   }

    IsoBuilding getCurrentBuilding() {
      if (this.current == nullptr) {
    return nullptr;
      } else {
         return this.current.getRoom() == nullptr ? nullptr : this.current.getRoom().building;
      }
   }

    float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
      return 0.0F;
   }

    void Move(Vector2 var1) {
      this.nx = this.nx + var1.x * GameTime.instance.getMultiplier();
      this.ny = this.ny + var1.y * GameTime.instance.getMultiplier();
      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         this.current = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, (int)this.z);
      }
   }

    void MoveUnmodded(Vector2 var1) {
      this.nx = this.nx + var1.x;
      this.ny = this.ny + var1.y;
      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         this.current = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, (int)this.z);
      }
   }

    bool isCharacter() {
      return dynamic_cast<IsoGameCharacter*>(this) != nullptr;
   }

    float DistTo(int var1, int var2) {
      return IsoUtils.DistanceManhatten(var1, var2, this.x, this.y);
   }

    float DistTo(IsoMovingObject var1) {
      return IsoUtils.DistanceManhatten(this.x, this.y, var1.x, var1.y);
   }

    float DistToProper(IsoObject var1) {
      return IsoUtils.DistanceTo(this.x, this.y, var1.getX(), var1.getY());
   }

    float DistToSquared(IsoMovingObject var1) {
      return IsoUtils.DistanceToSquared(this.x, this.y, var1.x, var1.y);
   }

    float DistToSquared(float var1, float var2) {
      return IsoUtils.DistanceToSquared(var1, var2, this.x, this.y);
   }

    void load(ByteBuffer var1, int var2, bool var3) {
    float var4 = var1.getFloat();
    float var5 = var1.getFloat();
      this.x = this.lx = this.nx = this.scriptnx = var1.getFloat() + IsoWorld.saveoffsetx * 300;
      this.y = this.ly = this.ny = this.scriptny = var1.getFloat() + IsoWorld.saveoffsety * 300;
      this.z = this.lz = var1.getFloat();
      this.dir = IsoDirections.fromIndex(var1.getInt());
      if (var1.get() != 0) {
         if (this.table == nullptr) {
            this.table = LuaManager.platform.newTable();
         }

         this.table.load(var1, var2);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      var1.put((byte)(this.Serialize() ? 1 : 0));
      var1.put(IsoObject.factoryGetClassID(this.getObjectName()));
      var1.putFloat(this.offsetX);
      var1.putFloat(this.offsetY);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putFloat(this.z);
      var1.putInt(this.dir.index());
      if (this.table != nullptr && !this.table.empty()) {
         var1.put((byte)1);
         this.table.save(var1);
      } else {
         var1.put((byte)0);
      }
   }

    void removeFromWorld() {
    IsoCell var1 = this.getCell();
      if (var1.isSafeToAdd()) {
         var1.getObjectList().remove(this);
         var1.getRemoveList().remove(this);
      } else {
         var1.getRemoveList().push_back(this);
      }

      var1.getAddList().remove(this);
      MovingObjectUpdateScheduler.instance.removeObject(this);
      super.removeFromWorld();
   }

    void removeFromSquare() {
      if (this.current != nullptr) {
         this.current.getMovingObjects().remove(this);
      }

      if (this.last != nullptr) {
         this.last.getMovingObjects().remove(this);
      }

      if (this.movingSq != nullptr) {
         this.movingSq.getMovingObjects().remove(this);
      }

      this.current = this.last = this.movingSq = nullptr;
      if (this.square != nullptr) {
         this.square.getStaticMovingObjects().remove(this);
      }

      super.removeFromSquare();
   }

    IsoGridSquare getFuturWalkedSquare() {
      if (this.current != nullptr) {
    IsoGridSquare var1 = this.getFeelerTile(this.feelersize);
         if (var1 != nullptr && var1 != this.current) {
    return var1;
         }
      }

    return nullptr;
   }

    float getGlobalMovementMod() {
      return this.getGlobalMovementMod(true);
   }

    float getGlobalMovementMod(bool var1) {
      if (this.current != nullptr && this.z - (int)this.z < 0.5F) {
         if (this.current.Has(IsoObjectType.tree) || this.current.getProperties() != nullptr && this.current.getProperties().Is("Bush")) {
            if (var1) {
               this.doTreeNoises();
            }

            for (int var2 = 1; var2 < this.current.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)this.current.getObjects().get(var2);
               if (dynamic_cast<IsoTree*>(var3) != nullptr) {
                  var3.setRenderEffect(RenderEffectType.Vegetation_Rustle);
               } else if (var3.getProperties() != nullptr && var3.getProperties().Is("Bush")) {
                  var3.setRenderEffect(RenderEffectType.Vegetation_Rustle);
               }
            }
         }

    IsoGridSquare var5 = this.getFeelerTile(this.feelersize);
         if (var5 != nullptr && var5 != this.current && (var5.Has(IsoObjectType.tree) || var5.getProperties() != nullptr && var5.getProperties().Is("Bush"))) {
            if (var1) {
               this.doTreeNoises();
            }

            for (int var6 = 1; var6 < var5.getObjects().size(); var6++) {
    IsoObject var4 = (IsoObject)var5.getObjects().get(var6);
               if (dynamic_cast<IsoTree*>(var4) != nullptr) {
                  var4.setRenderEffect(RenderEffectType.Vegetation_Rustle);
               } else if (var4.getSprite() != nullptr && var4.getProperties().Is("Bush")) {
                  var4.setRenderEffect(RenderEffectType.Vegetation_Rustle);
               }
            }
         }
      }

      return this.current != nullptr && this.current.HasStairs() ? 0.75F : 1.0F;
   }

    void doTreeNoises() {
      if (!GameServer.bServer) {
         if (!(dynamic_cast<IsoPhysicsObject*>(this) != nullptr)) {
            if (this.current != nullptr) {
               if (Rand.Next(Rand.AdjustForFramerate(50)) == 0) {
                  treeSoundMgr.addSquare(this.current);
               }
            }
         }
      }
   }

    void postupdate() {
    IsoGameCharacter var1 = (IsoGameCharacter)Type.tryCastTo(this, IsoGameCharacter.class);
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
    IsoZombie var3 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
      this.slideAwayFromWalls();
      if (var3 != nullptr && GameServer.bServer && !var3.isCurrentState(ZombieIdleState.instance())) {
    bool var4 = false;
      }

      if (var2 != nullptr && var2.isLocalPlayer()) {
         IsoPlayer.setInstance(var2);
         IsoCamera.CamCharacter = var2;
      }

      this.ensureOnTile();
      if (this.lastTargettedBy != nullptr && this.lastTargettedBy.isDead()) {
         this.lastTargettedBy = nullptr;
      }

      if (this.lastTargettedBy != nullptr && this.TimeSinceZombieAttack > 120) {
         this.lastTargettedBy = nullptr;
      }

      this.TimeSinceZombieAttack++;
      if (var2 != nullptr) {
         var2.setLastCollidedW(this.collidedW);
         var2.setLastCollidedN(this.collidedN);
      }

      if (!this.destroyed) {
         this.collidedThisFrame = false;
         this.collidedN = false;
         this.collidedS = false;
         this.collidedW = false;
         this.collidedE = false;
         this.CollidedWithDoor = false;
         this.last = this.current;
         this.CollidedObject = nullptr;
         this.nx = this.nx + this.impulsex;
         this.ny = this.ny + this.impulsey;
         if (this.nx < 0.0F) {
            this.nx = 0.0F;
         }

         if (this.ny < 0.0F) {
            this.ny = 0.0F;
         }

         tempo.set(this.nx - this.x, this.ny - this.y);
         if (tempo.getLength() > 1.0F) {
            tempo.normalize();
            this.nx = this.x + tempo.getX();
            this.ny = this.y + tempo.getY();
         }

         this.impulsex = 0.0F;
         this.impulsey = 0.0F;
         if (var3 == nullptr
            || (int)this.z != 0
            || this.getCurrentBuilding() != nullptr
            || this.isInLoadedArea((int)this.nx, (int)this.ny)
            || !var3.isCurrentState(PathFindState.instance()) && !var3.isCurrentState(WalkTowardState.instance())) {
    float var14 = this.nx;
    float var5 = this.ny;
            this.collidedWithVehicle = false;
            if (var1 != nullptr && !this.isOnFloor() && var1.getVehicle() == nullptr && this.isCollidable() && (var2 == nullptr || !var2.isNoClip())) {
    int var6 = (int)this.x;
    int var7 = (int)this.y;
    int var8 = (int)this.nx;
    int var9 = (int)this.ny;
    int var10 = (int)this.z;
               if (var1.getCurrentState() == nullptr || !var1.getCurrentState().isIgnoreCollide(var1, var6, var7, var10, var8, var9, var10)) {
    Vector2f var12 = PolygonalMap2.instance.resolveCollision(var1, this.nx, this.ny, L_postUpdate.vector2f);
                  if (var12.x != this.nx || var12.y != this.ny) {
                     this.nx = var12.x;
                     this.ny = var12.y;
                     this.collidedWithVehicle = true;
                  }
               }
            }

    float var15 = this.nx;
    float var16 = this.ny;
    float var17 = 0.0F;
    bool var19 = false;
            if (this.Collidable) {
               if (this.bAltCollide) {
                  this.DoCollide(2);
               } else {
                  this.DoCollide(1);
               }

               if (this.collidedN || this.collidedS) {
                  this.ny = this.ly;
                  this.DoCollideNorS();
               }

               if (this.collidedW || this.collidedE) {
                  this.nx = this.lx;
                  this.DoCollideWorE();
               }

               if (this.bAltCollide) {
                  this.DoCollide(1);
               } else {
                  this.DoCollide(2);
               }

               this.bAltCollide = !this.bAltCollide;
               if (this.collidedN || this.collidedS) {
                  this.ny = this.ly;
                  this.DoCollideNorS();
                  var19 = true;
               }

               if (this.collidedW || this.collidedE) {
                  this.nx = this.lx;
                  this.DoCollideWorE();
                  var19 = true;
               }

               var17 = Math.abs(this.nx - this.lx) + Math.abs(this.ny - this.ly);
    float var22 = this.nx;
    float var11 = this.ny;
               this.nx = var15;
               this.ny = var16;
               if (this.Collidable && var19) {
                  if (this.bAltCollide) {
                     this.DoCollide(2);
                  } else {
                     this.DoCollide(1);
                  }

                  if (this.collidedN || this.collidedS) {
                     this.ny = this.ly;
                     this.DoCollideNorS();
                  }

                  if (this.collidedW || this.collidedE) {
                     this.nx = this.lx;
                     this.DoCollideWorE();
                  }

                  if (this.bAltCollide) {
                     this.DoCollide(1);
                  } else {
                     this.DoCollide(2);
                  }

                  if (this.collidedN || this.collidedS) {
                     this.ny = this.ly;
                     this.DoCollideNorS();
                     var19 = true;
                  }

                  if (this.collidedW || this.collidedE) {
                     this.nx = this.lx;
                     this.DoCollideWorE();
                     var19 = true;
                  }

                  if (Math.abs(this.nx - this.lx) + Math.abs(this.ny - this.ly) < var17) {
                     this.nx = var22;
                     this.ny = var11;
                  }
               }
            }

            if (this.collidedThisFrame) {
               this.current = this.last;
            }

            this.checkHitWall();
            if (var2 != nullptr
               && !var2.isCurrentState(CollideWithWallState.instance())
               && !this.collidedN
               && !this.collidedS
               && !this.collidedW
               && !this.collidedE) {
               this.setCollideType(nullptr);
            }

    float var23 = this.nx - this.x;
    float var24 = this.ny - this.y;
    float var25 = !(Math.abs(var23) > 0.0F) && !(Math.abs(var24) > 0.0F) ? 0.0F : this.getGlobalMovementMod();
            if (Math.abs(var23) > 0.01F || Math.abs(var24) > 0.01F) {
               var23 *= var25;
               var24 *= var25;
            }

            this.x += var23;
            this.y += var24;
            this.doStairs();
            this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
            if (this.current == nullptr) {
               for (int var13 = (int)this.z; var13 >= 0; var13--) {
                  this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, var13);
                  if (this.current != nullptr) {
                     break;
                  }
               }

               if (this.current == nullptr && this.last != nullptr) {
                  this.current = this.last;
                  this.x = this.nx = this.scriptnx = this.current.getX() + 0.5F;
                  this.y = this.ny = this.scriptny = this.current.getY() + 0.5F;
               }
            }

            if (this.movingSq != nullptr) {
               this.movingSq.getMovingObjects().remove(this);
               this.movingSq = nullptr;
            }

            if (this.current != nullptr && !this.current.getMovingObjects().contains(this)) {
               this.current.getMovingObjects().push_back(this);
               this.movingSq = this.current;
            }

            this.ensureOnTile();
            this.square = this.current;
            this.scriptnx = this.nx;
            this.scriptny = this.ny;
            this.firstUpdate = false;
         } else {
            ZombiePopulationManager.instance.virtualizeZombie(var3);
         }
      }
   }

    void ensureOnTile() {
      if (this.current == nullptr) {
         if (!(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
            if (dynamic_cast<IsoSurvivor*>(this) != nullptr) {
               IsoWorld.instance.CurrentCell.Remove(this);
               IsoWorld.instance.CurrentCell.getSurvivorList().remove(this);
            }

            return;
         }

    bool var1 = true;
    bool var2 = false;
         if (this.last != nullptr && (this.last.Has(IsoObjectType.stairsTN) || this.last.Has(IsoObjectType.stairsTW))) {
            this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z + 1);
            var1 = false;
         }

         if (this.current == nullptr) {
            this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
            return;
         }

         if (var1) {
            this.x = this.nx = this.scriptnx = this.current.getX() + 0.5F;
            this.y = this.ny = this.scriptny = this.current.getY() + 0.5F;
         }

         this.z = this.current.getZ();
      }
   }

    void preupdate() {
      this.nx = this.x;
      this.ny = this.y;
   }

    void renderlast() {
      this.bOutline[IsoCamera.frameState.playerIndex] = false;
   }

    void spotted(IsoMovingObject var1, bool var2) {
   }

    void update() {
      if (this.def == nullptr) {
         this.def = IsoSpriteInstance.get(this.sprite);
      }

      this.movementLastFrame.x = this.x - this.lx;
      this.movementLastFrame.y = this.y - this.ly;
      this.lx = this.x;
      this.ly = this.y;
      this.lz = this.z;
      this.square = this.current;
      if (this.sprite != nullptr) {
         this.sprite.update(this.def);
      }

      this.StateEventDelayTimer = this.StateEventDelayTimer - GameTime.instance.getMultiplier();
   }

    void Collided() {
      this.collidedThisFrame = true;
   }

    int compareToY(IsoMovingObject var1) {
      if (this.sprite == nullptr && var1.sprite == nullptr) {
    return 0;
      } else if (this.sprite != nullptr && var1.sprite == nullptr) {
         return -1;
      } else if (this.sprite == nullptr) {
    return 1;
      } else {
    float var2 = IsoUtils.YToScreen(this.x, this.y, this.z, 0);
    float var3 = IsoUtils.YToScreen(var1.x, var1.y, var1.z, 0);
         if (var2 > var3) {
    return 1;
         } else {
            return var2 < var3 ? -1 : 0;
         }
      }
   }

    float distToNearestCamCharacter() {
    float var1 = float.MAX_VALUE;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr) {
            var1 = Math.min(var1, this.DistTo(var3));
         }
      }

    return var1;
   }

    bool isSolidForSeparate() {
      if (dynamic_cast<IsoZombieGiblets*>(this) != nullptr) {
    return false;
      } else if (this.current == nullptr) {
    return false;
      } else {
         return !this.solid ? false : !this.isOnFloor();
      }
   }

    bool isPushableForSeparate() {
    return true;
   }

    bool isPushedByForSeparate(IsoMovingObject var1) {
    return true;
   }

    void separate() {
      if (this.isSolidForSeparate()) {
         if (this.isPushableForSeparate()) {
    IsoGameCharacter var1 = (IsoGameCharacter)Type.tryCastTo(this, IsoGameCharacter.class);
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
            if (this.z < 0.0F) {
               this.z = 0.0F;
            }

            for (int var3 = 0; var3 <= 8; var3++) {
    IsoGridSquare var4 = var3 == 8 ? this.current : this.current.nav[var3];
               if (var4 != nullptr && !var4.getMovingObjects().empty() && (var4 == this.current || !this.current.isBlockedTo(var4))) {
    float var5 = var2 != nullptr && var2.getPrimaryHandItem() instanceof HandWeapon ? ((HandWeapon)var2.getPrimaryHandItem()).getMaxRange() : 0.3F;
    int var6 = 0;

                  for (int var7 = var4.getMovingObjects().size(); var6 < var7; var6++) {
    IsoMovingObject var8 = (IsoMovingObject)var4.getMovingObjects().get(var6);
                     if (var8 != this && var8.isSolidForSeparate() && !(Math.abs(this.z - var8.z) > 0.3F)) {
    IsoGameCharacter var9 = (IsoGameCharacter)Type.tryCastTo(var8, IsoGameCharacter.class);
    IsoPlayer var10 = (IsoPlayer)Type.tryCastTo(var8, IsoPlayer.class);
    float var11 = this.width + var8.width;
    Vector2 var12 = tempo;
                        var12.x = this.nx - var8.nx;
                        var12.y = this.ny - var8.ny;
    float var13 = var12.getLength();
                        if (var1 == nullptr || var9 == nullptr && !(dynamic_cast<BaseVehicle*>(var8) != nullptr)) {
                           if (var13 < var11) {
                              CollisionManager.instance.AddContact(this, var8);
                           }

                           return;
                        }

                        if (var9 != nullptr) {
                           if (var2 != nullptr
                              && var2.getBumpedChr() != var8
                              && var13 < var11 + var5
                              && var2.getForwardDirection().angleBetween(var12) > 2.6179938155736564
                              && var2.getBeenSprintingFor() >= 70.0F
                              && WeaponType.getWeaponType(var2) == WeaponType.spear) {
                              var2.reportEvent("ChargeSpearConnect");
                              var2.setAttackType("charge");
                              var2.attackStarted = true;
                              var2.setVariable("StartedAttackWhileSprinting", true);
                              var2.setBeenSprintingFor(0.0F);
                              return;
                           }

                           if (!(var13 >= var11)) {
    bool var14 = false;
                              if (var2 != nullptr && var2.getVariableFloat("WalkSpeed", 0.0F) > 0.2F && var2.runningTime > 0.5F && var2.getBumpedChr() != var8) {
                                 var14 = true;
                              }

                              if (GameClient.bClient && var2 != nullptr && dynamic_cast<IsoPlayer*>(var9) != nullptr && !ServerOptions.getInstance().PlayerBumpPlayer.getValue()) {
                                 var14 = false;
                              }

                              if (var14 && !"charge" == var2.getAttackType())) {
                                 boolean var15 = !this.isOnFloor()
                                    && (var1.getBumpedChr() != nullptr || (System.currentTimeMillis() - var2.getLastBump()) / 100L < 15L || var2.isSprinting())
                                    && (var10 == nullptr || !var10.isNPC());
                                 if (var15) {
                                    var1.bumpNbr++;
    int var16 = 10 - var1.bumpNbr * 3;
                                    var16 += var1.getPerkLevel(Perks.Fitness);
                                    var16 += var1.getPerkLevel(Perks.Strength);
                                    if (var1.Traits.Clumsy.isSet()) {
                                       var16 -= 5;
                                    }

                                    if (var1.Traits.Graceful.isSet()) {
                                       var16 += 5;
                                    }

                                    if (var1.Traits.VeryUnderweight.isSet()) {
                                       var16 -= 8;
                                    }

                                    if (var1.Traits.Underweight.isSet()) {
                                       var16 -= 4;
                                    }

                                    if (var1.Traits.Obese.isSet()) {
                                       var16 -= 8;
                                    }

                                    if (var1.Traits.Overweight.isSet()) {
                                       var16 -= 4;
                                    }

    BodyPart var17 = var1.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
                                    if (var17.getAdditionalPain(true) > 20.0F) {
                                       var16 = (int)(var16 - (var17.getAdditionalPain(true) - 20.0F) / 20.0F);
                                    }

                                    var16 = Math.min(80, var16);
                                    var16 = Math.max(1, var16);
                                    if (Rand.Next(var16) == 0 || var1.isSprinting()) {
                                       var1.setVariable("BumpDone", false);
                                       var1.setBumpFall(true);
                                       var1.setVariable("TripObstacleType", "zombie");
                                    }
                                 } else {
                                    var1.bumpNbr = 0;
                                 }

                                 var1.setLastBump(System.currentTimeMillis());
                                 var1.setBumpedChr(var9);
                                 var1.setBumpType(this.getBumpedType(var9));
    bool var22 = var1.isBehind(var9);
    std::string var23 = var1.getBumpType();
                                 if (var22) {
                                    if (var23 == "left")) {
                                       var23 = "right";
                                    } else {
                                       var23 = "left";
                                    }
                                 }

                                 var9.setBumpType(var23);
                                 var9.setHitFromBehind(var22);
                                 if (var15 | GameClient.bClient) {
                                    var1.actionContext.reportEvent("wasBumped");
                                 }
                              }

                              if (GameServer.bServer || this.distToNearestCamCharacter() < 60.0F) {
                                 if (this.isPushedByForSeparate(var8)) {
                                    var12.setLength((var13 - var11) / 8.0F);
                                    this.nx = this.nx - var12.x;
                                    this.ny = this.ny - var12.y;
                                 }

                                 this.collideWith(var8);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    std::string getBumpedType(IsoGameCharacter var1) {
    float var2 = this.x - var1.x;
    float var3 = this.y - var1.y;
    std::string var4 = "left";
      if (this.dir == IsoDirections.S || this.dir == IsoDirections.SE || this.dir == IsoDirections.SW) {
         if (var2 < 0.0F) {
            var4 = "left";
         } else {
            var4 = "right";
         }
      }

      if (this.dir == IsoDirections.N || this.dir == IsoDirections.NE || this.dir == IsoDirections.NW) {
         if (var2 > 0.0F) {
            var4 = "left";
         } else {
            var4 = "right";
         }
      }

      if (this.dir == IsoDirections.E) {
         if (var3 > 0.0F) {
            var4 = "left";
         } else {
            var4 = "right";
         }
      }

      if (this.dir == IsoDirections.W) {
         if (var3 < 0.0F) {
            var4 = "left";
         } else {
            var4 = "right";
         }
      }

    return var4;
   }

    void slideAwayFromWalls() {
      if (this.current != nullptr) {
    IsoZombie var1 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
         if (var1 != nullptr && (this.isOnFloor() || var1.isKnockedDown())) {
            if (!var1.isCrawling() || var1.getPath2() == nullptr && !var1.isMoving()) {
               if (!var1.isCurrentState(ClimbOverFenceState.instance()) && !var1.isCurrentState(ClimbThroughWindowState.instance())) {
                  if (var1.hasAnimationPlayer() && var1.getAnimationPlayer().isReady()) {
    Vector3 var2 = L_slideAwayFromWalls.vector3;
                     Model.BoneToWorldCoords(var1, var1.getAnimationPlayer().getSkinningBoneIndex("Bip01_Head", -1), var2);
                     if (Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderRadius.getValue()) {
                        LineDrawer.DrawIsoCircle(var2.x, var2.y, this.z, 0.3F, 16, 1.0F, 1.0F, 0.0F, 1.0F);
                     }

    Vector2 var3 = L_slideAwayFromWalls.vector2.set(var2.x - this.x, var2.y - this.y);
                     var3.normalize();
                     var2.x = var2.x + var3.x * 0.3F;
                     var2.y = var2.y + var3.y * 0.3F;
                     if (var1.isKnockedDown() && (var1.isCurrentState(ZombieFallDownState.instance()) || var1.isCurrentState(StaggerBackState.instance()))) {
    Vector2f var4 = PolygonalMap2.instance.resolveCollision(var1, var2.x, var2.y, L_slideAwayFromWalls.vector2f);
                        if (var4.x != var2.x || var4.y != var2.y) {
    float var7 = GameTime.getInstance().getMultiplier() / 5.0F;
                           this.nx = this.nx + (var4.x - var2.x) * var7;
                           this.ny = this.ny + (var4.y - var2.y) * var7;
                           return;
                        }
                     }

                     if ((int)var2.x != this.current.x || (int)var2.y != this.current.y) {
    IsoGridSquare var6 = this.getCell().getGridSquare((int)var2.x, (int)var2.y, (int)this.z);
                        if (var6 != nullptr) {
                           if (this.current.testCollideAdjacent(this, var6.x - this.current.x, var6.y - this.current.y, 0)) {
    float var5 = GameTime.getInstance().getMultiplier() / 5.0F;
                              if (var6.x < this.current.x) {
                                 this.nx = this.nx + (this.current.x - var2.x) * var5;
                              } else if (var6.x > this.current.x) {
                                 this.nx = this.nx + (var6.x - var2.x) * var5;
                              }

                              if (var6.y < this.current.y) {
                                 this.ny = this.ny + (this.current.y - var2.y) * var5;
                              } else if (var6.y > this.current.y) {
                                 this.ny = this.ny + (var6.y - var2.y) * var5;
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    bool DoCollide(int var1) {
    IsoGameCharacter var2 = (IsoGameCharacter)Type.tryCastTo(this, IsoGameCharacter.class);
      this.current = this.getCell().getGridSquare((int)this.nx, (int)this.ny, (int)this.z);
      if (dynamic_cast<IsoMolotovCocktail*>(this) != nullptr) {
         for (int var3 = (int)this.z; var3 > 0; var3--) {
            for (int var4 = -1; var4 <= 1; var4++) {
               for (int var5 = -1; var5 <= 1; var5++) {
    IsoGridSquare var6 = this.getCell().createNewGridSquare((int)this.nx + var5, (int)this.ny + var4, var3, false);
                  if (var6 != nullptr) {
                     var6.RecalcAllWithNeighbours(true);
                  }
               }
            }
         }
      }

      if (this.current != nullptr) {
         if (!this.current.TreatAsSolidFloor()) {
            this.current = this.getCell().getGridSquare((int)this.nx, (int)this.ny, (int)this.z);
         }

         if (this.current == nullptr) {
    return false;
         }

         this.current = this.getCell().getGridSquare((int)this.nx, (int)this.ny, (int)this.z);
      }

      if (this.current != this.last && this.last != nullptr && this.current != nullptr) {
         if (var2 != nullptr
            && var2.getCurrentState() != nullptr
            && var2.getCurrentState().isIgnoreCollide(var2, this.last.x, this.last.y, this.last.z, this.current.x, this.current.y, this.current.z)) {
    return false;
         }

         if (this == IsoCamera.CamCharacter) {
            IsoWorld.instance.CurrentCell.lightUpdateCount = 10;
         }

    int var9 = this.current.getX() - this.last.getX();
    int var10 = this.current.getY() - this.last.getY();
    int var11 = this.current.getZ() - this.last.getZ();
    bool var12 = false;
         if (this.last.testCollideAdjacent(this, var9, var10, var11) || this.current == nullptr) {
            var12 = true;
         }

         if (var12) {
            if (this.last.getX() < this.current.getX()) {
               this.collidedE = true;
            }

            if (this.last.getX() > this.current.getX()) {
               this.collidedW = true;
            }

            if (this.last.getY() < this.current.getY()) {
               this.collidedS = true;
            }

            if (this.last.getY() > this.current.getY()) {
               this.collidedN = true;
            }

            this.current = this.last;
            this.checkBreakHoppable();
            this.checkHitHoppable();
            if (var1 == 2) {
               if ((this.collidedS || this.collidedN) && (this.collidedE || this.collidedW)) {
                  this.collidedS = false;
                  this.collidedN = false;
               }
            } else if (var1 == 1 && (this.collidedS || this.collidedN) && (this.collidedE || this.collidedW)) {
               this.collidedW = false;
               this.collidedE = false;
            }

            this.Collided();
    return true;
         }
      } else if (this.nx != this.lx || this.ny != this.ly) {
         if (dynamic_cast<IsoZombie*>(this) != nullptr && Core.GameMode == "Tutorial")) {
    return true;
         }

         if (this.current == nullptr) {
            if (this.nx < this.lx) {
               this.collidedW = true;
            }

            if (this.nx > this.lx) {
               this.collidedE = true;
            }

            if (this.ny < this.ly) {
               this.collidedN = true;
            }

            if (this.ny > this.ly) {
               this.collidedS = true;
            }

            this.nx = this.lx;
            this.ny = this.ly;
            this.current = this.last;
            this.Collided();
    return true;
         }

         if (var2 != nullptr && var2.getPath2() != nullptr) {
    PathFindBehavior2 var7 = var2.getPathFindBehavior2();
            if ((int)var7.getTargetX() == (int)this.x && (int)var7.getTargetY() == (int)this.y && (int)var7.getTargetZ() == (int)this.z) {
    return false;
            }
         }

    IsoGridSquare var8 = this.getFeelerTile(this.feelersize);
         if (var2 != nullptr) {
            if (var2.isClimbing()) {
               var8 = this.current;
            }

            if (var8 != nullptr && var8 != this.current && var2.getPath2() != nullptr && !var2.getPath2().crossesSquare(var8.x, var8.y, var8.z)) {
               var8 = this.current;
            }
         }

         if (var8 != nullptr && var8 != this.current && this.current != nullptr) {
            if (var2 != nullptr
               && var2.getCurrentState() != nullptr
               && var2.getCurrentState().isIgnoreCollide(var2, this.current.x, this.current.y, this.current.z, var8.x, var8.y, var8.z)) {
    return false;
            }

            if (this.current.testCollideAdjacent(this, var8.getX() - this.current.getX(), var8.getY() - this.current.getY(), var8.getZ() - this.current.getZ())
               )
             {
               if (this.last != nullptr) {
                  if (this.current.getX() < var8.getX()) {
                     this.collidedE = true;
                  }

                  if (this.current.getX() > var8.getX()) {
                     this.collidedW = true;
                  }

                  if (this.current.getY() < var8.getY()) {
                     this.collidedS = true;
                  }

                  if (this.current.getY() > var8.getY()) {
                     this.collidedN = true;
                  }

                  this.checkBreakHoppable();
                  this.checkHitHoppable();
                  if (var1 == 2 && (this.collidedS || this.collidedN) && (this.collidedE || this.collidedW)) {
                     this.collidedS = false;
                     this.collidedN = false;
                  }

                  if (var1 == 1 && (this.collidedS || this.collidedN) && (this.collidedE || this.collidedW)) {
                     this.collidedW = false;
                     this.collidedE = false;
                  }
               }

               this.Collided();
    return true;
            }
         }
      }

    return false;
   }

    void checkHitHoppable() {
    IsoZombie var1 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
      if (var1 != nullptr && !var1.bCrawling) {
         if (!var1.isCurrentState(AttackState.instance())
            && !var1.isCurrentState(StaggerBackState.instance())
            && !var1.isCurrentState(ClimbOverFenceState.instance())
            && !var1.isCurrentState(ClimbThroughWindowState.instance())) {
            if (this.collidedW && !this.collidedN && !this.collidedS && this.last.Is(IsoFlagType.HoppableW)) {
               var1.climbOverFence(IsoDirections.W);
            }

            if (this.collidedN && !this.collidedE && !this.collidedW && this.last.Is(IsoFlagType.HoppableN)) {
               var1.climbOverFence(IsoDirections.N);
            }

            if (this.collidedS && !this.collidedE && !this.collidedW) {
    IsoGridSquare var2 = this.last.nav[IsoDirections.S.index()];
               if (var2 != nullptr && var2.Is(IsoFlagType.HoppableN)) {
                  var1.climbOverFence(IsoDirections.S);
               }
            }

            if (this.collidedE && !this.collidedN && !this.collidedS) {
    IsoGridSquare var3 = this.last.nav[IsoDirections.E.index()];
               if (var3 != nullptr && var3.Is(IsoFlagType.HoppableW)) {
                  var1.climbOverFence(IsoDirections.E);
               }
            }
         }
      }
   }

    void checkBreakHoppable() {
    IsoZombie var1 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
      if (var1 != nullptr && var1.bCrawling) {
         if (!var1.isCurrentState(AttackState.instance())
            && !var1.isCurrentState(StaggerBackState.instance())
            && !var1.isCurrentState(CrawlingZombieTurnState.instance())) {
    IsoDirections var2 = IsoDirections.Max;
            if (this.collidedW && !this.collidedN && !this.collidedS) {
               var2 = IsoDirections.W;
            }

            if (this.collidedN && !this.collidedE && !this.collidedW) {
               var2 = IsoDirections.N;
            }

            if (this.collidedS && !this.collidedE && !this.collidedW) {
               var2 = IsoDirections.S;
            }

            if (this.collidedE && !this.collidedN && !this.collidedS) {
               var2 = IsoDirections.E;
            }

            if (var2 != IsoDirections.Max) {
    IsoObject var3 = this.last.getHoppableTo(this.last.getAdjacentSquare(var2));
    IsoThumpable var4 = (IsoThumpable)Type.tryCastTo(var3, IsoThumpable.class);
               if (var4 != nullptr && !var4.isThumpable()) {
                  var1.setThumpTarget(var4);
               } else if (var3 != nullptr && var3.getThumpableFor(var1) != nullptr) {
                  var1.setThumpTarget(var3);
               }
            }
         }
      }
   }

    void checkHitWall() {
      if (this.collidedN || this.collidedS || this.collidedE || this.collidedW) {
         if (this.current != nullptr) {
    IsoPlayer var1 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
            if (var1 != nullptr) {
               if (StringUtils.isNullOrEmpty(this.getCollideType())) {
    bool var2 = false;
    int var3 = this.current.getWallType();
                  if ((var3 & 1) != 0 && this.collidedN && this.getDir() == IsoDirections.N) {
                     var2 = true;
                  }

                  if ((var3 & 2) != 0 && this.collidedS && this.getDir() == IsoDirections.S) {
                     var2 = true;
                  }

                  if ((var3 & 4) != 0 && this.collidedW && this.getDir() == IsoDirections.W) {
                     var2 = true;
                  }

                  if ((var3 & 8) != 0 && this.collidedE && this.getDir() == IsoDirections.E) {
                     var2 = true;
                  }

                  if (this.checkVaultOver()) {
                     var2 = false;
                  }

                  if (var2 && var1.isSprinting() && var1.isLocalPlayer()) {
                     this.setCollideType("wall");
                     var1.getActionContext().reportEvent("collideWithWall");
                     this.lastCollideTime = 70.0F;
                  }
               }
            }
         }
      }
   }

    bool checkVaultOver() {
    IsoPlayer var1 = (IsoPlayer)this;
      if (var1.isCurrentState(ClimbOverFenceState.instance()) || var1.isIgnoreAutoVault()) {
    return false;
      } else if (!var1.IsRunning() && !var1.isSprinting() && var1.isLocalPlayer()) {
    return false;
      } else {
    IsoDirections var2 = this.getDir();
    IsoGridSquare var3 = this.current.getAdjacentSquare(IsoDirections.SE);
         if (var2 == IsoDirections.SE && var3 != nullptr && var3.Is(IsoFlagType.HoppableN) && var3.Is(IsoFlagType.HoppableW)) {
    return false;
         } else {
    IsoGridSquare var4 = this.current;
            if (this.collidedS) {
               var4 = this.current.getAdjacentSquare(IsoDirections.S);
            } else if (this.collidedE) {
               var4 = this.current.getAdjacentSquare(IsoDirections.E);
            }

            if (var4 == nullptr) {
    return false;
            } else {
    bool var5 = false;
               if (this.current.getProperties().Is(IsoFlagType.HoppableN)
                  && this.collidedN
                  && !this.collidedW
                  && !this.collidedE
                  && (var2 == IsoDirections.NW || var2 == IsoDirections.N || var2 == IsoDirections.NE)) {
                  var2 = IsoDirections.N;
                  var5 = true;
               }

               if (var4.getProperties().Is(IsoFlagType.HoppableN)
                  && this.collidedS
                  && !this.collidedW
                  && !this.collidedE
                  && (var2 == IsoDirections.SW || var2 == IsoDirections.S || var2 == IsoDirections.SE)) {
                  var2 = IsoDirections.S;
                  var5 = true;
               }

               if (this.current.getProperties().Is(IsoFlagType.HoppableW)
                  && this.collidedW
                  && !this.collidedN
                  && !this.collidedS
                  && (var2 == IsoDirections.NW || var2 == IsoDirections.W || var2 == IsoDirections.SW)) {
                  var2 = IsoDirections.W;
                  var5 = true;
               }

               if (var4.getProperties().Is(IsoFlagType.HoppableW)
                  && this.collidedE
                  && !this.collidedN
                  && !this.collidedS
                  && (var2 == IsoDirections.NE || var2 == IsoDirections.E || var2 == IsoDirections.SE)) {
                  var2 = IsoDirections.E;
                  var5 = true;
               }

               if (var5 && var1.isSafeToClimbOver(var2)) {
                  ClimbOverFenceState.instance().setParams(var1, var2);
                  var1.getActionContext().reportEvent("EventClimbFence");
    return true;
               } else {
    return false;
               }
            }
         }
      }
   }

    void setMovingSquareNow() {
      if (this.movingSq != nullptr) {
         this.movingSq.getMovingObjects().remove(this);
         this.movingSq = nullptr;
      }

      if (this.current != nullptr && !this.current.getMovingObjects().contains(this)) {
         this.current.getMovingObjects().push_back(this);
         this.movingSq = this.current;
      }
   }

    IsoGridSquare getFeelerTile(float var1) {
    Vector2 var2 = tempo;
      var2.x = this.nx - this.lx;
      var2.y = this.ny - this.ly;
      var2.setLength(var1);
      return this.getCell().getGridSquare((int)(this.x + var2.x), (int)(this.y + var2.y), (int)this.z);
   }

    void DoCollideNorS() {
      this.ny = this.ly;
   }

    void DoCollideWorE() {
      this.nx = this.lx;
   }

    int getTimeSinceZombieAttack() {
      return this.TimeSinceZombieAttack;
   }

    void setTimeSinceZombieAttack(int var1) {
      this.TimeSinceZombieAttack = var1;
   }

    bool isCollidedE() {
      return this.collidedE;
   }

    void setCollidedE(bool var1) {
      this.collidedE = var1;
   }

    bool isCollidedN() {
      return this.collidedN;
   }

    void setCollidedN(bool var1) {
      this.collidedN = var1;
   }

    IsoObject getCollidedObject() {
      return this.CollidedObject;
   }

    void setCollidedObject(IsoObject var1) {
      this.CollidedObject = var1;
   }

    bool isCollidedS() {
      return this.collidedS;
   }

    void setCollidedS(bool var1) {
      this.collidedS = var1;
   }

    bool isCollidedThisFrame() {
      return this.collidedThisFrame;
   }

    void setCollidedThisFrame(bool var1) {
      this.collidedThisFrame = var1;
   }

    bool isCollidedW() {
      return this.collidedW;
   }

    void setCollidedW(bool var1) {
      this.collidedW = var1;
   }

    bool isCollidedWithDoor() {
      return this.CollidedWithDoor;
   }

    void setCollidedWithDoor(bool var1) {
      this.CollidedWithDoor = var1;
   }

    bool isCollidedWithVehicle() {
      return this.collidedWithVehicle;
   }

    IsoGridSquare getCurrentSquare() {
      return this.current;
   }

    Zone getCurrentZone() {
      return this.current != nullptr ? this.current.getZone() : nullptr;
   }

    void setCurrent(IsoGridSquare var1) {
      this.current = var1;
   }

    bool isDestroyed() {
      return this.destroyed;
   }

    void setDestroyed(bool var1) {
      this.destroyed = var1;
   }

    bool isFirstUpdate() {
      return this.firstUpdate;
   }

    void setFirstUpdate(bool var1) {
      this.firstUpdate = var1;
   }

    Vector2 getHitDir() {
      return this.hitDir;
   }

    void setHitDir(Vector2 var1) {
      this.hitDir.set(var1);
   }

    float getImpulsex() {
      return this.impulsex;
   }

    void setImpulsex(float var1) {
      this.impulsex = var1;
   }

    float getImpulsey() {
      return this.impulsey;
   }

    void setImpulsey(float var1) {
      this.impulsey = var1;
   }

    float getLimpulsex() {
      return this.limpulsex;
   }

    void setLimpulsex(float var1) {
      this.limpulsex = var1;
   }

    float getLimpulsey() {
      return this.limpulsey;
   }

    void setLimpulsey(float var1) {
      this.limpulsey = var1;
   }

    float getHitForce() {
      return this.hitForce;
   }

    void setHitForce(float var1) {
      this.hitForce = var1;
   }

    float getHitFromAngle() {
      return this.hitFromAngle;
   }

    void setHitFromAngle(float var1) {
      this.hitFromAngle = var1;
   }

    IsoGridSquare getLastSquare() {
      return this.last;
   }

    void setLast(IsoGridSquare var1) {
      this.last = var1;
   }

    float getLx() {
      return this.lx;
   }

    void setLx(float var1) {
      this.lx = var1;
   }

    float getLy() {
      return this.ly;
   }

    void setLy(float var1) {
      this.ly = var1;
   }

    float getLz() {
      return this.lz;
   }

    void setLz(float var1) {
      this.lz = var1;
   }

    float getNx() {
      return this.nx;
   }

    void setNx(float var1) {
      this.nx = var1;
   }

    float getNy() {
      return this.ny;
   }

    void setNy(float var1) {
      this.ny = var1;
   }

    bool getNoDamage() {
      return this.noDamage;
   }

    void setNoDamage(bool var1) {
      this.noDamage = var1;
   }

    bool isSolid() {
      return this.solid;
   }

    void setSolid(bool var1) {
      this.solid = var1;
   }

    float getStateEventDelayTimer() {
      return this.StateEventDelayTimer;
   }

    void setStateEventDelayTimer(float var1) {
      this.StateEventDelayTimer = var1;
   }

    float getWidth() {
      return this.width;
   }

    void setWidth(float var1) {
      this.width = var1;
   }

    bool isbAltCollide() {
      return this.bAltCollide;
   }

    void setbAltCollide(bool var1) {
      this.bAltCollide = var1;
   }

    bool isShootable() {
      return this.shootable;
   }

    void setShootable(bool var1) {
      this.shootable = var1;
   }

    IsoZombie getLastTargettedBy() {
      return this.lastTargettedBy;
   }

    void setLastTargettedBy(IsoZombie var1) {
      this.lastTargettedBy = var1;
   }

    bool isCollidable() {
      return this.Collidable;
   }

    void setCollidable(bool var1) {
      this.Collidable = var1;
   }

    float getScriptnx() {
      return this.scriptnx;
   }

    void setScriptnx(float var1) {
      this.scriptnx = var1;
   }

    float getScriptny() {
      return this.scriptny;
   }

    void setScriptny(float var1) {
      this.scriptny = var1;
   }

    std::string getScriptModule() {
      return this.ScriptModule;
   }

    void setScriptModule(const std::string& var1) {
      this.ScriptModule = var1;
   }

    Vector2 getMovementLastFrame() {
      return this.movementLastFrame;
   }

    void setMovementLastFrame(Vector2 var1) {
      this.movementLastFrame = var1;
   }

    float getFeelersize() {
      return this.feelersize;
   }

    void setFeelersize(float var1) {
      this.feelersize = var1;
   }

    uint8_t canHaveMultipleHits() {
    uint8_t var1 = 0;
    std::vector var2 = IsoWorld.instance.CurrentCell.getObjectList();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoMovingObject var4 = (IsoMovingObject)var2.get(var3);
    IsoPlayer var5 = (IsoPlayer)Type.tryCastTo(var4, IsoPlayer.class);
         if (var5 != nullptr) {
    HandWeapon var6 = (HandWeapon)Type.tryCastTo(var5.getPrimaryHandItem(), HandWeapon.class);
            if (var6 == nullptr || var5.bDoShove || var5.isForceShove()) {
               var6 = var5.bareHands;
            }

    float var7 = IsoUtils.DistanceTo(var5.x, var5.y, this.x, this.y);
    float var8 = var6.getMaxRange() * var6.getRangeMod(var5) + 2.0F;
            if (!(var7 > var8)) {
    float var9 = var5.getDotWithForwardDirection(this.x, this.y);
               if (!(var7 > 2.5) || !(var9 < 0.1F)) {
                  TestResults var10 = LosUtil.lineClear(
                     var5.getCell(), (int)var5.getX(), (int)var5.getY(), (int)var5.getZ(), (int)this.getX(), (int)this.getY(), (int)this.getZ(), false
                  );
                  if (var10 != TestResults.Blocked && var10 != TestResults.ClearThroughClosedDoor) {
                     if (++var1 >= 2) {
    return var1;
                     }
                  }
               }
            }
         }
      }

    return var1;
   }

    bool isOnFloor() {
      return this.bOnFloor;
   }

    void setOnFloor(bool var1) {
      this.bOnFloor = var1;
   }

    void Despawn() {
   }

    bool isCloseKilled() {
      return this.closeKilled;
   }

    void setCloseKilled(bool var1) {
      this.closeKilled = var1;
   }

    Vector2 getFacingPosition(Vector2 var1) {
      var1.set(this.getX(), this.getY());
    return var1;
   }

    bool isInLoadedArea(int var1, int var2) {
      if (GameServer.bServer) {
         for (int var3 = 0; var3 < ServerMap.instance.LoadedCells.size(); var3++) {
    ServerCell var4 = (ServerCell)ServerMap.instance.LoadedCells.get(var3);
            if (var1 >= var4.WX * 50 && var1 < (var4.WX + 1) * 50 && var2 >= var4.WY * 50 && var2 < (var4.WY + 1) * 50) {
    return true;
            }
         }
      } else {
         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoChunkMap var6 = IsoWorld.instance.CurrentCell.ChunkMap[var5];
            if (!var6.ignore
               && var1 >= var6.getWorldXMinTiles()
               && var1 < var6.getWorldXMaxTiles()
               && var2 >= var6.getWorldYMinTiles()
               && var2 < var6.getWorldYMaxTiles()) {
    return true;
            }
         }
      }

    return false;
   }

    bool isCollided() {
      return !StringUtils.isNullOrWhitespace(this.getCollideType());
   }

    std::string getCollideType() {
      return this.collideType;
   }

    void setCollideType(const std::string& var1) {
      this.collideType = var1;
   }

    float getLastCollideTime() {
      return this.lastCollideTime;
   }

    void setLastCollideTime(float var1) {
      this.lastCollideTime = var1;
   }

   public std::vector<IsoZombie> getEatingZombies() {
      return this.eatingZombies;
   }

    void setEatingZombies(std::vector<IsoZombie> var1) {
      this.eatingZombies.clear();
      this.eatingZombies.addAll(var1);
   }

    bool isEatingOther(IsoMovingObject var1) {
    return var1 = = nullptr ? false : var1.eatingZombies.contains(this);
   }

    float getDistanceSq(IsoMovingObject var1) {
    float var2 = this.x - var1.x;
    float var3 = this.y - var1.y;
      var2 *= var2;
      var3 *= var3;
      return var2 + var3;
   }

    void setZombiesDontAttack(bool var1) {
      this.zombiesDontAttack = var1;
   }

    bool isZombiesDontAttack() {
      return this.zombiesDontAttack;
   }
}
} // namespace iso
} // namespace zombie
