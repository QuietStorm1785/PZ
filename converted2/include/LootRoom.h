#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LootRoom.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <algorithm>
#include <vector>
#include "IsoGameCharacter.h"
#include "ItemContainer.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoRoom.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            OrderSequence, GotoNextTo, LootContainer, LootBuilding
class LootRoom : public OrderSequence {
public:
{
    public LootRoom(IsoGameCharacter chr, IsoRoom room, LootBuilding.LootStyle style)
    {
        super(chr);
        this.style = style;
        this.room = room;
        this.chr = chr;
        for(int n = 0; n < room.Containers.size(); n++)
        {
            ItemContainer con = (ItemContainer)room.Containers.get(n);
            IsoGridSquare sq = con.parent.square;
            Orders.add(new GotoNextTo(chr, sq.getX(), sq.getY(), sq.getZ()));
            Orders.add(new LootContainer(chr, con, style));
        }
    }
    public void init()
    {
    }
    IsoGameCharacter chr;
    IsoRoom room;
    LootBuilding.LootStyle style;
}
} // namespace
