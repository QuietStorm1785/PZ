#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsLastFiredParameter.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Trigger {
#include "THashMap.h"
#include <vector>
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "Trigger.h"
class IsLastFiredParameter : public BaseCommand {
public:
{
    public IsLastFiredParameter()
    {
        invert = false;
        param = 0;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        List trigList = (List)ScriptManager.instance.TriggerMap.get(val);
        if(trigList == nullptr)
            return false;
        if(trigList.isEmpty())
            return false;
        std::string par = nullptr;
        switch(param)
        {
        case 0: // '\0'
            par = ((Trigger)trigList.get(0)).TriggerParam;
            break;
        case 1: // '\001'
            par = ((Trigger)trigList.get(0)).TriggerParam2;
            break;
        case 2: // '\002'
            par = ((Trigger)trigList.get(0)).TriggerParam3;
            break;
        }
        if(invert)
            return !paramval == par);
        else
            return paramval == par);
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
        val = object.toLowerCase();
        if(val.indexOf("!") == 0)
        {
            invert = true;
            val = val.substring(1);
        }
        if(params.length == 1)
            paramval = params[0].trim().replace("\"", "");
        else
        if(params.length == 2)
        {
            param = Integer.parseInt(params[0].trim());
            paramval = params[1].trim().replace("\"", "");
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string val;
    std::string paramval;
    int param;
}
} // namespace
