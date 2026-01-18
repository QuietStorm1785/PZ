#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LockHud.java
namespace zombie {
namespace scripting {
namespace commands {
#include "ScriptManager.h"
#include "TutorialManager.h"
// Referenced classes of package zombie.scripting.commands:
//            BaseCommand
class LockHud : public BaseCommand {
public:
{
    public LockHud()
    {
        doIt = false;
    }
    public void init(std::string object, std::string params[])
    {
        if(params.length == 1)
            doIt = params[0].trim().equalsIgnoreCase("true");
    }
    public void begin()
    {
        TutorialManager.instance.StealControl = doIt;
        if(!doIt)
            ScriptManager.instance.skipping = false;
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
    bool doIt;
}
} // namespace
