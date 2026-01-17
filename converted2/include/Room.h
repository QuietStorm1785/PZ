#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Room.java
namespace zombie {
namespace scripting {
namespace objects {
#include <vector>
#include "IsoGridSquare.h"
#include "IsoRoom.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class Room : public BaseScriptObject {
public:
{
    public Room()
    {
        room = nullptr;
    }
    public Room(std::string RoomDef, IsoRoom room)
    {
        this.room = nullptr;
        name = RoomDef;
        this.room = room;
        IsoGridSquare sq = (IsoGridSquare)room.TileList.get(0);
        x = sq.getX();
        y = sq.getY();
        z = sq.getZ();
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        x = Integer.parseInt(strArray[0].trim());
        y = Integer.parseInt(strArray[1].trim());
        z = Integer.parseInt(strArray[2].trim());
    }
    public int x;
    public int y;
    public int z;
    public std::string name;
    public IsoRoom room;
}
} // namespace
