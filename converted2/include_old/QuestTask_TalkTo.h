#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_TalkTo.java
namespace zombie {
namespace Quests {
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_TalkTo : public QuestTask {
public:
{
    public QuestTask_TalkTo(std::string InternalName, std::string TaskNameString, std::string TaskCharacterName)
    {
        super(QuestTaskType.TalkTo, InternalName, TaskNameString);
        CharacterName = TaskCharacterName;
    }
    public void Update()
    {
        if(!Unlocked)
        {
            Complete = false;
            return;
        }
        if(!Complete)
        {
            Complete = true;
            if(UIManager.getOnscreenQuest() != nullptr)
                UIManager.getOnscreenQuest().TriggerQuestWiggle();
        }
        if(!Failed)
        {
            Failed = true;
            if(UIManager.getOnscreenQuest() != nullptr)
                UIManager.getOnscreenQuest().TriggerQuestWiggle();
        }
        super.Update();
    }
    std::string CharacterName;
}
} // namespace
