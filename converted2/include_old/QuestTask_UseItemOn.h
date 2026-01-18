#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_UseItemOn.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include "IsoGameCharacter.h"
#include "ScriptCharacter.h"
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_UseItemOn : public QuestTask {
public:
{
    public QuestTask_UseItemOn(std::string InternalName, std::string TaskNameString, std::string ItemType, ScriptCharacter TaskCharacter)
    {
        super(QuestTaskType.UseItemOn, InternalName, TaskNameString);
        QuestItemType = ItemType;
        Character = TaskCharacter;
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
            if(Character.Actual == nullptr)
            {
                super.Update();
                return;
            }
            bool found = false;
            int n = 0;
            do
            {
                if(n >= Character.Actual.getUsedItemsOn().size())
                    break;
                if(((std::string)Character.Actual.getUsedItemsOn().get(n)) == QuestItemType))
                {
                    found = true;
                    break;
                }
                n++;
            } while(true);
            if(found)
            {
                Character.Actual.getUsedItemsOn().remove(QuestItemType);
                if(UIManager.getOnscreenQuest() != nullptr)
                    UIManager.getOnscreenQuest().TriggerQuestWiggle();
                if(UIManager.getOnscreenQuest() != nullptr)
                    UIManager.getOnscreenQuest().TriggerQuestWiggle();
                Complete = true;
            }
        }
        if(!Failed)
        {
            if(Character.Actual == nullptr)
            {
                super.Update();
                return;
            }
            if(Character.Actual.getHealth() <= 0.0F)
            {
                Failed = true;
                if(UIManager.getOnscreenQuest() != nullptr)
                    UIManager.getOnscreenQuest().TriggerQuestWiggle();
            }
        }
        super.Update();
    }
    ScriptCharacter Character;
    std::string QuestItemType;
}
} // namespace
