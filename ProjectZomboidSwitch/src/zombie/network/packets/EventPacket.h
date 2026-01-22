#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/ai/states/ClimbDownSheetRopeState.h"
#include "zombie/ai/states/ClimbSheetRopeState.h"
#include "zombie/ai/states/FishingState.h"
#include "zombie/ai/states/SmashWindowState.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/NetworkPlayerVariables.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/EventPacket/1.h"
#include "zombie/network/packets/EventPacket/EventType.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class EventPacket {
public:
    static const int MAX_PLAYER_EVENTS = 10;
    static const long EVENT_TIMEOUT = 5000L;
    static const short EVENT_FLAGS_VAULT_OVER_SPRINT = 1;
    static const short EVENT_FLAGS_VAULT_OVER_RUN = 2;
    static const short EVENT_FLAGS_BUMP_FALL = 4;
    static const short EVENT_FLAGS_BUMP_STAGGERED = 8;
    static const short EVENT_FLAGS_ACTIVATE_ITEM = 16;
    static const short EVENT_FLAGS_CLIMB_SUCCESS = 32;
    static const short EVENT_FLAGS_CLIMB_STRUGGLE = 64;
    static const short EVENT_FLAGS_BUMP_FROM_BEHIND = 128;
    static const short EVENT_FLAGS_BUMP_TARGET_TYPE = 256;
    static const short EVENT_FLAGS_PRESSED_MOVEMENT = 512;
    static const short EVENT_FLAGS_PRESSED_CANCEL_ACTION = 1024;
    static const short EVENT_FLAGS_SMASH_CAR_WINDOW = 2048;
    static const short EVENT_FLAGS_FITNESS_FINISHED = 4096;
    short id;
    float x;
    float y;
    float z;
    uint8_t eventID;
    std::string type1;
    std::string type2;
    std::string type3;
    std::string type4;
    float strafeSpeed;
    float walkSpeed;
    float walkInjury;
    int booleanVariables;
    short flags;
    IsoPlayer player;
    EventType event;
    long timestamp;

    std::string getDescription() {
      return "[ player="
         + this.id
         + " \""
         + (this.player == nullptr ? "?" : this.player.getUsername())
         + "\" | name=\""
         + (this.event == nullptr ? "?" : this.event.name())
         + "\" | pos=( "
         + this.x
         + " ; "
         + this.y
         + " ; "
         + this.z
         + " ) | type1=\""
         + this.type1
         + "\" | type2=\""
         + this.type2
         + "\" | type3=\""
         + this.type3
         + "\" | type4=\""
         + this.type4
         + "\" | flags="
         + this.flags
         + "\" | variables="
         + this.booleanVariables
         + " ]";
   }

    bool isConsistent() {
    bool var1 = this.player != nullptr && this.event != nullptr;
      if (!var1 && Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, "[Event] is not consistent " + this.getDescription());
      }

    return var1;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.eventID = var1.get();
      this.type1 = GameWindow.ReadString(var1);
      this.type2 = GameWindow.ReadString(var1);
      this.type3 = GameWindow.ReadString(var1);
      this.type4 = GameWindow.ReadString(var1);
      this.strafeSpeed = var1.getFloat();
      this.walkSpeed = var1.getFloat();
      this.walkInjury = var1.getFloat();
      this.booleanVariables = var1.getInt();
      this.flags = var1.getShort();
      if (this.eventID >= 0 && this.eventID < EventType.values().length) {
         this.event = EventType.values()[this.eventID];
      } else {
         DebugLog.Multiplayer.warn("Unknown event=" + this.eventID);
         this.event = nullptr;
      }

      if (GameServer.bServer) {
         this.player = (IsoPlayer)GameServer.IDToPlayerMap.get(this.id);
      } else if (GameClient.bClient) {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(this.id);
      } else {
         this.player = nullptr;
      }

      this.timestamp = System.currentTimeMillis() + 5000L;
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putFloat(this.z);
      var1.putByte(this.eventID);
      var1.putUTF(this.type1);
      var1.putUTF(this.type2);
      var1.putUTF(this.type3);
      var1.putUTF(this.type4);
      var1.putFloat(this.strafeSpeed);
      var1.putFloat(this.walkSpeed);
      var1.putFloat(this.walkInjury);
      var1.putInt(this.booleanVariables);
      var1.putShort(this.flags);
   }

    bool isRelevant(UdpConnection var1) {
      return var1.RelevantTo(this.x, this.y);
   }

    bool isMovableEvent() {
      return !this.isConsistent() ? false : EventType.EventClimbFence == this.event) || EventType.EventFallClimb == this.event);
   }

    bool requireNonMoving() {
      return this.isConsistent()
         && (
            EventType.EventClimbWindow == this.event)
               || EventType.EventClimbFence == this.event)
               || EventType.EventClimbDownRope == this.event)
               || EventType.EventClimbRope == this.event)
               || EventType.EventClimbWall == this.event)
         );
   }

    IsoWindow getWindow(IsoPlayer var1) {
      for (IsoDirections var5 : IsoDirections.values()) {
    IsoObject var6 = var1.getContextDoorOrWindowOrWindowFrame(var5);
         if (dynamic_cast<IsoWindow*>(var6) != nullptr) {
            return (IsoWindow)var6;
         }
      }

    return nullptr;
   }

    IsoObject getObject(IsoPlayer var1) {
      for (IsoDirections var5 : IsoDirections.values()) {
    IsoObject var6 = var1.getContextDoorOrWindowOrWindowFrame(var5);
         if (dynamic_cast<IsoWindow*>(var6) != nullptr || dynamic_cast<IsoThumpable*>(var6) != nullptr || IsoWindowFrame.isWindowFrame(var6)) {
    return var6;
         }
      }

    return nullptr;
   }

    IsoDirections checkCurrentIsEventGridSquareFence(IsoPlayer var1) {
    IsoGridSquare var3 = var1.getCell().getGridSquare(this.x, this.y, this.z);
    IsoGridSquare var4 = var1.getCell().getGridSquare(this.x, this.y + 1.0F, this.z);
    IsoGridSquare var5 = var1.getCell().getGridSquare(this.x + 1.0F, this.y, this.z);
    IsoDirections var2;
      if (var3 != nullptr && var3.Is(IsoFlagType.HoppableN)) {
         var2 = IsoDirections.N;
      } else if (var3 != nullptr && var3.Is(IsoFlagType.HoppableW)) {
         var2 = IsoDirections.W;
      } else if (var4 != nullptr && var4.Is(IsoFlagType.HoppableN)) {
         var2 = IsoDirections.S;
      } else if (var5 != nullptr && var5.Is(IsoFlagType.HoppableW)) {
         var2 = IsoDirections.E;
      } else {
         var2 = IsoDirections.Max;
      }

    return var2;
   }

    bool isTimeout() {
      return System.currentTimeMillis() > this.timestamp;
   }

    void tryProcess() {
      if (this.isConsistent()) {
         if (this.player.networkAI.events.size() < 10) {
            this.player.networkAI.events.push_back(this);
         } else {
            DebugLog.Multiplayer.warn("Event skipped: " + this.getDescription());
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool process(IsoPlayer var1) {
    bool var2 = false;
      if (this.isConsistent()) {
         var1.overridePrimaryHandModel = nullptr;
         var1.overrideSecondaryHandModel = nullptr;
         if (var1.getCurrentSquare() == var1.getCell().getGridSquare(this.x, this.y, this.z) && !var1.isPlayerMoving() || !this.requireNonMoving()) {
            switch (1.$SwitchMap$zombie$network$packets$EventPacket$EventType[this.event.ordinal()]) {
               case 1:
                  if (var1.getPrimaryHandItem() != nullptr && var1.getPrimaryHandItem().canEmitLight()) {
                     var1.getPrimaryHandItem().setActivatedRemote((this.flags & 16) != 0);
                     var2 = true;
                  }
                  break;
               case 2:
                  if (var1.getSecondaryHandItem() != nullptr && var1.getSecondaryHandItem().canEmitLight()) {
                     var1.getSecondaryHandItem().setActivatedRemote((this.flags & 16) != 0);
                     var2 = true;
                  }
                  break;
               case 3:
                  var1.setVariable("ClimbFenceOutcome", "fall");
                  var1.setVariable("BumpDone", true);
                  var1.setFallOnFront(true);
                  var2 = true;
                  break;
               case 4:
                  var1.setCollideType(this.type1);
                  var1.actionContext.reportEvent("collideWithWall");
                  var2 = true;
                  break;
               case 5:
                  var1.setVariable("FishingStage", this.type1);
                  if (!FishingState.instance() == var1.getCurrentState())) {
                     var1.setVariable("forceGetUp", true);
                     var1.actionContext.reportEvent("EventFishing");
                  }

                  var2 = true;
                  break;
               case 6:
                  var1.setVariable("ExerciseType", this.type1);
                  var1.setVariable("FitnessFinished", false);
                  var1.actionContext.reportEvent("EventFitness");
                  var2 = true;
                  break;
               case 7:
                  var1.clearVariable("ExerciseHand");
                  var1.setVariable("ExerciseType", this.type2);
                  if (!StringUtils.isNullOrEmpty(this.type1)) {
                     var1.setVariable("ExerciseHand", this.type1);
                  }

                  var1.setFitnessSpeed();
                  if ((this.flags & 4096) != 0) {
                     var1.setVariable("ExerciseStarted", false);
                     var1.setVariable("ExerciseEnded", true);
                  }

                  var1.setPrimaryHandItem(nullptr);
                  var1.setSecondaryHandItem(nullptr);
                  var1.overridePrimaryHandModel = nullptr;
                  var1.overrideSecondaryHandModel = nullptr;
                  var1.overridePrimaryHandModel = this.type3;
                  var1.overrideSecondaryHandModel = this.type4;
                  var1.resetModelNextFrame();
                  var2 = true;
                  break;
               case 8:
                  var1.setVariable("emote", this.type1);
                  var1.actionContext.reportEvent("EventEmote");
                  var2 = true;
                  break;
               case 9:
                  var1.actionContext.reportEvent("EventSitOnGround");
                  var2 = true;
                  break;
               case 10:
                  var1.climbSheetRope();
                  var2 = true;
                  break;
               case 11:
                  var1.climbDownSheetRope();
                  var2 = true;
                  break;
               case 12:
    IsoDirections var14 = this.checkCurrentIsEventGridSquareFence(var1);
                  if (var14 != IsoDirections.Max) {
                     var1.climbOverFence(var14);
                     if (var1.isSprinting()) {
                        var1.setVariable("VaultOverSprint", true);
                     }

                     if (var1.isRunning()) {
                        var1.setVariable("VaultOverRun", true);
                     }

                     var2 = true;
                  }
                  break;
               case 13:
                  var1.setClimbOverWallStruggle((this.flags & 64) != 0);
                  var1.setClimbOverWallSuccess((this.flags & 32) != 0);

                  for (IsoDirections var6 : IsoDirections.values()) {
                     if (var1.climbOverWall(var6)) {
    return true;
                     }
                  }
                  break;
               case 14:
    IsoObject var12 = this.getObject(var1);
                  if (dynamic_cast<IsoWindow*>(var12) != nullptr) {
                     var1.climbThroughWindow((IsoWindow)var12);
                     var2 = true;
                  } else if (dynamic_cast<IsoThumpable*>(var12) != nullptr) {
                     var1.climbThroughWindow((IsoThumpable)var12);
                     var2 = true;
                  }

                  if (IsoWindowFrame.isWindowFrame(var12)) {
                     var1.climbThroughWindowFrame(var12);
                     var2 = true;
                  }
                  break;
               case 15:
    IsoWindow var11 = this.getWindow(var1);
                  if (var11 != nullptr) {
                     var1.openWindow(var11);
                     var2 = true;
                  }
                  break;
               case 16:
    IsoWindow var10 = this.getWindow(var1);
                  if (var10 != nullptr) {
                     var1.closeWindow(var10);
                     var2 = true;
                  }
                  break;
               case 17:
                  if ((this.flags & 2048) != 0) {
    BaseVehicle var8 = VehicleManager.instance.getVehicleByID(int16_t.parseShort(this.type1));
                     if (var8 != nullptr) {
    VehiclePart var4 = var8.getPartById(this.type2);
                        if (var4 != nullptr) {
    VehicleWindow var5 = var4.getWindow();
                           if (var5 != nullptr) {
                              var1.smashCarWindow(var4);
                              var2 = true;
                           }
                        }
                     }
                  } else {
    IsoWindow var9 = this.getWindow(var1);
                     if (var9 != nullptr) {
                        var1.smashWindow(var9);
                        var2 = true;
                     }
                  }
                  break;
               case 18:
                  var1.setBumpDone(false);
                  var1.setVariable("BumpFallAnimFinished", false);
                  var1.setBumpType(this.type1);
                  var1.setBumpFallType(this.type2);
                  var1.setBumpFall((this.flags & 4) != 0);
                  var1.setBumpStaggered((this.flags & 8) != 0);
                  var1.reportEvent("wasBumped");
                  if (!StringUtils.isNullOrEmpty(this.type3) && !StringUtils.isNullOrEmpty(this.type4)) {
    IsoGameCharacter var3 = nullptr;
                     if ((this.flags & 256) != 0) {
                        var3 = (IsoGameCharacter)GameClient.IDToZombieMap.get(int16_t.parseShort(this.type3));
                     } else {
                        var3 = (IsoGameCharacter)GameClient.IDToPlayerMap.get(int16_t.parseShort(this.type3));
                     }

                     if (var3 != nullptr) {
                        var3.setBumpType(this.type4);
                        var3.setHitFromBehind((this.flags & 128) != 0);
                     }
                  }

                  var2 = true;
                  break;
               case 19:
                  if (var1.getNetworkCharacterAI().getAction() != nullptr) {
                     var1.getNetworkCharacterAI().setOverride(true, this.type1, this.type2);
                  }

                  var2 = true;
                  break;
               case 20:
                  var2 = true;
                  break;
               case 21:
                  var1.networkAI.setPressedMovement((this.flags & 512) != 0);
                  var1.networkAI.setPressedCancelAction((this.flags & 1024) != 0);
                  var2 = true;
                  break;
               case 22:
               default:
                  DebugLog.Multiplayer.warn("[Event] unknown: " + this.getDescription());
                  var2 = true;
            }
         }
      }

    return var2;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool set(IsoPlayer var1, const std::string& var2) {
    bool var3 = false;
      this.player = var1;
      this.id = var1.getOnlineID();
      this.x = var1.getX();
      this.y = var1.getY();
      this.z = var1.getZ();
      this.type1 = nullptr;
      this.type2 = nullptr;
      this.type3 = nullptr;
      this.type4 = nullptr;
      this.booleanVariables = NetworkPlayerVariables.getBooleanVariables(var1);
      this.strafeSpeed = var1.getVariableFloat("StrafeSpeed", 1.0F);
      this.walkSpeed = var1.getVariableFloat("WalkSpeed", 1.0F);
      this.walkInjury = var1.getVariableFloat("WalkInjury", 0.0F);
      this.flags = 0;

      for (EventType var7 : EventType.values()) {
         if (var7.name() == var2)) {
            this.event = var7;
            this.eventID = (byte)var7.ordinal();
            switch (1.$SwitchMap$zombie$network$packets$EventPacket$EventType[var7.ordinal()]) {
               case 1:
                  this.flags = (short)(this.flags | (var1.getPrimaryHandItem().isActivated() ? 16 : 0));
                  break;
               case 2:
                  this.flags = (short)(this.flags | (var1.getSecondaryHandItem().isActivated() ? 16 : 0));
               case 3:
               case 9:
               case 10:
               case 11:
               case 14:
               case 15:
               case 16:
               case 20:
                  break;
               case 4:
                  this.type1 = var1.getCollideType();
                  break;
               case 5:
                  this.type1 = var1.getVariableString("FishingStage");
                  break;
               case 6:
                  this.type1 = var1.getVariableString("ExerciseType");
                  break;
               case 7:
                  this.type1 = var1.getVariableString("ExerciseHand");
                  this.type2 = var1.getVariableString("ExerciseType");
                  if (var1.getPrimaryHandItem() != nullptr) {
                     this.type3 = var1.getPrimaryHandItem().getStaticModel();
                  }

                  if (var1.getSecondaryHandItem() != nullptr && var1.getSecondaryHandItem() != var1.getPrimaryHandItem()) {
                     this.type4 = var1.getSecondaryHandItem().getStaticModel();
                  }

                  this.flags = (short)(this.flags | (var1.getVariableBoolean("FitnessFinished") ? 4096 : 0));
                  break;
               case 8:
                  this.type1 = var1.getVariableString("emote");
                  break;
               case 12:
                  if (var1.getVariableBoolean("VaultOverRun")) {
                     this.flags = (short)(this.flags | 2);
                  }

                  if (var1.getVariableBoolean("VaultOverSprint")) {
                     this.flags = (short)(this.flags | 1);
                  }
                  break;
               case 13:
                  this.flags = (short)(this.flags | (var1.isClimbOverWallSuccess() ? 32 : 0));
                  this.flags = (short)(this.flags | (var1.isClimbOverWallStruggle() ? 64 : 0));
                  break;
               case 17:
    std::unordered_map var11 = var1.getStateMachineParams(SmashWindowState.instance());
                  if (var11.get(1) instanceof BaseVehicle && var11.get(2) instanceof VehiclePart) {
    BaseVehicle var9 = (BaseVehicle)var11.get(1);
    VehiclePart var10 = (VehiclePart)var11.get(2);
                     this.flags = (short)(this.flags | 2048);
                     this.type1 = std::string.valueOf(var9.getId());
                     this.type2 = var10.getId();
                  }
                  break;
               case 18:
                  this.type1 = var1.getBumpType();
                  this.type2 = var1.getBumpFallType();
                  this.flags = (short)(this.flags | (var1.isBumpFall() ? 4 : 0));
                  this.flags = (short)(this.flags | (var1.isBumpStaggered() ? 8 : 0));
                  if (var1.getBumpedChr() != nullptr) {
                     this.type3 = std::string.valueOf(var1.getBumpedChr().getOnlineID());
                     this.type4 = var1.getBumpedChr().getBumpType();
                     this.flags = (short)(this.flags | (var1.isHitFromBehind() ? 128 : 0));
                     if (var1.getBumpedChr() instanceof IsoZombie) {
                        this.flags = (short)(this.flags | 256);
                     }
                  }
                  break;
               case 19:
                  if (var1.getNetworkCharacterAI().getAction() == nullptr) {
    return false;
                  }

    BaseAction var8 = var1.getNetworkCharacterAI().getAction();
                  this.type1 = var8.getPrimaryHandItem() == nullptr ? var8.getPrimaryHandMdl() : var8.getPrimaryHandItem().getStaticModel();
                  this.type2 = var8.getSecondaryHandItem() == nullptr ? var8.getSecondaryHandMdl() : var8.getSecondaryHandItem().getStaticModel();
                  break;
               case 21:
                  this.flags = (short)(this.flags | (var1.networkAI.isPressedMovement() ? 512 : 0));
                  this.flags = (short)(this.flags | (var1.networkAI.isPressedCancelAction() ? 1024 : 0));
                  break;
               default:
                  DebugLog.Multiplayer.warn("[Event] unknown " + this.getDescription());
    return false;
            }

            var3 = !ClimbDownSheetRopeState.instance() == var1.getCurrentState()) && !ClimbSheetRopeState.instance() == var1.getCurrentState());
         }
      }

    return var3;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
