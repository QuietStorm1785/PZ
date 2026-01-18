#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DumpLootOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include "DumpLootInContainer.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "Rand.h"
#include "ItemContainer.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoBuilding.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, GotoNextTo
class DumpLootOrder : public OrderSequence {
public:
{
    public DumpLootOrder(IsoGameCharacter chr, IsoBuilding b)
    {
        super(chr);
        if(b.container.size() == 0)
        {
            return;
        } else
        {
            ItemContainer con = (ItemContainer)b.container.get(Rand.Next(b.container.size()));
            Orders.add(new GotoNextTo(chr, con.parent.square.getX(), con.parent.square.getY(), con.parent.square.getZ()));
            Orders.add(new DumpLootInContainer(chr, con));
            return;
        }
    }
}
} // namespace
