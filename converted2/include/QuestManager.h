#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestManager.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include <algorithm>
#include "ScriptCharacter.h"
// Referenced classes of package zombie.Quests:
//            Quest, QuestTask
class QuestManager {
public:
{
    public QuestManager()
    {
        NumActiveQuests = 0;
        QuestStack = new Stack();
    }
    public QuestTask AddQuestTask_ArbitaryAction(Quest CurrentQuest, std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        LastAddedQuestTask = CurrentQuest.AddQuestTask_ArbitaryAction(InternalName, Title, ArbActionHandle);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_ScriptCondition(Quest CurrentQuest, std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        LastAddedQuestTask = CurrentQuest.AddQuestTask_ScriptCondition(InternalName, Title, ArbActionHandle);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_EquipItem(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, std::string ItemType)
    {
        LastAddedQuestTask = CurrentQuest.AddQuestTask_EquipItem(InternalName, NewTaskName, ItemType);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_FindItem(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, std::string ItemType, int NumRequired)
    {
        LastAddedQuestTask = CurrentQuest.AddTask_FindItem(InternalName, NewTaskName, ItemType, NumRequired);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_GiveItem(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, std::string QuestItemName, std::string QuestCharacterName)
    {
        LastAddedQuestTask = CurrentQuest.AddTask_GiveItem(InternalName, NewTaskName, QuestItemName, QuestCharacterName);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_GotoLocation(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, int x, int y, int z)
    {
        LastAddedQuestTask = CurrentQuest.AddTask_GotoLocation(InternalName, NewTaskName, x, y, z);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_TalkTo(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, std::string QuestCharacterName)
    {
        LastAddedQuestTask = CurrentQuest.AddTask_TalkTo(InternalName, NewTaskName, QuestCharacterName);
        return LastAddedQuestTask;
    }
    public QuestTask AddQuestTask_UseItemOn(Quest CurrentQuest, std::string InternalName, std::string NewTaskName, std::string ItemType, ScriptCharacter TaskCharacter)
    {
        LastAddedQuestTask = CurrentQuest.AddTask_UseItemOn(InternalName, NewTaskName, ItemType, TaskCharacter);
        return LastAddedQuestTask;
    }
    public Quest CreateQuest(std::string InternalName, std::string QuestName)
    {
        Quest NewQuest = new Quest(InternalName, QuestName);
        QuestStack.add(NewQuest);
        NumActiveQuests++;
        return NewQuest;
    }
    public Quest FindQuest(std::string InternalName)
    {
        for(Iterator i$ = QuestStack.iterator(); i$.hasNext();)
        {
            Quest q = (Quest)i$.next();
            if(q.getInternalName().trim().equalsIgnoreCase(InternalName))
                return q;
        }
        return nullptr;
    }
    public int getNumQuests()
    {
        return NumActiveQuests;
    }
    public Quest getQuest(int i)
    {
        if(i < 0)
            return nullptr;
        if(i >= QuestStack.size())
            return nullptr;
        else
            return (Quest)QuestStack.get(i);
    }
    public std::string getQuestName(int i)
    {
        if(i < 0)
            return nullptr;
        if(i >= QuestStack.size())
            return nullptr;
        else
            return ((Quest)QuestStack.get(i)).getName();
    }
    public bool QuestComplete(int i)
    {
        if(i < 0)
            return false;
        if(i >= QuestStack.size())
            return false;
        else
            return ((Quest)QuestStack.get(i)).Complete;
    }
    public void Update()
    {
        for(int i = 0; i < QuestStack.size(); i++)
            if(((Quest)QuestStack.get(i)).Unlocked)
                ((Quest)QuestStack.get(i)).Update();
    }
    public static QuestManager instance = new QuestManager();
    public int NumActiveQuests;
    public Stack<Quest> QuestStack;
    QuestTask LastAddedQuestTask;
}
} // namespace
