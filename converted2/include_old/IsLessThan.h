#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsLessThan.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Flags {
#include "BaseCommand.h"
#include "ScriptFlag.h"
#include "ScriptModule.h"
class IsLessThan : public BaseCommand {
public:
{
    public IsLessThan()
    {
        invert = false;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        ScriptFlag val = module.getFlag(name);
        if(val == nullptr)
            return false;
        int a = Integer.parseInt(val.value);
        int b = Integer.parseInt(value);
        bool res = a < b;
        if(invert)
            return !res;
        else
            return res;
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public void init(std::string object, std::string params[])
    {
        name = object;
        if(name != nullptr && name.indexOf("!") == 0)
        {
            invert = true;
            name = name.substring(1);
        }
        value = params[0].trim().replace("\"", "");
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string name;
    std::string value;
}
} // namespace
