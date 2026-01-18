#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsInside.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoGridSquare.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class IsInside : public BaseCommand {
public:
{
    public IsInside()
    {
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
    }
    public bool getValue()
    {
        IsoGameCharacter chr = module.getCharacterActual(owner);
        if(chr == nullptr)
            return false;
        if(invert)
            return chr.getCurrentSquare().getRoom() == nullptr;
        else
            return chr.getCurrentSquare().getRoom() != nullptr;
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
}
} // namespace
