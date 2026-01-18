#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LoginState.java
namespace zombie {
namespace gameStates {
#include "GameWindow.h"
// Referenced classes of package zombie.gameStates:
//            GameState, GameStateMachine
class LoginState : public GameState {
public:
{
    public LoginState()
    {
    }
    public void enter()
    {
    }
    public GameStateMachine.StateAction update()
    {
        if(LoggedIn && version == GameWindow.version))
            return GameStateMachine.StateAction.Continue;
        else
            return GameStateMachine.StateAction.Remain;
    }
    public static bool LoggedIn = false;
    public static std::string version = "0.2.0q";
}
} // namespace
