#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_GotoLocation.java
namespace zombie {
namespace Quests {
#include "IsoPlayer.h"
#include "iso.h"
#include "QuestHUD.h"
#include "UIManager.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_GotoLocation : public QuestTask {
public:
{
    public QuestTask_GotoLocation(std::string InternalName, std::string TaskNameString, int x, int y, int z)
    {
        super(QuestTaskType.GotoLocation, InternalName, TaskNameString);
        Task_x = x;
        Task_y = y;
        Task_z = z;
    }
    public void Update()
    {
        if(!Unlocked)
        {
            Complete = false;
            return;
        }
        if(!Complete && IsoPlayer.getInstance().getCurrentSquare().getX() > Task_x - 2 && IsoPlayer.getInstance().getCurrentSquare().getX() < Task_x + 2 && IsoPlayer.getInstance().getCurrentSquare().getY() > Task_y - 2 && IsoPlayer.getInstance().getCurrentSquare().getY() < Task_y + 2 && IsoPlayer.getInstance().getCurrentSquare().getZ() == Task_z && IsoPlayer.getInstance().getCurrentSquare().getRoom() == IsoWorld.instance.CurrentCell.getGridSquare(Task_x, Task_y, Task_z).getRoom())
        {
            Complete = true;
            if(UIManager.getOnscreenQuest() != nullptr)
                UIManager.getOnscreenQuest().TriggerQuestWiggle();
        }
        super.Update();
    }
    int Task_x;
    int Task_y;
    int Task_z;
}
} // namespace
