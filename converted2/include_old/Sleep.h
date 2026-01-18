#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Sleep.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "InvalidParameterException.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "BaseCommand.h"
#include "ScriptCharacter.h"
#include "ScriptModule.h"
#include "UIManager.h"
class Sleep : public BaseCommand {
public:
{
    public Sleep()
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
        num = Float.parseFloat(params[0].trim());
    }
    public void begin()
    {
        if(module.getCharacter(owner).Actual == nullptr)
            throw new InvalidParameterException();
        module.getCharacter(owner).Actual.setAsleep(true);
        if(module.getCharacter(owner).Actual == IsoPlayer.getInstance())
        {
            IsoPlayer.instance.setAsleepTime(0.0F);
            module.getCharacter(owner).Actual.setForceWakeUpTime(num);
            UIManager.setbFadeBeforeUI(true);
            UIManager.FadeOut(4);
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
