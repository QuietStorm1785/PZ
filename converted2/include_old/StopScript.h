#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopScript.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Script {
#include "ScriptManager.h"
#include "BaseCommand.h"
#include "Conditional.h"
#include "Script.h"
class StopScript : public BaseCommand {
public:
{
    public StopScript()
    {
    }
    public void init(std::string object, std::string params[])
    {
        position = object;
    }
    public void begin()
    {
        if(position == nullptr)
        {
            zombie.scripting.objects.Script.ScriptInstance parent;
            for(parent = currentinstance; parent.parent != nullptr && (parent.theScript instanceof Conditional); parent = parent.parent);
            ScriptManager.instance.StopScript(parent);
        } else
        {
            ScriptManager.instance.StopScript(position);
        }
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
