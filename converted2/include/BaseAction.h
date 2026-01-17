#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BaseAction.java
namespace zombie {
namespace characters {
namespace CharacterTimedActions {
#include "LuaEventManager.h"
#include "SoundManager.h"
#include "StateMachine.h"
#include "SwipeState.h"
#include "SwipeStatePlayer.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "Audio.h"
#include "ActionProgressBar.h"
#include "UIManager.h"
class BaseAction {
public:
{
    public BaseAction(IsoGameCharacter chr)
    {
        SoundEffect = nullptr;
        CurrentTime = 0;
        MaxTime = 60;
        UseProgressBar = true;
        StopOnWalk = true;
        StopOnRun = true;
        this.chr = chr;
    }
    public void PlayLoopedSoundTillComplete(std::string name, int radius, float maxGain)
    {
        SoundEffect = SoundManager.instance.PlayWorldSound(name, true, chr.getCurrentSquare(), 0.2F, radius, maxGain, true);
    }
    public void update()
    {
        if(chr.getStateMachine().getCurrent() == SwipeState.instance())
            chr.getStateMachine().changeState(chr.getDefaultState());
        if(chr.getStateMachine().getCurrent() == SwipeStatePlayer.instance())
            chr.getStateMachine().changeState(chr.getDefaultState());
        CurrentTime++;
        if(UseProgressBar && chr == IsoPlayer.getInstance())
        {
            UIManager.getProgressBar().setValue((float)CurrentTime / (float)MaxTime);
            if(CurrentTime > MaxTime)
                UIManager.getProgressBar().setValue(1.0F);
        }
    }
    public void start()
    {
    }
    public void stop()
    {
        if(SoundEffect != nullptr)
        {
            SoundManager.instance.StopSound(SoundEffect);
            SoundEffect = nullptr;
        }
        LuaEventManager.TriggerEvent("OnPlayerCancelTimedAction", this);
    }
    public bool valid()
    {
        return true;
    }
    public bool finished()
    {
        return CurrentTime >= MaxTime;
    }
    public void perform()
    {
    }
    public Audio SoundEffect;
    public int CurrentTime;
    public int MaxTime;
    public bool UseProgressBar;
    public IsoGameCharacter chr;
    public bool StopOnWalk;
    public bool StopOnRun;
}
} // namespace
