#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Pause.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "JOptionPane.h"
#include "ScriptManager.h"
#include "BaseCommand.h"
class Pause : public BaseCommand {
public:
{
    public Pause()
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
        ScriptManager.instance.PauseScript(position);
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
