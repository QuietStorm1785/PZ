#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter/PerkInfo.h"
#include "zombie/characters/IsoGameCharacter/XP.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
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
#include "zombie/vehicles/PolygonalMap2/Path.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>

namespace zombie {
namespace characters {


class ILuaGameCharacter {
public:
    virtual ~ILuaGameCharacter() = default;
   : public ILuaVariableSource,
   ILuaGameCharacterAttachedItems,
   ILuaGameCharacterDamage,
   ILuaGameCharacterClothing,
   ILuaGameCharacterHealth {
    std::string getFullName();

    SurvivorDesc getDescriptor();

    void setDescriptor(SurvivorDesc var1);

    bool isRangedWeaponEmpty();

    void setRangedWeaponEmpty(bool var1);

    BaseVisual getVisual();

    BaseCharacterSoundEmitter getEmitter();

    void resetModel();

    void resetModelNextFrame();

    IsoSpriteInstance getSpriteDef();

    bool hasItems(const std::string& var1, int var2);

    int getXpForLevel(int var1);

    XP getXp();

    bool isAsleep();

    void setAsleep(bool var1);

    int getZombieKills();

    void setForceWakeUpTime(float var1);

    ItemContainer getInventory();

    InventoryItem getPrimaryHandItem();

    void setPrimaryHandItem(InventoryItem var1);

    InventoryItem getSecondaryHandItem();

    void setSecondaryHandItem(InventoryItem var1);

    bool hasEquipped(const std::string& var1);

    bool hasEquippedTag(const std::string& var1);

    bool isHandItem(InventoryItem var1);

    bool isPrimaryHandItem(InventoryItem var1);

    bool isSecondaryHandItem(InventoryItem var1);

    bool isItemInBothHands(InventoryItem var1);

    bool removeFromHands(InventoryItem var1);

    void setSpeakColourInfo(ColorInfo var1);

    bool isSpeaking();

    Moodles getMoodles();

    Stats getStats();

    TraitCollection getTraits();

    int getMaxWeight();

    void PlayAnim(const std::string& var1);

    void PlayAnimWithSpeed(const std::string& var1, float var2);

    void PlayAnimUnlooped(const std::string& var1);

    void StartTimedActionAnim(const std::string& var1);

    void StartTimedActionAnim(const std::string& var1, const std::string& var2);

    void StopTimedActionAnim();

   std::stack<BaseAction> getCharacterActions();

    void StartAction(BaseAction var1);

    void StopAllActionQueue();

    int getPerkLevel(Perk var1);

    PerkInfo getPerkInfo(Perk var1);

    void setPerkLevelDebug(Perk var1, int var2);

    void LoseLevel(Perk var1);

    void LevelPerk(Perk var1, bool var2);

    void LevelPerk(Perk var1);

    void ReadLiterature(Literature var1);

    void setDir(IsoDirections var1);

    void Callout();

    bool IsSpeaking();

    void Say(const std::string& var1);

    void Say(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7);

    void setHaloNote(const std::string& var1);

    void setHaloNote(const std::string& var1, float var2);

    void setHaloNote(const std::string& var1, int var2, int var3, int var4, float var5);

    void initSpritePartsEmpty();

    bool HasTrait(const std::string& var1);

    void changeState(State var1);

    bool isCurrentState(State var1);

    State getCurrentState();

    void pathToLocation(int var1, int var2, int var3);

    void pathToLocationF(float var1, float var2, float var3);

    bool CanAttack();

    void smashCarWindow(VehiclePart var1);

    void smashWindow(IsoWindow var1);

    void openWindow(IsoWindow var1);

    void closeWindow(IsoWindow var1);

    void climbThroughWindow(IsoWindow var1);

    void climbThroughWindow(IsoWindow var1, int var2);

    void climbThroughWindowFrame(IsoObject var1);

    void climbSheetRope();

    void climbDownSheetRope();

    bool canClimbSheetRope(IsoGridSquare var1);

    bool canClimbDownSheetRopeInCurrentSquare();

    bool canClimbDownSheetRope(IsoGridSquare var1);

    void climbThroughWindow(IsoThumpable var1);

    void climbThroughWindow(IsoThumpable var1, int var2);

    void climbOverFence(IsoDirections var1);

    bool isAboveTopOfStairs();

    double getHoursSurvived();

    bool isOutside();

    bool isFemale();

    void setFemale(bool var1);

    bool isZombie();

    bool isEquipped(InventoryItem var1);

    bool isEquippedClothing(InventoryItem var1);

    bool isAttachedItem(InventoryItem var1);

    void faceThisObject(IsoObject var1);

    void facePosition(int var1, int var2);

    void faceThisObjectAlt(IsoObject var1);

    int getAlreadyReadPages(const std::string& var1);

    void setAlreadyReadPages(const std::string& var1, int var2);

    Safety getSafety();

    void setSafety(Safety var1);

    float getMeleeDelay();

    void setMeleeDelay(float var1);

    float getRecoilDelay();

    void setRecoilDelay(float var1);

    int getMaintenanceMod();

    float getHammerSoundMod();

    float getWeldingSoundMod();

    bool isGodMod();

    void setGodMod(bool var1);

    BaseVehicle getVehicle();

    void setVehicle(BaseVehicle var1);

    float getInventoryWeight();

   List<std::string> getKnownRecipes();

    bool isRecipeKnown(Recipe var1);

    bool isRecipeKnown(const std::string& var1);

    void addKnownMediaLine(const std::string& var1);

    void removeKnownMediaLine(const std::string& var1);

    void clearKnownMediaLines();

    bool isKnownMediaLine(const std::string& var1);

    long playSound(const std::string& var1);

    long playSoundLocal(const std::string& var1);

    void stopOrTriggerSound(long var1);

    void addWorldSoundUnlessInvisible(int var1, int var2, bool var3);

    bool isKnownPoison(InventoryItem var1);

    std::string getBedType();

    void setBedType(const std::string& var1);

    Path getPath2();

    void setPath2(Path var1);

    PathFindBehavior2 getPathFindBehavior2();

    IsoObject getBed();

    void setBed(IsoObject var1);

    bool isReading();

    void setReading(bool var1);

    float getTimeSinceLastSmoke();

    void setTimeSinceLastSmoke(float var1);

    bool isInvisible();

    void setInvisible(bool var1);

    bool isDriving();

    bool isInARoom();

    bool isUnlimitedCarry();

    void setUnlimitedCarry(bool var1);

    bool isBuildCheat();

    void setBuildCheat(bool var1);

    bool isFarmingCheat();

    void setFarmingCheat(bool var1);

    bool isHealthCheat();

    void setHealthCheat(bool var1);

    bool isMechanicsCheat();

    void setMechanicsCheat(bool var1);

    bool isMovablesCheat();

    void setMovablesCheat(bool var1);

    bool isTimedActionInstantCheat();

    void setTimedActionInstantCheat(bool var1);

    bool isTimedActionInstant();

    bool isShowAdminTag();

    void setShowAdminTag(bool var1);

    void reportEvent(const std::string& var1);

    AnimatorDebugMonitor getDebugMonitor();

    void setDebugMonitor(AnimatorDebugMonitor var1);

    bool isAiming();

    void resetBeardGrowingTime();

    void resetHairGrowingTime();
}
} // namespace characters
} // namespace zombie
