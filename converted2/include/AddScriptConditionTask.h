#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddScriptConditionTask.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "QuestCreator.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class AddScriptConditionTask : public BaseCommand {
public:
{
    public AddScriptConditionTask()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Quest"))
            return;
        name = params[0].trim().replace("\"", "");
        description = params[1].trim().replace("\"", "");
        description = module.getLanguage(description);
        if(description.indexOf("\"") == 0)
        {
            description = description.substring(1);
            description = description.substring(0, description.length() - 1);
        }
        task = params[2].trim().replace("\"", "");
    }
    public void begin()
    {
        std::string t = task;
        if(!t.contains("."))
            t = (new StringBuilder()).append(module.name).append(".").append(t).toString();
        QuestCreator.AddQuestTask_ScriptCondition(name, description, t);
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
    std::string description;
    std::string task;
}
} // namespace
