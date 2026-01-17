#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsNight.java
namespace zombie {
namespace scripting {
namespace commands {
namespace DayNight {
#include "GameTime.h"
#include "BaseCommand.h"
class IsNight : public BaseCommand {
public:
{
    public IsNight()
    {
        invert = false;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        bool bNight = false;
        if(GameTime.getInstance().getTimeOfDay() > 20F || GameTime.getInstance().getTimeOfDay() < 6F)
            bNight = true;
        if(invert)
            bNight = !bNight;
        return bNight;
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
        if(object != nullptr && object == "!"))
            invert = true;
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string character;
}
} // namespace
