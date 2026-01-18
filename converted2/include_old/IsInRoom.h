#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsInRoom.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoGridSquare.h"
#include "IsoRoom.h"
#include "BaseCommand.h"
#include "Room.h"
#include "ScriptModule.h"
class IsInRoom : public BaseCommand {
public:
{
    public IsInRoom()
    {
        invert = false;
    }
    public void init(std::string object, std::string params[])
    {
        if(params[0].contains(")"))
            object = object;
        owner = object;
        if(owner.indexOf("!") == 0)
        {
            invert = true;
            owner = owner.substring(1);
        }
        room = params[0].trim();
    }
    public bool getValue()
    {
        IsoGameCharacter chr = module.getCharacterActual(owner);
        if(chr == nullptr)
            return false;
        Room room = module.getRoom(this.room);
        if(room != nullptr)
        {
            if(chr.getCurrentSquare().getRoom() == nullptr)
                return false;
            if(invert)
                return !room.name == chr.getCurrentSquare().getRoom().RoomDef);
            else
                return room.name == chr.getCurrentSquare().getRoom().RoomDef);
        }
        IsoGameCharacter chr2 = module.getCharacterActual(this.room);
        if(chr2 == nullptr)
            return false;
        bool bTrue = false;
        if(chr.getCurrentSquare() == nullptr || chr2.getCurrentSquare() == nullptr)
            return false;
        if(chr.getCurrentSquare().getRoom() == chr2.getCurrentSquare().getRoom())
            bTrue = true;
        if(invert)
            return !bTrue;
        else
            return bTrue;
    }
    public void begin()
    {
    }
    public void Finish()
    {
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string room;
    bool invert;
}
} // namespace
