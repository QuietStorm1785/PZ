#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_GiveItem.java
namespace zombie {
namespace Quests {
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_GiveItem : public QuestTask {
public:
{
    public QuestTask_GiveItem(std::string InternalName, std::string TaskNameString, std::string TaskItemName, std::string TaskCharacterName)
    {
        super(QuestTaskType.GiveItem, InternalName, TaskNameString);
        ItemName = TaskItemName;
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
    std::string ItemName;
}
} // namespace
