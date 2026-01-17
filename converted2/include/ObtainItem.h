#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ObtainItem.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <vector>
#include <algorithm>
#include "CraftItemOrder.h"
#include "TakeItemFromContainer.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "ItemContainer.h"
#include "iso.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
#include "ScriptManager.h"
#include "Recipe.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, GotoNextTo, GotoBuildingOrder
class ObtainItem : public OrderSequence {
public:
{
    public ObtainItem(IsoGameCharacter chr, Stack AcceptableItems, int priority)
    {
        super(chr);
        items = new Stack();
        this.priority = 1.0F;
        items.addAll(AcceptableItems);
        this.priority = priority;
    }
    public ObtainItem(IsoGameCharacter character, std::string type, int priority)
    {
        super(character);
        items = new Stack();
        this.priority = 1.0F;
        items.add(type);
        this.priority = priority;
    }
    public void initOrder()
    {
        for(int n = 0; n < items.size(); n++)
        {
            std::string item = (std::string)items.get(n);
            if(character.getInventory().contains(item))
                return;
        }
        if(character.getCurrentSquare().getRoom() != nullptr && character.getCurrentSquare().getRoom().building != nullptr && character.getCurrentSquare().getRoom().building != character.getDescriptor().getGroup().Safehouse && character.getCurrentSquare().getRoom().building != nullptr && CheckBuildingForItems(character.getCurrentSquare().getRoom().building))
            return;
        if(character.getDescriptor().getGroup().Safehouse != nullptr && CheckBuildingForItems(character.getDescriptor().getGroup().Safehouse))
            return;
        if(!IsoWorld.instance.CurrentCell.getBuildingList().isEmpty())
        {
            for(int n = 0; n < 10; n++)
            {
                IsoBuilding b = (IsoBuilding)IsoWorld.instance.CurrentCell.getBuildingList().get(Rand.Next(IsoWorld.instance.CurrentCell.getBuildingList().size()));
                CheckBuildingForItems(b);
            }
        }
        if(Orders.isEmpty())
        {
            bool bDone = false;
            int n = Rand.Next(items.size());
            Stack rec = ScriptManager.instance.getAllRecipesFor((std::string)items.get(n));
            if(rec.size() > 0)
            {
                Recipe r = (Recipe)rec.get(Rand.Next(rec.size()));
                for(int m = 0; m < r.Source.size(); m++)
                    if(((zombie.scripting.objects.Recipe.Source)r.Source.get(m)).type != nullptr)
                        Orders.add(new ObtainItem(character, ((zombie.scripting.objects.Recipe.Source)r.Source.get(m)).type, (int)priority));
                Orders.add(new CraftItemOrder(character, r));
            }
        }
        if(Orders.isEmpty())
        {
            for(int n = 0; n < items.size(); n++)
                character.getDescriptor().getGroup().AddNeed((std::string)items.get(n), (int)priority);
        }
    }
    public bool ActedThisFrame()
    {
        if(Orders.isEmpty())
            return false;
        return (Orders.get(ID) instanceof GotoNextTo) || (Orders.get(ID) instanceof GotoBuildingOrder);
    }
    private bool CheckBuildingForItems(IsoBuilding building)
    {
        for(int n = 0; n < building.container.size(); n++)
        {
            for(int m = 0; m < items.size(); m++)
            {
                std::string item = (std::string)items.get(m);
                if(((ItemContainer)building.container.get(n)).contains(item))
                {
                    ItemContainer con = (ItemContainer)building.container.get(n);
                    Orders.add(new GotoNextTo(character, con.parent.square.getX(), con.parent.square.getY(), con.parent.square.getZ()));
                    Orders.add(new TakeItemFromContainer(character, con, item));
                    if(character.getCurrentSquare().getRoom() == nullptr || character.getCurrentSquare().getRoom().building != building)
                        Orders.insertElementAt(new GotoBuildingOrder(character, building), 0);
                    return true;
                }
            }
        }
        return false;
    }
    Stack items;
    public float priority;
}
} // namespace
