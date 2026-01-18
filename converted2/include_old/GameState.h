#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GameState.java
namespace zombie {
namespace gameStates {
// Referenced classes of package zombie.gameStates:
//            GameStateMachine
class GameState {
public:
{
    public GameState()
    {
    }
    public void enter()
    {
    }
    public void exit()
    {
    }
    public void render()
    {
    }
    public GameState redirectState()
    {
        return nullptr;
    }
    public GameStateMachine.StateAction update()
    {
        return GameStateMachine.StateAction.Continue;
    }
}
} // namespace
