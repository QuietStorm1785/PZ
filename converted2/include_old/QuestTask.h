#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestTask.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include <algorithm>
#include "QuestAction.h"
// Referenced classes of package zombie.Quests:
//            Completable, QuestTaskType
class QuestTask {
public:
    implements Completable
{
    public QuestTask(QuestTaskType TaskType, std::string InternalName, std::string TaskNameString)
    {
        Hidden = false;
        OnCompleteActions = new Stack();
        Unlocked = false;
        InternalTaskName = "Default Task Name";
        TaskName = "Default Task Name";
        InternalTaskName = InternalName;
        this.TaskType = TaskType;
        TaskName = TaskNameString;
        Complete = false;
        Failed = false;
        WasComplete = false;
    }
    public std::string getInternalName()
    {
        return InternalTaskName;
    }
    public std::string getName()
    {
        return TaskName;
    }
    public bool IsComplete()
    {
        return Complete;
    }
    public bool IsFailed()
    {
        return Failed;
    }
    public void Update()
    {
        if(Complete && !WasComplete)
        {
            QuestAction action;
            for(Iterator i$ = OnCompleteActions.iterator(); i$.hasNext(); action.Execute())
                action = (QuestAction)i$.next();
        }
        WasComplete = Complete;
    }
    public bool Complete;
    public bool Failed;
    public bool Hidden;
    public Stack OnCompleteActions;
    public QuestTaskType TaskType;
    public bool Unlocked;
    public bool WasComplete;
    std::string InternalTaskName;
    std::string TaskName;
}
} // namespace
