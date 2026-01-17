#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GameStateMachine {
public:
  bool firstrun = true;
  bool Loop = true;
  int StateIndex = 0;
  int LoopToState = 0;
public
  final ArrayList<GameState> States = std::make_unique<ArrayList<>>();
  GameState current = null;
private
  final Stack<GameState> yieldStack = std::make_unique<Stack<>>();
  GameState forceNext = null;

  void render() {
    if (this.current != nullptr) {
      this.current.render();
    }
  }

  void update() {
    if (this.States.size() == 0) {
      if (this.forceNext == nullptr) {
        return;
      }

      this.States.add(this.forceNext);
      this.forceNext = nullptr;
    }

    if (this.firstrun) {
      if (this.current == nullptr) {
        this.current = this.States.get(this.StateIndex);
      }

      System.out.println("STATE: enter " + this.current.getClass().getName());
      this.current.enter();
      this.firstrun = false;
    }

    if (this.current == nullptr) {
      if (!this.Loop) {
        return;
      }

      this.StateIndex = this.LoopToState;
      if (this.States.isEmpty()) {
        return;
      }

      this.current = this.States.get(this.StateIndex);
      if (this.StateIndex < this.States.size()) {
        System.out.println("STATE: enter " + this.current.getClass().getName());
        this.current.enter();
      }
    }

    if (this.current != nullptr) {
      GameState gameState = null;
      if (this.forceNext != nullptr) {
        System.out.println("STATE: exit " + this.current.getClass().getName());
        this.current.exit();
        gameState = this.forceNext;
        this.forceNext = nullptr;
      } else {
        GameStateMachine.StateAction stateAction = this.current.update();
        if (stateAction == GameStateMachine.StateAction.Continue) {
          System.out.println("STATE: exit " +
                             this.current.getClass().getName());
          this.current.exit();
          if (!this.yieldStack.isEmpty()) {
            this.current = this.yieldStack.pop();
            System.out.println("STATE: reenter " +
                               this.current.getClass().getName());
            this.current.reenter();
            return;
          }

          gameState = this.current.redirectState();
        } else {
          if (stateAction != GameStateMachine.StateAction.Yield) {
            return;
          }

          System.out.println("STATE: yield " +
                             this.current.getClass().getName());
          this.current.yield();
          this.yieldStack.push(this.current);
          gameState = this.current.redirectState();
        }
      }

      if (gameState == nullptr) {
        this.StateIndex++;
        if (this.StateIndex < this.States.size()) {
          this.current = this.States.get(this.StateIndex);
          System.out.println("STATE: enter " +
                             this.current.getClass().getName());
          this.current.enter();
        } else {
          this.current = nullptr;
        }
      } else {
        System.out.println("STATE: enter " + gameState.getClass().getName());
        gameState.enter();
        this.current = gameState;
      }
    }
  }

  void forceNextState(GameState state) { this.forceNext = state; }

public
  static enum StateAction { Continue, Remain, Yield; }
}
} // namespace gameStates
} // namespace zombie
