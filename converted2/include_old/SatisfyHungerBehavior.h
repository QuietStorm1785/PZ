#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SatisfyHungerBehavior.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include "Behavior.h"
#include "DecisionPath.h"
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "ItemType.h"
// Referenced classes of package zombie.behaviors.survivor:
//            ObtainItemBehavior
class SatisfyHungerBehavior : public Behavior {
public:
{
    public SatisfyHungerBehavior()
    {
        obtain = new ObtainItemBehavior();
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        obtain.FindItem = ItemType.Food;
        obtain.Found = false;
        zombie.behaviors.Behavior.BehaviorResult res = obtain.process(path, character);
        if(res == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
        {
            zombie.inventory.InventoryItem item = character.getInventory().Remove(ItemType.Food);
            character.Eat(item);
            reset();
        }
        return res;
    }
    public void reset()
    {
        obtain.reset();
        obtain.FindItem = ItemType.Food;
        obtain.Found = false;
        obtain.HaveLocation = false;
        obtain.DoneFindItem = false;
        obtain.container = nullptr;
    }
    public bool valid()
    {
        return true;
    }
    ObtainItemBehavior obtain;
}
} // namespace
