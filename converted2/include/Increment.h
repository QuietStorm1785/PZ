#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Increment.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Flags {
#include "BaseCommand.h"
#include "ScriptFlag.h"
#include "ScriptModule.h"
class Increment : public BaseCommand {
public:
{
    public Increment()
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
            val = module.getFlagValue(name);
            Integer ival = Integer.valueOf(Integer.parseInt(val));
            Integer integer = ival;
            Integer integer1 = ival = Integer.valueOf(ival.intValue() + 1);
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
