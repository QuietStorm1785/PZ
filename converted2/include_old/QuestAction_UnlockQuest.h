#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestAction_UnlockQuest.java
namespace zombie {
namespace Quests {
namespace questactions {
#include "Quest.h"
#include "QuestManager.h"
// Referenced classes of package zombie.Quests.questactions:
//            QuestAction
class QuestAction_UnlockQuest {
public:
    implements QuestAction
{
    public QuestAction_UnlockQuest(std::string questInternal)
    {
        Quest = questInternal;
    }
    public void Execute()
    {
        Quest quest = QuestManager.instance.FindQuest(Quest);
        if(quest == nullptr)
        {
            return;
        } else
        {
            quest.Unlocked = true;
            return;
        }
    }
    std::string Quest;
}
} // namespace
