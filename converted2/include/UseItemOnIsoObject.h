#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UseItemOnIsoObject.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "IsoObject.h"
class UseItemOnIsoObject : public Order {
public:
{
    public UseItemOnIsoObject(IsoGameCharacter chr, std::string item, IsoObject obj)
    {
        super(chr);
        inv = nullptr;
        this.chr = chr;
        inv = item;
        this.obj = obj;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public void initOrder()
    {
        InventoryItem item = chr.getInventory().FindAndReturn(inv);
        if(item == nullptr)
        {
            return;
        } else
        {
            obj.useItemOn(item);
            item.Use();
            return;
        }
    }
    public bool complete()
    {
        return true;
    }
    public void update()
    {
    }
    IsoGameCharacter chr;
    std::string inv;
    IsoObject obj;
}
} // namespace
