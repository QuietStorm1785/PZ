#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Literature.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * ILuaGameCharacter Provides the functions expected by LUA when dealing with
 * objects of this type.
 */
class ILuaGameCharacter {
public:
 virtual ~ILuaGameCharacter() = default;
 extends ILuaVariableSource, ILuaGameCharacterAttachedItems,
 ILuaGameCharacterDamage, ILuaGameCharacterClothing,
 ILuaGameCharacterHealth {
 std::string getFullName();

 SurvivorDesc getDescriptor();

 void setDescriptor(SurvivorDesc descriptor);

 bool isRangedWeaponEmpty();

 void setRangedWeaponEmpty(bool val);

 BaseVisual getVisual();

 BaseCharacterSoundEmitter getEmitter();

 void resetModel();

 void resetModelNextFrame();

 IsoSpriteInstance getSpriteDef();

 bool hasItems(std::string_view type, int count);

 int getXpForLevel(int level);

 IsoGameCharacter.XP getXp();

 bool isAsleep();

 void setAsleep(bool Asleep);

 int getZombieKills();

 void setForceWakeUpTime(float ForceWakeUpTime);

 ItemContainer getInventory();

 InventoryItem getPrimaryHandItem();

 void setPrimaryHandItem(InventoryItem leftHandItem);

 InventoryItem getSecondaryHandItem();

 void setSecondaryHandItem(InventoryItem rightHandItem);

 bool hasEquipped(std::string_view String);

 bool hasEquippedTag(std::string_view tag);

 bool isHandItem(InventoryItem item);

 bool isPrimaryHandItem(InventoryItem item);

 bool isSecondaryHandItem(InventoryItem item);

 bool isItemInBothHands(InventoryItem item);

 bool removeFromHands(InventoryItem item);

 void setSpeakColourInfo(ColorInfo info);

 bool isSpeaking();

 Moodles getMoodles();

 Stats getStats();

 TraitCollection getTraits();

 int getMaxWeight();

 void PlayAnim(std::string_view string);

 void PlayAnimWithSpeed(std::string_view string,
 float framesSpeedPerFrame);

 void PlayAnimUnlooped(std::string_view string);

 void StartTimedActionAnim(std::string_view event);

 void StartTimedActionAnim(std::string_view event,
 std::string_view type);

 void StopTimedActionAnim();

 Stack<BaseAction> getCharacterActions();

 void StartAction(BaseAction act);

 void StopAllActionQueue();

 int getPerkLevel(PerkFactory.Perk perks);

 IsoGameCharacter.PerkInfo getPerkInfo(PerkFactory.Perk perk);

 void setPerkLevelDebug(PerkFactory.Perk perks, int level);

 void LoseLevel(PerkFactory.Perk perk);

 void LevelPerk(PerkFactory.Perk perk, bool removePick);

 void LevelPerk(PerkFactory.Perk perk);

 void ReadLiterature(Literature literature);

 void setDir(IsoDirections directions);

 void Callout();

 bool IsSpeaking();

 void Say(std::string_view line);

 void Say(std::string_view line, float r, float g, float b, UIFont font,
 float baseRange, std::string_view customTag);

 void setHaloNote(std::string_view str);

 void setHaloNote(std::string_view str, float dispTime);

 void setHaloNote(std::string_view str, int r, int g, int b,
 float dispTime);

 void initSpritePartsEmpty();

 bool HasTrait(std::string_view trait);

 void changeState(State state);

 bool isCurrentState(State state);

 State getCurrentState();

 void pathToLocation(int x, int y, int z);

 void pathToLocationF(float x, float y, float z);

 bool CanAttack();

 void smashCarWindow(VehiclePart part);

 void smashWindow(IsoWindow w);

 void openWindow(IsoWindow w);

 void closeWindow(IsoWindow w);

 void climbThroughWindow(IsoWindow w);

 void climbThroughWindow(IsoWindow w, int startingFrame);

 void climbThroughWindowFrame(IsoObject obj);

 void climbSheetRope();

 void climbDownSheetRope();

 bool canClimbSheetRope(IsoGridSquare sq);

 bool canClimbDownSheetRopeInCurrentSquare();

 bool canClimbDownSheetRope(IsoGridSquare sq);

 void climbThroughWindow(IsoThumpable w);

 void climbThroughWindow(IsoThumpable w, int startingFrame);

 void climbOverFence(IsoDirections dir);

 bool isAboveTopOfStairs();

 double getHoursSurvived();

 bool isOutside();

 bool isFemale();

 void setFemale(bool isFemale);

 bool isZombie();

 bool isEquipped(InventoryItem item);

 bool isEquippedClothing(InventoryItem item);

 bool isAttachedItem(InventoryItem item);

 void faceThisObject(IsoObject object);

 void facePosition(int x, int y);

 void faceThisObjectAlt(IsoObject object);

 int getAlreadyReadPages(std::string_view fullType);

 void setAlreadyReadPages(std::string_view fullType, int pages);

 Safety getSafety();

 void setSafety(Safety safety);

 float getMeleeDelay();

 void setMeleeDelay(float delay);

 float getRecoilDelay();

 void setRecoilDelay(float recoilDelay);

 int getMaintenanceMod();

 float getHammerSoundMod();

 float getWeldingSoundMod();

 bool isGodMod();

 void setGodMod(bool b);

 BaseVehicle getVehicle();

 void setVehicle(BaseVehicle v);

 float getInventoryWeight();

 List<String> getKnownRecipes();

 bool isRecipeKnown(Recipe recipe);

 bool isRecipeKnown(std::string_view name);

 void addKnownMediaLine(std::string_view guid);

 void removeKnownMediaLine(std::string_view guid);

 void clearKnownMediaLines();

 bool isKnownMediaLine(std::string_view guid);

 long playSound(std::string_view file);

 long playSoundLocal(std::string_view file);

 void stopOrTriggerSound(long eventInstance);

 void addWorldSoundUnlessInvisible(int radius, int volume,
 bool bStressHumans);

 bool isKnownPoison(InventoryItem item);

 std::string getBedType();

 void setBedType(std::string_view bedType);

 PolygonalMap2.Path getPath2();

 void setPath2(PolygonalMap2.Path path);

 PathFindBehavior2 getPathFindBehavior2();

 IsoObject getBed();

 void setBed(IsoObject bed);

 bool isReading();

 void setReading(bool isReading);

 float getTimeSinceLastSmoke();

 void setTimeSinceLastSmoke(float timeSinceLastSmoke);

 bool isInvisible();

 void setInvisible(bool b);

 bool isDriving();

 bool isInARoom();

 bool isUnlimitedCarry();

 void setUnlimitedCarry(bool unlimitedCarry);

 bool isBuildCheat();

 void setBuildCheat(bool buildCheat);

 bool isFarmingCheat();

 void setFarmingCheat(bool b);

 bool isHealthCheat();

 void setHealthCheat(bool healthCheat);

 bool isMechanicsCheat();

 void setMechanicsCheat(bool mechanicsCheat);

 bool isMovablesCheat();

 void setMovablesCheat(bool b);

 bool isTimedActionInstantCheat();

 void setTimedActionInstantCheat(bool b);

 bool isTimedActionInstant();

 bool isShowAdminTag();

 void setShowAdminTag(bool showAdminTag);

 void reportEvent(std::string_view name);

 AnimatorDebugMonitor getDebugMonitor();

 void setDebugMonitor(AnimatorDebugMonitor monitor);

 bool isAiming();

 void resetBeardGrowingTime();

 void resetHairGrowingTime();
 }
} // namespace characters
} // namespace zombie
