#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   InventoryItem.java
namespace zombie {
namespace inventory {
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include <algorithm>
#include "KahluaTable.h"
#include "KahluaTableIterator.h"
#include "GameWindow.h"
#include "LuaManager.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "IsoSurvivor.h"
#include "SurvivorDesc.h"
#include "NulledArrayList.h"
#include "Texture.h"
#include "Clothing.h"
#include "DrainableComboItem.h"
#include "Food.h"
#include "HandWeapon.h"
#include "Literature.h"
#include "IsoDirections.h"
#include "IsoObject.h"
#include "ScriptManager.h"
#include "Item.h"
#include "ObjectTooltip.h"
#include "TutorialManager.h"
#include "UIManager.h"
// Referenced classes of package zombie.inventory:
//            ItemType, ItemContainer
class InventoryItem {
public:
{
		 protected IsoGameCharacter previousOwner = nullptr;
/*   52 */   protected Item ScriptItem = null;
/*   53 */   protected ItemType cat = ItemType.None;
/*   54 */   protected std::string consumeMenu = "Eat";
/*      */   protected ItemContainer container;
/*   56 */   protected int containerX = 0;
/*   57 */   protected int containerY = 0;
/*   58 */   protected bool DisappearOnUse = true;
/*      */   protected std::string name;
/*   60 */   protected std::string replaceOnUse = null;
/*   61 */   protected int ConditionMax = 100;
/*   62 */   protected ItemContainer rightClickContainer = null;
/*   63 */   protected std::string swingAnim = "Rifle";
/*      */   protected Texture texture;
/*      */   protected Texture texturerotten;
/*      */   protected Texture textureCooked;
/*      */   protected Texture textureBurnt;
/*      */   protected std::string type;
/*   69 */   protected int uses = 1;
/*   70 */   protected float Age = 0.0F;
/*   71 */   protected bool IsCookable = false;
/*   72 */   protected float CookingTime = 0.0F;
/*   73 */   protected float MinutesToCook = 60.0F;
/*   74 */   protected float MinutesToBurn = 120.0F;
/*   75 */   public bool Cooked = false;
/*   76 */   protected bool Burnt = false;
/*   77 */   protected int OffAge = 1000000000;
/*   78 */   protected int OffAgeMax = 1000000000;
/*   79 */   protected float Weight = 1.0F;
/*   80 */   protected float ActualWeight = 1.0F;
/*      */   protected std::string WorldTexture;
/*      */   protected std::string Description;
/*   83 */   protected int Condition = 100;
/*   84 */   protected std::string OffString = "Rotten";
/*   85 */   protected std::string CookedString = "Cooked";
/*   86 */   protected std::string UnCookedString = "Uncooked";
/*   87 */   protected std::string BurntString = "Burnt";
/*   88 */   protected std::string module = "Base";
/*   89 */   protected bool AlwaysWelcomeGift = false;
/*   90 */   protected bool CanBandage = false;
/*   91 */   protected float boredomChange = 0.0F;
/*   92 */   protected float unhappyChange = 0.0F;
/*   93 */   protected float stressChange = 0.0F;
/*   94 */   protected NulledArrayList<IsoObject> Taken = new NulledArrayList();
/*   95 */   protected IsoDirections placeDir = IsoDirections.Max;
/*   96 */   protected IsoDirections newPlaceDir = IsoDirections.Max;
/*   97 */   private KahluaTable table = null;
/*   98 */   public std::string ReplaceOnUseOn = null;
/*   99 */   public bool IsWaterSource = false;
/*  100 */   public bool CanStoreWater = false;
/*  101 */   public bool CanStack = true;
    public KahluaTable getModData()
    {
        if(table == nullptr)
            table = LuaManager.platform.newTable();
        return table;
    }
    public InventoryItem(std::string module, std::string name, std::string type, std::string tex)
    {
    	this.texture = Texture.getSharedTexture("media/inventory/" + tex + ".png");
    	/*  114 */     Texture.WarnFailFindTexture = false;
    	/*  115 */     this.texturerotten = Texture.trygetTexture("media/inventory/" + tex + "Rotten.png");
    	/*  116 */     this.textureCooked = Texture.trygetTexture("media/inventory/" + tex + "Cooked.png");
    	/*  117 */     this.textureBurnt = Texture.trygetTexture("media/inventory/" + tex + "Overdone.png");
    	/*  118 */     Texture.WarnFailFindTexture = true;
    	/*      */ 
    	/*  120 */     if (this.texture == null)
    	/*  121 */       this.texture = Texture.getSharedTexture("media/inventory/Question_On.png");
    	/*  122 */     if (this.texturerotten == null)
    	/*  123 */       this.texturerotten = this.texture;
    	/*  124 */     if (this.textureCooked == null)
    	/*  125 */       this.textureCooked = this.texture;
    	/*  126 */     if (this.textureBurnt == null) {
    	/*  127 */       this.textureBurnt = this.texture;
    	/*      */     }
    	/*  129 */     this.module = module;
    	/*  130 */     this.name = name;
    	/*  131 */     this.type = type;
    	/*  132 */     this.WorldTexture = tex.replace("Item_", "media/inventory/world/WItem_");
    	/*  133 */     this.WorldTexture += ".png";
    }
    public std::string getType()
    {
        return type;
    }
    public Texture getTex()
    {
        if(Burnt)
            return textureBurnt;
        if(Age > (float)OffAge)
            return texturerotten;
        if(isCooked())
            return textureCooked;
        else
            return texture;
    }
    public bool IsRotten()
    {
        return Age > (float)OffAge;
    }
    public float HowRotten()
    {
        if(OffAgeMax - OffAge == 0)
        {
            return Age <= (float)OffAge ? 0.0F : 1.0F;
        } else
        {
            float del = (Age - (float)OffAge) / (float)(OffAgeMax - OffAge);
            return del;
        }
    }
    public bool CanStack(InventoryItem item)
    {
        return this.Taken.isEmpty() && item.Taken.isEmpty() && name == item.name) && CanStack;
    }
    public void DoTooltip(ObjectTooltip tooltipUI)
    {
        tooltipUI.render();
        int mid = 60;
        int y = 5;
        if(Burnt)
            tooltipUI.DrawText((new StringBuilder()).append(BurntString).append(" ").append(name).toString(), 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        else
        if(Age > (float)OffAge)
            tooltipUI.DrawText((new StringBuilder()).append(OffString).append(" ").append(name).toString(), 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        else
        if(isCooked())
            tooltipUI.DrawText((new StringBuilder()).append(CookedString).append(" ").append(name).toString(), 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        else
        if(IsCookable)
            tooltipUI.DrawText((new StringBuilder()).append(UnCookedString).append(" ").append(name).toString(), 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        else
            tooltipUI.DrawText(name, 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        y += 20;
        mid = 100;
        if(type == "Tissue"))
        {
            tooltipUI.DrawText("Equip to mute sneezes and coughs", 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
            y += 20;
            tooltipUI.setWidth(200);
        }
        tooltipUI.DrawText("Weight:", 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
        Float weight = Float.valueOf(ActualWeight * (float)uses);
        tooltipUI.DrawValueRightNoPlus(weight.floatValue(), mid, y);
        y += 14;
        y += 19;
        tooltipUI.setHeight(y);
    }
    public void SetContainerPosition(int x, int y)
    {
        containerX = x;
        containerY = y;
    }
    public void Use()
    {
        Use(false);
    }
    public void Use(bool bCrafting)
    {
        Use(bCrafting, false);
    }
    public void Use(bool bCrafting, bool bInContainer)
    {
        if(!DisappearOnUse && !bCrafting)
            return;
        uses--;
        if(replaceOnUse != nullptr && !bInContainer && !bCrafting)
        {
            std::string s = replaceOnUse;
            if(!replaceOnUse.contains("."))
                s = (new StringBuilder()).append(module).append(".").append(s).toString();
            container.AddItem(s);
            container.dirty = true;
        }
        if(uses <= 0 && container != nullptr)
        {
            container.Items.remove(this);
            container.dirty = true;
            if(this == UIManager.getDragInventory())
                UIManager.setDragInventory(nullptr);
        }
    }
    public void Use(IsoGameCharacter useOn)
    {
        bool bNeeded = false;
        bool bUse = false;
        if(AlwaysWelcomeGift)
            bNeeded = true;
        if("Pills" == type))
            bUse = true;
        if("Pillow" == type))
        {
            bUse = false;
            if(useOn != TutorialManager.instance.wife);
        }
        if(CanBandage)
        {
            Iterator i$ = useOn.getWounds().iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                zombie.characters.IsoGameCharacter.Wound wound = (zombie.characters.IsoGameCharacter.Wound)i$.next();
                if(!wound.bandaged)
                {
                    wound.bandaged = true;
                    bUse = true;
                }
            } while(true);
            bUse = useOn.getBodyDamage().UseBandageOnMostNeededPart();
            if(bUse)
            {
                if(useOn instanceof IsoSurvivor)
                    ((IsoSurvivor)useOn).PatchedUpBy(IsoPlayer.getInstance());
                bNeeded = true;
            }
        }
        if(this instanceof Food)
            bNeeded = true;
        if(this instanceof HandWeapon)
            bNeeded = true;
        if("Belt" == type))
        {
            Iterator i$ = useOn.getWounds().iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                zombie.characters.IsoGameCharacter.Wound wound = (zombie.characters.IsoGameCharacter.Wound)i$.next();
                if(!wound.tourniquet)
                {
                    wound.tourniquet = true;
                    bUse = true;
                    wound.bleeding -= 0.5F;
                }
            } while(true);
        }
        if(bUse)
        {
            Use();
            useOn.getUsedItemsOn().add(type);
        } else
        if((useOn instanceof IsoSurvivor) && useOn != TutorialManager.instance.wife)
        {
            useOn.getInventory().AddItem(this, 1);
            Use(true, true);
        }
        if(!useOn.getScriptName() == "none"))
            ScriptManager.instance.Trigger("OnUseItemOnCharacter", useOn.getScriptName(), type);
        else
        if(useOn instanceof IsoSurvivor)
        {
            if(uses == 1)
            {
                IsoPlayer.instance.getInventory().Remove(this);
                ((IsoSurvivor)useOn).getInventory().AddItem(this);
            } else
            {
                Use(true);
                ((IsoSurvivor)useOn).getInventory().AddItem(getFullType());
            }
            ((IsoSurvivor)useOn).GivenItemBy(IsoPlayer.getInstance(), type, bNeeded);
        }
    }
    public void update()
    {
    }
    public bool finishupdate()
    {
        return true;
    }
    public std::string getFullType()
    {
        return (new StringBuilder()).append(module).append(".").append(type).toString();
    }
    public void save(DataOutputStream output)
        throws IOException
    {
        GameWindow.WriteString(output, getFullType());
        output.writeInt(uses);
    }
    public void load(DataInputStream input)
        throws IOException
    {
        uses = input.readInt();
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        GameWindow.WriteString(output, getFullType());
        output.putInt(uses);
        if(table != nullptr)
        {
            output.put((byte)1);
            table.save(output);
        } else
        {
            output.put((byte)0);
        }
    }
    public void load(ByteBuffer input)
        throws IOException
    {
        uses = input.getInt();
        if(input.get() == 1)
        {
            if(table == nullptr)
                table = LuaManager.platform.newTable();
            table.load(input);
        }
    }
    public bool IsFood()
    {
        return this instanceof Food;
    }
    public bool IsWeapon()
    {
        return this instanceof HandWeapon;
    }
    public bool IsDrainable()
    {
        return this instanceof DrainableComboItem;
    }
    public bool IsLiterature()
    {
        return this instanceof Literature;
    }
    public bool IsClothing()
    {
        return this instanceof Clothing;
    }
    static InventoryItem LoadFromFile(DataInputStream input)
        throws IOException
    {
        std::string type = GameWindow.ReadString(input);
        return nullptr;
    }
    public float getScore(SurvivorDesc desc)
    {
        return 0.0F;
    }
    public IsoGameCharacter getPreviousOwner()
    {
        return previousOwner;
    }
    public void setPreviousOwner(IsoGameCharacter previousOwner)
    {
        this.previousOwner = previousOwner;
    }
    public Item getScriptItem()
    {
        return ScriptItem;
    }
    public void setScriptItem(Item ScriptItem)
    {
        this.ScriptItem = ScriptItem;
    }
    public ItemType getCat()
    {
        return cat;
    }
    public void setCat(ItemType cat)
    {
        this.cat = cat;
    }
    public std::string getConsumeMenu()
    {
        return consumeMenu;
    }
    public void setConsumeMenu(std::string consumeMenu)
    {
        this.consumeMenu = consumeMenu;
    }
    public ItemContainer getContainer()
    {
        return container;
    }
    public void setContainer(ItemContainer container)
    {
        this.container = container;
    }
    public int getContainerX()
    {
        return containerX;
    }
    public void setContainerX(int containerX)
    {
        this.containerX = containerX;
    }
    public int getContainerY()
    {
        return containerY;
    }
    public void setContainerY(int containerY)
    {
        this.containerY = containerY;
    }
    public bool isDisappearOnUse()
    {
        return DisappearOnUse;
    }
    public void setDisappearOnUse(bool DisappearOnUse)
    {
        this.DisappearOnUse = DisappearOnUse;
    }
    public std::string getName()
    {
        return name;
    }
    public void setName(std::string name)
    {
        this.name = name;
    }
    public std::string getReplaceOnUse()
    {
        return replaceOnUse;
    }
    public void setReplaceOnUse(std::string replaceOnUse)
    {
        this.replaceOnUse = replaceOnUse;
    }
    public int getConditionMax()
    {
        return ConditionMax;
    }
    public void setConditionMax(int ConditionMax)
    {
        this.ConditionMax = ConditionMax;
    }
    public ItemContainer getRightClickContainer()
    {
        return rightClickContainer;
    }
    public void setRightClickContainer(ItemContainer rightClickContainer)
    {
        this.rightClickContainer = rightClickContainer;
    }
    public std::string getSwingAnim()
    {
        return swingAnim;
    }
    public void setSwingAnim(std::string swingAnim)
    {
        this.swingAnim = swingAnim;
    }
    public Texture getTexture()
    {
        return texture;
    }
    public void setTexture(Texture texture)
    {
        this.texture = texture;
    }
    public Texture getTexturerotten()
    {
        return texturerotten;
    }
    public void setTexturerotten(Texture texturerotten)
    {
        this.texturerotten = texturerotten;
    }
    public Texture getTextureCooked()
    {
        return textureCooked;
    }
    public void setTextureCooked(Texture textureCooked)
    {
        this.textureCooked = textureCooked;
    }
    public Texture getTextureBurnt()
    {
        return textureBurnt;
    }
    public void setTextureBurnt(Texture textureBurnt)
    {
        this.textureBurnt = textureBurnt;
    }
    public void setType(std::string type)
    {
        this.type = type;
    }
    public int getUses()
    {
        return uses;
    }
    public void setUses(int uses)
    {
        this.uses = uses;
    }
    public float getAge()
    {
        return Age;
    }
    public void setAge(float Age)
    {
        this.Age = Age;
    }
    public bool isIsCookable()
    {
        return IsCookable;
    }
    public void setIsCookable(bool IsCookable)
    {
        this.IsCookable = IsCookable;
    }
    public float getCookingTime()
    {
        return CookingTime;
    }
    public void setCookingTime(float CookingTime)
    {
        this.CookingTime = CookingTime;
    }
    public float getMinutesToCook()
    {
        return MinutesToCook;
    }
    public void setMinutesToCook(float MinutesToCook)
    {
        this.MinutesToCook = MinutesToCook;
    }
    public float getMinutesToBurn()
    {
        return MinutesToBurn;
    }
    public void setMinutesToBurn(float MinutesToBurn)
    {
        this.MinutesToBurn = MinutesToBurn;
    }
    public bool isCooked()
    {
        return Cooked;
    }
    public void setCooked(bool Cooked)
    {
        this.Cooked = Cooked;
    }
    public bool isBurnt()
    {
        return Burnt;
    }
    public void setBurnt(bool Burnt)
    {
        this.Burnt = Burnt;
    }
    public int getOffAge()
    {
        return OffAge;
    }
    public void setOffAge(int OffAge)
    {
        this.OffAge = OffAge;
    }
    public int getOffAgeMax()
    {
        return OffAgeMax;
    }
    public void setOffAgeMax(int OffAgeMax)
    {
        this.OffAgeMax = OffAgeMax;
    }
    public float getWeight()
    {
        return Weight;
    }
    public void setWeight(float Weight)
    {
        this.Weight = Weight;
    }
    public float getActualWeight()
    {
        return ActualWeight;
    }
    public void setActualWeight(float ActualWeight)
    {
        this.ActualWeight = ActualWeight;
    }
    public std::string getWorldTexture()
    {
        return WorldTexture;
    }
    public void setWorldTexture(std::string WorldTexture)
    {
        this.WorldTexture = WorldTexture;
    }
    public std::string getDescription()
    {
        return Description;
    }
    public void setDescription(std::string Description)
    {
        this.Description = Description;
    }
    public int getCondition()
    {
        return Condition;
    }
    public void setCondition(int Condition)
    {
        this.Condition = Condition;
    }
    public std::string getOffString()
    {
        return OffString;
    }
    public void setOffString(std::string OffString)
    {
        this.OffString = OffString;
    }
    public std::string getCookedString()
    {
        return CookedString;
    }
    public void setCookedString(std::string CookedString)
    {
        this.CookedString = CookedString;
    }
    public std::string getUnCookedString()
    {
        return UnCookedString;
    }
    public void setUnCookedString(std::string UnCookedString)
    {
        this.UnCookedString = UnCookedString;
    }
    public std::string getBurntString()
    {
        return BurntString;
    }
    public void setBurntString(std::string BurntString)
    {
        this.BurntString = BurntString;
    }
    public std::string getModule()
    {
        return module;
    }
    public void setModule(std::string module)
    {
        this.module = module;
    }
    public bool isAlwaysWelcomeGift()
    {
        return AlwaysWelcomeGift;
    }
    public void setAlwaysWelcomeGift(bool AlwaysWelcomeGift)
    {
        this.AlwaysWelcomeGift = AlwaysWelcomeGift;
    }
    public bool isCanBandage()
    {
        return CanBandage;
    }
    public void setCanBandage(bool CanBandage)
    {
        this.CanBandage = CanBandage;
    }
    public float getBoredomChange()
    {
        return boredomChange;
    }
    public void setBoredomChange(float boredomChange)
    {
        this.boredomChange = boredomChange;
    }
    public float getUnhappyChange()
    {
        return unhappyChange;
    }
    public void setUnhappyChange(float unhappyChange)
    {
        this.unhappyChange = unhappyChange;
    }
    public float getStressChange()
    {
        return stressChange;
    }
    public void setStressChange(float stressChange)
    {
        this.stressChange = stressChange;
    }
    public NulledArrayList getTaken()
    {
        return Taken;
    }
    public void setTaken(NulledArrayList Taken)
    {
        this.Taken = Taken;
    }
    public IsoDirections getPlaceDir()
    {
        return placeDir;
    }
    public void setPlaceDir(IsoDirections placeDir)
    {
        this.placeDir = placeDir;
    }
    public IsoDirections getNewPlaceDir()
    {
        return newPlaceDir;
    }
    public void setNewPlaceDir(IsoDirections newPlaceDir)
    {
        this.newPlaceDir = newPlaceDir;
    }
    public void setReplaceOnUseOn(std::string ReplaceOnUseOn)
    {
        this.ReplaceOnUseOn = ReplaceOnUseOn;
    }
    public std::string getReplaceOnUseOn()
    {
        return ReplaceOnUseOn;
    }
    public void setIsWaterSource(bool IsWaterSource)
    {
        this.IsWaterSource = IsWaterSource;
    }
    public bool isWaterSource()
    {
        return IsWaterSource;
    }
    bool CanStackNoTemp(InventoryItem item)
    {
        return CanStack(item);
    }
    public void CopyModData(KahluaTable DefaultModData)
    {
        if(DefaultModData == nullptr)
            return;
        KahluaTableIterator it = DefaultModData.iterator();
        KahluaTable n = getModData();
        for(; it.advance(); n.rawset(it.getKey(), it.getValue()));
    }
}
} // namespace
