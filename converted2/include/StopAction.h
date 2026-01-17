#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopAction.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "InvalidParameterException.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptCharacter.h"
#include "ScriptModule.h"
class StopAction : public BaseCommand {
public:
{
    public StopAction()
    {
        num = 1.0F;
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
        owner = object;
    }
    public void begin()
    {
        if(module.getCharacter(owner).Actual == nullptr)
        {
            throw new InvalidParameterException();
        } else
        {
            module.getCharacter(owner).Actual.StopAllActionQueue();
            return;
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    std::string owner;
    IsoGameCharacter chr;
    float num;
}
} // namespace
