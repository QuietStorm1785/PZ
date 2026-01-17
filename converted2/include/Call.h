#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Call.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "THashMap.h"
#include "JOptionPane.h"
#include "BaseCommand.h"
#include "objects.h"
class Call : public BaseCommand {
public:
{
    public Call()
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
            position = object;
            return;
        }
    }
    public void begin()
    {
        if(module.RandomSelectorMap.containsKey(position))
            ((RandomSelector)module.RandomSelectorMap.get(position)).Process(currentinstance);
        else
            module.PlayScript(position, currentinstance);
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
