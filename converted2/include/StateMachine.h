#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   StateMachine.java
namespace zombie {
namespace ai {
#include "LuaEventManager.h"
#include "IsoGameCharacter.h"
// Referenced classes of package zombie.ai:
//            State
class StateMachine {
public:
{
    public StateMachine(IsoGameCharacter owner)
    {
        Lock = false;
        Owner = owner;
    }
    public void changeState(State newState)
    {
        if(Lock)
            return;
        if(CurrentState == newState)
            return;
        PreviousState = CurrentState;
        if(CurrentState != nullptr)
            CurrentState.exit(Owner);
        CurrentState = newState;
        NextState = nullptr;
        if(CurrentState != nullptr)
            CurrentState.enter(Owner);
    }
    public void changeState(State newState, State nextState)
    {
        if(newState != CurrentState)
            LuaEventManager.TriggerEvent("OnAIStateChange", Owner, newState, CurrentState);
        if(Lock)
            return;
        PreviousState = CurrentState;
        if(CurrentState != nullptr)
            CurrentState.exit(Owner);
        CurrentState = newState;
        NextState = nextState;
        if(CurrentState != nullptr)
            CurrentState.enter(Owner);
    }
    public State getCurrent()
    {
        return CurrentState;
    }
    public State getGlobal()
    {
        return GlobalState;
    }
    public State getPrevious()
    {
        return PreviousState;
    }
    public void RevertToPrevious()
    {
        if(Lock)
        {
            return;
        } else
        {
            changeState(PreviousState);
            return;
        }
    }
    public void setCurrent(State state)
    {
        if(Lock)
        {
            return;
        } else
        {
            CurrentState = state;
            return;
        }
    }
    public void setGlobal(State state)
    {
        GlobalState = state;
    }
    public void setPrevious(State state)
    {
        if(Lock)
        {
            return;
        } else
        {
            PreviousState = state;
            return;
        }
    }
    public void update()
    {
        if(GlobalState != nullptr)
            GlobalState.execute(Owner);
        if(CurrentState != nullptr)
            CurrentState.execute(Owner);
    }
    public bool Lock;
    State CurrentState;
    State GlobalState;
    State NextState;
    IsoGameCharacter Owner;
    State PreviousState;
}} // namespace
