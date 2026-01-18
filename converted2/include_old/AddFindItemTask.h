#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AddFindItemTask.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "QuestCreator.h"
#include "BaseCommand.h"
#include "ScriptModule.h"
class AddFindItemTask : public BaseCommand {
public:
{
    public AddFindItemTask()
    {
        num = 1;
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
        item = params[2].trim().replace("\"", "");
        num = Integer.parseInt(params[3].trim());
    }
    public void begin()
    {
        QuestCreator.AddQuestTask_FindItem(name, description, item, num);
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
    std::string item;
    int num;
}
} // namespace
