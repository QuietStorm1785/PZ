#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DumpLootInContainer.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "LootBuilding.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "IsoSurvivor.h"
#include "NulledArrayList.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "Food.h"
#include "HandWeapon.h"
class DumpLootInContainer : public Order {
public:
{
    public DumpLootInContainer(IsoGameCharacter chr, ItemContainer con)
    {
        super(chr);
        this.chr = chr;
        this.con = con;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        for(int n = 0; n < chr.getInventory().Items.size(); n++)
        {
            InventoryItem item = (InventoryItem)chr.getInventory().Items.get(n);
            bool bSatisfiedWithFood = ((IsoSurvivor)chr).SatisfiedWithInventory(zombie.behaviors.survivor.orders.LootBuilding.LootStyle.Safehouse, zombie.characters.IsoSurvivor.SatisfiedBy.Food);
            bool bSatisfiedWithWeapons = ((IsoSurvivor)chr).SatisfiedWithInventory(zombie.behaviors.survivor.orders.LootBuilding.LootStyle.Safehouse, zombie.characters.IsoSurvivor.SatisfiedBy.Weapons);
            int wc = chr.getInventory().getWaterContainerCount();
            if(item.CanStoreWater)
            {
                if(wc > 2)
                {
                    chr.getInventory().Remove(item);
                    con.AddItem(item);
                }
                continue;
            }
            if(bSatisfiedWithFood && (item instanceof Food))
            {
                chr.getInventory().Remove(item);
                con.AddItem(item);
                continue;
            }
            if(bSatisfiedWithWeapons && (item instanceof HandWeapon))
            {
                chr.getInventory().Remove(item);
                con.AddItem(item);
                continue;
            }
            if(!(item instanceof HandWeapon) && !(item instanceof Food))
            {
                chr.getInventory().Remove(item);
                con.AddItem(item);
            }
        }
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public bool complete()
    {
        return true;
    }
    public void update()
    {
    }
    IsoGameCharacter chr;
    ItemContainer con;
}
} // namespace
