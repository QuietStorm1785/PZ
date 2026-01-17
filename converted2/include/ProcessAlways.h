#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ProcessAlways.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Trigger {
#include "THashMap.h"
#include <vector>
#include "JOptionPane.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "Trigger.h"
class ProcessAlways : public BaseCommand {
public:
{
    public ProcessAlways()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr)
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        } else
        {
            position = object.toLowerCase();
            return;
        }
    }
    public void begin()
    {
        List trigList = (List)ScriptManager.instance.CustomTriggerMap.get(position);
        for(int n = 0; n < trigList.size(); n++)
            ((Trigger)trigList.get(n)).Locked = false;
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
    std::string position;
}
} // namespace
