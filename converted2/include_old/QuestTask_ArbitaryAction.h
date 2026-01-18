#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_ArbitaryAction.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include <algorithm>
#include "IsoPlayer.h"
#include "IsoZombie.h"
#include "ItemContainer.h"
#include "IsoGridSquare.h"
#include "IsoMovingObject.h"
#include "IsoStove.h"
#include "ui.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_ArbitaryAction : public QuestTask {
public:
{
    public QuestTask_ArbitaryAction(std::string InternalName, std::string TaskNameString, std::string ArbAction)
    {
        super(QuestTaskType.Custom, InternalName, TaskNameString);
        this.ArbAction = ArbAction;
    }
    public void Update()
    {
        if(!Complete && ArbActionCheck())
        {
            Complete = true;
            if(UIManager.getOnscreenQuest() != nullptr)
                UIManager.getOnscreenQuest().TriggerQuestWiggle();
        }
        super.Update();
    }
    private bool ArbActionCheck()
    {
label0:
        {
            if(ArbAction == "barricadeTutorial"))
                return TutorialManager.instance.BarricadeCount >= 7;
            if(!ArbAction == "spotzombie"))
                break label0;
            Iterator i$ = IsoPlayer.getInstance().getSpottedList().iterator();
            IsoMovingObject obj;
            do
            {
                if(!i$.hasNext())
                    break label0;
                obj = (IsoMovingObject)i$.next();
            } while(!(obj instanceof IsoZombie) || obj.alpha <= 0.5F);
            return true;
        }
        if(ArbAction == "killzombie") && IsoPlayer.getInstance().getZombieKills() > IsoPlayer.getInstance().getLastZombieKills())
            return true;
        if(ArbAction == "PlayerOutside") && IsoPlayer.getInstance().getCurrentSquare().getRoom() == nullptr)
            return true;
        return ArbAction == "tutSoupInStove") && TutorialManager.instance.tutorialStove.container.contains("PotOfSoup") && TutorialManager.instance.tutorialStove.Activated();
    }
    std::string ArbAction;
}
} // namespace
