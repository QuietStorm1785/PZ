package zombie.scripting.objects;

import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;
import se.krka.kahlua.vm.KahluaTable;
import zombie.GameWindow;
import zombie.Lua.LuaManager;
import zombie.characterTextures.BloodClothingType;
import zombie.core.Color;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.Translator;
import zombie.core.skinnedmodel.population.ClothingItem;
import zombie.core.skinnedmodel.population.OutfitRNG;
import zombie.core.textures.Texture;
import zombie.debug.DebugLog;
import zombie.gameStates.GameLoadingState;
import zombie.inventory.InventoryItem;
import zombie.inventory.types.AlarmClock;
import zombie.inventory.types.AlarmClockClothing;
import zombie.inventory.types.Clothing;
import zombie.inventory.types.ComboItem;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Food;
import zombie.inventory.types.HandWeapon;
import zombie.inventory.types.InventoryContainer;
import zombie.inventory.types.Key;
import zombie.inventory.types.KeyRing;
import zombie.inventory.types.Literature;
import zombie.inventory.types.MapItem;
import zombie.inventory.types.Moveable;
import zombie.inventory.types.Radio;
import zombie.inventory.types.WeaponPart;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.radio.devices.DeviceData;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item.Type;
import zombie.util.StringUtils;
import zombie.world.WorldDictionary;
import zombie.worldMap.MapDefinitions;

public final class Item extends BaseScriptObject {
   public String clothingExtraSubmenu = null;
   public String DisplayName = null;
   public boolean Hidden = false;
   public boolean CantEat = false;
   public String Icon = "None";
   public boolean Medical = false;
   public boolean CannedFood = false;
   public boolean SurvivalGear = false;
   public boolean MechanicsItem = false;
   public boolean UseWorldItem = false;
   public float ScaleWorldIcon = 1.0F;
   public String CloseKillMove = null;
   public float WeaponLength = 0.4F;
   public float ActualWeight = 1.0F;
   public float WeightWet = 0.0F;
   public float WeightEmpty = 0.0F;
   public float HungerChange = 0.0F;
   public float CriticalChance = 20.0F;
   public int Count = 1;
   public int DaysFresh = 1000000000;
   public int DaysTotallyRotten = 1000000000;
   public int MinutesToCook = 60;
   public int MinutesToBurn = 120;
   public boolean IsCookable = false;
   private String CookingSound = null;
   public float StressChange = 0.0F;
   public float BoredomChange = 0.0F;
   public float UnhappyChange = 0.0F;
   public boolean AlwaysWelcomeGift = false;
   public String ReplaceOnDeplete = null;
   public boolean Ranged = false;
   public boolean CanStoreWater = false;
   public float MaxRange = 1.0F;
   public float MinRange = 0.0F;
   public float ThirstChange = 0.0F;
   public float FatigueChange = 0.0F;
   public float MinAngle = 1.0F;
   public boolean RequiresEquippedBothHands = false;
   public float MaxDamage = 1.5F;
   public float MinDamage = 0.0F;
   public float MinimumSwingTime = 0.0F;
   public String SwingSound = "BaseballBatSwing";
   public String WeaponSprite;
   public boolean AngleFalloff = false;
   public int SoundVolume = 0;
   public float ToHitModifier = 1.0F;
   public int SoundRadius = 0;
   public float OtherCharacterVolumeBoost;
   public final ArrayList<String> Categories = new ArrayList<>();
   public final ArrayList<String> Tags = new ArrayList<>();
   public String ImpactSound = "BaseballBatHit";
   public float SwingTime = 1.0F;
   public boolean KnockBackOnNoDeath = true;
   public boolean SplatBloodOnNoDeath = false;
   public float SwingAmountBeforeImpact = 0.0F;
   public String AmmoType = null;
   public int maxAmmo = 0;
   public String GunType = null;
   public int DoorDamage = 1;
   public int ConditionLowerChance = 1000000;
   public int ConditionMax = 10;
   public boolean CanBandage = false;
   public String name;
   public String moduleDotType;
   public int MaxHitCount = 1000;
   public boolean UseSelf = false;
   public boolean OtherHandUse = false;
   public String OtherHandRequire;
   public String PhysicsObject;
   public String SwingAnim = "Rifle";
   public float WeaponWeight = 1.0F;
   public float EnduranceChange = 0.0F;
   public String IdleAnim = "Idle";
   public String RunAnim = "Run";
   public String attachmentType = null;
   public String makeUpType = null;
   public String consolidateOption = null;
   public ArrayList<String> RequireInHandOrInventory = null;
   public String DoorHitSound = "BaseballBatHit";
   public String ReplaceOnUse = null;
   public boolean DangerousUncooked = false;
   public boolean Alcoholic = false;
   public float PushBackMod = 1.0F;
   public int SplatNumber = 2;
   public float NPCSoundBoost = 1.0F;
   public boolean RangeFalloff = false;
   public boolean UseEndurance = true;
   public boolean MultipleHitConditionAffected = true;
   public boolean ShareDamage = true;
   public boolean ShareEndurance = false;
   public boolean CanBarricade = false;
   public boolean UseWhileEquipped = true;
   public boolean UseWhileUnequipped = false;
   public int TicksPerEquipUse = 30;
   public boolean DisappearOnUse = true;
   public float UseDelta = 0.03125F;
   public boolean AlwaysKnockdown = false;
   public float EnduranceMod = 1.0F;
   public float KnockdownMod = 1.0F;
   public boolean CantAttackWithLowestEndurance = false;
   public String ReplaceOnUseOn = null;
   private String ReplaceTypes = null;
   private HashMap<String, String> ReplaceTypesMap = null;
   public boolean IsWaterSource = false;
   public ArrayList<String> attachmentsProvided = null;
   public String FoodType = null;
   public boolean Poison = false;
   public Integer PoisonDetectionLevel = null;
   public int PoisonPower = 0;
   public KahluaTable DefaultModData = null;
   public boolean IsAimedFirearm = false;
   public boolean IsAimedHandWeapon = false;
   public boolean CanStack = true;
   public float AimingMod = 1.0F;
   public int ProjectileCount = 1;
   public float HitAngleMod = 0.0F;
   public float SplatSize = 1.0F;
   public float Temperature = 0.0F;
   public int NumberOfPages = -1;
   public int LvlSkillTrained = -1;
   public int NumLevelsTrained = 1;
   public String SkillTrained = "";
   public int Capacity = 0;
   public int WeightReduction = 0;
   public String SubCategory = "";
   public boolean ActivatedItem = false;
   public float LightStrength = 0.0F;
   public boolean TorchCone = false;
   public int LightDistance = 0;
   public String CanBeEquipped = "";
   public boolean TwoHandWeapon = false;
   public String CustomContextMenu = null;
   public String Tooltip = null;
   public List<String> ReplaceOnCooked = null;
   public String DisplayCategory = null;
   public Boolean Trap = false;
   public boolean OBSOLETE = false;
   public boolean FishingLure = false;
   public boolean canBeWrite = false;
   public int AimingPerkCritModifier = 0;
   public float AimingPerkRangeModifier = 0.0F;
   public float AimingPerkHitChanceModifier = 0.0F;
   public int HitChance = 0;
   public float AimingPerkMinAngleModifier = 0.0F;
   public int RecoilDelay = 0;
   public boolean PiercingBullets = false;
   public float SoundGain = 1.0F;
   public boolean ProtectFromRainWhenEquipped = false;
   private float maxRangeModifier = 0.0F;
   private float minRangeRangedModifier = 0.0F;
   private float damageModifier = 0.0F;
   private float recoilDelayModifier = 0.0F;
   private int clipSizeModifier = 0;
   private ArrayList<String> mountOn = null;
   private String partType = null;
   private int ClipSize = 0;
   private int reloadTime = 0;
   private int reloadTimeModifier = 0;
   private int aimingTime = 0;
   private int aimingTimeModifier = 0;
   private int hitChanceModifier = 0;
   private float angleModifier = 0.0F;
   private float weightModifier = 0.0F;
   private int PageToWrite = 0;
   private boolean RemoveNegativeEffectOnCooked = false;
   private int treeDamage = 0;
   private float alcoholPower = 0.0F;
   private String PutInSound = null;
   private String PlaceOneSound = null;
   private String PlaceMultipleSound = null;
   private String OpenSound = null;
   private String CloseSound = null;
   private String breakSound = null;
   private String customEatSound = null;
   private String fillFromDispenserSound = null;
   private String fillFromTapSound = null;
   private String bulletOutSound = null;
   private String ShellFallSound = null;
   private HashMap<String, String> SoundMap = null;
   private float bandagePower = 0.0F;
   private float ReduceInfectionPower = 0.0F;
   private String OnCooked = null;
   private String OnlyAcceptCategory = null;
   private String AcceptItemFunction = null;
   private boolean padlock = false;
   private boolean digitalPadlock = false;
   private List<String> teachedRecipes = null;
   private int triggerExplosionTimer = 0;
   private boolean canBePlaced = false;
   private int explosionRange = 0;
   private int explosionPower = 0;
   private int fireRange = 0;
   private int firePower = 0;
   private int smokeRange = 0;
   private int noiseRange = 0;
   private int noiseDuration = 0;
   private float extraDamage = 0.0F;
   private int explosionTimer = 0;
   private String PlacedSprite = null;
   private boolean canBeReused = false;
   private int sensorRange = 0;
   private boolean canBeRemote = false;
   private boolean remoteController = false;
   private int remoteRange = 0;
   private String countDownSound = null;
   private String explosionSound = null;
   private int fluReduction = 0;
   private int ReduceFoodSickness = 0;
   private int painReduction = 0;
   private float rainFactor = 0.0F;
   public float torchDot = 0.96F;
   public int colorRed = 255;
   public int colorGreen = 255;
   public int colorBlue = 255;
   public boolean twoWay = false;
   public int transmitRange = 0;
   public int micRange = 0;
   public float baseVolumeRange = 0.0F;
   public boolean isPortable = false;
   public boolean isTelevision = false;
   public int minChannel = 88000;
   public int maxChannel = 108000;
   public boolean usesBattery = false;
   public boolean isHighTier = false;
   public String HerbalistType;
   private float carbohydrates = 0.0F;
   private float lipids = 0.0F;
   private float proteins = 0.0F;
   private float calories = 0.0F;
   private boolean packaged = false;
   private boolean cantBeFrozen = false;
   private String evolvedRecipeName = null;
   private String ReplaceOnRotten = null;
   private float metalValue = 0.0F;
   private String AlarmSound = null;
   private String itemWhenDry = null;
   private float wetCooldown = 0.0F;
   private boolean isWet = false;
   private String onEat = null;
   private boolean cantBeConsolided = false;
   private boolean BadInMicrowave = false;
   private boolean GoodHot = false;
   private boolean BadCold = false;
   public String map = null;
   private boolean keepOnDeplete = false;
   public int vehicleType = 0;
   private int maxCapacity = -1;
   private int itemCapacity = -1;
   private boolean ConditionAffectsCapacity = false;
   private float brakeForce = 0.0F;
   private int chanceToSpawnDamaged = 0;
   private float conditionLowerNormal = 0.0F;
   private float conditionLowerOffroad = 0.0F;
   private float wheelFriction = 0.0F;
   private float suspensionDamping = 0.0F;
   private float suspensionCompression = 0.0F;
   private float engineLoudness = 0.0F;
   public String ClothingItem = null;
   private ClothingItem clothingItemAsset = null;
   private String staticModel = null;
   public String primaryAnimMask = null;
   public String secondaryAnimMask = null;
   public String primaryAnimMaskAttachment = null;
   public String secondaryAnimMaskAttachment = null;
   public String replaceInSecondHand = null;
   public String replaceInPrimaryHand = null;
   public String replaceWhenUnequip = null;
   public ItemReplacement replacePrimaryHand = null;
   public ItemReplacement replaceSecondHand = null;
   public String worldObjectSprite = null;
   public String ItemName;
   public Texture NormalTexture;
   public List<Texture> SpecialTextures = new ArrayList<>();
   public List<String> SpecialWorldTextureNames = new ArrayList<>();
   public String WorldTextureName;
   public Texture WorldTexture;
   public String eatType;
   private ArrayList<String> IconsForTexture;
   private float baseSpeed = 1.0F;
   private ArrayList<BloodClothingType> bloodClothingType;
   private float stompPower = 1.0F;
   public float runSpeedModifier = 1.0F;
   public float combatSpeedModifier = 1.0F;
   public ArrayList<String> clothingItemExtra;
   public ArrayList<String> clothingItemExtraOption;
   private Boolean removeOnBroken = false;
   public Boolean canHaveHoles = true;
   private boolean cosmetic = false;
   private String ammoBox = null;
   public boolean hairDye = false;
   private String insertAmmoStartSound = null;
   private String insertAmmoSound = null;
   private String insertAmmoStopSound = null;
   private String ejectAmmoStartSound = null;
   private String ejectAmmoSound = null;
   private String ejectAmmoStopSound = null;
   private String rackSound = null;
   private String clickSound = "Stormy9mmClick";
   private String equipSound = null;
   private String unequipSound = null;
   private String bringToBearSound = null;
   private String magazineType = null;
   private String weaponReloadType = null;
   private boolean rackAfterShoot = false;
   private float jamGunChance = 1.0F;
   private ArrayList<ModelWeaponPart> modelWeaponPart = null;
   private boolean haveChamber = true;
   private boolean manuallyRemoveSpentRounds = false;
   private float biteDefense = 0.0F;
   private float scratchDefense = 0.0F;
   private float bulletDefense = 0.0F;
   private String damageCategory = null;
   private boolean damageMakeHole = false;
   public float neckProtectionModifier = 1.0F;
   private String attachmentReplacement = null;
   private boolean insertAllBulletsReload = false;
   private int chanceToFall = 0;
   public String fabricType = null;
   public boolean equippedNoSprint = false;
   public String worldStaticModel = null;
   private float critDmgMultiplier = 0.0F;
   private float insulation = 0.0F;
   private float windresist = 0.0F;
   private float waterresist = 0.0F;
   private String fireMode = null;
   private ArrayList<String> fireModePossibilities = null;
   public boolean RemoveUnhappinessWhenCooked = false;
   private short registry_id = -1;
   private boolean existsAsVanilla = false;
   private String modID;
   private String fileAbsPath;
   public float stopPower = 5.0F;
   private String recordedMediaCat;
   private byte acceptMediaType = -1;
   private boolean noTransmit = false;
   private boolean worldRender = true;
   private String LuaCreate = null;
   private HashMap<String, String> soundParameterMap = null;
   public String HitSound = "BaseballBatHit";
   public String hitFloorSound = "BatOnFloor";
   public String BodyLocation = "";
   public Stack<String> PaletteChoices = new Stack<>();
   public String SpriteName = null;
   public String PalettesStart = "";
   public static HashMap<Integer, String> NetIDToItem = new HashMap<>();
   public static HashMap<String, Integer> NetItemToID = new HashMap<>();
   static int IDMax = 0;
   public Type type = Type.Normal;
   private boolean Spice = false;
   private int UseForPoison;

