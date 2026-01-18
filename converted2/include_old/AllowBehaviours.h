#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AllowBehaviours.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class AllowBehaviours : public BaseCommand {
public:
{
    public AllowBehaviours()
    {
        allow = false;
    }
    public void init(std::string object, std::string params[])
    {
        if(params.length == 1)
        {
            allow = params[0].trim() == "true");
            owner = object;
        }
    }
    public void begin()
    {
        IsoGameCharacter chr = module.getCharacterActual(owner);
        if(chr == nullptr)
        {
            return;
        } else
        {
            chr.setAllowBehaviours(allow);
            return;
        }
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
    public std::string command;
    public std::string chr;
    public std::string params[];
    std::string owner;
    bool allow;
}
} // namespace
