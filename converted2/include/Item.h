#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Item.java
namespace zombie {
namespace scripting {
namespace objects {
#include "InvalidParameterException.h"
#include <vector>
#include <algorithm>
#include "J2SEPlatform.h"
#include "KahluaTable.h"
#include "LuaManager.h"
#include "Rand.h"
#include "InventoryItem.h"
#include "types.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject, ScriptModule
class Item : public BaseScriptObject {
public:
{
	/*      */   public static enum ClothingBodyLocation
	/*      */   {
	/* 1136 */     None, 
	/* 1137 */     Head, 
	/* 1138 */     Top, 
	/* 1139 */     Bottoms, 
	/* 1140 */     Shoes;
	/*      */   }
	/*      */   public static enum Type
	/*      */   {
	/* 1148 */     Normal, 
	/* 1149 */     Weapon, 
	/* 1150 */     Food, 
	/* 1151 */     Literature, 
	/* 1152 */     Drainable, 
	/* 1153 */     Clothing;
	/*      */   }
    public Item()
    {
        DisplayName = "Blooo";
        Icon = "None";
        ActualWeight = 1.0F;
        HungerChange = 0.0F;
        Count = 1;
        DaysFresh = 0x3b9aca00;
        DaysTotallyRotten = 0x3b9aca00;
        MinutesToCook = 60;
        MinutesToBurn = 120;
        IsCookable = false;
        StressChange = 0.0F;
        BoredomChange = 0.0F;
        UnhappyChange = 0.0F;
        AlwaysWelcomeGift = false;
        ReplaceOnDeplete = nullptr;
        Ranged = false;
        CanStoreWater = false;
        MaxRange = 1.0F;
        MinRange = 0.0F;
        ThistChange = 0.0F;
        MinAngle = 1.0F;
        MaxDamage = 1.5F;
        MinDamage = 0.0F;
        MinimumSwingTime = 0.0F;
        SwingSound = "batSwing";
        AngleFalloff = false;
        SoundVolume = 0;
        ToHitModifier = 1.0F;
        SoundRadius = 0;
        Categories = new ArrayList();
        ImpactSound = "zombieImpact";
        SwingTime = 1.0F;
        KnockBackOnNoDeath = true;
        SplatBloodOnNoDeath = false;
        SwingAmountBeforeImpact = 0.0F;
        AmmoType = nullptr;
        DoorDamage = 1;
        ConditionLowerChance = 0xf4240;
        ConditionMax = 100;
        CanBandage = false;
        MaxHitCount = 1000;
        UseSelf = false;
        OtherHandUse = false;
        SwingAnim = "Rifle";
        WeaponWeight = 1.0F;
        EnduranceChange = 0.0F;
        IdleAnim = "Idle";
        RunAnim = "Run";
        RequireInHandOrInventory = nullptr;
        DoorHitSound = "chopdoor";
        ReplaceOnUse = nullptr;
        DangerousUncooked = false;
        Alcoholic = false;
        PushBackMod = 1.0F;
        SplatNumber = 2;
        NPCSoundBoost = 1.0F;
        RangeFalloff = false;
        UseEndurance = true;
        MultipleHitConditionAffected = true;
        ShareDamage = true;
        ShareEndurance = false;
        CanBarricade = false;
        UseWhileEquipped = true;
        DisappearOnUse = true;
        UseDelta = 0.03125F;
        AlwaysKnockdown = false;
        EnduranceMod = 1.0F;
        KnockdownMod = 1.0F;
        CantAttackWithLowestEndurance = false;
        ReplaceOnUseOn = nullptr;
        IsWaterSource = false;
        DefaultModData = nullptr;
        IsAimedFirearm = false;
        IsAimedHandWeapon = false;
        CanStack = true;
        AimingMod = 1.0F;
        ProjectileCount = 1;
        HitAngleMod = 0.0F;
        SplatSize = 1.0F;
        bodyLocation = ClothingBodyLocation.None;
        PaletteChoices = new Stack();
        SpriteName = nullptr;
        PalettesStart = "";
        type = Type.Normal;
    }
    public std::string getDisplayName()
    {
        return DisplayName;
    }
    public void setDisplayName(std::string DisplayName)
    {
        this.DisplayName = DisplayName;
    }
    public std::string getIcon()
    {
        return Icon;
    }
    public void setIcon(std::string Icon)
    {
        this.Icon = Icon;
    }
    public float getActualWeight()
    {
        return ActualWeight;
    }
    public void setActualWeight(float ActualWeight)
    {
        this.ActualWeight = ActualWeight;
    }
    public float getHungerChange()
    {
        return HungerChange;
    }
    public void setHungerChange(float HungerChange)
    {
        this.HungerChange = HungerChange;
    }
    public int getCount()
    {
        return Count;
    }
    public void setCount(int Count)
    {
        this.Count = Count;
    }
    public int getDaysFresh()
    {
        return DaysFresh;
    }
    public void setDaysFresh(int DaysFresh)
    {
        this.DaysFresh = DaysFresh;
    }
    public int getDaysTotallyRotten()
    {
        return DaysTotallyRotten;
    }
    public void setDaysTotallyRotten(int DaysTotallyRotten)
    {
        this.DaysTotallyRotten = DaysTotallyRotten;
    }
    public int getMinutesToCook()
    {
        return MinutesToCook;
    }
    public void setMinutesToCook(int MinutesToCook)
    {
        this.MinutesToCook = MinutesToCook;
    }
    public int getMinutesToBurn()
    {
        return MinutesToBurn;
    }
    public void setMinutesToBurn(int MinutesToBurn)
    {
        this.MinutesToBurn = MinutesToBurn;
    }
    public bool isIsCookable()
    {
        return IsCookable;
    }
    public void setIsCookable(bool IsCookable)
    {
        this.IsCookable = IsCookable;
    }
    public float getStressChange()
    {
        return StressChange;
    }
    public void setStressChange(float StressChange)
    {
        this.StressChange = StressChange;
    }
    public float getBoredomChange()
    {
        return BoredomChange;
    }
    public void setBoredomChange(float BoredomChange)
    {
        this.BoredomChange = BoredomChange;
    }
    public float getUnhappyChange()
    {
        return UnhappyChange;
    }
    public void setUnhappyChange(float UnhappyChange)
    {
        this.UnhappyChange = UnhappyChange;
    }
    public bool isAlwaysWelcomeGift()
    {
        return AlwaysWelcomeGift;
    }
    public void setAlwaysWelcomeGift(bool AlwaysWelcomeGift)
    {
        this.AlwaysWelcomeGift = AlwaysWelcomeGift;
    }
    public bool isRanged()
    {
        return Ranged;
    }
    public void setRanged(bool Ranged)
    {
        this.Ranged = Ranged;
    }
    public float getMaxRange()
    {
        return MaxRange;
    }
    public void setMaxRange(float MaxRange)
    {
        this.MaxRange = MaxRange;
    }
    public float getMinAngle()
    {
        return MinAngle;
    }
    public void setMinAngle(float MinAngle)
    {
        this.MinAngle = MinAngle;
    }
    public float getMaxDamage()
    {
        return MaxDamage;
    }
    public void setMaxDamage(float MaxDamage)
    {
        this.MaxDamage = MaxDamage;
    }
    public float getMinDamage()
    {
        return MinDamage;
    }
    public void setMinDamage(float MinDamage)
    {
        this.MinDamage = MinDamage;
    }
    public float getMinimumSwingTime()
    {
        return MinimumSwingTime;
    }
    public void setMinimumSwingTime(float MinimumSwingTime)
    {
        this.MinimumSwingTime = MinimumSwingTime;
    }
    public std::string getSwingSound()
    {
        return SwingSound;
    }
    public void setSwingSound(std::string SwingSound)
    {
        this.SwingSound = SwingSound;
    }
    public std::string getWeaponSprite()
    {
        return WeaponSprite;
    }
    public void setWeaponSprite(std::string WeaponSprite)
    {
        this.WeaponSprite = WeaponSprite;
    }
    public bool isAngleFalloff()
    {
        return AngleFalloff;
    }
    public void setAngleFalloff(bool AngleFalloff)
    {
        this.AngleFalloff = AngleFalloff;
    }
    public int getSoundVolume()
    {
        return SoundVolume;
    }
    public void setSoundVolume(int SoundVolume)
    {
        this.SoundVolume = SoundVolume;
    }
    public float getToHitModifier()
    {
        return ToHitModifier;
    }
    public void setToHitModifier(float ToHitModifier)
    {
        this.ToHitModifier = ToHitModifier;
    }
    public int getSoundRadius()
    {
        return SoundRadius;
    }
    public void setSoundRadius(int SoundRadius)
    {
        this.SoundRadius = SoundRadius;
    }
    public float getOtherCharacterVolumeBoost()
    {
        return OtherCharacterVolumeBoost;
    }
    public void setOtherCharacterVolumeBoost(float OtherCharacterVolumeBoost)
    {
        this.OtherCharacterVolumeBoost = OtherCharacterVolumeBoost;
    }
    public ArrayList getCategories()
    {
        return Categories;
    }
    public void setCategories(ArrayList Categories)
    {
        this.Categories = Categories;
    }
    public std::string getImpactSound()
    {
        return ImpactSound;
    }
    public void setImpactSound(std::string ImpactSound)
    {
        this.ImpactSound = ImpactSound;
    }
    public float getSwingTime()
    {
        return SwingTime;
    }
    public void setSwingTime(float SwingTime)
    {
        this.SwingTime = SwingTime;
    }
    public bool isKnockBackOnNoDeath()
    {
        return KnockBackOnNoDeath;
    }
    public void setKnockBackOnNoDeath(bool KnockBackOnNoDeath)
    {
        this.KnockBackOnNoDeath = KnockBackOnNoDeath;
    }
    public bool isSplatBloodOnNoDeath()
    {
        return SplatBloodOnNoDeath;
    }
    public void setSplatBloodOnNoDeath(bool SplatBloodOnNoDeath)
    {
        this.SplatBloodOnNoDeath = SplatBloodOnNoDeath;
    }
    public float getSwingAmountBeforeImpact()
    {
        return SwingAmountBeforeImpact;
    }
    public void setSwingAmountBeforeImpact(float SwingAmountBeforeImpact)
    {
        this.SwingAmountBeforeImpact = SwingAmountBeforeImpact;
    }
    public std::string getAmmoType()
    {
        return AmmoType;
    }
    public void setAmmoType(std::string AmmoType)
    {
        this.AmmoType = AmmoType;
    }
    public int getDoorDamage()
    {
        return DoorDamage;
    }
    public void setDoorDamage(int DoorDamage)
    {
        this.DoorDamage = DoorDamage;
    }
    public int getConditionLowerChance()
    {
        return ConditionLowerChance;
    }
    public void setConditionLowerChance(int ConditionLowerChance)
    {
        this.ConditionLowerChance = ConditionLowerChance;
    }
    public int getConditionMax()
    {
        return ConditionMax;
    }
    public void setConditionMax(int ConditionMax)
    {
        this.ConditionMax = ConditionMax;
    }
    public bool isCanBandage()
    {
        return CanBandage;
    }
    public void setCanBandage(bool CanBandage)
    {
        this.CanBandage = CanBandage;
    }
    public std::string getName()
    {
        return name;
    }
    public void setName(std::string name)
    {
        this.name = name;
    }
    public int getMaxHitCount()
    {
        return MaxHitCount;
    }
    public void setMaxHitCount(int MaxHitCount)
    {
        this.MaxHitCount = MaxHitCount;
    }
    public bool isUseSelf()
    {
        return UseSelf;
    }
    public void setUseSelf(bool UseSelf)
    {
        this.UseSelf = UseSelf;
    }
    public bool isOtherHandUse()
    {
        return OtherHandUse;
    }
    public void setOtherHandUse(bool OtherHandUse)
    {
        this.OtherHandUse = OtherHandUse;
    }
    public std::string getOtherHandRequire()
    {
        return OtherHandRequire;
    }
    public void setOtherHandRequire(std::string OtherHandRequire)
    {
        this.OtherHandRequire = OtherHandRequire;
    }
    public std::string getPhysicsObject()
    {
        return PhysicsObject;
    }
    public void setPhysicsObject(std::string PhysicsObject)
    {
        this.PhysicsObject = PhysicsObject;
    }
    public std::string getSwingAnim()
    {
        return SwingAnim;
    }
    public void setSwingAnim(std::string SwingAnim)
    {
        this.SwingAnim = SwingAnim;
    }
    public float getWeaponWeight()
    {
        return WeaponWeight;
    }
    public void setWeaponWeight(float WeaponWeight)
    {
        this.WeaponWeight = WeaponWeight;
    }
    public float getEnduranceChange()
    {
        return EnduranceChange;
    }
    public void setEnduranceChange(float EnduranceChange)
    {
        this.EnduranceChange = EnduranceChange;
    }
    public std::string getRequireInHandOrInventory()
    {
        return RequireInHandOrInventory;
    }
    public void setRequireInHandOrInventory(std::string RequireInHandOrInventory)
    {
        this.RequireInHandOrInventory = RequireInHandOrInventory;
    }
    public std::string getDoorHitSound()
    {
        return DoorHitSound;
    }
    public void setDoorHitSound(std::string DoorHitSound)
    {
        this.DoorHitSound = DoorHitSound;
    }
    public std::string getReplaceOnUse()
    {
        return ReplaceOnUse;
    }
    public void setReplaceOnUse(std::string ReplaceOnUse)
    {
        this.ReplaceOnUse = ReplaceOnUse;
    }
    public bool isDangerousUncooked()
    {
        return DangerousUncooked;
    }
    public void setDangerousUncooked(bool DangerousUncooked)
    {
        this.DangerousUncooked = DangerousUncooked;
    }
    public bool isAlcoholic()
    {
        return Alcoholic;
    }
    public void setAlcoholic(bool Alcoholic)
    {
        this.Alcoholic = Alcoholic;
    }
    public float getPushBackMod()
    {
        return PushBackMod;
    }
    public void setPushBackMod(float PushBackMod)
    {
        this.PushBackMod = PushBackMod;
    }
    public int getSplatNumber()
    {
        return SplatNumber;
    }
    public void setSplatNumber(int SplatNumber)
    {
        this.SplatNumber = SplatNumber;
    }
    public float getNPCSoundBoost()
    {
        return NPCSoundBoost;
    }
    public void setNPCSoundBoost(float NPCSoundBoost)
    {
        this.NPCSoundBoost = NPCSoundBoost;
    }
    public bool isRangeFalloff()
    {
        return RangeFalloff;
    }
    public void setRangeFalloff(bool RangeFalloff)
    {
        this.RangeFalloff = RangeFalloff;
    }
    public bool isUseEndurance()
    {
        return UseEndurance;
    }
    public void setUseEndurance(bool UseEndurance)
    {
        this.UseEndurance = UseEndurance;
    }
    public bool isMultipleHitConditionAffected()
    {
        return MultipleHitConditionAffected;
    }
    public void setMultipleHitConditionAffected(bool MultipleHitConditionAffected)
    {
        this.MultipleHitConditionAffected = MultipleHitConditionAffected;
    }
    public bool isShareDamage()
    {
        return ShareDamage;
    }
    public void setShareDamage(bool ShareDamage)
    {
        this.ShareDamage = ShareDamage;
    }
    public bool isShareEndurance()
    {
        return ShareEndurance;
    }
    public void setShareEndurance(bool ShareEndurance)
    {
        this.ShareEndurance = ShareEndurance;
    }
    public bool isCanBarricade()
    {
        return CanBarricade;
    }
    public void setCanBarricade(bool CanBarricade)
    {
        this.CanBarricade = CanBarricade;
    }
    public bool isUseWhileEquipped()
    {
        return UseWhileEquipped;
    }
    public void setUseWhileEquipped(bool UseWhileEquipped)
    {
        this.UseWhileEquipped = UseWhileEquipped;
    }
    public bool isDisappearOnUse()
    {
        return DisappearOnUse;
    }
    public void setDisappearOnUse(bool DisappearOnUse)
    {
        this.DisappearOnUse = DisappearOnUse;
    }
    public float getUseDelta()
    {
        return UseDelta;
    }
    public void setUseDelta(float UseDelta)
    {
        this.UseDelta = UseDelta;
    }
    public bool isAlwaysKnockdown()
    {
        return AlwaysKnockdown;
    }
    public void setAlwaysKnockdown(bool AlwaysKnockdown)
    {
        this.AlwaysKnockdown = AlwaysKnockdown;
    }
    public float getEnduranceMod()
    {
        return EnduranceMod;
    }
    public void setEnduranceMod(float EnduranceMod)
    {
        this.EnduranceMod = EnduranceMod;
    }
    public float getKnockdownMod()
    {
        return KnockdownMod;
    }
    public void setKnockdownMod(float KnockdownMod)
    {
        this.KnockdownMod = KnockdownMod;
    }
    public bool isCantAttackWithLowestEndurance()
    {
        return CantAttackWithLowestEndurance;
    }
    public void setCantAttackWithLowestEndurance(bool CantAttackWithLowestEndurance)
    {
        this.CantAttackWithLowestEndurance = CantAttackWithLowestEndurance;
    }
    public ClothingBodyLocation getBodyLocation()
    {
        return bodyLocation;
    }
    public void setBodyLocation(ClothingBodyLocation bodyLocation)
    {
        this.bodyLocation = bodyLocation;
    }
    public Stack getPaletteChoices()
    {
        return PaletteChoices;
    }
    public void setPaletteChoices(Stack PaletteChoices)
    {
        this.PaletteChoices = PaletteChoices;
    }
    public std::string getSpriteName()
    {
        return SpriteName;
    }
    public void setSpriteName(std::string SpriteName)
    {
        this.SpriteName = SpriteName;
    }
    public std::string getPalettesStart()
    {
        return PalettesStart;
    }
    public void setPalettesStart(std::string PalettesStart)
    {
        this.PalettesStart = PalettesStart;
    }
    public Type getType()
    {
        return type;
    }
    public void setType(Type type)
    {
        this.type = type;
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        std::string arr$[] = strArray;
        int len$ = arr$.length;
        for(int i$ = 0; i$ < len$; i$++)
        {
            std::string str = arr$[i$];
            DoParam(str);
        }
        if(type == Type.Clothing)
        {
            for(int n = 0; n < PaletteChoices.size(); n++)
                InstanceItem((std::string)PaletteChoices.get(n));
            if(PaletteChoices.isEmpty())
                InstanceItem(nullptr);
        }
    }
    public InventoryItem InstanceItem(std::string param)
    {
        InventoryItem item = nullptr;
        if(type == Type.Food)
        {
            item = new Food(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).toString());
            Food food = (Food)item;
            food.setThirstChange(ThistChange / 100F);
            food.setHungChange(HungerChange / 100F);
            food.setEndChange(EnduranceChange / 100F);
            food.setReplaceOnUse(ReplaceOnUse);
            food.setOffAge(DaysFresh);
            food.setOffAgeMax(DaysTotallyRotten);
            food.setIsCookable(IsCookable);
            food.setMinutesToCook(MinutesToCook);
            food.setMinutesToBurn(MinutesToBurn);
            food.setbDangerousUncooked(DangerousUncooked);
            food.setRequireInHandOrInventory(RequireInHandOrInventory);
            food.setReplaceOnUse(ReplaceOnUse);
            food.setAlcoholic(Alcoholic);
        }
        if(type == Type.Literature)
        {
            item = new Literature(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).toString());
            Literature literature = (Literature)item;
            literature.setReplaceOnUse(ReplaceOnUse);
            literature.requireInHandOrInventory = RequireInHandOrInventory;
        } else
        if(type == Type.Weapon)
        {
            item = new HandWeapon(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).toString());
            HandWeapon weapon = (HandWeapon)item;
            weapon.setMultipleHitConditionAffected(MultipleHitConditionAffected);
            weapon.setConditionLowerChance(ConditionLowerChance);
            weapon.SplatSize = SplatSize;
            weapon.aimingMod = AimingMod;
            weapon.ProjectileCount = ProjectileCount;
            weapon.setMinDamage(MinDamage);
            weapon.setMaxDamage(MaxDamage);
            weapon.setPhysicsObject(PhysicsObject);
            weapon.setOtherHandRequire(OtherHandRequire);
            weapon.setOtherHandUse(OtherHandUse);
            weapon.setMaxRange(MaxRange);
            weapon.setMinRange(MinRange);
            weapon.setShareEndurance(ShareEndurance);
            weapon.setKnockdownMod(KnockdownMod);
            weapon.bIsAimedFirearm = IsAimedFirearm;
            weapon.RunAnim = RunAnim;
            weapon.IdleAnim = IdleAnim;
            weapon.HitAngleMod = (float)Math.toRadians(HitAngleMod);
            weapon.bIsAimedHandWeapon = IsAimedHandWeapon;
            weapon.setCantAttackWithLowestEndurance(CantAttackWithLowestEndurance);
            weapon.setAlwaysKnockdown(AlwaysKnockdown);
            weapon.setEnduranceMod(EnduranceMod);
            weapon.setUseSelf(UseSelf);
            weapon.setSwingAnim(SwingAnim);
            weapon.setMaxHitCount(MaxHitCount);
            weapon.setMinimumSwingTime(MinimumSwingTime);
            weapon.setSwingTime(SwingTime);
            weapon.setSwingAnim(SwingAnim);
            weapon.setDoSwingBeforeImpact(SwingAmountBeforeImpact);
            weapon.setMinAngle(MinAngle);
            weapon.setWeaponSprite(WeaponSprite);
            weapon.setDoorDamage(DoorDamage);
            weapon.setDoorHitSound(DoorHitSound);
            weapon.setPushBackMod(PushBackMod);
            weapon.setWeight(WeaponWeight);
            weapon.setImpactSound(ImpactSound);
            weapon.setSplatNumber(SplatNumber);
            weapon.setKnockBackOnNoDeath(KnockBackOnNoDeath);
            weapon.setSplatBloodOnNoDeath(SplatBloodOnNoDeath);
            weapon.setSwingSound(SwingSound);
            weapon.setAngleFalloff(AngleFalloff);
            weapon.setSoundVolume(SoundVolume);
            weapon.setSoundRadius(SoundRadius);
            weapon.setToHitModifier(ToHitModifier);
            weapon.setOtherBoost(NPCSoundBoost);
            weapon.setRanged(Ranged);
            weapon.setRangeFalloff(RangeFalloff);
            weapon.setUseEndurance(UseEndurance);
            weapon.setShareDamage(ShareDamage);
            weapon.setAmmoType(AmmoType);
            weapon.setCanBarracade(CanBarricade);
            weapon.setWeaponSprite(WeaponSprite);
        } else
        if(type == Type.Normal)
            item = new ComboItem(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).toString());
        else
        if(type == Type.Clothing)
        {
            std::string col = "";
            std::string pal = nullptr;
            if(!PaletteChoices.isEmpty() || param != nullptr)
            {
                int ran = Rand.Next(PaletteChoices.size());
                pal = (std::string)PaletteChoices.get(ran);
                if(param != nullptr)
                    pal = param;
                col = (new StringBuilder()).append("_").append(pal.replace(PalettesStart, "")).toString();
            }
            item = new Clothing(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).append(col).toString(), pal, SpriteName);
            ((Clothing)item).setBodyLocation(bodyLocation);
        } else
        if(type == Type.Drainable)
        {
            item = new DrainableComboItem(module.name, DisplayName, name, (new StringBuilder()).append("Item_").append(Icon).toString());
            DrainableComboItem drain = (DrainableComboItem)item;
            drain.setUseWhileEquiped(UseWhileEquipped);
            drain.setDisappearOnUse(DisappearOnUse);
            drain.setUseDelta(UseDelta);
            drain.setReplaceOnDeplete(ReplaceOnDeplete);
        }
        item.setCondition(ConditionMax);
        item.setConditionMax(ConditionMax);
        item.setActualWeight(ActualWeight);
        item.setUses(Count);
        item.setAlwaysWelcomeGift(AlwaysWelcomeGift);
        item.setCanBandage(CanBandage);
        item.setScriptItem(this);
        item.setBoredomChange(BoredomChange);
        item.setStressChange(StressChange);
        item.setUnhappyChange(UnhappyChange);
        item.setReplaceOnUseOn(ReplaceOnUseOn);
        item.setIsWaterSource(IsWaterSource);
        item.CanStoreWater = CanStoreWater;
        item.CanStack = CanStack;
        item.CopyModData(DefaultModData);
        return item;
    }
    public void DoParam(std::string str)
    {
        if(str.trim().length() == 0)
            return;
        try
        {
            std::string p[] = str.split("=");
            std::string param = p[0];
            std::string val = p[1];
            val = val.trim();
            val = new std::string(val);
            param = new std::string(param.trim());
            if(param.trim().equalsIgnoreCase("BodyLocation"))
                bodyLocation = bodyLocation.valueOf(val.trim());
            else
            if(param.trim().equalsIgnoreCase("Palettes"))
            {
                std::string split[] = val.split("/");
                for(int n = 0; n < split.length; n++)
                    PaletteChoices.add(split[n].trim());
            } else
            if(param.trim().equalsIgnoreCase("PalettesStart"))
                PalettesStart = val.trim();
            else
            if(param.trim().equalsIgnoreCase("DisplayName"))
                DisplayName = val.trim();
            else
            if(param.trim().equalsIgnoreCase("SpriteName"))
                SpriteName = val.trim();
            else
            if(param.trim().equalsIgnoreCase("Type"))
            {
                type = Type.valueOf(val.trim());
                if(type == Type.Clothing)
                    type = type;
            } else
            if(param.trim().equalsIgnoreCase("SplatSize"))
                SplatSize = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("CanStoreWater"))
                CanStoreWater = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("IsWaterSource"))
                IsWaterSource = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("SwingAnim"))
                SwingAnim = val;
            else
            if(param.trim().equalsIgnoreCase("Icon"))
                Icon = val;
            else
            if(param.trim().equalsIgnoreCase("DoorHitSound"))
                DoorHitSound = val;
            else
            if(param.trim().equalsIgnoreCase("Weight"))
                ActualWeight = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("HungerChange"))
                HungerChange = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("ThirstChange"))
                ThistChange = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("EnduranceChange"))
                EnduranceChange = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("DaysFresh"))
                DaysFresh = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("DaysTotallyRotten"))
                DaysTotallyRotten = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("IsCookable"))
                IsCookable = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("MinutesToCook"))
                MinutesToCook = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("MinutesToBurn"))
                MinutesToBurn = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("BoredomChange"))
                BoredomChange = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("StressChange"))
                StressChange = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("UnhappyChange"))
                UnhappyChange = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("ReplaceOnDeplete"))
                ReplaceOnDeplete = val;
            else
            if(param.trim().equalsIgnoreCase("ReplaceOnUseOn"))
                ReplaceOnUseOn = val;
            else
            if(param.trim().equalsIgnoreCase("Ranged"))
                Ranged = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("UseSelf"))
                UseSelf = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("OtherHandUse"))
                OtherHandUse = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("DangerousUncooked"))
                DangerousUncooked = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("MaxRange"))
                MaxRange = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("MinRange"))
                MinRange = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("MinAngle"))
                MinAngle = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("MaxDamage"))
                MaxDamage = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("ConditionLowerChanceOneIn"))
                ConditionLowerChance = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("MultipleHitConditionAffected"))
                MultipleHitConditionAffected = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("CanBandage"))
                CanBandage = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("ConditionMax"))
                ConditionMax = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("MinDamage"))
                MinDamage = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("MinimumSwingTime"))
                MinimumSwingTime = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("SwingSound"))
                SwingSound = val;
            else
            if(param.trim().equalsIgnoreCase("ReplaceOnUse"))
                ReplaceOnUse = val;
            else
            if(param.trim().equalsIgnoreCase("WeaponSprite"))
                WeaponSprite = val;
            else
            if(param.trim().equalsIgnoreCase("AngleFalloff"))
                AngleFalloff = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("SoundVolume"))
                SoundVolume = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("ToHitModifier"))
                ToHitModifier = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("SoundRadius"))
                SoundRadius = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("Categories"))
            {
                std::string s[] = val.split(",");
                for(int n = 0; n < s.length; n++)
                    Categories.add(s[n].trim());
            } else
            if(param.trim().equalsIgnoreCase("OtherCharacterVolumeBoost"))
                OtherCharacterVolumeBoost = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("ImpactSound"))
            {
                ImpactSound = val;
                if(ImpactSound == "nullptr"))
                    ImpactSound = nullptr;
            } else
            if(param.trim().equalsIgnoreCase("SwingTime"))
                SwingTime = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("KnockBackOnNoDeath"))
                KnockBackOnNoDeath = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("Alcoholic"))
                Alcoholic = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("SplatBloodOnNoDeath"))
                SplatBloodOnNoDeath = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("SwingAmountBeforeImpact"))
                SwingAmountBeforeImpact = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("AmmoType"))
                AmmoType = val;
            else
            if(param.trim().equalsIgnoreCase("HitAngleMod"))
                HitAngleMod = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("OtherHandRequire"))
                OtherHandRequire = val;
            else
            if(param.trim().equalsIgnoreCase("AlwaysWelcomeGift"))
                AlwaysWelcomeGift = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("CantAttackWithLowestEndurance"))
                CantAttackWithLowestEndurance = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("EnduranceMod"))
                EnduranceMod = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("KnockdownMod"))
                KnockdownMod = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("DoorDamage"))
                DoorDamage = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("MaxHitCount"))
                MaxHitCount = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("PhysicsObject"))
                PhysicsObject = val;
            else
            if(param.trim().equalsIgnoreCase("Count"))
                Count = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("SwingAnim"))
                SwingAnim = val;
            else
            if(param.trim().equalsIgnoreCase("WeaponWeight"))
                WeaponWeight = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("IdleAnim"))
                IdleAnim = val;
            else
            if(param.trim().equalsIgnoreCase("RunAnim"))
                RunAnim = val;
            else
            if(param.trim().equalsIgnoreCase("RequireInHandOrInventory"))
                RequireInHandOrInventory = val;
            else
            if(param.trim().equalsIgnoreCase("PushBackMod"))
                PushBackMod = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("NPCSoundBoost"))
                NPCSoundBoost = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("SplatNumber"))
                SplatNumber = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("RangeFalloff"))
                RangeFalloff = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("UseEndurance"))
                UseEndurance = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("ShareDamage"))
                ShareDamage = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("ShareEndurance"))
                ShareEndurance = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("AlwaysKnockdown"))
                AlwaysKnockdown = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("IsAimedFirearm"))
                IsAimedFirearm = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("IsAimedHandWeapon"))
                IsAimedHandWeapon = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("AimingMod"))
                AimingMod = Float.parseFloat(val);
            else
            if(param.trim().equalsIgnoreCase("ProjectileCount"))
                ProjectileCount = Integer.parseInt(val);
            else
            if(param.trim().equalsIgnoreCase("CanStack"))
                IsAimedFirearm = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("CanBarricade"))
                CanBarricade = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("UseWhileEquipped"))
                UseWhileEquipped = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("DisappearOnUse"))
                DisappearOnUse = val.equalsIgnoreCase("true");
            else
            if(param.trim().equalsIgnoreCase("UseDelta"))
            {
                UseDelta = Float.parseFloat(val);
            } else
            {
                if(DefaultModData == nullptr)
                    DefaultModData = LuaManager.platform.newTable();
                try
                {
                    Double tryConv = Double.valueOf(Double.parseDouble(val.trim()));
                    DefaultModData.rawset(param.trim(), tryConv);
                }
                catch(Exception ex)
                {
                    DefaultModData.rawset(param.trim(), val);
                }
            }
        }
        catch(Exception ex)
        {
            throw new InvalidParameterException((new StringBuilder()).append("Error: ").append(str.trim()).append(" is not a valid parameter in item: ").append(name).toString());
        }
    }
    public std::string DisplayName;
    public std::string Icon;
    public float ActualWeight;
    public float HungerChange;
    public int Count;
    public int DaysFresh;
    public int DaysTotallyRotten;
    public int MinutesToCook;
    public int MinutesToBurn;
    public bool IsCookable;
    public float StressChange;
    public float BoredomChange;
    public float UnhappyChange;
    public bool AlwaysWelcomeGift;
    public std::string ReplaceOnDeplete;
    public bool Ranged;
    public bool CanStoreWater;
    public float MaxRange;
    public float MinRange;
    public float ThistChange;
    public float MinAngle;
    public float MaxDamage;
    public float MinDamage;
    public float MinimumSwingTime;
    public std::string SwingSound;
    public std::string WeaponSprite;
    public bool AngleFalloff;
    public int SoundVolume;
    public float ToHitModifier;
    public int SoundRadius;
    public float OtherCharacterVolumeBoost;
    public ArrayList Categories;
    public std::string ImpactSound;
    public float SwingTime;
    public bool KnockBackOnNoDeath;
    public bool SplatBloodOnNoDeath;
    public float SwingAmountBeforeImpact;
    public std::string AmmoType;
    public int DoorDamage;
    public int ConditionLowerChance;
    public int ConditionMax;
    public bool CanBandage;
    public std::string name;
    public int MaxHitCount;
    public bool UseSelf;
    public bool OtherHandUse;
    public std::string OtherHandRequire;
    public std::string PhysicsObject;
    public std::string SwingAnim;
    public float WeaponWeight;
    public float EnduranceChange;
    public std::string IdleAnim;
    public std::string RunAnim;
    public std::string RequireInHandOrInventory;
    public std::string DoorHitSound;
    public std::string ReplaceOnUse;
    public bool DangerousUncooked;
    public bool Alcoholic;
    public float PushBackMod;
    public int SplatNumber;
    public float NPCSoundBoost;
    public bool RangeFalloff;
    public bool UseEndurance;
    public bool MultipleHitConditionAffected;
    public bool ShareDamage;
    public bool ShareEndurance;
    public bool CanBarricade;
    public bool UseWhileEquipped;
    public bool DisappearOnUse;
    public float UseDelta;
    public bool AlwaysKnockdown;
    public float EnduranceMod;
    public float KnockdownMod;
    public bool CantAttackWithLowestEndurance;
    public std::string ReplaceOnUseOn;
    public bool IsWaterSource;
    public KahluaTable DefaultModData;
    public bool IsAimedFirearm;
    public bool IsAimedHandWeapon;
    public bool CanStack;
    public float AimingMod;
    public int ProjectileCount;
    public float HitAngleMod;
    public float SplatSize;
    public ClothingBodyLocation bodyLocation;
    public Stack PaletteChoices;
    public std::string SpriteName;
    public std::string PalettesStart;
    public Type type;
}
} // namespace