   public String getDisplayName() {
      return this.DisplayName;
   }

   public void setDisplayName(String var1) {
      this.DisplayName = var1;
   }

   public boolean isHidden() {
      return this.Hidden;
   }

   public String getDisplayCategory() {
      return this.DisplayCategory;
   }

   public String getIcon() {
      return this.Icon;
   }

   public void setIcon(String var1) {
      this.Icon = var1;
   }

   public int getNoiseDuration() {
      return this.noiseDuration;
   }

   public Texture getNormalTexture() {
      return this.NormalTexture;
   }

   public int getNumberOfPages() {
      return this.NumberOfPages;
   }

   public float getActualWeight() {
      return this.ActualWeight;
   }

   public void setActualWeight(float var1) {
      this.ActualWeight = var1;
   }

   public float getWeightWet() {
      return this.WeightWet;
   }

   public void setWeightWet(float var1) {
      this.WeightWet = var1;
   }

   public float getWeightEmpty() {
      return this.WeightEmpty;
   }

   public void setWeightEmpty(float var1) {
      this.WeightEmpty = var1;
   }

   public float getHungerChange() {
      return this.HungerChange;
   }

   public void setHungerChange(float var1) {
      this.HungerChange = var1;
   }

   public float getThirstChange() {
      return this.ThirstChange;
   }

   public void setThirstChange(float var1) {
      this.ThirstChange = var1;
   }

   public int getCount() {
      return this.Count;
   }

   public void setCount(int var1) {
      this.Count = var1;
   }

   public int getDaysFresh() {
      return this.DaysFresh;
   }

   public void setDaysFresh(int var1) {
      this.DaysFresh = var1;
   }

   public int getDaysTotallyRotten() {
      return this.DaysTotallyRotten;
   }

   public void setDaysTotallyRotten(int var1) {
      this.DaysTotallyRotten = var1;
   }

   public int getMinutesToCook() {
      return this.MinutesToCook;
   }

   public void setMinutesToCook(int var1) {
      this.MinutesToCook = var1;
   }

   public int getMinutesToBurn() {
      return this.MinutesToBurn;
   }

   public void setMinutesToBurn(int var1) {
      this.MinutesToBurn = var1;
   }

   public boolean isIsCookable() {
      return this.IsCookable;
   }

   public void setIsCookable(boolean var1) {
      this.IsCookable = var1;
   }

