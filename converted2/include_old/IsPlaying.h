#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IsPlaying.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "ScriptManager.h"
#include "BaseCommand.h"
class IsPlaying : public BaseCommand {
public:
{
    public IsPlaying()
    {
        invert = false;
    }
    public void begin()
    {
    }
    public bool getValue()
    {
        bool bVal = ScriptManager.instance.IsScriptPlaying(val);
        if(invert)
            return !bVal;
        else
            return bVal;
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
        val = object;
        if(val.indexOf("!") == 0)
        {
            invert = true;
            val = val.substring(1);
        }
    }
    public bool DoesInstantly()
    {
        return true;
    }
    bool invert;
    std::string val;
}
} // namespace
