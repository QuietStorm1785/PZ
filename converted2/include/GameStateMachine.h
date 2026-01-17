#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GameStateMachine.java
namespace zombie {
namespace gameStates {
#include <vector>
// Referenced classes of package zombie.gameStates:
//            GameState
class GameStateMachine {
public:
{
	/*    */   public static enum StateAction
	/*    */   {
	/* 21 */     Continue, 
	/* 22 */     Remain;
	/*    */   }
    public GameStateMachine()
    {
        firstrun = true;
        Loop = true;
        StateIndex = 0;
        LoopToState = 0;
        States = new ArrayList();
        current = nullptr;
    }
    public void render()
    {
        if(current != nullptr)
            current.render();
    }
    public void update()
    {
        if(firstrun)
        {
            if(current == nullptr)
                current = (GameState)States.get(StateIndex);
            current.enter();
            firstrun = false;
        }
        if(current == nullptr)
            if(Loop)
            {
                StateIndex = LoopToState;
                current = (GameState)States.get(StateIndex);
                if(StateIndex < States.size())
                    current.enter();
            } else
            {
                return;
            }
        if(current != nullptr && current.update() == StateAction.Continue)
        {
            current.exit();
            GameState next = current.redirectState();
            if(next == nullptr)
            {
                StateIndex++;
                if(StateIndex < States.size())
                {
                    current = (GameState)States.get(StateIndex);
                    current.enter();
                } else
                {
                    current = nullptr;
                }
            } else
            {
                next.enter();
                current = next;
            }
        }
    }
    public bool firstrun;
    public bool Loop;
    public int StateIndex;
    public int LoopToState;
    public ArrayList States;
    GameState current;
}
} // namespace
