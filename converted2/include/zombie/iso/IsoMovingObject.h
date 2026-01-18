#pragma once
#include "fmod/fmod/Audio.h"
#include "org/joml/Vector2f.h"
#include "zombie/CollisionManager.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MovingObjectUpdateScheduler.h"
#include "zombie/SoundManager.h"
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
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponType.h"
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
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoMovingObject : public IsoObject {
public:
public
  static IsoMovingObject.TreeSoundManager treeSoundMgr =
      new IsoMovingObject.TreeSoundManager();
  static const int MAX_ZOMBIES_EATING = 3;
  static int IDCount = 0;
  static const Vector2 tempo = new Vector2();
  bool noDamage = false;
  IsoGridSquare last = null;
  float lx;
  float ly;
  float lz;
  float nx;
  float ny;
  float x;
  float y;
  float z;
  IsoSpriteInstance def = null;
  IsoGridSquare current = null;
  Vector2 hitDir = new Vector2();
  int ID = 0;
  IsoGridSquare movingSq = null;
  bool solid = true;
  float width = 0.24F;
  bool shootable = true;
  bool Collidable = true;
  float scriptnx = 0.0F;
  float scriptny = 0.0F;
  std::string ScriptModule = "none";
  Vector2 movementLastFrame = new Vector2();
  float weight = 1.0F;
  bool bOnFloor = false;
  bool closeKilled = false;
  std::string collideType = null;
  float lastCollideTime = 0.0F;
  int TimeSinceZombieAttack = 1000000;
  bool collidedE = false;
  bool collidedN = false;
  IsoObject CollidedObject = null;
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
  Thumpable thumpTarget = null;
  bool bAltCollide = false;
  IsoZombie lastTargettedBy = null;
  float feelersize = 0.5F;
public
  final boolean[] bOutline = new boolean[4];
public
  final ColorInfo[] outlineColor = new ColorInfo[4];
private
  final ArrayList<IsoZombie> eatingZombies = std::make_unique<ArrayList<>>();
  bool zombiesDontAttack = false;

public
  IsoMovingObject(IsoCell cell) {
    this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
    if (cell != nullptr) {
      this.ID = IDCount++;
      if (this.getCell().isSafeToAdd()) {
        this.getCell().getObjectList().add(this);
      } else {
        this.getCell().getAddList().add(this);
      }
    }
  }

public
  IsoMovingObject(IsoCell cell, bool bObjectListAdd) {
    this.ID = IDCount++;
    this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
    if (bObjectListAdd) {
      if (this.getCell().isSafeToAdd()) {
        this.getCell().getObjectList().add(this);
      } else {
        this.getCell().getAddList().add(this);
      }
    }
  }

public
  IsoMovingObject(IsoCell cell, IsoGridSquare square, IsoSprite spr,
                  bool bObjectListAdd) {
    this.ID = IDCount++;
    this.sprite = spr;
    if (bObjectListAdd) {
      if (this.getCell().isSafeToAdd()) {
        this.getCell().getObjectList().add(this);
      } else {
        this.getCell().getAddList().add(this);
      }
    }
  }

public
  IsoMovingObject() {
    this.ID = IDCount++;
    this.getCell().getAddList().add(this);
  }

  /**
   * @return the IDCount
   */
  static int getIDCount() { return IDCount; }

  /**
   *
   * @param aIDCount the IDCount to set
   */
  static void setIDCount(int aIDCount) { IDCount = aIDCount; }

  IsoBuilding getBuilding() {
    if (this.current == nullptr) {
      return null;
    } else {
      IsoRoom room = this.current.getRoom();
      return room = = null ? null : room.building;
    }
  }

  IWorldRegion getMasterRegion() {
    return this.current != nullptr ? this.current.getIsoWorldRegion() : nullptr;
  }

  float getWeight() { return this.weight; }

  /**
   *
   * @param _weight the weight to set
   */
  void setWeight(float _weight) { this.weight = _weight; }

  float getWeight(float _x, float _y) { return this.weight; }

  void onMouseRightClick(int _lx, int _ly) {
    if (this.square.getZ() == (int)IsoPlayer.getInstance().getZ() &&
        this.DistToProper(IsoPlayer.getInstance()) <= 2.0F) {
      IsoPlayer.getInstance().setDragObject(this);
    }
  }

  std::string getObjectName() { return "IsoMovingObject"; }

  void onMouseRightReleased() {}

  void collideWith(IsoObject obj) {
    if (this instanceof IsoGameCharacter && obj instanceof IsoGameCharacter) {
      LuaEventManager.triggerEvent("OnCharacterCollide", this, obj);
    } else {
      LuaEventManager.triggerEvent("OnObjectCollide", this, obj);
    }
  }

  void doStairs() {
    if (this.current != nullptr) {
      if (this.last != nullptr) {
        if (!(this instanceof IsoPhysicsObject)) {
          IsoGridSquare square0 = this.current;
          if (square0.z > 0 &&
              (square0.Has(IsoObjectType.stairsTN) ||
               square0.Has(IsoObjectType.stairsTW)) &&
              this.z - (int)this.z < 0.1F) {
            IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(
                square0.x, square0.y, square0.z - 1);
            if (square1 != nullptr && (square1.Has(IsoObjectType.stairsTN) ||
                                       square1.Has(IsoObjectType.stairsTW))) {
              square0 = square1;
            }
          }

          if (this instanceof
              IsoGameCharacter && (this.last.Has(IsoObjectType.stairsTN) ||
                                   this.last.Has(IsoObjectType.stairsTW))) {
            this.z = Math.round(this.z);
          }

          float float0 = this.z;
          if (square0.HasStairs()) {
            float0 = square0.getApparentZ(this.x - square0.getX(),
                                          this.y - square0.getY());
          }

          if (this instanceof IsoGameCharacter) {
            State state = ((IsoGameCharacter)this).getCurrentState();
            if (state == ClimbOverFenceState.instance() ||
                state == ClimbThroughWindowState.instance()) {
              if (square0.HasStairs() && this.z > float0) {
                this.z = Math.max(
                    float0,
                    this.z - 0.075F * GameTime.getInstance().getMultiplier());
              }

              return;
            }
          }

          if (Math.abs(float0 - this.z) < 0.95F) {
            this.z = float0;
          }
        }
      }
    }
  }

  int getID() { return this.ID; }

  /**
   *
   * @param _ID the ID to set
   */
  void setID(int _ID) { this.ID = _ID; }

  int getPathFindIndex() { return this.PathFindIndex; }

  /**
   *
   * @param _PathFindIndex the PathFindIndex to set
   */
  void setPathFindIndex(int _PathFindIndex) {
    this.PathFindIndex = _PathFindIndex;
  }

  float getScreenX() { return IsoUtils.XToScreen(this.x, this.y, this.z, 0); }

  float getScreenY() { return IsoUtils.YToScreen(this.x, this.y, this.z, 0); }

  Thumpable getThumpTarget() { return this.thumpTarget; }

  /**
   *
   * @param _thumpTarget the thumpTarget to set
   */
  void setThumpTarget(Thumpable _thumpTarget) {
    this.thumpTarget = _thumpTarget;
  }

  Vector2 getVectorFromDirection(Vector2 moveForwardVec) {
    return getVectorFromDirection();
  }

  static Vector2 getVectorFromDirection(Vector2 moveForwardVec,
                                        IsoDirections dir) {
    if (moveForwardVec == nullptr) {
      DebugLog.General.warn("Supplied vector2 is nullptr. Cannot be processed. "
                            "Using fail-safe fallback.");
      moveForwardVec = std::make_unique<Vector2>();
    }

    moveForwardVec.x = 0.0F;
    moveForwardVec.y = 0.0F;
    switch (dir) {
    case S:
      moveForwardVec.x = 0.0F;
      moveForwardVec.y = 1.0F;
      break;
    case N:
      moveForwardVec.x = 0.0F;
      moveForwardVec.y = -1.0F;
      break;
    case E:
      moveForwardVec.x = 1.0F;
      moveForwardVec.y = 0.0F;
      break;
    case W:
      moveForwardVec.x = -1.0F;
      moveForwardVec.y = 0.0F;
      break;
    case NW:
      moveForwardVec.x = -1.0F;
      moveForwardVec.y = -1.0F;
      break;
    case NE:
      moveForwardVec.x = 1.0F;
      moveForwardVec.y = -1.0F;
      break;
    case SW:
      moveForwardVec.x = -1.0F;
      moveForwardVec.y = 1.0F;
      break;
    case SE:
      moveForwardVec.x = 1.0F;
      moveForwardVec.y = 1.0F;
    }

    moveForwardVec.normalize();
    return moveForwardVec;
  }

  /**
   * Get the object's position. Stored in the supplied parameter.
   * @return The out parameter.
   */
  Vector3 getPosition(Vector3 out) {
    out.set(this.getX(), this.getY(), this.getZ());
    return out;
  }

  float getX() { return this.x; }

  /**
   *
   * @param _x the x to set
   */
  void setX(float _x) {
    this.x = _x;
    this.nx = _x;
    this.scriptnx = _x;
  }

  float getY() { return this.y; }

  /**
   *
   * @param _y the y to set
   */
  void setY(float _y) {
    this.y = _y;
    this.ny = _y;
    this.scriptny = _y;
  }

  float getZ() { return this.z; }

  /**
   *
   * @param _z the z to set
   */
  void setZ(float _z) {
    this.z = _z;
    this.lz = _z;
  }

  IsoGridSquare getSquare() {
    return this.current != nullptr ? this.current : this.square;
  }

  IsoBuilding getCurrentBuilding() {
    if (this.current == nullptr) {
      return null;
    } else {
      return this.current.getRoom() == nullptr
                 ? nullptr
                 : this.current.getRoom().building;
    }
  }

  float Hit(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit,
            bool bIgnoreDamage, float modDelta) {
    return 0.0F;
  }

  void Move(Vector2 dir) {
    this.nx = this.nx + dir.x * GameTime.instance.getMultiplier();
    this.ny = this.ny + dir.y * GameTime.instance.getMultiplier();
    if (this instanceof IsoPlayer) {
      this.current = IsoWorld.instance.CurrentCell.getGridSquare(
          (double)this.x, (double)this.y, (double)((int)this.z));
    }
  }

  void MoveUnmodded(Vector2 dir) {
    this.nx = this.nx + dir.x;
    this.ny = this.ny + dir.y;
    if (this instanceof IsoPlayer) {
      this.current = IsoWorld.instance.CurrentCell.getGridSquare(
          (double)this.x, (double)this.y, (double)((int)this.z));
    }
  }

  bool isCharacter() { return this instanceof IsoGameCharacter; }

  float DistTo(int _x, int _y) {
    return IsoUtils.DistanceManhatten(_x, _y, this.x, this.y);
  }

  float DistTo(IsoMovingObject other) {
    return IsoUtils.DistanceManhatten(this.x, this.y, other.x, other.y);
  }

  float DistToProper(IsoObject other) {
    return IsoUtils.DistanceTo(this.x, this.y, other.getX(), other.getY());
  }

  float DistToSquared(IsoMovingObject other) {
    return IsoUtils.DistanceToSquared(this.x, this.y, other.x, other.y);
  }

  float DistToSquared(float _x, float _y) {
    return IsoUtils.DistanceToSquared(_x, _y, this.x, this.y);
  }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    float float0 = input.getFloat();
    float float1 = input.getFloat();
    this.x = this.lx = this.nx = this.scriptnx =
        input.getFloat() + IsoWorld.saveoffsetx * 300;
    this.y = this.ly = this.ny = this.scriptny =
        input.getFloat() + IsoWorld.saveoffsety * 300;
    this.z = this.lz = input.getFloat();
    this.dir = IsoDirections.fromIndex(input.getInt());
    if (input.get() != 0) {
      if (this.table == nullptr) {
        this.table = LuaManager.platform.newTable();
      }

      this.table.load(input, WorldVersion);
    }
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    output.put((byte)(this.Serialize() ? 1 : 0));
    output.put(IsoObject.factoryGetClassID(this.getObjectName()));
    output.putFloat(this.offsetX);
    output.putFloat(this.offsetY);
    output.putFloat(this.x);
    output.putFloat(this.y);
    output.putFloat(this.z);
    output.putInt(this.dir.index());
    if (this.table != nullptr && !this.table.isEmpty()) {
      output.put((byte)1);
      this.table.save(output);
    } else {
      output.put((byte)0);
    }
  }

  void removeFromWorld() {
    IsoCell cell = this.getCell();
    if (cell.isSafeToAdd()) {
      cell.getObjectList().remove(this);
      cell.getRemoveList().remove(this);
    } else {
      cell.getRemoveList().add(this);
    }

    cell.getAddList().remove(this);
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
      IsoGridSquare square = this.getFeelerTile(this.feelersize);
      if (square != nullptr && square != this.current) {
        return square;
      }
    }

    return null;
  }

  float getGlobalMovementMod() { return this.getGlobalMovementMod(true); }

  float getGlobalMovementMod(bool bDoNoises) {
    if (this.current != nullptr && this.z - (int)this.z < 0.5F) {
      if (this.current.Has(IsoObjectType.tree) ||
          this.current.getProperties() != nullptr &&
              this.current.getProperties().Is("Bush")) {
        if (bDoNoises) {
          this.doTreeNoises();
        }

        for (int int0 = 1; int0 < this.current.getObjects().size(); int0++) {
          IsoObject object0 = this.current.getObjects().get(int0);
          if (object0 instanceof IsoTree) {
            object0.setRenderEffect(RenderEffectType.Vegetation_Rustle);
          } else if (object0.getProperties() != nullptr &&
                     object0.getProperties().Is("Bush")) {
            object0.setRenderEffect(RenderEffectType.Vegetation_Rustle);
          }
        }
      }

      IsoGridSquare square = this.getFeelerTile(this.feelersize);
      if (square != nullptr && square != this.current &&
          (square.Has(IsoObjectType.tree) ||
           square.getProperties() != nullptr &&
               square.getProperties().Is("Bush"))) {
        if (bDoNoises) {
          this.doTreeNoises();
        }

        for (int int1 = 1; int1 < square.getObjects().size(); int1++) {
          IsoObject object1 = square.getObjects().get(int1);
          if (object1 instanceof IsoTree) {
            object1.setRenderEffect(RenderEffectType.Vegetation_Rustle);
          } else if (object1.getSprite() != nullptr &&
                     object1.getProperties().Is("Bush")) {
            object1.setRenderEffect(RenderEffectType.Vegetation_Rustle);
          }
        }
      }
    }

    return this.current != nullptr && this.current.HasStairs() ? 0.75F : 1.0F;
  }

  void doTreeNoises() {
    if (!GameServer.bServer) {
      if (!(this instanceof IsoPhysicsObject)) {
        if (this.current != nullptr) {
          if (Rand.Next(Rand.AdjustForFramerate(50)) == 0) {
            treeSoundMgr.addSquare(this.current);
          }
        }
      }
    }
  }

  void postupdate() {
    IsoGameCharacter character = Type.tryCastTo(this, IsoGameCharacter.class);
    IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
    IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
    this.slideAwayFromWalls();
    if (zombie0 != nullptr && GameServer.bServer &&
        !zombie0.isCurrentState(ZombieIdleState.instance())) {
      bool boolean0 = false;
    }

    if (player != nullptr && player.isLocalPlayer()) {
      IsoPlayer.setInstance(player);
      IsoCamera.CamCharacter = player;
    }

    this.ensureOnTile();
    if (this.lastTargettedBy != nullptr && this.lastTargettedBy.isDead()) {
      this.lastTargettedBy = nullptr;
    }

    if (this.lastTargettedBy != nullptr && this.TimeSinceZombieAttack > 120) {
      this.lastTargettedBy = nullptr;
    }

    this.TimeSinceZombieAttack++;
    if (player != nullptr) {
      player.setLastCollidedW(this.collidedW);
      player.setLastCollidedN(this.collidedN);
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
      if (zombie0 == nullptr || (int)this.z != 0 ||
          this.getCurrentBuilding() != nullptr ||
          this.isInLoadedArea((int)this.nx, (int)this.ny) ||
          !zombie0.isCurrentState(PathFindState.instance()) &&
              !zombie0.isCurrentState(WalkTowardState.instance())) {
        float float0 = this.nx;
        float float1 = this.ny;
        this.collidedWithVehicle = false;
        if (character != nullptr && !this.isOnFloor() &&
            character.getVehicle() == nullptr && this.isCollidable() &&
            (player == nullptr || !player.isNoClip())) {
          int int0 = (int)this.x;
          int int1 = (int)this.y;
          int int2 = (int)this.nx;
          int int3 = (int)this.ny;
          int int4 = (int)this.z;
          if (character.getCurrentState() == nullptr ||
              !character.getCurrentState().isIgnoreCollide(
                  character, int0, int1, int4, int2, int3, int4)) {
            Vector2f vector2f = PolygonalMap2.instance.resolveCollision(
                character, this.nx, this.ny,
                IsoMovingObject.L_postUpdate.vector2f);
            if (vector2f.x != this.nx || vector2f.y != this.ny) {
              this.nx = vector2f.x;
              this.ny = vector2f.y;
              this.collidedWithVehicle = true;
            }
          }
        }

        float float2 = this.nx;
        float float3 = this.ny;
        float float4 = 0.0F;
        bool boolean1 = false;
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
            boolean1 = true;
          }

          if (this.collidedW || this.collidedE) {
            this.nx = this.lx;
            this.DoCollideWorE();
            boolean1 = true;
          }

          float4 = Math.abs(this.nx - this.lx) + Math.abs(this.ny - this.ly);
          float float5 = this.nx;
          float float6 = this.ny;
          this.nx = float2;
          this.ny = float3;
          if (this.Collidable && boolean1) {
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
              boolean1 = true;
            }

            if (this.collidedW || this.collidedE) {
              this.nx = this.lx;
              this.DoCollideWorE();
              boolean1 = true;
            }

            if (Math.abs(this.nx - this.lx) + Math.abs(this.ny - this.ly) <
                float4) {
              this.nx = float5;
              this.ny = float6;
            }
          }
        }

        if (this.collidedThisFrame) {
          this.current = this.last;
        }

        this.checkHitWall();
        if (player != nullptr &&
            !player.isCurrentState(CollideWithWallState.instance()) &&
            !this.collidedN && !this.collidedS && !this.collidedW &&
            !this.collidedE) {
          this.setCollideType(nullptr);
        }

        float float7 = this.nx - this.x;
        float float8 = this.ny - this.y;
        float float9 = !(Math.abs(float7) > 0.0F) && !(Math.abs(float8) > 0.0F)
                           ? 0.0F
                           : this.getGlobalMovementMod();
        if (Math.abs(float7) > 0.01F || Math.abs(float8) > 0.01F) {
          float7 *= float9;
          float8 *= float9;
        }

        this.x += float7;
        this.y += float8;
        this.doStairs();
        this.current =
            this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
        if (this.current == nullptr) {
          for (int int5 = (int)this.z; int5 >= 0; int5--) {
            this.current =
                this.getCell().getGridSquare((int)this.x, (int)this.y, int5);
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

        if (this.current != nullptr &&
            !this.current.getMovingObjects().contains(this)) {
          this.current.getMovingObjects().add(this);
          this.movingSq = this.current;
        }

        this.ensureOnTile();
        this.square = this.current;
        this.scriptnx = this.nx;
        this.scriptny = this.ny;
        this.firstUpdate = false;
      } else {
        ZombiePopulationManager.instance.virtualizeZombie(zombie0);
      }
    }
  }

  void ensureOnTile() {
    if (this.current == nullptr) {
      if (!(this instanceof IsoPlayer)) {
        if (this instanceof IsoSurvivor) {
          IsoWorld.instance.CurrentCell.Remove(this);
          IsoWorld.instance.CurrentCell.getSurvivorList().remove(this);
        }

        return;
      }

      bool boolean0 = true;
      bool boolean1 = false;
      if (this.last != nullptr && (this.last.Has(IsoObjectType.stairsTN) ||
                                   this.last.Has(IsoObjectType.stairsTW))) {
        this.current = this.getCell().getGridSquare((int)this.x, (int)this.y,
                                                    (int)this.z + 1);
        boolean0 = false;
      }

      if (this.current == nullptr) {
        this.current =
            this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
        return;
      }

      if (boolean0) {
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

  void renderlast() { this.bOutline[IsoCamera.frameState.playerIndex] = false; }

  void spotted(IsoMovingObject other, bool bForced) {}

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

    this.StateEventDelayTimer =
        this.StateEventDelayTimer - GameTime.instance.getMultiplier();
  }

  void Collided() { this.collidedThisFrame = true; }

  int compareToY(IsoMovingObject other) {
    if (this.sprite == nullptr && other.sprite == nullptr) {
      return 0;
    } else if (this.sprite != nullptr && other.sprite == nullptr) {
      return -1;
    } else if (this.sprite == nullptr) {
      return 1;
    } else {
      float float0 = IsoUtils.YToScreen(this.x, this.y, this.z, 0);
      float float1 = IsoUtils.YToScreen(other.x, other.y, other.z, 0);
      if (float0 > float1) {
        return 1;
      } else {
        return float0 < float1 ? -1 : 0;
      }
    }
  }

  float distToNearestCamCharacter() {
    float float0 = Float.MAX_VALUE;

    for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
      IsoPlayer player = IsoPlayer.players[int0];
      if (player != nullptr) {
        float0 = Math.min(float0, this.DistTo(player));
      }
    }

    return float0;
  }

  bool isSolidForSeparate() {
    if (this instanceof IsoZombieGiblets) {
      return false;
    } else if (this.current == nullptr) {
      return false;
    } else {
      return !this.solid ? false : !this.isOnFloor();
    }
  }

  bool isPushableForSeparate() { return true; }

  bool isPushedByForSeparate(IsoMovingObject other) { return true; }

  /**
   * Collision detection
   */
  void separate() {
    if (this.isSolidForSeparate()) {
      if (this.isPushableForSeparate()) {
        IsoGameCharacter character0 =
            Type.tryCastTo(this, IsoGameCharacter.class);
        IsoPlayer player0 = Type.tryCastTo(this, IsoPlayer.class);
        if (this.z < 0.0F) {
          this.z = 0.0F;
        }

        for (int int0 = 0; int0 <= 8; int0++) {
          IsoGridSquare square =
              int0 == 8 ? this.current : this.current.nav[int0];
          if (square != nullptr && !square.getMovingObjects().isEmpty() &&
              (square == this.current || !this.current.isBlockedTo(square))) {
            float float0 = player0 != nullptr && player0.getPrimaryHandItem()
                instanceof
                HandWeapon
                    ? ((HandWeapon)player0.getPrimaryHandItem()).getMaxRange()
                    : 0.3F;
            int int1 = 0;

            for (int int2 = square.getMovingObjects().size(); int1 < int2;
                 int1++) {
              IsoMovingObject movingObject1 =
                  square.getMovingObjects().get(int1);
              if (movingObject1 != this && movingObject1.isSolidForSeparate() &&
                  !(Math.abs(this.z - movingObject1.z) > 0.3F)) {
                IsoGameCharacter character1 =
                    Type.tryCastTo(movingObject1, IsoGameCharacter.class);
                IsoPlayer player1 =
                    Type.tryCastTo(movingObject1, IsoPlayer.class);
                float float1 = this.width + movingObject1.width;
                Vector2 vector = tempo;
                vector.x = this.nx - movingObject1.nx;
                vector.y = this.ny - movingObject1.ny;
                float float2 = vector.getLength();
                if (character0 == nullptr ||
                    character1 == nullptr &&
                        !(movingObject1 instanceof BaseVehicle)) {
                  if (float2 < float1) {
                    CollisionManager.instance.AddContact(this, movingObject1);
                  }

                  return;
                }

                if (character1 != nullptr) {
                  if (player0 != nullptr &&
                      player0.getBumpedChr() != movingObject1 &&
                      float2 < float1 + float0 &&
                      player0.getForwardDirection().angleBetween(vector) >
                          2.6179938155736564 &&
                      player0.getBeenSprintingFor() >= 70.0F &&
                      WeaponType.getWeaponType(player0) == WeaponType.spear) {
                    player0.reportEvent("ChargeSpearConnect");
                    player0.setAttackType("charge");
                    player0.attackStarted = true;
                    player0.setVariable("StartedAttackWhileSprinting", true);
                    player0.setBeenSprintingFor(0.0F);
                    return;
                  }

                  if (!(float2 >= float1)) {
                    bool boolean0 = false;
                    if (player0 != nullptr &&
                        player0.getVariableFloat("WalkSpeed", 0.0F) > 0.2F &&
                        player0.runningTime > 0.5F &&
                        player0.getBumpedChr() != movingObject1) {
                      boolean0 = true;
                    }

                    if (GameClient.bClient && player0 != nullptr &&
                            character1 instanceof
                        IsoPlayer && !ServerOptions.getInstance()
                                          .PlayerBumpPlayer.getValue()) {
                      boolean0 = false;
                    }

                    if (boolean0 && !"charge" == player0.getAttackType())) {
                        boolean boolean1 =
                            !this.isOnFloor() &&
                            (character0.getBumpedChr() != nullptr ||
                             (System.currentTimeMillis() -
                              player0.getLastBump()) /
                                     100L <
                                 15L ||
                             player0.isSprinting()) &&
                            (player1 == nullptr || !player1.isNPC());
                        if (boolean1) {
                          character0.bumpNbr++;
                          int int3 = 10 - character0.bumpNbr * 3;
                          int3 += character0.getPerkLevel(
                              PerkFactory.Perks.Fitness);
                          int3 += character0.getPerkLevel(
                              PerkFactory.Perks.Strength);
                          if (character0.Traits.Clumsy.isSet()) {
                            int3 -= 5;
                          }

                          if (character0.Traits.Graceful.isSet()) {
                            int3 += 5;
                          }

                          if (character0.Traits.VeryUnderweight.isSet()) {
                            int3 -= 8;
                          }

                          if (character0.Traits.Underweight.isSet()) {
                            int3 -= 4;
                          }

                          if (character0.Traits.Obese.isSet()) {
                            int3 -= 8;
                          }

                          if (character0.Traits.Overweight.isSet()) {
                            int3 -= 4;
                          }

                          BodyPart bodyPart =
                              character0.getBodyDamage().getBodyPart(
                                  BodyPartType.Torso_Lower);
                          if (bodyPart.getAdditionalPain(true) > 20.0F) {
                            int3 =
                                (int)(int3 - (bodyPart.getAdditionalPain(true) -
                                              20.0F) /
                                                 20.0F);
                          }

                          int3 = Math.min(80, int3);
                          int3 = Math.max(1, int3);
                          if (Rand.Next(int3) == 0 ||
                              character0.isSprinting()) {
                            character0.setVariable("BumpDone", false);
                            character0.setBumpFall(true);
                            character0.setVariable("TripObstacleType",
                                                   "zombie");
                          }
                        } else {
                          character0.bumpNbr = 0;
                        }

                        character0.setLastBump(System.currentTimeMillis());
                        character0.setBumpedChr(character1);
                        character0.setBumpType(this.getBumpedType(character1));
                        bool boolean2 = character0.isBehind(character1);
                        std::string string = character0.getBumpType();
                        if (boolean2) {
                          if (string == "left")) {
                                                    string = "right";
                                                }
                          else {
                            string = "left";
                          }
                        }

                        character1.setBumpType(string);
                        character1.setHitFromBehind(boolean2);
                        if (boolean1 | GameClient.bClient) {
                          character0.actionContext.reportEvent("wasBumped");
                        }
                      }

                    if (GameServer.bServer ||
                        this.distToNearestCamCharacter() < 60.0F) {
                      if (this.isPushedByForSeparate(movingObject1)) {
                        vector.setLength((float2 - float1) / 8.0F);
                        this.nx = this.nx - vector.x;
                        this.ny = this.ny - vector.y;
                      }

                      this.collideWith(movingObject1);
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

  std::string getBumpedType(IsoGameCharacter bumped) {
    float float0 = this.x - bumped.x;
    float float1 = this.y - bumped.y;
    std::string string = "left";
    if (this.dir == IsoDirections.S || this.dir == IsoDirections.SE ||
        this.dir == IsoDirections.SW) {
      if (float0 < 0.0F) {
        string = "left";
      } else {
        string = "right";
      }
    }

    if (this.dir == IsoDirections.N || this.dir == IsoDirections.NE ||
        this.dir == IsoDirections.NW) {
      if (float0 > 0.0F) {
        string = "left";
      } else {
        string = "right";
      }
    }

    if (this.dir == IsoDirections.E) {
      if (float1 > 0.0F) {
        string = "left";
      } else {
        string = "right";
      }
    }

    if (this.dir == IsoDirections.W) {
      if (float1 < 0.0F) {
        string = "left";
      } else {
        string = "right";
      }
    }

    return string;
  }

  void slideAwayFromWalls() {
    if (this.current != nullptr) {
      IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
      if (zombie0 != nullptr && (this.isOnFloor() || zombie0.isKnockedDown())) {
        if (!zombie0.isCrawling() ||
            zombie0.getPath2() == nullptr && !zombie0.isMoving()) {
          if (!zombie0.isCurrentState(ClimbOverFenceState.instance()) &&
              !zombie0.isCurrentState(ClimbThroughWindowState.instance())) {
            if (zombie0.hasAnimationPlayer() &&
                zombie0.getAnimationPlayer().isReady()) {
              Vector3 vector0 = IsoMovingObject.L_slideAwayFromWalls.vector3;
              Model.BoneToWorldCoords(
                  zombie0,
                  zombie0.getAnimationPlayer().getSkinningBoneIndex(
                      "Bip01_Head", -1),
                  vector0);
              if (Core.bDebug &&
                  DebugOptions.instance.CollideWithObstaclesRenderRadius
                      .getValue()) {
                LineDrawer.DrawIsoCircle(vector0.x, vector0.y, this.z, 0.3F, 16,
                                         1.0F, 1.0F, 0.0F, 1.0F);
              }

              Vector2 vector1 =
                  IsoMovingObject.L_slideAwayFromWalls.vector2.set(
                      vector0.x - this.x, vector0.y - this.y);
              vector1.normalize();
              vector0.x = vector0.x + vector1.x * 0.3F;
              vector0.y = vector0.y + vector1.y * 0.3F;
              if (zombie0.isKnockedDown() &&
                  (zombie0.isCurrentState(ZombieFallDownState.instance()) ||
                   zombie0.isCurrentState(StaggerBackState.instance()))) {
                Vector2f vector2f = PolygonalMap2.instance.resolveCollision(
                    zombie0, vector0.x, vector0.y,
                    IsoMovingObject.L_slideAwayFromWalls.vector2f);
                if (vector2f.x != vector0.x || vector2f.y != vector0.y) {
                  float float0 = GameTime.getInstance().getMultiplier() / 5.0F;
                  this.nx = this.nx + (vector2f.x - vector0.x) * float0;
                  this.ny = this.ny + (vector2f.y - vector0.y) * float0;
                  return;
                }
              }

              if ((int)vector0.x != this.current.x ||
                  (int)vector0.y != this.current.y) {
                IsoGridSquare square = this.getCell().getGridSquare(
                    (int)vector0.x, (int)vector0.y, (int)this.z);
                if (square != nullptr) {
                  if (this.current.testCollideAdjacent(
                          this, square.x - this.current.x,
                          square.y - this.current.y, 0)) {
                    float float1 =
                        GameTime.getInstance().getMultiplier() / 5.0F;
                    if (square.x < this.current.x) {
                      this.nx = this.nx + (this.current.x - vector0.x) * float1;
                    } else if (square.x > this.current.x) {
                      this.nx = this.nx + (square.x - vector0.x) * float1;
                    }

                    if (square.y < this.current.y) {
                      this.ny = this.ny + (this.current.y - vector0.y) * float1;
                    } else if (square.y > this.current.y) {
                      this.ny = this.ny + (square.y - vector0.y) * float1;
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

  bool DoCollide(int int6) {
    IsoGameCharacter character = Type.tryCastTo(this, IsoGameCharacter.class);
    this.current =
        this.getCell().getGridSquare((int)this.nx, (int)this.ny, (int)this.z);
    if (this instanceof IsoMolotovCocktail) {
      for (int int0 = (int)this.z; int0 > 0; int0--) {
        for (int int1 = -1; int1 <= 1; int1++) {
          for (int int2 = -1; int2 <= 1; int2++) {
            IsoGridSquare square0 = this.getCell().createNewGridSquare(
                (int)this.nx + int2, (int)this.ny + int1, int0, false);
            if (square0 != nullptr) {
              square0.RecalcAllWithNeighbours(true);
            }
          }
        }
      }
    }

    if (this.current != nullptr) {
      if (!this.current.TreatAsSolidFloor()) {
        this.current = this.getCell().getGridSquare((int)this.nx, (int)this.ny,
                                                    (int)this.z);
      }

      if (this.current == nullptr) {
        return false;
      }

      this.current =
          this.getCell().getGridSquare((int)this.nx, (int)this.ny, (int)this.z);
    }

    if (this.current != this.last && this.last != nullptr &&
        this.current != nullptr) {
      if (character != nullptr && character.getCurrentState() != nullptr &&
          character.getCurrentState().isIgnoreCollide(
              character, this.last.x, this.last.y, this.last.z, this.current.x,
              this.current.y, this.current.z)) {
        return false;
      }

      if (this == IsoCamera.CamCharacter) {
        IsoWorld.instance.CurrentCell.lightUpdateCount = 10;
      }

      int int3 = this.current.getX() - this.last.getX();
      int int4 = this.current.getY() - this.last.getY();
      int int5 = this.current.getZ() - this.last.getZ();
      bool boolean0 = false;
      if (this.last.testCollideAdjacent(this, int3, int4, int5) ||
          this.current == nullptr) {
        boolean0 = true;
      }

      if (boolean0) {
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
        if (int6 == 2) {
          if ((this.collidedS || this.collidedN) &&
              (this.collidedE || this.collidedW)) {
            this.collidedS = false;
            this.collidedN = false;
          }
        } else if (int6 == 1 && (this.collidedS || this.collidedN) &&
                   (this.collidedE || this.collidedW)) {
          this.collidedW = false;
          this.collidedE = false;
        }

        this.Collided();
        return true;
      }
    } else if (this.nx != this.lx || this.ny != this.ly) {
      if (this instanceof IsoZombie && Core.GameMode == "Tutorial")) {
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

      if (character != nullptr && character.getPath2() != nullptr) {
        PathFindBehavior2 pathFindBehavior2 = character.getPathFindBehavior2();
        if ((int)pathFindBehavior2.getTargetX() == (int)this.x &&
            (int)pathFindBehavior2.getTargetY() == (int)this.y &&
            (int)pathFindBehavior2.getTargetZ() == (int)this.z) {
          return false;
        }
      }

      IsoGridSquare square1 = this.getFeelerTile(this.feelersize);
      if (character != nullptr) {
        if (character.isClimbing()) {
          square1 = this.current;
        }

        if (square1 != nullptr && square1 != this.current &&
            character.getPath2() != nullptr &&
            !character.getPath2().crossesSquare(square1.x, square1.y,
                                                square1.z)) {
          square1 = this.current;
        }
      }

      if (square1 != nullptr && square1 != this.current &&
          this.current != nullptr) {
        if (character != nullptr && character.getCurrentState() != nullptr &&
            character.getCurrentState().isIgnoreCollide(
                character, this.current.x, this.current.y, this.current.z,
                square1.x, square1.y, square1.z)) {
          return false;
        }

        if (this.current.testCollideAdjacent(
                this, square1.getX() - this.current.getX(),
                square1.getY() - this.current.getY(),
                square1.getZ() - this.current.getZ())) {
          if (this.last != nullptr) {
            if (this.current.getX() < square1.getX()) {
              this.collidedE = true;
            }

            if (this.current.getX() > square1.getX()) {
              this.collidedW = true;
            }

            if (this.current.getY() < square1.getY()) {
              this.collidedS = true;
            }

            if (this.current.getY() > square1.getY()) {
              this.collidedN = true;
            }

            this.checkBreakHoppable();
            this.checkHitHoppable();
            if (int6 == 2 && (this.collidedS || this.collidedN) &&
                (this.collidedE || this.collidedW)) {
              this.collidedS = false;
              this.collidedN = false;
            }

            if (int6 == 1 && (this.collidedS || this.collidedN) &&
                (this.collidedE || this.collidedW)) {
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
    IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
    if (zombie0 != nullptr && !zombie0.bCrawling) {
      if (!zombie0.isCurrentState(AttackState.instance()) &&
          !zombie0.isCurrentState(StaggerBackState.instance()) &&
          !zombie0.isCurrentState(ClimbOverFenceState.instance()) &&
          !zombie0.isCurrentState(ClimbThroughWindowState.instance())) {
        if (this.collidedW && !this.collidedN && !this.collidedS &&
            this.last.Is(IsoFlagType.HoppableW)) {
          zombie0.climbOverFence(IsoDirections.W);
        }

        if (this.collidedN && !this.collidedE && !this.collidedW &&
            this.last.Is(IsoFlagType.HoppableN)) {
          zombie0.climbOverFence(IsoDirections.N);
        }

        if (this.collidedS && !this.collidedE && !this.collidedW) {
          IsoGridSquare square0 = this.last.nav[IsoDirections.S.index()];
          if (square0 != nullptr && square0.Is(IsoFlagType.HoppableN)) {
            zombie0.climbOverFence(IsoDirections.S);
          }
        }

        if (this.collidedE && !this.collidedN && !this.collidedS) {
          IsoGridSquare square1 = this.last.nav[IsoDirections.E.index()];
          if (square1 != nullptr && square1.Is(IsoFlagType.HoppableW)) {
            zombie0.climbOverFence(IsoDirections.E);
          }
        }
      }
    }
  }

  void checkBreakHoppable() {
    IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
    if (zombie0 != nullptr && zombie0.bCrawling) {
      if (!zombie0.isCurrentState(AttackState.instance()) &&
          !zombie0.isCurrentState(StaggerBackState.instance()) &&
          !zombie0.isCurrentState(CrawlingZombieTurnState.instance())) {
        IsoDirections directions = IsoDirections.Max;
        if (this.collidedW && !this.collidedN && !this.collidedS) {
          directions = IsoDirections.W;
        }

        if (this.collidedN && !this.collidedE && !this.collidedW) {
          directions = IsoDirections.N;
        }

        if (this.collidedS && !this.collidedE && !this.collidedW) {
          directions = IsoDirections.S;
        }

        if (this.collidedE && !this.collidedN && !this.collidedS) {
          directions = IsoDirections.E;
        }

        if (directions != IsoDirections.Max) {
          IsoObject object =
              this.last.getHoppableTo(this.last.getAdjacentSquare(directions));
          IsoThumpable thumpable = Type.tryCastTo(object, IsoThumpable.class);
          if (thumpable != nullptr && !thumpable.isThumpable()) {
            zombie0.setThumpTarget(thumpable);
          } else if (object != nullptr &&
                     object.getThumpableFor(zombie0) != nullptr) {
            zombie0.setThumpTarget(object);
          }
        }
      }
    }
  }

  void checkHitWall() {
    if (this.collidedN || this.collidedS || this.collidedE || this.collidedW) {
      if (this.current != nullptr) {
        IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
        if (player != nullptr) {
          if (StringUtils.isNullOrEmpty(this.getCollideType())) {
            bool boolean0 = false;
            int int0 = this.current.getWallType();
            if ((int0 & 1) != 0 && this.collidedN &&
                this.getDir() == IsoDirections.N) {
              boolean0 = true;
            }

            if ((int0 & 2) != 0 && this.collidedS &&
                this.getDir() == IsoDirections.S) {
              boolean0 = true;
            }

            if ((int0 & 4) != 0 && this.collidedW &&
                this.getDir() == IsoDirections.W) {
              boolean0 = true;
            }

            if ((int0 & 8) != 0 && this.collidedE &&
                this.getDir() == IsoDirections.E) {
              boolean0 = true;
            }

            if (this.checkVaultOver()) {
              boolean0 = false;
            }

            if (boolean0 && player.isSprinting() && player.isLocalPlayer()) {
              this.setCollideType("wall");
              player.getActionContext().reportEvent("collideWithWall");
              this.lastCollideTime = 70.0F;
            }
          }
        }
      }
    }
  }

  bool checkVaultOver() {
    IsoPlayer player = (IsoPlayer)this;
    if (player.isCurrentState(ClimbOverFenceState.instance()) ||
        player.isIgnoreAutoVault()) {
      return false;
    } else if (!player.IsRunning() && !player.isSprinting() &&
               player.isLocalPlayer()) {
      return false;
    } else {
      IsoDirections directions = this.getDir();
      IsoGridSquare square0 = this.current.getAdjacentSquare(IsoDirections.SE);
      if (directions == IsoDirections.SE && square0 != nullptr &&
          square0.Is(IsoFlagType.HoppableN) &&
          square0.Is(IsoFlagType.HoppableW)) {
        return false;
      } else {
        IsoGridSquare square1 = this.current;
        if (this.collidedS) {
          square1 = this.current.getAdjacentSquare(IsoDirections.S);
        } else if (this.collidedE) {
          square1 = this.current.getAdjacentSquare(IsoDirections.E);
        }

        if (square1 == nullptr) {
          return false;
        } else {
          bool boolean0 = false;
          if (this.current.getProperties().Is(IsoFlagType.HoppableN) &&
              this.collidedN && !this.collidedW && !this.collidedE &&
              (directions == IsoDirections.NW ||
               directions == IsoDirections.N ||
               directions == IsoDirections.NE)) {
            directions = IsoDirections.N;
            boolean0 = true;
          }

          if (square1.getProperties().Is(IsoFlagType.HoppableN) &&
              this.collidedS && !this.collidedW && !this.collidedE &&
              (directions == IsoDirections.SW ||
               directions == IsoDirections.S ||
               directions == IsoDirections.SE)) {
            directions = IsoDirections.S;
            boolean0 = true;
          }

          if (this.current.getProperties().Is(IsoFlagType.HoppableW) &&
              this.collidedW && !this.collidedN && !this.collidedS &&
              (directions == IsoDirections.NW ||
               directions == IsoDirections.W ||
               directions == IsoDirections.SW)) {
            directions = IsoDirections.W;
            boolean0 = true;
          }

          if (square1.getProperties().Is(IsoFlagType.HoppableW) &&
              this.collidedE && !this.collidedN && !this.collidedS &&
              (directions == IsoDirections.NE ||
               directions == IsoDirections.E ||
               directions == IsoDirections.SE)) {
            directions = IsoDirections.E;
            boolean0 = true;
          }

          if (boolean0 && player.isSafeToClimbOver(directions)) {
            ClimbOverFenceState.instance().setParams(player, directions);
            player.getActionContext().reportEvent("EventClimbFence");
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

    if (this.current != nullptr &&
        !this.current.getMovingObjects().contains(this)) {
      this.current.getMovingObjects().add(this);
      this.movingSq = this.current;
    }
  }

  IsoGridSquare getFeelerTile(float dist) {
    Vector2 vector = tempo;
    vector.x = this.nx - this.lx;
    vector.y = this.ny - this.ly;
    vector.setLength(dist);
    return this.getCell().getGridSquare((int)(this.x + vector.x),
                                        (int)(this.y + vector.y), (int)this.z);
  }

  void DoCollideNorS() { this.ny = this.ly; }

  void DoCollideWorE() { this.nx = this.lx; }

  /**
   * @return the TimeSinceZombieAttack
   */
  int getTimeSinceZombieAttack() { return this.TimeSinceZombieAttack; }

  /**
   *
   * @param _TimeSinceZombieAttack the TimeSinceZombieAttack to set
   */
  void setTimeSinceZombieAttack(int _TimeSinceZombieAttack) {
    this.TimeSinceZombieAttack = _TimeSinceZombieAttack;
  }

  /**
   * @return the collidedE
   */
  bool isCollidedE() { return this.collidedE; }

  /**
   *
   * @param _collidedE the collidedE to set
   */
  void setCollidedE(bool _collidedE) { this.collidedE = _collidedE; }

  /**
   * @return the collidedN
   */
  bool isCollidedN() { return this.collidedN; }

  /**
   *
   * @param _collidedN the collidedN to set
   */
  void setCollidedN(bool _collidedN) { this.collidedN = _collidedN; }

  /**
   * @return the CollidedObject
   */
  IsoObject getCollidedObject() { return this.CollidedObject; }

  /**
   *
   * @param _CollidedObject the CollidedObject to set
   */
  void setCollidedObject(IsoObject _CollidedObject) {
    this.CollidedObject = _CollidedObject;
  }

  /**
   * @return the collidedS
   */
  bool isCollidedS() { return this.collidedS; }

  /**
   *
   * @param _collidedS the collidedS to set
   */
  void setCollidedS(bool _collidedS) { this.collidedS = _collidedS; }

  /**
   * @return the collidedThisFrame
   */
  bool isCollidedThisFrame() { return this.collidedThisFrame; }

  /**
   *
   * @param _collidedThisFrame the collidedThisFrame to set
   */
  void setCollidedThisFrame(bool _collidedThisFrame) {
    this.collidedThisFrame = _collidedThisFrame;
  }

  /**
   * @return the collidedW
   */
  bool isCollidedW() { return this.collidedW; }

  /**
   *
   * @param _collidedW the collidedW to set
   */
  void setCollidedW(bool _collidedW) { this.collidedW = _collidedW; }

  /**
   * @return the CollidedWithDoor
   */
  bool isCollidedWithDoor() { return this.CollidedWithDoor; }

  /**
   *
   * @param _CollidedWithDoor the CollidedWithDoor to set
   */
  void setCollidedWithDoor(bool _CollidedWithDoor) {
    this.CollidedWithDoor = _CollidedWithDoor;
  }

  bool isCollidedWithVehicle() { return this.collidedWithVehicle; }

  /**
   * @return the current
   */
  IsoGridSquare getCurrentSquare() { return this.current; }

public
  IsoMetaGrid.Zone getCurrentZone() {
    return this.current != nullptr ? this.current.getZone() : nullptr;
  }

  /**
   *
   * @param _current the current to set
   */
  void setCurrent(IsoGridSquare _current) { this.current = _current; }

  /**
   * @return the destroyed
   */
  bool isDestroyed() { return this.destroyed; }

  /**
   *
   * @param _destroyed the destroyed to set
   */
  void setDestroyed(bool _destroyed) { this.destroyed = _destroyed; }

  /**
   * @return the firstUpdate
   */
  bool isFirstUpdate() { return this.firstUpdate; }

  /**
   *
   * @param _firstUpdate the firstUpdate to set
   */
  void setFirstUpdate(bool _firstUpdate) { this.firstUpdate = _firstUpdate; }

  /**
   * @return the hitDir
   */
  Vector2 getHitDir() { return this.hitDir; }

  /**
   *
   * @param _hitDir the hitDir to set
   */
  void setHitDir(Vector2 _hitDir) { this.hitDir.set(_hitDir); }

  /**
   * @return the impulsex
   */
  float getImpulsex() { return this.impulsex; }

  /**
   *
   * @param _impulsex the impulsex to set
   */
  void setImpulsex(float _impulsex) { this.impulsex = _impulsex; }

  /**
   * @return the impulsey
   */
  float getImpulsey() { return this.impulsey; }

  /**
   *
   * @param _impulsey the impulsey to set
   */
  void setImpulsey(float _impulsey) { this.impulsey = _impulsey; }

  /**
   * @return the limpulsex
   */
  float getLimpulsex() { return this.limpulsex; }

  /**
   *
   * @param _limpulsex the limpulsex to set
   */
  void setLimpulsex(float _limpulsex) { this.limpulsex = _limpulsex; }

  /**
   * @return the limpulsey
   */
  float getLimpulsey() { return this.limpulsey; }

  /**
   *
   * @param _limpulsey the limpulsey to set
   */
  void setLimpulsey(float _limpulsey) { this.limpulsey = _limpulsey; }

  /**
   * @return the hitForce
   */
  float getHitForce() { return this.hitForce; }

  /**
   *
   * @param _hitForce the hitForce to set
   */
  void setHitForce(float _hitForce) { this.hitForce = _hitForce; }

  /**
   * @return the hitFromAngle
   */
  float getHitFromAngle() { return this.hitFromAngle; }

  /**
   *
   * @param _hitFromAngle the hitFromAngle to set
   */
  void setHitFromAngle(float _hitFromAngle) {
    this.hitFromAngle = _hitFromAngle;
  }

  /**
   * @return the last
   */
  IsoGridSquare getLastSquare() { return this.last; }

  /**
   *
   * @param _last the last to set
   */
  void setLast(IsoGridSquare _last) { this.last = _last; }

  /**
   * @return the lx
   */
  float getLx() { return this.lx; }

  /**
   *
   * @param _lx the lx to set
   */
  void setLx(float _lx) { this.lx = _lx; }

  /**
   * @return the ly
   */
  float getLy() { return this.ly; }

  /**
   *
   * @param _ly the ly to set
   */
  void setLy(float _ly) { this.ly = _ly; }

  /**
   * @return the lz
   */
  float getLz() { return this.lz; }

  /**
   *
   * @param _lz the lz to set
   */
  void setLz(float _lz) { this.lz = _lz; }

  /**
   * @return the nx
   */
  float getNx() { return this.nx; }

  /**
   *
   * @param _nx the nx to set
   */
  void setNx(float _nx) { this.nx = _nx; }

  /**
   * @return the ny
   */
  float getNy() { return this.ny; }

  /**
   *
   * @param _ny the ny to set
   */
  void setNy(float _ny) { this.ny = _ny; }

  /**
   * @return whether the object should take damage or not.
   */
  bool getNoDamage() { return this.noDamage; }

  /**
   *
   * @param dmg whether the object should take damage.
   */
  void setNoDamage(bool dmg) { this.noDamage = dmg; }

  /**
   * @return the solid
   */
  bool isSolid() { return this.solid; }

  /**
   *
   * @param _solid the solid to set
   */
  void setSolid(bool _solid) { this.solid = _solid; }

  /**
   * @return the StateEventDelayTimer
   */
  float getStateEventDelayTimer() { return this.StateEventDelayTimer; }

  /**
   *
   * @param _StateEventDelayTimer the StateEventDelayTimer to set
   */
  void setStateEventDelayTimer(float _StateEventDelayTimer) {
    this.StateEventDelayTimer = _StateEventDelayTimer;
  }

  /**
   * @return the width
   */
  float getWidth() { return this.width; }

  /**
   *
   * @param _width the width to set
   */
  void setWidth(float _width) { this.width = _width; }

  /**
   * @return the bAltCollide
   */
  bool isbAltCollide() { return this.bAltCollide; }

  /**
   *
   * @param _bAltCollide the bAltCollide to set
   */
  void setbAltCollide(bool _bAltCollide) { this.bAltCollide = _bAltCollide; }

  /**
   * @return the shootable
   */
  bool isShootable() { return this.shootable; }

  /**
   *
   * @param _shootable the shootable to set
   */
  void setShootable(bool _shootable) { this.shootable = _shootable; }

  /**
   * @return the lastTargettedBy
   */
  IsoZombie getLastTargettedBy() { return this.lastTargettedBy; }

  /**
   *
   * @param _lastTargettedBy the lastTargettedBy to set
   */
  void setLastTargettedBy(IsoZombie _lastTargettedBy) {
    this.lastTargettedBy = _lastTargettedBy;
  }

  /**
   * @return the Collidable
   */
  bool isCollidable() { return this.Collidable; }

  /**
   *
   * @param _Collidable the Collidable to set
   */
  void setCollidable(bool _Collidable) { this.Collidable = _Collidable; }

  /**
   * @return the scriptnx
   */
  float getScriptnx() { return this.scriptnx; }

  /**
   *
   * @param _scriptnx the scriptnx to set
   */
  void setScriptnx(float _scriptnx) { this.scriptnx = _scriptnx; }

  /**
   * @return the scriptny
   */
  float getScriptny() { return this.scriptny; }

  /**
   *
   * @param _scriptny the scriptny to set
   */
  void setScriptny(float _scriptny) { this.scriptny = _scriptny; }

  /**
   * @return the ScriptModule
   */
  std::string getScriptModule() { return this.ScriptModule; }

  /**
   *
   * @param _ScriptModule the ScriptModule to set
   */
  void setScriptModule(const std::string &_ScriptModule) {
    this.ScriptModule = _ScriptModule;
  }

  /**
   * @return the movementLastFrame
   */
  Vector2 getMovementLastFrame() { return this.movementLastFrame; }

  /**
   *
   * @param _movementLastFrame the movementLastFrame to set
   */
  void setMovementLastFrame(Vector2 _movementLastFrame) {
    this.movementLastFrame = _movementLastFrame;
  }

  /**
   * @return the feelersize
   */
  float getFeelersize() { return this.feelersize; }

  /**
   *
   * @param _feelersize the feelersize to set
   */
  void setFeelersize(float _feelersize) { this.feelersize = _feelersize; }

  /**
   * This function calculate count of attackers
   * @return 0 - no attackets, 1 - one player can attack this character, 2 -
   * multiply players can attack this character
   */
  uint8_t canHaveMultipleHits() {
    uint8_t byte0 = 0;
    std::vector arrayList = IsoWorld.instance.CurrentCell.getObjectList();

    for (int int0 = 0; int0 < arrayList.size(); int0++) {
      IsoMovingObject movingObject0 = (IsoMovingObject)arrayList.get(int0);
      IsoPlayer player = Type.tryCastTo(movingObject0, IsoPlayer.class);
      if (player != nullptr) {
        HandWeapon weapon =
            Type.tryCastTo(player.getPrimaryHandItem(), HandWeapon.class);
        if (weapon == nullptr || player.bDoShove || player.isForceShove()) {
          weapon = player.bareHands;
        }

        float float0 = IsoUtils.DistanceTo(player.x, player.y, this.x, this.y);
        float float1 = weapon.getMaxRange() * weapon.getRangeMod(player) + 2.0F;
        if (!(float0 > float1)) {
          float float2 = player.getDotWithForwardDirection(this.x, this.y);
          if (!(float0 > 2.5) || !(float2 < 0.1F)) {
            LosUtil.TestResults testResults = LosUtil.lineClear(
                player.getCell(), (int)player.getX(), (int)player.getY(),
                (int)player.getZ(), (int)this.getX(), (int)this.getY(),
                (int)this.getZ(), false);
            if (testResults != LosUtil.TestResults.Blocked &&
                testResults != LosUtil.TestResults.ClearThroughClosedDoor) {
              if (++byte0 >= 2) {
                return byte0;
              }
            }
          }
        }
      }
    }

    return byte0;
  }

  bool isOnFloor() { return this.bOnFloor; }

  void setOnFloor(bool _bOnFloor) { this.bOnFloor = _bOnFloor; }

  void Despawn() {}

  bool isCloseKilled() { return this.closeKilled; }

  void setCloseKilled(bool _closeKilled) { this.closeKilled = _closeKilled; }

  Vector2 getFacingPosition(Vector2 pos) {
    pos.set(this.getX(), this.getY());
    return pos;
  }

  bool isInLoadedArea(int int2, int int1) {
    if (GameServer.bServer) {
      for (int int0 = 0; int0 < ServerMap.instance.LoadedCells.size(); int0++) {
        ServerMap.ServerCell serverCell =
            ServerMap.instance.LoadedCells.get(int0);
        if (int2 >= serverCell.WX * 50 && int2 < (serverCell.WX + 1) * 50 &&
            int1 >= serverCell.WY * 50 && int1 < (serverCell.WY + 1) * 50) {
          return true;
        }
      }
    } else {
      for (int int3 = 0; int3 < IsoPlayer.numPlayers; int3++) {
        IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[int3];
        if (!chunkMap.ignore && int2 >= chunkMap.getWorldXMinTiles() &&
            int2 < chunkMap.getWorldXMaxTiles() &&
            int1 >= chunkMap.getWorldYMinTiles() &&
            int1 < chunkMap.getWorldYMaxTiles()) {
          return true;
        }
      }
    }

    return false;
  }

  bool isCollided() {
    return !StringUtils.isNullOrWhitespace(this.getCollideType());
  }

  std::string getCollideType() { return this.collideType; }

  void setCollideType(const std::string &_collideType) {
    this.collideType = _collideType;
  }

  float getLastCollideTime() { return this.lastCollideTime; }

  void setLastCollideTime(float _lastCollideTime) {
    this.lastCollideTime = _lastCollideTime;
  }

public
  ArrayList<IsoZombie> getEatingZombies() { return this.eatingZombies; }

  void setEatingZombies(ArrayList<IsoZombie> zeds) {
    this.eatingZombies.clear();
    this.eatingZombies.addAll(zeds);
  }

  bool isEatingOther(IsoMovingObject other) {
    return other = = null ? false : other.eatingZombies.contains(this);
  }

  float getDistanceSq(IsoMovingObject other) {
    float float0 = this.x - other.x;
    float float1 = this.y - other.y;
    float0 *= float0;
    float1 *= float1;
    return float0 + float1;
  }

  void setZombiesDontAttack(bool b) { this.zombiesDontAttack = b; }

  bool isZombiesDontAttack() { return this.zombiesDontAttack; }

private
  static final class L_postUpdate {
    static const Vector2f vector2f = new Vector2f();
  }

  private static final class L_slideAwayFromWalls {
    static const Vector2f vector2f = new Vector2f();
    static const Vector2 vector2 = new Vector2();
    static const Vector3 vector3 = new Vector3();
  }

  public static class TreeSoundManager {
  private
    ArrayList<IsoGridSquare> squares = std::make_unique<ArrayList<>>();
  private
    long[] soundTime = new long[6];
  private
    Comparator<IsoGridSquare> comp = (square0, square1)->{
      float float0 = this.getClosestListener(square0.x + 0.5F, square0.y + 0.5F,
                                             square0.z);
      float float1 = this.getClosestListener(square1.x + 0.5F, square1.y + 0.5F,
                                             square1.z);
      if (float0 > float1) {
        return 1;
      } else {
        return float0 < float1 ? -1 : 0;
      }
    };

    void addSquare(IsoGridSquare square) {
      if (!this.squares.contains(square)) {
        this.squares.add(square);
      }
    }

    void update() {
      if (!this.squares.isEmpty()) {
        Collections.sort(this.squares, this.comp);
        long long0 = System.currentTimeMillis();

        for (int int0 = 0;
             int0 < this.soundTime.length && int0 < this.squares.size();
             int0++) {
          IsoGridSquare square = this.squares.get(int0);
          if (!(this.getClosestListener(square.x + 0.5F, square.y + 0.5F,
                                        square.z) > 20.0F)) {
            int int1 = this.getFreeSoundSlot(long0);
            if (int1 == -1) {
              break;
            }

            Audio audio = null;
            float float0 = 0.05F;
            float float1 = 16.0F;
            float float2 = 0.29999998F;
            if (GameClient.bClient) {
              audio = SoundManager.instance.PlayWorldSoundImpl(
                  "Bushes", false, square.getX(), square.getY(), square.getZ(),
                  float0, float1, float2, false);
            } else {
              BaseSoundEmitter baseSoundEmitter =
                  IsoWorld.instance.getFreeEmitter(square.x + 0.5F,
                                                   square.y + 0.5F, square.z);
              if (baseSoundEmitter.playSound("Bushes") != 0L) {
                this.soundTime[int1] = long0;
              }
            }

            if (audio != nullptr) {
              this.soundTime[int1] = long0;
            }
          }
        }

        this.squares.clear();
      }
    }

    float getClosestListener(float float5, float float6, float float7) {
      float float0 = Float.MAX_VALUE;

      for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
        IsoPlayer player = IsoPlayer.players[int0];
        if (player != nullptr && player.getCurrentSquare() != nullptr) {
          float float1 = player.getX();
          float float2 = player.getY();
          float float3 = player.getZ();
          float float4 = IsoUtils.DistanceTo(float1, float2, float3 * 3.0F,
                                             float5, float6, float7 * 3.0F);
          if (player.Traits.HardOfHearing.isSet()) {
            float4 *= 4.5F;
          }

          if (float4 < float0) {
            float0 = float4;
          }
        }
      }

      return float0;
    }

    int getFreeSoundSlot(long long1) {
      long long0 = Long.MAX_VALUE;
      int int0 = -1;

      for (int int1 = 0; int1 < this.soundTime.length; int1++) {
        if (this.soundTime[int1] < long0) {
          long0 = this.soundTime[int1];
          int0 = int1;
        }
      }

      return long1 - long0 < 1000L ? -1 : int0;
    }
  }
}
} // namespace iso
} // namespace zombie
