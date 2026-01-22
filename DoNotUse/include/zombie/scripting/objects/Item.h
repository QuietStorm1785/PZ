#pragma once
#include <stack>
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
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/util/StringUtils.h"
#include "zombie/world/WorldDictionary.h"
#include "zombie/worldMap/MapDefinitions.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


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
   public const std::vector<std::string> Categories = std::make_unique<std::vector<>>();
   public const std::vector<std::string> Tags = std::make_unique<std::vector<>>();
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
   public std::vector<std::string> RequireInHandOrInventory = nullptr;
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
   private std::unordered_map<std::string, std::string> ReplaceTypesMap = nullptr;
    bool IsWaterSource = false;
   public std::vector<std::string> attachmentsProvided = nullptr;
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
   public List<std::string> ReplaceOnCooked = nullptr;
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
   private std::vector<std::string> mountOn = nullptr;
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
   private std::unordered_map<std::string, std::string> SoundMap = nullptr;
    float bandagePower = 0.0F;
    float ReduceInfectionPower = 0.0F;
    std::string OnCooked = nullptr;
    std::string OnlyAcceptCategory = nullptr;
    std::string AcceptItemFunction = nullptr;
    bool padlock = false;
    bool digitalPadlock = false;
   private List<std::string> teachedRecipes = nullptr;
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
   public List<Texture> SpecialTextures = std::make_unique<std::vector<>>();
   public List<std::string> SpecialWorldTextureNames = std::make_unique<std::vector<>>();
    std::string WorldTextureName;
    Texture WorldTexture;
    std::string eatType;
   private std::vector<std::string> IconsForTexture;
    float baseSpeed = 1.0F;
   private std::vector<BloodClothingType> bloodClothingType;
    float stompPower = 1.0F;
    float runSpeedModifier = 1.0F;
    float combatSpeedModifier = 1.0F;
   public std::vector<std::string> clothingItemExtra;
   public std::vector<std::string> clothingItemExtraOption;
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
   private std::vector<ModelWeaponPart> modelWeaponPart = nullptr;
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
   private std::vector<std::string> fireModePossibilities = nullptr;
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
   private std::unordered_map<std::string, std::string> soundParameterMap = nullptr;
    std::string HitSound = "BaseballBatHit";
    std::string hitFloorSound = "BatOnFloor";
    std::string BodyLocation = "";
   public std::stack<std::string> PaletteChoices = std::make_unique<std::stack<>>();
    std::string SpriteName = nullptr;
    std::string PalettesStart = "";
   public static std::unordered_map<int, std::string> NetIDToItem = std::make_unique<std::unordered_map<>>();
   public static std::unordered_map<std::string, int> NetItemToID = std::make_unique<std::unordered_map<>>();
    static int IDMax = 0;
    Type type = Type.Normal;
    bool Spice = false;
    int UseForPoison;

    std::string getDisplayName() {
      return this.DisplayName;
   }

    void setDisplayName(const std::string& var1) {
      this.DisplayName = var1;
   }

    bool isHidden() {
      return this.Hidden;
   }

    std::string getDisplayCategory() {
      return this.DisplayCategory;
   }

    std::string getIcon() {
      return this.Icon;
   }

    void setIcon(const std::string& var1) {
      this.Icon = var1;
   }

    int getNoiseDuration() {
      return this.noiseDuration;
   }

    Texture getNormalTexture() {
      return this.NormalTexture;
   }

    int getNumberOfPages() {
      return this.NumberOfPages;
   }

    float getActualWeight() {
      return this.ActualWeight;
   }

    void setActualWeight(float var1) {
      this.ActualWeight = var1;
   }

    float getWeightWet() {
      return this.WeightWet;
   }

    void setWeightWet(float var1) {
      this.WeightWet = var1;
   }

    float getWeightEmpty() {
      return this.WeightEmpty;
   }

    void setWeightEmpty(float var1) {
      this.WeightEmpty = var1;
   }

    float getHungerChange() {
      return this.HungerChange;
   }

    void setHungerChange(float var1) {
      this.HungerChange = var1;
   }

    float getThirstChange() {
      return this.ThirstChange;
   }

    void setThirstChange(float var1) {
      this.ThirstChange = var1;
   }

    int getCount() {
      return this.Count;
   }

    void setCount(int var1) {
      this.Count = var1;
   }

    int getDaysFresh() {
      return this.DaysFresh;
   }

    void setDaysFresh(int var1) {
      this.DaysFresh = var1;
   }

    int getDaysTotallyRotten() {
      return this.DaysTotallyRotten;
   }

    void setDaysTotallyRotten(int var1) {
      this.DaysTotallyRotten = var1;
   }

    int getMinutesToCook() {
      return this.MinutesToCook;
   }

    void setMinutesToCook(int var1) {
      this.MinutesToCook = var1;
   }

    int getMinutesToBurn() {
      return this.MinutesToBurn;
   }

    void setMinutesToBurn(int var1) {
      this.MinutesToBurn = var1;
   }

    bool isIsCookable() {
      return this.IsCookable;
   }

    void setIsCookable(bool var1) {
      this.IsCookable = var1;
   }

    std::string getCookingSound() {
      return this.CookingSound;
   }

    float getStressChange() {
      return this.StressChange;
   }

    void setStressChange(float var1) {
      this.StressChange = var1;
   }

    float getBoredomChange() {
      return this.BoredomChange;
   }

    void setBoredomChange(float var1) {
      this.BoredomChange = var1;
   }

    float getUnhappyChange() {
      return this.UnhappyChange;
   }

    void setUnhappyChange(float var1) {
      this.UnhappyChange = var1;
   }

    bool isAlwaysWelcomeGift() {
      return this.AlwaysWelcomeGift;
   }

    void setAlwaysWelcomeGift(bool var1) {
      this.AlwaysWelcomeGift = var1;
   }

    bool isRanged() {
      return this.Ranged;
   }

    bool getCanStoreWater() {
      return this.CanStoreWater;
   }

    void setRanged(bool var1) {
      this.Ranged = var1;
   }

    float getMaxRange() {
      return this.MaxRange;
   }

    void setMaxRange(float var1) {
      this.MaxRange = var1;
   }

    float getMinAngle() {
      return this.MinAngle;
   }

    void setMinAngle(float var1) {
      this.MinAngle = var1;
   }

    float getMaxDamage() {
      return this.MaxDamage;
   }

    void setMaxDamage(float var1) {
      this.MaxDamage = var1;
   }

    float getMinDamage() {
      return this.MinDamage;
   }

    void setMinDamage(float var1) {
      this.MinDamage = var1;
   }

    float getMinimumSwingTime() {
      return this.MinimumSwingTime;
   }

    void setMinimumSwingTime(float var1) {
      this.MinimumSwingTime = var1;
   }

    std::string getSwingSound() {
      return this.SwingSound;
   }

    void setSwingSound(const std::string& var1) {
      this.SwingSound = var1;
   }

    std::string getWeaponSprite() {
      return this.WeaponSprite;
   }

    void setWeaponSprite(const std::string& var1) {
      this.WeaponSprite = var1;
   }

    bool isAngleFalloff() {
      return this.AngleFalloff;
   }

    void setAngleFalloff(bool var1) {
      this.AngleFalloff = var1;
   }

    int getSoundVolume() {
      return this.SoundVolume;
   }

    void setSoundVolume(int var1) {
      this.SoundVolume = var1;
   }

    float getToHitModifier() {
      return this.ToHitModifier;
   }

    void setToHitModifier(float var1) {
      this.ToHitModifier = var1;
   }

    int getSoundRadius() {
      return this.SoundRadius;
   }

    void setSoundRadius(int var1) {
      this.SoundRadius = var1;
   }

    float getOtherCharacterVolumeBoost() {
      return this.OtherCharacterVolumeBoost;
   }

    void setOtherCharacterVolumeBoost(float var1) {
      this.OtherCharacterVolumeBoost = var1;
   }

   public std::vector<std::string> getCategories() {
      return this.Categories;
   }

    void setCategories(std::vector<std::string> var1) {
      this.Categories.clear();
      this.Categories.addAll(var1);
   }

   public std::vector<std::string> getTags() {
      return this.Tags;
   }

    std::string getImpactSound() {
      return this.ImpactSound;
   }

    void setImpactSound(const std::string& var1) {
      this.ImpactSound = var1;
   }

    float getSwingTime() {
      return this.SwingTime;
   }

    void setSwingTime(float var1) {
      this.SwingTime = var1;
   }

    bool isKnockBackOnNoDeath() {
      return this.KnockBackOnNoDeath;
   }

    void setKnockBackOnNoDeath(bool var1) {
      this.KnockBackOnNoDeath = var1;
   }

    bool isSplatBloodOnNoDeath() {
      return this.SplatBloodOnNoDeath;
   }

    void setSplatBloodOnNoDeath(bool var1) {
      this.SplatBloodOnNoDeath = var1;
   }

    float getSwingAmountBeforeImpact() {
      return this.SwingAmountBeforeImpact;
   }

    void setSwingAmountBeforeImpact(float var1) {
      this.SwingAmountBeforeImpact = var1;
   }

    std::string getAmmoType() {
      return this.AmmoType;
   }

    void setAmmoType(const std::string& var1) {
      this.AmmoType = var1;
   }

    int getDoorDamage() {
      return this.DoorDamage;
   }

    void setDoorDamage(int var1) {
      this.DoorDamage = var1;
   }

    int getConditionLowerChance() {
      return this.ConditionLowerChance;
   }

    void setConditionLowerChance(int var1) {
      this.ConditionLowerChance = var1;
   }

    int getConditionMax() {
      return this.ConditionMax;
   }

    void setConditionMax(int var1) {
      this.ConditionMax = var1;
   }

    bool isCanBandage() {
      return this.CanBandage;
   }

    void setCanBandage(bool var1) {
      this.CanBandage = var1;
   }

    bool isCosmetic() {
      return this.cosmetic;
   }

    std::string getName() {
      return this.name;
   }

    std::string getModuleName() {
      return this.module.name;
   }

    std::string getFullName() {
      return this.moduleDotType;
   }

    void setName(const std::string& var1) {
      this.name = var1;
      this.moduleDotType = this.module.name + "." + var1;
   }

    int getMaxHitCount() {
      return this.MaxHitCount;
   }

    void setMaxHitCount(int var1) {
      this.MaxHitCount = var1;
   }

    bool isUseSelf() {
      return this.UseSelf;
   }

    void setUseSelf(bool var1) {
      this.UseSelf = var1;
   }

    bool isOtherHandUse() {
      return this.OtherHandUse;
   }

    void setOtherHandUse(bool var1) {
      this.OtherHandUse = var1;
   }

    std::string getOtherHandRequire() {
      return this.OtherHandRequire;
   }

    void setOtherHandRequire(const std::string& var1) {
      this.OtherHandRequire = var1;
   }

    std::string getPhysicsObject() {
      return this.PhysicsObject;
   }

    void setPhysicsObject(const std::string& var1) {
      this.PhysicsObject = var1;
   }

    std::string getSwingAnim() {
      return this.SwingAnim;
   }

    void setSwingAnim(const std::string& var1) {
      this.SwingAnim = var1;
   }

    float getWeaponWeight() {
      return this.WeaponWeight;
   }

    void setWeaponWeight(float var1) {
      this.WeaponWeight = var1;
   }

    float getEnduranceChange() {
      return this.EnduranceChange;
   }

    void setEnduranceChange(float var1) {
      this.EnduranceChange = var1;
   }

    std::string getBreakSound() {
      return this.breakSound;
   }

    std::string getBulletOutSound() {
      return this.bulletOutSound;
   }

    std::string getCloseSound() {
      return this.CloseSound;
   }

    std::string getClothingItem() {
      return this.ClothingItem;
   }

    void setClothingItemAsset(ClothingItem var1) {
      this.clothingItemAsset = var1;
   }

    ClothingItem getClothingItemAsset() {
      return this.clothingItemAsset;
   }

   public std::vector<std::string> getClothingItemExtra() {
      return this.clothingItemExtra;
   }

   public std::vector<std::string> getClothingItemExtraOption() {
      return this.clothingItemExtraOption;
   }

    std::string getFabricType() {
      return this.fabricType;
   }

   public std::vector<std::string> getIconsForTexture() {
      return this.IconsForTexture;
   }

    std::string getCustomEatSound() {
      return this.customEatSound;
   }

    std::string getFillFromDispenserSound() {
      return this.fillFromDispenserSound;
   }

    std::string getFillFromTapSound() {
      return this.fillFromTapSound;
   }

    std::string getEatType() {
      return this.eatType;
   }

    std::string getCountDownSound() {
      return this.countDownSound;
   }

    std::string getBringToBearSound() {
      return this.bringToBearSound;
   }

    std::string getEjectAmmoStartSound() {
      return this.ejectAmmoStartSound;
   }

    std::string getEjectAmmoSound() {
      return this.ejectAmmoSound;
   }

    std::string getEjectAmmoStopSound() {
      return this.ejectAmmoStopSound;
   }

    std::string getInsertAmmoStartSound() {
      return this.insertAmmoStartSound;
   }

    std::string getInsertAmmoSound() {
      return this.insertAmmoSound;
   }

    std::string getInsertAmmoStopSound() {
      return this.insertAmmoStopSound;
   }

    std::string getEquipSound() {
      return this.equipSound;
   }

    std::string getUnequipSound() {
      return this.unequipSound;
   }

    std::string getExplosionSound() {
      return this.explosionSound;
   }

    std::string getStaticModel() {
      return this.staticModel;
   }

    std::string getOpenSound() {
      return this.OpenSound;
   }

    std::string getPutInSound() {
      return this.PutInSound;
   }

    std::string getPlaceOneSound() {
      return this.PlaceOneSound;
   }

    std::string getPlaceMultipleSound() {
      return this.PlaceMultipleSound;
   }

    std::string getShellFallSound() {
      return this.ShellFallSound;
   }

    std::string getSoundByID(const std::string& var1) {
      return this.SoundMap == nullptr ? nullptr : this.SoundMap.getOrDefault(var1, nullptr);
   }

    std::string getSkillTrained() {
      return this.SkillTrained;
   }

    std::string getDoorHitSound() {
      return this.DoorHitSound;
   }

    void setDoorHitSound(const std::string& var1) {
      this.DoorHitSound = var1;
   }

    bool isManuallyRemoveSpentRounds() {
      return this.manuallyRemoveSpentRounds;
   }

    float getRainFactor() {
      return this.rainFactor;
   }

    std::string getReplaceOnUse() {
      return this.ReplaceOnUse;
   }

    void setReplaceOnUse(const std::string& var1) {
      this.ReplaceOnUse = var1;
   }

    std::string getReplaceOnDeplete() {
      return this.ReplaceOnDeplete;
   }

    void setReplaceOnDeplete(const std::string& var1) {
      this.ReplaceOnDeplete = var1;
   }

    std::string getReplaceTypes() {
      return this.ReplaceTypes;
   }

   public std::unordered_map<std::string, std::string> getReplaceTypesMap() {
      return this.ReplaceTypesMap;
   }

    std::string getReplaceType(const std::string& var1) {
      return this.ReplaceTypesMap == nullptr ? nullptr : this.ReplaceTypesMap.get(var1);
   }

    bool hasReplaceType(const std::string& var1) {
      return this.getReplaceType(var1) != nullptr;
   }

    bool isDangerousUncooked() {
      return this.DangerousUncooked;
   }

    void setDangerousUncooked(bool var1) {
      this.DangerousUncooked = var1;
   }

    bool isAlcoholic() {
      return this.Alcoholic;
   }

    void setAlcoholic(bool var1) {
      this.Alcoholic = var1;
   }

    float getPushBackMod() {
      return this.PushBackMod;
   }

    void setPushBackMod(float var1) {
      this.PushBackMod = var1;
   }

    int getSplatNumber() {
      return this.SplatNumber;
   }

    void setSplatNumber(int var1) {
      this.SplatNumber = var1;
   }

    float getNPCSoundBoost() {
      return this.NPCSoundBoost;
   }

    void setNPCSoundBoost(float var1) {
      this.NPCSoundBoost = var1;
   }

    bool isRangeFalloff() {
      return this.RangeFalloff;
   }

    void setRangeFalloff(bool var1) {
      this.RangeFalloff = var1;
   }

    bool isUseEndurance() {
      return this.UseEndurance;
   }

    void setUseEndurance(bool var1) {
      this.UseEndurance = var1;
   }

    bool isMultipleHitConditionAffected() {
      return this.MultipleHitConditionAffected;
   }

    void setMultipleHitConditionAffected(bool var1) {
      this.MultipleHitConditionAffected = var1;
   }

    bool isShareDamage() {
      return this.ShareDamage;
   }

    void setShareDamage(bool var1) {
      this.ShareDamage = var1;
   }

    bool isShareEndurance() {
      return this.ShareEndurance;
   }

    void setShareEndurance(bool var1) {
      this.ShareEndurance = var1;
   }

    bool isCanBarricade() {
      return this.CanBarricade;
   }

    void setCanBarricade(bool var1) {
      this.CanBarricade = var1;
   }

    bool isUseWhileEquipped() {
      return this.UseWhileEquipped;
   }

    void setUseWhileEquipped(bool var1) {
      this.UseWhileEquipped = var1;
   }

    bool isUseWhileUnequipped() {
      return this.UseWhileUnequipped;
   }

    void setUseWhileUnequipped(bool var1) {
      this.UseWhileUnequipped = var1;
   }

    void setTicksPerEquipUse(int var1) {
      this.TicksPerEquipUse = var1;
   }

    float getTicksPerEquipUse() {
      return this.TicksPerEquipUse;
   }

    bool isDisappearOnUse() {
      return this.DisappearOnUse;
   }

    void setDisappearOnUse(bool var1) {
      this.DisappearOnUse = var1;
   }

    float getUseDelta() {
      return this.UseDelta;
   }

    void setUseDelta(float var1) {
      this.UseDelta = var1;
   }

    bool isAlwaysKnockdown() {
      return this.AlwaysKnockdown;
   }

    void setAlwaysKnockdown(bool var1) {
      this.AlwaysKnockdown = var1;
   }

    float getEnduranceMod() {
      return this.EnduranceMod;
   }

    void setEnduranceMod(float var1) {
      this.EnduranceMod = var1;
   }

    float getKnockdownMod() {
      return this.KnockdownMod;
   }

    void setKnockdownMod(float var1) {
      this.KnockdownMod = var1;
   }

    bool isCantAttackWithLowestEndurance() {
      return this.CantAttackWithLowestEndurance;
   }

    void setCantAttackWithLowestEndurance(bool var1) {
      this.CantAttackWithLowestEndurance = var1;
   }

    std::string getBodyLocation() {
      return this.BodyLocation;
   }

    void setBodyLocation(const std::string& var1) {
      this.BodyLocation = var1;
   }

   public std::stack<std::string> getPaletteChoices() {
      return this.PaletteChoices;
   }

    void setPaletteChoices(std::stack<std::string> var1) {
      this.PaletteChoices = var1;
   }

    std::string getSpriteName() {
      return this.SpriteName;
   }

    void setSpriteName(const std::string& var1) {
      this.SpriteName = var1;
   }

    std::string getPalettesStart() {
      return this.PalettesStart;
   }

    void setPalettesStart(const std::string& var1) {
      this.PalettesStart = var1;
   }

    Type getType() {
      return this.type;
   }

    void setType(Type var1) {
      this.type = var1;
   }

    std::string getTypeString() {
      return this.type.name();
   }

    std::string getMapID() {
      return this.map;
   }

    void Load(const std::string& var1, std::string[] var2) {
      this.name = var1;
      this.moduleDotType = this.module.name + "." + var1;
    int var3 = IDMax++;
      NetIDToItem.put(var3, this.moduleDotType);
      NetItemToID.put(this.moduleDotType, var3);
      this.modID = ScriptManager.getCurrentLoadFileMod();
      if (this.modID == "pz-vanilla")) {
         this.existsAsVanilla = true;
      }

      this.fileAbsPath = ScriptManager.getCurrentLoadFileAbsPath();

    for (auto& var7 : var2)         this.DoParam(var7);
      }

      if (this.DisplayName == nullptr) {
         this.DisplayName = this.getFullName();
         this.Hidden = true;
      }

      if (!StringUtils.isNullOrWhitespace(this.replaceInPrimaryHand)) {
         std::string[] var8 = this.replaceInPrimaryHand.trim().split("\\s+");
         if (var8.length == 2) {
            this.replacePrimaryHand = std::make_unique<ItemReplacement>();
            this.replacePrimaryHand.clothingItemName = var8[0].trim();
            this.replacePrimaryHand.maskVariableValue = var8[1].trim();
            this.replacePrimaryHand.maskVariableName = "RightHandMask";
         }
      }

      if (!StringUtils.isNullOrWhitespace(this.replaceInSecondHand)) {
         std::string[] var9 = this.replaceInSecondHand.trim().split("\\s+");
         if (var9.length == 2) {
            this.replaceSecondHand = std::make_unique<ItemReplacement>();
            this.replaceSecondHand.clothingItemName = var9[0].trim();
            this.replaceSecondHand.maskVariableValue = var9[1].trim();
            this.replaceSecondHand.maskVariableName = "LeftHandMask";
         }
      }

      if (!StringUtils.isNullOrWhitespace(this.primaryAnimMask)) {
         this.replacePrimaryHand = std::make_unique<ItemReplacement>();
         this.replacePrimaryHand.maskVariableValue = this.primaryAnimMask;
         this.replacePrimaryHand.maskVariableName = "RightHandMask";
         this.replacePrimaryHand.attachment = this.primaryAnimMaskAttachment;
      }

      if (!StringUtils.isNullOrWhitespace(this.secondaryAnimMask)) {
         this.replaceSecondHand = std::make_unique<ItemReplacement>();
         this.replaceSecondHand.maskVariableValue = this.secondaryAnimMask;
         this.replaceSecondHand.maskVariableName = "LeftHandMask";
         this.replaceSecondHand.attachment = this.secondaryAnimMaskAttachment;
      }

      WorldDictionary.onLoadItem(this);
   }

    InventoryItem InstanceItem(const std::string& var1) {
    void* var2 = nullptr;
      if (this.type == Type.Key) {
         var2 = std::make_shared<Key>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
         ((Key)var2).setDigitalPadlock(this.digitalPadlock);
         ((Key)var2).setPadlock(this.padlock);
         if (((Key)var2).isPadlock()) {
            ((Key)var2).setNumberOfKey(2);
            ((Key)var2).setKeyId(Rand.Next(10000000));
         }
      }

      if (this.type == Type.KeyRing) {
         var2 = std::make_shared<KeyRing>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
      }

      if (this.type == Type.WeaponPart) {
         var2 = std::make_shared<WeaponPart>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
    WeaponPart var3 = (WeaponPart)var2;
         var3.setDamage(this.damageModifier);
         var3.setClipSize(this.clipSizeModifier);
         var3.setMaxRange(this.maxRangeModifier);
         var3.setMinRangeRanged(this.minRangeRangedModifier);
         var3.setRecoilDelay(this.recoilDelayModifier);
         var3.setMountOn(this.mountOn);
         var3.setPartType(this.partType);
         var3.setReloadTime(this.reloadTimeModifier);
         var3.setAimingTime(this.aimingTimeModifier);
         var3.setHitChance(this.hitChanceModifier);
         var3.setAngle(this.angleModifier);
         var3.setWeightModifier(this.weightModifier);
      }

      if (this.type == Type.Container) {
         var2 = std::make_shared<InventoryContainer>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
    InventoryContainer var6 = (InventoryContainer)var2;
         var6.setItemCapacity(this.Capacity);
         var6.setCapacity(this.Capacity);
         var6.setWeightReduction(this.WeightReduction);
         var6.setCanBeEquipped(this.CanBeEquipped);
         var6.getInventory().setPutSound(this.PutInSound);
         var6.getInventory().setCloseSound(this.CloseSound);
         var6.getInventory().setOpenSound(this.OpenSound);
         var6.getInventory().setOnlyAcceptCategory(this.OnlyAcceptCategory);
         var6.getInventory().setAcceptItemFunction(this.AcceptItemFunction);
      }

      if (this.type == Type.Food) {
         var2 = std::make_shared<Food>(this.module.name, this.DisplayName, this.name, this);
    Food var7 = (Food)var2;
         var7.Poison = this.Poison;
         var7.setPoisonLevelForRecipe(this.PoisonDetectionLevel);
         var7.setFoodType(this.FoodType);
         var7.setPoisonPower(this.PoisonPower);
         var7.setUseForPoison(this.UseForPoison);
         var7.setThirstChange(this.ThirstChange / 100.0F);
         var7.setHungChange(this.HungerChange / 100.0F);
         var7.setBaseHunger(this.HungerChange / 100.0F);
         var7.setEndChange(this.EnduranceChange / 100.0F);
         var7.setOffAge(this.DaysFresh);
         var7.setOffAgeMax(this.DaysTotallyRotten);
         var7.setIsCookable(this.IsCookable);
         var7.setMinutesToCook(this.MinutesToCook);
         var7.setMinutesToBurn(this.MinutesToBurn);
         var7.setbDangerousUncooked(this.DangerousUncooked);
         var7.setReplaceOnUse(this.ReplaceOnUse);
         var7.setReplaceOnCooked(this.ReplaceOnCooked);
         var7.setSpice(this.Spice);
         var7.setRemoveNegativeEffectOnCooked(this.RemoveNegativeEffectOnCooked);
         var7.setCustomEatSound(this.customEatSound);
         var7.setOnCooked(this.OnCooked);
         var7.setFluReduction(this.fluReduction);
         var7.setReduceFoodSickness(this.ReduceFoodSickness);
         var7.setPainReduction(this.painReduction);
         var7.setHerbalistType(this.HerbalistType);
         var7.setCarbohydrates(this.carbohydrates);
         var7.setLipids(this.lipids);
         var7.setProteins(this.proteins);
         var7.setCalories(this.calories);
         var7.setPackaged(this.packaged);
         var7.setCanBeFrozen(!this.cantBeFrozen);
         var7.setReplaceOnRotten(this.ReplaceOnRotten);
         var7.setOnEat(this.onEat);
         var7.setBadInMicrowave(this.BadInMicrowave);
         var7.setGoodHot(this.GoodHot);
         var7.setBadCold(this.BadCold);
      }

      if (this.type == Type.Literature) {
         var2 = std::make_shared<Literature>(this.module.name, this.DisplayName, this.name, this);
    Literature var8 = (Literature)var2;
         var8.setReplaceOnUse(this.ReplaceOnUse);
         var8.setNumberOfPages(this.NumberOfPages);
         var8.setAlreadyReadPages(0);
         var8.setSkillTrained(this.SkillTrained);
         var8.setLvlSkillTrained(this.LvlSkillTrained);
         var8.setNumLevelsTrained(this.NumLevelsTrained);
         var8.setCanBeWrite(this.canBeWrite);
         var8.setPageToWrite(this.PageToWrite);
         var8.setTeachedRecipes(this.teachedRecipes);
      } else if (this.type == Type.AlarmClock) {
         var2 = std::make_shared<AlarmClock>(this.module.name, this.DisplayName, this.name, this);
    AlarmClock var9 = (AlarmClock)var2;
         var9.setAlarmSound(this.AlarmSound);
         var9.setSoundRadius(this.SoundRadius);
      } else if (this.type == Type.AlarmClockClothing) {
    std::string var10 = "";
    std::string var4 = nullptr;
         if (!this.PaletteChoices.empty() || var1 != nullptr) {
    int var5 = Rand.Next(this.PaletteChoices.size());
            var4 = this.PaletteChoices.get(var5);
            if (var1 != nullptr) {
               var4 = var1;
            }

            var10 = "_" + var4.replace(this.PalettesStart, "");
         }

         var2 = std::make_shared<AlarmClockClothing>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon.replace(".png", "") + var10, var4, this.SpriteName);
    AlarmClockClothing var20 = (AlarmClockClothing)var2;
         var20.setTemperature(this.Temperature);
         var20.setInsulation(this.insulation);
         var20.setConditionLowerChance(this.ConditionLowerChance);
         var20.setStompPower(this.stompPower);
         var20.setRunSpeedModifier(this.runSpeedModifier);
         var20.setCombatSpeedModifier(this.combatSpeedModifier);
         var20.setRemoveOnBroken(this.removeOnBroken);
         var20.setCanHaveHoles(this.canHaveHoles);
         var20.setWeightWet(this.WeightWet);
         var20.setBiteDefense(this.biteDefense);
         var20.setBulletDefense(this.bulletDefense);
         var20.setNeckProtectionModifier(this.neckProtectionModifier);
         var20.setScratchDefense(this.scratchDefense);
         var20.setChanceToFall(this.chanceToFall);
         var20.setWindresistance(this.windresist);
         var20.setWaterResistance(this.waterresist);
         var20.setAlarmSound(this.AlarmSound);
         var20.setSoundRadius(this.SoundRadius);
      } else if (this.type == Type.Weapon) {
         var2 = std::make_shared<HandWeapon>(this.module.name, this.DisplayName, this.name, this);
    HandWeapon var11 = (HandWeapon)var2;
         var11.setMultipleHitConditionAffected(this.MultipleHitConditionAffected);
         var11.setConditionLowerChance(this.ConditionLowerChance);
         var11.SplatSize = this.SplatSize;
         var11.aimingMod = this.AimingMod;
         var11.setMinDamage(this.MinDamage);
         var11.setMaxDamage(this.MaxDamage);
         var11.setBaseSpeed(this.baseSpeed);
         var11.setPhysicsObject(this.PhysicsObject);
         var11.setOtherHandRequire(this.OtherHandRequire);
         var11.setOtherHandUse(this.OtherHandUse);
         var11.setMaxRange(this.MaxRange);
         var11.setMinRange(this.MinRange);
         var11.setShareEndurance(this.ShareEndurance);
         var11.setKnockdownMod(this.KnockdownMod);
         var11.bIsAimedFirearm = this.IsAimedFirearm;
         var11.RunAnim = this.RunAnim;
         var11.IdleAnim = this.IdleAnim;
         var11.HitAngleMod = (float)Math.toRadians(this.HitAngleMod);
         var11.bIsAimedHandWeapon = this.IsAimedHandWeapon;
         var11.setCantAttackWithLowestEndurance(this.CantAttackWithLowestEndurance);
         var11.setAlwaysKnockdown(this.AlwaysKnockdown);
         var11.setEnduranceMod(this.EnduranceMod);
         var11.setUseSelf(this.UseSelf);
         var11.setMaxHitCount(this.MaxHitCount);
         var11.setMinimumSwingTime(this.MinimumSwingTime);
         var11.setSwingTime(this.SwingTime);
         var11.setDoSwingBeforeImpact(this.SwingAmountBeforeImpact);
         var11.setMinAngle(this.MinAngle);
         var11.setDoorDamage(this.DoorDamage);
         var11.setTreeDamage(this.treeDamage);
         var11.setDoorHitSound(this.DoorHitSound);
         var11.setHitFloorSound(this.hitFloorSound);
         var11.setZombieHitSound(this.HitSound);
         var11.setPushBackMod(this.PushBackMod);
         var11.setWeight(this.WeaponWeight);
         var11.setImpactSound(this.ImpactSound);
         var11.setSplatNumber(this.SplatNumber);
         var11.setKnockBackOnNoDeath(this.KnockBackOnNoDeath);
         var11.setSplatBloodOnNoDeath(this.SplatBloodOnNoDeath);
         var11.setSwingSound(this.SwingSound);
         var11.setBulletOutSound(this.bulletOutSound);
         var11.setShellFallSound(this.ShellFallSound);
         var11.setAngleFalloff(this.AngleFalloff);
         var11.setSoundVolume(this.SoundVolume);
         var11.setSoundRadius(this.SoundRadius);
         var11.setToHitModifier(this.ToHitModifier);
         var11.setOtherBoost(this.NPCSoundBoost);
         var11.setRanged(this.Ranged);
         var11.setRangeFalloff(this.RangeFalloff);
         var11.setUseEndurance(this.UseEndurance);
         var11.setCriticalChance(this.CriticalChance);
         var11.setCritDmgMultiplier(this.critDmgMultiplier);
         var11.setShareDamage(this.ShareDamage);
         var11.setCanBarracade(this.CanBarricade);
         var11.setWeaponSprite(this.WeaponSprite);
         var11.setOriginalWeaponSprite(this.WeaponSprite);
         var11.setSubCategory(this.SubCategory);
         var11.setCategories(this.Categories);
         var11.setSoundGain(this.SoundGain);
         var11.setAimingPerkCritModifier(this.AimingPerkCritModifier);
         var11.setAimingPerkRangeModifier(this.AimingPerkRangeModifier);
         var11.setAimingPerkHitChanceModifier(this.AimingPerkHitChanceModifier);
         var11.setHitChance(this.HitChance);
         var11.setRecoilDelay(this.RecoilDelay);
         var11.setAimingPerkMinAngleModifier(this.AimingPerkMinAngleModifier);
         var11.setPiercingBullets(this.PiercingBullets);
         var11.setClipSize(this.ClipSize);
         var11.setReloadTime(this.reloadTime);
         var11.setAimingTime(this.aimingTime);
         var11.setTriggerExplosionTimer(this.triggerExplosionTimer);
         var11.setSensorRange(this.sensorRange);
         var11.setWeaponLength(this.WeaponLength);
         var11.setPlacedSprite(this.PlacedSprite);
         var11.setExplosionTimer(this.explosionTimer);
         var11.setCanBePlaced(this.canBePlaced);
         var11.setCanBeReused(this.canBeReused);
         var11.setExplosionRange(this.explosionRange);
         var11.setExplosionPower(this.explosionPower);
         var11.setFireRange(this.fireRange);
         var11.setFirePower(this.firePower);
         var11.setSmokeRange(this.smokeRange);
         var11.setNoiseRange(this.noiseRange);
         var11.setExtraDamage(this.extraDamage);
         var11.setAmmoBox(this.ammoBox);
         var11.setRackSound(this.rackSound);
         var11.setClickSound(this.clickSound);
         var11.setMagazineType(this.magazineType);
         var11.setWeaponReloadType(this.weaponReloadType);
         var11.setInsertAllBulletsReload(this.insertAllBulletsReload);
         var11.setRackAfterShoot(this.rackAfterShoot);
         var11.setJamGunChance(this.jamGunChance);
         var11.setModelWeaponPart(this.modelWeaponPart);
         var11.setHaveChamber(this.haveChamber);
         var11.setDamageCategory(this.damageCategory);
         var11.setDamageMakeHole(this.damageMakeHole);
         var11.setFireMode(this.fireMode);
         var11.setFireModePossibilities(this.fireModePossibilities);
      } else if (this.type == Type.Normal) {
         var2 = std::make_shared<ComboItem>(this.module.name, this.DisplayName, this.name, this);
      } else if (this.type == Type.Clothing) {
    std::string var12 = "";
    std::string var18 = nullptr;
         if (!this.PaletteChoices.empty() || var1 != nullptr) {
    int var21 = Rand.Next(this.PaletteChoices.size());
            var18 = this.PaletteChoices.get(var21);
            if (var1 != nullptr) {
               var18 = var1;
            }

            var12 = "_" + var18.replace(this.PalettesStart, "");
         }

         var2 = std::make_shared<Clothing>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon.replace(".png", "") + var12, var18, this.SpriteName);
    Clothing var22 = (Clothing)var2;
         var22.setTemperature(this.Temperature);
         var22.setInsulation(this.insulation);
         var22.setConditionLowerChance(this.ConditionLowerChance);
         var22.setStompPower(this.stompPower);
         var22.setRunSpeedModifier(this.runSpeedModifier);
         var22.setCombatSpeedModifier(this.combatSpeedModifier);
         var22.setRemoveOnBroken(this.removeOnBroken);
         var22.setCanHaveHoles(this.canHaveHoles);
         var22.setWeightWet(this.WeightWet);
         var22.setBiteDefense(this.biteDefense);
         var22.setBulletDefense(this.bulletDefense);
         var22.setNeckProtectionModifier(this.neckProtectionModifier);
         var22.setScratchDefense(this.scratchDefense);
         var22.setChanceToFall(this.chanceToFall);
         var22.setWindresistance(this.windresist);
         var22.setWaterResistance(this.waterresist);
      } else if (this.type == Type.Drainable) {
         var2 = std::make_shared<DrainableComboItem>(this.module.name, this.DisplayName, this.name, this);
    DrainableComboItem var13 = (DrainableComboItem)var2;
         var13.setUseWhileEquiped(this.UseWhileEquipped);
         var13.setUseWhileUnequiped(this.UseWhileUnequipped);
         var13.setTicksPerEquipUse(this.TicksPerEquipUse);
         var13.setUseDelta(this.UseDelta);
         var13.setReplaceOnDeplete(this.ReplaceOnDeplete);
         var13.setIsCookable(this.IsCookable);
         var13.setReplaceOnCooked(this.ReplaceOnCooked);
         var13.setMinutesToCook(this.MinutesToCook);
         var13.setOnCooked(this.OnCooked);
         var13.setRainFactor(this.rainFactor);
         var13.setCanConsolidate(!this.cantBeConsolided);
         var13.setWeightEmpty(this.WeightEmpty);
      } else if (this.type == Type.Radio) {
         var2 = std::make_shared<Radio>(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
    Radio var14 = (Radio)var2;
    DeviceData var19 = var14.getDeviceData();
         if (var19 != nullptr) {
            if (this.DisplayName != nullptr) {
               var19.setDeviceName(this.DisplayName);
            }

            var19.setIsTwoWay(this.twoWay);
            var19.setTransmitRange(this.transmitRange);
            var19.setMicRange(this.micRange);
            var19.setBaseVolumeRange(this.baseVolumeRange);
            var19.setIsPortable(this.isPortable);
            var19.setIsTelevision(this.isTelevision);
            var19.setMinChannelRange(this.minChannel);
            var19.setMaxChannelRange(this.maxChannel);
            var19.setIsBatteryPowered(this.usesBattery);
            var19.setIsHighTier(this.isHighTier);
            var19.setUseDelta(this.UseDelta);
            var19.setMediaType(this.acceptMediaType);
            var19.setNoTransmit(this.noTransmit);
            var19.generatePresets();
            var19.setRandomChannel();
         }

         if (!StringUtils.isNullOrWhitespace(this.worldObjectSprite) && !var14.ReadFromWorldSprite(this.worldObjectSprite)) {
            DebugLog.log("Item -> Radio item = " + (this.moduleDotType != nullptr ? this.moduleDotType : "unknown"));
         }
      } else if (this.type == Type.Moveable) {
         var2 = std::make_shared<Moveable>(this.module.name, this.DisplayName, this.name, this);
    Moveable var15 = (Moveable)var2;
         var15.ReadFromWorldSprite(this.worldObjectSprite);
         this.ActualWeight = var15.getActualWeight();
      } else if (this.type == Type.Map) {
    MapItem var16 = std::make_shared<MapItem>(this.module.name, this.DisplayName, this.name, this);
         if (StringUtils.isNullOrWhitespace(this.map)) {
            var16.setMapID(MapDefinitions.getInstance().pickRandom());
         } else {
            var16.setMapID(this.map);
         }

         var2 = var16;
      }

      if (this.colorRed < 255 || this.colorGreen < 255 || this.colorBlue < 255) {
         var2.setColor(std::make_shared<Color>(this.colorRed / 255.0F, this.colorGreen / 255.0F, this.colorBlue / 255.0F));
      }

      var2.setAlcoholPower(this.alcoholPower);
      var2.setConditionMax(this.ConditionMax);
      var2.setCondition(this.ConditionMax);
      var2.setCanBeActivated(this.ActivatedItem);
      var2.setLightStrength(this.LightStrength);
      var2.setTorchCone(this.TorchCone);
      var2.setLightDistance(this.LightDistance);
      var2.setActualWeight(this.ActualWeight);
      var2.setWeight(this.ActualWeight);
      var2.setUses(this.Count);
      var2.setScriptItem(this);
      var2.setBoredomChange(this.BoredomChange);
      var2.setStressChange(this.StressChange / 100.0F);
      var2.setUnhappyChange(this.UnhappyChange);
      var2.setReplaceOnUseOn(this.ReplaceOnUseOn);
      var2.setRequireInHandOrInventory(this.RequireInHandOrInventory);
      var2.setAttachmentsProvided(this.attachmentsProvided);
      var2.setAttachmentReplacement(this.attachmentReplacement);
      var2.setIsWaterSource(this.IsWaterSource);
      ((InventoryItem)var2).CanStoreWater = this.CanStoreWater;
      ((InventoryItem)var2).CanStack = this.CanStack;
      var2.copyModData(this.DefaultModData);
      var2.setCount(this.Count);
      var2.setFatigueChange(this.FatigueChange / 100.0F);
      var2.setTooltip(this.Tooltip);
      var2.setDisplayCategory(this.DisplayCategory);
      var2.setAlcoholic(this.Alcoholic);
      ((InventoryItem)var2).RequiresEquippedBothHands = this.RequiresEquippedBothHands;
      var2.setBreakSound(this.breakSound);
      var2.setReplaceOnUse(this.ReplaceOnUse);
      var2.setBandagePower(this.bandagePower);
      var2.setReduceInfectionPower(this.ReduceInfectionPower);
      var2.setCanBeRemote(this.canBeRemote);
      var2.setRemoteController(this.remoteController);
      var2.setRemoteRange(this.remoteRange);
      var2.setCountDownSound(this.countDownSound);
      var2.setExplosionSound(this.explosionSound);
      var2.setColorRed(this.colorRed / 255.0F);
      var2.setColorGreen(this.colorGreen / 255.0F);
      var2.setColorBlue(this.colorBlue / 255.0F);
      var2.setEvolvedRecipeName(this.evolvedRecipeName);
      var2.setMetalValue(this.metalValue);
      var2.setWet(this.isWet);
      var2.setWetCooldown(this.wetCooldown);
      var2.setItemWhenDry(this.itemWhenDry);
      ((InventoryItem)var2).keepOnDeplete = this.keepOnDeplete;
      var2.setItemCapacity(this.itemCapacity);
      var2.setMaxCapacity(this.maxCapacity);
      var2.setBrakeForce(this.brakeForce);
      var2.setChanceToSpawnDamaged(this.chanceToSpawnDamaged);
      var2.setConditionLowerNormal(this.conditionLowerNormal);
      var2.setConditionLowerOffroad(this.conditionLowerOffroad);
      var2.setWheelFriction(this.wheelFriction);
      var2.setSuspensionCompression(this.suspensionCompression);
      var2.setEngineLoudness(this.engineLoudness);
      var2.setSuspensionDamping(this.suspensionDamping);
      if (this.CustomContextMenu != nullptr) {
         var2.setCustomMenuOption(Translator.getText("ContextMenu_" + this.CustomContextMenu));
      }

      if (this.IconsForTexture != nullptr && !this.IconsForTexture.empty()) {
         var2.setIconsForTexture(this.IconsForTexture);
      }

      var2.setBloodClothingType(this.bloodClothingType);
      ((InventoryItem)var2).CloseKillMove = this.CloseKillMove;
      var2.setAmmoType(this.AmmoType);
      var2.setMaxAmmo(this.maxAmmo);
      var2.setGunType(this.GunType);
      var2.setAttachmentType(this.attachmentType);
    long var17 = OutfitRNG.getSeed();
      OutfitRNG.setSeed(Rand.Next(int.MAX_VALUE));
      var2.synchWithVisual();
      OutfitRNG.setSeed(var17);
      var2.setRegistry_id(this);
    Thread var23 = Thread.currentThread();
      if ((var23 == GameWindow.GameThread || var23 == GameLoadingState.loader || var23 == GameServer.MainThread) && !var2.isInitialised()) {
         var2.initialiseItem();
      }

      return (InventoryItem)var2;
   }

    void DoParam(const std::string& var1) {
      if (var1.trim().length() != 0) {
         try {
            std::string[] var2 = var1.split("=");
    std::string var3 = var2[0].trim();
    std::string var4 = var2[1].trim();
            if (var3.trim().equalsIgnoreCase("BodyLocation")) {
               this.BodyLocation = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("Palettes")) {
               std::string[] var5 = var4.split("/");

               for (int var6 = 0; var6 < var5.length; var6++) {
                  this.PaletteChoices.push_back(var5[var6].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("HitSound")) {
               this.HitSound = var4.trim();
               if (this.HitSound == "nullptr")) {
                  this.HitSound = nullptr;
               }
            } else if (var3.trim().equalsIgnoreCase("HitFloorSound")) {
               this.hitFloorSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PalettesStart")) {
               this.PalettesStart = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("DisplayName")) {
               this.DisplayName = Translator.getDisplayItemName(var4.trim());
               this.DisplayName = Translator.getItemNameFromFullType(this.getFullName());
            } else if (var3.trim().equalsIgnoreCase("MetalValue")) {
               this.metalValue = std::make_shared<float>(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SpriteName")) {
               this.SpriteName = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("Type")) {
               this.type = Type.valueOf(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SplatSize")) {
               this.SplatSize = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CanStoreWater")) {
               this.CanStoreWater = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("IsWaterSource")) {
               this.IsWaterSource = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Poison")) {
               this.Poison = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("FoodType")) {
               this.FoodType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PoisonDetectionLevel")) {
               this.PoisonDetectionLevel = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("PoisonPower")) {
               this.PoisonPower = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UseForPoison")) {
               this.UseForPoison = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingAnim")) {
               this.SwingAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("Icon")) {
               this.Icon = var4;
               this.ItemName = "Item_" + this.Icon;
               this.NormalTexture = Texture.trygetTexture(this.ItemName);
               if (this.NormalTexture == nullptr) {
                  this.NormalTexture = Texture.getSharedTexture("media/inventory/Question_On.png");
               }

               this.WorldTextureName = this.ItemName.replace("Item_", "media/inventory/world/WItem_");
               this.WorldTextureName = this.WorldTextureName + ".png";
               this.WorldTexture = Texture.getSharedTexture(this.WorldTextureName);
               if (this.type == Type.Food) {
    Texture var17 = Texture.trygetTexture(this.ItemName + "Rotten");
    std::string var33 = this.WorldTextureName.replace(".png", "Rotten.png");
                  if (var17 == nullptr) {
                     var17 = Texture.trygetTexture(this.ItemName + "Spoiled");
                     var33 = var33.replace("Rotten.png", "Spoiled.png");
                  }

                  this.SpecialWorldTextureNames.push_back(var33);
                  this.SpecialTextures.push_back(var17);
                  this.SpecialTextures.push_back(Texture.trygetTexture(this.ItemName + "Cooked"));
                  this.SpecialWorldTextureNames.push_back(this.WorldTextureName.replace(".png", "Cooked.png"));
    Texture var7 = Texture.trygetTexture(this.ItemName + "Overdone");
    std::string var8 = this.WorldTextureName.replace(".png", "Overdone.png");
                  if (var7 == nullptr) {
                     var7 = Texture.trygetTexture(this.ItemName + "Burnt");
                     var8 = var8.replace("Overdone.png", "Burnt.png");
                  }

                  this.SpecialTextures.push_back(var7);
                  this.SpecialWorldTextureNames.push_back(var8);
               }
            } else if (var3.trim().equalsIgnoreCase("UseWorldItem")) {
               this.UseWorldItem = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("Medical")) {
               this.Medical = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("CannedFood")) {
               this.CannedFood = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("MechanicsItem")) {
               this.MechanicsItem = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("SurvivalGear")) {
               this.SurvivalGear = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("ScaleWorldIcon")) {
               this.ScaleWorldIcon = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HairDye")) {
               this.hairDye = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("DoorHitSound")) {
               this.DoorHitSound = var4;
            } else if (var3.trim().equalsIgnoreCase("Weight")) {
               this.ActualWeight = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightWet")) {
               this.WeightWet = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightEmpty")) {
               this.WeightEmpty = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HungerChange")) {
               this.HungerChange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ThirstChange")) {
               this.ThirstChange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("FatigueChange")) {
               this.FatigueChange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("EnduranceChange")) {
               this.EnduranceChange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CriticalChance")) {
               this.CriticalChance = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("critDmgMultiplier")) {
               this.critDmgMultiplier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DaysFresh")) {
               this.DaysFresh = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("DaysTotallyRotten")) {
               this.DaysTotallyRotten = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("IsCookable")) {
               this.IsCookable = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CookingSound")) {
               this.CookingSound = var4;
            } else if (var3.trim().equalsIgnoreCase("MinutesToCook")) {
               this.MinutesToCook = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MinutesToBurn")) {
               this.MinutesToBurn = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("BoredomChange")) {
               this.BoredomChange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("StressChange")) {
               this.StressChange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UnhappyChange")) {
               this.UnhappyChange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RemoveUnhappinessWhenCooked")) {
               this.RemoveUnhappinessWhenCooked = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnDeplete")) {
               this.ReplaceOnDeplete = var4;
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnUseOn")) {
               this.ReplaceOnUseOn = var4;
               if (var4.contains("-")) {
                  std::string[] var18 = var4.split("-");
    std::string var34 = var18[0].trim();
    std::string var46 = var18[1].trim();
                  if (!var34.empty() && !var46.empty()) {
                     if (this.ReplaceTypesMap == nullptr) {
                        this.ReplaceTypesMap = std::make_unique<std::unordered_map<>>();
                     }

                     this.ReplaceTypesMap.put(var34, var46);
                  }
               }
            } else if (var3.trim().equalsIgnoreCase("ReplaceTypes")) {
               this.ReplaceTypes = var4;
               std::string[] var19 = var4.split(";");

    for (auto& var9 : var19)                  std::string[] var10 = var9.trim().split("\\s+");
                  if (var10.length == 2) {
    std::string var11 = var10[0].trim();
    std::string var12 = var10[1].trim();
                     if (!var11.empty() && !var12.empty()) {
                        if (this.ReplaceTypesMap == nullptr) {
                           this.ReplaceTypesMap = std::make_unique<std::unordered_map<>>();
                        }

                        this.ReplaceTypesMap.put(var11, var12);
                     }
                  }
               }
            } else if (var3.trim().equalsIgnoreCase("Ranged")) {
               this.Ranged = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("UseSelf")) {
               this.UseSelf = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("OtherHandUse")) {
               this.OtherHandUse = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("DangerousUncooked")) {
               this.DangerousUncooked = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("MaxRange")) {
               this.MaxRange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinRange")) {
               this.MinRange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinAngle")) {
               this.MinAngle = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxDamage")) {
               this.MaxDamage = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("BaseSpeed")) {
               this.baseSpeed = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("stompPower")) {
               this.stompPower = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("combatSpeedModifier")) {
               this.combatSpeedModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("runSpeedModifier")) {
               this.runSpeedModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("clothingItemExtra")) {
               this.clothingItemExtra = std::make_unique<std::vector<>>();
               std::string[] var20 = var4.split(";");

               for (int var36 = 0; var36 < var20.length; var36++) {
                  this.clothingItemExtra.push_back(var20[var36]);
               }
            } else if (var3.trim().equalsIgnoreCase("clothingExtraSubmenu")) {
               this.clothingExtraSubmenu = var4;
            } else if (var3.trim().equalsIgnoreCase("removeOnBroken")) {
               this.removeOnBroken = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("canHaveHoles")) {
               this.canHaveHoles = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("Cosmetic")) {
               this.cosmetic = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("ammoBox")) {
               this.ammoBox = var4;
            } else if (var3.trim().equalsIgnoreCase("InsertAmmoStartSound")) {
               this.insertAmmoStartSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("InsertAmmoSound")) {
               this.insertAmmoSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("InsertAmmoStopSound")) {
               this.insertAmmoStopSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("EjectAmmoStartSound")) {
               this.ejectAmmoStartSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("EjectAmmoSound")) {
               this.ejectAmmoSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("EjectAmmoStopSound")) {
               this.ejectAmmoStopSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("rackSound")) {
               this.rackSound = var4;
            } else if (var3.trim().equalsIgnoreCase("clickSound")) {
               this.clickSound = var4;
            } else if (var3.equalsIgnoreCase("BringToBearSound")) {
               this.bringToBearSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.equalsIgnoreCase("EquipSound")) {
               this.equipSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.equalsIgnoreCase("UnequipSound")) {
               this.unequipSound = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("magazineType")) {
               this.magazineType = var4;
            } else if (var3.trim().equalsIgnoreCase("jamGunChance")) {
               this.jamGunChance = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("modelWeaponPart")) {
               if (this.modelWeaponPart == nullptr) {
                  this.modelWeaponPart = std::make_unique<std::vector<>>();
               }

               std::string[] var21 = var4.split("\\s+");
               if (var21.length >= 2 && var21.length <= 4) {
    ModelWeaponPart var37 = nullptr;

                  for (int var48 = 0; var48 < this.modelWeaponPart.size(); var48++) {
    ModelWeaponPart var52 = this.modelWeaponPart.get(var48);
                     if (var52.partType == var21[0])) {
                        var37 = var52;
                        break;
                     }
                  }

                  if (var37 == nullptr) {
                     var37 = std::make_unique<ModelWeaponPart>();
                  }

                  var37.partType = var21[0];
                  var37.modelName = var21[1];
                  var37.attachmentNameSelf = var21.length > 2 ? var21[2] : nullptr;
                  var37.attachmentParent = var21.length > 3 ? var21[3] : nullptr;
                  if (!var37.partType.contains(".")) {
                     var37.partType = this.module.name + "." + var37.partType;
                  }

                  if (!var37.modelName.contains(".")) {
                     var37.modelName = this.module.name + "." + var37.modelName;
                  }

                  if ("none".equalsIgnoreCase(var37.attachmentNameSelf)) {
                     var37.attachmentNameSelf = nullptr;
                  }

                  if ("none".equalsIgnoreCase(var37.attachmentParent)) {
                     var37.attachmentParent = nullptr;
                  }

                  this.modelWeaponPart.push_back(var37);
               }
            } else if (var3.trim().equalsIgnoreCase("rackAfterShoot")) {
               this.rackAfterShoot = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("haveChamber")) {
               this.haveChamber = bool.parseBoolean(var4);
            } else if (var3.equalsIgnoreCase("ManuallyRemoveSpentRounds")) {
               this.manuallyRemoveSpentRounds = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("biteDefense")) {
               this.biteDefense = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("bulletDefense")) {
               this.bulletDefense = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("neckProtectionModifier")) {
               this.neckProtectionModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("damageCategory")) {
               this.damageCategory = var4;
            } else if (var3.trim().equalsIgnoreCase("fireMode")) {
               this.fireMode = var4;
            } else if (var3.trim().equalsIgnoreCase("damageMakeHole")) {
               this.damageMakeHole = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("equippedNoSprint")) {
               this.equippedNoSprint = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("scratchDefense")) {
               this.scratchDefense = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("weaponReloadType")) {
               this.weaponReloadType = var4;
            } else if (var3.trim().equalsIgnoreCase("insertAllBulletsReload")) {
               this.insertAllBulletsReload = bool.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("clothingItemExtraOption")) {
               this.clothingItemExtraOption = std::make_unique<std::vector<>>();
               std::string[] var22 = var4.split(";");

               for (int var38 = 0; var38 < var22.length; var38++) {
                  this.clothingItemExtraOption.push_back(var22[var38]);
               }
            } else if (var3.trim().equalsIgnoreCase("ConditionLowerChanceOneIn")) {
               this.ConditionLowerChance = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MultipleHitConditionAffected")) {
               this.MultipleHitConditionAffected = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CanBandage")) {
               this.CanBandage = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ConditionMax")) {
               this.ConditionMax = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SoundGain")) {
               this.SoundGain = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinDamage")) {
               this.MinDamage = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinimumSwingTime")) {
               this.MinimumSwingTime = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingSound")) {
               this.SwingSound = var4;
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnUse")) {
               this.ReplaceOnUse = var4;
            } else if (var3.trim().equalsIgnoreCase("WeaponSprite")) {
               this.WeaponSprite = var4;
            } else if (var3.trim().equalsIgnoreCase("AimingPerkCritModifier")) {
               this.AimingPerkCritModifier = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkRangeModifier")) {
               this.AimingPerkRangeModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkHitChanceModifier")) {
               this.AimingPerkHitChanceModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AngleModifier")) {
               this.angleModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightModifier")) {
               this.weightModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkMinAngleModifier")) {
               this.AimingPerkMinAngleModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HitChance")) {
               this.HitChance = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RecoilDelay")) {
               this.RecoilDelay = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("StopPower")) {
               this.stopPower = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("PiercingBullets")) {
               this.PiercingBullets = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AngleFalloff")) {
               this.AngleFalloff = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SoundVolume")) {
               this.SoundVolume = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ToHitModifier")) {
               this.ToHitModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SoundRadius")) {
               this.SoundRadius = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("Categories")) {
               std::string[] var23 = var4.split(";");

               for (int var39 = 0; var39 < var23.length; var39++) {
                  this.Categories.push_back(var23[var39].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("Tags")) {
               std::string[] var24 = var4.split(";");

               for (int var40 = 0; var40 < var24.length; var40++) {
                  this.Tags.push_back(var24[var40].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("OtherCharacterVolumeBoost")) {
               this.OtherCharacterVolumeBoost = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ImpactSound")) {
               this.ImpactSound = var4;
               if (this.ImpactSound == "nullptr")) {
                  this.ImpactSound = nullptr;
               }
            } else if (var3.trim().equalsIgnoreCase("SwingTime")) {
               this.SwingTime = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("KnockBackOnNoDeath")) {
               this.KnockBackOnNoDeath = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Alcoholic")) {
               this.Alcoholic = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SplatBloodOnNoDeath")) {
               this.SplatBloodOnNoDeath = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SwingAmountBeforeImpact")) {
               this.SwingAmountBeforeImpact = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AmmoType")) {
               this.AmmoType = var4;
            } else if (var3.trim().equalsIgnoreCase("maxAmmo")) {
               this.maxAmmo = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("GunType")) {
               this.GunType = var4;
            } else if (var3.trim().equalsIgnoreCase("HitAngleMod")) {
               this.HitAngleMod = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("OtherHandRequire")) {
               this.OtherHandRequire = var4;
            } else if (var3.trim().equalsIgnoreCase("AlwaysWelcomeGift")) {
               this.AlwaysWelcomeGift = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CantAttackWithLowestEndurance")) {
               this.CantAttackWithLowestEndurance = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("EnduranceMod")) {
               this.EnduranceMod = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("KnockdownMod")) {
               this.KnockdownMod = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DoorDamage")) {
               this.DoorDamage = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxHitCount")) {
               this.MaxHitCount = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("PhysicsObject")) {
               this.PhysicsObject = var4;
            } else if (var3.trim().equalsIgnoreCase("Count")) {
               this.Count = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingAnim")) {
               this.SwingAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("WeaponWeight")) {
               this.WeaponWeight = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("IdleAnim")) {
               this.IdleAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("RunAnim")) {
               this.RunAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("RequireInHandOrInventory")) {
               this.RequireInHandOrInventory = new std::vector<>(Arrays.asList(var4.split("/")));
            } else if (var3.trim().equalsIgnoreCase("fireModePossibilities")) {
               this.fireModePossibilities = new std::vector<>(Arrays.asList(var4.split("/")));
            } else if (var3.trim().equalsIgnoreCase("attachmentsProvided")) {
               this.attachmentsProvided = new std::vector<>(Arrays.asList(var4.split(";")));
            } else if (var3.trim().equalsIgnoreCase("attachmentReplacement")) {
               this.attachmentReplacement = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PushBackMod")) {
               this.PushBackMod = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("NPCSoundBoost")) {
               this.NPCSoundBoost = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SplatNumber")) {
               this.SplatNumber = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RangeFalloff")) {
               this.RangeFalloff = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("UseEndurance")) {
               this.UseEndurance = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ShareDamage")) {
               this.ShareDamage = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ShareEndurance")) {
               this.ShareEndurance = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AlwaysKnockdown")) {
               this.AlwaysKnockdown = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("IsAimedFirearm")) {
               this.IsAimedFirearm = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("bulletOutSound")) {
               this.bulletOutSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("ShellFallSound")) {
               this.ShellFallSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("SoundMap")) {
               std::string[] var25 = var4.split("\\s+");
               if (var25.length == 2 && !var25[0].trim().empty()) {
                  if (this.SoundMap == nullptr) {
                     this.SoundMap = std::make_unique<std::unordered_map<>>();
                  }

                  this.SoundMap.put(var25[0].trim(), var25[1].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("IsAimedHandWeapon")) {
               this.IsAimedHandWeapon = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AimingMod")) {
               this.AimingMod = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ProjectileCount")) {
               this.ProjectileCount = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("CanStack")) {
               this.IsAimedFirearm = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("HerbalistType")) {
               this.HerbalistType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("CanBarricade")) {
               this.CanBarricade = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("UseWhileEquipped")) {
               this.UseWhileEquipped = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("UseWhileUnequipped")) {
               this.UseWhileUnequipped = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("TicksPerEquipUse")) {
               this.TicksPerEquipUse = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("DisappearOnUse")) {
               this.DisappearOnUse = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Temperature")) {
               this.Temperature = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("Insulation")) {
               this.insulation = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WindResistance")) {
               this.windresist = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WaterResistance")) {
               this.waterresist = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CloseKillMove")) {
               this.CloseKillMove = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("UseDelta")) {
               this.UseDelta = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("RainFactor")) {
               this.rainFactor = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("TorchDot")) {
               this.torchDot = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("NumberOfPages")) {
               this.NumberOfPages = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SkillTrained")) {
               this.SkillTrained = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("LvlSkillTrained")) {
               this.LvlSkillTrained = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("NumLevelsTrained")) {
               this.NumLevelsTrained = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Capacity")) {
               this.Capacity = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("MaxCapacity")) {
               this.maxCapacity = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ItemCapacity")) {
               this.itemCapacity = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ConditionAffectsCapacity")) {
               this.ConditionAffectsCapacity = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("BrakeForce")) {
               this.brakeForce = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ChanceToSpawnDamaged")) {
               this.chanceToSpawnDamaged = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WeaponLength")) {
               this.WeaponLength = std::make_shared<float>(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ClipSize")) {
               this.ClipSize = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReloadTime")) {
               this.reloadTime = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AimingTime")) {
               this.aimingTime = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AimingTimeModifier")) {
               this.aimingTimeModifier = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReloadTimeModifier")) {
               this.reloadTimeModifier = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("HitChanceModifier")) {
               this.hitChanceModifier = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WeightReduction")) {
               this.WeightReduction = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CanBeEquipped")) {
               this.CanBeEquipped = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("SubCategory")) {
               this.SubCategory = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("ActivatedItem")) {
               this.ActivatedItem = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ProtectFromRainWhenEquipped")) {
               this.ProtectFromRainWhenEquipped = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("LightStrength")) {
               this.LightStrength = std::make_shared<float>(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("TorchCone")) {
               this.TorchCone = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("LightDistance")) {
               this.LightDistance = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("TwoHandWeapon")) {
               this.TwoHandWeapon = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Tooltip")) {
               this.Tooltip = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("DisplayCategory")) {
               this.DisplayCategory = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("BadInMicrowave")) {
               this.BadInMicrowave = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("GoodHot")) {
               this.GoodHot = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("BadCold")) {
               this.BadCold = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AlarmSound")) {
               this.AlarmSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("RequiresEquippedBothHands")) {
               this.RequiresEquippedBothHands = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnCooked")) {
               this.ReplaceOnCooked = Arrays.asList(var4.trim().split(";"));
            } else if (var3.trim().equalsIgnoreCase("CustomContextMenu")) {
               this.CustomContextMenu = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("Trap")) {
               this.Trap = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Wet")) {
               this.isWet = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("WetCooldown")) {
               this.wetCooldown = float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ItemWhenDry")) {
               this.itemWhenDry = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("FishingLure")) {
               this.FishingLure = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CanBeWrite")) {
               this.canBeWrite = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("PageToWrite")) {
               this.PageToWrite = int.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Spice")) {
               this.Spice = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("RemoveNegativeEffectOnCooked")) {
               this.RemoveNegativeEffectOnCooked = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ClipSizeModifier")) {
               this.clipSizeModifier = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RecoilDelayModifier")) {
               this.recoilDelayModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxRangeModifier")) {
               this.maxRangeModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinRangeModifier")) {
               this.minRangeRangedModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DamageModifier")) {
               this.damageModifier = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("Map")) {
               this.map = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PutInSound")) {
               this.PutInSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PlaceOneSound")) {
               this.PlaceOneSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("PlaceMultipleSound")) {
               this.PlaceMultipleSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CloseSound")) {
               this.CloseSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("OpenSound")) {
               this.OpenSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("BreakSound")) {
               this.breakSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("TreeDamage")) {
               this.treeDamage = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("CustomEatSound")) {
               this.customEatSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("FillFromDispenserSound")) {
               this.fillFromDispenserSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("FillFromTapSound")) {
               this.fillFromTapSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AlcoholPower")) {
               this.alcoholPower = float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("BandagePower")) {
               this.bandagePower = float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReduceInfectionPower")) {
               this.ReduceInfectionPower = float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("OnCooked")) {
               this.OnCooked = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("OnlyAcceptCategory")) {
               this.OnlyAcceptCategory = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("AcceptItemFunction")) {
               this.AcceptItemFunction = StringUtils.discardNullOrWhitespace(var4);
            } else if (var3.trim().equalsIgnoreCase("Padlock")) {
               this.padlock = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("DigitalPadlock")) {
               this.digitalPadlock = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("triggerExplosionTimer")) {
               this.triggerExplosionTimer = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("sensorRange")) {
               this.sensorRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("remoteRange")) {
               this.remoteRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("CountDownSound")) {
               this.countDownSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("explosionSound")) {
               this.explosionSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PlacedSprite")) {
               this.PlacedSprite = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("explosionTimer")) {
               this.explosionTimer = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("explosionRange")) {
               this.explosionRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("explosionPower")) {
               this.explosionPower = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("fireRange")) {
               this.fireRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("firePower")) {
               this.firePower = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("canBePlaced")) {
               this.canBePlaced = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CanBeReused")) {
               this.canBeReused = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("canBeRemote")) {
               this.canBeRemote = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("remoteController")) {
               this.remoteController = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("smokeRange")) {
               this.smokeRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("noiseRange")) {
               this.noiseRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("noiseDuration")) {
               this.noiseDuration = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("extraDamage")) {
               this.extraDamage = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("TwoWay")) {
               this.twoWay = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("TransmitRange")) {
               this.transmitRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MicRange")) {
               this.micRange = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("BaseVolumeRange")) {
               this.baseVolumeRange = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("IsPortable")) {
               this.isPortable = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("IsTelevision")) {
               this.isTelevision = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("MinChannel")) {
               this.minChannel = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxChannel")) {
               this.maxChannel = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UsesBattery")) {
               this.usesBattery = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("IsHighTier")) {
               this.isHighTier = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WorldObjectSprite")) {
               this.worldObjectSprite = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("fluReduction")) {
               this.fluReduction = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ReduceFoodSickness")) {
               this.ReduceFoodSickness = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("painReduction")) {
               this.painReduction = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorRed")) {
               this.colorRed = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorGreen")) {
               this.colorGreen = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorBlue")) {
               this.colorBlue = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("calories")) {
               this.calories = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("carbohydrates")) {
               this.carbohydrates = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("lipids")) {
               this.lipids = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("proteins")) {
               this.proteins = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("Packaged")) {
               this.packaged = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CantBeFrozen")) {
               this.cantBeFrozen = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("EvolvedRecipeName")) {
               Translator.setDefaultItemEvolvedRecipeName(this.getFullName(), var4);
               this.evolvedRecipeName = Translator.getItemEvolvedRecipeName(this.getFullName());
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnRotten")) {
               this.ReplaceOnRotten = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("CantBeConsolided")) {
               this.cantBeConsolided = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("OnEat")) {
               this.onEat = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("KeepOnDeplete")) {
               this.keepOnDeplete = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("VehicleType")) {
               this.vehicleType = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ChanceToFall")) {
               this.chanceToFall = int.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("conditionLowerOffroad")) {
               this.conditionLowerOffroad = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ConditionLowerStandard")) {
               this.conditionLowerNormal = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("wheelFriction")) {
               this.wheelFriction = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("suspensionDamping")) {
               this.suspensionDamping = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("suspensionCompression")) {
               this.suspensionCompression = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("engineLoudness")) {
               this.engineLoudness = float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("attachmentType")) {
               this.attachmentType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("makeUpType")) {
               this.makeUpType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("consolidateOption")) {
               this.consolidateOption = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("fabricType")) {
               this.fabricType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("TeachedRecipes")) {
               this.teachedRecipes = std::make_unique<std::vector<>>();
               std::string[] var26 = var4.split(";");

               for (int var41 = 0; var41 < var26.length; var41++) {
    std::string var49 = var26[var41].trim();
                  this.teachedRecipes.push_back(var49);
                  if (Translator.debug) {
                     Translator.getRecipeName(var49);
                  }
               }
            } else if (var3.trim().equalsIgnoreCase("MountOn")) {
               this.mountOn = std::make_unique<std::vector<>>();
               std::string[] var27 = var4.split(";");

               for (int var42 = 0; var42 < var27.length; var42++) {
                  this.mountOn.push_back(var27[var42].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("PartType")) {
               this.partType = var4;
            } else if (var3.trim().equalsIgnoreCase("ClothingItem")) {
               this.ClothingItem = var4;
            } else if (var3.trim().equalsIgnoreCase("EvolvedRecipe")) {
               std::string[] var28 = var4.split(";");

               for (int var43 = 0; var43 < var28.length; var43++) {
    std::string var50 = var28[var43];
    void* var53 = nullptr;
    int var55 = 0;
    bool var56 = false;
                  if (!var50.contains(":")) {
                     var53 = var50;
                  } else {
                     var53 = var50.split(":")[0];
    std::string var57 = var50.split(":")[1];
                     if (!var57.contains("|")) {
                        var55 = int.parseInt(var50.split(":")[1]);
                     } else {
                        std::string[] var59 = var57.split("\\|");

                        for (int var13 = 0; var13 < var59.length; var13++) {
                           if ("Cooked" == var59[var13])) {
                              var56 = true;
                           }
                        }

                        var55 = int.parseInt(var59[0]);
                     }
                  }

    ItemRecipe var58 = std::make_shared<ItemRecipe>(this.name, this.module.getName(), var55);
    EvolvedRecipe var60 = nullptr;

                  for (EvolvedRecipe var14 : ((ScriptModule)ScriptManager.instance.ModuleMap.get("Base")).EvolvedRecipeMap) {
                     if (var14.name == var53)) {
                        var60 = var14;
                        break;
                     }
                  }

                  var58.cooked = var56;
                  if (var60 == nullptr) {
                     var60 = std::make_shared<EvolvedRecipe>((std::string)var53);
                     ((ScriptModule)ScriptManager.instance.ModuleMap.get("Base")).EvolvedRecipeMap.push_back(var60);
                  }

                  var60.itemsList.put(this.name, var58);
               }
            } else if (var3.trim().equalsIgnoreCase("StaticModel")) {
               this.staticModel = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("worldStaticModel")) {
               this.worldStaticModel = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("primaryAnimMask")) {
               this.primaryAnimMask = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("secondaryAnimMask")) {
               this.secondaryAnimMask = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("primaryAnimMaskAttachment")) {
               this.primaryAnimMaskAttachment = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("secondaryAnimMaskAttachment")) {
               this.secondaryAnimMaskAttachment = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("replaceInSecondHand")) {
               this.replaceInSecondHand = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("replaceInPrimaryHand")) {
               this.replaceInPrimaryHand = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("replaceWhenUnequip")) {
               this.replaceWhenUnequip = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("EatType")) {
               this.eatType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("IconsForTexture")) {
               this.IconsForTexture = std::make_unique<std::vector<>>();
               std::string[] var29 = var4.split(";");

               for (int var44 = 0; var44 < var29.length; var44++) {
                  this.IconsForTexture.push_back(var29[var44].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("BloodLocation")) {
               this.bloodClothingType = std::make_unique<std::vector<>>();
               std::string[] var30 = var4.split(";");

               for (int var45 = 0; var45 < var30.length; var45++) {
                  this.bloodClothingType.push_back(BloodClothingType.fromString(var30[var45].trim()));
               }
            } else if (var3.trim().equalsIgnoreCase("MediaCategory")) {
               this.recordedMediaCat = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("AcceptMediaType")) {
               this.acceptMediaType = uint8_t.parseByte(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("NoTransmit")) {
               this.noTransmit = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WorldRender")) {
               this.worldRender = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CantEat")) {
               this.CantEat = bool.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("OBSOLETE")) {
               this.OBSOLETE = var4.trim().toLowerCase() == "true");
            } else if (var3.trim().equalsIgnoreCase("OnCreate")) {
               this.LuaCreate = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("SoundParameter")) {
               std::string[] var31 = var4.split("\\s+");
               if (this.soundParameterMap == nullptr) {
                  this.soundParameterMap = std::make_unique<std::unordered_map<>>();
               }

               this.soundParameterMap.put(var31[0].trim(), var31[1].trim());
            } else {
               DebugLog.log("adding unknown item param \"" + var3.trim() + "\" = \"" + var4.trim() + "\"");
               if (this.DefaultModData == nullptr) {
                  this.DefaultModData = LuaManager.platform.newTable();
               }

               try {
    double var32 = double.parseDouble(var4.trim());
                  this.DefaultModData.rawset(var3.trim(), var32);
               } catch (Exception var15) {
                  this.DefaultModData.rawset(var3.trim(), var4);
               }
            }
         } catch (Exception var16) {
            throw InvalidParameterException("Error: " + var1.trim() + " is not a valid parameter in item: " + this.name);
         }
      }
   }

    int getLevelSkillTrained() {
      return this.LvlSkillTrained;
   }

    int getNumLevelsTrained() {
      return this.NumLevelsTrained;
   }

    int getMaxLevelTrained() {
      return this.LvlSkillTrained == -1 ? -1 : this.LvlSkillTrained + this.NumLevelsTrained;
   }

   public List<std::string> getTeachedRecipes() {
      return this.teachedRecipes;
   }

    float getTemperature() {
      return this.Temperature;
   }

    void setTemperature(float var1) {
      this.Temperature = var1;
   }

    bool isConditionAffectsCapacity() {
      return this.ConditionAffectsCapacity;
   }

    int getChanceToFall() {
      return this.chanceToFall;
   }

    float getInsulation() {
      return this.insulation;
   }

    void setInsulation(float var1) {
      this.insulation = var1;
   }

    float getWindresist() {
      return this.windresist;
   }

    void setWindresist(float var1) {
      this.windresist = var1;
   }

    float getWaterresist() {
      return this.waterresist;
   }

    void setWaterresist(float var1) {
      this.waterresist = var1;
   }

    bool getObsolete() {
      return this.OBSOLETE;
   }

    std::string getAcceptItemFunction() {
      return this.AcceptItemFunction;
   }

   public std::vector<BloodClothingType> getBloodClothingType() {
      return this.bloodClothingType;
   }

    std::string toString() {
      return this.getClass().getSimpleName()
         + "{Module: "
         + (this.module != nullptr ? this.module.name : "nullptr")
         + ", Name:"
         + this.name
         + ", Type:"
         + this.type
         + "}";
   }

    std::string getReplaceWhenUnequip() {
      return this.replaceWhenUnequip;
   }

    void resolveItemTypes() {
      this.AmmoType = ScriptManager.instance.resolveItemType(this.module, this.AmmoType);
      this.magazineType = ScriptManager.instance.resolveItemType(this.module, this.magazineType);
      if (this.RequireInHandOrInventory != nullptr) {
         for (int var1 = 0; var1 < this.RequireInHandOrInventory.size(); var1++) {
    std::string var2 = this.RequireInHandOrInventory.get(var1);
            var2 = ScriptManager.instance.resolveItemType(this.module, var2);
            this.RequireInHandOrInventory.set(var1, var2);
         }
      }

      if (this.ReplaceTypesMap != nullptr) {
         for (std::string var6 : this.ReplaceTypesMap.keySet()) {
    std::string var3 = this.ReplaceTypesMap.get(var6);
            this.ReplaceTypesMap.replace(var6, ScriptManager.instance.resolveItemType(this.module, var3));
         }
      }
   }

    void resolveModelScripts() {
      this.staticModel = ScriptManager.instance.resolveModelScript(this.module, this.staticModel);
      this.worldStaticModel = ScriptManager.instance.resolveModelScript(this.module, this.worldStaticModel);
   }

    short getRegistry_id() {
      return this.registry_id;
   }

    void setRegistry_id(short var1) {
      if (this.registry_id != -1) {
         WorldDictionary.DebugPrintItem(var1);
         throw RuntimeException(
            "Cannot override existing registry id ("
               + this.registry_id
               + ") to std::make_shared<id>("
               + var1
               + "), item: "
               + (this.getFullName() != nullptr ? this.getFullName() : "unknown")
         );
      } else {
         this.registry_id = var1;
      }
   }

    std::string getModID() {
      return this.modID;
   }

    bool getExistsAsVanilla() {
      return this.existsAsVanilla;
   }

    std::string getFileAbsPath() {
      return this.fileAbsPath;
   }

    void setModID(const std::string& var1) {
      if (GameClient.bClient) {
         if (this.modID == nullptr) {
            this.modID = var1;
         } else if (!var1 == this.modID) && Core.bDebug) {
            WorldDictionary.DebugPrintItem(this);
            throw RuntimeException("Cannot override modID. ModID=" + (var1 != nullptr ? var1 : "nullptr"));
         }
      }
   }

    std::string getRecordedMediaCat() {
      return this.recordedMediaCat;
   }

    bool isWorldRender() {
      return this.worldRender;
   }

    bool isCantEat() {
      return this.CantEat;
   }

    std::string getLuaCreate() {
      return this.LuaCreate;
   }

    void setLuaCreate(const std::string& var1) {
      this.LuaCreate = var1;
   }

    std::string getSoundParameter(const std::string& var1) {
      return this.soundParameterMap == nullptr ? nullptr : this.soundParameterMap.get(var1);
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
