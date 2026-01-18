#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RegisterOneTime.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Hook {
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class RegisterOneTime : public BaseCommand {
public:
{
    public RegisterOneTime()
    {
        num = 1;
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Hook"))
        {
            return;
        } else
        {
            event = params[0].trim().replace("\"", "");
            script = params[1].trim().replace("\"", "");
            return;
        }
    }
    public void begin()
    {
        std::string str = script;
        if(!str.contains("."))
            str = (new StringBuilder()).append(module.name).append(".").append(str).toString();
        ScriptManager.instance.AddOneTime(event, str);
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
    std::string event;
    std::string script;
    int num;
}
} // namespace
