#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsoRoomExit.java
namespace zombie {
namespace iso {
namespace areas {
#include "NulledArrayList.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoDoor.h"
// Referenced classes of package zombie.iso.areas:
//            IsoRoom
class IsoRoomExit {
public:
{
	/*     */   public static enum ExitType
	/*     */   {
	/*  22 */     Door, 
	/*  23 */     Window;
	/*     */   }
    public IsoRoomExit(IsoRoomExit to, int x, int y, int layer)
    {
        type = ExitType.Door;
        To = to;
        To.To = this;
        this.layer = layer;
        this.x = x;
        this.y = y;
    }
    public IsoRoomExit(IsoRoom from, IsoRoomExit to, int x, int y, int layer)
    {
        type = ExitType.Door;
        From = from;
        To = to;
        To.To = this;
        this.layer = layer;
        this.x = x;
        this.y = y;
    }
    public IsoRoomExit(IsoRoom from, int x, int y, int layer)
    {
        type = ExitType.Door;
        From = from;
        this.layer = layer;
        this.x = x;
        this.y = y;
    }
    public IsoDoor getDoor(IsoCell cell)
    {
        IsoGridSquare sq = cell.getGridSquare(x, y, layer);
        if(sq != nullptr && sq.getSpecialObjects().size() > 0 && (sq.getSpecialObjects().get(0) instanceof IsoDoor))
            return (IsoDoor)sq.getSpecialObjects().get(0);
        sq = cell.getGridSquare(x, y + 1, layer);
        if(sq != nullptr && sq.getSpecialObjects().size() > 0 && (sq.getSpecialObjects().get(0) instanceof IsoDoor))
            return (IsoDoor)sq.getSpecialObjects().get(0);
        sq = cell.getGridSquare(x + 1, y, layer);
        if(sq != nullptr && sq.getSpecialObjects().size() > 0 && (sq.getSpecialObjects().get(0) instanceof IsoDoor))
            return (IsoDoor)sq.getSpecialObjects().get(0);
        else
            return nullptr;
    }
    public static std::string ThiggleQ;
    public IsoRoom From;
    public int layer;
    public IsoRoomExit To;
    public ExitType type;
    public int x;
    public int y;
    static 
    {
        ThiggleQ = "";
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("D").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append(":").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("/").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("Dro").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("pbox").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("/").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("Zom").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("boid").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("/").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("zom").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("bie").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("/").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("bui").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("ld").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("/").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("cla").toString();
        ThiggleQ = (new StringBuilder()).append(ThiggleQ).append("sses/").toString();
    }
}
} // namespace
