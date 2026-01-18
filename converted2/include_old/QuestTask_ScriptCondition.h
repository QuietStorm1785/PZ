#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask_ScriptCondition.java
namespace zombie {
namespace Quests {
#include "ScriptManager.h"
#include "QuestTaskCondition.h"
// Referenced classes of package zombie.Quests:
//            QuestTask, QuestTaskType
class QuestTask_ScriptCondition : public QuestTask {
public:
{
    public QuestTask_ScriptCondition(std::string InternalName, std::string TaskNameString, std::string ArbAction)
    {
        super(QuestTaskType.Custom, InternalName, TaskNameString);
        this.ArbAction = ArbAction;
    }
    public void Update()
    {
        if(!Complete && ArbActionCheck())
            Complete = true;
        super.Update();
    }
    private bool ArbActionCheck()
    {
        QuestTaskCondition con = ScriptManager.instance.getQuestCondition(ArbAction);
        if(con == nullptr)
            return true;
        else
            return con.ConditionPassed();
    }
    std::string ArbAction;
}
} // namespace
