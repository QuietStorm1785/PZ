#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   LuaState.java
namespace zombie {
namespace ai {
namespace states {
#include "LuaEventManager.h"
#include "SoundManager.h"
#include "State.h"
#include "IsoGameCharacter.h"
class LuaState : public State {
public:
{
    public LuaState()
    {
    }
    public static LuaState instance()
    {
        return _instance;
    }
    public void execute(IsoGameCharacter owner)
    {
        LuaEventManager.TriggerEvent("OnAIStateExecute", owner);
    }
    public void enter(IsoGameCharacter owner)
    {
        LuaEventManager.TriggerEvent("OnAIStateEnter", owner);
    }
    public void exit(IsoGameCharacter owner)
    {
        LuaEventManager.TriggerEvent("OnAIStateExit", owner);
    }
    void calculate()
    {
        SoundManager.instance.update3();
    }
    static LuaState _instance = new LuaState();
}} // namespace
