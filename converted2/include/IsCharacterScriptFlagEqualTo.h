#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsCharacterScriptFlagEqualTo.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "SurvivorDesc.h"
#include "BaseCommand.h"
#include "objects.h"
class IsCharacterScriptFlagEqualTo : public BaseCommand {
public:
{
    public IsCharacterScriptFlagEqualTo()
    {
        modifier = 0;
        value = "";
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
        name = params[1].trim().replace("\"", "");
        value = params[2].trim().replace("\"", "");
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
            other = currentinstance.getAlias(Other);
        else
        if(module.getCharacter(Other) == nullptr)
            other = nullptr;
        else
        if(module.getCharacter(Other).Actual == nullptr)
            other = nullptr;
        else
            other = module.getCharacter(Other).Actual;
        if(chr == nullptr)
            return false;
        std::string str = "";
        if(other != nullptr)
            str = (new StringBuilder()).append(chr.getDescriptor().getID()).append("_").append(other.getDescriptor().getID()).append("_").append(name).toString();
        else
            str = (new StringBuilder()).append(chr.getDescriptor().getID()).append("_").append(name).toString();
        ScriptFlag flag = module.getFlag(name);
        if(flag == nullptr)
            return false;
        else
            return flag.IsValue(value);
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
    public std::string name;
    std::string value;
    std::string Other;
    bool invert;
}
} // namespace