   public String getCookingSound() {
      return this.CookingSound;
   }

   public float getStressChange() {
      return this.StressChange;
   }

   public void setStressChange(float var1) {
      this.StressChange = var1;
   }

   public float getBoredomChange() {
      return this.BoredomChange;
   }

   public void setBoredomChange(float var1) {
      this.BoredomChange = var1;
   }

   public float getUnhappyChange() {
      return this.UnhappyChange;
   }

   public void setUnhappyChange(float var1) {
      this.UnhappyChange = var1;
   }

   public boolean isAlwaysWelcomeGift() {
      return this.AlwaysWelcomeGift;
   }

   public void setAlwaysWelcomeGift(boolean var1) {
      this.AlwaysWelcomeGift = var1;
   }

   public boolean isRanged() {
      return this.Ranged;
   }

   public boolean getCanStoreWater() {
      return this.CanStoreWater;
   }

   public void setRanged(boolean var1) {
      this.Ranged = var1;
   }

   public float getMaxRange() {
      return this.MaxRange;
   }

   public void setMaxRange(float var1) {
      this.MaxRange = var1;
   }

   public float getMinAngle() {
      return this.MinAngle;
   }

   public void setMinAngle(float var1) {
      this.MinAngle = var1;
   }

   public float getMaxDamage() {
      return this.MaxDamage;
   }

   public void setMaxDamage(float var1) {
      this.MaxDamage = var1;
   }

   public float getMinDamage() {
      return this.MinDamage;
   }

   public void setMinDamage(float var1) {
      this.MinDamage = var1;
   }

   public float getMinimumSwingTime() {
      return this.MinimumSwingTime;
   }

   public void setMinimumSwingTime(float var1) {
      this.MinimumSwingTime = var1;
   }

   public String getSwingSound() {
      return this.SwingSound;
   }

   public void setSwingSound(String var1) {
      this.SwingSound = var1;
   }

   public String getWeaponSprite() {
      return this.WeaponSprite;
   }

   public void setWeaponSprite(String var1) {
      this.WeaponSprite = var1;
   }

   public boolean isAngleFalloff() {
      return this.AngleFalloff;
   }

   public void setAngleFalloff(boolean var1) {
      this.AngleFalloff = var1;
   }

   public int getSoundVolume() {
      return this.SoundVolume;
   }

   public void setSoundVolume(int var1) {
      this.SoundVolume = var1;
   }

   public float getToHitModifier() {
      return this.ToHitModifier;
   }

   public void setToHitModifier(float var1) {
      this.ToHitModifier = var1;
   }

   public int getSoundRadius() {
      return this.SoundRadius;
   }

   public void setSoundRadius(int var1) {
      this.SoundRadius = var1;
   }

   public float getOtherCharacterVolumeBoost() {
      return this.OtherCharacterVolumeBoost;
   }

   public void setOtherCharacterVolumeBoost(float var1) {
      this.OtherCharacterVolumeBoost = var1;
   }

   public ArrayList<String> getCategories() {
      return this.Categories;
   }

   public void setCategories(ArrayList<String> var1) {
      this.Categories.clear();
      this.Categories.addAll(var1);
   }

   public ArrayList<String> getTags() {
      return this.Tags;
   }

   public String getImpactSound() {
      return this.ImpactSound;
   }

   public void setImpactSound(String var1) {
      this.ImpactSound = var1;
   }

   public float getSwingTime() {
      return this.SwingTime;
   }

   public void setSwingTime(float var1) {
      this.SwingTime = var1;
   }

   public boolean isKnockBackOnNoDeath() {
      return this.KnockBackOnNoDeath;
   }

   public void setKnockBackOnNoDeath(boolean var1) {
      this.KnockBackOnNoDeath = var1;
   }

   public boolean isSplatBloodOnNoDeath() {
      return this.SplatBloodOnNoDeath;
   }

   public void setSplatBloodOnNoDeath(boolean var1) {
      this.SplatBloodOnNoDeath = var1;
   }

   public float getSwingAmountBeforeImpact() {
      return this.SwingAmountBeforeImpact;
   }

   public void setSwingAmountBeforeImpact(float var1) {
      this.SwingAmountBeforeImpact = var1;
   }

   public String getAmmoType() {
      return this.AmmoType;
   }

   public void setAmmoType(String var1) {
      this.AmmoType = var1;
   }

   public int getDoorDamage() {
      return this.DoorDamage;
   }

   public void setDoorDamage(int var1) {
      this.DoorDamage = var1;
   }

   public int getConditionLowerChance() {
      return this.ConditionLowerChance;
   }

   public void setConditionLowerChance(int var1) {
      this.ConditionLowerChance = var1;
   }

   public int getConditionMax() {
      return this.ConditionMax;
   }

   public void setConditionMax(int var1) {
      this.ConditionMax = var1;
   }

   public boolean isCanBandage() {
      return this.CanBandage;
   }

   public void setCanBandage(boolean var1) {
      this.CanBandage = var1;
   }

   public boolean isCosmetic() {
      return this.cosmetic;
   }

   public String getName() {
      return this.name;
   }

   public String getModuleName() {
      return this.module.name;
   }

   public String getFullName() {
      return this.moduleDotType;
   }

   public void setName(String var1) {
      this.name = var1;
      this.moduleDotType = this.module.name + "." + var1;
   }

   public int getMaxHitCount() {
      return this.MaxHitCount;
   }

   public void setMaxHitCount(int var1) {
      this.MaxHitCount = var1;
   }

   public boolean isUseSelf() {
      return this.UseSelf;
   }

   public void setUseSelf(boolean var1) {
      this.UseSelf = var1;
   }

   public boolean isOtherHandUse() {
      return this.OtherHandUse;
   }

   public void setOtherHandUse(boolean var1) {
      this.OtherHandUse = var1;
   }

   public String getOtherHandRequire() {
      return this.OtherHandRequire;
   }

   public void setOtherHandRequire(String var1) {
      this.OtherHandRequire = var1;
   }

   public String getPhysicsObject() {
      return this.PhysicsObject;
   }

   public void setPhysicsObject(String var1) {
      this.PhysicsObject = var1;
   }

   public String getSwingAnim() {
      return this.SwingAnim;
   }

   public void setSwingAnim(String var1) {
      this.SwingAnim = var1;
   }

   public float getWeaponWeight() {
      return this.WeaponWeight;
   }

   public void setWeaponWeight(float var1) {
      this.WeaponWeight = var1;
   }

   public float getEnduranceChange() {
      return this.EnduranceChange;
   }

   public void setEnduranceChange(float var1) {
      this.EnduranceChange = var1;
   }

   public String getBreakSound() {
      return this.breakSound;
   }

   public String getBulletOutSound() {
      return this.bulletOutSound;
   }

   public String getCloseSound() {
      return this.CloseSound;
   }

   public String getClothingItem() {
      return this.ClothingItem;
   }

   public void setClothingItemAsset(ClothingItem var1) {
      this.clothingItemAsset = var1;
   }

   public ClothingItem getClothingItemAsset() {
      return this.clothingItemAsset;
   }

   public ArrayList<String> getClothingItemExtra() {
      return this.clothingItemExtra;
   }

   public ArrayList<String> getClothingItemExtraOption() {
      return this.clothingItemExtraOption;
   }

   public String getFabricType() {
      return this.fabricType;
   }

   public ArrayList<String> getIconsForTexture() {
      return this.IconsForTexture;
   }

   public String getCustomEatSound() {
      return this.customEatSound;
   }

   public String getFillFromDispenserSound() {
      return this.fillFromDispenserSound;
   }

   public String getFillFromTapSound() {
      return this.fillFromTapSound;
   }

   public String getEatType() {
      return this.eatType;
   }

   public String getCountDownSound() {
      return this.countDownSound;
   }

   public String getBringToBearSound() {
      return this.bringToBearSound;
   }

   public String getEjectAmmoStartSound() {
      return this.ejectAmmoStartSound;
   }

   public String getEjectAmmoSound() {
      return this.ejectAmmoSound;
   }

   public String getEjectAmmoStopSound() {
      return this.ejectAmmoStopSound;
   }

   public String getInsertAmmoStartSound() {
      return this.insertAmmoStartSound;
   }

   public String getInsertAmmoSound() {
      return this.insertAmmoSound;
   }

   public String getInsertAmmoStopSound() {
      return this.insertAmmoStopSound;
   }

   public String getEquipSound() {
      return this.equipSound;
   }

   public String getUnequipSound() {
      return this.unequipSound;
   }

   public String getExplosionSound() {
      return this.explosionSound;
   }

   public String getStaticModel() {
      return this.staticModel;
   }

   public String getOpenSound() {
      return this.OpenSound;
   }

   public String getPutInSound() {
      return this.PutInSound;
   }

