#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ItemContainerFiller.java
namespace zombie {
namespace inventory {
#include <algorithm>
#include "NulledArrayList.h"
#include "Rand.h"
#include "PropertyContainer.h"
#include "iso.h"
#include "IsoFlagType.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
// Referenced classes of package zombie.inventory:
//            ItemContainer
class ItemContainerFiller {
public:
{
    public ItemContainerFiller()
    {
    }
    public static void DistributeGoodItems(IsoCell cell)
    {
        PlaceOnRandomFloor(cell, "foodItems", "TinnedSoup", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Crisps", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Crisps2", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Crisps3", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Pop", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Pop2", 8);
        PlaceOnRandomFloor(cell, "foodItems", "Pop3", 8);
        for(int n = 0; n < 6; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
            {
                container.AddItem("Shotgun");
                container.AddItem("ShotgunShells");
            }
        }
        for(int n = 0; n < 15; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
                container.AddItem("ShotgunShells");
        }
        for(int n = 0; n < 6; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
                container.AddItem("Shotgun");
        }
        for(int n = 0; n < 8; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
                container.AddItem("BaseballBat");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable");
            if(container != nullptr)
                container.AddItem("Battery");
        }
        for(int n = 0; n < 6; n++)
        {
            ItemContainer container = getRandomContainer("crate");
            if(container != nullptr)
                container.AddItem("PetrolCan");
        }
        for(int n = 0; n < 6; n++)
        {
            ItemContainer container = getRandomContainer("crate,counter");
            if(container != nullptr)
                container.AddItem("Hammer");
        }
        for(int n = 0; n < 1; n++)
        {
            ItemContainer container = getRandomContainer("crate,counter");
            if(container != nullptr)
                container.AddItem("Axe");
        }
        for(int n = 0; n < 4; n++)
        {
            ItemContainer container = getRandomContainer("crate,counter");
            if(container != nullptr)
                container.AddItem("Axe");
        }
        for(int n = 0; n < 60; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable");
            if(container != nullptr)
                container.AddItem("Nails");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("wardrobe");
            if(container != nullptr)
                container.AddItem("Sheet");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("wardrobe");
            if(container != nullptr)
                container.AddItem("Belt");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("wardrobe");
            if(container != nullptr)
                container.AddItem("Socks");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable");
            if(container != nullptr)
                container.AddItem("Lighter");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable,fridge");
            if(container != nullptr)
                container.AddItem("WhiskeyFull");
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("vendingsnacks");
            if(container != nullptr)
            {
                container.AddItem("Crisps");
                container.AddItem("Crisps2");
                container.AddItem("Crisps3");
            }
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("vendingpop");
            if(container != nullptr)
            {
                container.AddItem("Pop");
                container.AddItem("Pop2");
                container.AddItem("Pop3");
            }
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable,fridge");
            if(container != nullptr)
                container.AddItem("Chocolate");
        }
        for(int n = 0; n < 5; n++)
        {
            ItemContainer container = getRandomContainer("counter,crate,sidetable,fridge");
            if(container != nullptr)
                container.AddItem("Torch");
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("fridge");
            if(container != nullptr)
                container.AddItem("Bread");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter");
            if(container != nullptr)
                container.AddItem("DishCloth");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter,sidetable");
            if(container != nullptr)
                container.AddItem("Pen");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter,sidetable");
            if(container != nullptr)
                container.AddItem("Pencil");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("fridge");
            if(container != nullptr)
                container.AddItem("Carrots");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("fridge");
            if(container != nullptr)
                container.AddItem("Steak");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter");
            if(container != nullptr)
                container.AddItem("Carrots");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("counter");
            if(container != nullptr)
                container.AddItem("Steak");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("medicine");
            if(container != nullptr)
                container.AddItem("Pills");
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("medicine");
            if(container != nullptr)
                container.AddItem("PillsBeta");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("medicine");
            if(container != nullptr)
                container.AddItem("PillsSleepingTablets");
        }
        for(int n = 0; n < 10; n++)
        {
            ItemContainer container = getRandomContainer("medicine");
            if(container != nullptr)
                container.AddItem("PillsAntiDep");
        }
        for(int n = 0; n < 20; n++)
        {
            ItemContainer container = getRandomContainer("fridge");
            if(container != nullptr)
                container.AddItem("Apple");
        }
        for(int n = 0; n < 6; n++)
        {
            ItemContainer container = getRandomContainer("counter");
            if(container != nullptr)
                container.AddItem("TinOpener");
        }
        for(int n = 0; n < 30; n++)
        {
            ItemContainer container = getRandomContainer("crate");
            if(container != nullptr)
                container.AddItem("Plank");
        }
        for(int n = 0; n < 3; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
                container.AddItem("BaseballBat");
        }
        for(int n = 0; n < 12; n++)
        {
            ItemContainer container = getRandomContainer("counter,wardrobe,crate");
            if(container != nullptr)
                container.AddItem("ShotgunShells");
        }
    }
    public static void FillContainer(ItemContainer container, std::string roomDef)
    {
        std::string containerType = container.type;
        if(containerType == "counter"))
            DoCounter(container, roomDef);
        if(containerType == "wardrobe"))
            DoWardrobe(container, roomDef);
        if(containerType == "medicine"))
            DoMedicine(container, roomDef);
        if(roomDef == "rangerHut") && container.type == "counter"))
            container.AddItem("Axe");
        if(roomDef == "tutKitchen2") && container.type == "fridge"))
        {
            container.AddItem("Carrots");
            container.AddItem("Apple");
        }
    }
    public static void FillRoom(IsoRoom room)
    {
        if(room.RoomDef == "shopBig"))
            DoShopBig(room);
        if(room.RoomDef == "bar"))
            DoBar(room);
        ItemContainer container;
        for(Iterator i$ = room.Containers.iterator(); i$.hasNext(); FillContainer(container, room.RoomDef))
            container = (ItemContainer)i$.next();
    }
    public static void FillTable(IsoGridSquare sq, std::string roomDef)
    {
        bool doE = false;
        bool doS = false;
        if(sq.getProperties().Is(IsoFlagType.tableE))
            doE = true;
        if(sq.getProperties().Is(IsoFlagType.tableS))
            doS = true;
        if(doE)
        {
            for(int n = 0; n < 3; n++)
            {
                float height = 0.5F;
                float x = 0.45F + (float)Rand.Next(10) / 200F;
                float y = (float)n * 0.33F;
                if(Rand.Next(5) == 0 || roomDef == "shopGeneral") || roomDef == "tutKitchen1"))
                    AddShelfItem(roomDef, sq, x, y, height);
            }
        }
        if(doS)
        {
            for(int n = 0; n < 3; n++)
            {
                float height = 0.5F;
                float y = 0.45F + (float)Rand.Next(10) / 200F;
                float x = (float)n * 0.33F;
                if(Rand.Next(5) == 0 || roomDef == "shopGeneral") || roomDef == "tutKitchen1"))
                    AddShelfItem(roomDef, sq, x, y, height);
            }
        }
    }
    public static void FillTable(IsoGridSquare sq, std::string roomDef, std::string type, float height)
    {
        bool doE = false;
        bool doS = false;
        if(sq.getProperties().Is(IsoFlagType.tableE))
            doE = true;
        if(sq.getProperties().Is(IsoFlagType.tableS))
            doS = true;
        if(doE)
        {
            for(int n = 0; n < 5; n++)
            {
                float x = 0.8F;
                float y = (float)n * 0.2F;
                AddShelfItem(roomDef, sq, x, y, height, type);
            }
        }
        if(doS)
        {
            for(int n = 0; n < 5; n++)
            {
                float y = 0.8F;
                float x = (float)n * 0.2F;
                AddShelfItem(roomDef, sq, x, y, height, type);
            }
        }
    }
    public static void FillTable(int lootval, IsoGridSquare sq, std::string roomDef, std::string type, float height)
    {
        bool doE = false;
        bool doS = false;
        if(sq.getProperties().Is(IsoFlagType.tableE))
            doE = true;
        if(sq.getProperties().Is(IsoFlagType.tableS))
            doS = true;
        if(doE)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(lootval) == 0)
                {
                    float x = 0.8F;
                    float y = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
        if(doS)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(lootval) == 0)
                {
                    float y = 0.8F;
                    float x = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
    }
    public static void FillTable(int lootval, IsoGridSquare sq, std::string roomDef, std::string type, float height, float depth)
    {
        bool doE = false;
        bool doS = false;
        if(sq.getProperties().Is(IsoFlagType.tableE))
            doE = true;
        if(sq.getProperties().Is(IsoFlagType.tableS))
            doS = true;
        if(doE)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(lootval) == 0)
                {
                    float x = depth;
                    float y = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
        if(doS)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(lootval) == 0)
                {
                    float y = depth;
                    float x = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
    }
    public static void FillTable(IsoGridSquare sq, std::string roomDef, std::string type, float height, float depth)
    {
        bool doE = false;
        bool doS = false;
        if(sq.getProperties().Is(IsoFlagType.tableE))
            doE = true;
        if(sq.getProperties().Is(IsoFlagType.tableS))
            doS = true;
        if(doE)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(4) == 0)
                {
                    float x = depth;
                    float y = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
        if(doS)
        {
            for(int n = 0; n < 5; n++)
                if(Rand.Next(4) == 0)
                {
                    float y = depth;
                    float x = (float)n * 0.2F;
                    AddShelfItem(roomDef, sq, x, y, height, type);
                }
        }
    }
    static void AddShelfItem(std::string roomDef, IsoGridSquare sq, float x, float y, float height)
    {
        if(roomDef == "tutKitchen1") && sq.getX() == 40 && sq.getY() == 25 && x == 0.33F)
            sq.AddWorldInventoryItem("Pot", x, y, height);
        if(roomDef == "kitchen"))
            switch(Rand.Next(4))
            {
            case 0: // '\0'
                sq.AddWorldInventoryItem("WhiskeyHalf", x, y, height);
                break;
            case 1: // '\001'
                sq.AddWorldInventoryItem("WhiskeyFull", x, y, height);
                break;
            case 2: // '\002'
                sq.AddWorldInventoryItem("Bread", x, y, height);
                break;
            case 3: // '\003'
                sq.AddWorldInventoryItem("TinnedSoup", x, y, height);
                break;
            }
    }
    private static void AddShelfItem(std::string roomDef, IsoGridSquare sq, float x, float y, float height, std::string std::string)
    {
        sq.AddWorldInventoryItem(std::string, x, y, height);
    }
    private static void AddToRandomContainer(IsoRoom room, std::string item)
    {
        int n = Rand.Next(room.Containers.size());
        ((ItemContainer)room.Containers.get(n)).AddItem(item);
    }
    private static void AddToRandomContainer(IsoRoom room, std::string item, std::string containerType)
    {
        Stack containers = new Stack();
        Iterator i$ = room.Containers.iterator();
        do
        {
            if(!i$.hasNext())
                break;
            ItemContainer c = (ItemContainer)i$.next();
            if(c.type == containerType))
                containers.add(c);
        } while(true);
        int n = Rand.Next(containers.size());
        ((ItemContainer)containers.get(n)).AddItem(item);
    }
    private static void DoBar(IsoRoom room)
    {
        Iterator i$ = room.TileList.iterator();
        do
        {
            if(!i$.hasNext())
                break;
            IsoGridSquare sq = (IsoGridSquare)i$.next();
            if(sq.getProperties().Is(IsoFlagType.shelfS))
            {
                bool isCounter = false;
                for(int n = 0; n < sq.getObjects().size(); n++)
                {
                    IsoObject obj = (IsoObject)sq.getObjects().get(n);
                    if(obj.container != nullptr && obj.container.type == "counter"))
                        isCounter = true;
                }
                if(isCounter)
                    continue;
                std::string type = "WhiskeyFull";
                switch(Rand.Next(5))
                {
                case 0: // '\0'
                    type = "WhiskeyFull";
                    break;
                case 1: // '\001'
                    type = "WhiskeyHalf";
                    break;
                case 2: // '\002'
                    type = "WhiskeyEmpty";
                    break;
                case 3: // '\003'
                    type = "WineEmpty";
                    break;
                case 4: // '\004'
                    type = "WineEmpty2";
                    break;
                }
                FillTable(sq, room.RoomDef, type, 0.75F);
            }
            if(sq.getProperties().Is(IsoFlagType.tableS))
            {
                bool isCounter = false;
                for(int n = 0; n < sq.getObjects().size(); n++)
                {
                    IsoObject obj = (IsoObject)sq.getObjects().get(n);
                    if(obj.container != nullptr && obj.container.type == "counter"))
                        isCounter = true;
                }
                if(isCounter)
                    continue;
                std::string type = "WhiskeyFull";
                switch(Rand.Next(5))
                {
                case 0: // '\0'
                    type = "WhiskeyFull";
                    break;
                case 1: // '\001'
                    type = "WhiskeyHalf";
                    break;
                case 2: // '\002'
                    type = "WhiskeyEmpty";
                    break;
                case 3: // '\003'
                    type = "WineEmpty";
                    break;
                case 4: // '\004'
                    type = "WineEmpty2";
                    break;
                }
                FillTable(sq, room.RoomDef, type, 0.45F);
            }
            if(sq.getProperties().Is(IsoFlagType.floorS))
            {
                bool isCounter = false;
                for(int n = 0; n < sq.getObjects().size(); n++)
                {
                    IsoObject obj = (IsoObject)sq.getObjects().get(n);
                    if(obj.container != nullptr && obj.container.type == "counter"))
                        isCounter = true;
                }
                if(!isCounter)
                {
                    std::string type = "WhiskeyFull";
                    switch(Rand.Next(5))
                    {
                    case 0: // '\0'
                        type = "WhiskeyFull";
                        break;
                    case 1: // '\001'
                        type = "WhiskeyHalf";
                        break;
                    case 2: // '\002'
                        type = "WhiskeyEmpty";
                        break;
                    case 3: // '\003'
                        type = "WineEmpty";
                        break;
                    case 4: // '\004'
                        type = "WineEmpty2";
                        break;
                    }
                    FillTable(sq, room.RoomDef, type, 0.15F);
                }
            }
        } while(true);
    }
    private static void DoCounter(ItemContainer container, std::string roomDef)
    {
        FillTable(container.SourceGrid, roomDef);
        if(!roomDef == "tutKitchen2"))
            if(roomDef == "shopGeneral"))
            {
                int m = Rand.Next(3) + 1;
                for(int n = 0; n < m; n++)
                    container.AddItem("Bread");
                m = Rand.Next(3) + 1;
                for(int n = 0; n < m; n++)
                    container.AddItem("WhiskeyFull");
                if(Rand.Next(10) == 0)
                    container.AddItem("BaseballBat");
            } else
            if(roomDef == "shed"))
            {
                int m = 10;
                for(int n = 0; n < m; n++)
                    container.AddItem("Plank");
                m = 3;
                for(int n = 0; n < m; n++)
                    container.AddItem("Nails");
            }
    }
    private static void DoMedicine(ItemContainer container, std::string roomDef)
    {
        if(roomDef == "tutorialBathroom"))
            container.AddItem("Pills");
    }
    private static void DoShopBig(IsoRoom room)
    {
        Iterator i$ = room.TileList.iterator();
        do
        {
            if(!i$.hasNext())
                break;
            IsoGridSquare sq = (IsoGridSquare)i$.next();
            if(sq.getProperties().Is(IsoFlagType.tableS))
            {
                bool isCounter = false;
                for(int n = 0; n < sq.getObjects().size(); n++)
                {
                    IsoObject obj = (IsoObject)sq.getObjects().get(n);
                    if(obj.container != nullptr && obj.container.type == "counter"))
                        isCounter = true;
                }
                if(isCounter)
                    continue;
                std::string type = "None";
                switch(Rand.Next(9))
                {
                case 0: // '\0'
                    type = "Bread";
                    break;
                case 1: // '\001'
                    type = "TinnedSoup";
                    break;
                case 2: // '\002'
                    type = "WhiskeyFull";
                    break;
                case 3: // '\003'
                    type = "Pop";
                    break;
                case 4: // '\004'
                    type = "Pop2";
                    break;
                case 5: // '\005'
                    type = "Pop3";
                    break;
                case 6: // '\006'
                    type = "Crisps";
                    break;
                case 7: // '\007'
                    type = "Crisps2";
                    break;
                case 8: // '\b'
                    type = "Crisps3";
                    break;
                }
                FillTable(sq, room.RoomDef, type, 0.5F);
            }
            if(sq.getProperties().Is(IsoFlagType.floorS))
            {
                bool isCounter = false;
                for(int n = 0; n < sq.getObjects().size(); n++)
                {
                    IsoObject obj = (IsoObject)sq.getObjects().get(n);
                    if(obj.container != nullptr && obj.container.type == "counter"))
                        isCounter = true;
                }
                if(!isCounter)
                {
                    std::string type = "None";
                    switch(Rand.Next(9))
                    {
                    case 0: // '\0'
                        type = "Bread";
                        break;
                    case 1: // '\001'
                        type = "TinnedSoup";
                        break;
                    case 2: // '\002'
                        type = "WhiskeyFull";
                        break;
                    case 3: // '\003'
                        type = "Pop";
                        break;
                    case 4: // '\004'
                        type = "Pop2";
                        break;
                    case 5: // '\005'
                        type = "Pop3";
                        break;
                    case 6: // '\006'
                        type = "Crisps";
                        break;
                    case 7: // '\007'
                        type = "Crisps2";
                        break;
                    case 8: // '\b'
                        type = "Crisps3";
                        break;
                    }
                    FillTable(sq, room.RoomDef, type, 0.15F);
                }
            }
        } while(true);
    }
    private static void DoWardrobe(ItemContainer container, std::string roomDef)
    {
        if(roomDef == "tutorialBedroom"))
        {
            container.AddItem("Sheet");
            container.AddItem("Pillow");
        }
    }
    private static ItemContainer getRandomContainer(std::string containerTypes)
    {
        NulledArrayList choices = new NulledArrayList();
        if(DistributionTarget.isEmpty())
            return nullptr;
        std::string con[] = containerTypes.split(",");
        bool bDone = false;
        do
        {
            if(bDone)
                break;
            int n = Rand.Next(DistributionTarget.size());
            IsoBuilding b = (IsoBuilding)DistributionTarget.get(n);
            for(int l = 0; l < b.container.size(); l++)
            {
                for(int k = 0; k < con.length; k++)
                    if(((ItemContainer)b.container.get(l)).type == con[k].trim()))
                        choices.add(b.container.get(l));
            }
            if(!choices.isEmpty())
                bDone = true;
        } while(true);
        return (ItemContainer)choices.get(Rand.Next(choices.size()));
    }
    private static void PlaceOnRandomFloor(IsoCell cell, std::string zoneTypes, std::string objectType, int count)
    {
        NulledArrayList choices = new NulledArrayList();
        std::string con[] = zoneTypes.split(",");
        bool bDone = false;
        do
        {
            if(bDone)
                break;
            for(int l = 0; l < cell.getZoneStack().size(); l++)
            {
                zombie.iso.IsoCell.Zone b = (zombie.iso.IsoCell.Zone)cell.getZoneStack().get(l);
                for(int k = 0; k < con.length; k++)
                    if(b.Name == con[k].trim()))
                        choices.add(b);
            }
            if(!choices.isEmpty())
                bDone = true;
        } while(true);
        for(int n = 0; n < count; n++)
        {
            zombie.iso.IsoCell.Zone choice = (zombie.iso.IsoCell.Zone)choices.get(Rand.Next(choices.size()));
            IsoGridSquare sq = cell.getFreeTile(choice);
            if(sq != nullptr)
                sq.AddWorldInventoryItem(objectType, (float)(100 + Rand.Next(400)) / 1000F, (float)(100 + Rand.Next(400)) / 1000F, 0.0F);
        }
    }
    public static NulledArrayList DistributionTarget = new NulledArrayList();
    public static NulledArrayList Containers = new NulledArrayList();
}
} // namespace
