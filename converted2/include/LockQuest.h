#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LockQuest.java
namespace zombie {
namespace scripting {
namespace commands {
namespace quest {
#include "Quest.h"
#include "QuestManager.h"
#include "BaseCommand.h"
#include "QuestPanel.h"
class LockQuest : public BaseCommand {
public:
{
    public LockQuest()
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
            return;
        questa.Unlocked = false;
        if(QuestPanel.instance.ActiveQuest == questa)
            QuestPanel.instance.ActiveQuest = nullptr;
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
