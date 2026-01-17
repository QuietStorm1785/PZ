#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Decrement.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Flags {
#include "BaseCommand.h"
#include "ScriptFlag.h"
#include "ScriptModule.h"
class Decrement : public BaseCommand {
public:
{
    public Decrement()
    {
    }
    public void init(std::string object, std::string params[])
    {
        name = object.trim().replace("\"", "");
    }
    public void begin()
    {
        try
        {
            Integer ival = Integer.valueOf(Integer.parseInt(module.getFlagValue(name)));
            Integer integer = ival;
            Integer integer1 = ival = Integer.valueOf(ival.intValue() - 1);
            Integer _tmp = integer;
            module.getFlag(name).SetValue(ival.toString());
        }
        catch(Exception ex) { }
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
    std::string name;
    std::string val;
}
} // namespace
