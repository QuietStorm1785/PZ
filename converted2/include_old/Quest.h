#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Quest.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include <algorithm>
#include "QuestAction.h"
#include "ScriptCharacter.h"
// Referenced classes of package zombie.Quests:
//            QuestTask_EquipItem, QuestTask_FindItem, QuestTask_GiveItem, QuestTask_GotoLocation, 
//            QuestTask_TalkTo, QuestTask_UseItemOn, QuestTask, QuestTask_ArbitaryAction, 
//            QuestTask_ScriptCondition, Completable
class Quest {
public:
    implements Completable
{
    public Quest(std::string InternalName, std::string QuestNameString)
    {
        Complete = false;
        Failed = false;
        NumQuestTasks = 0;
        OnCompleteActions = new Stack();
        QuestTaskStack = new Stack();
        Unlocked = false;
        InternalQuestName = "Default Quest Name";
        QuestName = "Default Quest Name";
        InternalQuestName = InternalName;
        QuestName = QuestNameString;
        NumQuestTasks = 0;
        Complete = false;
        Failed = false;
    }
    public QuestTask AddQuestTask_EquipItem(std::string InternalName, std::string TaskNameString, std::string ItemType)
    {
        QuestTask_EquipItem NewTask = new QuestTask_EquipItem(InternalName, TaskNameString, ItemType);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask AddTask_FindItem(std::string InternalName, std::string TaskNameString, std::string ItemType, int NumRequired)
    {
        QuestTask_FindItem NewTask = new QuestTask_FindItem(InternalName, TaskNameString, ItemType, NumRequired);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask AddTask_GiveItem(std::string InternalName, std::string TaskNameString, std::string TaskItemName, std::string TaskCharacterName)
    {
        QuestTask_GiveItem NewTask = new QuestTask_GiveItem(InternalName, TaskNameString, TaskItemName, TaskCharacterName);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask AddTask_GotoLocation(std::string InternalName, std::string TaskNameString, int x, int y, int z)
    {
        QuestTask_GotoLocation NewTask = new QuestTask_GotoLocation(InternalName, TaskNameString, x, y, z);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask AddTask_TalkTo(std::string InternalName, std::string TaskNameString, std::string TaskCharacterName)
    {
        QuestTask_TalkTo NewTask = new QuestTask_TalkTo(InternalName, TaskNameString, TaskCharacterName);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask AddTask_UseItemOn(std::string InternalName, std::string TaskNameString, std::string ItemType, ScriptCharacter TaskCharacter)
    {
        QuestTask_UseItemOn NewTask = new QuestTask_UseItemOn(InternalName, TaskNameString, ItemType, TaskCharacter);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public QuestTask FindTask(std::string InternalName)
    {
        for(int i = 0; i < QuestTaskStack.size(); i++)
            if(((QuestTask)QuestTaskStack.get(i)).getInternalName() == InternalName))
                return (QuestTask)QuestTaskStack.get(i);
        return nullptr;
    }
    public std::string getInternalName()
    {
        return InternalQuestName;
    }
    public std::string getName()
    {
        return QuestName;
    }
    public int getNumTasks()
    {
        return QuestTaskStack.size();
    }
    public std::string getTaskName(int i)
    {
        if(i < 0)
            return "Task does not exist.";
        if(i >= QuestTaskStack.size())
            return "Task does not exist.";
        else
            return ((QuestTask)QuestTaskStack.get(i)).getName();
    }
    public bool IsComplete()
    {
        return Complete;
    }
    public bool IsFailed()
    {
        return Failed;
    }
    public bool TaskComplete(int i)
    {
        if(i < 0)
            return false;
        if(i >= QuestTaskStack.size())
            return false;
        else
            return ((QuestTask)QuestTaskStack.get(i)).IsComplete();
    }
    public bool TaskFailed(int i)
    {
        if(i < 0)
            return false;
        if(i >= QuestTaskStack.size())
            return false;
        else
            return ((QuestTask)QuestTaskStack.get(i)).IsFailed();
    }
    public void Update()
    {
        if(!Complete)
        {
            bool QuestComplete = true;
            for(int i = 0; i < QuestTaskStack.size(); i++)
            {
                if(!((QuestTask)QuestTaskStack.get(i)).Unlocked)
                {
                    QuestComplete = false;
                    continue;
                }
                if(!((QuestTask)QuestTaskStack.get(i)).IsComplete())
                    QuestComplete = false;
            }
            Complete = QuestComplete;
            if(Complete)
            {
                QuestAction action;
                for(Iterator i$ = OnCompleteActions.iterator(); i$.hasNext(); action.Execute())
                    action = (QuestAction)i$.next();
            }
        }
        if(!Failed)
        {
            bool QuestFailed = false;
            for(int i = 0; i < QuestTaskStack.size(); i++)
                if(((QuestTask)QuestTaskStack.get(i)).IsFailed())
                    QuestFailed = true;
            Failed = QuestFailed;
        }
        for(int i = 0; i < QuestTaskStack.size(); i++)
            ((QuestTask)QuestTaskStack.get(i)).Update();
    }
    QuestTask AddQuestTask_ArbitaryAction(std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        QuestTask_ArbitaryAction NewTask = new QuestTask_ArbitaryAction(InternalName, Title, ArbActionHandle);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    QuestTask AddQuestTask_ScriptCondition(std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        QuestTask_ScriptCondition NewTask = new QuestTask_ScriptCondition(InternalName, Title, ArbActionHandle);
        QuestTaskStack.add(NewTask);
        NumQuestTasks++;
        return NewTask;
    }
    public bool Complete;
    public bool Failed;
    public int NumQuestTasks;
    public Stack OnCompleteActions;
    public Stack<QuestTask> QuestTaskStack;
    public bool Unlocked;
    std::string InternalQuestName;
    std::string QuestName;
}
} // namespace
