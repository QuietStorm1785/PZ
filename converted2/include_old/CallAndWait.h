#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CallAndWait.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "THashMap.h"
#include "JOptionPane.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "objects.h"
class CallAndWait : public BaseCommand {
public:
{
    public CallAndWait()
    {
        inst = nullptr;
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr)
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        } else
        {
            position = object;
            return;
        }
    }
    public void begin()
    {
        if(module.RandomSelectorMap.containsKey(position))
        {
            inst = ((RandomSelector)module.RandomSelectorMap.get(position)).Process(currentinstance);
        } else
        {
            inst = module.PlayScript(position, currentinstance);
            check = position;
        }
    }
    public bool IsFinished()
    {
        return !ScriptManager.instance.IsScriptPlaying(inst);
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return false;
    }
    std::string position;
    std::string check;
    zombie.scripting.objects.Script.ScriptInstance inst;
}
} // namespace
