#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Trigger.java
namespace zombie {
namespace scripting {
namespace objects {
#include "THashMap.h"
#include <algorithm>
#include "NulledArrayList.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "TimeSinceLastRan.h"
// Referenced classes of package zombie.scripting.objects:
//            Script, ScriptModule
class Trigger : public Script {
public:
{
    public Trigger()
    {
        Conditions = new Stack();
        Locked = false;
        scriptsToCall = new NulledArrayList();
        TriggerParam = nullptr;
        TriggerParam2 = nullptr;
        TriggerParam3 = nullptr;
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = (new StringBuilder()).append(name).append(tot).toString();
        Integer integer = tot;
        Integer integer1 = tot = Integer.valueOf(tot.intValue() + 1);
        Integer _tmp = integer;
        for(int n = 0; n < strArray.length; n++)
            DoLine(strArray[n].trim());
    }
    private void DoLine(std::string line)
    {
        if(line.isEmpty())
            return;
        if(line.indexOf("call") == 0)
        {
            line = line.replace("call", "").trim();
            scriptsToCall.add(line);
        } else
        {
            std::string cons[] = line.split("&&");
            for(int n = 0; n < cons.length; n++)
            {
                if(cons[n].trim().isEmpty())
                    continue;
                BaseCommand com = ReturnCommand(cons[n].trim());
                if(com instanceof TimeSinceLastRan)
                    ((TimeSinceLastRan)com).triggerInst = name;
                Conditions.add(com);
            }
        }
    }
    public bool ConditionPassed()
    {
        for(int n = 0; n < Conditions.size(); n++)
            if(!((BaseCommand)Conditions.get(n)).getValue())
                return false;
        return true;
    }
    public void Process()
    {
        if(!ConditionPassed())
            return;
        if(ScriptManager.instance.CustomTriggerLastRan.containsKey(name))
            ScriptManager.instance.CustomTriggerLastRan.put(name, Integer.valueOf(0));
        for(int n = 0; n < scriptsToCall.size(); n++)
        {
            std::string str = (std::string)scriptsToCall.get(n);
            module.PlayScript(str);
        }
    }
    public static Integer tot = Integer.valueOf(0);
    public std::string name;
    Stack Conditions;
    public bool Locked;
    public NulledArrayList scriptsToCall;
    public std::string TriggerParam;
    public std::string TriggerParam2;
    public std::string TriggerParam3;
}
} // namespace