   public String getPlaceOneSound() {
      return this.PlaceOneSound;
   }

   public String getPlaceMultipleSound() {
      return this.PlaceMultipleSound;
   }

   public String getShellFallSound() {
      return this.ShellFallSound;
   }

   public String getSoundByID(String var1) {
      return this.SoundMap == null ? null : this.SoundMap.getOrDefault(var1, null);
   }

   public String getSkillTrained() {
      return this.SkillTrained;
   }

   public String getDoorHitSound() {
      return this.DoorHitSound;
   }

   public void setDoorHitSound(String var1) {
      this.DoorHitSound = var1;
   }

   public boolean isManuallyRemoveSpentRounds() {
      return this.manuallyRemoveSpentRounds;
   }

   public float getRainFactor() {
      return this.rainFactor;
   }

   public String getReplaceOnUse() {
      return this.ReplaceOnUse;
   }

   public void setReplaceOnUse(String var1) {
      this.ReplaceOnUse = var1;
   }

   public String getReplaceOnDeplete() {
      return this.ReplaceOnDeplete;
   }

   public void setReplaceOnDeplete(String var1) {
      this.ReplaceOnDeplete = var1;
   }

   public String getReplaceTypes() {
      return this.ReplaceTypes;
   }

   public HashMap<String, String> getReplaceTypesMap() {
      return this.ReplaceTypesMap;
   }

   public String getReplaceType(String var1) {
      return this.ReplaceTypesMap == null ? null : this.ReplaceTypesMap.get(var1);
   }

   public boolean hasReplaceType(String var1) {
      return this.getReplaceType(var1) != null;
   }

   public boolean isDangerousUncooked() {
      return this.DangerousUncooked;
   }

   public void setDangerousUncooked(boolean var1) {
      this.DangerousUncooked = var1;
   }

   public boolean isAlcoholic() {
      return this.Alcoholic;
   }

   public void setAlcoholic(boolean var1) {
      this.Alcoholic = var1;
   }

   public float getPushBackMod() {
      return this.PushBackMod;
   }

   public void setPushBackMod(float var1) {
      this.PushBackMod = var1;
   }

   public int getSplatNumber() {
      return this.SplatNumber;
   }

   public void setSplatNumber(int var1) {
      this.SplatNumber = var1;
   }

   public float getNPCSoundBoost() {
      return this.NPCSoundBoost;
   }

   public void setNPCSoundBoost(float var1) {
      this.NPCSoundBoost = var1;
   }

   public boolean isRangeFalloff() {
      return this.RangeFalloff;
   }

   public void setRangeFalloff(boolean var1) {
      this.RangeFalloff = var1;
   }

   public boolean isUseEndurance() {
      return this.UseEndurance;
   }

   public void setUseEndurance(boolean var1) {
      this.UseEndurance = var1;
   }

   public boolean isMultipleHitConditionAffected() {
      return this.MultipleHitConditionAffected;
   }

   public void setMultipleHitConditionAffected(boolean var1) {
      this.MultipleHitConditionAffected = var1;
   }

   public boolean isShareDamage() {
      return this.ShareDamage;
   }

   public void setShareDamage(boolean var1) {
      this.ShareDamage = var1;
   }

   public boolean isShareEndurance() {
      return this.ShareEndurance;
   }

   public void setShareEndurance(boolean var1) {
      this.ShareEndurance = var1;
   }

   public boolean isCanBarricade() {
      return this.CanBarricade;
   }

   public void setCanBarricade(boolean var1) {
      this.CanBarricade = var1;
   }

   public boolean isUseWhileEquipped() {
      return this.UseWhileEquipped;
   }

   public void setUseWhileEquipped(boolean var1) {
      this.UseWhileEquipped = var1;
   }

   public boolean isUseWhileUnequipped() {
      return this.UseWhileUnequipped;
   }

   public void setUseWhileUnequipped(boolean var1) {
      this.UseWhileUnequipped = var1;
   }

   public void setTicksPerEquipUse(int var1) {
      this.TicksPerEquipUse = var1;
   }

   public float getTicksPerEquipUse() {
      return this.TicksPerEquipUse;
   }

   public boolean isDisappearOnUse() {
      return this.DisappearOnUse;
   }

   public void setDisappearOnUse(boolean var1) {
      this.DisappearOnUse = var1;
   }

   public float getUseDelta() {
      return this.UseDelta;
   }

   public void setUseDelta(float var1) {
      this.UseDelta = var1;
   }

   public boolean isAlwaysKnockdown() {
      return this.AlwaysKnockdown;
   }

   public void setAlwaysKnockdown(boolean var1) {
      this.AlwaysKnockdown = var1;
   }

   public float getEnduranceMod() {
      return this.EnduranceMod;
   }

   public void setEnduranceMod(float var1) {
      this.EnduranceMod = var1;
   }

   public float getKnockdownMod() {
      return this.KnockdownMod;
   }

   public void setKnockdownMod(float var1) {
      this.KnockdownMod = var1;
   }

   public boolean isCantAttackWithLowestEndurance() {
      return this.CantAttackWithLowestEndurance;
   }

   public void setCantAttackWithLowestEndurance(boolean var1) {
      this.CantAttackWithLowestEndurance = var1;
   }

   public String getBodyLocation() {
      return this.BodyLocation;
   }

   public void setBodyLocation(String var1) {
      this.BodyLocation = var1;
   }

   public Stack<String> getPaletteChoices() {
      return this.PaletteChoices;
   }

   public void setPaletteChoices(Stack<String> var1) {
      this.PaletteChoices = var1;
   }

   public String getSpriteName() {
      return this.SpriteName;
   }

   public void setSpriteName(String var1) {
      this.SpriteName = var1;
   }

   public String getPalettesStart() {
      return this.PalettesStart;
   }

   public void setPalettesStart(String var1) {
      this.PalettesStart = var1;
   }

   public Type getType() {
      return this.type;
   }

   public void setType(Type var1) {
      this.type = var1;
   }

   public String getTypeString() {
      return this.type.name();
   }

   public String getMapID() {
      return this.map;
   }

   public void Load(String var1, String[] var2) {
      this.name = var1;
      this.moduleDotType = this.module.name + "." + var1;
      int var3 = IDMax++;
      NetIDToItem.put(var3, this.moduleDotType);
      NetItemToID.put(this.moduleDotType, var3);
      this.modID = ScriptManager.getCurrentLoadFileMod();
      if (this.modID.equals("pz-vanilla")) {
         this.existsAsVanilla = true;
      }

      this.fileAbsPath = ScriptManager.getCurrentLoadFileAbsPath();

      for (String var7 : var2) {
         this.DoParam(var7);
      }

      if (this.DisplayName == null) {
         this.DisplayName = this.getFullName();
         this.Hidden = true;
      }

      if (!StringUtils.isNullOrWhitespace(this.replaceInPrimaryHand)) {
         String[] var8 = this.replaceInPrimaryHand.trim().split("\\s+");
         if (var8.length == 2) {
            this.replacePrimaryHand = new ItemReplacement();
            this.replacePrimaryHand.clothingItemName = var8[0].trim();
            this.replacePrimaryHand.maskVariableValue = var8[1].trim();
            this.replacePrimaryHand.maskVariableName = "RightHandMask";
         }
      }

      if (!StringUtils.isNullOrWhitespace(this.replaceInSecondHand)) {
         String[] var9 = this.replaceInSecondHand.trim().split("\\s+");
         if (var9.length == 2) {
            this.replaceSecondHand = new ItemReplacement();
            this.replaceSecondHand.clothingItemName = var9[0].trim();
            this.replaceSecondHand.maskVariableValue = var9[1].trim();
            this.replaceSecondHand.maskVariableName = "LeftHandMask";
         }
      }

      if (!StringUtils.isNullOrWhitespace(this.primaryAnimMask)) {
         this.replacePrimaryHand = new ItemReplacement();
         this.replacePrimaryHand.maskVariableValue = this.primaryAnimMask;
         this.replacePrimaryHand.maskVariableName = "RightHandMask";
         this.replacePrimaryHand.attachment = this.primaryAnimMaskAttachment;
      }

      if (!StringUtils.isNullOrWhitespace(this.secondaryAnimMask)) {
         this.replaceSecondHand = new ItemReplacement();
         this.replaceSecondHand.maskVariableValue = this.secondaryAnimMask;
         this.replaceSecondHand.maskVariableName = "LeftHandMask";
         this.replaceSecondHand.attachment = this.secondaryAnimMaskAttachment;
      }

      WorldDictionary.onLoadItem(this);
   }

