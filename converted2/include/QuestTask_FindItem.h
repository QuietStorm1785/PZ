#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_FindItem.java
namespace zombie {
namespace Quests {
#include "IsoPlayer.h"
#include "NulledArrayList.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_FindItem : public QuestTask {
public:
{
    public QuestTask_FindItem(std::string InternalName, std::string TaskNameString, std::string ItemType, int NumRequired)
    {
        super(QuestTaskType.FindItem, InternalName, TaskNameString);
        QuestItemType = ItemType;
        QuestItemRequiredAmmount = NumRequired;
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
            int NumItemsGathered = 0;
            for(int i = 0; i < IsoPlayer.getInstance().getInventory().Items.size(); i++)
                if(((InventoryItem)IsoPlayer.getInstance().getInventory().Items.get(i)).getType() == QuestItemType))
                    NumItemsGathered += ((InventoryItem)IsoPlayer.getInstance().getInventory().Items.get(i)).getUses();
            if(NumItemsGathered >= QuestItemRequiredAmmount)
            {
                Complete = true;
                if(UIManager.getOnscreenQuest() != nullptr)
                    UIManager.getOnscreenQuest().TriggerQuestWiggle();
            }
        }
        super.Update();
    }
    int QuestItemRequiredAmmount;
    std::string QuestItemType;
}
} // namespace
