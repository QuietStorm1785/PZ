#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FindKnownItemBehavior.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include "Behavior.h"
#include "DecisionPath.h"
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "ItemType.h"
#include "IsoGridSquare.h"
#include "IsoBuilding.h"
#include "IsoRoom.h"
class FindKnownItemBehavior : public Behavior {
public:
{
    public FindKnownItemBehavior()
    {
        FindItem = ItemType.None;
        Found = false;
        LocationIsInventory = false;
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        Found = false;
        if(character.getInventory().HasType(FindItem))
        {
            LocationIsInventory = true;
            Found = true;
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        }
        LocationIsInventory = false;
        if(character.getCurrentSquare().getRoom() != nullptr)
        {
            container = character.getCurrentSquare().getRoom().building.getContainerWith(FindItem);
            if(container != nullptr)
            {
                Found = true;
                return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
            }
        }
        return zombie.behaviors.Behavior.BehaviorResult.Failed;
    }
    public void reset()
    {
    }
    public bool valid()
    {
        return true;
    }
    public ItemType FindItem;
    public bool Found;
    public bool LocationIsInventory;
    ItemContainer container;
}
} // namespace