   public InventoryItem InstanceItem(String var1) {
      Object var2 = null;
      if (this.type == Type.Key) {
         var2 = new Key(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
         ((Key)var2).setDigitalPadlock(this.digitalPadlock);
         ((Key)var2).setPadlock(this.padlock);
         if (((Key)var2).isPadlock()) {
            ((Key)var2).setNumberOfKey(2);
            ((Key)var2).setKeyId(Rand.Next(10000000));
         }
      }

      if (this.type == Type.KeyRing) {
         var2 = new KeyRing(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
      }

      if (this.type == Type.WeaponPart) {
         var2 = new WeaponPart(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
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
         var2 = new InventoryContainer(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
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
         var2 = new Food(this.module.name, this.DisplayName, this.name, this);
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
         var2 = new Literature(this.module.name, this.DisplayName, this.name, this);
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
         var2 = new AlarmClock(this.module.name, this.DisplayName, this.name, this);
         AlarmClock var9 = (AlarmClock)var2;
         var9.setAlarmSound(this.AlarmSound);
         var9.setSoundRadius(this.SoundRadius);
      } else if (this.type == Type.AlarmClockClothing) {
         String var10 = "";
         String var4 = null;
         if (!this.PaletteChoices.isEmpty() || var1 != null) {
            int var5 = Rand.Next(this.PaletteChoices.size());
            var4 = this.PaletteChoices.get(var5);
            if (var1 != null) {
               var4 = var1;
            }

            var10 = "_" + var4.replace(this.PalettesStart, "");
         }

         var2 = new AlarmClockClothing(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon.replace(".png", "") + var10, var4, this.SpriteName);
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
         var2 = new HandWeapon(this.module.name, this.DisplayName, this.name, this);
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
         var2 = new ComboItem(this.module.name, this.DisplayName, this.name, this);
      } else if (this.type == Type.Clothing) {
         String var12 = "";
         String var18 = null;
         if (!this.PaletteChoices.isEmpty() || var1 != null) {
            int var21 = Rand.Next(this.PaletteChoices.size());
            var18 = this.PaletteChoices.get(var21);
            if (var1 != null) {
               var18 = var1;
            }

            var12 = "_" + var18.replace(this.PalettesStart, "");
         }

         var2 = new Clothing(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon.replace(".png", "") + var12, var18, this.SpriteName);
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
         var2 = new DrainableComboItem(this.module.name, this.DisplayName, this.name, this);
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
         var2 = new Radio(this.module.name, this.DisplayName, this.name, "Item_" + this.Icon);
         Radio var14 = (Radio)var2;
         DeviceData var19 = var14.getDeviceData();
         if (var19 != null) {
            if (this.DisplayName != null) {
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
            DebugLog.log("Item -> Radio item = " + (this.moduleDotType != null ? this.moduleDotType : "unknown"));
         }
      } else if (this.type == Type.Moveable) {
         var2 = new Moveable(this.module.name, this.DisplayName, this.name, this);
         Moveable var15 = (Moveable)var2;
         var15.ReadFromWorldSprite(this.worldObjectSprite);
         this.ActualWeight = var15.getActualWeight();
      } else if (this.type == Type.Map) {
         MapItem var16 = new MapItem(this.module.name, this.DisplayName, this.name, this);
         if (StringUtils.isNullOrWhitespace(this.map)) {
            var16.setMapID(MapDefinitions.getInstance().pickRandom());
         } else {
            var16.setMapID(this.map);
         }

         var2 = var16;
      }

      if (this.colorRed < 255 || this.colorGreen < 255 || this.colorBlue < 255) {
         var2.setColor(new Color(this.colorRed / 255.0F, this.colorGreen / 255.0F, this.colorBlue / 255.0F));
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
      if (this.CustomContextMenu != null) {
         var2.setCustomMenuOption(Translator.getText("ContextMenu_" + this.CustomContextMenu));
      }

      if (this.IconsForTexture != null && !this.IconsForTexture.isEmpty()) {
         var2.setIconsForTexture(this.IconsForTexture);
      }

      var2.setBloodClothingType(this.bloodClothingType);
      ((InventoryItem)var2).CloseKillMove = this.CloseKillMove;
      var2.setAmmoType(this.AmmoType);
      var2.setMaxAmmo(this.maxAmmo);
      var2.setGunType(this.GunType);
      var2.setAttachmentType(this.attachmentType);
      long var17 = OutfitRNG.getSeed();
      OutfitRNG.setSeed(Rand.Next(Integer.MAX_VALUE));
      var2.synchWithVisual();
      OutfitRNG.setSeed(var17);
      var2.setRegistry_id(this);
      Thread var23 = Thread.currentThread();
      if ((var23 == GameWindow.GameThread || var23 == GameLoadingState.loader || var23 == GameServer.MainThread) && !var2.isInitialised()) {
         var2.initialiseItem();
      }

      return (InventoryItem)var2;
   }

   public void DoParam(String var1) {
      if (var1.trim().length() != 0) {
         try {
            String[] var2 = var1.split("=");
            String var3 = var2[0].trim();
            String var4 = var2[1].trim();
            if (var3.trim().equalsIgnoreCase("BodyLocation")) {
               this.BodyLocation = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("Palettes")) {
               String[] var5 = var4.split("/");

               for (int var6 = 0; var6 < var5.length; var6++) {
                  this.PaletteChoices.add(var5[var6].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("HitSound")) {
               this.HitSound = var4.trim();
               if (this.HitSound.equals("null")) {
                  this.HitSound = null;
               }
            } else if (var3.trim().equalsIgnoreCase("HitFloorSound")) {
               this.hitFloorSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PalettesStart")) {
               this.PalettesStart = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("DisplayName")) {
               this.DisplayName = Translator.getDisplayItemName(var4.trim());
               this.DisplayName = Translator.getItemNameFromFullType(this.getFullName());
            } else if (var3.trim().equalsIgnoreCase("MetalValue")) {
               this.metalValue = new Float(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SpriteName")) {
               this.SpriteName = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("Type")) {
               this.type = Type.valueOf(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SplatSize")) {
               this.SplatSize = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CanStoreWater")) {
               this.CanStoreWater = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("IsWaterSource")) {
               this.IsWaterSource = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Poison")) {
               this.Poison = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("FoodType")) {
               this.FoodType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PoisonDetectionLevel")) {
               this.PoisonDetectionLevel = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("PoisonPower")) {
               this.PoisonPower = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UseForPoison")) {
               this.UseForPoison = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingAnim")) {
               this.SwingAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("Icon")) {
               this.Icon = var4;
               this.ItemName = "Item_" + this.Icon;
               this.NormalTexture = Texture.trygetTexture(this.ItemName);
               if (this.NormalTexture == null) {
                  this.NormalTexture = Texture.getSharedTexture("media/inventory/Question_On.png");
               }

               this.WorldTextureName = this.ItemName.replace("Item_", "media/inventory/world/WItem_");
               this.WorldTextureName = this.WorldTextureName + ".png";
               this.WorldTexture = Texture.getSharedTexture(this.WorldTextureName);
               if (this.type == Type.Food) {
                  Texture var17 = Texture.trygetTexture(this.ItemName + "Rotten");
                  String var33 = this.WorldTextureName.replace(".png", "Rotten.png");
                  if (var17 == null) {
                     var17 = Texture.trygetTexture(this.ItemName + "Spoiled");
                     var33 = var33.replace("Rotten.png", "Spoiled.png");
                  }

                  this.SpecialWorldTextureNames.add(var33);
                  this.SpecialTextures.add(var17);
                  this.SpecialTextures.add(Texture.trygetTexture(this.ItemName + "Cooked"));
                  this.SpecialWorldTextureNames.add(this.WorldTextureName.replace(".png", "Cooked.png"));
                  Texture var7 = Texture.trygetTexture(this.ItemName + "Overdone");
                  String var8 = this.WorldTextureName.replace(".png", "Overdone.png");
                  if (var7 == null) {
                     var7 = Texture.trygetTexture(this.ItemName + "Burnt");
                     var8 = var8.replace("Overdone.png", "Burnt.png");
                  }

                  this.SpecialTextures.add(var7);
                  this.SpecialWorldTextureNames.add(var8);
               }
            } else if (var3.trim().equalsIgnoreCase("UseWorldItem")) {
               this.UseWorldItem = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("Medical")) {
               this.Medical = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("CannedFood")) {
               this.CannedFood = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("MechanicsItem")) {
               this.MechanicsItem = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("SurvivalGear")) {
               this.SurvivalGear = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("ScaleWorldIcon")) {
               this.ScaleWorldIcon = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HairDye")) {
               this.hairDye = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("DoorHitSound")) {
               this.DoorHitSound = var4;
            } else if (var3.trim().equalsIgnoreCase("Weight")) {
               this.ActualWeight = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightWet")) {
               this.WeightWet = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightEmpty")) {
               this.WeightEmpty = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HungerChange")) {
               this.HungerChange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ThirstChange")) {
               this.ThirstChange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("FatigueChange")) {
               this.FatigueChange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("EnduranceChange")) {
               this.EnduranceChange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CriticalChance")) {
               this.CriticalChance = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("critDmgMultiplier")) {
               this.critDmgMultiplier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DaysFresh")) {
               this.DaysFresh = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("DaysTotallyRotten")) {
               this.DaysTotallyRotten = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("IsCookable")) {
               this.IsCookable = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CookingSound")) {
               this.CookingSound = var4;
            } else if (var3.trim().equalsIgnoreCase("MinutesToCook")) {
               this.MinutesToCook = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MinutesToBurn")) {
               this.MinutesToBurn = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("BoredomChange")) {
               this.BoredomChange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("StressChange")) {
               this.StressChange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UnhappyChange")) {
               this.UnhappyChange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RemoveUnhappinessWhenCooked")) {
               this.RemoveUnhappinessWhenCooked = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnDeplete")) {
               this.ReplaceOnDeplete = var4;
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnUseOn")) {
               this.ReplaceOnUseOn = var4;
               if (var4.contains("-")) {
                  String[] var18 = var4.split("-");
                  String var34 = var18[0].trim();
                  String var46 = var18[1].trim();
                  if (!var34.isEmpty() && !var46.isEmpty()) {
                     if (this.ReplaceTypesMap == null) {
                        this.ReplaceTypesMap = new HashMap<>();
                     }

                     this.ReplaceTypesMap.put(var34, var46);
                  }
               }
            } else if (var3.trim().equalsIgnoreCase("ReplaceTypes")) {
               this.ReplaceTypes = var4;
               String[] var19 = var4.split(";");

               for (String var9 : var19) {
                  String[] var10 = var9.trim().split("\\s+");
                  if (var10.length == 2) {
                     String var11 = var10[0].trim();
                     String var12 = var10[1].trim();
                     if (!var11.isEmpty() && !var12.isEmpty()) {
                        if (this.ReplaceTypesMap == null) {
                           this.ReplaceTypesMap = new HashMap<>();
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
               this.MaxRange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinRange")) {
               this.MinRange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinAngle")) {
               this.MinAngle = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxDamage")) {
               this.MaxDamage = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("BaseSpeed")) {
               this.baseSpeed = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("stompPower")) {
               this.stompPower = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("combatSpeedModifier")) {
               this.combatSpeedModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("runSpeedModifier")) {
               this.runSpeedModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("clothingItemExtra")) {
               this.clothingItemExtra = new ArrayList<>();
               String[] var20 = var4.split(";");

               for (int var36 = 0; var36 < var20.length; var36++) {
                  this.clothingItemExtra.add(var20[var36]);
               }
            } else if (var3.trim().equalsIgnoreCase("clothingExtraSubmenu")) {
               this.clothingExtraSubmenu = var4;
            } else if (var3.trim().equalsIgnoreCase("removeOnBroken")) {
               this.removeOnBroken = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("canHaveHoles")) {
               this.canHaveHoles = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("Cosmetic")) {
               this.cosmetic = Boolean.parseBoolean(var4);
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
               this.jamGunChance = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("modelWeaponPart")) {
               if (this.modelWeaponPart == null) {
                  this.modelWeaponPart = new ArrayList<>();
               }

               String[] var21 = var4.split("\\s+");
               if (var21.length >= 2 && var21.length <= 4) {
                  ModelWeaponPart var37 = null;

                  for (int var48 = 0; var48 < this.modelWeaponPart.size(); var48++) {
                     ModelWeaponPart var52 = this.modelWeaponPart.get(var48);
                     if (var52.partType.equals(var21[0])) {
                        var37 = var52;
                        break;
                     }
                  }

                  if (var37 == null) {
                     var37 = new ModelWeaponPart();
                  }

                  var37.partType = var21[0];
                  var37.modelName = var21[1];
                  var37.attachmentNameSelf = var21.length > 2 ? var21[2] : null;
                  var37.attachmentParent = var21.length > 3 ? var21[3] : null;
                  if (!var37.partType.contains(".")) {
                     var37.partType = this.module.name + "." + var37.partType;
                  }

                  if (!var37.modelName.contains(".")) {
                     var37.modelName = this.module.name + "." + var37.modelName;
                  }

                  if ("none".equalsIgnoreCase(var37.attachmentNameSelf)) {
                     var37.attachmentNameSelf = null;
                  }

                  if ("none".equalsIgnoreCase(var37.attachmentParent)) {
                     var37.attachmentParent = null;
                  }

                  this.modelWeaponPart.add(var37);
               }
            } else if (var3.trim().equalsIgnoreCase("rackAfterShoot")) {
               this.rackAfterShoot = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("haveChamber")) {
               this.haveChamber = Boolean.parseBoolean(var4);
            } else if (var3.equalsIgnoreCase("ManuallyRemoveSpentRounds")) {
               this.manuallyRemoveSpentRounds = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("biteDefense")) {
               this.biteDefense = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("bulletDefense")) {
               this.bulletDefense = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("neckProtectionModifier")) {
               this.neckProtectionModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("damageCategory")) {
               this.damageCategory = var4;
            } else if (var3.trim().equalsIgnoreCase("fireMode")) {
               this.fireMode = var4;
            } else if (var3.trim().equalsIgnoreCase("damageMakeHole")) {
               this.damageMakeHole = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("equippedNoSprint")) {
               this.equippedNoSprint = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("scratchDefense")) {
               this.scratchDefense = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("weaponReloadType")) {
               this.weaponReloadType = var4;
            } else if (var3.trim().equalsIgnoreCase("insertAllBulletsReload")) {
               this.insertAllBulletsReload = Boolean.parseBoolean(var4);
            } else if (var3.trim().equalsIgnoreCase("clothingItemExtraOption")) {
               this.clothingItemExtraOption = new ArrayList<>();
               String[] var22 = var4.split(";");

               for (int var38 = 0; var38 < var22.length; var38++) {
                  this.clothingItemExtraOption.add(var22[var38]);
               }
            } else if (var3.trim().equalsIgnoreCase("ConditionLowerChanceOneIn")) {
               this.ConditionLowerChance = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MultipleHitConditionAffected")) {
               this.MultipleHitConditionAffected = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CanBandage")) {
               this.CanBandage = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ConditionMax")) {
               this.ConditionMax = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SoundGain")) {
               this.SoundGain = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinDamage")) {
               this.MinDamage = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinimumSwingTime")) {
               this.MinimumSwingTime = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingSound")) {
               this.SwingSound = var4;
            } else if (var3.trim().equalsIgnoreCase("ReplaceOnUse")) {
               this.ReplaceOnUse = var4;
            } else if (var3.trim().equalsIgnoreCase("WeaponSprite")) {
               this.WeaponSprite = var4;
            } else if (var3.trim().equalsIgnoreCase("AimingPerkCritModifier")) {
               this.AimingPerkCritModifier = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkRangeModifier")) {
               this.AimingPerkRangeModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkHitChanceModifier")) {
               this.AimingPerkHitChanceModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AngleModifier")) {
               this.angleModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WeightModifier")) {
               this.weightModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AimingPerkMinAngleModifier")) {
               this.AimingPerkMinAngleModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("HitChance")) {
               this.HitChance = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RecoilDelay")) {
               this.RecoilDelay = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("StopPower")) {
               this.stopPower = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("PiercingBullets")) {
               this.PiercingBullets = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AngleFalloff")) {
               this.AngleFalloff = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SoundVolume")) {
               this.SoundVolume = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ToHitModifier")) {
               this.ToHitModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SoundRadius")) {
               this.SoundRadius = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("Categories")) {
               String[] var23 = var4.split(";");

               for (int var39 = 0; var39 < var23.length; var39++) {
                  this.Categories.add(var23[var39].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("Tags")) {
               String[] var24 = var4.split(";");

               for (int var40 = 0; var40 < var24.length; var40++) {
                  this.Tags.add(var24[var40].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("OtherCharacterVolumeBoost")) {
               this.OtherCharacterVolumeBoost = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ImpactSound")) {
               this.ImpactSound = var4;
               if (this.ImpactSound.equals("null")) {
                  this.ImpactSound = null;
               }
            } else if (var3.trim().equalsIgnoreCase("SwingTime")) {
               this.SwingTime = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("KnockBackOnNoDeath")) {
               this.KnockBackOnNoDeath = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Alcoholic")) {
               this.Alcoholic = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SplatBloodOnNoDeath")) {
               this.SplatBloodOnNoDeath = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("SwingAmountBeforeImpact")) {
               this.SwingAmountBeforeImpact = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("AmmoType")) {
               this.AmmoType = var4;
            } else if (var3.trim().equalsIgnoreCase("maxAmmo")) {
               this.maxAmmo = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("GunType")) {
               this.GunType = var4;
            } else if (var3.trim().equalsIgnoreCase("HitAngleMod")) {
               this.HitAngleMod = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("OtherHandRequire")) {
               this.OtherHandRequire = var4;
            } else if (var3.trim().equalsIgnoreCase("AlwaysWelcomeGift")) {
               this.AlwaysWelcomeGift = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CantAttackWithLowestEndurance")) {
               this.CantAttackWithLowestEndurance = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("EnduranceMod")) {
               this.EnduranceMod = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("KnockdownMod")) {
               this.KnockdownMod = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DoorDamage")) {
               this.DoorDamage = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxHitCount")) {
               this.MaxHitCount = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("PhysicsObject")) {
               this.PhysicsObject = var4;
            } else if (var3.trim().equalsIgnoreCase("Count")) {
               this.Count = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("SwingAnim")) {
               this.SwingAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("WeaponWeight")) {
               this.WeaponWeight = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("IdleAnim")) {
               this.IdleAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("RunAnim")) {
               this.RunAnim = var4;
            } else if (var3.trim().equalsIgnoreCase("RequireInHandOrInventory")) {
               this.RequireInHandOrInventory = new ArrayList<>(Arrays.asList(var4.split("/")));
            } else if (var3.trim().equalsIgnoreCase("fireModePossibilities")) {
               this.fireModePossibilities = new ArrayList<>(Arrays.asList(var4.split("/")));
            } else if (var3.trim().equalsIgnoreCase("attachmentsProvided")) {
               this.attachmentsProvided = new ArrayList<>(Arrays.asList(var4.split(";")));
            } else if (var3.trim().equalsIgnoreCase("attachmentReplacement")) {
               this.attachmentReplacement = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PushBackMod")) {
               this.PushBackMod = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("NPCSoundBoost")) {
               this.NPCSoundBoost = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("SplatNumber")) {
               this.SplatNumber = Integer.parseInt(var4);
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
               String[] var25 = var4.split("\\s+");
               if (var25.length == 2 && !var25[0].trim().isEmpty()) {
                  if (this.SoundMap == null) {
                     this.SoundMap = new HashMap<>();
                  }

                  this.SoundMap.put(var25[0].trim(), var25[1].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("IsAimedHandWeapon")) {
               this.IsAimedHandWeapon = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("AimingMod")) {
               this.AimingMod = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ProjectileCount")) {
               this.ProjectileCount = Integer.parseInt(var4);
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
               this.TicksPerEquipUse = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("DisappearOnUse")) {
               this.DisappearOnUse = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("Temperature")) {
               this.Temperature = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("Insulation")) {
               this.insulation = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WindResistance")) {
               this.windresist = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("WaterResistance")) {
               this.waterresist = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("CloseKillMove")) {
               this.CloseKillMove = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("UseDelta")) {
               this.UseDelta = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("RainFactor")) {
               this.rainFactor = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("TorchDot")) {
               this.torchDot = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("NumberOfPages")) {
               this.NumberOfPages = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("SkillTrained")) {
               this.SkillTrained = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("LvlSkillTrained")) {
               this.LvlSkillTrained = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("NumLevelsTrained")) {
               this.NumLevelsTrained = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Capacity")) {
               this.Capacity = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("MaxCapacity")) {
               this.maxCapacity = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ItemCapacity")) {
               this.itemCapacity = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ConditionAffectsCapacity")) {
               this.ConditionAffectsCapacity = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("BrakeForce")) {
               this.brakeForce = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ChanceToSpawnDamaged")) {
               this.chanceToSpawnDamaged = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WeaponLength")) {
               this.WeaponLength = new Float(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ClipSize")) {
               this.ClipSize = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReloadTime")) {
               this.reloadTime = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AimingTime")) {
               this.aimingTime = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AimingTimeModifier")) {
               this.aimingTimeModifier = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReloadTimeModifier")) {
               this.reloadTimeModifier = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("HitChanceModifier")) {
               this.hitChanceModifier = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WeightReduction")) {
               this.WeightReduction = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CanBeEquipped")) {
               this.CanBeEquipped = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("SubCategory")) {
               this.SubCategory = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("ActivatedItem")) {
               this.ActivatedItem = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ProtectFromRainWhenEquipped")) {
               this.ProtectFromRainWhenEquipped = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("LightStrength")) {
               this.LightStrength = new Float(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("TorchCone")) {
               this.TorchCone = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("LightDistance")) {
               this.LightDistance = Integer.parseInt(var4.trim());
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
               this.Trap = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Wet")) {
               this.isWet = var4.equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("WetCooldown")) {
               this.wetCooldown = Float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ItemWhenDry")) {
               this.itemWhenDry = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("FishingLure")) {
               this.FishingLure = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CanBeWrite")) {
               this.canBeWrite = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("PageToWrite")) {
               this.PageToWrite = Integer.parseInt(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("Spice")) {
               this.Spice = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("RemoveNegativeEffectOnCooked")) {
               this.RemoveNegativeEffectOnCooked = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("ClipSizeModifier")) {
               this.clipSizeModifier = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("RecoilDelayModifier")) {
               this.recoilDelayModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxRangeModifier")) {
               this.maxRangeModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("MinRangeModifier")) {
               this.minRangeRangedModifier = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("DamageModifier")) {
               this.damageModifier = Float.parseFloat(var4);
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
               this.treeDamage = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("CustomEatSound")) {
               this.customEatSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("FillFromDispenserSound")) {
               this.fillFromDispenserSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("FillFromTapSound")) {
               this.fillFromTapSound = StringUtils.discardNullOrWhitespace(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("AlcoholPower")) {
               this.alcoholPower = Float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("BandagePower")) {
               this.bandagePower = Float.parseFloat(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("ReduceInfectionPower")) {
               this.ReduceInfectionPower = Float.parseFloat(var4.trim());
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
               this.triggerExplosionTimer = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("sensorRange")) {
               this.sensorRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("remoteRange")) {
               this.remoteRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("CountDownSound")) {
               this.countDownSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("explosionSound")) {
               this.explosionSound = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("PlacedSprite")) {
               this.PlacedSprite = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("explosionTimer")) {
               this.explosionTimer = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("explosionRange")) {
               this.explosionRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("explosionPower")) {
               this.explosionPower = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("fireRange")) {
               this.fireRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("firePower")) {
               this.firePower = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("canBePlaced")) {
               this.canBePlaced = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("CanBeReused")) {
               this.canBeReused = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("canBeRemote")) {
               this.canBeRemote = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("remoteController")) {
               this.remoteController = var4.trim().equalsIgnoreCase("true");
            } else if (var3.trim().equalsIgnoreCase("smokeRange")) {
               this.smokeRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("noiseRange")) {
               this.noiseRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("noiseDuration")) {
               this.noiseDuration = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("extraDamage")) {
               this.extraDamage = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("TwoWay")) {
               this.twoWay = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("TransmitRange")) {
               this.transmitRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MicRange")) {
               this.micRange = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("BaseVolumeRange")) {
               this.baseVolumeRange = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("IsPortable")) {
               this.isPortable = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("IsTelevision")) {
               this.isTelevision = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("MinChannel")) {
               this.minChannel = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("MaxChannel")) {
               this.maxChannel = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("UsesBattery")) {
               this.usesBattery = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("IsHighTier")) {
               this.isHighTier = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WorldObjectSprite")) {
               this.worldObjectSprite = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("fluReduction")) {
               this.fluReduction = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ReduceFoodSickness")) {
               this.ReduceFoodSickness = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("painReduction")) {
               this.painReduction = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorRed")) {
               this.colorRed = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorGreen")) {
               this.colorGreen = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ColorBlue")) {
               this.colorBlue = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("calories")) {
               this.calories = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("carbohydrates")) {
               this.carbohydrates = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("lipids")) {
               this.lipids = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("proteins")) {
               this.proteins = Float.parseFloat(var4);
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
               this.vehicleType = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("ChanceToFall")) {
               this.chanceToFall = Integer.parseInt(var4);
            } else if (var3.trim().equalsIgnoreCase("conditionLowerOffroad")) {
               this.conditionLowerOffroad = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("ConditionLowerStandard")) {
               this.conditionLowerNormal = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("wheelFriction")) {
               this.wheelFriction = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("suspensionDamping")) {
               this.suspensionDamping = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("suspensionCompression")) {
               this.suspensionCompression = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("engineLoudness")) {
               this.engineLoudness = Float.parseFloat(var4);
            } else if (var3.trim().equalsIgnoreCase("attachmentType")) {
               this.attachmentType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("makeUpType")) {
               this.makeUpType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("consolidateOption")) {
               this.consolidateOption = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("fabricType")) {
               this.fabricType = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("TeachedRecipes")) {
               this.teachedRecipes = new ArrayList<>();
               String[] var26 = var4.split(";");

               for (int var41 = 0; var41 < var26.length; var41++) {
                  String var49 = var26[var41].trim();
                  this.teachedRecipes.add(var49);
                  if (Translator.debug) {
                     Translator.getRecipeName(var49);
                  }
               }
            } else if (var3.trim().equalsIgnoreCase("MountOn")) {
               this.mountOn = new ArrayList<>();
               String[] var27 = var4.split(";");

               for (int var42 = 0; var42 < var27.length; var42++) {
                  this.mountOn.add(var27[var42].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("PartType")) {
               this.partType = var4;
            } else if (var3.trim().equalsIgnoreCase("ClothingItem")) {
               this.ClothingItem = var4;
            } else if (var3.trim().equalsIgnoreCase("EvolvedRecipe")) {
               String[] var28 = var4.split(";");

               for (int var43 = 0; var43 < var28.length; var43++) {
                  String var50 = var28[var43];
                  Object var53 = null;
                  int var55 = 0;
                  boolean var56 = false;
                  if (!var50.contains(":")) {
                     var53 = var50;
                  } else {
                     var53 = var50.split(":")[0];
                     String var57 = var50.split(":")[1];
                     if (!var57.contains("|")) {
                        var55 = Integer.parseInt(var50.split(":")[1]);
                     } else {
                        String[] var59 = var57.split("\\|");

                        for (int var13 = 0; var13 < var59.length; var13++) {
                           if ("Cooked".equals(var59[var13])) {
                              var56 = true;
                           }
                        }

                        var55 = Integer.parseInt(var59[0]);
                     }
                  }

                  ItemRecipe var58 = new ItemRecipe(this.name, this.module.getName(), var55);
                  EvolvedRecipe var60 = null;

                  for (EvolvedRecipe var14 : ((ScriptModule)ScriptManager.instance.ModuleMap.get("Base")).EvolvedRecipeMap) {
                     if (var14.name.equals(var53)) {
                        var60 = var14;
                        break;
                     }
                  }

                  var58.cooked = var56;
                  if (var60 == null) {
                     var60 = new EvolvedRecipe((String)var53);
                     ((ScriptModule)ScriptManager.instance.ModuleMap.get("Base")).EvolvedRecipeMap.add(var60);
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
               this.IconsForTexture = new ArrayList<>();
               String[] var29 = var4.split(";");

               for (int var44 = 0; var44 < var29.length; var44++) {
                  this.IconsForTexture.add(var29[var44].trim());
               }
            } else if (var3.trim().equalsIgnoreCase("BloodLocation")) {
               this.bloodClothingType = new ArrayList<>();
               String[] var30 = var4.split(";");

               for (int var45 = 0; var45 < var30.length; var45++) {
                  this.bloodClothingType.add(BloodClothingType.fromString(var30[var45].trim()));
               }
            } else if (var3.trim().equalsIgnoreCase("MediaCategory")) {
               this.recordedMediaCat = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("AcceptMediaType")) {
               this.acceptMediaType = Byte.parseByte(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("NoTransmit")) {
               this.noTransmit = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("WorldRender")) {
               this.worldRender = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("CantEat")) {
               this.CantEat = Boolean.parseBoolean(var4.trim());
            } else if (var3.trim().equalsIgnoreCase("OBSOLETE")) {
               this.OBSOLETE = var4.trim().toLowerCase().equals("true");
            } else if (var3.trim().equalsIgnoreCase("OnCreate")) {
               this.LuaCreate = var4.trim();
            } else if (var3.trim().equalsIgnoreCase("SoundParameter")) {
               String[] var31 = var4.split("\\s+");
               if (this.soundParameterMap == null) {
                  this.soundParameterMap = new HashMap<>();
               }

               this.soundParameterMap.put(var31[0].trim(), var31[1].trim());
            } else {
               DebugLog.log("adding unknown item param \"" + var3.trim() + "\" = \"" + var4.trim() + "\"");
               if (this.DefaultModData == null) {
                  this.DefaultModData = LuaManager.platform.newTable();
               }

               try {
                  Double var32 = Double.parseDouble(var4.trim());
                  this.DefaultModData.rawset(var3.trim(), var32);
               } catch (Exception var15) {
                  this.DefaultModData.rawset(var3.trim(), var4);
               }
            }
         } catch (Exception var16) {
            throw new InvalidParameterException("Error: " + var1.trim() + " is not a valid parameter in item: " + this.name);
         }
      }
   }

   public int getLevelSkillTrained() {
      return this.LvlSkillTrained;
   }

   public int getNumLevelsTrained() {
      return this.NumLevelsTrained;
   }

   public int getMaxLevelTrained() {
      return this.LvlSkillTrained == -1 ? -1 : this.LvlSkillTrained + this.NumLevelsTrained;
   }

   public List<String> getTeachedRecipes() {
      return this.teachedRecipes;
   }

   public float getTemperature() {
      return this.Temperature;
   }

   public void setTemperature(float var1) {
      this.Temperature = var1;
   }

   public boolean isConditionAffectsCapacity() {
      return this.ConditionAffectsCapacity;
   }

   public int getChanceToFall() {
      return this.chanceToFall;
   }

   public float getInsulation() {
      return this.insulation;
   }

   public void setInsulation(float var1) {
      this.insulation = var1;
   }

   public float getWindresist() {
      return this.windresist;
   }

   public void setWindresist(float var1) {
      this.windresist = var1;
   }

   public float getWaterresist() {
      return this.waterresist;
   }

   public void setWaterresist(float var1) {
      this.waterresist = var1;
   }

   public boolean getObsolete() {
      return this.OBSOLETE;
   }

   public String getAcceptItemFunction() {
      return this.AcceptItemFunction;
   }

   public ArrayList<BloodClothingType> getBloodClothingType() {
      return this.bloodClothingType;
   }

   public String toString() {
      return this.getClass().getSimpleName()
         + "{Module: "
         + (this.module != null ? this.module.name : "null")
         + ", Name:"
         + this.name
         + ", Type:"
         + this.type
         + "}";
   }

   public String getReplaceWhenUnequip() {
      return this.replaceWhenUnequip;
   }

   public void resolveItemTypes() {
      this.AmmoType = ScriptManager.instance.resolveItemType(this.module, this.AmmoType);
      this.magazineType = ScriptManager.instance.resolveItemType(this.module, this.magazineType);
      if (this.RequireInHandOrInventory != null) {
         for (int var1 = 0; var1 < this.RequireInHandOrInventory.size(); var1++) {
            String var2 = this.RequireInHandOrInventory.get(var1);
            var2 = ScriptManager.instance.resolveItemType(this.module, var2);
            this.RequireInHandOrInventory.set(var1, var2);
         }
      }

      if (this.ReplaceTypesMap != null) {
         for (String var6 : this.ReplaceTypesMap.keySet()) {
            String var3 = this.ReplaceTypesMap.get(var6);
            this.ReplaceTypesMap.replace(var6, ScriptManager.instance.resolveItemType(this.module, var3));
         }
      }
   }

   public void resolveModelScripts() {
      this.staticModel = ScriptManager.instance.resolveModelScript(this.module, this.staticModel);
      this.worldStaticModel = ScriptManager.instance.resolveModelScript(this.module, this.worldStaticModel);
   }

   public short getRegistry_id() {
      return this.registry_id;
   }

   public void setRegistry_id(short var1) {
      if (this.registry_id != -1) {
         WorldDictionary.DebugPrintItem(var1);
         throw new RuntimeException(
            "Cannot override existing registry id ("
               + this.registry_id
               + ") to new id ("
               + var1
               + "), item: "
               + (this.getFullName() != null ? this.getFullName() : "unknown")
         );
      } else {
         this.registry_id = var1;
      }
   }

   public String getModID() {
      return this.modID;
   }

   public boolean getExistsAsVanilla() {
      return this.existsAsVanilla;
   }

   public String getFileAbsPath() {
      return this.fileAbsPath;
   }

   public void setModID(String var1) {
      if (GameClient.bClient) {
         if (this.modID == null) {
            this.modID = var1;
         } else if (!var1.equals(this.modID) && Core.bDebug) {
            WorldDictionary.DebugPrintItem(this);
            throw new RuntimeException("Cannot override modID. ModID=" + (var1 != null ? var1 : "null"));
         }
      }
   }

   public String getRecordedMediaCat() {
      return this.recordedMediaCat;
   }

   public Boolean isWorldRender() {
      return this.worldRender;
   }

   public Boolean isCantEat() {
      return this.CantEat;
   }

   public String getLuaCreate() {
      return this.LuaCreate;
   }

   public void setLuaCreate(String var1) {
      this.LuaCreate = var1;
   }

   public String getSoundParameter(String var1) {
      return this.soundParameterMap == null ? null : this.soundParameterMap.get(var1);
   }
}
