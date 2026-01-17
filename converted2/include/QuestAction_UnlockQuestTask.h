#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestAction_UnlockQuestTask.java
namespace zombie {
namespace Quests {
namespace questactions {
#include "Quest.h"
#include "QuestTask.h"
// Referenced classes of package zombie.Quests.questactions:
//            QuestAction
class QuestAction_UnlockQuestTask {
public:
    implements QuestAction
{
    public QuestAction_UnlockQuestTask(Quest quest, std::string taskInternal)
    {
        Task = taskInternal;
        Quest = quest;
    }
    public void Execute()
    {
        QuestTask task = Quest.FindTask(Task);
        task.Unlocked = true;
    }
    Quest Quest;
    std::string Task;
}
} // namespace
