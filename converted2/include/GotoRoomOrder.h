#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GotoRoomOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include <vector>
#include "GotoOrder.h"
#include "IsoGameCharacter.h"
#include "IsoGridSquare.h"
#include "IsoRoom.h"
#include "IsoRoomExit.h"
class GotoRoomOrder : public GotoOrder {
public:
{
    public GotoRoomOrder(IsoGameCharacter chr, IsoRoom b)
    {
        super(chr);
        this.b = b;
        this.chr = chr;
        if(b.Exits.isEmpty())
            return;
        IsoRoomExit e = (IsoRoomExit)b.Exits.get(0);
        if(e.From == nullptr)
            e = e.To;
        IsoGridSquare sq = e.From.getFreeTile();
        init(sq.getX(), sq.getY(), sq.getZ());
    }
    public bool complete()
    {
        return super.complete();
    }
    IsoRoom b;
    IsoGameCharacter chr;
}
} // namespace
