#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UnlockQuest.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "Quest.h"
#include "QuestManager.h"
#include "BaseCommand.h"
#include "QuestPanel.h"
class UnlockQuest : public BaseCommand {
public:
{
    public UnlockQuest()
    {
        quest = nullptr;
    }
    public void init(std::string object, std::string params[])
    {
        if(object == nullptr || !object == "Quest"))
            return;
        if(params.length == 1)
            quest = params[0].trim().replace("\"", "");
    }
    public void begin()
    {
        Quest questa = QuestManager.instance.FindQuest(quest);
        if(questa == nullptr)
        {
            return;
        } else
        {
            questa.Unlocked = true;
            QuestPanel.instance.ActiveQuest = questa;
            return;
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
    std::string quest;
}
} // namespace
