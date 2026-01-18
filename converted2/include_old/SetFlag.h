#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   SetFlag.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Flags {
#include "BaseCommand.h"
#include "ScriptFlag.h"
#include "ScriptModule.h"
class SetFlag : public BaseCommand {
public:
{
    public SetFlag()
    {
    }
    public void init(std::string object, std::string params[])
    {
        name = object.trim().replace("\"", "");
        val = params[0].trim().replace("\"", "");
    }
    public void begin()
    {
        ScriptFlag vala;
        vala = module.getFlag(name);
        if(vala == nullptr)
            return;
        try
        {
            vala.SetValue(val);
        }
        catch(Exception ex)
        {
            ex = ex;
        }
        return;
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
