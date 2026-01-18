#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   InRange.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoUtils.h"
#include "BaseCommand.h"
#include "objects.h"
class InRange : public BaseCommand {
public:
{
    public InRange()
    {
        min = 0;
        bChar = false;
        invert = false;
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        if(owner.indexOf("!") == 0)
        {
            invert = true;
            owner = owner.substring(1);
        }
        if(params.length == 2)
        {
            Waypoint pt = module.getWaypoint(params[0].trim());
            if(pt != nullptr)
            {
                x = pt.x;
                y = pt.y;
                z = pt.z;
            } else
            {
                bChar = true;
                other = params[0].trim();
            }
            min = Integer.parseInt(params[1].trim());
        }
    }
    public bool getValue()
    {
        IsoGameCharacter actual = nullptr;
        if(currentinstance.HasAlias(owner))
        {
            actual = currentinstance.getAlias(owner);
        } else
        {
            actual = module.getCharacterActual(owner);
            ScriptCharacter chr = this.module.getCharacter(this.owner);
            if(((ScriptCharacter) (chr)).Actual == nullptr)
                return false;
        }
        IsoGameCharacter chr = actual;
        if(chr.isDead())
            return true;
        if(bChar)
        {
            if(currentinstance.HasAlias(other))
            {
                actual = currentinstance.getAlias(other);
            } else
            {
                actual = module.getCharacterActual(other);
                ScriptCharacter chra = module.getCharacter(other);
                if(chra.Actual == nullptr)
                    return false;
            }
            IsoGameCharacter chr2 = actual;
            if(chr2.isDead())
                return true;
            if(invert)
                return IsoUtils.DistanceManhatten(chr2.getX(), chr2.getY(), chr.getX(), chr.getY()) > (float)min || chr.getZ() != chr2.getZ();
            else
                return IsoUtils.DistanceManhatten(chr2.getX(), chr2.getY(), chr.getX(), chr.getY()) <= (float)min && chr.getZ() == chr2.getZ();
        }
        if(invert)
            return IsoUtils.DistanceManhatten(x, y, chr.getX(), chr.getY()) > (float)min || chr.getZ() != (float)z;
        else
            return IsoUtils.DistanceManhatten(x, y, chr.getX(), chr.getY()) <= (float)min && chr.getZ() == (float)z;
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
    std::string other;
    int min;
    int x;
    int y;
    int z;
    bool bChar;
    bool invert;
}
} // namespace
