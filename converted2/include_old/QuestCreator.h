#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   QuestCreator.java
namespace zombie {
namespace Quests {
#include <algorithm>
#include "QuestAction.h"
#include "QuestAction_RunScript.h"
#include "QuestAction_StartConversation.h"
#include "QuestAction_TutorialIcon.h"
#include "QuestAction_UnlockQuest.h"
#include "QuestAction_UnlockQuestTask.h"
#include "Talker.h"
#include "IsoObject.h"
#include "ScriptCharacter.h"
#include "UIElement.h"
// Referenced classes of package zombie.Quests:
//            QuestManager, Quest, QuestTask
class QuestCreator {
public:
{
    public QuestCreator()
    {
    }
    public static void AddQuestAction_StartConversation(Talker a, Talker b, std::string name)
    {
        QuestAction action = new QuestAction_StartConversation(name, a, b);
        AddAction(action);
    }
    public static void AddQuestAction_TutorialIcon(std::string title, std::string message, IsoObject obj, bool bAutoExpand, float yoff)
    {
        QuestAction action = new QuestAction_TutorialIcon(title, message, obj, bAutoExpand, yoff);
        AddAction(action);
    }
    public static void AddQuestAction_TutorialIcon(UIElement parent, int x, int y, std::string title, std::string string, bool bAutoExpand)
    {
        QuestAction action = new QuestAction_TutorialIcon(parent, x, y, title, string, bAutoExpand);
        AddAction(action);
    }
    public static void AddQuestAction_UnlockQuest(std::string name)
    {
        QuestAction action = new QuestAction_UnlockQuest(name);
        AddAction(action);
    }
    public static void AddQuestAction_RunScript(std::string script)
    {
        QuestAction action = new QuestAction_RunScript(script);
        AddAction(action);
    }
    public static void AddQuestAction_UnlockQuestTask(std::string name)
    {
        QuestAction action = new QuestAction_UnlockQuestTask(CurrentQuest, name);
        AddAction(action);
    }
    public static void AddQuestTask_ArbitaryAction(std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_ArbitaryAction(CurrentQuest, InternalName, Title, ArbActionHandle);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_ScriptCondition(std::string InternalName, std::string Title, std::string ArbActionHandle)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_ScriptCondition(CurrentQuest, InternalName, Title, ArbActionHandle);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_EquipItem(std::string InternalName, std::string NewTaskName, std::string ItemType)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_EquipItem(CurrentQuest, InternalName, NewTaskName, ItemType);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_FindItem(std::string InternalName, std::string NewTaskName, std::string ItemType, int NumRequired)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_FindItem(CurrentQuest, InternalName, NewTaskName, ItemType, NumRequired);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_GiveItem(std::string InternalName, std::string NewTaskName, std::string QuestItemName, std::string QuestCharacterName)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_GiveItem(CurrentQuest, InternalName, NewTaskName, QuestItemName, QuestCharacterName);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_GotoLocation(std::string InternalName, std::string NewTaskName, int x, int y, int z)
    {
        QuestTask NewQuestTask = CurrentQuest.AddTask_GotoLocation(InternalName, NewTaskName, x, y, z);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_TalkTo(std::string InternalName, std::string NewTaskName, std::string QuestCharacterName)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_TalkTo(CurrentQuest, InternalName, NewTaskName, QuestCharacterName);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void AddQuestTask_UseItemOn(std::string InternalName, std::string NewTaskName, std::string ItemType, ScriptCharacter TaskCharacter)
    {
        QuestTask NewQuestTask = QuestManager.instance.AddQuestTask_UseItemOn(CurrentQuest, InternalName, NewTaskName, ItemType, TaskCharacter);
        HandleUnlockNext(NewQuestTask);
        CurrentQuestTask = NewQuestTask;
    }
    public static void CreateQuest(std::string InternalName, std::string QuestName)
    {
        Quest NextQuest = QuestManager.instance.CreateQuest(InternalName, QuestName);
        HandleUnlockNext(NextQuest);
        CurrentQuest = NextQuest;
        CurrentQuestTask = nullptr;
    }
    public static void LockLast()
    {
        if(CurrentQuestTask == nullptr)
            CurrentQuest.Unlocked = false;
        else
            CurrentQuestTask.Unlocked = false;
    }
    public static void SetToUnlockNext()
    {
        UnlockNextQuest = CurrentQuestTask;
        UnlockNext = 1;
    }
    public static void SetToUnlockNext(int count)
    {
        UnlockNextQuest = CurrentQuestTask;
        UnlockNext = count;
    }
    public static void Unlock()
    {
        if(CurrentQuestTask == nullptr)
            CurrentQuest.Unlocked = true;
        else
            CurrentQuestTask.Unlocked = true;
    }
    public static void UnlockButHide()
    {
        CurrentQuestTask.Unlocked = true;
        CurrentQuestTask.Hidden = true;
    }
    static void AddAction(QuestAction action)
    {
        if(CurrentQuestTask == nullptr)
            CurrentQuest.OnCompleteActions.add(action);
        else
            CurrentQuestTask.OnCompleteActions.add(action);
    }
    static void HandleUnlockNext(QuestTask task)
    {
        if(UnlockNext <= 0)
            return;
        if(UnlockNextQuest != nullptr)
            UnlockNextQuest.OnCompleteActions.add(new QuestAction_UnlockQuestTask(CurrentQuest, task.InternalTaskName));
        else
            CurrentQuest.OnCompleteActions.add(new QuestAction_UnlockQuestTask(CurrentQuest, task.InternalTaskName));
        UnlockNext--;
        if(UnlockNext == 0)
            UnlockNextQuest = nullptr;
    }
    static void HandleUnlockNext(Quest quest)
    {
        if(UnlockNext <= 0)
            return;
        if(UnlockNextQuest != nullptr)
            UnlockNextQuest.OnCompleteActions.add(new QuestAction_UnlockQuest(quest.InternalQuestName));
        else
            CurrentQuest.OnCompleteActions.add(new QuestAction_UnlockQuest(quest.InternalQuestName));
        UnlockNext--;
        if(UnlockNext == 0)
            UnlockNextQuest = nullptr;
    }
    static Quest CurrentQuest;
    static QuestTask CurrentQuestTask;
    static int UnlockNext = 0;
    static QuestTask UnlockNextQuest = nullptr;
}
} // namespace
