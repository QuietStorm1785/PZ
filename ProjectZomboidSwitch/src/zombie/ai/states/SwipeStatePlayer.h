#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "org/joml/Vector3f.h"
#include "org/joml/Vector4f.h"
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/SwipeStatePlayer/CustomComparator.h"
#include "zombie/ai/states/SwipeStatePlayer/LOSVisitor.h"
#include "zombie/ai/states/SwipeStatePlayer/WindowVisitor.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/HitReactionNetworkAI.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/VehicleScript/Area.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"

namespace zombie {
namespace ai {
namespace states {


class SwipeStatePlayer : public State {
public:
    static const SwipeStatePlayer _instance = std::make_shared<SwipeStatePlayer>();
    static const int PARAM_LOWER_CONDITION = 0;
    static const int PARAM_ATTACKED = 1;
   private static const std::vector<HitInfo> HitList2 = std::make_unique<std::vector<>>();
    static const Vector2 tempVector2_1 = std::make_shared<Vector2>();
    static const Vector2 tempVector2_2 = std::make_shared<Vector2>();
   private const std::vector<float> dotList = std::make_unique<std::vector<>>();
    bool bHitOnlyTree;
   public const ObjectPool<HitInfo> hitInfoPool = std::make_shared<ObjectPool>(HitInfo::new);
    static const CustomComparator Comparator = std::make_shared<CustomComparator>();
    static const Vector3 tempVector3_1 = std::make_shared<Vector3>();
    static const Vector3 tempVector3_2 = std::make_shared<Vector3>();
    static const Vector3 tempVectorBonePos = std::make_shared<Vector3>();
   static const std::vector<IsoMovingObject> movingStatic = std::make_unique<std::vector<>>();
    const Vector4f tempVector4f = std::make_shared<Vector4f>();
    const WindowVisitor windowVisitor = std::make_shared<WindowVisitor>();

    static SwipeStatePlayer instance() {
    return _instance;
   }

    static void WeaponLowerCondition(HandWeapon var0, IsoGameCharacter var1) {
      if (var0.getUses() > 1) {
         var0.Use();
    InventoryItem var2 = InventoryItemFactory.CreateItem(var0.getFullType());
         var2.setCondition(var0.getCondition() - 1);
         var0.getContainer().AddItem(var2);
         var1.setPrimaryHandItem(var2);
      } else {
         var0.setCondition(var0.getCondition() - 1);
      }
   }

    static HandWeapon GetWeapon(IsoGameCharacter var0) {
    HandWeapon var1 = var0.getUseHandWeapon();
      if (((IsoLivingCharacter)var0).bDoShove || var0.isForceShove()) {
         var1 = ((IsoLivingCharacter)var0).bareHands;
      }

    return var1;
   }

    void doAttack(IsoPlayer var1, float var2, bool var3, const std::string& var4, AttackVars var5) {
      var1.setForceShove(var3);
      var1.setClickSound(var4);
      if (var3) {
         var2 *= 2.0F;
      }

      if (var2 > 90.0F) {
         var2 = 90.0F;
      }

      var2 /= 25.0F;
      var1.useChargeDelta = var2;
    void* var6 = var1.getPrimaryHandItem();
      if (var6 == nullptr || !(dynamic_cast<HandWeapon*>(var6) != nullptr) || var3 || var5.bDoShove) {
         var6 = var1.bareHands;
      }

      if (dynamic_cast<HandWeapon*>(var6) != nullptr) {
         var1.setUseHandWeapon((HandWeapon)var6);
         if (var1.PlayerIndex == 0 && var1.JoypadBind == -1 && UIManager.getPicked() != nullptr && (!GameClient.bClient || var1.isLocalPlayer())) {
            if (UIManager.getPicked().dynamic_cast<IsoMovingObject*>(tile) != nullptr) {
               var1.setAttackTargetSquare(((IsoMovingObject)UIManager.getPicked().tile).getCurrentSquare());
            } else {
               var1.setAttackTargetSquare(UIManager.getPicked().square);
            }
         }

         var1.setRecoilDelay(var5.recoilDelay);
         if (var3) {
            var1.setRecoilDelay(10.0F);
         }
      }
   }

    void enter(IsoGameCharacter var1) {
      if ("HitReaction" == var1.getHitReaction())) {
         var1.clearVariable("HitReaction");
      }

      UIManager.speedControls.SetCurrentGameSpeed(1);
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var2.put(PARAM_LOWER_CONDITION, bool.FALSE);
      var2.put(PARAM_ATTACKED, bool.FALSE);
      if (!(dynamic_cast<IsoPlayer*>(var1) != nullptr) || !((IsoPlayer)var1).bRemote) {
         var1.updateRecoilVar();
      }

      if ("Auto" == var1.getVariableString("FireMode"))) {
         var1.setVariable("autoShootSpeed", 4.0F * GameTime.getAnimSpeedFix());
         var1.setVariable("autoShootVarY", 0.0F);
         if (System.currentTimeMillis() - var1.lastAutomaticShoot < 600L) {
            var1.shootInARow++;
    float var3 = Math.max(0.0F, 1.0F - var1.shootInARow / 20.0F);
            var1.setVariable("autoShootVarX", var3);
         } else {
            var1.setVariable("autoShootVarX", 1.0F);
            var1.shootInARow = 0;
         }

         var1.lastAutomaticShoot = System.currentTimeMillis();
      }

    IsoPlayer var6 = (IsoPlayer)var1;
      var1.setVariable("ShotDone", false);
      var1.setVariable("ShoveAnim", false);
      this.CalcAttackVars((IsoLivingCharacter)var1, var6.attackVars);
      this.doAttack(var6, 2.0F, var1.isForceShove(), var1.getClickSound(), var6.attackVars);
    HandWeapon var4 = var1.getUseHandWeapon();
      if (!GameClient.bClient || var6.isLocalPlayer()) {
         var1.setVariable("AimFloorAnim", var6.attackVars.bAimAtFloor);
      }

      LuaEventManager.triggerEvent("OnWeaponSwing", var1, var4);
      if (LuaHookManager.TriggerHook("WeaponSwing", var1, var4)) {
         var1.getStateMachine().revertToPreviousState(this);
      }

      var1.StopAllActionQueue();
      if (((IsoPlayer)var1).isLocalPlayer()) {
         IsoWorld.instance.CurrentCell.setDrag(nullptr, ((IsoPlayer)var1).PlayerIndex);
      }

      var4 = var6.attackVars.getWeapon(var6);
      var6.setAimAtFloor(var6.attackVars.bAimAtFloor);
    bool var5 = var6.bDoShove;
      var6.setDoShove(var6.attackVars.bDoShove);
      var6.useChargeDelta = var6.attackVars.useChargeDelta;
      var6.targetOnGround = (IsoGameCharacter)var6.attackVars.targetOnGround.getMovingObject();
      if (!var6.bDoShove && !var5 && var6.getClickSound() == nullptr && var4.getPhysicsObject() == nullptr && !var4.isRanged()) {
      }

      if (GameClient.bClient && var1 == IsoPlayer.getInstance()) {
         GameClient.instance.sendPlayer((IsoPlayer)var1);
      }

      if (!var6.bDoShove && !var5 && !var4.isRanged() && var6.isLocalPlayer()) {
         var1.clearVariable("PlayedSwingSound");
      } else if ((var6.bDoShove || var5) && var6.isLocalPlayer()) {
         if (var6.targetOnGround != nullptr) {
            var1.playSound("AttackStomp");
         } else {
            var1.playSound("AttackShove");
         }
      }
   }

    void execute(IsoGameCharacter var1) {
      var1.StopAllActionQueue();
   }

    int DoSwingCollisionBoneCheck(IsoGameCharacter var1, HandWeapon var2, IsoGameCharacter var3, int var4, float var5) {
      movingStatic.clear();
    float var8 = var2.WeaponLength;
      var8 += 0.5F;
      if (var1.isAimAtFloor() && ((IsoLivingCharacter)var1).bDoShove) {
         var8 = 0.3F;
      }

      Model.BoneToWorldCoords(var3, var4, tempVectorBonePos);

      for (int var9 = 1; var9 <= 10; var9++) {
    float var10 = var9 / 10.0F;
         tempVector3_1.x = var1.x;
         tempVector3_1.y = var1.y;
         tempVector3_1.z = var1.z;
         tempVector3_1.x = tempVector3_1.x + var1.getForwardDirection().x * var8 * var10;
         tempVector3_1.y = tempVector3_1.y + var1.getForwardDirection().y * var8 * var10;
         tempVector3_1.x = tempVectorBonePos.x - tempVector3_1.x;
         tempVector3_1.y = tempVectorBonePos.y - tempVector3_1.y;
         tempVector3_1.z = 0.0F;
    bool var11 = tempVector3_1.getLength() < var5;
         if (var11) {
    return var4;
         }
      }

      return -1;
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
      if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing") || var2.m_EventName.equalsIgnoreCase("NonLoopedAnimFadeOut")) {
    bool var4 = var3.get(PARAM_LOWER_CONDITION) == bool.TRUE;
         if (var4 && !var1.isRangedWeaponEmpty()) {
            var3.put(PARAM_LOWER_CONDITION, bool.FALSE);
    HandWeapon var5 = GetWeapon(var1);
    int var6 = var5.getConditionLowerChance();
            if (dynamic_cast<IsoPlayer*>(var1) != nullptr && "charge" == ((IsoPlayer)var1).getAttackType())) {
               var6 = (int)(var6 / 1.5);
            }

            if (Rand.Next(var6 + var1.getMaintenanceMod() * 2) == 0) {
               WeaponLowerCondition(var5, var1);
            } else if (Rand.NextBool(2) && !var5.isRanged() && WeaponType.getWeaponType(var1) != WeaponType.barehand) {
               if (var5.isTwoHandWeapon() && (var1.getPrimaryHandItem() != var5 || var1.getSecondaryHandItem() != var5) && Rand.NextBool(3)) {
                  return;
               }

               var1.getXp().AddXP(Perks.Maintenance, 1.0F);
            }
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("AttackAnim")) {
         var1.setAttackAnim(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("BlockTurn")) {
         var1.setIgnoreMovement(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("ShoveAnim")) {
         var1.setVariable("ShoveAnim", bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("StompAnim")) {
         var1.setVariable("StompAnim", bool.parseBoolean(var2.m_ParameterValue));
      }

    HandWeapon var7 = GetWeapon(var1);
      if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck")
         && var3.get(PARAM_ATTACKED) == bool.FALSE
         && dynamic_cast<IsoPlayer*>(var1) != nullptr
         && ((IsoPlayer)var1).isLocalPlayer()) {
         this.ConnectSwing(var1, var7);
      }

      if (var2.m_EventName.equalsIgnoreCase("BlockMovement") && SandboxOptions.instance.AttackBlockMovements.getValue()) {
         var1.setVariable("SlowingMovement", bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("WeaponEmptyCheck") && var1.getClickSound() != nullptr) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
            return;
         }

         var1.playSound(var1.getClickSound());
         var1.setRecoilDelay(10.0F);
      }

      if (var2.m_EventName.equalsIgnoreCase("ShotDone") && var7 != nullptr && var7.isRackAfterShoot()) {
         var1.setVariable("ShotDone", true);
      }

      if (var2.m_EventName.equalsIgnoreCase("SetVariable") && var2.m_ParameterValue.startsWith("ShotDone=")) {
         var1.setVariable("ShotDone", var1.getVariableBoolean("ShotDone") && var7 != nullptr && var7.isRackAfterShoot());
      }

      if (var2.m_EventName.equalsIgnoreCase("playRackSound")) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
            return;
         }

