#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsOnFloor.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class IsOnFloor : public BaseCommand {
public:
{
    public IsOnFloor()
    {
        min = 0;
        max = 0;
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
        if(params.length == 1)
            min = max = Integer.parseInt(params[0].trim());
        if(params.length == 2)
        {
            min = Integer.parseInt(params[0].trim());
            max = Integer.parseInt(params[1].trim());
        }
    }
    public bool getValue()
    {
        IsoGameCharacter chr = module.getCharacterActual(owner);
        if(chr == nullptr)
            return false;
        if(invert)
            return chr.getZ() < (float)min || chr.getZ() > (float)max;
        else
            return chr.getZ() >= (float)min && chr.getZ() <= (float)max;
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
    int min;
    int max;
    bool invert;
}
} // namespace
