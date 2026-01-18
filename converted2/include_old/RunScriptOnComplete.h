#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RunScriptOnComplete.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "QuestCreator.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class RunScriptOnComplete : public BaseCommand {
public:
{
    public RunScriptOnComplete()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Quest"))
        {
            return;
        } else
        {
            script = params[0].trim().replace("\"", "");
            return;
        }
    }
    public void begin()
    {
        if(script.contains("."))
            QuestCreator.AddQuestAction_RunScript(script);
        else
            QuestCreator.AddQuestAction_RunScript((new StringBuilder()).append(module.name).append(".").append(script).toString());
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
    std::string script;
}
} // namespace
