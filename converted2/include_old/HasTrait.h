#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   HasTrait.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class HasTrait : public BaseCommand {
public:
{
    public HasTrait()
    {
        invert = false;
        val = "";
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        if(owner.indexOf("!") == 0)
        {
            invert = true;
            owner = owner.substring(1);
        }
        val = params[0].trim().replace("\"", "");
    }
    public bool getValue()
    {
        IsoGameCharacter chr = module.getCharacterActual(owner);
        if(chr == nullptr)
            return false;
        if(invert)
            return !chr.HasTrait(val);
        else
            return chr.HasTrait(val);
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
    bool invert;
    std::string val;
}
} // namespace
