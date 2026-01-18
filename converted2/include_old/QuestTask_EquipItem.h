#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_EquipItem.java
namespace zombie {
namespace Quests {
#include "IsoPlayer.h"
#include "InventoryItem.h"
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_EquipItem : public QuestTask {
public:
{
    public QuestTask_EquipItem(std::string InternalName, std::string TaskNameString, std::string ItemType)
    {
        super(QuestTaskType.FindItem, InternalName, TaskNameString);
        QuestItemType = ItemType;
    }
    public void Update()
    {
        if(!Complete && IsoPlayer.getInstance().getPrimaryHandItem() != nullptr && IsoPlayer.getInstance().getPrimaryHandItem().getType() == QuestItemType))
        {
            Complete = true;
            if(UIManager.getOnscreenQuest() != nullptr)
                UIManager.getOnscreenQuest().TriggerQuestWiggle();
        }
        super.Update();
    }
    std::string QuestItemType;
}
} // namespace
