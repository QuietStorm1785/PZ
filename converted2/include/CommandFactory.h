#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CommandFactory.java
namespace zombie {
namespace scripting {
namespace commands {
#include "IsActivated.h"
#include "ToggleActivatable.h"
#include "ActualizeCommand.h"
#include "AddEnemy.h"
#include "AddInventory.h"
#include "AddToGroup.h"
#include "AimWhileStationary.h"
#include "AllowBehaviours.h"
#include "AllowConversation.h"
#include "Anger.h"
#include "Attack.h"
#include "Die.h"
#include "EquipItem.h"
#include "Exists.h"
#include "FaceCommand.h"
#include "HasInventory.h"
#include "HasTrait.h"
#include "InRange.h"
#include "IncrementCharacterScriptFlag.h"
#include "IsAggressive.h"
#include "IsAggressivePose.h"
#include "IsCharacterScriptFlagEqualTo.h"
#include "IsCharacterScriptFlagOver.h"
#include "IsDead.h"
#include "IsFriendly.h"
#include "IsInGroup.h"
#include "IsInGroupWith.h"
#include "IsInRoom.h"
#include "IsInside.h"
#include "IsLeaderOfGroup.h"
#include "IsNeutral.h"
#include "IsNumberOfEnemiesOver.h"
#include "IsNumberOfEnemiesUnder.h"
#include "IsNumberOfLocalOver.h"
#include "IsNumberOfLocalUnder.h"
#include "IsNumberOfNeutralOver.h"
#include "IsNumberOfNeutralUnder.h"
#include "IsOnFloor.h"
#include "IsPlayer.h"
#include "IsSpeaking.h"
#include "MetCountIsOver.h"
#include "NamedOrder.h"
#include "Order.h"
#include "PopOrder.h"
#include "RemoveNamedOrder.h"
#include "SayAt.h"
#include "SayCommand.h"
#include "SayIdle.h"
#include "Sleep.h"
#include "StopAction.h"
#include "TestStat.h"
#include "WalkCommand.h"
#include "WalkToLastHeardSound.h"
#include "WalkToLastKnownLocationOf.h"
#include "WalkWithinRangeOf.h"
#include "IsNight.h"
#include "Decrement.h"
#include "Increment.h"
#include "IsFlagValue.h"
#include "IsGreaterThan.h"
#include "IsGreaterThanEqualTo.h"
#include "IsLessThan.h"
#include "IsLessThanEqualTo.h"
#include "SetFlag.h"
#include "RegisterOneTime.h"
#include "Enabled.h"
#include "Call.h"
#include "CallAndWait.h"
#include "CharactersAlreadyInScript.h"
#include "IsPlaying.h"
#include "Pause.h"
#include "Resume.h"
#include "StopScript.h"
#include "IsLastFiredParameter.h"
#include "ProcessAlways.h"
#include "ProcessNever.h"
#include "TimeSinceLastRan.h"
#include "AddHelpIconToUIElement.h"
#include "AddHelpIconToWorld.h"
#include "DisableTutorialZombieControl.h"
#include "SetZombieLimit.h"
#include "CreateZombieSwarm.h"
#include "PlaySoundEffect.h"
#include "PlayWorldSoundEffect.h"
#include "SpawnZombie.h"
#include "StartFire.h"
#include "AddEquipItemTask.h"
#include "AddFindItemTask.h"
#include "AddGotoLocationTask.h"
#include "AddHardCodedTask.h"
#include "AddScriptConditionTask.h"
#include "AddUseItemOnTask.h"
#include "CreateQuest.h"
#include "LockQuest.h"
#include "RunScriptOnComplete.h"
#include "UnlockLast.h"
#include "UnlockLastButHide.h"
#include "UnlockQuest.h"
#include "UnlockTaskOnComplete.h"
#include "UnlockTasksOnComplete.h"
// Referenced classes of package zombie.scripting.commands:
//            SetModuleAlias, StopAllScriptsExceptContaining, StopAllScriptsContaining, StopAllScriptsExcept, 
//            PauseAllScriptsExcept, ResumeAllScriptsExcept, WaitCommand, LockHud, 
//            LoadTexturePage, BaseCommand
class CommandFactory {
public:
{
    public CommandFactory()
    {
    }
    public static BaseCommand CreateCommand(std::string command)
    {
        if(command == "CreateQuest"))
            return new CreateQuest();
        if(command == "SetModuleAlias"))
            return new SetModuleAlias();
        if(command == "SayAt"))
            return new SayAt();
        if(command == "Exists"))
            return new Exists();
        if(command == "TestStat"))
            return new TestStat();
        if(command == "Enabled"))
            return new Enabled();
        if(command == "AddHelpIconToWorld"))
            return new AddHelpIconToWorld();
        if(command == "AddHelpIconToUIElement"))
            return new AddHelpIconToUIElement();
        if(command == "AimWhileStationary"))
            return new AimWhileStationary();
        if(command == "HasTrait"))
            return new HasTrait();
        if(command == "Die"))
            return new Die();
        if(command == "LockQuest"))
            return new LockQuest();
        if(command == "IsDead"))
            return new IsDead();
        if(command == "StopAllScriptsExceptContaining"))
            return new StopAllScriptsExceptContaining();
        if(command == "StopAllScriptsContaining"))
            return new StopAllScriptsContaining();
        if(command == "IsInRoom"))
            return new IsInRoom();
        if(command == "Attack"))
            return new Attack();
        if(command == "InRange"))
            return new InRange();
        if(command == "Increment"))
            return new Increment();
        if(command == "Decrement"))
            return new Decrement();
        if(command == "IsLessThan"))
            return new IsLessThan();
        if(command == "IsLessThanEqualTo"))
            return new IsLessThanEqualTo();
        if(command == "IsGreaterThan"))
            return new IsGreaterThan();
        if(command == "IsGreaterThanEqualTo"))
            return new IsGreaterThanEqualTo();
        if(command == "DisableTutorialZombieControl"))
            return new DisableTutorialZombieControl();
        if(command == "IsAggressivePose"))
            return new IsAggressivePose();
        if(command == "IsAggressive"))
            return new IsAggressive();
        if(command == "IsNeutral"))
            return new IsNeutral();
        if(command == "IsFriendly"))
            return new IsFriendly();
        if(command == "Equip"))
            return new EquipItem();
        if(command == "AllowConversation"))
            return new AllowConversation();
        if(command == "IsNumberOfEnemiesUnder"))
            return new IsNumberOfEnemiesUnder();
        if(command == "IsNumberOfEnemiesOver"))
            return new IsNumberOfEnemiesOver();
        if(command == "IsPlayer"))
            return new IsPlayer();
        if(command == "Order"))
            return new Order();
        if(command == "CharactersAlreadyInScript"))
            return new CharactersAlreadyInScript();
        if(command == "PopOrder"))
            return new PopOrder();
        if(command == "IsLastFiredParameter"))
            return new IsLastFiredParameter();
        if(command == "PlaySoundEffect"))
            return new PlaySoundEffect();
        if(command == "StopScript"))
            return new StopScript();
        if(command == "WalkWithinRangeOf"))
            return new WalkWithinRangeOf();
        if(command == "IsNumberOfLocalUnder"))
            return new IsNumberOfLocalUnder();
        if(command == "IsNumberOfLocalOver"))
            return new IsNumberOfLocalOver();
        if(command == "IsCharacterScriptFlagOver"))
            return new IsCharacterScriptFlagOver();
        if(command == "IsCharacterScriptFlagEqualTo"))
            return new IsCharacterScriptFlagEqualTo();
        if(command == "IncrementCharacterScriptFlag"))
            return new IncrementCharacterScriptFlag();
        if(command == "MetCountIsOver"))
            return new MetCountIsOver();
        if(command == "Anger"))
            return new Anger();
        if(command == "NamedOrder"))
            return new NamedOrder();
        if(command == "RemoveNamedOrder"))
            return new RemoveNamedOrder();
        if(command == "IsNumberOfNeutralUnder"))
            return new IsNumberOfNeutralUnder();
        if(command == "IsNumberOfNeutralOver"))
            return new IsNumberOfNeutralOver();
        if(command == "IsLeaderOfGroup"))
            return new IsLeaderOfGroup();
        if(command == "Call"))
            return new Call();
        if(command == "AllowBehaviours"))
            return new AllowBehaviours();
        if(command == "CallWait"))
            return new CallAndWait();
        if(command == "WalkToLastHeardSound"))
            return new WalkToLastHeardSound();
        if(command == "PlayWorldSound"))
            return new PlayWorldSoundEffect();
        if(command == "IsInside"))
            return new IsInside();
        if(command == "CreateZombieSwarm"))
            return new CreateZombieSwarm();
        if(command == "StartFire"))
            return new StartFire();
        if(command == "TimeSinceLastRan"))
            return new TimeSinceLastRan();
        if(command == "UnlockButHide"))
            return new UnlockLastButHide();
        if(command == "IsPlaying"))
            return new IsPlaying();
        if(command == "IsOnFloor"))
            return new IsOnFloor();
        if(command == "StopAction"))
            return new StopAction();
        if(command == "StopAllScriptsExcept"))
            return new StopAllScriptsExcept();
        if(command == "WalkToLastKnownLocationOf"))
            return new WalkToLastKnownLocationOf();
        if(command == "PauseAllScriptsExcept"))
            return new PauseAllScriptsExcept();
        if(command == "ResumeAllScriptsExcept"))
            return new ResumeAllScriptsExcept();
        if(command == "AddInventory"))
            return new AddInventory();
        if(command == "IsActivated"))
            return new IsActivated();
        if(command == "Toggle"))
            return new ToggleActivatable();
        if(command == "SetZombieLimit"))
            return new SetZombieLimit();
        if(command == "IsSpeaking"))
            return new IsSpeaking();
        if(command == "RegisterOneTime"))
            return new RegisterOneTime();
        if(command == "Sleep"))
            return new Sleep();
        if(command == "SpawnZombie"))
            return new SpawnZombie();
        if(command == "HasInventory"))
            return new HasInventory();
        if(command == "AddUseItemOnTask"))
            return new AddUseItemOnTask();
        if(command == "ProcessNever"))
            return new ProcessNever();
        if(command == "ProcessAlways"))
            return new ProcessAlways();
        if(command == "IsNight"))
            return new IsNight();
        if(command == "Is"))
            return new IsFlagValue();
        if(command == "Set"))
            return new SetFlag();
        if(command == "Wait"))
            return new WaitCommand();
        if(command == "AddGotoLocationTask"))
            return new AddGotoLocationTask();
        if(command == "AddHardCodedTask"))
            return new AddHardCodedTask();
        if(command == "AddScriptConditionTask"))
            return new AddScriptConditionTask();
        if(command == "RunScriptOnComplete"))
            return new RunScriptOnComplete();
        if(command == "AddFindItemTask"))
            return new AddFindItemTask();
        if(command == "AddEquipItemTask"))
            return new AddEquipItemTask();
        if(command == "UnlockTaskOnComplete"))
            return new UnlockTaskOnComplete();
        if(command == "UnlockNextTasksOnComplete"))
            return new UnlockTasksOnComplete();
        if(command == "Unlock"))
            return new UnlockLast();
        if(command == "Walk"))
            return new WalkCommand();
        if(command == "UnlockQuest"))
            return new UnlockQuest();
        if(command == "LockHud"))
            return new LockHud();
        if(command == "LoadTexturePage"))
            return new LoadTexturePage();
        if(command == "Actualize"))
            return new ActualizeCommand();
        if(command == "Face"))
            return new FaceCommand();
        if(command == "Say"))
            return new SayCommand();
        if(command == "Pause"))
            return new Pause();
        if(command == "Resume"))
            return new Resume();
        if(command == "SayIdle"))
            return new SayIdle();
        if(command == "AddEnemy"))
            return new AddEnemy();
        if(command == "AddToGroup"))
            return new AddToGroup();
        if(command == "IsInGroup"))
            return new IsInGroup();
        if(command == "IsInGroupWith"))
        {
            return new IsInGroupWith();
        } else
        {
            command = command;
            return nullptr;
        }
    }
}
} // namespace
