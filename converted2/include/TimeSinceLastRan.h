#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TimeSinceLastRan.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Trigger {
#include "THashMap.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
class TimeSinceLastRan : public BaseCommand {
public:
{
    public TimeSinceLastRan()
    {
        invert = false;
        frames = 0;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        bool bOver = ((Integer)ScriptManager.instance.CustomTriggerLastRan.get(triggerInst)).intValue() > frames;
        if(invert)
            return !bOver;
        else
            return bOver;
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
        if(object != nullptr)
        {
            triggerInst = object.toLowerCase();
            if(triggerInst.indexOf("!") == 0)
            {
                invert = true;
                triggerInst = triggerInst.substring(1);
            }
        }
        frames = (int)(30F * Float.parseFloat(params[0].trim()));
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    public std::string triggerInst;
    int frames;
}
} // namespace
