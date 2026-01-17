#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsInGroupWith.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "characters.h"
#include "BaseCommand.h"
#include "objects.h"
class IsInGroupWith : public BaseCommand {
public:
{
    public IsInGroupWith()
    {
        modifier = 0;
        Other = "";
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
        Other = params[0].trim();
    }
    public bool getValue()
    {
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
        {
            chr = currentinstance.getAlias(owner);
        } else
        {
            if(module.getCharacter(owner) == nullptr)
                return false;
            if(module.getCharacter(owner).Actual == nullptr)
                return false;
            chr = module.getCharacter(owner).Actual;
        }
        IsoGameCharacter other;
        if(currentinstance != nullptr && currentinstance.HasAlias(Other))
        {
            other = currentinstance.getAlias(Other);
        } else
        {
            if(module.getCharacter(Other) == nullptr)
                return false;
            if(module.getCharacter(Other).Actual == nullptr)
                return false;
            other = module.getCharacter(Other).Actual;
        }
        if(chr == nullptr)
            return false;
        if(chr.getDescriptor().getGroup() != nullptr && chr.getDescriptor().getGroup().IsMember(other.getDescriptor()))
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
    std::string Other;
    bool invert;
}
} // namespace
