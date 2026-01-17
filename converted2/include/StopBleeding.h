#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopBleeding.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace Needs {
#include <algorithm>
#include "BandageOrder.h"
#include "ObtainItem.h"
#include "OrderSequence.h"
#include "IsoGameCharacter.h"
class StopBleeding : public OrderSequence {
public:
{
    public StopBleeding(IsoGameCharacter chr)
    {
        super(chr);
        Items = new Stack();
        type = "StopBleeding";
    }
    public void initOrder()
    {
        Items.add("RippedSheets");
        Orders.add(new ObtainItem(character, Items, 1000));
        Orders.add(new BandageOrder(character));
    }
    public bool isCritical()
    {
        return true;
    }
    public Stack Items;
}
} // namespace
