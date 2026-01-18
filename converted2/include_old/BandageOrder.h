#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BandageOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "Order.h"
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
class BandageOrder : public Order {
public:
{
    public BandageOrder(IsoGameCharacter chr)
    {
        super(chr);
        this.chr = chr;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public void initOrder()
    {
        InventoryItem item = chr.getInventory().getBestBandage(chr.getDescriptor());
        if(item == nullptr)
        {
            return;
        } else
        {
            chr.getBodyDamage().UseBandageOnMostNeededPart();
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
}
} // namespace
