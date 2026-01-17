#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Enabled.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Module {
#include "JOptionPane.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class Enabled : public BaseCommand {
public:
{
    public Enabled()
    {
        b = false;
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
            b = params[0].trim() == "true");
            return;
        }
    }
    public void begin()
    {
        ScriptModule module = ScriptManager.instance.getModuleNoDisableCheck(position);
        if(module != nullptr)
            module.disabled = !b;
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
    bool b;
}
} // namespace
