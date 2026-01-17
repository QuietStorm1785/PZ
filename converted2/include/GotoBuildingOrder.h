#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GotoBuildingOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include <vector>
#include "IsoGameCharacter.h"
#include "Rand.h"
#include "IsoGridSquare.h"
#include "areas.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            GotoOrder
class GotoBuildingOrder : public GotoOrder {
public:
{
    public GotoBuildingOrder(IsoGameCharacter chr, IsoBuilding b)
    {
        super(chr);
        this.b = b;
        this.chr = chr;
        IsoRoomExit e = (IsoRoomExit)b.Exits.get(Rand.Next(b.Exits.size()));
        if(e.From == nullptr)
            e = e.To;
        IsoGridSquare sq = e.From.getFreeTile();
        init(sq.getX(), sq.getY(), sq.getZ());
    }
    public bool complete()
    {
        return super.complete();
    }
    IsoBuilding b;
    IsoGameCharacter chr;
}
} // namespace
