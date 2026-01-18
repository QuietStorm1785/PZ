#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/InvalidParameterException.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/AlarmClockClothing.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/ComboItem.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/inventory/types/KeyRing.h"
#include "zombie/inventory/types/Literature.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/world/WorldDictionary.h"
#include "zombie/worldMap/MapDefinitions.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Item : public BaseScriptObject {
public:
 std::string clothingExtraSubmenu = nullptr;
 std::string DisplayName = nullptr;
 bool Hidden = false;
 bool CantEat = false;
 std::string Icon = "None";
 bool Medical = false;
 bool CannedFood = false;
 bool SurvivalGear = false;
 bool MechanicsItem = false;
 bool UseWorldItem = false;
 float ScaleWorldIcon = 1.0F;
 std::string CloseKillMove = nullptr;
 float WeaponLength = 0.4F;
 float ActualWeight = 1.0F;
 float WeightWet = 0.0F;
 float WeightEmpty = 0.0F;
 float HungerChange = 0.0F;
 float CriticalChance = 20.0F;
 int Count = 1;
 int DaysFresh = 1000000000;
 int DaysTotallyRotten = 1000000000;
 int MinutesToCook = 60;
 int MinutesToBurn = 120;
 bool IsCookable = false;
 std::string CookingSound = nullptr;
 float StressChange = 0.0F;
 float BoredomChange = 0.0F;
 float UnhappyChange = 0.0F;
 bool AlwaysWelcomeGift = false;
 std::string ReplaceOnDeplete = nullptr;
 bool Ranged = false;
 bool CanStoreWater = false;
 float MaxRange = 1.0F;
 float MinRange = 0.0F;
 float ThirstChange = 0.0F;
 float FatigueChange = 0.0F;
 float MinAngle = 1.0F;
 bool RequiresEquippedBothHands = false;
 float MaxDamage = 1.5F;
 float MinDamage = 0.0F;
 float MinimumSwingTime = 0.0F;
 std::string SwingSound = "BaseballBatSwing";
 std::string WeaponSprite;
 bool AngleFalloff = false;
 int SoundVolume = 0;
 float ToHitModifier = 1.0F;
 int SoundRadius = 0;
 float OtherCharacterVolumeBoost;
 public ArrayList<String> Categories = std::make_unique<ArrayList<>>();
 public ArrayList<String> Tags = std::make_unique<ArrayList<>>();
 std::string ImpactSound = "BaseballBatHit";
 float SwingTime = 1.0F;
 bool KnockBackOnNoDeath = true;
 bool SplatBloodOnNoDeath = false;
 float SwingAmountBeforeImpact = 0.0F;
 std::string AmmoType = nullptr;
 int maxAmmo = 0;
 std::string GunType = nullptr;
 int DoorDamage = 1;
 int ConditionLowerChance = 1000000;
 int ConditionMax = 10;
 bool CanBandage = false;
 std::string name;
 std::string moduleDotType;
 int MaxHitCount = 1000;
 bool UseSelf = false;
 bool OtherHandUse = false;
 std::string OtherHandRequire;
 std::string PhysicsObject;
 std::string SwingAnim = "Rifle";
 float WeaponWeight = 1.0F;
 float EnduranceChange = 0.0F;
 std::string IdleAnim = "Idle";
 std::string RunAnim = "Run";
 std::string attachmentType = nullptr;
 std::string makeUpType = nullptr;
 std::string consolidateOption = nullptr;
 public ArrayList<String> RequireInHandOrInventory = nullptr;
 std::string DoorHitSound = "BaseballBatHit";
 std::string ReplaceOnUse = nullptr;
 bool DangerousUncooked = false;
 bool Alcoholic = false;
 float PushBackMod = 1.0F;
 int SplatNumber = 2;
 float NPCSoundBoost = 1.0F;
 bool RangeFalloff = false;
 bool UseEndurance = true;
 bool MultipleHitConditionAffected = true;
 bool ShareDamage = true;
 bool ShareEndurance = false;
 bool CanBarricade = false;
 bool UseWhileEquipped = true;
 bool UseWhileUnequipped = false;
 int TicksPerEquipUse = 30;
 bool DisappearOnUse = true;
 float UseDelta = 0.03125F;
 bool AlwaysKnockdown = false;
 float EnduranceMod = 1.0F;
 float KnockdownMod = 1.0F;
 bool CantAttackWithLowestEndurance = false;
 std::string ReplaceOnUseOn = nullptr;
 std::string ReplaceTypes = nullptr;
 private HashMap<String, String> ReplaceTypesMap = nullptr;
 bool IsWaterSource = false;
 public ArrayList<String> attachmentsProvided = nullptr;
 std::string FoodType = nullptr;
 bool Poison = false;
 int PoisonDetectionLevel = nullptr;
 int PoisonPower = 0;
 KahluaTable DefaultModData = nullptr;
 bool IsAimedFirearm = false;
 bool IsAimedHandWeapon = false;
 bool CanStack = true;
 float AimingMod = 1.0F;
 int ProjectileCount = 1;
 float HitAngleMod = 0.0F;
 float SplatSize = 1.0F;
 float Temperature = 0.0F;
 int NumberOfPages = -1;
 int LvlSkillTrained = -1;
 int NumLevelsTrained = 1;
 std::string SkillTrained = "";
 int Capacity = 0;
 int WeightReduction = 0;
 std::string SubCategory = "";
 bool ActivatedItem = false;
 float LightStrength = 0.0F;
 bool TorchCone = false;
 int LightDistance = 0;
 std::string CanBeEquipped = "";
 bool TwoHandWeapon = false;
 std::string CustomContextMenu = nullptr;
 std::string Tooltip = nullptr;
 public List<String> ReplaceOnCooked = nullptr;
 std::string DisplayCategory = nullptr;
 bool Trap = false;
 bool OBSOLETE = false;
 bool FishingLure = false;
 bool canBeWrite = false;
 int AimingPerkCritModifier = 0;
 float AimingPerkRangeModifier = 0.0F;
 float AimingPerkHitChanceModifier = 0.0F;
 int HitChance = 0;
 float AimingPerkMinAngleModifier = 0.0F;
 int RecoilDelay = 0;
 bool PiercingBullets = false;
 float SoundGain = 1.0F;
 bool ProtectFromRainWhenEquipped = false;
 float maxRangeModifier = 0.0F;
 float minRangeRangedModifier = 0.0F;
 float damageModifier = 0.0F;
 float recoilDelayModifier = 0.0F;
 int clipSizeModifier = 0;
 private ArrayList<String> mountOn = nullptr;
 std::string partType = nullptr;
 int ClipSize = 0;
 int reloadTime = 0;
 int reloadTimeModifier = 0;
 int aimingTime = 0;
 int aimingTimeModifier = 0;
 int hitChanceModifier = 0;
 float angleModifier = 0.0F;
 float weightModifier = 0.0F;
 int PageToWrite = 0;
 bool RemoveNegativeEffectOnCooked = false;
 int treeDamage = 0;
 float alcoholPower = 0.0F;
 std::string PutInSound = nullptr;
 std::string PlaceOneSound = nullptr;
 std::string PlaceMultipleSound = nullptr;
 std::string OpenSound = nullptr;
 std::string CloseSound = nullptr;
 std::string breakSound = nullptr;
 std::string customEatSound = nullptr;
 std::string fillFromDispenserSound = nullptr;
 std::string fillFromTapSound = nullptr;
 std::string bulletOutSound = nullptr;
 std::string ShellFallSound = nullptr;
 private HashMap<String, String> SoundMap = nullptr;
 float bandagePower = 0.0F;
 float ReduceInfectionPower = 0.0F;
 std::string OnCooked = nullptr;
 std::string OnlyAcceptCategory = nullptr;
 std::string AcceptItemFunction = nullptr;
 bool padlock = false;
 bool digitalPadlock = false;
 private List<String> teachedRecipes = nullptr;
 int triggerExplosionTimer = 0;
 bool canBePlaced = false;
 int explosionRange = 0;
 int explosionPower = 0;
 int fireRange = 0;
 int firePower = 0;
 int smokeRange = 0;
 int noiseRange = 0;
 int noiseDuration = 0;
 float extraDamage = 0.0F;
 int explosionTimer = 0;
 std::string PlacedSprite = nullptr;
 bool canBeReused = false;
 int sensorRange = 0;
 bool canBeRemote = false;
 bool remoteController = false;
 int remoteRange = 0;
 std::string countDownSound = nullptr;
 std::string explosionSound = nullptr;
 int fluReduction = 0;
 int ReduceFoodSickness = 0;
 int painReduction = 0;
 float rainFactor = 0.0F;
 float torchDot = 0.96F;
 int colorRed = 255;
 int colorGreen = 255;
 int colorBlue = 255;
 bool twoWay = false;
 int transmitRange = 0;
 int micRange = 0;
 float baseVolumeRange = 0.0F;
 bool isPortable = false;
 bool isTelevision = false;
 int minChannel = 88000;
 int maxChannel = 108000;
 bool usesBattery = false;
 bool isHighTier = false;
 std::string HerbalistType;
 float carbohydrates = 0.0F;
 float lipids = 0.0F;
 float proteins = 0.0F;
 float calories = 0.0F;
 bool packaged = false;
 bool cantBeFrozen = false;
 std::string evolvedRecipeName = nullptr;
 std::string ReplaceOnRotten = nullptr;
 float metalValue = 0.0F;
 std::string AlarmSound = nullptr;
 std::string itemWhenDry = nullptr;
 float wetCooldown = 0.0F;
 bool isWet = false;
 std::string onEat = nullptr;
 bool cantBeConsolided = false;
 bool BadInMicrowave = false;
 bool GoodHot = false;
 bool BadCold = false;
 std::string map = nullptr;
 bool keepOnDeplete = false;
 int vehicleType = 0;
 int maxCapacity = -1;
 int itemCapacity = -1;
 bool ConditionAffectsCapacity = false;
 float brakeForce = 0.0F;
 int chanceToSpawnDamaged = 0;
 float conditionLowerNormal = 0.0F;
 float conditionLowerOffroad = 0.0F;
 float wheelFriction = 0.0F;
 float suspensionDamping = 0.0F;
 float suspensionCompression = 0.0F;
 float engineLoudness = 0.0F;
 std::string ClothingItem = nullptr;
 ClothingItem clothingItemAsset = nullptr;
 std::string staticModel = nullptr;
 std::string primaryAnimMask = nullptr;
 std::string secondaryAnimMask = nullptr;
 std::string primaryAnimMaskAttachment = nullptr;
 std::string secondaryAnimMaskAttachment = nullptr;
 std::string replaceInSecondHand = nullptr;
 std::string replaceInPrimaryHand = nullptr;
 std::string replaceWhenUnequip = nullptr;
 ItemReplacement replacePrimaryHand = nullptr;
 ItemReplacement replaceSecondHand = nullptr;
 std::string worldObjectSprite = nullptr;
 std::string ItemName;
 Texture NormalTexture;
 public List<Texture> SpecialTextures = std::make_unique<ArrayList<>>();
 public List<String> SpecialWorldTextureNames = std::make_unique<ArrayList<>>();
 std::string WorldTextureName;
 Texture WorldTexture;
 std::string eatType;
 private ArrayList<String> IconsForTexture;
 float baseSpeed = 1.0F;
 private ArrayList<BloodClothingType> bloodClothingType;
 float stompPower = 1.0F;
 float runSpeedModifier = 1.0F;
 float combatSpeedModifier = 1.0F;
 public ArrayList<String> clothingItemExtra;
 public ArrayList<String> clothingItemExtraOption;
 bool removeOnBroken = false;
 bool canHaveHoles = true;
 bool cosmetic = false;
 std::string ammoBox = nullptr;
 bool hairDye = false;
 std::string insertAmmoStartSound = nullptr;
 std::string insertAmmoSound = nullptr;
 std::string insertAmmoStopSound = nullptr;
 std::string ejectAmmoStartSound = nullptr;
 std::string ejectAmmoSound = nullptr;
 std::string ejectAmmoStopSound = nullptr;
 std::string rackSound = nullptr;
 std::string clickSound = "Stormy9mmClick";
 std::string equipSound = nullptr;
 std::string unequipSound = nullptr;
 std::string bringToBearSound = nullptr;
 std::string magazineType = nullptr;
 std::string weaponReloadType = nullptr;
 bool rackAfterShoot = false;
 float jamGunChance = 1.0F;
 private ArrayList<ModelWeaponPart> modelWeaponPart = nullptr;
 bool haveChamber = true;
 bool manuallyRemoveSpentRounds = false;
 float biteDefense = 0.0F;
 float scratchDefense = 0.0F;
 float bulletDefense = 0.0F;
 std::string damageCategory = nullptr;
 bool damageMakeHole = false;
 float neckProtectionModifier = 1.0F;
 std::string attachmentReplacement = nullptr;
 bool insertAllBulletsReload = false;
 int chanceToFall = 0;
 std::string fabricType = nullptr;
 bool equippedNoSprint = false;
 std::string worldStaticModel = nullptr;
 float critDmgMultiplier = 0.0F;
 float insulation = 0.0F;
 float windresist = 0.0F;
 float waterresist = 0.0F;
 std::string fireMode = nullptr;
 private ArrayList<String> fireModePossibilities = nullptr;
 bool RemoveUnhappinessWhenCooked = false;
 short registry_id = -1;
 bool existsAsVanilla = false;
 std::string modID;
 std::string fileAbsPath;
 float stopPower = 5.0F;
 std::string recordedMediaCat;
 uint8_t acceptMediaType = -1;
 bool noTransmit = false;
 bool worldRender = true;
 std::string LuaCreate = nullptr;
 private HashMap<String, String> soundParameterMap = nullptr;
 std::string HitSound = "BaseballBatHit";
 std::string hitFloorSound = "BatOnFloor";
 std::string BodyLocation = "";
 public Stack<String> PaletteChoices = std::make_unique<Stack<>>();
 std::string SpriteName = nullptr;
 std::string PalettesStart = "";
 public static HashMap<Integer, String> NetIDToItem = std::make_unique<HashMap<>>();
 public static HashMap<String, Integer> NetItemToID = std::make_unique<HashMap<>>();
 static int IDMax = 0;
 public Item.Type type = Item.Type.Normal;
 bool Spice = false;
 int UseForPoison;

 /**
 * @return the DisplayName
 */
 std::string getDisplayName() {
 return this->DisplayName;
 }

 /**
 * 
 * @param _DisplayName the DisplayName to set
 */
 void setDisplayName(const std::string& _DisplayName) {
 this->DisplayName = _DisplayName;
 }

 bool isHidden() {
 return this->Hidden;
 }

 std::string getDisplayCategory() {
 return this->DisplayCategory;
 }

 /**
 * @return the Icon
 */
 std::string getIcon() {
 return this->Icon;
 }

 /**
 * 
 * @param _Icon the Icon to set
 */
 void setIcon(const std::string& _Icon) {
 this->Icon = _Icon;
 }

 int getNoiseDuration() {
 return this->noiseDuration;
 }

 Texture getNormalTexture() {
 return this->NormalTexture;
 }

 int getNumberOfPages() {
 return this->NumberOfPages;
 }

 /**
 * @return the ActualWeight
 */
 float getActualWeight() {
 return this->ActualWeight;
 }

 /**
 * 
 * @param _ActualWeight the ActualWeight to set
 */
 void setActualWeight(float _ActualWeight) {
 this->ActualWeight = _ActualWeight;
 }

 float getWeightWet() {
 return this->WeightWet;
 }

 void setWeightWet(float weight) {
 this->WeightWet = weight;
 }

 /**
 * @return the EmptyWeight
 */
 float getWeightEmpty() {
 return this->WeightEmpty;
 }

 /**
 * 
 * @param weight the EmptyWeight to set
 */
 void setWeightEmpty(float weight) {
 this->WeightEmpty = weight;
 }

 /**
 * @return the HungerChange
 */
 float getHungerChange() {
 return this->HungerChange;
 }

 /**
 * 
 * @param _HungerChange the HungerChange to set
 */
 void setHungerChange(float _HungerChange) {
 this->HungerChange = _HungerChange;
 }

 float getThirstChange() {
 return this->ThirstChange;
 }

 void setThirstChange(float _ThirstChange) {
 this->ThirstChange = _ThirstChange;
 }

 /**
 * @return the Count
 */
 int getCount() {
 return this->Count;
 }

 /**
 * 
 * @param _Count the Count to set
 */
 void setCount(int _Count) {
 this->Count = _Count;
 }

 /**
 * @return the DaysFresh
 */
 int getDaysFresh() {
 return this->DaysFresh;
 }

 /**
 * 
 * @param _DaysFresh the DaysFresh to set
 */
 void setDaysFresh(int _DaysFresh) {
 this->DaysFresh = _DaysFresh;
 }

 /**
 * @return the DaysTotallyRotten
 */
 int getDaysTotallyRotten() {
 return this->DaysTotallyRotten;
 }

 /**
 * 
 * @param _DaysTotallyRotten the DaysTotallyRotten to set
 */
 void setDaysTotallyRotten(int _DaysTotallyRotten) {
 this->DaysTotallyRotten = _DaysTotallyRotten;
 }

 /**
 * @return the MinutesToCook
 */
 int getMinutesToCook() {
 return this->MinutesToCook;
 }

 /**
 * 
 * @param _MinutesToCook the MinutesToCook to set
 */
 void setMinutesToCook(int _MinutesToCook) {
 this->MinutesToCook = _MinutesToCook;
 }

 /**
 * @return the MinutesToBurn
 */
 int getMinutesToBurn() {
 return this->MinutesToBurn;
 }

 /**
 * 
 * @param _MinutesToBurn the MinutesToBurn to set
 */
 void setMinutesToBurn(int _MinutesToBurn) {
 this->MinutesToBurn = _MinutesToBurn;
 }

 /**
 * @return the IsCookable
 */
 bool isIsCookable() {
 return this->IsCookable;
 }

 /**
 * 
 * @param _IsCookable the IsCookable to set
 */
 void setIsCookable(bool _IsCookable) {
 this->IsCookable = _IsCookable;
 }

 std::string getCookingSound() {
 return this->CookingSound;
 }

 /**
 * @return the StressChange
 */
 float getStressChange() {
 return this->StressChange;
 }

 /**
 * 
 * @param _StressChange the StressChange to set
 */
 void setStressChange(float _StressChange) {
 this->StressChange = _StressChange;
 }

 /**
 * @return the BoredomChange
 */
 float getBoredomChange() {
 return this->BoredomChange;
 }

 /**
 * 
 * @param _BoredomChange the BoredomChange to set
 */
 void setBoredomChange(float _BoredomChange) {
 this->BoredomChange = _BoredomChange;
 }

 /**
 * @return the UnhappyChange
 */
 float getUnhappyChange() {
 return this->UnhappyChange;
 }

 /**
 * 
 * @param _UnhappyChange the UnhappyChange to set
 */
 void setUnhappyChange(float _UnhappyChange) {
 this->UnhappyChange = _UnhappyChange;
 }

 /**
 * @return the AlwaysWelcomeGift
 */
 bool isAlwaysWelcomeGift() {
 return this->AlwaysWelcomeGift;
 }

 /**
 * 
 * @param _AlwaysWelcomeGift the AlwaysWelcomeGift to set
 */
 void setAlwaysWelcomeGift(bool _AlwaysWelcomeGift) {
 this->AlwaysWelcomeGift = _AlwaysWelcomeGift;
 }

 /**
 * @return the Ranged
 */
 bool isRanged() {
 return this->Ranged;
 }

 bool getCanStoreWater() {
 return this->CanStoreWater;
 }

 /**
 * 
 * @param _Ranged the Ranged to set
 */
 void setRanged(bool _Ranged) {
 this->Ranged = _Ranged;
 }

 /**
 * @return the MaxRange
 */
 float getMaxRange() {
 return this->MaxRange;
 }

 /**
 * 
 * @param _MaxRange the MaxRange to set
 */
 void setMaxRange(float _MaxRange) {
 this->MaxRange = _MaxRange;
 }

 /**
 * @return the MinAngle
 */
 float getMinAngle() {
 return this->MinAngle;
 }

 /**
 * 
 * @param _MinAngle the MinAngle to set
 */
 void setMinAngle(float _MinAngle) {
 this->MinAngle = _MinAngle;
 }

 /**
 * @return the MaxDamage
 */
 float getMaxDamage() {
 return this->MaxDamage;
 }

 /**
 * 
 * @param _MaxDamage the MaxDamage to set
 */
 void setMaxDamage(float _MaxDamage) {
 this->MaxDamage = _MaxDamage;
 }

 /**
 * @return the MinDamage
 */
 float getMinDamage() {
 return this->MinDamage;
 }

 /**
 * 
 * @param _MinDamage the MinDamage to set
 */
 void setMinDamage(float _MinDamage) {
 this->MinDamage = _MinDamage;
 }

 /**
 * @return the MinimumSwingTime
 */
 float getMinimumSwingTime() {
 return this->MinimumSwingTime;
 }

 /**
 * 
 * @param _MinimumSwingTime the MinimumSwingTime to set
 */
 void setMinimumSwingTime(float _MinimumSwingTime) {
 this->MinimumSwingTime = _MinimumSwingTime;
 }

 /**
 * @return the SwingSound
 */
 std::string getSwingSound() {
 return this->SwingSound;
 }

 /**
 * 
 * @param _SwingSound the SwingSound to set
 */
 void setSwingSound(const std::string& _SwingSound) {
 this->SwingSound = _SwingSound;
 }

 /**
 * @return the WeaponSprite
 */
 std::string getWeaponSprite() {
 return this->WeaponSprite;
 }

 /**
 * 
 * @param _WeaponSprite the WeaponSprite to set
 */
 void setWeaponSprite(const std::string& _WeaponSprite) {
 this->WeaponSprite = _WeaponSprite;
 }

 /**
 * @return the AngleFalloff
 */
 bool isAngleFalloff() {
 return this->AngleFalloff;
 }

 /**
 * 
 * @param _AngleFalloff the AngleFalloff to set
 */
 void setAngleFalloff(bool _AngleFalloff) {
 this->AngleFalloff = _AngleFalloff;
 }

 /**
 * @return the SoundVolume
 */
 int getSoundVolume() {
 return this->SoundVolume;
 }

 /**
 * 
 * @param _SoundVolume the SoundVolume to set
 */
 void setSoundVolume(int _SoundVolume) {
 this->SoundVolume = _SoundVolume;
 }

 /**
 * @return the ToHitModifier
 */
 float getToHitModifier() {
 return this->ToHitModifier;
 }

 /**
 * 
 * @param _ToHitModifier the ToHitModifier to set
 */
 void setToHitModifier(float _ToHitModifier) {
 this->ToHitModifier = _ToHitModifier;
 }

 /**
 * @return the SoundRadius
 */
 int getSoundRadius() {
 return this->SoundRadius;
 }

 /**
 * 
 * @param _SoundRadius the SoundRadius to set
 */
 void setSoundRadius(int _SoundRadius) {
 this->SoundRadius = _SoundRadius;
 }

 /**
 * @return the OtherCharacterVolumeBoost
 */
 float getOtherCharacterVolumeBoost() {
 return this->OtherCharacterVolumeBoost;
 }

 /**
 * 
 * @param _OtherCharacterVolumeBoost the OtherCharacterVolumeBoost to set
 */
 void setOtherCharacterVolumeBoost(float _OtherCharacterVolumeBoost) {
 this->OtherCharacterVolumeBoost = _OtherCharacterVolumeBoost;
 }

 /**
 * @return the Categories
 */
 public ArrayList<String> getCategories() {
 return this->Categories;
 }

 /**
 * 
 * @param _Categories the Categories to set
 */
 void setCategories(ArrayList<String> _Categories) {
 this->Categories.clear();
 this->Categories.addAll(_Categories);
 }

 public ArrayList<String> getTags() {
 return this->Tags;
 }

 /**
 * @return the ImpactSound
 */
 std::string getImpactSound() {
 return this->ImpactSound;
 }

 /**
 * 
 * @param _ImpactSound the ImpactSound to set
 */
 void setImpactSound(const std::string& _ImpactSound) {
 this->ImpactSound = _ImpactSound;
 }

 /**
 * @return the SwingTime
 */
 float getSwingTime() {
 return this->SwingTime;
 }

 /**
 * 
 * @param _SwingTime the SwingTime to set
 */
 void setSwingTime(float _SwingTime) {
 this->SwingTime = _SwingTime;
 }

 /**
 * @return the KnockBackOnNoDeath
 */
 bool isKnockBackOnNoDeath() {
 return this->KnockBackOnNoDeath;
 }

 /**
 * 
 * @param _KnockBackOnNoDeath the KnockBackOnNoDeath to set
 */
 void setKnockBackOnNoDeath(bool _KnockBackOnNoDeath) {
 this->KnockBackOnNoDeath = _KnockBackOnNoDeath;
 }

 /**
 * @return the SplatBloodOnNoDeath
 */
 bool isSplatBloodOnNoDeath() {
 return this->SplatBloodOnNoDeath;
 }

 /**
 * 
 * @param _SplatBloodOnNoDeath the SplatBloodOnNoDeath to set
 */
 void setSplatBloodOnNoDeath(bool _SplatBloodOnNoDeath) {
 this->SplatBloodOnNoDeath = _SplatBloodOnNoDeath;
 }

 /**
 * @return the SwingAmountBeforeImpact
 */
 float getSwingAmountBeforeImpact() {
 return this->SwingAmountBeforeImpact;
 }

 /**
 * 
 * @param _SwingAmountBeforeImpact the SwingAmountBeforeImpact to set
 */
 void setSwingAmountBeforeImpact(float _SwingAmountBeforeImpact) {
 this->SwingAmountBeforeImpact = _SwingAmountBeforeImpact;
 }

 /**
 * @return the AmmoType
 */
 std::string getAmmoType() {
 return this->AmmoType;
 }

 /**
 * 
 * @param _AmmoType the AmmoType to set
 */
 void setAmmoType(const std::string& _AmmoType) {
 this->AmmoType = _AmmoType;
 }

 /**
 * @return the DoorDamage
 */
 int getDoorDamage() {
 return this->DoorDamage;
 }

 /**
 * 
 * @param _DoorDamage the DoorDamage to set
 */
 void setDoorDamage(int _DoorDamage) {
 this->DoorDamage = _DoorDamage;
 }

 /**
 * @return the ConditionLowerChance
 */
 int getConditionLowerChance() {
 return this->ConditionLowerChance;
 }

 /**
 * 
 * @param _ConditionLowerChance the ConditionLowerChance to set
 */
 void setConditionLowerChance(int _ConditionLowerChance) {
 this->ConditionLowerChance = _ConditionLowerChance;
 }

 /**
 * @return the ConditionMax
 */
 int getConditionMax() {
 return this->ConditionMax;
 }

 /**
 * 
 * @param _ConditionMax the ConditionMax to set
 */
 void setConditionMax(int _ConditionMax) {
 this->ConditionMax = _ConditionMax;
 }

 /**
 * @return the CanBandage
 */
 bool isCanBandage() {
 return this->CanBandage;
 }

 /**
 * 
 * @param _CanBandage the CanBandage to set
 */
 void setCanBandage(bool _CanBandage) {
 this->CanBandage = _CanBandage;
 }

 bool isCosmetic() {
 return this->cosmetic;
 }

 /**
 * @return the name
 */
 std::string getName() {
 return this->name;
 }

 std::string getModuleName() {
 return this->module.name;
 }

 std::string getFullName() {
 return this->moduleDotType;
 }

 /**
 * 
 * @param _name the name to set
 */
 void setName(const std::string& _name) {
 this->name = _name;
 this->moduleDotType = this->module.name + "." + _name;
 }

 /**
 * @return the MaxHitCount
 */
 int getMaxHitCount() {
 return this->MaxHitCount;
 }

 /**
 * 
 * @param _MaxHitCount the MaxHitCount to set
 */
 void setMaxHitCount(int _MaxHitCount) {
 this->MaxHitCount = _MaxHitCount;
 }

 /**
 * @return the UseSelf
 */
 bool isUseSelf() {
 return this->UseSelf;
 }

 /**
 * 
 * @param _UseSelf the UseSelf to set
 */
 void setUseSelf(bool _UseSelf) {
 this->UseSelf = _UseSelf;
 }

 /**
 * @return the OtherHandUse
 */
 bool isOtherHandUse() {
 return this->OtherHandUse;
 }

 /**
 * 
 * @param _OtherHandUse the OtherHandUse to set
 */
 void setOtherHandUse(bool _OtherHandUse) {
 this->OtherHandUse = _OtherHandUse;
 }

 /**
 * @return the OtherHandRequire
 */
 std::string getOtherHandRequire() {
 return this->OtherHandRequire;
 }

 /**
 * 
 * @param _OtherHandRequire the OtherHandRequire to set
 */
 void setOtherHandRequire(const std::string& _OtherHandRequire) {
 this->OtherHandRequire = _OtherHandRequire;
 }

 /**
 * @return the PhysicsObject
 */
 std::string getPhysicsObject() {
 return this->PhysicsObject;
 }

 /**
 * 
 * @param _PhysicsObject the PhysicsObject to set
 */
 void setPhysicsObject(const std::string& _PhysicsObject) {
 this->PhysicsObject = _PhysicsObject;
 }

 /**
 * @return the SwingAnim
 */
 std::string getSwingAnim() {
 return this->SwingAnim;
 }

 /**
 * 
 * @param _SwingAnim the SwingAnim to set
 */
 void setSwingAnim(const std::string& _SwingAnim) {
 this->SwingAnim = _SwingAnim;
 }

 /**
 * @return the WeaponWeight
 */
 float getWeaponWeight() {
 return this->WeaponWeight;
 }

 /**
 * 
 * @param _WeaponWeight the WeaponWeight to set
 */
 void setWeaponWeight(float _WeaponWeight) {
 this->WeaponWeight = _WeaponWeight;
 }

 /**
 * @return the EnduranceChange
 */
 float getEnduranceChange() {
 return this->EnduranceChange;
 }

 /**
 * 
 * @param _EnduranceChange the EnduranceChange to set
 */
 void setEnduranceChange(float _EnduranceChange) {
 this->EnduranceChange = _EnduranceChange;
 }

 std::string getBreakSound() {
 return this->breakSound;
 }

 std::string getBulletOutSound() {
 return this->bulletOutSound;
 }

 std::string getCloseSound() {
 return this->CloseSound;
 }

 std::string getClothingItem() {
 return this->ClothingItem;
 }

 void setClothingItemAsset(ClothingItem asset) {
 this->clothingItemAsset = asset;
 }

 ClothingItem getClothingItemAsset() {
 return this->clothingItemAsset;
 }

 public ArrayList<String> getClothingItemExtra() {
 return this->clothingItemExtra;
 }

 public ArrayList<String> getClothingItemExtraOption() {
 return this->clothingItemExtraOption;
 }

 std::string getFabricType() {
 return this->fabricType;
 }

 public ArrayList<String> getIconsForTexture() {
 return this->IconsForTexture;
 }

 std::string getCustomEatSound() {
 return this->customEatSound;
 }

 std::string getFillFromDispenserSound() {
 return this->fillFromDispenserSound;
 }

 std::string getFillFromTapSound() {
 return this->fillFromTapSound;
 }

 std::string getEatType() {
 return this->eatType;
 }

 std::string getCountDownSound() {
 return this->countDownSound;
 }

 std::string getBringToBearSound() {
 return this->bringToBearSound;
 }

 std::string getEjectAmmoStartSound() {
 return this->ejectAmmoStartSound;
 }

 std::string getEjectAmmoSound() {
 return this->ejectAmmoSound;
 }

 std::string getEjectAmmoStopSound() {
 return this->ejectAmmoStopSound;
 }

 std::string getInsertAmmoStartSound() {
 return this->insertAmmoStartSound;
 }

 std::string getInsertAmmoSound() {
 return this->insertAmmoSound;
 }

 std::string getInsertAmmoStopSound() {
 return this->insertAmmoStopSound;
 }

 std::string getEquipSound() {
 return this->equipSound;
 }

 std::string getUnequipSound() {
 return this->unequipSound;
 }

 std::string getExplosionSound() {
 return this->explosionSound;
 }

 std::string getStaticModel() {
 return this->staticModel;
 }

 std::string getOpenSound() {
 return this->OpenSound;
 }

 std::string getPutInSound() {
 return this->PutInSound;
 }

 std::string getPlaceOneSound() {
 return this->PlaceOneSound;
 }

 std::string getPlaceMultipleSound() {
 return this->PlaceMultipleSound;
 }

 std::string getShellFallSound() {
 return this->ShellFallSound;
 }

 std::string getSoundByID(const std::string& ID) {
 return this->SoundMap.empty() ? nullptr : this->SoundMap.getOrDefault(ID, nullptr);
 }

 std::string getSkillTrained() {
 return this->SkillTrained;
 }

 /**
 * @return the DoorHitSound
 */
 std::string getDoorHitSound() {
 return this->DoorHitSound;
 }

 /**
 * 
 * @param _DoorHitSound the DoorHitSound to set
 */
 void setDoorHitSound(const std::string& _DoorHitSound) {
 this->DoorHitSound = _DoorHitSound;
 }

 bool isManuallyRemoveSpentRounds() {
 return this->manuallyRemoveSpentRounds;
 }

 float getRainFactor() {
 return this->rainFactor;
 }

 /**
 * @return the ReplaceOnUse
 */
 std::string getReplaceOnUse() {
 return this->ReplaceOnUse;
 }

 /**
 * 
 * @param _ReplaceOnUse the ReplaceOnUse to set
 */
 void setReplaceOnUse(const std::string& _ReplaceOnUse) {
 this->ReplaceOnUse = _ReplaceOnUse;
 }

 std::string getReplaceOnDeplete() {
 return this->ReplaceOnDeplete;
 }

 void setReplaceOnDeplete(const std::string& _ReplaceOnDeplete) {
 this->ReplaceOnDeplete = _ReplaceOnDeplete;
 }

 std::string getReplaceTypes() {
 return this->ReplaceTypes;
 }

 public HashMap<String, String> getReplaceTypesMap() {
 return this->ReplaceTypesMap;
 }

 std::string getReplaceType(const std::string& key) {
 return this->ReplaceTypesMap.empty() ? nullptr : this->ReplaceTypesMap.get(key);
 }

 bool hasReplaceType(const std::string& key) {
 return this->getReplaceType(key) != nullptr;
 }

 /**
 * @return the DangerousUncooked
 */
 bool isDangerousUncooked() {
 return this->DangerousUncooked;
 }

 /**
 * 
 * @param _DangerousUncooked the DangerousUncooked to set
 */
 void setDangerousUncooked(bool _DangerousUncooked) {
 this->DangerousUncooked = _DangerousUncooked;
 }

 /**
 * @return the Alcoholic
 */
 bool isAlcoholic() {
 return this->Alcoholic;
 }

 /**
 * 
 * @param _Alcoholic the Alcoholic to set
 */
 void setAlcoholic(bool _Alcoholic) {
 this->Alcoholic = _Alcoholic;
 }

 /**
 * @return the PushBackMod
 */
 float getPushBackMod() {
 return this->PushBackMod;
 }

 /**
 * 
 * @param _PushBackMod the PushBackMod to set
 */
 void setPushBackMod(float _PushBackMod) {
 this->PushBackMod = _PushBackMod;
 }

 /**
 * @return the SplatNumber
 */
 int getSplatNumber() {
 return this->SplatNumber;
 }

 /**
 * 
 * @param _SplatNumber the SplatNumber to set
 */
 void setSplatNumber(int _SplatNumber) {
 this->SplatNumber = _SplatNumber;
 }

 /**
 * @return the NPCSoundBoost
 */
 float getNPCSoundBoost() {
 return this->NPCSoundBoost;
 }

 /**
 * 
 * @param _NPCSoundBoost the NPCSoundBoost to set
 */
 void setNPCSoundBoost(float _NPCSoundBoost) {
 this->NPCSoundBoost = _NPCSoundBoost;
 }

 /**
 * @return the RangeFalloff
 */
 bool isRangeFalloff() {
 return this->RangeFalloff;
 }

 /**
 * 
 * @param _RangeFalloff the RangeFalloff to set
 */
 void setRangeFalloff(bool _RangeFalloff) {
 this->RangeFalloff = _RangeFalloff;
 }

 /**
 * @return the UseEndurance
 */
 bool isUseEndurance() {
 return this->UseEndurance;
 }

 /**
 * 
 * @param _UseEndurance the UseEndurance to set
 */
 void setUseEndurance(bool _UseEndurance) {
 this->UseEndurance = _UseEndurance;
 }

 /**
 * @return the MultipleHitConditionAffected
 */
 bool isMultipleHitConditionAffected() {
 return this->MultipleHitConditionAffected;
 }

 /**
 * 
 * @param _MultipleHitConditionAffected the MultipleHitConditionAffected to set
 */
 void setMultipleHitConditionAffected(bool _MultipleHitConditionAffected) {
 this->MultipleHitConditionAffected = _MultipleHitConditionAffected;
 }

 /**
 * @return the ShareDamage
 */
 bool isShareDamage() {
 return this->ShareDamage;
 }

 /**
 * 
 * @param _ShareDamage the ShareDamage to set
 */
 void setShareDamage(bool _ShareDamage) {
 this->ShareDamage = _ShareDamage;
 }

 /**
 * @return the ShareEndurance
 */
 bool isShareEndurance() {
 return this->ShareEndurance;
 }

 /**
 * 
 * @param _ShareEndurance the ShareEndurance to set
 */
 void setShareEndurance(bool _ShareEndurance) {
 this->ShareEndurance = _ShareEndurance;
 }

 /**
 * @return the CanBarricade
 */
 bool isCanBarricade() {
 return this->CanBarricade;
 }

 /**
 * 
 * @param _CanBarricade the CanBarricade to set
 */
 void setCanBarricade(bool _CanBarricade) {
 this->CanBarricade = _CanBarricade;
 }

 /**
 * @return the UseWhileEquipped
 */
 bool isUseWhileEquipped() {
 return this->UseWhileEquipped;
 }

 /**
 * 
 * @param _UseWhileEquipped the UseWhileEquipped to set
 */
 void setUseWhileEquipped(bool _UseWhileEquipped) {
 this->UseWhileEquipped = _UseWhileEquipped;
 }

 /**
 * @return the UseWhileUnequipped
 */
 bool isUseWhileUnequipped() {
 return this->UseWhileUnequipped;
 }

 /**
 * 
 * @param _UseWhileUnequipped the UseWhileUnequipped to set
 */
 void setUseWhileUnequipped(bool _UseWhileUnequipped) {
 this->UseWhileUnequipped = _UseWhileUnequipped;
 }

 /**
 * 
 * @param _TicksPerEquipUse the TicksPerEquipUse to set
 */
 void setTicksPerEquipUse(int _TicksPerEquipUse) {
 this->TicksPerEquipUse = _TicksPerEquipUse;
 }

 float getTicksPerEquipUse() {
 return this->TicksPerEquipUse;
 }

 /**
 * @return the DisappearOnUse
 */
 bool isDisappearOnUse() {
 return this->DisappearOnUse;
 }

 /**
 * 
 * @param _DisappearOnUse the DisappearOnUse to set
 */
 void setDisappearOnUse(bool _DisappearOnUse) {
 this->DisappearOnUse = _DisappearOnUse;
 }

 /**
 * @return the UseDelta
 */
 float getUseDelta() {
 return this->UseDelta;
 }

 /**
 * 
 * @param _UseDelta the UseDelta to set
 */
 void setUseDelta(float _UseDelta) {
 this->UseDelta = _UseDelta;
 }

 /**
 * @return the AlwaysKnockdown
 */
 bool isAlwaysKnockdown() {
 return this->AlwaysKnockdown;
 }

 /**
 * 
 * @param _AlwaysKnockdown the AlwaysKnockdown to set
 */
 void setAlwaysKnockdown(bool _AlwaysKnockdown) {
 this->AlwaysKnockdown = _AlwaysKnockdown;
 }

 /**
 * @return the EnduranceMod
 */
 float getEnduranceMod() {
 return this->EnduranceMod;
 }

 /**
 * 
 * @param _EnduranceMod the EnduranceMod to set
 */
 void setEnduranceMod(float _EnduranceMod) {
 this->EnduranceMod = _EnduranceMod;
 }

 /**
 * @return the KnockdownMod
 */
 float getKnockdownMod() {
 return this->KnockdownMod;
 }

 /**
 * 
 * @param _KnockdownMod the KnockdownMod to set
 */
 void setKnockdownMod(float _KnockdownMod) {
 this->KnockdownMod = _KnockdownMod;
 }

 /**
 * @return the CantAttackWithLowestEndurance
 */
 bool isCantAttackWithLowestEndurance() {
 return this->CantAttackWithLowestEndurance;
 }

 /**
 * 
 * @param _CantAttackWithLowestEndurance the CantAttackWithLowestEndurance to set
 */
 void setCantAttackWithLowestEndurance(bool _CantAttackWithLowestEndurance) {
 this->CantAttackWithLowestEndurance = _CantAttackWithLowestEndurance;
 }

 /**
 * @return the bodyLocation
 */
 std::string getBodyLocation() {
 return this->BodyLocation;
 }

 /**
 * 
 * @param bodyLocation the bodyLocation to set
 */
 void setBodyLocation(const std::string& bodyLocation) {
 this->BodyLocation = bodyLocation;
 }

 /**
 * @return the PaletteChoices
 */
 public Stack<String> getPaletteChoices() {
 return this->PaletteChoices;
 }

 /**
 * 
 * @param _PaletteChoices the PaletteChoices to set
 */
 void setPaletteChoices(Stack<String> _PaletteChoices) {
 this->PaletteChoices = _PaletteChoices;
 }

 /**
 * @return the SpriteName
 */
 std::string getSpriteName() {
 return this->SpriteName;
 }

 /**
 * 
 * @param _SpriteName the SpriteName to set
 */
 void setSpriteName(const std::string& _SpriteName) {
 this->SpriteName = _SpriteName;
 }

 /**
 * @return the PalettesStart
 */
 std::string getPalettesStart() {
 return this->PalettesStart;
 }

 /**
 * 
 * @param _PalettesStart the PalettesStart to set
 */
 void setPalettesStart(const std::string& _PalettesStart) {
 this->PalettesStart = _PalettesStart;
 }

 /**
 * @return the type
 */
 public Item.Type getType() {
 return this->type;
 }

 /**
 * 
 * @param _type the type to set
 */
 void setType(Item.Type _type) {
 this->type = _type;
 }

 std::string getTypeString() {
 return this->type.name();
 }

 std::string getMapID() {
 return this->map;
 }

 void Load(const std::string& string0, String[] strings0) {
 this->name = string0;
 this->moduleDotType = this->module.name + "." + string0;
 int int0 = IDMax++;
 NetIDToItem.put(int0, this->moduleDotType);
 NetItemToID.put(this->moduleDotType, int0);
 this->modID = ScriptManager.getCurrentLoadFileMod();
 if (this->modID == "pz-vanilla")) {
 this->existsAsVanilla = true;
 }

 this->fileAbsPath = ScriptManager.getCurrentLoadFileAbsPath();

 for (auto& string1 : strings0) this->DoParam(string1);
 }

 if (this->DisplayName.empty()) {
 this->DisplayName = this->getFullName();
 this->Hidden = true;
 }

 if (!StringUtils.isNullOrWhitespace(this->replaceInPrimaryHand) {
 String[] strings1 = this->replaceInPrimaryHand.trim().split("\\s+");
 if (strings1.length == 2) {
 this->replacePrimaryHand = std::make_unique<ItemReplacement>();
 this->replacePrimaryHand.clothingItemName = strings1[0].trim();
 this->replacePrimaryHand.maskVariableValue = strings1[1].trim();
 this->replacePrimaryHand.maskVariableName = "RightHandMask";
 }
 }

 if (!StringUtils.isNullOrWhitespace(this->replaceInSecondHand) {
 String[] strings2 = this->replaceInSecondHand.trim().split("\\s+");
 if (strings2.length == 2) {
 this->replaceSecondHand = std::make_unique<ItemReplacement>();
 this->replaceSecondHand.clothingItemName = strings2[0].trim();
 this->replaceSecondHand.maskVariableValue = strings2[1].trim();
 this->replaceSecondHand.maskVariableName = "LeftHandMask";
 }
 }

 if (!StringUtils.isNullOrWhitespace(this->primaryAnimMask) {
 this->replacePrimaryHand = std::make_unique<ItemReplacement>();
 this->replacePrimaryHand.maskVariableValue = this->primaryAnimMask;
 this->replacePrimaryHand.maskVariableName = "RightHandMask";
 this->replacePrimaryHand.attachment = this->primaryAnimMaskAttachment;
 }

 if (!StringUtils.isNullOrWhitespace(this->secondaryAnimMask) {
 this->replaceSecondHand = std::make_unique<ItemReplacement>();
 this->replaceSecondHand.maskVariableValue = this->secondaryAnimMask;
 this->replaceSecondHand.maskVariableName = "LeftHandMask";
 this->replaceSecondHand.attachment = this->secondaryAnimMaskAttachment;
 }

 WorldDictionary.onLoadItem(this);
 }

 InventoryItem InstanceItem(const std::string& param) {
 void* object = nullptr;
 if (this->type == Item.Type.Key) {
 object = new Key(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon);
 ((Key)object).setDigitalPadlock(this->digitalPadlock);
 ((Key)object).setPadlock(this->padlock);
 if (((Key)object).isPadlock()) {
 ((Key)object).setNumberOfKey(2);
 ((Key)object).setKeyId(Rand.Next(10000000);
 }
 }

 if (this->type == Item.Type.KeyRing) {
 object = new KeyRing(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon);
 }

 if (this->type == Item.Type.WeaponPart) {
 object = new WeaponPart(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon);
 WeaponPart weaponPart = (WeaponPart)object;
 weaponPart.setDamage(this->damageModifier);
 weaponPart.setClipSize(this->clipSizeModifier);
 weaponPart.setMaxRange(this->maxRangeModifier);
 weaponPart.setMinRangeRanged(this->minRangeRangedModifier);
 weaponPart.setRecoilDelay(this->recoilDelayModifier);
 weaponPart.setMountOn(this->mountOn);
 weaponPart.setPartType(this->partType);
 weaponPart.setReloadTime(this->reloadTimeModifier);
 weaponPart.setAimingTime(this->aimingTimeModifier);
 weaponPart.setHitChance(this->hitChanceModifier);
 weaponPart.setAngle(this->angleModifier);
 weaponPart.setWeightModifier(this->weightModifier);
 }

 if (this->type == Item.Type.Container) {
 object = new InventoryContainer(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon);
 InventoryContainer inventoryContainer = (InventoryContainer)object;
 inventoryContainer.setItemCapacity(this->Capacity);
 inventoryContainer.setCapacity(this->Capacity);
 inventoryContainer.setWeightReduction(this->WeightReduction);
 inventoryContainer.setCanBeEquipped(this->CanBeEquipped);
 inventoryContainer.getInventory().setPutSound(this->PutInSound);
 inventoryContainer.getInventory().setCloseSound(this->CloseSound);
 inventoryContainer.getInventory().setOpenSound(this->OpenSound);
 inventoryContainer.getInventory().setOnlyAcceptCategory(this->OnlyAcceptCategory);
 inventoryContainer.getInventory().setAcceptItemFunction(this->AcceptItemFunction);
 }

 if (this->type == Item.Type.Food) {
 object = new Food(this->module.name, this->DisplayName, this->name, this);
 Food food = (Food)object;
 food.Poison = this->Poison;
 food.setPoisonLevelForRecipe(this->PoisonDetectionLevel);
 food.setFoodType(this->FoodType);
 food.setPoisonPower(this->PoisonPower);
 food.setUseForPoison(this->UseForPoison);
 food.setThirstChange(this->ThirstChange / 100.0F);
 food.setHungChange(this->HungerChange / 100.0F);
 food.setBaseHunger(this->HungerChange / 100.0F);
 food.setEndChange(this->EnduranceChange / 100.0F);
 food.setOffAge(this->DaysFresh);
 food.setOffAgeMax(this->DaysTotallyRotten);
 food.setIsCookable(this->IsCookable);
 food.setMinutesToCook(this->MinutesToCook);
 food.setMinutesToBurn(this->MinutesToBurn);
 food.setbDangerousUncooked(this->DangerousUncooked);
 food.setReplaceOnUse(this->ReplaceOnUse);
 food.setReplaceOnCooked(this->ReplaceOnCooked);
 food.setSpice(this->Spice);
 food.setRemoveNegativeEffectOnCooked(this->RemoveNegativeEffectOnCooked);
 food.setCustomEatSound(this->customEatSound);
 food.setOnCooked(this->OnCooked);
 food.setFluReduction(this->fluReduction);
 food.setReduceFoodSickness(this->ReduceFoodSickness);
 food.setPainReduction(this->painReduction);
 food.setHerbalistType(this->HerbalistType);
 food.setCarbohydrates(this->carbohydrates);
 food.setLipids(this->lipids);
 food.setProteins(this->proteins);
 food.setCalories(this->calories);
 food.setPackaged(this->packaged);
 food.setCanBeFrozen(!this->cantBeFrozen);
 food.setReplaceOnRotten(this->ReplaceOnRotten);
 food.setOnEat(this->onEat);
 food.setBadInMicrowave(this->BadInMicrowave);
 food.setGoodHot(this->GoodHot);
 food.setBadCold(this->BadCold);
 }

 if (this->type == Item.Type.Literature) {
 object = new Literature(this->module.name, this->DisplayName, this->name, this);
 Literature literature = (Literature)object;
 literature.setReplaceOnUse(this->ReplaceOnUse);
 literature.setNumberOfPages(this->NumberOfPages);
 literature.setAlreadyReadPages(0);
 literature.setSkillTrained(this->SkillTrained);
 literature.setLvlSkillTrained(this->LvlSkillTrained);
 literature.setNumLevelsTrained(this->NumLevelsTrained);
 literature.setCanBeWrite(this->canBeWrite);
 literature.setPageToWrite(this->PageToWrite);
 literature.setTeachedRecipes(this->teachedRecipes);
 } else if (this->type == Item.Type.AlarmClock) {
 object = new AlarmClock(this->module.name, this->DisplayName, this->name, this);
 AlarmClock alarmClock = (AlarmClock)object;
 alarmClock.setAlarmSound(this->AlarmSound);
 alarmClock.setSoundRadius(this->SoundRadius);
 } else if (this->type == Item.Type.AlarmClockClothing) {
 std::string string0 = "";
 std::string string1 = nullptr;
 if (!this->PaletteChoices.empty() || param != nullptr) {
 int int0 = Rand.Next(this->PaletteChoices.size());
 string1 = this->PaletteChoices.get(int0);
 if (param != nullptr) {
 string1 = param;
 }

 string0 = "_" + string1.replace(this->PalettesStart, "");
 }

 object = new AlarmClockClothing(
 this->module.name, this->DisplayName, this->name, "Item_" + this->Icon.replace(".png", "") + string0, string1, this->SpriteName
 );
 AlarmClockClothing alarmClockClothing = (AlarmClockClothing)object;
 alarmClockClothing.setTemperature(this->Temperature);
 alarmClockClothing.setInsulation(this->insulation);
 alarmClockClothing.setConditionLowerChance(this->ConditionLowerChance);
 alarmClockClothing.setStompPower(this->stompPower);
 alarmClockClothing.setRunSpeedModifier(this->runSpeedModifier);
 alarmClockClothing.setCombatSpeedModifier(this->combatSpeedModifier);
 alarmClockClothing.setRemoveOnBroken(this->removeOnBroken);
 alarmClockClothing.setCanHaveHoles(this->canHaveHoles);
 alarmClockClothing.setWeightWet(this->WeightWet);
 alarmClockClothing.setBiteDefense(this->biteDefense);
 alarmClockClothing.setBulletDefense(this->bulletDefense);
 alarmClockClothing.setNeckProtectionModifier(this->neckProtectionModifier);
 alarmClockClothing.setScratchDefense(this->scratchDefense);
 alarmClockClothing.setChanceToFall(this->chanceToFall);
 alarmClockClothing.setWindresistance(this->windresist);
 alarmClockClothing.setWaterResistance(this->waterresist);
 alarmClockClothing.setAlarmSound(this->AlarmSound);
 alarmClockClothing.setSoundRadius(this->SoundRadius);
 } else if (this->type == Item.Type.Weapon) {
 object = new HandWeapon(this->module.name, this->DisplayName, this->name, this);
 HandWeapon weapon = (HandWeapon)object;
 weapon.setMultipleHitConditionAffected(this->MultipleHitConditionAffected);
 weapon.setConditionLowerChance(this->ConditionLowerChance);
 weapon.SplatSize = this->SplatSize;
 weapon.aimingMod = this->AimingMod;
 weapon.setMinDamage(this->MinDamage);
 weapon.setMaxDamage(this->MaxDamage);
 weapon.setBaseSpeed(this->baseSpeed);
 weapon.setPhysicsObject(this->PhysicsObject);
 weapon.setOtherHandRequire(this->OtherHandRequire);
 weapon.setOtherHandUse(this->OtherHandUse);
 weapon.setMaxRange(this->MaxRange);
 weapon.setMinRange(this->MinRange);
 weapon.setShareEndurance(this->ShareEndurance);
 weapon.setKnockdownMod(this->KnockdownMod);
 weapon.bIsAimedFirearm = this->IsAimedFirearm;
 weapon.RunAnim = this->RunAnim;
 weapon.IdleAnim = this->IdleAnim;
 weapon.HitAngleMod = (float)Math.toRadians(this->HitAngleMod);
 weapon.bIsAimedHandWeapon = this->IsAimedHandWeapon;
 weapon.setCantAttackWithLowestEndurance(this->CantAttackWithLowestEndurance);
 weapon.setAlwaysKnockdown(this->AlwaysKnockdown);
 weapon.setEnduranceMod(this->EnduranceMod);
 weapon.setUseSelf(this->UseSelf);
 weapon.setMaxHitCount(this->MaxHitCount);
 weapon.setMinimumSwingTime(this->MinimumSwingTime);
 weapon.setSwingTime(this->SwingTime);
 weapon.setDoSwingBeforeImpact(this->SwingAmountBeforeImpact);
 weapon.setMinAngle(this->MinAngle);
 weapon.setDoorDamage(this->DoorDamage);
 weapon.setTreeDamage(this->treeDamage);
 weapon.setDoorHitSound(this->DoorHitSound);
 weapon.setHitFloorSound(this->hitFloorSound);
 weapon.setZombieHitSound(this->HitSound);
 weapon.setPushBackMod(this->PushBackMod);
 weapon.setWeight(this->WeaponWeight);
 weapon.setImpactSound(this->ImpactSound);
 weapon.setSplatNumber(this->SplatNumber);
 weapon.setKnockBackOnNoDeath(this->KnockBackOnNoDeath);
 weapon.setSplatBloodOnNoDeath(this->SplatBloodOnNoDeath);
 weapon.setSwingSound(this->SwingSound);
 weapon.setBulletOutSound(this->bulletOutSound);
 weapon.setShellFallSound(this->ShellFallSound);
 weapon.setAngleFalloff(this->AngleFalloff);
 weapon.setSoundVolume(this->SoundVolume);
 weapon.setSoundRadius(this->SoundRadius);
 weapon.setToHitModifier(this->ToHitModifier);
 weapon.setOtherBoost(this->NPCSoundBoost);
 weapon.setRanged(this->Ranged);
 weapon.setRangeFalloff(this->RangeFalloff);
 weapon.setUseEndurance(this->UseEndurance);
 weapon.setCriticalChance(this->CriticalChance);
 weapon.setCritDmgMultiplier(this->critDmgMultiplier);
 weapon.setShareDamage(this->ShareDamage);
 weapon.setCanBarracade(this->CanBarricade);
 weapon.setWeaponSprite(this->WeaponSprite);
 weapon.setOriginalWeaponSprite(this->WeaponSprite);
 weapon.setSubCategory(this->SubCategory);
 weapon.setCategories(this->Categories);
 weapon.setSoundGain(this->SoundGain);
 weapon.setAimingPerkCritModifier(this->AimingPerkCritModifier);
 weapon.setAimingPerkRangeModifier(this->AimingPerkRangeModifier);
 weapon.setAimingPerkHitChanceModifier(this->AimingPerkHitChanceModifier);
 weapon.setHitChance(this->HitChance);
 weapon.setRecoilDelay(this->RecoilDelay);
 weapon.setAimingPerkMinAngleModifier(this->AimingPerkMinAngleModifier);
 weapon.setPiercingBullets(this->PiercingBullets);
 weapon.setClipSize(this->ClipSize);
 weapon.setReloadTime(this->reloadTime);
 weapon.setAimingTime(this->aimingTime);
 weapon.setTriggerExplosionTimer(this->triggerExplosionTimer);
 weapon.setSensorRange(this->sensorRange);
 weapon.setWeaponLength(this->WeaponLength);
 weapon.setPlacedSprite(this->PlacedSprite);
 weapon.setExplosionTimer(this->explosionTimer);
 weapon.setCanBePlaced(this->canBePlaced);
 weapon.setCanBeReused(this->canBeReused);
 weapon.setExplosionRange(this->explosionRange);
 weapon.setExplosionPower(this->explosionPower);
 weapon.setFireRange(this->fireRange);
 weapon.setFirePower(this->firePower);
 weapon.setSmokeRange(this->smokeRange);
 weapon.setNoiseRange(this->noiseRange);
 weapon.setExtraDamage(this->extraDamage);
 weapon.setAmmoBox(this->ammoBox);
 weapon.setRackSound(this->rackSound);
 weapon.setClickSound(this->clickSound);
 weapon.setMagazineType(this->magazineType);
 weapon.setWeaponReloadType(this->weaponReloadType);
 weapon.setInsertAllBulletsReload(this->insertAllBulletsReload);
 weapon.setRackAfterShoot(this->rackAfterShoot);
 weapon.setJamGunChance(this->jamGunChance);
 weapon.setModelWeaponPart(this->modelWeaponPart);
 weapon.setHaveChamber(this->haveChamber);
 weapon.setDamageCategory(this->damageCategory);
 weapon.setDamageMakeHole(this->damageMakeHole);
 weapon.setFireMode(this->fireMode);
 weapon.setFireModePossibilities(this->fireModePossibilities);
 } else if (this->type == Item.Type.Normal) {
 object = new ComboItem(this->module.name, this->DisplayName, this->name, this);
 } else if (this->type == Item.Type.Clothing) {
 std::string string2 = "";
 std::string string3 = nullptr;
 if (!this->PaletteChoices.empty() || param != nullptr) {
 int int1 = Rand.Next(this->PaletteChoices.size());
 string3 = this->PaletteChoices.get(int1);
 if (param != nullptr) {
 string3 = param;
 }

 string2 = "_" + string3.replace(this->PalettesStart, "");
 }

 object = new Clothing(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon.replace(".png", "") + string2, string3, this->SpriteName);
 Clothing clothing = (Clothing)object;
 clothing.setTemperature(this->Temperature);
 clothing.setInsulation(this->insulation);
 clothing.setConditionLowerChance(this->ConditionLowerChance);
 clothing.setStompPower(this->stompPower);
 clothing.setRunSpeedModifier(this->runSpeedModifier);
 clothing.setCombatSpeedModifier(this->combatSpeedModifier);
 clothing.setRemoveOnBroken(this->removeOnBroken);
 clothing.setCanHaveHoles(this->canHaveHoles);
 clothing.setWeightWet(this->WeightWet);
 clothing.setBiteDefense(this->biteDefense);
 clothing.setBulletDefense(this->bulletDefense);
 clothing.setNeckProtectionModifier(this->neckProtectionModifier);
 clothing.setScratchDefense(this->scratchDefense);
 clothing.setChanceToFall(this->chanceToFall);
 clothing.setWindresistance(this->windresist);
 clothing.setWaterResistance(this->waterresist);
 } else if (this->type == Item.Type.Drainable) {
 object = new DrainableComboItem(this->module.name, this->DisplayName, this->name, this);
 DrainableComboItem drainableComboItem = (DrainableComboItem)object;
 drainableComboItem.setUseWhileEquiped(this->UseWhileEquipped);
 drainableComboItem.setUseWhileUnequiped(this->UseWhileUnequipped);
 drainableComboItem.setTicksPerEquipUse(this->TicksPerEquipUse);
 drainableComboItem.setUseDelta(this->UseDelta);
 drainableComboItem.setReplaceOnDeplete(this->ReplaceOnDeplete);
 drainableComboItem.setIsCookable(this->IsCookable);
 drainableComboItem.setReplaceOnCooked(this->ReplaceOnCooked);
 drainableComboItem.setMinutesToCook(this->MinutesToCook);
 drainableComboItem.setOnCooked(this->OnCooked);
 drainableComboItem.setRainFactor(this->rainFactor);
 drainableComboItem.setCanConsolidate(!this->cantBeConsolided);
 drainableComboItem.setWeightEmpty(this->WeightEmpty);
 } else if (this->type == Item.Type.Radio) {
 object = new Radio(this->module.name, this->DisplayName, this->name, "Item_" + this->Icon);
 Radio radio = (Radio)object;
 DeviceData deviceData = radio.getDeviceData();
 if (deviceData != nullptr) {
 if (this->DisplayName != nullptr) {
 deviceData.setDeviceName(this->DisplayName);
 }

 deviceData.setIsTwoWay(this->twoWay);
 deviceData.setTransmitRange(this->transmitRange);
 deviceData.setMicRange(this->micRange);
 deviceData.setBaseVolumeRange(this->baseVolumeRange);
 deviceData.setIsPortable(this->isPortable);
 deviceData.setIsTelevision(this->isTelevision);
 deviceData.setMinChannelRange(this->minChannel);
 deviceData.setMaxChannelRange(this->maxChannel);
 deviceData.setIsBatteryPowered(this->usesBattery);
 deviceData.setIsHighTier(this->isHighTier);
 deviceData.setUseDelta(this->UseDelta);
 deviceData.setMediaType(this->acceptMediaType);
 deviceData.setNoTransmit(this->noTransmit);
 deviceData.generatePresets();
 deviceData.setRandomChannel();
 }

 if (!StringUtils.isNullOrWhitespace(this->worldObjectSprite) && !radio.ReadFromWorldSprite(this->worldObjectSprite) {
 DebugLog.log("Item -> Radio item = " + (this->moduleDotType != nullptr ? this->moduleDotType : "unknown"));
 }
 } else if (this->type == Item.Type.Moveable) {
 object = new Moveable(this->module.name, this->DisplayName, this->name, this);
 Moveable moveable = (Moveable)object;
 moveable.ReadFromWorldSprite(this->worldObjectSprite);
 this->ActualWeight = moveable.getActualWeight();
 } else if (this->type == Item.Type.Map) {
 MapItem mapItem = new MapItem(this->module.name, this->DisplayName, this->name, this);
 if (StringUtils.isNullOrWhitespace(this->map) {
 mapItem.setMapID(MapDefinitions.getInstance().pickRandom());
 } else {
 mapItem.setMapID(this->map);
 }

 object = mapItem;
 }

 if (this->colorRed < 255 || this->colorGreen < 255 || this->colorBlue < 255) {
 ((InventoryItem)object).setColor(new Color(this->colorRed / 255.0F, this->colorGreen / 255.0F, this->colorBlue / 255.0F);
 }

 ((InventoryItem)object).setAlcoholPower(this->alcoholPower);
 ((InventoryItem)object).setConditionMax(this->ConditionMax);
 ((InventoryItem)object).setCondition(this->ConditionMax);
 ((InventoryItem)object).setCanBeActivated(this->ActivatedItem);
 ((InventoryItem)object).setLightStrength(this->LightStrength);
 ((InventoryItem)object).setTorchCone(this->TorchCone);
 ((InventoryItem)object).setLightDistance(this->LightDistance);
 ((InventoryItem)object).setActualWeight(this->ActualWeight);
 ((InventoryItem)object).setWeight(this->ActualWeight);
 ((InventoryItem)object).setUses(this->Count);
 ((InventoryItem)object).setScriptItem(this);
 ((InventoryItem)object).setBoredomChange(this->BoredomChange);
 ((InventoryItem)object).setStressChange(this->StressChange / 100.0F);
 ((InventoryItem)object).setUnhappyChange(this->UnhappyChange);
 ((InventoryItem)object).setReplaceOnUseOn(this->ReplaceOnUseOn);
 ((InventoryItem)object).setRequireInHandOrInventory(this->RequireInHandOrInventory);
 ((InventoryItem)object).setAttachmentsProvided(this->attachmentsProvided);
 ((InventoryItem)object).setAttachmentReplacement(this->attachmentReplacement);
 ((InventoryItem)object).setIsWaterSource(this->IsWaterSource);
 ((InventoryItem)object).CanStoreWater = this->CanStoreWater;
 ((InventoryItem)object).CanStack = this->CanStack;
 ((InventoryItem)object).copyModData(this->DefaultModData);
 ((InventoryItem)object).setCount(this->Count);
 ((InventoryItem)object).setFatigueChange(this->FatigueChange / 100.0F);
 ((InventoryItem)object).setTooltip(this->Tooltip);
 ((InventoryItem)object).setDisplayCategory(this->DisplayCategory);
 ((InventoryItem)object).setAlcoholic(this->Alcoholic);
 ((InventoryItem)object).RequiresEquippedBothHands = this->RequiresEquippedBothHands;
 ((InventoryItem)object).setBreakSound(this->breakSound);
 ((InventoryItem)object).setReplaceOnUse(this->ReplaceOnUse);
 ((InventoryItem)object).setBandagePower(this->bandagePower);
 ((InventoryItem)object).setReduceInfectionPower(this->ReduceInfectionPower);
 ((InventoryItem)object).setCanBeRemote(this->canBeRemote);
 ((InventoryItem)object).setRemoteController(this->remoteController);
 ((InventoryItem)object).setRemoteRange(this->remoteRange);
 ((InventoryItem)object).setCountDownSound(this->countDownSound);
 ((InventoryItem)object).setExplosionSound(this->explosionSound);
 ((InventoryItem)object).setColorRed(this->colorRed / 255.0F);
 ((InventoryItem)object).setColorGreen(this->colorGreen / 255.0F);
 ((InventoryItem)object).setColorBlue(this->colorBlue / 255.0F);
 ((InventoryItem)object).setEvolvedRecipeName(this->evolvedRecipeName);
 ((InventoryItem)object).setMetalValue(this->metalValue);
 ((InventoryItem)object).setWet(this->isWet);
 ((InventoryItem)object).setWetCooldown(this->wetCooldown);
 ((InventoryItem)object).setItemWhenDry(this->itemWhenDry);
 ((InventoryItem)object).keepOnDeplete = this->keepOnDeplete;
 ((InventoryItem)object).setItemCapacity(this->itemCapacity);
 ((InventoryItem)object).setMaxCapacity(this->maxCapacity);
 ((InventoryItem)object).setBrakeForce(this->brakeForce);
 ((InventoryItem)object).setChanceToSpawnDamaged(this->chanceToSpawnDamaged);
 ((InventoryItem)object).setConditionLowerNormal(this->conditionLowerNormal);
 ((InventoryItem)object).setConditionLowerOffroad(this->conditionLowerOffroad);
 ((InventoryItem)object).setWheelFriction(this->wheelFriction);
 ((InventoryItem)object).setSuspensionCompression(this->suspensionCompression);
 ((InventoryItem)object).setEngineLoudness(this->engineLoudness);
 ((InventoryItem)object).setSuspensionDamping(this->suspensionDamping);
 if (this->CustomContextMenu != nullptr) {
 ((InventoryItem)object).setCustomMenuOption(Translator.getText("ContextMenu_" + this->CustomContextMenu);
 }

 if (this->IconsForTexture != nullptr && !this->IconsForTexture.empty()) {
 ((InventoryItem)object).setIconsForTexture(this->IconsForTexture);
 }

 ((InventoryItem)object).setBloodClothingType(this->bloodClothingType);
 ((InventoryItem)object).CloseKillMove = this->CloseKillMove;
 ((InventoryItem)object).setAmmoType(this->AmmoType);
 ((InventoryItem)object).setMaxAmmo(this->maxAmmo);
 ((InventoryItem)object).setGunType(this->GunType);
 ((InventoryItem)object).setAttachmentType(this->attachmentType);
 long long0 = OutfitRNG.getSeed();
 OutfitRNG.setSeed(Rand.Next(Integer.MAX_VALUE);
 ((InventoryItem)object).synchWithVisual();
 OutfitRNG.setSeed(long0);
 ((InventoryItem)object).setRegistry_id(this);
 Thread thread = Thread.currentThread();
 if ((thread == GameWindow.GameThread || thread == GameLoadingState.loader || thread == GameServer.MainThread)
 && !((InventoryItem)object).isInitialised()) {
 ((InventoryItem)object).initialiseItem();
 }

 return (InventoryItem)object;
 }

 void DoParam(const std::string& str) {
 if (str.trim().length() != 0) {
 try {
 String[] strings0 = str.split("=");
 std::string string0 = strings0[0].trim();
 std::string string1 = strings0[1].trim();
 if (string0.trim().equalsIgnoreCase("BodyLocation")) {
 this->BodyLocation = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("Palettes")) {
 String[] strings1 = string1.split("/");

 for (int int0 = 0; int0 < strings1.length; int0++) {
 this->PaletteChoices.add(strings1[int0].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("HitSound")) {
 this->HitSound = string1.trim();
 if (this->HitSound == "nullptr")) {
 this->HitSound = nullptr;
 }
 } else if (string0.trim().equalsIgnoreCase("HitFloorSound")) {
 this->hitFloorSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PalettesStart")) {
 this->PalettesStart = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("DisplayName")) {
 this->DisplayName = Translator.getDisplayItemName(string1.trim());
 this->DisplayName = Translator.getItemNameFromFullType(this->getFullName());
 } else if (string0.trim().equalsIgnoreCase("MetalValue")) {
 this->metalValue = new Float(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("SpriteName")) {
 this->SpriteName = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("Type")) {
 this->type = Item.Type.valueOf(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("SplatSize")) {
 this->SplatSize = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("CanStoreWater")) {
 this->CanStoreWater = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("IsWaterSource")) {
 this->IsWaterSource = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("Poison")) {
 this->Poison = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("FoodType")) {
 this->FoodType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PoisonDetectionLevel")) {
 this->PoisonDetectionLevel = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("PoisonPower")) {
 this->PoisonPower = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("UseForPoison")) {
 this->UseForPoison = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("SwingAnim")) {
 this->SwingAnim = string1;
 } else if (string0.trim().equalsIgnoreCase("Icon")) {
 this->Icon = string1;
 this->ItemName = "Item_" + this->Icon;
 this->NormalTexture = Texture.trygetTexture(this->ItemName);
 if (this->NormalTexture.empty()) {
 this->NormalTexture = Texture.getSharedTexture("media/inventory/Question_On.png");
 }

 this->WorldTextureName = this->ItemName.replace("Item_", "media/inventory/world/WItem_");
 this->WorldTextureName = this->WorldTextureName + ".png";
 this->WorldTexture = Texture.getSharedTexture(this->WorldTextureName);
 if (this->type == Item.Type.Food) {
 Texture texture0 = Texture.trygetTexture(this->ItemName + "Rotten");
 std::string string2 = this->WorldTextureName.replace(".png", "Rotten.png");
 if (texture0.empty()) {
 texture0 = Texture.trygetTexture(this->ItemName + "Spoiled");
 string2 = string2.replace("Rotten.png", "Spoiled.png");
 }

 this->SpecialWorldTextureNames.add(string2);
 this->SpecialTextures.add(texture0);
 this->SpecialTextures.add(Texture.trygetTexture(this->ItemName + "Cooked"));
 this->SpecialWorldTextureNames.add(this->WorldTextureName.replace(".png", "Cooked.png"));
 Texture texture1 = Texture.trygetTexture(this->ItemName + "Overdone");
 std::string string3 = this->WorldTextureName.replace(".png", "Overdone.png");
 if (texture1.empty()) {
 texture1 = Texture.trygetTexture(this->ItemName + "Burnt");
 string3 = string3.replace("Overdone.png", "Burnt.png");
 }

 this->SpecialTextures.add(texture1);
 this->SpecialWorldTextureNames.add(string3);
 }
 } else if (string0.trim().equalsIgnoreCase("UseWorldItem")) {
 this->UseWorldItem = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("Medical")) {
 this->Medical = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("CannedFood")) {
 this->CannedFood = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("MechanicsItem")) {
 this->MechanicsItem = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("SurvivalGear")) {
 this->SurvivalGear = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("ScaleWorldIcon")) {
 this->ScaleWorldIcon = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("HairDye")) {
 this->hairDye = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("DoorHitSound")) {
 this->DoorHitSound = string1;
 } else if (string0.trim().equalsIgnoreCase("Weight")) {
 this->ActualWeight = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("WeightWet")) {
 this->WeightWet = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("WeightEmpty")) {
 this->WeightEmpty = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("HungerChange")) {
 this->HungerChange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("ThirstChange")) {
 this->ThirstChange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("FatigueChange")) {
 this->FatigueChange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("EnduranceChange")) {
 this->EnduranceChange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("CriticalChance")) {
 this->CriticalChance = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("critDmgMultiplier")) {
 this->critDmgMultiplier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("DaysFresh")) {
 this->DaysFresh = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("DaysTotallyRotten")) {
 this->DaysTotallyRotten = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("IsCookable")) {
 this->IsCookable = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("CookingSound")) {
 this->CookingSound = string1;
 } else if (string0.trim().equalsIgnoreCase("MinutesToCook")) {
 this->MinutesToCook = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("MinutesToBurn")) {
 this->MinutesToBurn = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("BoredomChange")) {
 this->BoredomChange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("StressChange")) {
 this->StressChange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("UnhappyChange")) {
 this->UnhappyChange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("RemoveUnhappinessWhenCooked")) {
 this->RemoveUnhappinessWhenCooked = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("ReplaceOnDeplete")) {
 this->ReplaceOnDeplete = string1;
 } else if (string0.trim().equalsIgnoreCase("ReplaceOnUseOn")) {
 this->ReplaceOnUseOn = string1;
 if (string1.contains("-")) {
 String[] strings2 = string1.split("-");
 std::string string4 = strings2[0].trim();
 std::string string5 = strings2[1].trim();
 if (!string4.empty() && !string5.empty()) {
 if (this->ReplaceTypesMap.empty()) {
 this->ReplaceTypesMap = std::make_unique<HashMap<>>();
 }

 this->ReplaceTypesMap.put(string4, string5);
 }
 }
 } else if (string0.trim().equalsIgnoreCase("ReplaceTypes")) {
 this->ReplaceTypes = string1;
 String[] strings3 = string1.split(";");

 for (auto& string6 : strings3) String[] strings4 = string6.trim().split("\\s+");
 if (strings4.length == 2) {
 std::string string7 = strings4[0].trim();
 std::string string8 = strings4[1].trim();
 if (!string7.empty() && !string8.empty()) {
 if (this->ReplaceTypesMap.empty()) {
 this->ReplaceTypesMap = std::make_unique<HashMap<>>();
 }

 this->ReplaceTypesMap.put(string7, string8);
 }
 }
 }
 } else if (string0.trim().equalsIgnoreCase("Ranged")) {
 this->Ranged = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("UseSelf")) {
 this->UseSelf = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("OtherHandUse")) {
 this->OtherHandUse = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("DangerousUncooked")) {
 this->DangerousUncooked = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("MaxRange")) {
 this->MaxRange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MinRange")) {
 this->MinRange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MinAngle")) {
 this->MinAngle = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MaxDamage")) {
 this->MaxDamage = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("BaseSpeed")) {
 this->baseSpeed = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("stompPower")) {
 this->stompPower = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("combatSpeedModifier")) {
 this->combatSpeedModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("runSpeedModifier")) {
 this->runSpeedModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("clothingItemExtra")) {
 this->clothingItemExtra = std::make_unique<ArrayList<>>();
 String[] strings5 = string1.split(";");

 for (int int1 = 0; int1 < strings5.length; int1++) {
 this->clothingItemExtra.add(strings5[int1]);
 }
 } else if (string0.trim().equalsIgnoreCase("clothingExtraSubmenu")) {
 this->clothingExtraSubmenu = string1;
 } else if (string0.trim().equalsIgnoreCase("removeOnBroken")) {
 this->removeOnBroken = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("canHaveHoles")) {
 this->canHaveHoles = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("Cosmetic")) {
 this->cosmetic = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("ammoBox")) {
 this->ammoBox = string1;
 } else if (string0.trim().equalsIgnoreCase("InsertAmmoStartSound")) {
 this->insertAmmoStartSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("InsertAmmoSound")) {
 this->insertAmmoSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("InsertAmmoStopSound")) {
 this->insertAmmoStopSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("EjectAmmoStartSound")) {
 this->ejectAmmoStartSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("EjectAmmoSound")) {
 this->ejectAmmoSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("EjectAmmoStopSound")) {
 this->ejectAmmoStopSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("rackSound")) {
 this->rackSound = string1;
 } else if (string0.trim().equalsIgnoreCase("clickSound")) {
 this->clickSound = string1;
 } else if (string0.equalsIgnoreCase("BringToBearSound")) {
 this->bringToBearSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.equalsIgnoreCase("EquipSound")) {
 this->equipSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.equalsIgnoreCase("UnequipSound")) {
 this->unequipSound = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("magazineType")) {
 this->magazineType = string1;
 } else if (string0.trim().equalsIgnoreCase("jamGunChance")) {
 this->jamGunChance = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("modelWeaponPart")) {
 if (this->modelWeaponPart.empty()) {
 this->modelWeaponPart = std::make_unique<ArrayList<>>();
 }

 String[] strings6 = string1.split("\\s+");
 if (strings6.length >= 2 && strings6.length <= 4) {
 ModelWeaponPart modelWeaponPart0 = nullptr;

 for (int int2 = 0; int2 < this->modelWeaponPart.size(); int2++) {
 ModelWeaponPart modelWeaponPart1 = this->modelWeaponPart.get(int2);
 if (modelWeaponPart1.partType == strings6[0])) {
 modelWeaponPart0 = modelWeaponPart1;
 break;
 }
 }

 if (modelWeaponPart0.empty()) {
 modelWeaponPart0 = std::make_unique<ModelWeaponPart>();
 }

 modelWeaponPart0.partType = strings6[0];
 modelWeaponPart0.modelName = strings6[1];
 modelWeaponPart0.attachmentNameSelf = strings6.length > 2 ? strings6[2] : nullptr;
 modelWeaponPart0.attachmentParent = strings6.length > 3 ? strings6[3] : nullptr;
 if (!modelWeaponPart0.partType.contains(".")) {
 modelWeaponPart0.partType = this->module.name + "." + modelWeaponPart0.partType;
 }

 if (!modelWeaponPart0.modelName.contains(".")) {
 modelWeaponPart0.modelName = this->module.name + "." + modelWeaponPart0.modelName;
 }

 if ("none".equalsIgnoreCase(modelWeaponPart0.attachmentNameSelf) {
 modelWeaponPart0.attachmentNameSelf = nullptr;
 }

 if ("none".equalsIgnoreCase(modelWeaponPart0.attachmentParent) {
 modelWeaponPart0.attachmentParent = nullptr;
 }

 this->modelWeaponPart.add(modelWeaponPart0);
 }
 } else if (string0.trim().equalsIgnoreCase("rackAfterShoot")) {
 this->rackAfterShoot = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("haveChamber")) {
 this->haveChamber = Boolean.parseBoolean(string1);
 } else if (string0.equalsIgnoreCase("ManuallyRemoveSpentRounds")) {
 this->manuallyRemoveSpentRounds = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("biteDefense")) {
 this->biteDefense = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("bulletDefense")) {
 this->bulletDefense = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("neckProtectionModifier")) {
 this->neckProtectionModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("damageCategory")) {
 this->damageCategory = string1;
 } else if (string0.trim().equalsIgnoreCase("fireMode")) {
 this->fireMode = string1;
 } else if (string0.trim().equalsIgnoreCase("damageMakeHole")) {
 this->damageMakeHole = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("equippedNoSprint")) {
 this->equippedNoSprint = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("scratchDefense")) {
 this->scratchDefense = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("weaponReloadType")) {
 this->weaponReloadType = string1;
 } else if (string0.trim().equalsIgnoreCase("insertAllBulletsReload")) {
 this->insertAllBulletsReload = Boolean.parseBoolean(string1);
 } else if (string0.trim().equalsIgnoreCase("clothingItemExtraOption")) {
 this->clothingItemExtraOption = std::make_unique<ArrayList<>>();
 String[] strings7 = string1.split(";");

 for (int int3 = 0; int3 < strings7.length; int3++) {
 this->clothingItemExtraOption.add(strings7[int3]);
 }
 } else if (string0.trim().equalsIgnoreCase("ConditionLowerChanceOneIn")) {
 this->ConditionLowerChance = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("MultipleHitConditionAffected")) {
 this->MultipleHitConditionAffected = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("CanBandage")) {
 this->CanBandage = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ConditionMax")) {
 this->ConditionMax = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("SoundGain")) {
 this->SoundGain = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MinDamage")) {
 this->MinDamage = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MinimumSwingTime")) {
 this->MinimumSwingTime = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("SwingSound")) {
 this->SwingSound = string1;
 } else if (string0.trim().equalsIgnoreCase("ReplaceOnUse")) {
 this->ReplaceOnUse = string1;
 } else if (string0.trim().equalsIgnoreCase("WeaponSprite")) {
 this->WeaponSprite = string1;
 } else if (string0.trim().equalsIgnoreCase("AimingPerkCritModifier")) {
 this->AimingPerkCritModifier = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("AimingPerkRangeModifier")) {
 this->AimingPerkRangeModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("AimingPerkHitChanceModifier")) {
 this->AimingPerkHitChanceModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("AngleModifier")) {
 this->angleModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("WeightModifier")) {
 this->weightModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("AimingPerkMinAngleModifier")) {
 this->AimingPerkMinAngleModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("HitChance")) {
 this->HitChance = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("RecoilDelay")) {
 this->RecoilDelay = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("StopPower")) {
 this->stopPower = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("PiercingBullets")) {
 this->PiercingBullets = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("AngleFalloff")) {
 this->AngleFalloff = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("SoundVolume")) {
 this->SoundVolume = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ToHitModifier")) {
 this->ToHitModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("SoundRadius")) {
 this->SoundRadius = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("Categories")) {
 String[] strings8 = string1.split(";");

 for (int int4 = 0; int4 < strings8.length; int4++) {
 this->Categories.add(strings8[int4].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("Tags")) {
 String[] strings9 = string1.split(";");

 for (int int5 = 0; int5 < strings9.length; int5++) {
 this->Tags.add(strings9[int5].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("OtherCharacterVolumeBoost")) {
 this->OtherCharacterVolumeBoost = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("ImpactSound")) {
 this->ImpactSound = string1;
 if (this->ImpactSound == "nullptr")) {
 this->ImpactSound = nullptr;
 }
 } else if (string0.trim().equalsIgnoreCase("SwingTime")) {
 this->SwingTime = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("KnockBackOnNoDeath")) {
 this->KnockBackOnNoDeath = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("Alcoholic")) {
 this->Alcoholic = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("SplatBloodOnNoDeath")) {
 this->SplatBloodOnNoDeath = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("SwingAmountBeforeImpact")) {
 this->SwingAmountBeforeImpact = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("AmmoType")) {
 this->AmmoType = string1;
 } else if (string0.trim().equalsIgnoreCase("maxAmmo")) {
 this->maxAmmo = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("GunType")) {
 this->GunType = string1;
 } else if (string0.trim().equalsIgnoreCase("HitAngleMod")) {
 this->HitAngleMod = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("OtherHandRequire")) {
 this->OtherHandRequire = string1;
 } else if (string0.trim().equalsIgnoreCase("AlwaysWelcomeGift")) {
 this->AlwaysWelcomeGift = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("CantAttackWithLowestEndurance")) {
 this->CantAttackWithLowestEndurance = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("EnduranceMod")) {
 this->EnduranceMod = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("KnockdownMod")) {
 this->KnockdownMod = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("DoorDamage")) {
 this->DoorDamage = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("MaxHitCount")) {
 this->MaxHitCount = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("PhysicsObject")) {
 this->PhysicsObject = string1;
 } else if (string0.trim().equalsIgnoreCase("Count")) {
 this->Count = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("SwingAnim")) {
 this->SwingAnim = string1;
 } else if (string0.trim().equalsIgnoreCase("WeaponWeight")) {
 this->WeaponWeight = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("IdleAnim")) {
 this->IdleAnim = string1;
 } else if (string0.trim().equalsIgnoreCase("RunAnim")) {
 this->RunAnim = string1;
 } else if (string0.trim().equalsIgnoreCase("RequireInHandOrInventory")) {
 this->RequireInHandOrInventory = new ArrayList<>(Arrays.asList(string1.split("/")));
 } else if (string0.trim().equalsIgnoreCase("fireModePossibilities")) {
 this->fireModePossibilities = new ArrayList<>(Arrays.asList(string1.split("/")));
 } else if (string0.trim().equalsIgnoreCase("attachmentsProvided")) {
 this->attachmentsProvided = new ArrayList<>(Arrays.asList(string1.split(";")));
 } else if (string0.trim().equalsIgnoreCase("attachmentReplacement")) {
 this->attachmentReplacement = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PushBackMod")) {
 this->PushBackMod = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("NPCSoundBoost")) {
 this->NPCSoundBoost = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("SplatNumber")) {
 this->SplatNumber = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("RangeFalloff")) {
 this->RangeFalloff = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("UseEndurance")) {
 this->UseEndurance = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ShareDamage")) {
 this->ShareDamage = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ShareEndurance")) {
 this->ShareEndurance = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("AlwaysKnockdown")) {
 this->AlwaysKnockdown = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("IsAimedFirearm")) {
 this->IsAimedFirearm = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("bulletOutSound")) {
 this->bulletOutSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("ShellFallSound")) {
 this->ShellFallSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("SoundMap")) {
 String[] strings10 = string1.split("\\s+");
 if (strings10.length == 2 && !strings10[0].trim().empty()) {
 if (this->SoundMap.empty()) {
 this->SoundMap = std::make_unique<HashMap<>>();
 }

 this->SoundMap.put(strings10[0].trim(), strings10[1].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("IsAimedHandWeapon")) {
 this->IsAimedHandWeapon = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("AimingMod")) {
 this->AimingMod = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("ProjectileCount")) {
 this->ProjectileCount = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("CanStack")) {
 this->IsAimedFirearm = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("HerbalistType")) {
 this->HerbalistType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("CanBarricade")) {
 this->CanBarricade = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("UseWhileEquipped")) {
 this->UseWhileEquipped = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("UseWhileUnequipped")) {
 this->UseWhileUnequipped = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("TicksPerEquipUse")) {
 this->TicksPerEquipUse = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("DisappearOnUse")) {
 this->DisappearOnUse = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("Temperature")) {
 this->Temperature = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("Insulation")) {
 this->insulation = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("WindResistance")) {
 this->windresist = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("WaterResistance")) {
 this->waterresist = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("CloseKillMove")) {
 this->CloseKillMove = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("UseDelta")) {
 this->UseDelta = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("RainFactor")) {
 this->rainFactor = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("TorchDot")) {
 this->torchDot = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("NumberOfPages")) {
 this->NumberOfPages = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("SkillTrained")) {
 this->SkillTrained = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("LvlSkillTrained")) {
 this->LvlSkillTrained = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("NumLevelsTrained")) {
 this->NumLevelsTrained = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("Capacity")) {
 this->Capacity = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("MaxCapacity")) {
 this->maxCapacity = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ItemCapacity")) {
 this->itemCapacity = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ConditionAffectsCapacity")) {
 this->ConditionAffectsCapacity = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("BrakeForce")) {
 this->brakeForce = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ChanceToSpawnDamaged")) {
 this->chanceToSpawnDamaged = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("WeaponLength")) {
 this->WeaponLength = new Float(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ClipSize")) {
 this->ClipSize = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ReloadTime")) {
 this->reloadTime = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("AimingTime")) {
 this->aimingTime = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("AimingTimeModifier")) {
 this->aimingTimeModifier = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ReloadTimeModifier")) {
 this->reloadTimeModifier = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("HitChanceModifier")) {
 this->hitChanceModifier = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("WeightReduction")) {
 this->WeightReduction = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("CanBeEquipped")) {
 this->CanBeEquipped = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("SubCategory")) {
 this->SubCategory = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("ActivatedItem")) {
 this->ActivatedItem = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ProtectFromRainWhenEquipped")) {
 this->ProtectFromRainWhenEquipped = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("LightStrength")) {
 this->LightStrength = new Float(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("TorchCone")) {
 this->TorchCone = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("LightDistance")) {
 this->LightDistance = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("TwoHandWeapon")) {
 this->TwoHandWeapon = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("Tooltip")) {
 this->Tooltip = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("DisplayCategory")) {
 this->DisplayCategory = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("BadInMicrowave")) {
 this->BadInMicrowave = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("GoodHot")) {
 this->GoodHot = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("BadCold")) {
 this->BadCold = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("AlarmSound")) {
 this->AlarmSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("RequiresEquippedBothHands")) {
 this->RequiresEquippedBothHands = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ReplaceOnCooked")) {
 this->ReplaceOnCooked = Arrays.asList(string1.trim().split(";"));
 } else if (string0.trim().equalsIgnoreCase("CustomContextMenu")) {
 this->CustomContextMenu = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("Trap")) {
 this->Trap = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("Wet")) {
 this->isWet = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("WetCooldown")) {
 this->wetCooldown = Float.parseFloat(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ItemWhenDry")) {
 this->itemWhenDry = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("FishingLure")) {
 this->FishingLure = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("CanBeWrite")) {
 this->canBeWrite = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("PageToWrite")) {
 this->PageToWrite = Integer.parseInt(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("Spice")) {
 this->Spice = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("RemoveNegativeEffectOnCooked")) {
 this->RemoveNegativeEffectOnCooked = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("ClipSizeModifier")) {
 this->clipSizeModifier = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("RecoilDelayModifier")) {
 this->recoilDelayModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MaxRangeModifier")) {
 this->maxRangeModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("MinRangeModifier")) {
 this->minRangeRangedModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("DamageModifier")) {
 this->damageModifier = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("Map")) {
 this->map = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PutInSound")) {
 this->PutInSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PlaceOneSound")) {
 this->PlaceOneSound = StringUtils.discardNullOrWhitespace(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("PlaceMultipleSound")) {
 this->PlaceMultipleSound = StringUtils.discardNullOrWhitespace(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("CloseSound")) {
 this->CloseSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("OpenSound")) {
 this->OpenSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("BreakSound")) {
 this->breakSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("TreeDamage")) {
 this->treeDamage = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("CustomEatSound")) {
 this->customEatSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("FillFromDispenserSound")) {
 this->fillFromDispenserSound = StringUtils.discardNullOrWhitespace(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("FillFromTapSound")) {
 this->fillFromTapSound = StringUtils.discardNullOrWhitespace(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("AlcoholPower")) {
 this->alcoholPower = Float.parseFloat(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("BandagePower")) {
 this->bandagePower = Float.parseFloat(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("ReduceInfectionPower")) {
 this->ReduceInfectionPower = Float.parseFloat(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("OnCooked")) {
 this->OnCooked = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("OnlyAcceptCategory")) {
 this->OnlyAcceptCategory = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("AcceptItemFunction")) {
 this->AcceptItemFunction = StringUtils.discardNullOrWhitespace(string1);
 } else if (string0.trim().equalsIgnoreCase("Padlock")) {
 this->padlock = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("DigitalPadlock")) {
 this->digitalPadlock = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("triggerExplosionTimer")) {
 this->triggerExplosionTimer = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("sensorRange")) {
 this->sensorRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("remoteRange")) {
 this->remoteRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("CountDownSound")) {
 this->countDownSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("explosionSound")) {
 this->explosionSound = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("PlacedSprite")) {
 this->PlacedSprite = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("explosionTimer")) {
 this->explosionTimer = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("explosionRange")) {
 this->explosionRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("explosionPower")) {
 this->explosionPower = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("fireRange")) {
 this->fireRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("firePower")) {
 this->firePower = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("canBePlaced")) {
 this->canBePlaced = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("CanBeReused")) {
 this->canBeReused = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("canBeRemote")) {
 this->canBeRemote = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("remoteController")) {
 this->remoteController = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("smokeRange")) {
 this->smokeRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("noiseRange")) {
 this->noiseRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("noiseDuration")) {
 this->noiseDuration = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("extraDamage")) {
 this->extraDamage = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("TwoWay")) {
 this->twoWay = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("TransmitRange")) {
 this->transmitRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("MicRange")) {
 this->micRange = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("BaseVolumeRange")) {
 this->baseVolumeRange = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("IsPortable")) {
 this->isPortable = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("IsTelevision")) {
 this->isTelevision = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("MinChannel")) {
 this->minChannel = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("MaxChannel")) {
 this->maxChannel = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("UsesBattery")) {
 this->usesBattery = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("IsHighTier")) {
 this->isHighTier = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("WorldObjectSprite")) {
 this->worldObjectSprite = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("fluReduction")) {
 this->fluReduction = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ReduceFoodSickness")) {
 this->ReduceFoodSickness = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("painReduction")) {
 this->painReduction = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ColorRed")) {
 this->colorRed = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ColorGreen")) {
 this->colorGreen = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ColorBlue")) {
 this->colorBlue = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("calories")) {
 this->calories = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("carbohydrates")) {
 this->carbohydrates = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("lipids")) {
 this->lipids = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("proteins")) {
 this->proteins = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("Packaged")) {
 this->packaged = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("CantBeFrozen")) {
 this->cantBeFrozen = string1.trim().equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("EvolvedRecipeName")) {
 Translator.setDefaultItemEvolvedRecipeName(this->getFullName(), string1);
 this->evolvedRecipeName = Translator.getItemEvolvedRecipeName(this->getFullName());
 } else if (string0.trim().equalsIgnoreCase("ReplaceOnRotten")) {
 this->ReplaceOnRotten = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("CantBeConsolided")) {
 this->cantBeConsolided = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("OnEat")) {
 this->onEat = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("KeepOnDeplete")) {
 this->keepOnDeplete = string1.equalsIgnoreCase("true");
 } else if (string0.trim().equalsIgnoreCase("VehicleType")) {
 this->vehicleType = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("ChanceToFall")) {
 this->chanceToFall = Integer.parseInt(string1);
 } else if (string0.trim().equalsIgnoreCase("conditionLowerOffroad")) {
 this->conditionLowerOffroad = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("ConditionLowerStandard")) {
 this->conditionLowerNormal = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("wheelFriction")) {
 this->wheelFriction = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("suspensionDamping")) {
 this->suspensionDamping = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("suspensionCompression")) {
 this->suspensionCompression = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("engineLoudness")) {
 this->engineLoudness = Float.parseFloat(string1);
 } else if (string0.trim().equalsIgnoreCase("attachmentType")) {
 this->attachmentType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("makeUpType")) {
 this->makeUpType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("consolidateOption")) {
 this->consolidateOption = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("fabricType")) {
 this->fabricType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("TeachedRecipes")) {
 this->teachedRecipes = std::make_unique<ArrayList<>>();
 String[] strings11 = string1.split(";");

 for (int int6 = 0; int6 < strings11.length; int6++) {
 std::string string9 = strings11[int6].trim();
 this->teachedRecipes.add(string9);
 if (Translator.debug) {
 Translator.getRecipeName(string9);
 }
 }
 } else if (string0.trim().equalsIgnoreCase("MountOn")) {
 this->mountOn = std::make_unique<ArrayList<>>();
 String[] strings12 = string1.split(";");

 for (int int7 = 0; int7 < strings12.length; int7++) {
 this->mountOn.add(strings12[int7].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("PartType")) {
 this->partType = string1;
 } else if (string0.trim().equalsIgnoreCase("ClothingItem")) {
 this->ClothingItem = string1;
 } else if (string0.trim().equalsIgnoreCase("EvolvedRecipe")) {
 String[] strings13 = string1.split(";");

 for (int int8 = 0; int8 < strings13.length; int8++) {
 std::string string10 = strings13[int8];
 void* object = nullptr;
 int int9 = 0;
 bool boolean0 = false;
 if (!string10.contains(":")) {
 object = string10;
 } else {
 object = string10.split(":")[0];
 std::string string11 = string10.split(":")[1];
 if (!string11.contains("|")) {
 int9 = Integer.parseInt(string10.split(":")[1]);
 } else {
 String[] strings14 = string11.split("\\|");

 for (int int10 = 0; int10 < strings14.length; int10++) {
 if ("Cooked" == strings14[int10])) {
 boolean0 = true;
 }
 }

 int9 = Integer.parseInt(strings14[0]);
 }
 }

 ItemRecipe itemRecipe = new ItemRecipe(this->name, this->module.getName(), int9);
 EvolvedRecipe evolvedRecipe0 = nullptr;

 for (EvolvedRecipe evolvedRecipe1 : ScriptManager.instance.ModuleMap.get("Base").EvolvedRecipeMap) {
 if (evolvedRecipe1.name == object) {
 evolvedRecipe0 = evolvedRecipe1;
 break;
 }
 }

 itemRecipe.cooked = boolean0;
 if (evolvedRecipe0.empty()) {
 evolvedRecipe0 = new EvolvedRecipe((String)object);
 ScriptManager.instance.ModuleMap.get("Base").EvolvedRecipeMap.add(evolvedRecipe0);
 }

 evolvedRecipe0.itemsList.put(this->name, itemRecipe);
 }
 } else if (string0.trim().equalsIgnoreCase("StaticModel")) {
 this->staticModel = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("worldStaticModel")) {
 this->worldStaticModel = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("primaryAnimMask")) {
 this->primaryAnimMask = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("secondaryAnimMask")) {
 this->secondaryAnimMask = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("primaryAnimMaskAttachment")) {
 this->primaryAnimMaskAttachment = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("secondaryAnimMaskAttachment")) {
 this->secondaryAnimMaskAttachment = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("replaceInSecondHand")) {
 this->replaceInSecondHand = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("replaceInPrimaryHand")) {
 this->replaceInPrimaryHand = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("replaceWhenUnequip")) {
 this->replaceWhenUnequip = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("EatType")) {
 this->eatType = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("IconsForTexture")) {
 this->IconsForTexture = std::make_unique<ArrayList<>>();
 String[] strings15 = string1.split(";");

 for (int int11 = 0; int11 < strings15.length; int11++) {
 this->IconsForTexture.add(strings15[int11].trim());
 }
 } else if (string0.trim().equalsIgnoreCase("BloodLocation")) {
 this->bloodClothingType = std::make_unique<ArrayList<>>();
 String[] strings16 = string1.split(";");

 for (int int12 = 0; int12 < strings16.length; int12++) {
 this->bloodClothingType.add(BloodClothingType.fromString(strings16[int12].trim()));
 }
 } else if (string0.trim().equalsIgnoreCase("MediaCategory")) {
 this->recordedMediaCat = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("AcceptMediaType")) {
 this->acceptMediaType = Byte.parseByte(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("NoTransmit")) {
 this->noTransmit = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("WorldRender")) {
 this->worldRender = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("CantEat")) {
 this->CantEat = Boolean.parseBoolean(string1.trim());
 } else if (string0.trim().equalsIgnoreCase("OBSOLETE")) {
 this->OBSOLETE = string1.trim().toLowerCase() == "true");
 } else if (string0.trim().equalsIgnoreCase("OnCreate")) {
 this->LuaCreate = string1.trim();
 } else if (string0.trim().equalsIgnoreCase("SoundParameter")) {
 String[] strings17 = string1.split("\\s+");
 if (this->soundParameterMap.empty()) {
 this->soundParameterMap = std::make_unique<HashMap<>>();
 }

 this->soundParameterMap.put(strings17[0].trim(), strings17[1].trim());
 } else {
 DebugLog.log("adding unknown item param \"" + string0.trim() + "\" = \"" + string1.trim() + "\"");
 if (this->DefaultModData.empty()) {
 this->DefaultModData = LuaManager.platform.newTable();
 }

 try {
 double double0 = Double.parseDouble(string1.trim());
 this->DefaultModData.rawset(string0.trim(), double0);
 } catch (Exception exception0) {
 this->DefaultModData.rawset(string0.trim(), string1);
 }
 }
 } catch (Exception exception1) {
 throw InvalidParameterException("Error: " + str.trim() + " is not a valid parameter in item: " + this->name);
 }
 }
 }

 int getLevelSkillTrained() {
 return this->LvlSkillTrained;
 }

 int getNumLevelsTrained() {
 return this->NumLevelsTrained;
 }

 int getMaxLevelTrained() {
 return this->LvlSkillTrained == -1 ? -1 : this->LvlSkillTrained + this->NumLevelsTrained;
 }

 public List<String> getTeachedRecipes() {
 return this->teachedRecipes;
 }

 float getTemperature() {
 return this->Temperature;
 }

 void setTemperature(float temperature) {
 this->Temperature = temperature;
 }

 bool isConditionAffectsCapacity() {
 return this->ConditionAffectsCapacity;
 }

 int getChanceToFall() {
 return this->chanceToFall;
 }

 float getInsulation() {
 return this->insulation;
 }

 void setInsulation(float f) {
 this->insulation = f;
 }

 float getWindresist() {
 return this->windresist;
 }

 void setWindresist(float w) {
 this->windresist = w;
 }

 float getWaterresist() {
 return this->waterresist;
 }

 void setWaterresist(float w) {
 this->waterresist = w;
 }

 bool getObsolete() {
 return this->OBSOLETE;
 }

 std::string getAcceptItemFunction() {
 return this->AcceptItemFunction;
 }

 public ArrayList<BloodClothingType> getBloodClothingType() {
 return this->bloodClothingType;
 }

 std::string toString() {
 return this->getClass().getSimpleName()
 + "{Module: "
 + (this->module != nullptr ? this->module.name : "nullptr")
 + ", Name:"
 + this->name
 + ", Type:"
 + this->type
 + "}";
 }

 std::string getReplaceWhenUnequip() {
 return this->replaceWhenUnequip;
 }

 void resolveItemTypes() {
 this->AmmoType = ScriptManager.instance.resolveItemType(this->module, this->AmmoType);
 this->magazineType = ScriptManager.instance.resolveItemType(this->module, this->magazineType);
 if (this->RequireInHandOrInventory != nullptr) {
 for (int int0 = 0; int0 < this->RequireInHandOrInventory.size(); int0++) {
 std::string string0 = this->RequireInHandOrInventory.get(int0);
 string0 = ScriptManager.instance.resolveItemType(this->module, string0);
 this->RequireInHandOrInventory.set(int0, string0);
 }
 }

 if (this->ReplaceTypesMap != nullptr) {
 for (String string1 : this->ReplaceTypesMap.keySet()) {
 std::string string2 = this->ReplaceTypesMap.get(string1);
 this->ReplaceTypesMap.replace(string1, ScriptManager.instance.resolveItemType(this->module, string2);
 }
 }
 }

 void resolveModelScripts() {
 this->staticModel = ScriptManager.instance.resolveModelScript(this->module, this->staticModel);
 this->worldStaticModel = ScriptManager.instance.resolveModelScript(this->module, this->worldStaticModel);
 }

 short getRegistry_id() {
 return this->registry_id;
 }

 void setRegistry_id(short id) {
 if (this->registry_id != -1) {
 WorldDictionary.DebugPrintItem(id);
 throw RuntimeException(
 "Cannot override existing registry id ("
 + this->registry_id
 + ") to new id ("
 + id
 + "), item: "
 + (this->getFullName() != nullptr ? this->getFullName() : "unknown")
 );
 } else {
 this->registry_id = id;
 }
 }

 std::string getModID() {
 return this->modID;
 }

 bool getExistsAsVanilla() {
 return this->existsAsVanilla;
 }

 std::string getFileAbsPath() {
 return this->fileAbsPath;
 }

 void setModID(const std::string& modid) {
 if (GameClient.bClient) {
 if (this->modID.empty()) {
 this->modID = modid;
 } else if (!modid == this->modID) && Core.bDebug) {
 WorldDictionary.DebugPrintItem(this);
 throw RuntimeException("Cannot override modID. ModID=" + (modid != nullptr ? modid : "nullptr"));
 }
 }
 }

 std::string getRecordedMediaCat() {
 return this->recordedMediaCat;
 }

 bool isWorldRender() {
 return this->worldRender;
 }

 bool isCantEat() {
 return this->CantEat;
 }

 std::string getLuaCreate() {
 return this->LuaCreate;
 }

 void setLuaCreate(const std::string& functionName) {
 this->LuaCreate = functionName;
 }

 std::string getSoundParameter(const std::string& parameterName) {
 return this->soundParameterMap.empty() ? nullptr : this->soundParameterMap.get(parameterName);
 }

 public static enum Type {
 Normal,
 Weapon,
 Food,
 Literature,
 Drainable,
 Clothing,
 Container,
 WeaponPart,
 Key,
 KeyRing,
 Moveable,
 Radio,
 AlarmClock,
 AlarmClockClothing,
 Map;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
