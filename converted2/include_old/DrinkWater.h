#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DrinkWater.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace Needs {
#include <algorithm>
#include "GotoBuildingOrder.h"
#include "GotoNextTo.h"
#include "GotoRoomOrder.h"
#include "UseItemOnIsoObject.h"
#include "Order.h"
#include "OrderSequence.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "iso.h"
#include "areas.h"
class DrinkWater : public OrderSequence {
public:
{
    public DrinkWater(IsoGameCharacter chr)
    {
        super(chr);
        type = "DrinkWater";
    }
    public void initOrder()
    {
        IsoBuilding b = nullptr;
        if(character.getCurrentSquare().getRoom() != nullptr && character.getCurrentSquare().getRoom().building.hasWater())
            b = character.getCurrentSquare().getRoom().building;
        if(b == nullptr && character.getDescriptor().getGroup().Safehouse.hasWater())
            b = character.getDescriptor().getGroup().Safehouse;
        if(b == nullptr)
        {
            Iterator buildings = IsoWorld.instance.getCell().getBuildingList().iterator();
            do
            {
                if(buildings == nullptr || !buildings.hasNext())
                    break;
                IsoBuilding bb = (IsoBuilding)buildings.next();
                if(bb.hasWater())
                    choices.add(bb);
            } while(true);
        }
        float closest = 1E+007F;
label0:
        for(int n = 0; n < choices.size(); n++)
        {
            IsoBuilding choice = (IsoBuilding)choices.get(n);
            int x = 0;
            do
            {
                if(x >= choice.Exits.size())
                    continue label0;
                float dist = IsoUtils.DistanceManhatten(((IsoRoomExit)choice.Exits.get(x)).x, ((IsoRoomExit)choice.Exits.get(x)).y, character.x, character.y);
                if(dist < closest)
                {
                    b = choice;
                    continue label0;
                }
                x++;
            } while(true);
        }
        choices.clear();
        Iterator it = nullptr;
        if(b == nullptr)
            return;
        if(character.getCurrentBuilding() != b)
            Orders.add(new GotoBuildingOrder(character, b));
        for(it = b.Rooms.iterator(); it != nullptr && it.hasNext();)
        {
            IsoRoom r = (IsoRoom)it.next();
            if(!r.WaterSources.isEmpty())
            {
                IsoObject waterSource = nullptr;
                int i = 0;
                do
                {
                    if(i >= r.WaterSources.size())
                        break;
                    if(((IsoObject)r.WaterSources.get(i)).hasWater())
                    {
                        waterSource = (IsoObject)r.WaterSources.get(i);
                        break;
                    }
                    i++;
                } while(true);
                if(waterSource != nullptr)
                {
                    GotoRoomOrder roomOrder = new GotoRoomOrder(character, r);
                    Orders.add(roomOrder);
                    if(character.getInventory().getWaterContainerCount() > 0)
                    {
                        Orders.add(new GotoNextTo(character, waterSource.square.getX(), waterSource.square.getY(), waterSource.square.getZ()));
                        ArrayList items = character.getInventory().getAllWaterFillables();
                        for(int n = 0; n < items.size(); n++)
                            Orders.add(new UseItemOnIsoObject(character, ((InventoryItem)items.get(n)).getType(), waterSource));
                    }
                    return;
                }
            }
        }
    }
    public bool ActedThisFrame()
    {
        return ((Order)Orders.get(ID)).ActedThisFrame();
    }
    static ArrayList choices = new ArrayList();
}
} // namespace
