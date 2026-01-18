#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UnlockTaskOnComplete.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "QuestCreator.h"
#include "BaseCommand.h"
class UnlockTaskOnComplete : public BaseCommand {
public:
{
    public UnlockTaskOnComplete()
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
        QuestCreator.AddQuestAction_UnlockQuestTask(script);
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
