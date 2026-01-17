#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ObtainItemBehavior.java
namespace zombie {
namespace behaviors {
namespace survivor {
#include "Behavior.h"
#include "DecisionPath.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "ItemType.h"
#include "IsoGridSquare.h"
// Referenced classes of package zombie.behaviors.survivor:
//            FindKnownItemBehavior
class ObtainItemBehavior : public Behavior {
public:
{
    public ObtainItemBehavior()
    {
        FindItem = ItemType.None;
        DoneFindItem = false;
        findItem = new FindKnownItemBehavior();
        Found = false;
        HaveLocation = false;
        LocationIsInventory = false;
        pathFind = new PathFindBehavior("ObtainItem");
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        if(!HaveLocation)
        {
            if(!DoneFindItem)
            {
                DoneFindItem = true;
                findItem.reset();
                findItem.FindItem = FindItem;
                zombie.behaviors.Behavior.BehaviorResult res = findItem.process(path, character);
                if(res == zombie.behaviors.Behavior.BehaviorResult.Failed)
                    return zombie.behaviors.Behavior.BehaviorResult.Working;
                if(res == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
                {
                    if(findItem.LocationIsInventory)
                    {
                        LocationIsInventory = true;
                        Found = true;
                        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
                    }
                    LocationIsInventory = false;
                    Found = true;
                    container = findItem.container;
                    pathFind.reset();
                    pathFind.sx = (int)character.getX();
                    pathFind.sy = (int)character.getY();
                    pathFind.sz = (int)character.getZ();
                    pathFind.tx = container.SourceGrid.getX();
                    pathFind.ty = container.SourceGrid.getY();
                    pathFind.tz = container.SourceGrid.getZ();
                    HaveLocation = true;
                }
            }
        } else
        {
            zombie.behaviors.Behavior.BehaviorResult result = pathFind.process(path, character);
            if(result == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
            {
                zombie.inventory.InventoryItem item = container.Remove(FindItem);
                pathFind.reset();
                character.setPath(nullptr);
                if(item != nullptr)
                {
                    character.getInventory().AddItem(item);
                    return result;
                }
            }
            if(result == zombie.behaviors.Behavior.BehaviorResult.Failed)
                return result;
        }
        return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public void reset()
    {
        HaveLocation = false;
        findItem.reset();
    }
    public bool valid()
    {
        return true;
    }
    public ItemType FindItem;
    ItemContainer container;
    bool DoneFindItem;
    FindKnownItemBehavior findItem;
    bool Found;
    bool HaveLocation;
    bool LocationIsInventory;
    PathFindBehavior pathFind;
}
} // namespace
