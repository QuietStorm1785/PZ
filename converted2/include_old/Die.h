#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Die.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "IsoGameCharacter.h"
#include "IsoDeadBody.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class Die : public BaseCommand {
public:
{
    public Die()
    {
        bGory = false;
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        bGory = params[0] == "true");
    }
    public void begin()
    {
        IsoGameCharacter actual = module.getCharacterActual(owner);
        if(actual != nullptr)
        {
            actual.setHealth(0.0F);
            IsoDeadBody body = new IsoDeadBody(actual);
        }
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
    bool bGory;
}
} // namespace
