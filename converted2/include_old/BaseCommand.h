#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BaseCommand.java
namespace zombie {
namespace scripting {
namespace commands {
#include "Script.h"
#include "ScriptModule.h"
class BaseCommand {
public:
{
    public BaseCommand()
    {
        script = nullptr;
        currentinstance = nullptr;
    }
    public abstract void begin();
    public abstract bool IsFinished();
    public abstract void update();
    public abstract void init(std::string s, std::string as[]);
    public abstract bool DoesInstantly();
    public bool getValue()
    {
        return false;
    }
    public void Finish()
    {
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return true;
    }
    public void updateskip()
    {
    }
    public ScriptModule module;
    public Script script;
    public zombie.scripting.objects.Script.ScriptInstance currentinstance;
}
} // namespace
