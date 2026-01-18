#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "java/awt/geom/Line2D.h"
#include "org/joml/Vector3f.h"
#include "org/joml/Vector4f.h"
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/HitReactionNetworkAI.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory.h"
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
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include <algorithm>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SwipeStatePlayer : public State {
public:
 static const SwipeStatePlayer _instance = new SwipeStatePlayer();
 static const int PARAM_LOWER_CONDITION = 0;
 static const int PARAM_ATTACKED = 1;
 private static ArrayList<HitInfo> HitList2 = std::make_unique<ArrayList<>>();
 static const Vector2 tempVector2_1 = new Vector2();
 static const Vector2 tempVector2_2 = new Vector2();
 private ArrayList<Float> dotList = std::make_unique<ArrayList<>>();
 bool bHitOnlyTree;
 public ObjectPool<HitInfo> hitInfoPool = new ObjectPool<>(HitInfo::new);
 private static SwipeStatePlayer.CustomComparator Comparator = new SwipeStatePlayer.CustomComparator();
 static const Vector3 tempVector3_1 = new Vector3();
 static const Vector3 tempVector3_2 = new Vector3();
 static const Vector3 tempVectorBonePos = new Vector3();
 static ArrayList<IsoMovingObject> movingStatic = std::make_unique<ArrayList<>>();
 const Vector4f tempVector4f = new Vector4f();
 private SwipeStatePlayer.WindowVisitor windowVisitor = new SwipeStatePlayer.WindowVisitor();

 static SwipeStatePlayer instance() {
 return _instance;
 }

 static void WeaponLowerCondition(HandWeapon weapon, IsoGameCharacter owner) {
 if (weapon.getUses() > 1) {
 weapon.Use();
 InventoryItem item = InventoryItemFactory.CreateItem(weapon.getFullType());
 item.setCondition(weapon.getCondition() - 1);
 weapon.getContainer().AddItem(item);
 owner.setPrimaryHandItem(item);
 } else {
 weapon.setCondition(weapon.getCondition() - 1);
 }
 }

 static HandWeapon GetWeapon(IsoGameCharacter character) {
 HandWeapon weapon = character.getUseHandWeapon();
 if (((IsoLivingCharacter)character).bDoShove || character.isForceShove()) {
 weapon = ((IsoLivingCharacter)character).bareHands;
 }

 return weapon;
 }

 void doAttack(IsoPlayer player, float float0, bool boolean0, const std::string& string, AttackVars attackVars) {
 player.setForceShove(boolean0);
 player.setClickSound(string);
 if (boolean0) {
 float0 *= 2.0F;
 }

 if (float0 > 90.0F) {
 float0 = 90.0F;
 }

 float0 /= 25.0F;
 player.useChargeDelta = float0;
 void* object = player.getPrimaryHandItem();
 if (object.empty() || !(object instanceof HandWeapon) || boolean0 || attackVars.bDoShove) {
 object = player.bareHands;
 }

 if (object instanceof HandWeapon) {
 player.setUseHandWeapon((HandWeapon)object);
 if (player.PlayerIndex == 0 && player.JoypadBind == -1 && UIManager.getPicked() != nullptr && (!GameClient.bClient || player.isLocalPlayer())) {
 if (UIManager.getPicked().tile instanceof IsoMovingObject) {
 player.setAttackTargetSquare(((IsoMovingObject)UIManager.getPicked().tile).getCurrentSquare());
 } else {
 player.setAttackTargetSquare(UIManager.getPicked().square);
 }
 }

 player.setRecoilDelay(attackVars.recoilDelay);
 if (boolean0) {
 player.setRecoilDelay(10.0F);
 }
 }
 }

 void enter(IsoGameCharacter owner) {
 if ("HitReaction" == owner.getHitReaction())) {
 owner.clearVariable("HitReaction");
 }

 UIManager.speedControls.SetCurrentGameSpeed(1);
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 hashMap.put(PARAM_LOWER_CONDITION, Boolean.FALSE);
 hashMap.put(PARAM_ATTACKED, Boolean.FALSE);
 if (!(owner instanceof IsoPlayer) || !((IsoPlayer)owner).bRemote) {
 owner.updateRecoilVar();
 }

 if ("Auto" == owner.getVariableString("FireMode"))) {
 owner.setVariable("autoShootSpeed", 4.0F * GameTime.getAnimSpeedFix());
 owner.setVariable("autoShootVarY", 0.0F);
 if (System.currentTimeMillis() - owner.lastAutomaticShoot < 600L) {
 owner.shootInARow++;
 float float0 = Math.max(0.0F, 1.0F - owner.shootInARow / 20.0F);
 owner.setVariable("autoShootVarX", float0);
 } else {
 owner.setVariable("autoShootVarX", 1.0F);
 owner.shootInARow = 0;
 }

 owner.lastAutomaticShoot = System.currentTimeMillis();
 }

 IsoPlayer player = (IsoPlayer)owner;
 owner.setVariable("ShotDone", false);
 owner.setVariable("ShoveAnim", false);
 this->CalcAttackVars((IsoLivingCharacter)owner, player.attackVars);
 this->doAttack(player, 2.0F, owner.isForceShove(), owner.getClickSound(), player.attackVars);
 HandWeapon weapon = owner.getUseHandWeapon();
 if (!GameClient.bClient || player.isLocalPlayer()) {
 owner.setVariable("AimFloorAnim", player.attackVars.bAimAtFloor);
 }

 LuaEventManager.triggerEvent("OnWeaponSwing", owner, weapon);
 if (LuaHookManager.TriggerHook("WeaponSwing", owner, weapon) {
 owner.getStateMachine().revertToPreviousState(this);
 }

 owner.StopAllActionQueue();
 if (((IsoPlayer)owner).isLocalPlayer()) {
 IsoWorld.instance.CurrentCell.setDrag(nullptr, ((IsoPlayer)owner).PlayerIndex);
 }

 weapon = player.attackVars.getWeapon(player);
 player.setAimAtFloor(player.attackVars.bAimAtFloor);
 bool boolean0 = player.bDoShove;
 player.setDoShove(player.attackVars.bDoShove);
 player.useChargeDelta = player.attackVars.useChargeDelta;
 player.targetOnGround = (IsoGameCharacter)player.attackVars.targetOnGround.getMovingObject();
 if (!player.bDoShove && !boolean0 && player.getClickSound() == nullptr && weapon.getPhysicsObject() == nullptr && !weapon.isRanged()) {
 }

 if (GameClient.bClient && owner == IsoPlayer.getInstance()) {
 GameClient.instance.sendPlayer((IsoPlayer)owner);
 }

 if (!player.bDoShove && !boolean0 && !weapon.isRanged() && player.isLocalPlayer()) {
 owner.clearVariable("PlayedSwingSound");
 } else if ((player.bDoShove || boolean0) && player.isLocalPlayer()) {
 if (player.targetOnGround != nullptr) {
 owner.playSound("AttackStomp");
 } else {
 owner.playSound("AttackShove");
 }
 }
 }

 void execute(IsoGameCharacter owner) {
 owner.StopAllActionQueue();
 }

 int DoSwingCollisionBoneCheck(IsoGameCharacter character0, HandWeapon weapon, IsoGameCharacter character1, int int0, float float2) {
 movingStatic.clear();
 float float0 = weapon.WeaponLength;
 float0 += 0.5F;
 if (character0.isAimAtFloor() && ((IsoLivingCharacter)character0).bDoShove) {
 float0 = 0.3F;
 }

 Model.BoneToWorldCoords(character1, int0, tempVectorBonePos);

 for (int int1 = 1; int1 <= 10; int1++) {
 float float1 = int1 / 10.0F;
 tempVector3_1.x = character0.x;
 tempVector3_1.y = character0.y;
 tempVector3_1.z = character0.z;
 tempVector3_1.x = tempVector3_1.x + character0.getForwardDirection().x * float0 * float1;
 tempVector3_1.y = tempVector3_1.y + character0.getForwardDirection().y * float0 * float1;
 tempVector3_1.x = tempVectorBonePos.x - tempVector3_1.x;
 tempVector3_1.y = tempVectorBonePos.y - tempVector3_1.y;
 tempVector3_1.z = 0.0F;
 bool boolean0 = tempVector3_1.getLength() < float2;
 if (boolean0) {
 return int0;
 }
 }

 return -1;
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (event.m_EventName.equalsIgnoreCase("ActiveAnimFinishing") || event.m_EventName.equalsIgnoreCase("NonLoopedAnimFadeOut")) {
 bool boolean0 = hashMap.get(PARAM_LOWER_CONDITION) == Boolean.TRUE;
 if (boolean0 && !owner.isRangedWeaponEmpty()) {
 hashMap.put(PARAM_LOWER_CONDITION, Boolean.FALSE);
 HandWeapon weapon0 = GetWeapon(owner);
 int int0 = weapon0.getConditionLowerChance();
 if (owner instanceof IsoPlayer && "charge" == ((IsoPlayer)owner).getAttackType())) {
 int0 = (int)(int0 / 1.5);
 }

 if (Rand.Next(int0 + owner.getMaintenanceMod() * 2) == 0) {
 WeaponLowerCondition(weapon0, owner);
 } else if (Rand.NextBool(2) && !weapon0.isRanged() && WeaponType.getWeaponType(owner) != WeaponType.barehand) {
 if (weapon0.isTwoHandWeapon() && (owner.getPrimaryHandItem() != weapon0 || owner.getSecondaryHandItem() != weapon0) && Rand.NextBool(3) {
 return;
 }

 owner.getXp().AddXP(PerkFactory.Perks.Maintenance, 1.0F);
 }
 }
 }

 if (event.m_EventName.equalsIgnoreCase("AttackAnim")) {
 owner.setAttackAnim(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("BlockTurn")) {
 owner.setIgnoreMovement(Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("ShoveAnim")) {
 owner.setVariable("ShoveAnim", Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("StompAnim")) {
 owner.setVariable("StompAnim", Boolean.parseBoolean(event.m_ParameterValue);
 }

 HandWeapon weapon1 = GetWeapon(owner);
 if (event.m_EventName.equalsIgnoreCase("AttackCollisionCheck")
 && hashMap.get(PARAM_ATTACKED) == Boolean.FALSE
 && owner instanceof IsoPlayer
 && ((IsoPlayer)owner).isLocalPlayer()) {
 this->ConnectSwing(owner, weapon1);
 }

 if (event.m_EventName.equalsIgnoreCase("BlockMovement") && SandboxOptions.instance.AttackBlockMovements.getValue()) {
 owner.setVariable("SlowingMovement", Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("WeaponEmptyCheck") && owner.getClickSound() != nullptr) {
 if (owner instanceof IsoPlayer && !((IsoPlayer)owner).isLocalPlayer()) {
 return;
 }

 owner.playSound(owner.getClickSound());
 owner.setRecoilDelay(10.0F);
 }

 if (event.m_EventName.equalsIgnoreCase("ShotDone") && weapon1 != nullptr && weapon1.isRackAfterShoot()) {
 owner.setVariable("ShotDone", true);
 }

 if (event.m_EventName.equalsIgnoreCase("SetVariable") && event.m_ParameterValue.startsWith("ShotDone=")) {
 owner.setVariable("ShotDone", owner.getVariableBoolean("ShotDone") && weapon1 != nullptr && weapon1.isRackAfterShoot());
 }

 if (event.m_EventName.equalsIgnoreCase("playRackSound")) {
 if (owner instanceof IsoPlayer && !((IsoPlayer)owner).isLocalPlayer()) {
 return;
 }

 owner.playSound(weapon1.getRackSound());
 }

 if (event.m_EventName.equalsIgnoreCase("playClickSound")) {
 if (owner instanceof IsoPlayer && !((IsoPlayer)owner).isLocalPlayer()) {
 return;
 }

 owner.playSound(weapon1.getClickSound());
 }

 if (event.m_EventName.equalsIgnoreCase("PlaySwingSound")) {
 if (owner instanceof IsoPlayer && !((IsoPlayer)owner).isLocalPlayer()) {
 return;
 }

 if (weapon1.empty()) {
 return;
 }

 if (owner.getVariableBoolean("PlayedSwingSound")) {
 return;
 }

 owner.setVariable("PlayedSwingSound", true);
 if (!StringUtils.isNullOrWhitespace(event.m_ParameterValue) {
 std::string string = weapon1.getSoundByID(event.m_ParameterValue);
 if (string != nullptr) {
 owner.playSound(string);
 return;
 }
 }

 owner.playSound(weapon1.getSwingSound());
 }

 if (event.m_EventName.equalsIgnoreCase("SetMeleeDelay")) {
 owner.setMeleeDelay(PZMath.tryParseFloat(event.m_ParameterValue, 0.0F);
 }

 if (event.m_EventName.equalsIgnoreCase("SitGroundStarted")) {
 owner.setVariable("SitGroundAnim", "Idle");
 }
 }

 void exit(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 owner.setSprinting(false);
 ((IsoPlayer)owner).setForceSprint(false);
 owner.setIgnoreMovement(false);
 owner.setVariable("ShoveAnim", false);
 owner.setVariable("StompAnim", false);
 owner.setAttackAnim(false);
 owner.setVariable("AimFloorAnim", false);
 ((IsoPlayer)owner).setBlockMovement(false);
 if (owner.isAimAtFloor() && ((IsoLivingCharacter)owner).bDoShove) {
 Clothing clothing = (Clothing)owner.getWornItem("Shoes");
 int int0 = 10;
 if (clothing.empty()) {
 int0 = 3;
 } else {
 int0 += clothing.getConditionLowerChance() / 2;
 if (Rand.Next(clothing.getConditionLowerChance()) == 0) {
 clothing.setCondition(clothing.getCondition() - 1);
 }
 }

 if (Rand.Next(int0) == 0) {
 if (clothing.empty()) {
 owner.getBodyDamage().getBodyPart(BodyPartType.Foot_R).AddDamage(Rand.Next(5, 10);
 owner.getBodyDamage()
 .getBodyPart(BodyPartType.Foot_R)
 .setAdditionalPain(owner.getBodyDamage().getBodyPart(BodyPartType.Foot_R).getAdditionalPain() + Rand.Next(5, 10);
 } else {
 owner.getBodyDamage().getBodyPart(BodyPartType.Foot_R).AddDamage(Rand.Next(1, 5);
 owner.getBodyDamage()
 .getBodyPart(BodyPartType.Foot_R)
 .setAdditionalPain(owner.getBodyDamage().getBodyPart(BodyPartType.Foot_R).getAdditionalPain() + Rand.Next(1, 5);
 }
 }
 }

 HandWeapon weapon = GetWeapon(owner);
 owner.clearVariable("ZombieHitReaction");
 ((IsoPlayer)owner).attackStarted = false;
 ((IsoPlayer)owner).setAttackType(nullptr);
 ((IsoLivingCharacter)owner).setDoShove(false);
 owner.clearVariable("RackWeapon");
 owner.clearVariable("bShoveAiming");
 owner.clearVariable("PlayedSwingSound");
 bool boolean0 = hashMap.get(PARAM_ATTACKED) == Boolean.TRUE;
 if (weapon != nullptr && (weapon.getCondition() <= 0 || boolean0 && weapon.isUseSelf())) {
 owner.removeFromHands(weapon);
 if (DebugOptions.instance.MultiplayerAutoEquip.getValue() && weapon.getPhysicsObject() != nullptr) {
 owner.setPrimaryHandItem(owner.getInventory().getItemFromType(weapon.getType()));
 }

 owner.getInventory().setDrawDirty(true);
 }

 if (owner.isRangedWeaponEmpty()) {
 owner.setRecoilDelay(10.0F);
 }

 owner.setRangedWeaponEmpty(false);
 owner.setForceShove(false);
 owner.setClickSound(nullptr);
 if (boolean0) {
 LuaEventManager.triggerEvent("OnPlayerAttackFinished", owner, weapon);
 }

 owner.hitList.clear();
 owner.attackVars.clear();
 }

 void CalcAttackVars(IsoLivingCharacter owner, AttackVars vars) {
 HandWeapon weapon = Type.tryCastTo(owner.getPrimaryHandItem(), HandWeapon.class);
 if (weapon != nullptr && weapon.getOtherHandRequire() != nullptr) {
 InventoryItem item = owner.getSecondaryHandItem();
 if (item.empty() || !item.getType() == weapon.getOtherHandRequire())) {
 weapon = nullptr;
 }
 }

 if (!GameClient.bClient || owner.isLocal()) {
 bool boolean0 = owner.isAttackAnim() || owner.getVariableBoolean("ShoveAnim") || owner.getVariableBoolean("StompAnim");
 vars.setWeapon(weapon.empty() ? owner.bareHands : weapon);
 vars.targetOnGround.setMovingObject(nullptr);
 vars.bAimAtFloor = false;
 vars.bCloseKill = false;
 vars.bDoShove = owner.bDoShove;
 if (!boolean0) {
 owner.setVariable("ShoveAimX", 0.5F);
 owner.setVariable("ShoveAimY", 1.0F);
 if (vars.bDoShove && owner.getVariableBoolean("isMoving")) {
 owner.setVariable("ShoveAim", true);
 } else {
 owner.setVariable("ShoveAim", false);
 }
 }

 vars.useChargeDelta = owner.useChargeDelta;
 vars.recoilDelay = 0;
 if (vars.getWeapon(owner) == owner.bareHands || vars.bDoShove || owner.isForceShove()) {
 vars.bDoShove = true;
 vars.bAimAtFloor = false;
 vars.setWeapon(owner.bareHands);
 }

 this->calcValidTargets(owner, vars.getWeapon(owner), true, vars.targetsProne, vars.targetsStanding);
 HitInfo hitInfo0 = vars.targetsStanding.empty() ? nullptr : vars.targetsStanding.get(0);
 HitInfo hitInfo1 = vars.targetsProne.empty() ? nullptr : vars.targetsProne.get(0);
 if (this->isProneTargetBetter(owner, hitInfo0, hitInfo1) {
 hitInfo0 = nullptr;
 }

 if (!boolean0) {
 owner.setAimAtFloor(false);
 }

 float float0 = Float.MAX_VALUE;
 if (hitInfo0 != nullptr) {
 if (!boolean0) {
 owner.setAimAtFloor(false);
 }

 vars.bAimAtFloor = false;
 vars.targetOnGround.setMovingObject(nullptr);
 float0 = hitInfo0.distSq;
 } else if (hitInfo1 != nullptr && (Core.OptionAutoProneAtk || owner.bDoShove) {
 if (!boolean0) {
 owner.setAimAtFloor(true);
 }

 vars.bAimAtFloor = true;
 vars.targetOnGround.setMovingObject(hitInfo1.getObject());
 }

 if (!(float0 >= vars.getWeapon(owner).getMinRange() * vars.getWeapon(owner).getMinRange())
 && (hitInfo0.empty() || !this->isWindowBetween(owner, hitInfo0.getObject()))) {
 if (owner.getStats().NumChasingZombies <= 1 && WeaponType.getWeaponType(owner) == WeaponType.knife) {
 vars.bCloseKill = true;
 return;
 }

 vars.bDoShove = true;
 IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
 if (player != nullptr && !player.isAuthorizeShoveStomp()) {
 vars.bDoShove = false;
 }

 vars.bAimAtFloor = false;
 if (owner.bareHands.getSwingAnim() != nullptr) {
 vars.useChargeDelta = 3.0F;
 }
 }

 int int0 = Core.getInstance().getKey("ManualFloorAtk");
 int int1 = Core.getInstance().getKey("Sprint");
 bool boolean1 = owner.getVariableBoolean("StartedAttackWhileSprinting");
 if (Keyboard.isKeyDown(int0) && (int0 != int1 || !boolean1) {
 vars.bAimAtFloor = true;
 vars.bDoShove = false;
 owner.setDoShove(false);
 }

 if (vars.getWeapon(owner).isRanged()) {
 int int2 = vars.getWeapon(owner).getRecoilDelay();
 float float1 = int2 * (1.0F - owner.getPerkLevel(PerkFactory.Perks.Aiming) / 30.0F);
 vars.recoilDelay = float1.intValue();
 owner.setVariable("singleShootSpeed", (0.8F + owner.getPerkLevel(PerkFactory.Perks.Aiming) / 10.0F) * GameTime.getAnimSpeedFix());
 }
 }
 }

 public void calcValidTargets(
 IsoLivingCharacter owner, HandWeapon weapon, boolean extraRange, ArrayList<HitInfo> targetsProne, ArrayList<HitInfo> targetsStanding
 ) {
 this->hitInfoPool.release(targetsProne);
 this->hitInfoPool.release(targetsStanding);
 targetsProne.clear();
 targetsStanding.clear();
 float float0 = Core.getInstance().getIgnoreProneZombieRange();
 float float1 = weapon.getMaxRange() * weapon.getRangeMod(owner);
 float float2 = Math.max(float0, float1 + (extraRange ? 1.0F : 0.0F);
 std::vector arrayList = IsoWorld.instance.CurrentCell.getObjectList();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int0);
 HitInfo hitInfo = this->calcValidTarget(owner, weapon, movingObject, float2);
 if (hitInfo != nullptr) {
 if (isStanding(movingObject) {
 targetsStanding.add(hitInfo);
 } else {
 targetsProne.add(hitInfo);
 }
 }
 }

 if (!targetsProne.empty() && this->shouldIgnoreProneZombies(owner, targetsStanding, float0) {
 this->hitInfoPool.release(targetsProne);
 targetsProne.clear();
 }

 float float3 = weapon.getMinAngle();
 float float4 = weapon.getMaxAngle();
 if (weapon.isRanged()) {
 float3 -= weapon.getAimingPerkMinAngleModifier() * (owner.getPerkLevel(PerkFactory.Perks.Aiming) / 2.0F);
 }

 this->removeUnhittableTargets(owner, weapon, float3, float4, extraRange, targetsStanding);
 float3 = weapon.getMinAngle();
 float3 = (float)(float3 / 1.5);
 this->removeUnhittableTargets(owner, weapon, float3, float4, extraRange, targetsProne);
 targetsStanding.sort(Comparator);
 targetsProne.sort(Comparator);
 }

 bool shouldIgnoreProneZombies(IsoGameCharacter character, ArrayList<HitInfo> arrayList, float float0) {
 if (float0 <= 0.0F) {
 return false;
 } else {
 bool boolean0 = character.isInvisible() || character instanceof IsoPlayer && ((IsoPlayer)character).isGhostMode();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 HitInfo hitInfo = (HitInfo)arrayList.get(int0);
 IsoZombie zombie0 = Type.tryCastTo(hitInfo.getObject(), IsoZombie.class);
 if ((zombie0.empty() || zombie0.target != nullptr || boolean0) && !(hitInfo.distSq > float0 * float0) {
 int int1 = (int)character.z;
 boolean boolean1 = PolygonalMap2.instance
 .lineClearCollide(character.x, character.y, hitInfo.getObject().x, hitInfo.getObject().y, int1, character, false, true);
 if (!boolean1) {
 return true;
 }
 }
 }

 return false;
 }
 }

 bool isUnhittableTarget(IsoGameCharacter character, HandWeapon weapon, float float1, float float0, HitInfo hitInfo, bool boolean0) {
 if (!(hitInfo.dot < float1) && !(hitInfo.dot > float0) {
 Vector3 vector = tempVectorBonePos.set(hitInfo.x, hitInfo.y, hitInfo.z);
 return !character.IsAttackRange(weapon, hitInfo.getObject(), vector, boolean0);
 } else {
 return true;
 }
 }

 private void removeUnhittableTargets(
 IsoGameCharacter character, HandWeapon weapon, float float0, float float1, boolean boolean0, ArrayList<HitInfo> arrayList
 ) {
 for (int int0 = arrayList.size() - 1; int0 >= 0; int0--) {
 HitInfo hitInfo = (HitInfo)arrayList.get(int0);
 if (this->isUnhittableTarget(character, weapon, float0, float1, hitInfo, boolean0) {
 this->hitInfoPool.release(hitInfo);
 arrayList.remove(int0);
 }
 }
 }

 bool getNearestTargetPosAndDot(IsoGameCharacter character0, HandWeapon weapon, IsoMovingObject movingObject, bool boolean0, Vector4f vector4f) {
 this->getNearestTargetPosAndDot(character0, movingObject, vector4f);
 float float0 = vector4f.w;
 float float1 = weapon.getMinAngle();
 float float2 = weapon.getMaxAngle();
 IsoGameCharacter character1 = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character1 != nullptr) {
 if (isStanding(movingObject) {
 if (weapon.isRanged()) {
 float1 -= weapon.getAimingPerkMinAngleModifier() * (character0.getPerkLevel(PerkFactory.Perks.Aiming) / 2.0F);
 }
 } else {
 float1 /= 1.5F;
 }
 }

 if (!(float0 < float1) && !(float0 > float2) {
 Vector3 vector = tempVectorBonePos.set(vector4f.x, vector4f.y, vector4f.z);
 return character0.IsAttackRange(weapon, movingObject, vector, boolean0);
 } else {
 return false;
 }
 }

 void getNearestTargetPosAndDot(IsoGameCharacter character, Vector3 vector0, Vector2 vector1, Vector4f vector4f) {
 float float0 = character.getDotWithForwardDirection(vector0);
 float0 = PZMath.clamp(float0, -1.0F, 1.0F);
 vector4f.w = Math.max(float0, vector4f.w);
 float float1 = IsoUtils.DistanceToSquared(character.x, character.y, (int)character.z * 3, vector0.x, vector0.y, (int)Math.max(vector0.z, 0.0F) * 3);
 if (float1 < vector1.x) {
 vector1.x = float1;
 vector4f.set(vector0.x, vector0.y, vector0.z, vector4f.w);
 }
 }

 void getNearestTargetPosAndDot(IsoGameCharacter character, IsoMovingObject movingObject, const std::string& string, Vector2 vector1, Vector4f vector4f) {
 Vector3 vector0 = getBoneWorldPos(movingObject, string, tempVectorBonePos);
 this->getNearestTargetPosAndDot(character, vector0, vector1, vector4f);
 }

 void getNearestTargetPosAndDot(IsoGameCharacter character1, IsoMovingObject movingObject, Vector4f vector4f) {
 Vector2 vector0 = tempVector2_1.set(Float.MAX_VALUE, Float.NaN);
 vector4f.w = Float.NEGATIVE_INFINITY;
 IsoGameCharacter character0 = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character0.empty()) {
 this->getNearestTargetPosAndDot(character1, movingObject, (String)nullptr, vector0, vector4f);
 } else {
 getBoneWorldPos(movingObject, "Bip01_Head", tempVector3_1);
 getBoneWorldPos(movingObject, "Bip01_HeadNub", tempVector3_2);
 tempVector3_1.addToThis(tempVector3_2);
 tempVector3_1.div(2.0F);
 Vector3 vector1 = tempVector3_1;
 if (isStanding(movingObject) {
 this->getNearestTargetPosAndDot(character1, vector1, vector0, vector4f);
 this->getNearestTargetPosAndDot(character1, movingObject, "Bip01_Pelvis", vector0, vector4f);
 Vector3 vector2 = tempVectorBonePos.set(movingObject.getX(), movingObject.getY(), movingObject.getZ());
 this->getNearestTargetPosAndDot(character1, vector2, vector0, vector4f);
 } else {
 this->getNearestTargetPosAndDot(character1, vector1, vector0, vector4f);
 this->getNearestTargetPosAndDot(character1, movingObject, "Bip01_Pelvis", vector0, vector4f);
 this->getNearestTargetPosAndDot(character1, movingObject, "Bip01_DressFrontNub", vector0, vector4f);
 }
 }
 }

 HitInfo calcValidTarget(IsoLivingCharacter livingCharacter, HandWeapon weapon, IsoMovingObject movingObject, float float3) {
 if (movingObject == livingCharacter) {
 return nullptr;
 } else {
 IsoGameCharacter character = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character.empty()) {
 return nullptr;
 } else if (character.isGodMod()) {
 return nullptr;
 } else if (!checkPVP(livingCharacter, movingObject) {
 return nullptr;
 } else {
 float float0 = Math.abs(character.getZ() - livingCharacter.getZ());
 if (!weapon.isRanged() && float0 >= 0.5F) {
 return nullptr;
 } else if (float0 > 3.3F) {
 return nullptr;
 } else if (!character.isShootable()) {
 return nullptr;
 } else if (character.isCurrentState(FakeDeadZombieState.instance())) {
 return nullptr;
 } else if (character.isDead()) {
 return nullptr;
 } else if (character.getHitReaction() != nullptr && character.getHitReaction().contains("Death")) {
 return nullptr;
 } else {
 Vector4f vector4f = this->tempVector4f;
 this->getNearestTargetPosAndDot(livingCharacter, character, vector4f);
 float float1 = vector4f.w;
 float float2 = IsoUtils.DistanceToSquared(
 livingCharacter.x, livingCharacter.y, (int)livingCharacter.z * 3, vector4f.x, vector4f.y, (int)vector4f.z * 3
 );
 if (float1 < 0.0F) {
 return nullptr;
 } else if (float2 > float3 * float3) {
 return nullptr;
 } else {
 LosUtil.TestResults testResults = LosUtil.lineClear(
 livingCharacter.getCell(),
 (int)livingCharacter.getX(),
 (int)livingCharacter.getY(),
 (int)livingCharacter.getZ(),
 (int)character.getX(),
 (int)character.getY(),
 (int)character.getZ(),
 false
 );
 return testResults != LosUtil.TestResults.Blocked && testResults != LosUtil.TestResults.ClearThroughClosedDoor
 ? this->hitInfoPool.alloc().init(character, float1, float2, vector4f.x, vector4f.y, vector4f.z)
 : nullptr;
 }
 }
 }
 }
 }

 static bool isProne(IsoMovingObject obj) {
 IsoZombie zombie0 = Type.tryCastTo(obj, IsoZombie.class);
 if (zombie0.empty()) {
 return obj.isOnFloor();
 } else if (zombie0.isOnFloor()) {
 return true;
 } else if (zombie0.isCurrentState(ZombieEatBodyState.instance())) {
 return true;
 } else if (zombie0.isDead()) {
 return true;
 } else {
 return zombie0.isSitAgainstWall() ? true : zombie0.isCrawling();
 }
 }

 static bool isStanding(IsoMovingObject obj) {
 return !isProne(obj);
 }

 bool isProneTargetBetter(IsoGameCharacter owner, HitInfo bestStanding, HitInfo bestProne) {
 if (bestStanding.empty() || bestStanding.getObject() == nullptr) {
 return false;
 } else if (bestProne.empty() || bestProne.getObject() == nullptr) {
 return false;
 } else if (bestStanding.distSq <= bestProne.distSq) {
 return false;
 } else {
 int int0 = (int)owner.z;
 boolean boolean0 = PolygonalMap2.instance
 .lineClearCollide(owner.x, owner.y, bestStanding.getObject().x, bestStanding.getObject().y, int0, nullptr, false, true);
 if (!boolean0) {
 return false;
 } else {
 int0 = (int)owner.z;
 boolean boolean1 = PolygonalMap2.instance
 .lineClearCollide(owner.x, owner.y, bestProne.getObject().x, bestProne.getObject().y, int0, nullptr, false, true);
 return !boolean1;
 }
 }
 }

 static bool checkPVP(IsoGameCharacter owner, IsoMovingObject obj) {
 IsoPlayer player0 = Type.tryCastTo(owner, IsoPlayer.class);
 IsoPlayer player1 = Type.tryCastTo(obj, IsoPlayer.class);
 if (GameClient.bClient && player1 != nullptr && owner != nullptr) {
 if (player1.isGodMod()
 || !ServerOptions.instance.PVP.getValue()
 || ServerOptions.instance.SafetySystem.getValue() && owner.getSafety().isEnabled() && ((IsoGameCharacter)obj).getSafety().isEnabled()) {
 return false;
 }

 if (NonPvpZone.getNonPvpZone((int)obj.getX(), (int)obj.getY()) != nullptr) {
 return false;
 }

 if (player0 != nullptr && NonPvpZone.getNonPvpZone((int)owner.getX(), (int)owner.getY()) != nullptr) {
 return false;
 }

 if (player0 != nullptr && !player0.factionPvp && !player1.factionPvp) {
 Faction faction0 = Faction.getPlayerFaction(player0);
 Faction faction1 = Faction.getPlayerFaction(player1);
 if (faction1 != nullptr && faction0 == faction1) {
 return false;
 }
 }
 }

 return GameClient.bClient || player1.empty() || IsoPlayer.getCoopPVP();
 }

 void CalcHitListShove(IsoGameCharacter character0, bool boolean1, AttackVars attackVars, ArrayList<HitInfo> arrayList1) {
 HandWeapon weapon = attackVars.getWeapon((IsoLivingCharacter)character0);
 std::vector arrayList0 = IsoWorld.instance.CurrentCell.getObjectList();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList0.get(int0);
 if (movingObject != character0 && !(movingObject instanceof BaseVehicle) {
 IsoGameCharacter character1 = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character1 != nullptr && !character1.isGodMod() && !character1.isDead()) {
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if ((zombie0.empty() || !zombie0.isCurrentState(FakeDeadZombieState.instance())) && checkPVP(character0, movingObject) {
 boolean boolean0 = movingObject == attackVars.targetOnGround.getMovingObject()
 || movingObject.isShootable() && isStanding(movingObject) && !attackVars.bAimAtFloor
 || movingObject.isShootable() && isProne(movingObject) && attackVars.bAimAtFloor;
 if (boolean0) {
 Vector4f vector4f = this->tempVector4f;
 if (this->getNearestTargetPosAndDot(character0, weapon, movingObject, boolean1, vector4f) {
 float float0 = vector4f.w;
 float float1 = IsoUtils.DistanceToSquared(
 character0.x, character0.y, (int)character0.z * 3, vector4f.x, vector4f.y, (int)vector4f.z * 3
 );
 LosUtil.TestResults testResults = LosUtil.lineClear(
 character0.getCell(),
 (int)character0.getX(),
 (int)character0.getY(),
 (int)character0.getZ(),
 (int)movingObject.getX(),
 (int)movingObject.getY(),
 (int)movingObject.getZ(),
 false
 );
 if (testResults != LosUtil.TestResults.Blocked
 && testResults != LosUtil.TestResults.ClearThroughClosedDoor
 && (
 movingObject.getCurrentSquare() == nullptr
 || character0.getCurrentSquare() == nullptr
 || movingObject.getCurrentSquare() == character0.getCurrentSquare()
 || !movingObject.getCurrentSquare().isWindowBlockedTo(character0.getCurrentSquare())
 )
 && movingObject.getSquare().getTransparentWallTo(character0.getSquare()) == nullptr) {
 HitInfo hitInfo = this->hitInfoPool.alloc().init(movingObject, float0, float1, vector4f.x, vector4f.y, vector4f.z);
 if (attackVars.targetOnGround.getMovingObject() == movingObject) {
 arrayList1.clear();
 arrayList1.add(hitInfo);
 break;
 }

 arrayList1.add(hitInfo);
 }
 }
 }
 }
 }
 }
 }
 }

 void CalcHitListWeapon(IsoGameCharacter character0, bool boolean1, AttackVars attackVars, ArrayList<HitInfo> arrayList1) {
 HandWeapon weapon = attackVars.getWeapon((IsoLivingCharacter)character0);
 std::vector arrayList0 = IsoWorld.instance.CurrentCell.getObjectList();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList0.get(int0);
 if (movingObject != character0) {
 IsoGameCharacter character1 = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if ((character1.empty() || !character1.isGodMod()) && (character1.empty() || !character1.isDead())) {
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if ((zombie0.empty() || !zombie0.isCurrentState(FakeDeadZombieState.instance())) && checkPVP(character0, movingObject) {
 boolean boolean0 = movingObject == attackVars.targetOnGround.getMovingObject()
 || movingObject.isShootable() && isStanding(movingObject) && !attackVars.bAimAtFloor
 || movingObject.isShootable() && isProne(movingObject) && attackVars.bAimAtFloor;
 if (boolean0) {
 Vector4f vector4f = this->tempVector4f;
 if (movingObject instanceof BaseVehicle) {
 VehiclePart part = ((BaseVehicle)movingObject).getNearestBodyworkPart(character0);
 if (part.empty()) {
 continue;
 }

 float float0 = character0.getDotWithForwardDirection(movingObject.x, movingObject.y);
 if (float0 < 0.8F) {
 continue;
 }

 vector4f.set(movingObject.x, movingObject.y, movingObject.z, float0);
 } else if (character1.empty() || !this->getNearestTargetPosAndDot(character0, weapon, movingObject, boolean1, vector4f) {
 continue;
 }

 LosUtil.TestResults testResults = LosUtil.lineClear(
 character0.getCell(),
 (int)character0.getX(),
 (int)character0.getY(),
 (int)character0.getZ(),
 (int)movingObject.getX(),
 (int)movingObject.getY(),
 (int)movingObject.getZ(),
 false
 );
 if (testResults != LosUtil.TestResults.Blocked && testResults != LosUtil.TestResults.ClearThroughClosedDoor) {
 float float1 = vector4f.w;
 float float2 = IsoUtils.DistanceToSquared(
 character0.x, character0.y, (int)character0.z * 3, vector4f.x, vector4f.y, (int)vector4f.z * 3
 );
 if (movingObject.getSquare().getTransparentWallTo(character0.getSquare()) != nullptr && character0 instanceof IsoPlayer) {
 if (WeaponType.getWeaponType(character0) == WeaponType.spear) {
 ((IsoPlayer)character0).setAttackType("spearStab");
 } else if (WeaponType.getWeaponType(character0) != WeaponType.knife) {
 continue;
 }
 }

 IsoWindow window = this->getWindowBetween(character0, movingObject);
 if (window.empty() || !window.isBarricaded()) {
 HitInfo hitInfo = this->hitInfoPool.alloc().init(movingObject, float1, float2, vector4f.x, vector4f.y, vector4f.z);
 hitInfo.window.setObject(window);
 arrayList1.add(hitInfo);
 }
 }
 }
 }
 }
 }
 }

 if (arrayList1.empty()) {
 this->CalcHitListWindow(character0, weapon, arrayList1);
 }
 }

 void CalcHitListWindow(IsoGameCharacter character, HandWeapon weapon, ArrayList<HitInfo> arrayList1) {
 Vector2 vector = character.getLookVector(tempVector2_1);
 vector.setLength(weapon.getMaxRange() * weapon.getRangeMod(character);
 HitInfo hitInfo = nullptr;
 std::vector arrayList0 = IsoWorld.instance.CurrentCell.getWindowList();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 IsoWindow window = (IsoWindow)arrayList0.get(int0);
 if ((int)window.getZ() == (int)character.z && this->windowVisitor.isHittable(window) {
 float float0 = window.getX();
 float float1 = window.getY();
 float float2 = float0 + (window.getNorth() ? 1.0F : 0.0F);
 float float3 = float1 + (window.getNorth() ? 0.0F : 1.0F);
 if (Line2D.linesIntersect(character.x, character.y, character.x + vector.x, character.y + vector.y, float0, float1, float2, float3) {
 IsoGridSquare square = window.getAddSheetSquare(character);
 if (square != nullptr && !LosUtil.lineClearCollide((int)character.x, (int)character.y, (int)character.z, square.x, square.y, square.z, false) {
 float float4 = IsoUtils.DistanceToSquared(
 character.x, character.y, float0 + (float2 - float0) / 2.0F, float1 + (float3 - float1) / 2.0F
 );
 if (hitInfo.empty() || !(hitInfo.distSq < float4) {
 float float5 = 1.0F;
 if (hitInfo.empty()) {
 hitInfo = this->hitInfoPool.alloc();
 }

 hitInfo.init(window, float5, float4);
 }
 }
 }
 }
 }

 if (hitInfo != nullptr) {
 arrayList1.add(hitInfo);
 }
 }

 void CalcHitList(IsoGameCharacter owner, bool extraRange, AttackVars attackVars, ArrayList<HitInfo> hitList) {
 if (!GameClient.bClient || owner.isLocal()) {
 this->hitInfoPool.release(hitList);
 hitList.clear();
 HandWeapon weapon = attackVars.getWeapon((IsoLivingCharacter)owner);
 int int0 = weapon.getMaxHitCount();
 if (attackVars.bDoShove) {
 int0 = WeaponType.getWeaponType(owner) != WeaponType.barehand ? 3 : 1;
 }

 if (!weapon.isRanged() && !SandboxOptions.instance.MultiHitZombies.getValue()) {
 int0 = 1;
 }

 if (weapon == ((IsoPlayer)owner).bareHands && !(owner.getPrimaryHandItem() instanceof HandWeapon) {
 int0 = 1;
 }

 if (weapon == ((IsoPlayer)owner).bareHands && attackVars.targetOnGround.getMovingObject() != nullptr) {
 int0 = 1;
 }

 if (0 < int0) {
 if (attackVars.bDoShove) {
 this->CalcHitListShove(owner, extraRange, attackVars, hitList);
 } else {
 this->CalcHitListWeapon(owner, extraRange, attackVars, hitList);
 }

 if (hitList.size() == 1 && ((HitInfo)hitList.get(0).getObject() == nullptr) {
 return;
 }

 this->filterTargetsByZ(owner);
 Collections.sort(hitList, Comparator);
 if (weapon.isPiercingBullets()) {
 HitList2.clear();
 double double0 = 0.0;

 for (int int1 = 0; int1 < hitList.size(); int1++) {
 HitInfo hitInfo0 = (HitInfo)hitList.get(int1);
 IsoMovingObject movingObject = hitInfo0.getObject();
 if (movingObject != nullptr) {
 double double1 = owner.getX() - movingObject.getX();
 double double2 = -(owner.getY() - movingObject.getY());
 double double3 = Math.atan2(double2, double1);
 if (double3 < 0.0) {
 double3 = Math.abs(double3);
 } else {
 double3 = (Math.PI * 2) - double3;
 }

 if (int1 == 0) {
 double0 = Math.toDegrees(double3);
 HitList2.add(hitInfo0);
 } else {
 double double4 = Math.toDegrees(double3);
 if (Math.abs(double0 - double4) < 1.0) {
 HitList2.add(hitInfo0);
 break;
 }
 }
 }
 }

 hitList.removeAll(HitList2);
 this->hitInfoPool.release(hitList);
 hitList.clear();
 hitList.addAll(HitList2);
 } else {
 while (hitList.size() > int0) {
 this->hitInfoPool.release((HitInfo)hitList.remove(hitList.size() - 1);
 }
 }
 }

 for (int int2 = 0; int2 < hitList.size(); int2++) {
 HitInfo hitInfo1 = (HitInfo)hitList.get(int2);
 hitInfo1.chance = this->CalcHitChance(owner, weapon, hitInfo1);
 }
 }
 }

 void filterTargetsByZ(IsoGameCharacter character) {
 float float0 = Float.MAX_VALUE;
 HitInfo hitInfo0 = nullptr;

 for (int int0 = 0; int0 < character.hitList.size(); int0++) {
 HitInfo hitInfo1 = character.hitList.get(int0);
 float float1 = Math.abs(hitInfo1.z - character.getZ());
 if (float1 < float0) {
 float0 = float1;
 hitInfo0 = hitInfo1;
 }
 }

 if (hitInfo0 != nullptr) {
 for (int int1 = character.hitList.size() - 1; int1 >= 0; int1--) {
 HitInfo hitInfo2 = character.hitList.get(int1);
 if (hitInfo2 != hitInfo0) {
 float float2 = Math.abs(hitInfo2.z - hitInfo0.z);
 if (float2 > 0.5F) {
 this->hitInfoPool.release(hitInfo2);
 character.hitList.remove(int1);
 }
 }
 }
 }
 }

 int CalcHitChance(IsoGameCharacter owner, HandWeapon weapon, HitInfo hitInfo) {
 IsoMovingObject movingObject = hitInfo.getObject();
 if (movingObject.empty()) {
 return 0;
 } else {
 if (owner.getVehicle() != nullptr) {
 BaseVehicle vehicle = owner.getVehicle();
 Vector3f vector3f = vehicle.getForwardVector(BaseVehicle.TL_vector3f_pool.get().alloc());
 Vector2 vector0 = BaseVehicle.TL_vector2_pool.get().alloc();
 vector0.x = vector3f.x;
 vector0.y = vector3f.z;
 vector0.normalize();
 int int0 = vehicle.getSeat(owner);
 VehicleScript.Area area = vehicle.getScript().getAreaById(vehicle.getPassengerArea(int0);
 uint8_t byte0 = -90;
 if (area.x > 0.0F) {
 byte0 = 90;
 }

 vector0.rotate((float)Math.toRadians(byte0);
 vector0.normalize();
 Vector2 vector1 = BaseVehicle.TL_vector2_pool.get().alloc();
 vector1.x = movingObject.x;
 vector1.y = movingObject.y;
 vector1.x = vector1.x - owner.x;
 vector1.y = vector1.y - owner.y;
 vector1.normalize();
 float float0 = vector1.dot(vector0);
 if (float0 > -0.6) {
 return 0;
 }

 BaseVehicle.TL_vector2_pool.get().release(vector0);
 BaseVehicle.TL_vector2_pool.get().release(vector1);
 BaseVehicle.TL_vector3f_pool.get().release(vector3f);
 }

 if (System.currentTimeMillis() - owner.lastAutomaticShoot > 600L) {
 owner.shootInARow = 0;
 }

 int int1 = weapon.getHitChance();
 int1 = (int)(int1 + weapon.getAimingPerkHitChanceModifier() * owner.getPerkLevel(PerkFactory.Perks.Aiming);
 if (int1 > 95) {
 int1 = 95;
 }

 int1 -= owner.shootInARow * 2;
 float float1 = PZMath.sqrt(hitInfo.distSq);
 float float2 = 1.3F;
 if (movingObject instanceof IsoPlayer) {
 float1 = (float)(float1 * 1.5);
 float2 = 1.0F;
 }

 int1 = (int)(int1 + (weapon.getMaxRange() * weapon.getRangeMod(owner) - float1) * float2);
 if (weapon.getMinRangeRanged() > 0.0F) {
 if (float1 < weapon.getMinRangeRanged()) {
 int1 -= 50;
 }
 } else if (float1 < 1.7 && weapon.isRanged() && !(movingObject instanceof IsoPlayer) {
 int1 += 35;
 }

 if (weapon.isRanged() && owner.getBeenMovingFor() > weapon.getAimingTime() + owner.getPerkLevel(PerkFactory.Perks.Aiming) {
 int1 = (int)(int1 - (owner.getBeenMovingFor() - (weapon.getAimingTime() + owner.getPerkLevel(PerkFactory.Perks.Aiming);
 }

 if (hitInfo.getObject() instanceof IsoPlayer) {
 IsoPlayer player = (IsoPlayer)hitInfo.getObject();
 if (player.isPlayerMoving()) {
 int1 -= 5;
 }

 if (player.isRunning()) {
 int1 -= 10;
 }

 if (player.isSprinting()) {
 int1 -= 15;
 }
 }

 if (weapon.isRanged() && owner.getVehicle() != nullptr) {
 int1 = (int)(int1 - Math.abs(owner.getVehicle().getCurrentSpeedKmHour()) * 2.0F);
 }

 if (owner.Traits.Marksman.isSet()) {
 int1 += 20;
 }

 float float3 = 0.0F;

 for (int int2 = BodyPartType.ToIndex(BodyPartType.Hand_L); int2 <= BodyPartType.ToIndex(BodyPartType.UpperArm_R); int2++) {
 float3 += owner.getBodyDamage().getBodyParts().get(int2).getPain();
 }

 if (float3 > 0.0F) {
 int1 = (int)(int1 - float3 / 10.0F);
 }

 int1 -= owner.getMoodles().getMoodleLevel(MoodleType.Tired) * 5;
 if (int1 <= 10) {
 int1 = 10;
 }

 if (int1 > 100 || !weapon.isRanged()) {
 int1 = 100;
 }

 return int1;
 }
 }

 static Vector3 getBoneWorldPos(IsoMovingObject target, const std::string& boneName, Vector3 bonePos) {
 IsoGameCharacter character = Type.tryCastTo(target, IsoGameCharacter.class);
 if (character != nullptr && boneName != nullptr) {
 AnimationPlayer animationPlayer = character.getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 int int0 = animationPlayer.getSkinningBoneIndex(boneName, -1);
 if (int0 == -1) {
 return bonePos.set(target.x, target.y, target.z);
 } else {
 Model.BoneToWorldCoords(character, int0, bonePos);
 return bonePos;
 }
 } else {
 return bonePos.set(target.x, target.y, target.z);
 }
 } else {
 return bonePos.set(target.x, target.y, target.z);
 }
 }

 void ConnectSwing(IsoGameCharacter owner, HandWeapon weapon) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoLivingCharacter livingCharacter = (IsoLivingCharacter)owner;
 IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
 if (owner.getVariableBoolean("ShoveAnim")) {
 livingCharacter.setDoShove(true);
 }

 if (GameServer.bServer) {
 DebugLog.log(DebugType.Network, "Player swing connects.");
 }

 LuaEventManager.triggerEvent("OnWeaponSwingHitPoint", owner, weapon);
 if (weapon.getPhysicsObject() != nullptr) {
 owner.Throw(weapon);
 }

 if (weapon.isUseSelf()) {
 weapon.Use();
 }

 if (weapon.isOtherHandUse() && owner.getSecondaryHandItem() != nullptr) {
 owner.getSecondaryHandItem().Use();
 }

 bool boolean0 = false;
 if (livingCharacter.bDoShove && !owner.isAimAtFloor()) {
 boolean0 = true;
 }

 bool boolean1 = false;
 bool boolean2 = false;
 owner.attackVars.setWeapon(weapon);
 owner.attackVars.targetOnGround.setMovingObject(livingCharacter.targetOnGround);
 owner.attackVars.bAimAtFloor = owner.isAimAtFloor();
 owner.attackVars.bDoShove = livingCharacter.bDoShove;
 if (owner.getVariableBoolean("ShoveAnim")) {
 owner.attackVars.bDoShove = true;
 }

 this->CalcHitList(owner, false, owner.attackVars, owner.hitList);
 int int0 = owner.hitList.size();
 bool boolean3 = false;
 if (int0 == 0) {
 boolean3 = this->CheckObjectHit(owner, weapon);
 }

 if (weapon.isUseEndurance()) {
 float float0 = 0.0F;
 if (weapon.isTwoHandWeapon() && (owner.getPrimaryHandItem() != weapon || owner.getSecondaryHandItem() != weapon) {
 float0 = weapon.getWeight() / 1.5F / 10.0F;
 }

 if (int0 <= 0 && !owner.isForceShove()) {
 float float1 = (weapon.getWeight() * 0.18F * weapon.getFatigueMod(owner) * owner.getFatigueMod() * weapon.getEnduranceMod() * 0.3F + float0)
 * 0.04F;
 float float2 = 1.0F;
 if (owner.Traits.Asthmatic.isSet()) {
 float2 = 1.3F;
 }

 owner.getStats().endurance -= float1 * float2;
 }
 }

 owner.setLastHitCount(owner.hitList.size());
 if (!weapon.isMultipleHitConditionAffected()) {
 boolean1 = true;
 }

 int int1 = 1;
 this->dotList.clear();
 if (owner.hitList.empty() && owner.getClickSound() != nullptr && !livingCharacter.bDoShove) {
 if (owner instanceof IsoPlayer && ((IsoPlayer)owner).isLocalPlayer() || !(owner instanceof IsoPlayer) {
 owner.getEmitter().playSound(owner.getClickSound());
 }

 owner.setRecoilDelay(10.0F);
 }

 bool boolean4 = false;

 for (int int2 = 0; int2 < owner.hitList.size(); int2++) {
 uint8_t byte0 = 0;
 bool boolean5 = false;
 HitInfo hitInfo = owner.hitList.get(int2);
 IsoMovingObject movingObject = hitInfo.getObject();
 BaseVehicle vehicle = Type.tryCastTo(movingObject, BaseVehicle.class);
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if (hitInfo.getObject() == nullptr && hitInfo.window.getObject() != nullptr) {
 hitInfo.window.getObject().WeaponHit(owner, weapon);
 } else {
 this->smashWindowBetween(owner, movingObject, weapon);
 if (!this->isWindowBetween(owner, movingObject) {
 int int3 = hitInfo.chance;
 bool boolean6 = Rand.Next(100) <= int3;
 if (boolean6) {
 Vector2 vector0 = tempVector2_1.set(owner.getX(), owner.getY());
 Vector2 vector1 = tempVector2_2.set(movingObject.getX(), movingObject.getY());
 vector1.x = vector1.x - vector0.x;
 vector1.y = vector1.y - vector0.y;
 Vector2 vector2 = owner.getLookVector(tempVector2_1);
 vector2.tangent();
 vector1.normalize();
 bool boolean7 = true;
 float float3 = vector2.dot(vector1);

 for (int int4 = 0; int4 < this->dotList.size(); int4++) {
 float float4 = this->dotList.get(int4);
 if (Math.abs(float3 - float4) < 1.0E-4) {
 boolean7 = false;
 }
 }

 float float5 = weapon.getMinDamage();
 float float6 = weapon.getMaxDamage();
 long long0 = 0L;
 if (!boolean7) {
 float5 /= 5.0F;
 float6 /= 5.0F;
 }

 if (owner.isAimAtFloor() && !weapon.isRanged() && owner.isNPC()) {
 splash(movingObject, weapon, owner);
 byte0 = (byte)Rand.Next(2);
 } else if (owner.isAimAtFloor() && !weapon.isRanged()) {
 if (player.empty() || player.isLocalPlayer()) {
 if (!StringUtils.isNullOrEmpty(weapon.getHitFloorSound())) {
 owner.getEmitter().stopSoundByName(weapon.getSwingSound());
 if (player != nullptr) {
 player.setMeleeHitSurface(ParameterMeleeHitSurface.Material.Body);
 }

 long0 = owner.playSound(weapon.getHitFloorSound());
 } else {
 owner.getEmitter().stopSoundByName(weapon.getSwingSound());
 if (player != nullptr) {
 player.setMeleeHitSurface(ParameterMeleeHitSurface.Material.Body);
 }

 long0 = owner.playSound(weapon.getZombieHitSound());
 }
 }

 int int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_Head", -1),
 0.28F
 );
 if (int5 == -1) {
 int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_Spine", -1),
 0.28F
 );
 if (int5 == -1) {
 int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_L_Calf", -1),
 0.13F
 );
 if (int5 == -1) {
 int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Calf", -1),
 0.13F
 );
 }

 if (int5 == -1) {
 int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_L_Foot", -1),
 0.23F
 );
 }

 if (int5 == -1) {
 int5 = this->DoSwingCollisionBoneCheck(
 owner,
 GetWeapon(owner),
 (IsoGameCharacter)movingObject,
 ((IsoGameCharacter)movingObject).getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Foot", -1),
 0.23F
 );
 }

 if (int5 == -1) {
 continue;
 }

 boolean5 = true;
 }
 } else {
 splash(movingObject, weapon, owner);
 splash(movingObject, weapon, owner);
 byte0 = (byte)(Rand.Next(0, 3) + 1);
 }
 }

 if (!owner.attackVars.bAimAtFloor
 && (!owner.attackVars.bCloseKill || !owner.isCriticalHit())
 && !livingCharacter.bDoShove
 && movingObject instanceof IsoGameCharacter
 && (player.empty() || player.isLocalPlayer())) {
 if (player != nullptr) {
 player.setMeleeHitSurface(ParameterMeleeHitSurface.Material.Body);
 }

 if (weapon.isRanged()) {
 long0 = ((IsoGameCharacter)movingObject).playSound(weapon.getZombieHitSound());
 } else {
 owner.getEmitter().stopSoundByName(weapon.getSwingSound());
 long0 = owner.playSound(weapon.getZombieHitSound());
 }
 }

 if (weapon.isRanged() && zombie0 != nullptr) {
 Vector2 vector3 = tempVector2_1.set(owner.getX(), owner.getY());
 Vector2 vector4 = tempVector2_2.set(movingObject.getX(), movingObject.getY());
 vector4.x = vector4.x - vector3.x;
 vector4.y = vector4.y - vector3.y;
 Vector2 vector5 = zombie0.getForwardDirection();
 vector4.normalize();
 vector5.normalize();
 float float7 = vector4.dot(vector5);
 zombie0.setHitFromBehind(float7 > 0.5);
 }

 if (this->dotList.empty()) {
 this->dotList.add(float3);
 }

 if (zombie0 != nullptr && zombie0.isCurrentState(ZombieOnGroundState.instance())) {
 zombie0.setReanimateTimer(zombie0.getReanimateTimer() + Rand.Next(10);
 }

 if (zombie0 != nullptr && zombie0.isCurrentState(ZombieGetUpState.instance())) {
 zombie0.setReanimateTimer(Rand.Next(60) + 30);
 }

 bool boolean8 = false;
 if (!weapon.isTwoHandWeapon() || owner.isItemInBothHands(weapon) {
 boolean8 = true;
 }

 float float8 = float6 - float5;
 float float9;
 if (float8 == 0.0F) {
 float9 = float5 + 0.0F;
 } else {
 float9 = float5 + Rand.Next((int)(float8 * 1000.0F) / 1000.0F;
 }

 if (!weapon.isRanged()) {
 float9 *= weapon.getDamageMod(owner) * owner.getHittingMod();
 }

 if (!boolean8 && !weapon.isRanged() && float6 > float5) {
 float9 -= float5;
 }

 if (owner.isAimAtFloor() && livingCharacter.bDoShove) {
 float float10 = 0.0F;

 for (int int6 = BodyPartType.ToIndex(BodyPartType.UpperLeg_L); int6 <= BodyPartType.ToIndex(BodyPartType.Foot_R); int6++) {
 float10 += owner.getBodyDamage().getBodyParts().get(int6).getPain();
 }

 if (float10 > 10.0F) {
 float9 /= PZMath.clamp(float10 / 10.0F, 1.0F, 30.0F);
 MoodlesUI.getInstance().wiggle(MoodleType.Pain);
 MoodlesUI.getInstance().wiggle(MoodleType.Injured);
 }
 } else {
 float float11 = 0.0F;

 for (int int7 = BodyPartType.ToIndex(BodyPartType.Hand_L); int7 <= BodyPartType.ToIndex(BodyPartType.UpperArm_R); int7++) {
 float11 += owner.getBodyDamage().getBodyParts().get(int7).getPain();
 }

 if (float11 > 10.0F) {
 float9 /= PZMath.clamp(float11 / 10.0F, 1.0F, 30.0F);
 MoodlesUI.getInstance().wiggle(MoodleType.Pain);
 MoodlesUI.getInstance().wiggle(MoodleType.Injured);
 }
 }

 if (owner.Traits.Underweight.isSet()) {
 float9 *= 0.8F;
 }

 if (owner.Traits.VeryUnderweight.isSet()) {
 float9 *= 0.6F;
 }

 if (owner.Traits.Emaciated.isSet()) {
 float9 *= 0.4F;
 }

 float float12 = float9 / (int1 / 2.0F);
 if (owner.isAttackWasSuperAttack()) {
 float12 *= 5.0F;
 }

 int1++;
 if (weapon.isMultipleHitConditionAffected()) {
 boolean1 = true;
 }

 Vector2 vector6 = tempVector2_1.set(owner.getX(), owner.getY());
 Vector2 vector7 = tempVector2_2.set(movingObject.getX(), movingObject.getY());
 vector7.x = vector7.x - vector6.x;
 vector7.y = vector7.y - vector6.y;
 float float13 = vector7.getLength();
 float float14 = 1.0F;
 if (weapon.isRangeFalloff()) {
 float14 = 1.0F;
 } else if (weapon.isRanged()) {
 float14 = 0.5F;
 } else {
 float14 = float13 / weapon.getMaxRange(owner);
 }

 float14 *= 2.0F;
 if (float14 < 0.3F) {
 float14 = 1.0F;
 }

 if (weapon.isRanged() && owner.getPerkLevel(PerkFactory.Perks.Aiming) < 6 && owner.getMoodles().getMoodleLevel(MoodleType.Panic) > 2) {
 float12 -= owner.getMoodles().getMoodleLevel(MoodleType.Panic) * 0.2F;
 MoodlesUI.getInstance().wiggle(MoodleType.Panic);
 }

 if (!weapon.isRanged() && owner.getMoodles().getMoodleLevel(MoodleType.Panic) > 1) {
 float12 -= owner.getMoodles().getMoodleLevel(MoodleType.Panic) * 0.1F;
 MoodlesUI.getInstance().wiggle(MoodleType.Panic);
 }

 if (owner.getMoodles().getMoodleLevel(MoodleType.Stress) > 1) {
 float12 -= owner.getMoodles().getMoodleLevel(MoodleType.Stress) * 0.1F;
 MoodlesUI.getInstance().wiggle(MoodleType.Stress);
 }

 if (float12 < 0.0F) {
 float12 = 0.1F;
 }

 if (owner.isAimAtFloor() && livingCharacter.bDoShove) {
 float12 = Rand.Next(0.7F, 1.0F) + owner.getPerkLevel(PerkFactory.Perks.Strength) * 0.2F;
 Clothing clothing = (Clothing)owner.getWornItem("Shoes");
 if (clothing.empty()) {
 float12 *= 0.5F;
 } else {
 float12 *= clothing.getStompPower();
 }
 }

 if (!weapon.isRanged()) {
 switch (owner.getMoodles().getMoodleLevel(MoodleType.Endurance) {
 case 0:
 default:
 break;
 case 1:
 float12 *= 0.5F;
 MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
 break;
 case 2:
 float12 *= 0.2F;
 MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
 break;
 case 3:
 float12 *= 0.1F;
 MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
 break;
 case 4:
 float12 *= 0.05F;
 MoodlesUI.getInstance().wiggle(MoodleType.Endurance);
 }

 switch (owner.getMoodles().getMoodleLevel(MoodleType.Tired) {
 case 0:
 default:
 break;
 case 1:
 float12 *= 0.5F;
 MoodlesUI.getInstance().wiggle(MoodleType.Tired);
 break;
 case 2:
 float12 *= 0.2F;
 MoodlesUI.getInstance().wiggle(MoodleType.Tired);
 break;
 case 3:
 float12 *= 0.1F;
 MoodlesUI.getInstance().wiggle(MoodleType.Tired);
 break;
 case 4:
 float12 *= 0.05F;
 MoodlesUI.getInstance().wiggle(MoodleType.Tired);
 }
 }

 owner.knockbackAttackMod = 1.0F;
 if ("KnifeDeath" == owner.getVariableString("ZombieHitReaction"))) {
 float14 *= 1000.0F;
 owner.knockbackAttackMod = 0.0F;
 owner.addWorldSoundUnlessInvisible(4, 4, false);
 owner.attackVars.bCloseKill = true;
 movingObject.setCloseKilled(true);
 } else {
 owner.attackVars.bCloseKill = false;
 movingObject.setCloseKilled(false);
 owner.addWorldSoundUnlessInvisible(8, 8, false);
 if (Rand.Next(3) != 0 && (!owner.isAimAtFloor() || !livingCharacter.bDoShove) {
 if (Rand.Next(7) == 0) {
 owner.addWorldSoundUnlessInvisible(16, 16, false);
 }
 } else {
 owner.addWorldSoundUnlessInvisible(10, 10, false);
 }
 }

 movingObject.setHitFromAngle(hitInfo.dot);
 if (zombie0 != nullptr) {
 zombie0.setHitFromBehind(owner.isBehind(zombie0);
 zombie0.setHitAngle(owner.getForwardDirection());
 zombie0.setPlayerAttackPosition(zombie0.testDotSide(owner);
 zombie0.setHitHeadWhileOnFloor(byte0);
 zombie0.setHitLegsWhileOnFloor(boolean5);
 if (byte0 > 0) {
 zombie0.addBlood(BloodBodyPartType.Head, true, true, true);
 zombie0.addBlood(BloodBodyPartType.Torso_Upper, true, false, false);
 zombie0.addBlood(BloodBodyPartType.UpperArm_L, true, false, false);
 zombie0.addBlood(BloodBodyPartType.UpperArm_R, true, false, false);
 float12 *= 3.0F;
 }

 if (boolean5) {
 float12 = 0.05F;
 }

 int int8 = 0;
 if (byte0 > 0) {
 int8 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Head), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
 } else if (boolean5) {
 int8 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Groin), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1);
 } else {
 int8 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
 }

 float float15 = zombie0.getBodyPartClothingDefense(int8, false, weapon.isRanged()) / 2.0F;
 float15 += zombie0.getBodyPartClothingDefense(int8, true, weapon.isRanged());
 if (float15 > 70.0F) {
 float15 = 70.0F;
 }

 float float16 = float12 * Math.abs(1.0F - float15 / 100.0F);
 float12 = float16;
 if (!GameClient.bClient && !GameServer.bServer
 || GameClient.bClient && owner instanceof IsoPlayer && ((IsoPlayer)owner).isLocalPlayer()) {
 boolean2 = zombie0.helmetFall(byte0 > 0);
 }

 if ("KnifeDeath" == owner.getVariableString("ZombieHitReaction")) && !"Tutorial" == Core.GameMode) {
 uint8_t byte1 = 8;
 if (zombie0.isCurrentState(AttackState.instance())) {
 byte1 = 3;
 }

 int int9 = owner.getPerkLevel(PerkFactory.Perks.SmallBlade) + 1;
 if (Rand.NextBool(byte1 + int9 * 2) {
 InventoryItem item = owner.getPrimaryHandItem();
 owner.getInventory().Remove(item);
 owner.removeFromHands(item);
 zombie0.setAttachedItem("JawStab", item);
 zombie0.setJawStabAttach(true);
 }

 zombie0.setKnifeDeath(true);
 }
 }

 float float17 = 0.0F;
 bool boolean9 = owner.isCriticalHit();
 if (vehicle.empty() && movingObject.getSquare() != nullptr && owner.getSquare() != nullptr) {
 movingObject.setCloseKilled(owner.attackVars.bCloseKill);
 if (((IsoPlayer)owner).isLocalPlayer() || owner.isNPC()) {
 float17 = movingObject.Hit(weapon, owner, float12, boolean0, float14);
 this->setParameterCharacterHitResult(owner, zombie0, long0);
 }

 LuaEventManager.triggerEvent("OnWeaponHitXp", owner, weapon, movingObject, float12);
 if ((!livingCharacter.bDoShove || owner.isAimAtFloor())
 && owner.DistToSquared(movingObject) < 2.0F
 && Math.abs(owner.z - movingObject.z) < 0.5F) {
 owner.addBlood(nullptr, false, false, false);
 }

 if (movingObject instanceof IsoGameCharacter) {
 if (((IsoGameCharacter)movingObject).isDead()) {
 owner.getStats().stress -= 0.02F;
 } else if (!(movingObject instanceof IsoPlayer) && (!livingCharacter.bDoShove || owner.isAimAtFloor())) {
 splash(movingObject, weapon, owner);
 }
 }
 } else if (vehicle != nullptr) {
 VehiclePart part0 = vehicle.getNearestBodyworkPart(owner);
 if (part0 != nullptr) {
 VehicleWindow vehicleWindow = part0.getWindow();

 for (int int10 = 0; int10 < part0.getChildCount(); int10++) {
 VehiclePart part1 = part0.getChild(int10);
 if (part1.getWindow() != nullptr) {
 vehicleWindow = part1.getWindow();
 break;
 }
 }

 if (vehicleWindow != nullptr && vehicleWindow.isHittable()) {
 int int11 = this->calcDamageToVehicle((int)float12 * 10, weapon.getDoorDamage(), true);
 vehicleWindow.damage(int11);
 owner.playSound("HitVehicleWindowWithWeapon");
 } else {
 int int12 = this->calcDamageToVehicle((int)float12 * 10, weapon.getDoorDamage(), false);
 part0.setCondition(part0.getCondition() - int12);
 player.setVehicleHitLocation(vehicle);
 owner.playSound("HitVehiclePartWithWeapon");
 }
 }
 }

 if (GameClient.bClient && owner.isLocal()) {
 if (movingObject instanceof IsoGameCharacter) {
 HitReactionNetworkAI.CalcHitReactionWeapon(owner, (IsoGameCharacter)movingObject, weapon);
 }

 boolean4 = GameClient.sendHitCharacter(owner, movingObject, weapon, float17, boolean0, float14, boolean9, boolean2, byte0 > 0);
 }
 }
 }
 }
 }

 if (GameClient.bClient && ((IsoPlayer)owner).isLocalPlayer() && !boolean4) {
 GameClient.sendHitCharacter(owner, nullptr, weapon, 0.0F, boolean0, 1.0F, owner.isCriticalHit(), false, false);
 }

 if (!boolean1 && boolean3) {
 bool boolean10 = this->bHitOnlyTree && weapon.getScriptItem().Categories.contains("Axe");
 int int13 = boolean10 ? 2 : 1;
 if (Rand.Next(weapon.getConditionLowerChance() * int13 + owner.getMaintenanceMod() * 2) == 0) {
 boolean1 = true;
 } else if (Rand.NextBool(2)
 && WeaponType.getWeaponType(owner) != WeaponType.barehand
 && (!weapon.isTwoHandWeapon() || owner.getPrimaryHandItem() == weapon || owner.getSecondaryHandItem() == weapon || !Rand.NextBool(3) {
 owner.getXp().AddXP(PerkFactory.Perks.Maintenance, 1.0F);
 }
 }

 hashMap.put(PARAM_LOWER_CONDITION, boolean1 ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_ATTACKED, Boolean.TRUE);
 }

 int calcDamageToVehicle(int int0, int int2, bool boolean0) {
 if (int0 <= 0) {
 return 0;
 } else {
 float float0 = int0;
 float float1 = PZMath.clamp(float0 / (boolean0 ? 10.0F : 40.0F), 0.0F, 1.0F);
 int int1 = (int)(int2 * float1);
 return PZMath.clamp(int1, 1, int2);
 }
 }

 static void splash(IsoMovingObject obj, HandWeapon weapon, IsoGameCharacter owner) {
 IsoGameCharacter character = (IsoGameCharacter)obj;
 if (weapon != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1) {
 int int0 = weapon.getSplatNumber();
 if (int0 < 1) {
 int0 = 1;
 }

 if (Core.bLastStand) {
 int0 *= 3;
 }

 switch (SandboxOptions.instance.BloodLevel.getValue()) {
 case 2:
 int0 /= 2;
 case 3:
 default:
 break;
 case 4:
 int0 *= 2;
 break;
 case 5:
 int0 *= 5;
 }

 for (int int1 = 0; int1 < int0; int1++) {
 character.splatBlood(3, 0.3F);
 }
 }

 uint8_t byte0 = 3;
 uint8_t byte1 = 7;
 switch (SandboxOptions.instance.BloodLevel.getValue()) {
 case 1:
 byte1 = 0;
 break;
 case 2:
 byte1 = 4;
 byte0 = 5;
 case 3:
 default:
 break;
 case 4:
 byte1 = 10;
 byte0 = 2;
 break;
 case 5:
 byte1 = 15;
 byte0 = 0;
 }

 if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
 character.splatBloodFloorBig();
 }

 float float0 = 0.5F;
 if (character instanceof IsoZombie && (((IsoZombie)character).bCrawling || character.getCurrentState() == ZombieOnGroundState.instance())) {
 float0 = 0.2F;
 }

 float float1 = Rand.Next(1.5F, 5.0F);
 float float2 = Rand.Next(1.5F, 5.0F);
 if (owner instanceof IsoPlayer && ((IsoPlayer)owner).bDoShove) {
 float1 = Rand.Next(0.0F, 0.5F);
 float2 = Rand.Next(0.0F, 0.5F);
 }

 if (byte1 > 0) {
 character.playBloodSplatterSound();
 }

 for (int int2 = 0; int2 < byte1; int2++) {
 if (Rand.Next((int)byte0) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 character.getCell(),
 character.getX(),
 character.getY(),
 character.getZ() + float0,
 character.getHitDir().x * float1,
 character.getHitDir().y * float2
 );
 }
 }
 }

 bool checkObjectHit(IsoGameCharacter character, HandWeapon weapon, IsoGridSquare square, bool boolean1, bool boolean0) {
 if (square.empty()) {
 return false;
 } else {
 for (int int0 = square.getSpecialObjects().size() - 1; int0 >= 0; int0--) {
 IsoObject object = square.getSpecialObjects().get(int0);
 IsoDoor door = Type.tryCastTo(object, IsoDoor.class);
 IsoThumpable thumpable0 = Type.tryCastTo(object, IsoThumpable.class);
 IsoWindow window = Type.tryCastTo(object, IsoWindow.class);
 if (door != nullptr && (boolean1 && door.north || boolean0 && !door.north) {
 Thumpable thumpable1 = door.getThumpableFor(character);
 if (thumpable1 != nullptr) {
 thumpable1.WeaponHit(character, weapon);
 return true;
 }
 }

 if (thumpable0 != nullptr) {
 if (!thumpable0.isDoor() && !thumpable0.isWindow() && thumpable0.isBlockAllTheSquare()) {
 Thumpable thumpable2 = thumpable0.getThumpableFor(character);
 if (thumpable2 != nullptr) {
 thumpable2.WeaponHit(character, weapon);
 return true;
 }
 } else if (boolean1 && thumpable0.north || boolean0 && !thumpable0.north) {
 Thumpable thumpable3 = thumpable0.getThumpableFor(character);
 if (thumpable3 != nullptr) {
 thumpable3.WeaponHit(character, weapon);
 return true;
 }
 }
 }

 if (window != nullptr && (boolean1 && window.north || boolean0 && !window.north) {
 Thumpable thumpable4 = window.getThumpableFor(character);
 if (thumpable4 != nullptr) {
 thumpable4.WeaponHit(character, weapon);
 return true;
 }
 }
 }

 return false;
 }
 }

 bool CheckObjectHit(IsoGameCharacter character, HandWeapon weapon) {
 if (character.isAimAtFloor()) {
 this->bHitOnlyTree = false;
 return false;
 } else {
 bool boolean0 = false;
 int int0 = 0;
 int int1 = 0;
 IsoDirections directions = IsoDirections.fromAngle(character.getForwardDirection());
 int int2 = 0;
 int int3 = 0;
 if (directions == IsoDirections.NE || directions == IsoDirections.N || directions == IsoDirections.NW) {
 int3--;
 }

 if (directions == IsoDirections.SE || directions == IsoDirections.S || directions == IsoDirections.SW) {
 int3++;
 }

 if (directions == IsoDirections.NW || directions == IsoDirections.W || directions == IsoDirections.SW) {
 int2--;
 }

 if (directions == IsoDirections.NE || directions == IsoDirections.E || directions == IsoDirections.SE) {
 int2++;
 }

 IsoCell cell = IsoWorld.instance.CurrentCell;
 IsoGridSquare square0 = character.getCurrentSquare();
 IsoGridSquare square1 = cell.getGridSquare(square0.getX() + int2, square0.getY() + int3, square0.getZ());
 if (square1 != nullptr) {
 if (this->checkObjectHit(character, weapon, square1, false, false) {
 boolean0 = true;
 int0++;
 }

 if (!square1.isBlockedTo(square0) {
 for (int int4 = 0; int4 < square1.getObjects().size(); int4++) {
 IsoObject object = square1.getObjects().get(int4);
 if (object instanceof IsoTree) {
 ((IsoTree)object).WeaponHit(character, weapon);
 boolean0 = true;
 int0++;
 int1++;
 if (object.getObjectIndex() == -1) {
 int4--;
 }
 }
 }
 }
 }

 if ((directions == IsoDirections.NE || directions == IsoDirections.N || directions == IsoDirections.NW)
 && this->checkObjectHit(character, weapon, square0, true, false) {
 boolean0 = true;
 int0++;
 }

 if (directions == IsoDirections.SE || directions == IsoDirections.S || directions == IsoDirections.SW) {
 IsoGridSquare square2 = cell.getGridSquare(square0.getX(), square0.getY() + 1, square0.getZ());
 if (this->checkObjectHit(character, weapon, square2, true, false) {
 boolean0 = true;
 int0++;
 }
 }

 if (directions == IsoDirections.SE || directions == IsoDirections.E || directions == IsoDirections.NE) {
 IsoGridSquare square3 = cell.getGridSquare(square0.getX() + 1, square0.getY(), square0.getZ());
 if (this->checkObjectHit(character, weapon, square3, false, true) {
 boolean0 = true;
 int0++;
 }
 }

 if ((directions == IsoDirections.NW || directions == IsoDirections.W || directions == IsoDirections.SW)
 && this->checkObjectHit(character, weapon, square0, false, true) {
 boolean0 = true;
 int0++;
 }

 this->bHitOnlyTree = boolean0 && int0 == int1;
 return boolean0;
 }
 }

 private LosUtil.TestResults los(int int5, int int2, int int4, int int1, int int7, SwipeStatePlayer.LOSVisitor lOSVisitor) {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 int int0 = int1 - int2;
 int int3 = int4 - int5;
 int int6 = int7 - int7;
 float float0 = 0.5F;
 float float1 = 0.5F;
 IsoGridSquare square0 = cell.getGridSquare(int5, int2, int7);
 if (Math.abs(int3) > Math.abs(int0) {
 float float2 = (float)int0 / int3;
 float float3 = (float)int6 / int3;
 float0 += int2;
 float1 += int7;
 int3 = int3 < 0 ? -1 : 1;
 float2 *= int3;
 float3 *= int3;

 while (int5 != int4) {
 int5 += int3;
 float0 += float2;
 float1 += float3;
 IsoGridSquare square1 = cell.getGridSquare(int5, (int)float0, (int)float1);
 if (lOSVisitor.visit(square1, square0) {
 return lOSVisitor.getResult();
 }

 square0 = square1;
 }
 } else {
 float float4 = (float)int3 / int0;
 float float5 = (float)int6 / int0;
 float0 += int5;
 float1 += int7;
 int0 = int0 < 0 ? -1 : 1;
 float4 *= int0;
 float5 *= int0;

 while (int2 != int1) {
 int2 += int0;
 float0 += float4;
 float1 += float5;
 IsoGridSquare square2 = cell.getGridSquare((int)float0, int2, (int)float1);
 if (lOSVisitor.visit(square2, square0) {
 return lOSVisitor.getResult();
 }

 square0 = square2;
 }
 }

 return LosUtil.TestResults.Clear;
 }

 IsoWindow getWindowBetween(int int0, int int1, int int2, int int3, int int4) {
 this->windowVisitor.init();
 this->los(int0, int1, int2, int3, int4, this->windowVisitor);
 return this->windowVisitor.window;
 }

 IsoWindow getWindowBetween(IsoMovingObject movingObject0, IsoMovingObject movingObject1) {
 return this->getWindowBetween((int)movingObject0.x, (int)movingObject0.y, (int)movingObject1.x, (int)movingObject1.y, (int)movingObject0.z);
 }

 bool isWindowBetween(IsoMovingObject movingObject0, IsoMovingObject movingObject1) {
 return this->getWindowBetween(movingObject0, movingObject1) != nullptr;
 }

 void smashWindowBetween(IsoGameCharacter character, IsoMovingObject movingObject, HandWeapon weapon) {
 IsoWindow window = this->getWindowBetween(character, movingObject);
 if (window != nullptr) {
 window.WeaponHit(character, weapon);
 }
 }

 void changeWeapon(HandWeapon weapon, IsoGameCharacter owner) {
 if (weapon != nullptr && weapon.isUseSelf()) {
 owner.getInventory().setDrawDirty(true);

 for (InventoryItem item : owner.getInventory().getItems()) {
 if (item != weapon && item instanceof HandWeapon && item.getType() == weapon.getType() && item.getCondition() > 0) {
 if (owner.getPrimaryHandItem() == weapon && owner.getSecondaryHandItem() == weapon) {
 owner.setPrimaryHandItem(item);
 owner.setSecondaryHandItem(item);
 } else if (owner.getPrimaryHandItem() == weapon) {
 owner.setPrimaryHandItem(item);
 } else if (owner.getSecondaryHandItem() == weapon) {
 owner.setSecondaryHandItem(item);
 }

 return;
 }
 }
 }

 if (weapon.empty() || weapon.getCondition() <= 0 || weapon.isUseSelf()) {
 HandWeapon _weapon = (HandWeapon)owner.getInventory().getBestWeapon(owner.getDescriptor());
 owner.setPrimaryHandItem(nullptr);
 if (owner.getSecondaryHandItem() == weapon) {
 owner.setSecondaryHandItem(nullptr);
 }

 if (_weapon != nullptr && _weapon != owner.getPrimaryHandItem() && _weapon.getCondition() > 0) {
 owner.setPrimaryHandItem(_weapon);
 if (_weapon.isTwoHandWeapon() && owner.getSecondaryHandItem() == nullptr) {
 owner.setSecondaryHandItem(_weapon);
 }
 }
 }
 }

 void setParameterCharacterHitResult(IsoGameCharacter character, IsoZombie zombie0, long long0) {
 if (long0 != 0L) {
 uint8_t byte0 = 0;
 if (zombie0 != nullptr) {
 if (zombie0.isDead()) {
 byte0 = 2;
 } else if (zombie0.isKnockedDown()) {
 byte0 = 1;
 }
 }

 character.getEmitter().setParameterValue(long0, FMODManager.instance.getParameterDescription("CharacterHitResult"), byte0);
 }
 }

 public static class CustomComparator implements Comparator<HitInfo> {
 int compare(HitInfo hitInfo0, HitInfo hitInfo1) {
 float float0 = hitInfo0.distSq;
 float float1 = hitInfo1.distSq;
 IsoZombie zombie0 = Type.tryCastTo(hitInfo0.getObject(), IsoZombie.class);
 IsoZombie zombie1 = Type.tryCastTo(hitInfo1.getObject(), IsoZombie.class);
 if (zombie0 != nullptr && zombie1 != nullptr) {
 bool boolean0 = SwipeStatePlayer.isProne(zombie0);
 bool boolean1 = SwipeStatePlayer.isProne(zombie1);
 bool boolean2 = zombie0.isCurrentState(ZombieGetUpState.instance());
 bool boolean3 = zombie1.isCurrentState(ZombieGetUpState.instance());
 if (boolean2 && !boolean3 && boolean1) {
 return -1;
 }

 if (!boolean2 && boolean0 && boolean3) {
 return 1;
 }

 if (boolean0 && boolean1) {
 if (zombie0.isCrawling() && !zombie1.isCrawling()) {
 return -1;
 }

 if (!zombie0.isCrawling() && zombie1.isCrawling()) {
 return 1;
 }
 }
 }

 if (float0 > float1) {
 return 1;
 } else {
 return float1 > float0 ? -1 : 0;
 }
 }
 }

 private interface LOSVisitor {
 bool visit(IsoGridSquare var1, IsoGridSquare var2);

 LosUtil.TestResults getResult();
 }

 private static class WindowVisitor implements SwipeStatePlayer.LOSVisitor {
 LosUtil.TestResults test;
 IsoWindow window;

 void init() {
 this->test = LosUtil.TestResults.Clear;
 this->window = nullptr;
 }

 bool visit(IsoGridSquare square1, IsoGridSquare square0) {
 if (square1 != nullptr && square0 != nullptr) {
 bool boolean0 = true;
 bool boolean1 = false;
 LosUtil.TestResults testResults = square1.testVisionAdjacent(
 square0.getX() - square1.getX(), square0.getY() - square1.getY(), square0.getZ() - square1.getZ(), boolean0, boolean1
 );
 if (testResults == LosUtil.TestResults.ClearThroughWindow) {
 IsoWindow windowx = square1.getWindowTo(square0);
 if (this->isHittable(windowx) && windowx.TestVision(square1, square0) == IsoObject.VisionResult.Unblocked) {
 this->window = windowx;
 return true;
 }
 }

 if (testResults != LosUtil.TestResults.Blocked
 && this->test != LosUtil.TestResults.Clear
 && (testResults != LosUtil.TestResults.ClearThroughWindow || this->test != LosUtil.TestResults.ClearThroughOpenDoor) {
 if (testResults == LosUtil.TestResults.ClearThroughClosedDoor && this->test == LosUtil.TestResults.ClearThroughOpenDoor) {
 this->test = testResults;
 }
 } else {
 this->test = testResults;
 }

 return this->test == LosUtil.TestResults.Blocked;
 } else {
 return false;
 }
 }

 public LosUtil.TestResults getResult() {
 return this->test;
 }

 bool isHittable(IsoWindow windowx) {
 if (windowx.empty()) {
 return false;
 } else {
 return windowx.isBarricaded() ? true : !windowx.isDestroyed() && !windowx.IsOpen();
 }
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
