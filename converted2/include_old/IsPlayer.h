#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsPlayer.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "BaseCommand.h"
#include "objects.h"
class IsPlayer : public BaseCommand {
public:
{
    public IsPlayer()
    {
        modifier = 0;
        invert = false;
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object.indexOf("!") == 0)
        {
            invert = true;
            object = object.substring(1);
        }
        owner = object;
    }
    public bool getValue()
    {
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
            chr = currentinstance.getAlias(owner);
        else
            chr = module.getCharacter(owner).Actual;
        if(chr == nullptr)
            return false;
        if(chr instanceof IsoPlayer)
            return !invert;
        else
            return invert;
    }
    public void begin()
    {
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return true;
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    std::string stat;
    int modifier;
    IsoGameCharacter chr;
    bool invert;
}
} // namespace