         var1.playSound(var7.getRackSound());
      }

      if (var2.m_EventName.equalsIgnoreCase("playClickSound")) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
            return;
         }

         var1.playSound(var7.getClickSound());
      }

      if (var2.m_EventName.equalsIgnoreCase("PlaySwingSound")) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
            return;
         }

         if (var7 == nullptr) {
            return;
         }

         if (var1.getVariableBoolean("PlayedSwingSound")) {
            return;
         }

         var1.setVariable("PlayedSwingSound", true);
         if (!StringUtils.isNullOrWhitespace(var2.m_ParameterValue)) {
    std::string var8 = var7.getSoundByID(var2.m_ParameterValue);
            if (var8 != nullptr) {
               var1.playSound(var8);
               return;
            }
         }

         var1.playSound(var7.getSwingSound());
      }

      if (var2.m_EventName.equalsIgnoreCase("SetMeleeDelay")) {
         var1.setMeleeDelay(PZMath.tryParseFloat(var2.m_ParameterValue, 0.0F));
      }

      if (var2.m_EventName.equalsIgnoreCase("SitGroundStarted")) {
         var1.setVariable("SitGroundAnim", "Idle");
      }
   }

    void exit(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var1.setSprinting(false);
      ((IsoPlayer)var1).setForceSprint(false);
      var1.setIgnoreMovement(false);
      var1.setVariable("ShoveAnim", false);
      var1.setVariable("StompAnim", false);
      var1.setAttackAnim(false);
      var1.setVariable("AimFloorAnim", false);
      ((IsoPlayer)var1).setBlockMovement(false);
      if (var1.isAimAtFloor() && ((IsoLivingCharacter)var1).bDoShove) {
    Clothing var3 = (Clothing)var1.getWornItem("Shoes");
    int var4 = 10;
         if (var3 == nullptr) {
            var4 = 3;
         } else {
            var4 += var3.getConditionLowerChance() / 2;
            if (Rand.Next(var3.getConditionLowerChance()) == 0) {
               var3.setCondition(var3.getCondition() - 1);
            }
         }

         if (Rand.Next(var4) == 0) {
            if (var3 == nullptr) {
               var1.getBodyDamage().getBodyPart(BodyPartType.Foot_R).AddDamage(Rand.Next(5, 10));
               var1.getBodyDamage()
                  .getBodyPart(BodyPartType.Foot_R)
                  .setAdditionalPain(var1.getBodyDamage().getBodyPart(BodyPartType.Foot_R).getAdditionalPain() + Rand.Next(5, 10));
            } else {
               var1.getBodyDamage().getBodyPart(BodyPartType.Foot_R).AddDamage(Rand.Next(1, 5));
               var1.getBodyDamage()
                  .getBodyPart(BodyPartType.Foot_R)
                  .setAdditionalPain(var1.getBodyDamage().getBodyPart(BodyPartType.Foot_R).getAdditionalPain() + Rand.Next(1, 5));
            }
         }
      }

    HandWeapon var5 = GetWeapon(var1);
      var1.clearVariable("ZombieHitReaction");
      ((IsoPlayer)var1).attackStarted = false;
      ((IsoPlayer)var1).setAttackType(nullptr);
      ((IsoLivingCharacter)var1).setDoShove(false);
      var1.clearVariable("RackWeapon");
      var1.clearVariable("bShoveAiming");
      var1.clearVariable("PlayedSwingSound");
    bool var7 = var2.get(PARAM_ATTACKED) == bool.TRUE;
      if (var5 != nullptr && (var5.getCondition() <= 0 || var7 && var5.isUseSelf())) {
         var1.removeFromHands(var5);
         if (DebugOptions.instance.MultiplayerAutoEquip.getValue() && var5.getPhysicsObject() != nullptr) {
            var1.setPrimaryHandItem(var1.getInventory().getItemFromType(var5.getType()));
         }

         var1.getInventory().setDrawDirty(true);
      }

      if (var1.isRangedWeaponEmpty()) {
         var1.setRecoilDelay(10.0F);
      }

      var1.setRangedWeaponEmpty(false);
      var1.setForceShove(false);
      var1.setClickSound(nullptr);
      if (var7) {
         LuaEventManager.triggerEvent("OnPlayerAttackFinished", var1, var5);
      }

      var1.hitList.clear();
      var1.attackVars.clear();
   }

    void CalcAttackVars(IsoLivingCharacter var1, AttackVars var2) {
    HandWeapon var3 = (HandWeapon)Type.tryCastTo(var1.getPrimaryHandItem(), HandWeapon.class);
      if (var3 != nullptr && var3.getOtherHandRequire() != nullptr) {
    InventoryItem var4 = var1.getSecondaryHandItem();
         if (var4 == nullptr || !var4.getType() == var3.getOtherHandRequire())) {
            var3 = nullptr;
         }
      }

      if (!GameClient.bClient || var1.isLocal()) {
    bool var13 = var1.isAttackAnim() || var1.getVariableBoolean("ShoveAnim") || var1.getVariableBoolean("StompAnim");
         var2.setWeapon(var3 == nullptr ? var1.bareHands : var3);
         var2.targetOnGround.setMovingObject(nullptr);
         var2.bAimAtFloor = false;
         var2.bCloseKill = false;
         var2.bDoShove = var1.bDoShove;
         if (!var13) {
            var1.setVariable("ShoveAimX", 0.5F);
            var1.setVariable("ShoveAimY", 1.0F);
            if (var2.bDoShove && var1.getVariableBoolean("isMoving")) {
               var1.setVariable("ShoveAim", true);
            } else {
               var1.setVariable("ShoveAim", false);
            }
         }

         var2.useChargeDelta = var1.useChargeDelta;
         var2.recoilDelay = 0;
         if (var2.getWeapon(var1) == var1.bareHands || var2.bDoShove || var1.isForceShove()) {
            var2.bDoShove = true;
            var2.bAimAtFloor = false;
            var2.setWeapon(var1.bareHands);
         }

         this.calcValidTargets(var1, var2.getWeapon(var1), true, var2.targetsProne, var2.targetsStanding);
    HitInfo var5 = var2.targetsStanding.empty() ? nullptr : (HitInfo)var2.targetsStanding.get(0);
    HitInfo var6 = var2.targetsProne.empty() ? nullptr : (HitInfo)var2.targetsProne.get(0);
         if (this.isProneTargetBetter(var1, var5, var6)) {
            var5 = nullptr;
         }

         if (!var13) {
            var1.setAimAtFloor(false);
         }

    float var7 = float.MAX_VALUE;
         if (var5 != nullptr) {
            if (!var13) {
               var1.setAimAtFloor(false);
            }

            var2.bAimAtFloor = false;
            var2.targetOnGround.setMovingObject(nullptr);
            var7 = var5.distSq;
         } else if (var6 != nullptr && (Core.OptionAutoProneAtk || var1.bDoShove)) {
            if (!var13) {
               var1.setAimAtFloor(true);
            }

            var2.bAimAtFloor = true;
            var2.targetOnGround.setMovingObject(var6.getObject());
         }

         if (!(var7 >= var2.getWeapon(var1).getMinRange() * var2.getWeapon(var1).getMinRange())
            && (var5 == nullptr || !this.isWindowBetween(var1, var5.getObject()))) {
            if (var1.getStats().NumChasingZombies <= 1 && WeaponType.getWeaponType(var1) == WeaponType.knife) {
               var2.bCloseKill = true;
               return;
            }

            var2.bDoShove = true;
    IsoPlayer var8 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
            if (var8 != nullptr && !var8.isAuthorizeShoveStomp()) {
               var2.bDoShove = false;
            }

            var2.bAimAtFloor = false;
            if (var1.bareHands.getSwingAnim() != nullptr) {
               var2.useChargeDelta = 3.0F;
            }
         }

    int var14 = Core.getInstance().getKey("ManualFloorAtk");
    int var9 = Core.getInstance().getKey("Sprint");
    bool var10 = var1.getVariableBoolean("StartedAttackWhileSprinting");
         if (Keyboard.isKeyDown(var14) && (var14 != var9 || !var10)) {
            var2.bAimAtFloor = true;
            var2.bDoShove = false;
            var1.setDoShove(false);
         }

         if (var2.getWeapon(var1).isRanged()) {
    int var11 = var2.getWeapon(var1).getRecoilDelay();
    float var12 = var11 * (1.0F - var1.getPerkLevel(Perks.Aiming) / 30.0F);
            var2.recoilDelay = var12.intValue();
            var1.setVariable("singleShootSpeed", (0.8F + var1.getPerkLevel(Perks.Aiming) / 10.0F) * GameTime.getAnimSpeedFix());
         }
      }
   }

    void calcValidTargets(IsoLivingCharacter var1, HandWeapon var2, bool var3, std::vector<HitInfo> var4, std::vector<HitInfo> var5) {
      this.hitInfoPool.release(var4);
      this.hitInfoPool.release(var5);
      var4.clear();
      var5.clear();
    float var6 = Core.getInstance().getIgnoreProneZombieRange();
    float var7 = var2.getMaxRange() * var2.getRangeMod(var1);
    float var8 = Math.max(var6, var7 + (var3 ? 1.0F : 0.0F));
    std::vector var9 = IsoWorld.instance.CurrentCell.getObjectList();

      for (int var10 = 0; var10 < var9.size(); var10++) {
    IsoMovingObject var11 = (IsoMovingObject)var9.get(var10);
    HitInfo var12 = this.calcValidTarget(var1, var2, var11, var8);
         if (var12 != nullptr) {
            if (isStanding(var11)) {
               var5.push_back(var12);
            } else {
               var4.push_back(var12);
            }
         }
      }

      if (!var4.empty() && this.shouldIgnoreProneZombies(var1, var5, var6)) {
         this.hitInfoPool.release(var4);
         var4.clear();
      }

    float var13 = var2.getMinAngle();
    float var16 = var2.getMaxAngle();
      if (var2.isRanged()) {
         var13 -= var2.getAimingPerkMinAngleModifier() * (var1.getPerkLevel(Perks.Aiming) / 2.0F);
      }

      this.removeUnhittableTargets(var1, var2, var13, var16, var3, var5);
      var13 = var2.getMinAngle();
      var13 = (float)(var13 / 1.5);
      this.removeUnhittableTargets(var1, var2, var13, var16, var3, var4);
      var5.sort(Comparator);
      var4.sort(Comparator);
   }

    bool shouldIgnoreProneZombies(IsoGameCharacter var1, std::vector<HitInfo> var2, float var3) {
      if (var3 <= 0.0F) {
    return false;
      } else {
    bool var4 = var1.isInvisible() || dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isGhostMode();

         for (int var5 = 0; var5 < var2.size(); var5++) {
    HitInfo var6 = (HitInfo)var2.get(var5);
    IsoZombie var7 = (IsoZombie)Type.tryCastTo(var6.getObject(), IsoZombie.class);
            if ((var7 == nullptr || var7.target != nullptr || var4) && !(var6.distSq > var3 * var3)) {
    int var10005 = (int)var1.z;
    bool var8 = PolygonalMap2.instance.lineClearCollide(var1.x, var1.y, var6.getObject().x, var6.getObject().y, var10005, var1, false, true);
               if (!var8) {
    return true;
               }
            }
         }

    return false;
      }
   }

    bool isUnhittableTarget(IsoGameCharacter var1, HandWeapon var2, float var3, float var4, HitInfo var5, bool var6) {
      if (!(var5.dot < var3) && !(var5.dot > var4)) {
    Vector3 var7 = tempVectorBonePos.set(var5.x, var5.y, var5.z);
         return !var1.IsAttackRange(var2, var5.getObject(), var7, var6);
      } else {
    return true;
      }
   }

    void removeUnhittableTargets(IsoGameCharacter var1, HandWeapon var2, float var3, float var4, bool var5, std::vector<HitInfo> var6) {
      for (int var7 = var6.size() - 1; var7 >= 0; var7--) {
    HitInfo var8 = (HitInfo)var6.get(var7);
         if (this.isUnhittableTarget(var1, var2, var3, var4, var8, var5)) {
            this.hitInfoPool.release(var8);
            var6.remove(var7);
         }
      }
   }

    bool getNearestTargetPosAndDot(IsoGameCharacter var1, HandWeapon var2, IsoMovingObject var3, bool var4, Vector4f var5) {
      this.getNearestTargetPosAndDot(var1, var3, var5);
    float var6 = var5.w;
    float var7 = var2.getMinAngle();
    float var8 = var2.getMaxAngle();
    IsoGameCharacter var9 = (IsoGameCharacter)Type.tryCastTo(var3, IsoGameCharacter.class);
      if (var9 != nullptr) {
         if (isStanding(var3)) {
            if (var2.isRanged()) {
               var7 -= var2.getAimingPerkMinAngleModifier() * (var1.getPerkLevel(Perks.Aiming) / 2.0F);
            }
         } else {
            var7 /= 1.5F;
         }
      }

      if (!(var6 < var7) && !(var6 > var8)) {
    Vector3 var10 = tempVectorBonePos.set(var5.x, var5.y, var5.z);
         return var1.IsAttackRange(var2, var3, var10, var4);
      } else {
    return false;
      }
   }

    void getNearestTargetPosAndDot(IsoGameCharacter var1, Vector3 var2, Vector2 var3, Vector4f var4) {
    float var5 = var1.getDotWithForwardDirection(var2);
      var5 = PZMath.clamp(var5, -1.0F, 1.0F);
      var4.w = Math.max(var5, var4.w);
    float var6 = IsoUtils.DistanceToSquared(var1.x, var1.y, (int)var1.z * 3, var2.x, var2.y, (int)Math.max(var2.z, 0.0F) * 3);
      if (var6 < var3.x) {
         var3.x = var6;
         var4.set(var2.x, var2.y, var2.z, var4.w);
      }
   }

    void getNearestTargetPosAndDot(IsoGameCharacter var1, IsoMovingObject var2, const std::string& var3, Vector2 var4, Vector4f var5) {
    Vector3 var6 = getBoneWorldPos(var2, var3, tempVectorBonePos);
      this.getNearestTargetPosAndDot(var1, var6, var4, var5);
   }

    void getNearestTargetPosAndDot(IsoGameCharacter var1, IsoMovingObject var2, Vector4f var3) {
    Vector2 var4 = tempVector2_1.set(float.MAX_VALUE, float.NaN);
      var3.w = float.NEGATIVE_INFINITY;
    IsoGameCharacter var5 = (IsoGameCharacter)Type.tryCastTo(var2, IsoGameCharacter.class);
      if (var5 == nullptr) {
         this.getNearestTargetPosAndDot(var1, var2, (std::string)nullptr, var4, var3);
      } else {
         getBoneWorldPos(var2, "Bip01_Head", tempVector3_1);
         getBoneWorldPos(var2, "Bip01_HeadNub", tempVector3_2);
         tempVector3_1.addToThis(tempVector3_2);
         tempVector3_1.div(2.0F);
    Vector3 var6 = tempVector3_1;
         if (isStanding(var2)) {
            this.getNearestTargetPosAndDot(var1, var6, var4, var3);
            this.getNearestTargetPosAndDot(var1, var2, "Bip01_Pelvis", var4, var3);
    Vector3 var7 = tempVectorBonePos.set(var2.getX(), var2.getY(), var2.getZ());
            this.getNearestTargetPosAndDot(var1, var7, var4, var3);
         } else {
            this.getNearestTargetPosAndDot(var1, var6, var4, var3);
            this.getNearestTargetPosAndDot(var1, var2, "Bip01_Pelvis", var4, var3);
            this.getNearestTargetPosAndDot(var1, var2, "Bip01_DressFrontNub", var4, var3);
         }
      }
   }

    HitInfo calcValidTarget(IsoLivingCharacter var1, HandWeapon var2, IsoMovingObject var3, float var4) {
      if (var3 == var1) {
    return nullptr;
      } else {
    IsoGameCharacter var5 = (IsoGameCharacter)Type.tryCastTo(var3, IsoGameCharacter.class);
         if (var5 == nullptr) {
    return nullptr;
         } else if (var5.isGodMod()) {
    return nullptr;
         } else if (!checkPVP(var1, var3)) {
    return nullptr;
         } else {
    float var6 = Math.abs(var5.getZ() - var1.getZ());
            if (!var2.isRanged() && var6 >= 0.5F) {
    return nullptr;
            } else if (var6 > 3.3F) {
    return nullptr;
            } else if (!var5.isShootable()) {
    return nullptr;
            } else if (var5.isCurrentState(FakeDeadZombieState.instance())) {
    return nullptr;
            } else if (var5.isDead()) {
    return nullptr;
            } else if (var5.getHitReaction() != nullptr && var5.getHitReaction().contains("Death")) {
    return nullptr;
            } else {
    Vector4f var7 = this.tempVector4f;
               this.getNearestTargetPosAndDot(var1, var5, var7);
    float var8 = var7.w;
    float var9 = IsoUtils.DistanceToSquared(var1.x, var1.y, (int)var1.z * 3, var7.x, var7.y, (int)var7.z * 3);
               if (var8 < 0.0F) {
    return nullptr;
               } else if (var9 > var4 * var4) {
    return nullptr;
               } else {
                  TestResults var10 = LosUtil.lineClear(
                     var1.getCell(), (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), (int)var5.getX(), (int)var5.getY(), (int)var5.getZ(), false
                  );
                  return var10 != TestResults.Blocked && var10 != TestResults.ClearThroughClosedDoor
                     ? ((HitInfo)this.hitInfoPool.alloc()).init(var5, var8, var9, var7.x, var7.y, var7.z)
                     : nullptr;
               }
            }
         }
      }
   }

    static bool isProne(IsoMovingObject var0) {
    IsoZombie var1 = (IsoZombie)Type.tryCastTo(var0, IsoZombie.class);
      if (var1 == nullptr) {
         return var0.isOnFloor();
      } else if (var1.isOnFloor()) {
    return true;
      } else if (var1.isCurrentState(ZombieEatBodyState.instance())) {
    return true;
      } else if (var1.isDead()) {
    return true;
      } else {
         return var1.isSitAgainstWall() ? true : var1.isCrawling();
      }
   }

    static bool isStanding(IsoMovingObject var0) {
      return !isProne(var0);
   }

    bool isProneTargetBetter(IsoGameCharacter var1, HitInfo var2, HitInfo var3) {
      if (var2 == nullptr || var2.getObject() == nullptr) {
    return false;
      } else if (var3 == nullptr || var3.getObject() == nullptr) {
    return false;
      } else if (var2.distSq <= var3.distSq) {
    return false;
      } else {
    int var10005 = (int)var1.z;
    bool var4 = PolygonalMap2.instance.lineClearCollide(var1.x, var1.y, var2.getObject().x, var2.getObject().y, var10005, nullptr, false, true);
         if (!var4) {
    return false;
         } else {
            var10005 = (int)var1.z;
    bool var5 = PolygonalMap2.instance.lineClearCollide(var1.x, var1.y, var3.getObject().x, var3.getObject().y, var10005, nullptr, false, true);
            return !var5;
         }
      }
   }

    static bool checkPVP(IsoGameCharacter var0, IsoMovingObject var1) {
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var0, IsoPlayer.class);
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (GameClient.bClient && var3 != nullptr && var0 != nullptr) {
         if (var3.isGodMod()
            || !ServerOptions.instance.PVP.getValue()
            || ServerOptions.instance.SafetySystem.getValue() && var0.getSafety().isEnabled() && ((IsoGameCharacter)var1).getSafety().isEnabled()) {
    return false;
         }

         if (NonPvpZone.getNonPvpZone((int)var1.getX(), (int)var1.getY()) != nullptr) {
    return false;
         }

         if (var2 != nullptr && NonPvpZone.getNonPvpZone((int)var0.getX(), (int)var0.getY()) != nullptr) {
    return false;
         }

         if (var2 != nullptr && !var2.factionPvp && !var3.factionPvp) {
    Faction var4 = Faction.getPlayerFaction(var2);
    Faction var5 = Faction.getPlayerFaction(var3);
            if (var5 != nullptr && var4 == var5) {
    return false;
            }
         }
      }

      return GameClient.bClient || var3 == nullptr || IsoPlayer.getCoopPVP();
   }

    void CalcHitListShove(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
    HandWeapon var5 = var3.getWeapon((IsoLivingCharacter)var1);
    std::vector var6 = IsoWorld.instance.CurrentCell.getObjectList();

      for (int var7 = 0; var7 < var6.size(); var7++) {
    IsoMovingObject var8 = (IsoMovingObject)var6.get(var7);
         if (var8 != var1 && !(dynamic_cast<BaseVehicle*>(var8) != nullptr)) {
    IsoGameCharacter var9 = (IsoGameCharacter)Type.tryCastTo(var8, IsoGameCharacter.class);
            if (var9 != nullptr && !var9.isGodMod() && !var9.isDead()) {
    IsoZombie var10 = (IsoZombie)Type.tryCastTo(var8, IsoZombie.class);
               if ((var10 == nullptr || !var10.isCurrentState(FakeDeadZombieState.instance())) && checkPVP(var1, var8)) {
                  boolean var11 = var8 == var3.targetOnGround.getMovingObject()
                     || var8.isShootable() && isStanding(var8) && !var3.bAimAtFloor
                     || var8.isShootable() && isProne(var8) && var3.bAimAtFloor;
                  if (var11) {
    Vector4f var12 = this.tempVector4f;
                     if (this.getNearestTargetPosAndDot(var1, var5, var8, var2, var12)) {
    float var13 = var12.w;
    float var14 = IsoUtils.DistanceToSquared(var1.x, var1.y, (int)var1.z * 3, var12.x, var12.y, (int)var12.z * 3);
                        TestResults var15 = LosUtil.lineClear(
                           var1.getCell(), (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), (int)var8.getX(), (int)var8.getY(), (int)var8.getZ(), false
                        );
                        if (var15 != TestResults.Blocked
                           && var15 != TestResults.ClearThroughClosedDoor
                           && (
                              var8.getCurrentSquare() == nullptr
                                 || var1.getCurrentSquare() == nullptr
                                 || var8.getCurrentSquare() == var1.getCurrentSquare()
                                 || !var8.getCurrentSquare().isWindowBlockedTo(var1.getCurrentSquare())
                           )
                           && var8.getSquare().getTransparentWallTo(var1.getSquare()) == nullptr) {
    HitInfo var16 = ((HitInfo)this.hitInfoPool.alloc()).init(var8, var13, var14, var12.x, var12.y, var12.z);
                           if (var3.targetOnGround.getMovingObject() == var8) {
                              var4.clear();
                              var4.push_back(var16);
                              break;
                           }

                           var4.push_back(var16);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void CalcHitListWeapon(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
    HandWeapon var5 = var3.getWeapon((IsoLivingCharacter)var1);
    std::vector var6 = IsoWorld.instance.CurrentCell.getObjectList();

      for (int var7 = 0; var7 < var6.size(); var7++) {
    IsoMovingObject var8 = (IsoMovingObject)var6.get(var7);
         if (var8 != var1) {
    IsoGameCharacter var9 = (IsoGameCharacter)Type.tryCastTo(var8, IsoGameCharacter.class);
            if ((var9 == nullptr || !var9.isGodMod()) && (var9 == nullptr || !var9.isDead())) {
    IsoZombie var10 = (IsoZombie)Type.tryCastTo(var8, IsoZombie.class);
               if ((var10 == nullptr || !var10.isCurrentState(FakeDeadZombieState.instance())) && checkPVP(var1, var8)) {
                  boolean var11 = var8 == var3.targetOnGround.getMovingObject()
                     || var8.isShootable() && isStanding(var8) && !var3.bAimAtFloor
                     || var8.isShootable() && isProne(var8) && var3.bAimAtFloor;
                  if (var11) {
    Vector4f var12 = this.tempVector4f;
                     if (dynamic_cast<BaseVehicle*>(var8) != nullptr) {
    VehiclePart var13 = ((BaseVehicle)var8).getNearestBodyworkPart(var1);
                        if (var13 == nullptr) {
                           continue;
                        }

    float var14 = var1.getDotWithForwardDirection(var8.x, var8.y);
                        if (var14 < 0.8F) {
                           continue;
                        }

                        var12.set(var8.x, var8.y, var8.z, var14);
                     } else if (var9 == nullptr || !this.getNearestTargetPosAndDot(var1, var5, var8, var2, var12)) {
                        continue;
                     }

                     TestResults var18 = LosUtil.lineClear(
                        var1.getCell(), (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), (int)var8.getX(), (int)var8.getY(), (int)var8.getZ(), false
                     );
                     if (var18 != TestResults.Blocked && var18 != TestResults.ClearThroughClosedDoor) {
    float var19 = var12.w;
    float var15 = IsoUtils.DistanceToSquared(var1.x, var1.y, (int)var1.z * 3, var12.x, var12.y, (int)var12.z * 3);
                        if (var8.getSquare().getTransparentWallTo(var1.getSquare()) != nullptr && dynamic_cast<IsoPlayer*>(var1) != nullptr) {
                           if (WeaponType.getWeaponType(var1) == WeaponType.spear) {
                              ((IsoPlayer)var1).setAttackType("spearStab");
                           } else if (WeaponType.getWeaponType(var1) != WeaponType.knife) {
                              continue;
                           }
                        }

    IsoWindow var16 = this.getWindowBetween(var1, var8);
                        if (var16 == nullptr || !var16.isBarricaded()) {
    HitInfo var17 = ((HitInfo)this.hitInfoPool.alloc()).init(var8, var19, var15, var12.x, var12.y, var12.z);
                           var17.window.setObject(var16);
                           var4.push_back(var17);
                        }
                     }
                  }
               }
            }
         }
      }

      if (var4.empty()) {
         this.CalcHitListWindow(var1, var5, var4);
      }
   }

    void CalcHitListWindow(IsoGameCharacter var1, HandWeapon var2, std::vector<HitInfo> var3) {
    Vector2 var4 = var1.getLookVector(tempVector2_1);
      var4.setLength(var2.getMaxRange() * var2.getRangeMod(var1));
    HitInfo var5 = nullptr;
    std::vector var6 = IsoWorld.instance.CurrentCell.getWindowList();

      for (int var7 = 0; var7 < var6.size(); var7++) {
    IsoWindow var8 = (IsoWindow)var6.get(var7);
         if ((int)var8.getZ() == (int)var1.z && this.windowVisitor.isHittable(var8)) {
    float var9 = var8.getX();
    float var10 = var8.getY();
    float var11 = var9 + (var8.getNorth() ? 1.0F : 0.0F);
    float var12 = var10 + (var8.getNorth() ? 0.0F : 1.0F);
            if (Line2D.linesIntersect(var1.x, var1.y, var1.x + var4.x, var1.y + var4.y, var9, var10, var11, var12)) {
    IsoGridSquare var13 = var8.getAddSheetSquare(var1);
               if (var13 != nullptr && !LosUtil.lineClearCollide((int)var1.x, (int)var1.y, (int)var1.z, var13.x, var13.y, var13.z, false)) {
    float var14 = IsoUtils.DistanceToSquared(var1.x, var1.y, var9 + (var11 - var9) / 2.0F, var10 + (var12 - var10) / 2.0F);
                  if (var5 == nullptr || !(var5.distSq < var14)) {
    float var15 = 1.0F;
                     if (var5 == nullptr) {
                        var5 = (HitInfo)this.hitInfoPool.alloc();
                     }

                     var5.init(var8, var15, var14);
                  }
               }
            }
         }
      }

      if (var5 != nullptr) {
         var3.push_back(var5);
      }
   }

    void CalcHitList(IsoGameCharacter var1, bool var2, AttackVars var3, std::vector<HitInfo> var4) {
      if (!GameClient.bClient || var1.isLocal()) {
         this.hitInfoPool.release(var4);
         var4.clear();
    HandWeapon var5 = var3.getWeapon((IsoLivingCharacter)var1);
    int var6 = var5.getMaxHitCount();
         if (var3.bDoShove) {
            var6 = WeaponType.getWeaponType(var1) != WeaponType.barehand ? 3 : 1;
         }

         if (!var5.isRanged() && !SandboxOptions.instance.MultiHitZombies.getValue()) {
            var6 = 1;
         }

         if (var5 == ((IsoPlayer)var1).bareHands && !(var1.getPrimaryHandItem() instanceof HandWeapon)) {
            var6 = 1;
         }

         if (var5 == ((IsoPlayer)var1).bareHands && var3.targetOnGround.getMovingObject() != nullptr) {
            var6 = 1;
         }

         if (0 < var6) {
            if (var3.bDoShove) {
               this.CalcHitListShove(var1, var2, var3, var4);
            } else {
               this.CalcHitListWeapon(var1, var2, var3, var4);
            }

            if (var4.size() == 1 && ((HitInfo)var4.get(0)).getObject() == nullptr) {
               return;
            }

            this.filterTargetsByZ(var1);
            Collections.sort(var4, Comparator);
            if (var5.isPiercingBullets()) {
               HitList2.clear();
    double var7 = 0.0;

               for (int var9 = 0; var9 < var4.size(); var9++) {
    HitInfo var10 = (HitInfo)var4.get(var9);
    IsoMovingObject var11 = var10.getObject();
                  if (var11 != nullptr) {
    double var12 = var1.getX() - var11.getX();
    double var14 = -(var1.getY() - var11.getY());
    double var16 = Math.atan2(var14, var12);
                     if (var16 < 0.0) {
                        var16 = Math.abs(var16);
                     } else {
                        var16 = (Math.PI * 2) - var16;
                     }

                     if (var9 == 0) {
                        var7 = Math.toDegrees(var16);
                        HitList2.push_back(var10);
                     } else {
    double var18 = Math.toDegrees(var16);
                        if (Math.abs(var7 - var18) < 1.0) {
                           HitList2.push_back(var10);
                           break;
                        }
                     }
                  }
               }

               var4.removeAll(HitList2);
               this.hitInfoPool.release(var4);
               var4.clear();
               var4.addAll(HitList2);
            } else {
               while (var4.size() > var6) {
                  this.hitInfoPool.release((HitInfo)var4.remove(var4.size() - 1));
               }
            }
         }

         for (int var20 = 0; var20 < var4.size(); var20++) {
    HitInfo var8 = (HitInfo)var4.get(var20);
            var8.chance = this.CalcHitChance(var1, var5, var8);
         }
      }
   }

    void filterTargetsByZ(IsoGameCharacter var1) {
    float var2 = float.MAX_VALUE;
    HitInfo var3 = nullptr;

      for (int var4 = 0; var4 < var1.hitList.size(); var4++) {
    HitInfo var5 = (HitInfo)var1.hitList.get(var4);
    float var6 = Math.abs(var5.z - var1.getZ());
         if (var6 < var2) {
            var2 = var6;
            var3 = var5;
         }
      }

      if (var3 != nullptr) {
         for (int var7 = var1.hitList.size() - 1; var7 >= 0; var7--) {
    HitInfo var8 = (HitInfo)var1.hitList.get(var7);
            if (var8 != var3) {
    float var9 = Math.abs(var8.z - var3.z);
               if (var9 > 0.5F) {
                  this.hitInfoPool.release(var8);
                  var1.hitList.remove(var7);
               }
            }
         }
      }
   }

    int CalcHitChance(IsoGameCharacter var1, HandWeapon var2, HitInfo var3) {
    IsoMovingObject var4 = var3.getObject();
      if (var4 == nullptr) {
    return 0;
      } else {
         if (var1.getVehicle() != nullptr) {
    BaseVehicle var5 = var1.getVehicle();
    Vector3f var6 = var5.getForwardVector((Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc());
    Vector2 var7 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
            var7.x = var6.x;
            var7.y = var6.z;
            var7.normalize();
    int var8 = var5.getSeat(var1);
    Area var9 = var5.getScript().getAreaById(var5.getPassengerArea(var8));
    uint8_t var10 = -90;
            if (var9.x > 0.0F) {
               var10 = 90;
            }

            var7.rotate((float)Math.toRadians(var10));
            var7.normalize();
    Vector2 var11 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
            var11.x = var4.x;
            var11.y = var4.y;
            var11.x = var11.x - var1.x;
            var11.y = var11.y - var1.y;
            var11.normalize();
    float var12 = var11.dot(var7);
            if (var12 > -0.6) {
    return 0;
            }

            ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var7);
            ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var11);
            ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var6);
         }

         if (System.currentTimeMillis() - var1.lastAutomaticShoot > 600L) {
            var1.shootInARow = 0;
         }

    int var13 = var2.getHitChance();
         var13 = (int)(var13 + var2.getAimingPerkHitChanceModifier() * var1.getPerkLevel(Perks.Aiming));
         if (var13 > 95) {
            var13 = 95;
         }

         var13 -= var1.shootInARow * 2;
    float var18 = PZMath.sqrt(var3.distSq);
    float var19 = 1.3F;
         if (dynamic_cast<IsoPlayer*>(var4) != nullptr) {
            var18 = (float)(var18 * 1.5);
            var19 = 1.0F;
         }

         var13 = (int)(var13 + (var2.getMaxRange() * var2.getRangeMod(var1) - var18) * var19);
         if (var2.getMinRangeRanged() > 0.0F) {
            if (var18 < var2.getMinRangeRanged()) {
               var13 -= 50;
            }
         } else if (var18 < 1.7 && var2.isRanged() && !(dynamic_cast<IsoPlayer*>(var4) != nullptr)) {
            var13 += 35;
         }

         if (var2.isRanged() && var1.getBeenMovingFor() > var2.getAimingTime() + var1.getPerkLevel(Perks.Aiming)) {
            var13 = (int)(var13 - (var1.getBeenMovingFor() - (var2.getAimingTime() + var1.getPerkLevel(Perks.Aiming))));
         }

         if (var3.getObject() instanceof IsoPlayer) {
    IsoPlayer var20 = (IsoPlayer)var3.getObject();
            if (var20.isPlayerMoving()) {
               var13 -= 5;
            }

            if (var20.isRunning()) {
               var13 -= 10;
            }

            if (var20.isSprinting()) {
               var13 -= 15;
            }
         }

         if (var2.isRanged() && var1.getVehicle() != nullptr) {
            var13 = (int)(var13 - Math.abs(var1.getVehicle().getCurrentSpeedKmHour()) * 2.0F);
         }

         if (var1.Traits.Marksman.isSet()) {
            var13 += 20;
         }

    float var21 = 0.0F;

         for (int var22 = BodyPartType.ToIndex(BodyPartType.Hand_L); var22 <= BodyPartType.ToIndex(BodyPartType.UpperArm_R); var22++) {
            var21 += ((BodyPart)var1.getBodyDamage().getBodyParts().get(var22)).getPain();
         }

         if (var21 > 0.0F) {
            var13 = (int)(var13 - var21 / 10.0F);
         }

         var13 -= var1.getMoodles().getMoodleLevel(MoodleType.Tired) * 5;
         if (var13 <= 10) {
            var13 = 10;
         }

         if (var13 > 100 || !var2.isRanged()) {
            var13 = 100;
         }

    return var13;
      }
   }

    static Vector3 getBoneWorldPos(IsoMovingObject var0, const std::string& var1, Vector3 var2) {
    IsoGameCharacter var3 = (IsoGameCharacter)Type.tryCastTo(var0, IsoGameCharacter.class);
      if (var3 != nullptr && var1 != nullptr) {
    AnimationPlayer var4 = var3.getAnimationPlayer();
         if (var4 != nullptr && var4.isReady()) {
    int var5 = var4.getSkinningBoneIndex(var1, -1);
            if (var5 == -1) {
               return var2.set(var0.x, var0.y, var0.z);
            } else {
               Model.BoneToWorldCoords(var3, var5, var2);
    return var2;
            }
         } else {
            return var2.set(var0.x, var0.y, var0.z);
         }
      } else {
         return var2.set(var0.x, var0.y, var0.z);
      }
   }

    void ConnectSwing(IsoGameCharacter var1, HandWeapon var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoLivingCharacter var4 = (IsoLivingCharacter)var1;
    IsoPlayer var5 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var1.getVariableBoolean("ShoveAnim")) {
         var4.setDoShove(true);
      }

      if (GameServer.bServer) {
         DebugLog.log(DebugType.Network, "Player swing connects.");
      }

      LuaEventManager.triggerEvent("OnWeaponSwingHitPoint", var1, var2);
      if (var2.getPhysicsObject() != nullptr) {
         var1.Throw(var2);
      }

      if (var2.isUseSelf()) {
         var2.Use();
      }

      if (var2.isOtherHandUse() && var1.getSecondaryHandItem() != nullptr) {
         var1.getSecondaryHandItem().Use();
      }

    bool var6 = false;
      if (var4.bDoShove && !var1.isAimAtFloor()) {
         var6 = true;
      }

    bool var7 = false;
    bool var8 = false;
      var1.attackVars.setWeapon(var2);
      var1.attackVars.targetOnGround.setMovingObject(var4.targetOnGround);
      var1.attackVars.bAimAtFloor = var1.isAimAtFloor();
      var1.attackVars.bDoShove = var4.bDoShove;
      if (var1.getVariableBoolean("ShoveAnim")) {
         var1.attackVars.bDoShove = true;
      }

      this.CalcHitList(var1, false, var1.attackVars, var1.hitList);
    int var9 = var1.hitList.size();
    bool var10 = false;
      if (var9 == 0) {
         var10 = this.CheckObjectHit(var1, var2);
      }

      if (var2.isUseEndurance()) {
    float var11 = 0.0F;
         if (var2.isTwoHandWeapon() && (var1.getPrimaryHandItem() != var2 || var1.getSecondaryHandItem() != var2)) {
            var11 = var2.getWeight() / 1.5F / 10.0F;
         }

         if (var9 <= 0 && !var1.isForceShove()) {
    float var12 = (var2.getWeight() * 0.18F * var2.getFatigueMod(var1) * var1.getFatigueMod() * var2.getEnduranceMod() * 0.3F + var11) * 0.04F;
    float var13 = 1.0F;
            if (var1.Traits.Asthmatic.isSet()) {
               var13 = 1.3F;
            }

            var1.getStats().endurance -= var12 * var13;
         }
      }

      var1.setLastHitCount(var1.hitList.size());
      if (!var2.isMultipleHitConditionAffected()) {
         var7 = true;
      }

    int var45 = 1;
      this.dotList.clear();
      if (var1.hitList.empty() && var1.getClickSound() != nullptr && !var4.bDoShove) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer() || !(dynamic_cast<IsoPlayer*>(var1) != nullptr)) {
            var1.getEmitter().playSound(var1.getClickSound());
         }

         var1.setRecoilDelay(10.0F);
      }

    bool var46 = false;

      for (int var47 = 0; var47 < var1.hitList.size(); var47++) {
    uint8_t var14 = 0;
    bool var15 = false;
    HitInfo var16 = (HitInfo)var1.hitList.get(var47);
    IsoMovingObject var17 = var16.getObject();
    BaseVehicle var18 = (BaseVehicle)Type.tryCastTo(var17, BaseVehicle.class);
    IsoZombie var19 = (IsoZombie)Type.tryCastTo(var17, IsoZombie.class);
         if (var16.getObject() == nullptr && var16.window.getObject() != nullptr) {
            var16.window.getObject().WeaponHit(var1, var2);
         } else {
            this.smashWindowBetween(var1, var17, var2);
            if (!this.isWindowBetween(var1, var17)) {
    int var20 = var16.chance;
    bool var21 = Rand.Next(100) <= var20;
               if (var21) {
    Vector2 var22 = tempVector2_1.set(var1.getX(), var1.getY());
    Vector2 var23 = tempVector2_2.set(var17.getX(), var17.getY());
                  var23.x = var23.x - var22.x;
                  var23.y = var23.y - var22.y;
    Vector2 var24 = var1.getLookVector(tempVector2_1);
                  var24.tangent();
                  var23.normalize();
    bool var25 = true;
    float var26 = var24.dot(var23);

                  for (int var27 = 0; var27 < this.dotList.size(); var27++) {
    float var28 = this.dotList.get(var27);
                     if (Math.abs(var26 - var28) < 1.0E-4) {
                        var25 = false;
                     }
                  }

    float var50 = var2.getMinDamage();
    float var51 = var2.getMaxDamage();
    long var29 = 0L;
                  if (!var25) {
                     var50 /= 5.0F;
                     var51 /= 5.0F;
                  }

                  if (var1.isAimAtFloor() && !var2.isRanged() && var1.isNPC()) {
                     splash(var17, var2, var1);
                     var14 = (byte)Rand.Next(2);
                  } else if (var1.isAimAtFloor() && !var2.isRanged()) {
                     if (var5 == nullptr || var5.isLocalPlayer()) {
                        if (!StringUtils.isNullOrEmpty(var2.getHitFloorSound())) {
                           var1.getEmitter().stopSoundByName(var2.getSwingSound());
                           if (var5 != nullptr) {
                              var5.setMeleeHitSurface(Material.Body);
                           }

                           var29 = var1.playSound(var2.getHitFloorSound());
                        } else {
                           var1.getEmitter().stopSoundByName(var2.getSwingSound());
                           if (var5 != nullptr) {
                              var5.setMeleeHitSurface(Material.Body);
                           }

                           var29 = var1.playSound(var2.getZombieHitSound());
                        }
                     }

                     int var31 = this.DoSwingCollisionBoneCheck(
                        var1,
                        GetWeapon(var1),
                        (IsoGameCharacter)var17,
                        ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_Head", -1),
                        0.28F
                     );
                     if (var31 == -1) {
                        var31 = this.DoSwingCollisionBoneCheck(
                           var1,
                           GetWeapon(var1),
                           (IsoGameCharacter)var17,
                           ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_Spine", -1),
                           0.28F
                        );
                        if (var31 == -1) {
                           var31 = this.DoSwingCollisionBoneCheck(
                              var1,
                              GetWeapon(var1),
                              (IsoGameCharacter)var17,
                              ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_L_Calf", -1),
                              0.13F
                           );
                           if (var31 == -1) {
                              var31 = this.DoSwingCollisionBoneCheck(
                                 var1,
                                 GetWeapon(var1),
                                 (IsoGameCharacter)var17,
                                 ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Calf", -1),
                                 0.13F
                              );
                           }

                           if (var31 == -1) {
                              var31 = this.DoSwingCollisionBoneCheck(
                                 var1,
                                 GetWeapon(var1),
                                 (IsoGameCharacter)var17,
                                 ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_L_Foot", -1),
                                 0.23F
                              );
                           }

                           if (var31 == -1) {
                              var31 = this.DoSwingCollisionBoneCheck(
                                 var1,
                                 GetWeapon(var1),
                                 (IsoGameCharacter)var17,
                                 ((IsoGameCharacter)var17).getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Foot", -1),
                                 0.23F
                              );
                           }

                           if (var31 == -1) {
                              continue;
                           }

                           var15 = true;
                        }
                     } else {
                        splash(var17, var2, var1);
                        splash(var17, var2, var1);
                        var14 = (byte)(Rand.Next(0, 3) + 1);
                     }
                  }

                  if (!var1.attackVars.bAimAtFloor
                     && (!var1.attackVars.bCloseKill || !var1.isCriticalHit())
                     && !var4.bDoShove
                     && dynamic_cast<IsoGameCharacter*>(var17) != nullptr
                     && (var5 == nullptr || var5.isLocalPlayer())) {
                     if (var5 != nullptr) {
                        var5.setMeleeHitSurface(Material.Body);
                     }

                     if (var2.isRanged()) {
                        var29 = ((IsoGameCharacter)var17).playSound(var2.getZombieHitSound());
                     } else {
                        var1.getEmitter().stopSoundByName(var2.getSwingSound());
                        var29 = var1.playSound(var2.getZombieHitSound());
                     }
                  }

                  if (var2.isRanged() && var19 != nullptr) {
    Vector2 var54 = tempVector2_1.set(var1.getX(), var1.getY());
    Vector2 var32 = tempVector2_2.set(var17.getX(), var17.getY());
                     var32.x = var32.x - var54.x;
                     var32.y = var32.y - var54.y;
    Vector2 var33 = var19.getForwardDirection();
                     var32.normalize();
                     var33.normalize();
    float var34 = var32.dot(var33);
                     var19.setHitFromBehind(var34 > 0.5);
                  }

                  if (this.dotList.empty()) {
                     this.dotList.push_back(var26);
                  }

                  if (var19 != nullptr && var19.isCurrentState(ZombieOnGroundState.instance())) {
                     var19.setReanimateTimer(var19.getReanimateTimer() + Rand.Next(10));
                  }

                  if (var19 != nullptr && var19.isCurrentState(ZombieGetUpState.instance())) {
                     var19.setReanimateTimer(Rand.Next(60) + 30);
                  }

    bool var55 = false;
                  if (!var2.isTwoHandWeapon() || var1.isItemInBothHands(var2)) {
                     var55 = true;
                  }

    float var57 = var51 - var50;
    float var56;
                  if (var57 == 0.0F) {
                     var56 = var50 + 0.0F;
                  } else {
                     var56 = var50 + Rand.Next((int)(var57 * 1000.0F)) / 1000.0F;
                  }

                  if (!var2.isRanged()) {
                     var56 *= var2.getDamageMod(var1) * var1.getHittingMod();
                  }

                  if (!var55 && !var2.isRanged() && var51 > var50) {
                     var56 -= var50;
                  }

                  if (var1.isAimAtFloor() && var4.bDoShove) {
    float var59 = 0.0F;

                     for (int var62 = BodyPartType.ToIndex(BodyPartType.UpperLeg_L); var62 <= BodyPartType.ToIndex(BodyPartType.Foot_R); var62++) {
                        var59 += ((BodyPart)var1.getBodyDamage().getBodyParts().get(var62)).getPain();
                     }

                     if (var59 > 10.0F) {
                        var56 /= PZMath.clamp(var59 / 10.0F, 1.0F, 30.0F);
                        MoodlesUI.getInstance().wiggle(MoodleType.Pain);
                        MoodlesUI.getInstance().wiggle(MoodleType.Injured);
                     }
                  } else {
    float var58 = 0.0F;

                     for (int var35 = BodyPartType.ToIndex(BodyPartType.Hand_L); var35 <= BodyPartType.ToIndex(BodyPartType.UpperArm_R); var35++) {
                        var58 += ((BodyPart)var1.getBodyDamage().getBodyParts().get(var35)).getPain();
                     }

                     if (var58 > 10.0F) {
                        var56 /= PZMath.clamp(var58 / 10.0F, 1.0F, 30.0F);
                        MoodlesUI.getInstance().wiggle(MoodleType.Pain);
                        MoodlesUI.getInstance().wiggle(MoodleType.Injured);
                     }
                  }

                  if (var1.Traits.Underweight.isSet()) {
                     var56 *= 0.8F;
                  }

                  if (var1.Traits.VeryUnderweight.isSet()) {
                     var56 *= 0.6F;
                  }

                  if (var1.Traits.Emaciated.isSet()) {
                     var56 *= 0.4F;
                  }

    float var60 = var56 / (var45 / 2.0F);
                  if (var1.isAttackWasSuperAttack()) {
                     var60 *= 5.0F;
                  }

                  var45++;
                  if (var2.isMultipleHitConditionAffected()) {
                     var7 = true;
                  }

    Vector2 var63 = tempVector2_1.set(var1.getX(), var1.getY());
    Vector2 var36 = tempVector2_2.set(var17.getX(), var17.getY());
                  var36.x = var36.x - var63.x;
                  var36.y = var36.y - var63.y;
    float var37 = var36.getLength();
    float var38 = 1.0F;
                  if (var2.isRangeFalloff()) {
                     var38 = 1.0F;
                  } else if (var2.isRanged()) {
                     var38 = 0.5F;
                  } else {
                     var38 = var37 / var2.getMaxRange(var1);
                  }

                  var38 *= 2.0F;
                  if (var38 < 0.3F) {
                     var38 = 1.0F;
                  }

                  if (var2.isRanged() && var1.getPerkLevel(Perks.Aiming) < 6 && var1.getMoodles().getMoodleLevel(MoodleType.Panic) > 2) {
                     var60 -= var1.getMoodles().getMoodleLevel(MoodleType.Panic) * 0.2F;
                     MoodlesUI.getInstance().wiggle(MoodleType.Panic);
                  }

                  if (!var2.isRanged() && var1.getMoodles().getMoodleLevel(MoodleType.Panic) > 1) {
                     var60 -= var1.getMoodles().getMoodleLevel(MoodleType.Panic) * 0.1F;
                     MoodlesUI.getInstance().wiggle(MoodleType.Panic);
                  }

                  if (var1.getMoodles().getMoodleLevel(MoodleType.Stress) > 1) {
                     var60 -= var1.getMoodles().getMoodleLevel(MoodleType.Stress) * 0.1F;
                     MoodlesUI.getInstance().wiggle(MoodleType.Stress);
                  }

                  if (var60 < 0.0F) {
                     var60 = 0.1F;
                  }

                  if (var1.isAimAtFloor() && var4.bDoShove) {
                     var60 = Rand.Next(0.7F, 1.0F) + var1.getPerkLevel(Perks.Strength) * 0.2F;
    Clothing var39 = (Clothing)var1.getWornItem("Shoes");
                     if (var39 == nullptr) {
                        var60 *= 0.5F;
                     } else {
                        var60 *= var39.getStompPower();
                     }
                  }

                  if (!var2.isRanged()) {
                     switch (var1.getMoodles().getMoodleLevel(MoodleType.Endurance)) {
                        case 0:
                        default:
                           break;
                        case 1:
                           var60 *= 0.5F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
                           break;
                        case 2:
                           var60 *= 0.2F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
                           break;
                        case 3:
                           var60 *= 0.1F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
                           break;
                        case 4:
                           var60 *= 0.05F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
                     }

                     switch (var1.getMoodles().getMoodleLevel(MoodleType.Tired)) {
                        case 0:
                        default:
                           break;
                        case 1:
                           var60 *= 0.5F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Tired);
                           break;
                        case 2:
                           var60 *= 0.2F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Tired);
                           break;
                        case 3:
                           var60 *= 0.1F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Tired);
                           break;
                        case 4:
                           var60 *= 0.05F;
                           MoodlesUI.getInstance().wiggle(MoodleType.Tired);
                     }
                  }

                  var1.knockbackAttackMod = 1.0F;
                  if ("KnifeDeath" == var1.getVariableString("ZombieHitReaction"))) {
                     var38 *= 1000.0F;
                     var1.knockbackAttackMod = 0.0F;
                     var1.addWorldSoundUnlessInvisible(4, 4, false);
                     var1.attackVars.bCloseKill = true;
                     var17.setCloseKilled(true);
                  } else {
                     var1.attackVars.bCloseKill = false;
                     var17.setCloseKilled(false);
                     var1.addWorldSoundUnlessInvisible(8, 8, false);
                     if (Rand.Next(3) != 0 && (!var1.isAimAtFloor() || !var4.bDoShove)) {
                        if (Rand.Next(7) == 0) {
                           var1.addWorldSoundUnlessInvisible(16, 16, false);
                        }
                     } else {
                        var1.addWorldSoundUnlessInvisible(10, 10, false);
                     }
                  }

                  var17.setHitFromAngle(var16.dot);
                  if (var19 != nullptr) {
                     var19.setHitFromBehind(var1.isBehind(var19));
                     var19.setHitAngle(var1.getForwardDirection());
                     var19.setPlayerAttackPosition(var19.testDotSide(var1));
                     var19.setHitHeadWhileOnFloor(var14);
                     var19.setHitLegsWhileOnFloor(var15);
                     if (var14 > 0) {
                        var19.addBlood(BloodBodyPartType.Head, true, true, true);
                        var19.addBlood(BloodBodyPartType.Torso_Upper, true, false, false);
                        var19.addBlood(BloodBodyPartType.UpperArm_L, true, false, false);
                        var19.addBlood(BloodBodyPartType.UpperArm_R, true, false, false);
                        var60 *= 3.0F;
                     }

                     if (var15) {
                        var60 = 0.05F;
                     }

    int var66 = 0;
                     if (var14 > 0) {
                        var66 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Head), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
                     } else if (var15) {
                        var66 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Groin), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1);
                     } else {
                        var66 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
                     }

    float var40 = var19.getBodyPartClothingDefense(var66, false, var2.isRanged()) / 2.0F;
                     var40 += var19.getBodyPartClothingDefense(var66, true, var2.isRanged());
                     if (var40 > 70.0F) {
                        var40 = 70.0F;
                     }

    float var41 = var60 * Math.abs(1.0F - var40 / 100.0F);
                     var60 = var41;
                     if (!GameClient.bClient && !GameServer.bServer || GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
                        var8 = var19.helmetFall(var14 > 0);
                     }

                     if ("KnifeDeath" == var1.getVariableString("ZombieHitReaction")) && !"Tutorial" == Core.GameMode)) {
    uint8_t var42 = 8;
                        if (var19.isCurrentState(AttackState.instance())) {
                           var42 = 3;
                        }

    int var43 = var1.getPerkLevel(Perks.SmallBlade) + 1;
                        if (Rand.NextBool(var42 + var43 * 2)) {
    InventoryItem var44 = var1.getPrimaryHandItem();
                           var1.getInventory().Remove(var44);
                           var1.removeFromHands(var44);
                           var19.setAttachedItem("JawStab", var44);
                           var19.setJawStabAttach(true);
                        }

                        var19.setKnifeDeath(true);
                     }
                  }

    float var68 = 0.0F;
    bool var70 = var1.isCriticalHit();
                  if (var18 == nullptr && var17.getSquare() != nullptr && var1.getSquare() != nullptr) {
                     var17.setCloseKilled(var1.attackVars.bCloseKill);
                     if (((IsoPlayer)var1).isLocalPlayer() || var1.isNPC()) {
                        var68 = var17.Hit(var2, var1, var60, var6, var38);
                        this.setParameterCharacterHitResult(var1, var19, var29);
                     }

                     LuaEventManager.triggerEvent("OnWeaponHitXp", var1, var2, var17, var60);
                     if ((!var4.bDoShove || var1.isAimAtFloor()) && var1.DistToSquared(var17) < 2.0F && Math.abs(var1.z - var17.z) < 0.5F) {
                        var1.addBlood(nullptr, false, false, false);
                     }

                     if (dynamic_cast<IsoGameCharacter*>(var17) != nullptr) {
                        if (((IsoGameCharacter)var17).isDead()) {
                           var1.getStats().stress -= 0.02F;
                        } else if (!(dynamic_cast<IsoPlayer*>(var17) != nullptr) && (!var4.bDoShove || var1.isAimAtFloor())) {
                           splash(var17, var2, var1);
                        }
                     }
                  } else if (var18 != nullptr) {
    VehiclePart var71 = var18.getNearestBodyworkPart(var1);
                     if (var71 != nullptr) {
    VehicleWindow var72 = var71.getWindow();

                        for (int var73 = 0; var73 < var71.getChildCount(); var73++) {
    VehiclePart var76 = var71.getChild(var73);
                           if (var76.getWindow() != nullptr) {
                              var72 = var76.getWindow();
                              break;
                           }
                        }

                        if (var72 != nullptr && var72.isHittable()) {
    int var75 = this.calcDamageToVehicle((int)var60 * 10, var2.getDoorDamage(), true);
                           var72.damage(var75);
                           var1.playSound("HitVehicleWindowWithWeapon");
                        } else {
    int var74 = this.calcDamageToVehicle((int)var60 * 10, var2.getDoorDamage(), false);
                           var71.setCondition(var71.getCondition() - var74);
                           var5.setVehicleHitLocation(var18);
                           var1.playSound("HitVehiclePartWithWeapon");
                        }
                     }
                  }

                  if (GameClient.bClient && var1.isLocal()) {
                     if (dynamic_cast<IsoGameCharacter*>(var17) != nullptr) {
                        HitReactionNetworkAI.CalcHitReactionWeapon(var1, (IsoGameCharacter)var17, var2);
                     }

                     var46 = GameClient.sendHitCharacter(var1, var17, var2, var68, var6, var38, var70, var8, var14 > 0);
                  }
               }
            }
         }
      }

      if (GameClient.bClient && ((IsoPlayer)var1).isLocalPlayer() && !var46) {
         GameClient.sendHitCharacter(var1, nullptr, var2, 0.0F, var6, 1.0F, var1.isCriticalHit(), false, false);
      }

      if (!var7 && var10) {
    bool var48 = this.bHitOnlyTree && var2.getScriptItem().Categories.contains("Axe");
    int var49 = var48 ? 2 : 1;
         if (Rand.Next(var2.getConditionLowerChance() * var49 + var1.getMaintenanceMod() * 2) == 0) {
            var7 = true;
         } else if (Rand.NextBool(2)
            && WeaponType.getWeaponType(var1) != WeaponType.barehand
            && (!var2.isTwoHandWeapon() || var1.getPrimaryHandItem() == var2 || var1.getSecondaryHandItem() == var2 || !Rand.NextBool(3))) {
            var1.getXp().AddXP(Perks.Maintenance, 1.0F);
         }
      }

      var3.put(PARAM_LOWER_CONDITION, var7 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_ATTACKED, bool.TRUE);
   }

    int calcDamageToVehicle(int var1, int var2, bool var3) {
      if (var1 <= 0) {
    return 0;
      } else {
    float var4 = var1;
    float var5 = PZMath.clamp(var4 / (var3 ? 10.0F : 40.0F), 0.0F, 1.0F);
    int var6 = (int)(var2 * var5);
         return PZMath.clamp(var6, 1, var2);
      }
   }

    static void splash(IsoMovingObject var0, HandWeapon var1, IsoGameCharacter var2) {
    IsoGameCharacter var3 = (IsoGameCharacter)var0;
      if (var1 != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1) {
    int var4 = var1.getSplatNumber();
         if (var4 < 1) {
            var4 = 1;
         }

         if (Core.bLastStand) {
            var4 *= 3;
         }

         switch (SandboxOptions.instance.BloodLevel.getValue()) {
            case 2:
               var4 /= 2;
            case 3:
            default:
               break;
            case 4:
               var4 *= 2;
               break;
            case 5:
               var4 *= 5;
         }

         for (int var5 = 0; var5 < var4; var5++) {
            var3.splatBlood(3, 0.3F);
         }
      }

    uint8_t var10 = 3;
    uint8_t var11 = 7;
      switch (SandboxOptions.instance.BloodLevel.getValue()) {
         case 1:
            var11 = 0;
            break;
         case 2:
            var11 = 4;
            var10 = 5;
         case 3:
         default:
            break;
         case 4:
            var11 = 10;
            var10 = 2;
            break;
         case 5:
            var11 = 15;
            var10 = 0;
      }

      if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
         var3.splatBloodFloorBig();
      }

    float var6 = 0.5F;
      if (dynamic_cast<IsoZombie*>(var3) != nullptr && (((IsoZombie)var3).bCrawling || var3.getCurrentState() == ZombieOnGroundState.instance())) {
         var6 = 0.2F;
      }

    float var7 = Rand.Next(1.5F, 5.0F);
    float var8 = Rand.Next(1.5F, 5.0F);
      if (dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).bDoShove) {
         var7 = Rand.Next(0.0F, 0.5F);
         var8 = Rand.Next(0.0F, 0.5F);
      }

      if (var11 > 0) {
         var3.playBloodSplatterSound();
      }

      for (int var9 = 0; var9 < var11; var9++) {
         if (Rand.Next(var10) == 0) {
            std::make_shared<IsoZombieGiblets>(
               GibletType.A, var3.getCell(), var3.getX(), var3.getY(), var3.getZ() + var6, var3.getHitDir().x * var7, var3.getHitDir().y * var8
            );
         }
      }
   }

    bool checkObjectHit(IsoGameCharacter var1, HandWeapon var2, IsoGridSquare var3, bool var4, bool var5) {
      if (var3 == nullptr) {
    return false;
      } else {
         for (int var6 = var3.getSpecialObjects().size() - 1; var6 >= 0; var6--) {
    IsoObject var7 = (IsoObject)var3.getSpecialObjects().get(var6);
    IsoDoor var8 = (IsoDoor)Type.tryCastTo(var7, IsoDoor.class);
    IsoThumpable var9 = (IsoThumpable)Type.tryCastTo(var7, IsoThumpable.class);
    IsoWindow var10 = (IsoWindow)Type.tryCastTo(var7, IsoWindow.class);
            if (var8 != nullptr && (var4 && var8.north || var5 && !var8.north)) {
    Thumpable var11 = var8.getThumpableFor(var1);
               if (var11 != nullptr) {
                  var11.WeaponHit(var1, var2);
    return true;
               }
            }

            if (var9 != nullptr) {
               if (!var9.isDoor() && !var9.isWindow() && var9.isBlockAllTheSquare()) {
    Thumpable var13 = var9.getThumpableFor(var1);
                  if (var13 != nullptr) {
                     var13.WeaponHit(var1, var2);
    return true;
                  }
               } else if (var4 && var9.north || var5 && !var9.north) {
    Thumpable var12 = var9.getThumpableFor(var1);
                  if (var12 != nullptr) {
                     var12.WeaponHit(var1, var2);
    return true;
                  }
               }
            }

            if (var10 != nullptr && (var4 && var10.north || var5 && !var10.north)) {
    Thumpable var14 = var10.getThumpableFor(var1);
               if (var14 != nullptr) {
                  var14.WeaponHit(var1, var2);
    return true;
               }
            }
         }

    return false;
      }
   }

    bool CheckObjectHit(IsoGameCharacter var1, HandWeapon var2) {
      if (var1.isAimAtFloor()) {
         this.bHitOnlyTree = false;
    return false;
      } else {
    bool var3 = false;
    int var4 = 0;
    int var5 = 0;
    IsoDirections var6 = IsoDirections.fromAngle(var1.getForwardDirection());
    int var7 = 0;
    int var8 = 0;
         if (var6 == IsoDirections.NE || var6 == IsoDirections.N || var6 == IsoDirections.NW) {
            var8--;
         }

         if (var6 == IsoDirections.SE || var6 == IsoDirections.S || var6 == IsoDirections.SW) {
            var8++;
         }

         if (var6 == IsoDirections.NW || var6 == IsoDirections.W || var6 == IsoDirections.SW) {
            var7--;
         }

         if (var6 == IsoDirections.NE || var6 == IsoDirections.E || var6 == IsoDirections.SE) {
            var7++;
         }

    IsoCell var9 = IsoWorld.instance.CurrentCell;
    IsoGridSquare var10 = var1.getCurrentSquare();
    IsoGridSquare var11 = var9.getGridSquare(var10.getX() + var7, var10.getY() + var8, var10.getZ());
         if (var11 != nullptr) {
            if (this.checkObjectHit(var1, var2, var11, false, false)) {
               var3 = true;
               var4++;
            }

            if (!var11.isBlockedTo(var10)) {
               for (int var12 = 0; var12 < var11.getObjects().size(); var12++) {
    IsoObject var13 = (IsoObject)var11.getObjects().get(var12);
                  if (dynamic_cast<IsoTree*>(var13) != nullptr) {
                     ((IsoTree)var13).WeaponHit(var1, var2);
                     var3 = true;
                     var4++;
                     var5++;
                     if (var13.getObjectIndex() == -1) {
                        var12--;
                     }
                  }
               }
            }
         }

         if ((var6 == IsoDirections.NE || var6 == IsoDirections.N || var6 == IsoDirections.NW) && this.checkObjectHit(var1, var2, var10, true, false)) {
            var3 = true;
            var4++;
         }

         if (var6 == IsoDirections.SE || var6 == IsoDirections.S || var6 == IsoDirections.SW) {
    IsoGridSquare var14 = var9.getGridSquare(var10.getX(), var10.getY() + 1, var10.getZ());
            if (this.checkObjectHit(var1, var2, var14, true, false)) {
               var3 = true;
               var4++;
            }
         }

         if (var6 == IsoDirections.SE || var6 == IsoDirections.E || var6 == IsoDirections.NE) {
    IsoGridSquare var15 = var9.getGridSquare(var10.getX() + 1, var10.getY(), var10.getZ());
            if (this.checkObjectHit(var1, var2, var15, false, true)) {
               var3 = true;
               var4++;
            }
         }

         if ((var6 == IsoDirections.NW || var6 == IsoDirections.W || var6 == IsoDirections.SW) && this.checkObjectHit(var1, var2, var10, false, true)) {
            var3 = true;
            var4++;
         }

         this.bHitOnlyTree = var3 && var4 == var5;
    return var3;
      }
   }

    TestResults los(int var1, int var2, int var3, int var4, int var5, LOSVisitor var6) {
    IsoCell var7 = IsoWorld.instance.CurrentCell;
    int var10 = var4 - var2;
    int var11 = var3 - var1;
    int var12 = var5 - var5;
    float var13 = 0.5F;
    float var14 = 0.5F;
    IsoGridSquare var15 = var7.getGridSquare(var1, var2, var5);
      if (Math.abs(var11) > Math.abs(var10)) {
    float var16 = (float)var10 / var11;
    float var17 = (float)var12 / var11;
         var13 += var2;
         var14 += var5;
         var11 = var11 < 0 ? -1 : 1;
         var16 *= var11;
         var17 *= var11;

         while (var1 != var3) {
            var1 += var11;
            var13 += var16;
            var14 += var17;
    IsoGridSquare var18 = var7.getGridSquare(var1, (int)var13, (int)var14);
            if (var6.visit(var18, var15)) {
               return var6.getResult();
            }

            var15 = var18;
         }
      } else {
    float var26 = (float)var11 / var10;
    float var29 = (float)var12 / var10;
         var13 += var1;
         var14 += var5;
         var10 = var10 < 0 ? -1 : 1;
         var26 *= var10;
         var29 *= var10;

         while (var2 != var4) {
            var2 += var10;
            var13 += var26;
            var14 += var29;
    IsoGridSquare var31 = var7.getGridSquare((int)var13, var2, (int)var14);
            if (var6.visit(var31, var15)) {
               return var6.getResult();
            }

            var15 = var31;
         }
      }

      return TestResults.Clear;
   }

    IsoWindow getWindowBetween(int var1, int var2, int var3, int var4, int var5) {
      this.windowVisitor.init();
      this.los(var1, var2, var3, var4, var5, this.windowVisitor);
      return this.windowVisitor.window;
   }

    IsoWindow getWindowBetween(IsoMovingObject var1, IsoMovingObject var2) {
      return this.getWindowBetween((int)var1.x, (int)var1.y, (int)var2.x, (int)var2.y, (int)var1.z);
   }

    bool isWindowBetween(IsoMovingObject var1, IsoMovingObject var2) {
      return this.getWindowBetween(var1, var2) != nullptr;
   }

    void smashWindowBetween(IsoGameCharacter var1, IsoMovingObject var2, HandWeapon var3) {
    IsoWindow var4 = this.getWindowBetween(var1, var2);
      if (var4 != nullptr) {
         var4.WeaponHit(var1, var3);
      }
   }

    void changeWeapon(HandWeapon var1, IsoGameCharacter var2) {
      if (var1 != nullptr && var1.isUseSelf()) {
         var2.getInventory().setDrawDirty(true);

         for (InventoryItem var4 : var2.getInventory().getItems()) {
            if (var4 != var1 && dynamic_cast<HandWeapon*>(var4) != nullptr && var4.getType() == var1.getType() && var4.getCondition() > 0) {
               if (var2.getPrimaryHandItem() == var1 && var2.getSecondaryHandItem() == var1) {
                  var2.setPrimaryHandItem(var4);
                  var2.setSecondaryHandItem(var4);
               } else if (var2.getPrimaryHandItem() == var1) {
                  var2.setPrimaryHandItem(var4);
               } else if (var2.getSecondaryHandItem() == var1) {
                  var2.setSecondaryHandItem(var4);
               }

               return;
            }
         }
      }

      if (var1 == nullptr || var1.getCondition() <= 0 || var1.isUseSelf()) {
    HandWeapon var5 = (HandWeapon)var2.getInventory().getBestWeapon(var2.getDescriptor());
         var2.setPrimaryHandItem(nullptr);
         if (var2.getSecondaryHandItem() == var1) {
            var2.setSecondaryHandItem(nullptr);
         }

         if (var5 != nullptr && var5 != var2.getPrimaryHandItem() && var5.getCondition() > 0) {
            var2.setPrimaryHandItem(var5);
            if (var5.isTwoHandWeapon() && var2.getSecondaryHandItem() == nullptr) {
               var2.setSecondaryHandItem(var5);
            }
         }
      }
   }

    void setParameterCharacterHitResult(IsoGameCharacter var1, IsoZombie var2, long var3) {
      if (var3 != 0L) {
    uint8_t var5 = 0;
         if (var2 != nullptr) {
            if (var2.isDead()) {
               var5 = 2;
            } else if (var2.isKnockedDown()) {
               var5 = 1;
            }
         }

         var1.getEmitter().setParameterValue(var3, FMODManager.instance.getParameterDescription("CharacterHitResult"), var5);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
