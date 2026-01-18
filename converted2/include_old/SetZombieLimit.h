#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SetZombieLimit.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Tutorial {
#include "JOptionPane.h"
#include "BaseCommand.h"
#include "TutorialManager.h"
class SetZombieLimit : public BaseCommand {
public:
{
    public SetZombieLimit()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Tutorial"))
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append("Command: ").append(getClass().getName()).append(" is not part of ").append(object).toString(), "Error", 0);
            return;
        } else
        {
            limit = Integer.parseInt(params[0].trim().replace("\"", ""));
            return;
        }
    }
    public void begin()
    {
        TutorialManager.instance.TargetZombies = limit;
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
    int limit;
}
} // namespace
