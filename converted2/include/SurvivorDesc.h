#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SurvivorDesc.java
namespace zombie {
namespace characters {
#include "THashMap.h"
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
#include <unordered_map>
#include <algorithm>
#include "GameWindow.h"
#include "Rand.h"
#include "IsoMovingObject.h"
#include "IsoWorld.h"
// Referenced classes of package zombie.characters:
//            SurvivorGroup, IsoZombie, IsoSurvivor, IsoPlayer, 
//            IsoGameCharacter
class SurvivorDesc {
public:
{
    public static int getIDCount()
    {
        return IDCount;
    }
    public static void setIDCount(int aIDCount)
    {
        IDCount = aIDCount;
    }
    public SurvivorDesc()
    {
        Profession = "";
        ChildrenList = new Stack();
        forename = "None";
        ID = 0;
        Instance = nullptr;
        ParentList = new Stack();
        SiblingList = new Stack();
        surname = "None";
        InventoryScript = nullptr;
        legs = "Base_Legs";
        torso = "Base_Torso";
        head = "Base_Head1";
        top = "Shirt";
        bottoms = "Trousers";
        shoes = "Shoes1";
        shoespal = nullptr;
        bottomspal = "Trousers_Grey";
        toppal = "Shirt_Blue";
        skinpal = "Skin_01";
        MetCount = new THashMap();
        bravery = 1.0F;
        loner = 0.0F;
        aggressiveness = 1.0F;
        compassion = 1.0F;
        temper = 0.0F;
        friendliness = 0.0F;
        favourindoors = 0.0F;
        loyalty = 0.0F;
        Group = new SurvivorGroup(this);
        ID = IDCount++;
        IsoWorld.instance.SurvivorDescriptors.put(Integer.valueOf(ID), this);
        doStats();
    }
    public SurvivorDesc(bool bNew)
    {
        Profession = "";
        ChildrenList = new Stack();
        forename = "None";
        ID = 0;
        Instance = nullptr;
        ParentList = new Stack();
        SiblingList = new Stack();
        surname = "None";
        InventoryScript = nullptr;
        legs = "Base_Legs";
        torso = "Base_Torso";
        head = "Base_Head1";
        top = "Shirt";
        bottoms = "Trousers";
        shoes = "Shoes1";
        shoespal = nullptr;
        bottomspal = "Trousers_Grey";
        toppal = "Shirt_Blue";
        skinpal = "Skin_01";
        MetCount = new THashMap();
        bravery = 1.0F;
        loner = 0.0F;
        aggressiveness = 1.0F;
        compassion = 1.0F;
        temper = 0.0F;
        friendliness = 0.0F;
        favourindoors = 0.0F;
        loyalty = 0.0F;
        Group = new SurvivorGroup(this);
        ID = IDCount++;
        doStats();
    }
    public void meet(SurvivorDesc desc)
    {
        if(MetCount.containsKey(Integer.valueOf(desc.ID)))
            MetCount.put(Integer.valueOf(desc.ID), Integer.valueOf(((Integer)MetCount.get(Integer.valueOf(desc.ID))).intValue() + 1));
        else
            MetCount.put(Integer.valueOf(desc.ID), Integer.valueOf(1));
        if(desc.MetCount.containsKey(Integer.valueOf(ID)))
            desc.MetCount.put(Integer.valueOf(ID), Integer.valueOf(((Integer)desc.MetCount.get(Integer.valueOf(ID))).intValue() + 1));
        else
            desc.MetCount.put(Integer.valueOf(ID), Integer.valueOf(1));
    }
    public void load(DataInputStream input, IsoGameCharacter chr)
        throws IOException
    {
        ID = input.readInt();
        IsoWorld.instance.SurvivorDescriptors.put(Integer.valueOf(ID), this);
        forename = GameWindow.ReadString(input);
        surname = GameWindow.ReadString(input);
        legs = GameWindow.ReadString(input);
        torso = GameWindow.ReadString(input);
        head = GameWindow.ReadString(input);
        top = GameWindow.ReadString(input);
        bottoms = GameWindow.ReadString(input);
        shoes = GameWindow.ReadString(input);
        shoespal = GameWindow.ReadString(input);
        bottomspal = GameWindow.ReadString(input);
        toppal = GameWindow.ReadString(input);
        skinpal = GameWindow.ReadString(input);
        if(shoespal.length() == 0)
            shoespal = nullptr;
        doStats();
        if(IDCount < ID)
            IDCount = ID;
        Instance = chr;
    }
    public void load(ByteBuffer input, IsoGameCharacter chr)
        throws IOException
    {
        ID = input.getInt();
        IsoWorld.instance.SurvivorDescriptors.put(Integer.valueOf(ID), this);
        forename = GameWindow.ReadString(input);
        surname = GameWindow.ReadString(input);
        legs = GameWindow.ReadString(input);
        torso = GameWindow.ReadString(input);
        head = GameWindow.ReadString(input);
        top = GameWindow.ReadString(input);
        bottoms = GameWindow.ReadString(input);
        shoes = GameWindow.ReadString(input);
        shoespal = GameWindow.ReadString(input);
        bottomspal = GameWindow.ReadString(input);
        toppal = GameWindow.ReadString(input);
        skinpal = GameWindow.ReadString(input);
        if(shoespal.length() == 0)
            shoespal = nullptr;
        doStats();
        if(IDCount < ID)
            IDCount = ID;
        Instance = chr;
    }
    public void save(DataOutputStream output)
        throws IOException
    {
        output.writeInt(ID);
        GameWindow.WriteString(output, forename);
        GameWindow.WriteString(output, surname);
        GameWindow.WriteString(output, legs);
        GameWindow.WriteString(output, torso);
        GameWindow.WriteString(output, head);
        GameWindow.WriteString(output, top);
        GameWindow.WriteString(output, bottoms);
        GameWindow.WriteString(output, shoes);
        if(shoespal == nullptr)
            GameWindow.WriteString(output, "");
        else
            GameWindow.WriteString(output, shoespal);
        GameWindow.WriteString(output, bottomspal);
        GameWindow.WriteString(output, toppal);
        GameWindow.WriteString(output, skinpal);
    }
    public void save(ByteBuffer output)
        throws IOException
    {
        output.putInt(ID);
        GameWindow.WriteString(output, forename);
        GameWindow.WriteString(output, surname);
        GameWindow.WriteString(output, legs);
        GameWindow.WriteString(output, torso);
        GameWindow.WriteString(output, head);
        GameWindow.WriteString(output, top);
        GameWindow.WriteString(output, bottoms);
        GameWindow.WriteString(output, shoes);
        if(shoespal == nullptr)
            GameWindow.WriteString(output, "");
        else
            GameWindow.WriteString(output, shoespal);
        GameWindow.WriteString(output, bottomspal);
        GameWindow.WriteString(output, toppal);
        GameWindow.WriteString(output, skinpal);
    }
    public void AddToGroup(SurvivorGroup Group)
    {
        if(this.Group == Group)
        {
            return;
        } else
        {
            Group.AddMember(this);
            this.Group = Group;
            return;
        }
    }
    public bool InGroupWith(IsoMovingObject obj)
    {
        if(obj instanceof IsoZombie)
            return false;
        if((obj instanceof IsoSurvivor) || (obj instanceof IsoPlayer))
            return ((IsoGameCharacter)obj).descriptor.Group == Group && Group != nullptr;
        else
            return false;
    }
    private void doStats()
    {
        bravery = Rand.Next(0.1F, 10F);
        aggressiveness = bravery;
        aggressiveness += Rand.Next(-5F, 5F);
        if(aggressiveness > 10F)
            aggressiveness = 10F;
        if(aggressiveness < 0.1F)
            aggressiveness = 0.1F;
        compassion = Rand.Next(0.1F, 10F);
        loner = Rand.Next(0.0F, 10F);
        if(Rand.Next(3) == 0)
        {
            loner += 5F;
            if(loner > 10F)
                loner = 10F;
        }
        temper = Rand.Next(0.1F, 10F);
        if(Rand.Next(3) == 0)
        {
            temper += 5F;
            if(temper > 10F)
                temper = 10F;
        }
        friendliness = Rand.Next(0.1F, 10F);
        favourindoors = Rand.Next(0.1F, 10F);
        loyalty = Rand.Next(0.1F, 10F);
    }
    public bool Test(float val)
    {
        val *= 10F;
        return (float)Rand.Next(100) < val;
    }
    void AddToOthersGroup(SurvivorDesc descriptor)
    {
        if(descriptor.Group == Group && Group != nullptr)
        {
            return;
        } else
        {
            Group = descriptor.Group;
            Group.AddMember(this);
            return;
        }
    }
    public int getMetCount(SurvivorDesc descriptor)
    {
        if(MetCount.containsKey(Integer.valueOf(descriptor.ID)))
            return ((Integer)MetCount.get(Integer.valueOf(descriptor.ID))).intValue();
        else
            return 0;
    }
    bool IsLeader()
    {
        return Group != nullptr && Group.Leader == this;
    }
    public SurvivorGroup getGroup()
    {
        return Group;
    }
    public void setGroup(SurvivorGroup Group)
    {
        this.Group = Group;
    }
    public Stack getChildrenList()
    {
        return ChildrenList;
    }
    public void setChildrenList(Stack ChildrenList)
    {
        this.ChildrenList = ChildrenList;
    }
    public std::string getForename()
    {
        return forename;
    }
    public void setForename(std::string forename)
    {
        this.forename = forename;
    }
    public int getID()
    {
        return ID;
    }
    public void setID(int ID)
    {
        this.ID = ID;
    }
    public IsoGameCharacter getInstance()
    {
        return Instance;
    }
    public void setInstance(IsoGameCharacter Instance)
    {
        this.Instance = Instance;
    }
    public Stack getParentList()
    {
        return ParentList;
    }
    public void setParentList(Stack ParentList)
    {
        this.ParentList = ParentList;
    }
    public Stack getSiblingList()
    {
        return SiblingList;
    }
    public void setSiblingList(Stack SiblingList)
    {
        this.SiblingList = SiblingList;
    }
    public std::string getSurname()
    {
        return surname;
    }
    public void setSurname(std::string surname)
    {
        this.surname = surname;
    }
    public std::string getInventoryScript()
    {
        return InventoryScript;
    }
    public void setInventoryScript(std::string InventoryScript)
    {
        this.InventoryScript = InventoryScript;
    }
    public std::string getLegs()
    {
        return legs;
    }
    public void setLegs(std::string legs)
    {
        this.legs = legs;
    }
    public std::string getTorso()
    {
        return torso;
    }
    public void setTorso(std::string torso)
    {
        this.torso = torso;
    }
    public std::string getHead()
    {
        return head;
    }
    public void setHead(std::string head)
    {
        this.head = head;
    }
    public std::string getTop()
    {
        return top;
    }
    public void setTop(std::string top)
    {
        this.top = top;
    }
    public std::string getBottoms()
    {
        return bottoms;
    }
    public void setBottoms(std::string bottoms)
    {
        this.bottoms = bottoms;
    }
    public std::string getShoes()
    {
        return shoes;
    }
    public void setShoes(std::string shoes)
    {
        this.shoes = shoes;
    }
    public std::string getShoespal()
    {
        return shoespal;
    }
    public void setShoespal(std::string shoespal)
    {
        this.shoespal = shoespal;
    }
    public std::string getBottomspal()
    {
        return bottomspal;
    }
    public void setBottomspal(std::string bottomspal)
    {
        this.bottomspal = bottomspal;
    }
    public std::string getToppal()
    {
        return toppal;
    }
    public void setToppal(std::string toppal)
    {
        this.toppal = toppal;
    }
    public std::string getSkinpal()
    {
        return skinpal;
    }
    public void setSkinpal(std::string skinpal)
    {
        this.skinpal = skinpal;
    }
    public THashMap getMetCount()
    {
        return MetCount;
    }
    public void setMetCount(THashMap MetCount)
    {
        this.MetCount = MetCount;
    }
    public float getBravery()
    {
        return bravery;
    }
    public void setBravery(float bravery)
    {
        this.bravery = bravery;
    }
    public float getLoner()
    {
        return loner;
    }
    public void setLoner(float loner)
    {
        this.loner = loner;
    }
    public float getAggressiveness()
    {
        return aggressiveness;
    }
    public void setAggressiveness(float aggressiveness)
    {
        this.aggressiveness = aggressiveness;
    }
    public float getCompassion()
    {
        return compassion;
    }
    public void setCompassion(float compassion)
    {
        this.compassion = compassion;
    }
    public float getTemper()
    {
        return temper;
    }
    public void setTemper(float temper)
    {
        this.temper = temper;
    }
    public float getFriendliness()
    {
        return friendliness;
    }
    public void setFriendliness(float friendliness)
    {
        this.friendliness = friendliness;
    }
    public float getFavourindoors()
    {
        return favourindoors;
    }
    public void setFavourindoors(float favourindoors)
    {
        this.favourindoors = favourindoors;
    }
    public float getLoyalty()
    {
        return loyalty;
    }
    public void setLoyalty(float loyalty)
    {
        this.loyalty = loyalty;
    }
    public std::string getProfession()
    {
        return Profession;
    }
    public void setProfession(std::string Profession)
    {
        this.Profession = Profession;
    }
    protected static int IDCount = 0;
    public std::string Profession;
    protected SurvivorGroup Group;
    protected Stack ChildrenList;
    protected std::string forename;
    protected int ID;
    protected IsoGameCharacter Instance;
    protected Stack ParentList;
    protected Stack SiblingList;
    protected std::string surname;
    protected std::string InventoryScript;
    protected std::string legs;
    protected std::string torso;
    protected std::string head;
    protected std::string top;
    protected std::string bottoms;
    protected std::string shoes;
    protected std::string shoespal;
    protected std::string bottomspal;
    protected std::string toppal;
    protected std::string skinpal;
    protected THashMap MetCount;
    protected float bravery;
    protected float loner;
    protected float aggressiveness;
    protected float compassion;
    protected float temper;
    protected float friendliness;
    protected float favourindoors;
    protected float loyalty;
}
} // namespace
