#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include <algorithm>

namespace zombie {
namespace gameStates {


class GameStateMachine {
public:
    bool firstrun = true;
    bool Loop = true;
    int StateIndex = 0;
    int LoopToState = 0;
   public const std::vector<GameState> States = std::make_unique<std::vector<>>();
    GameState current = nullptr;
   private const std::stack<GameState> yieldStack = std::make_unique<std::stack<>>();
    GameState forceNext = nullptr;

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

         this.States.push_back(this.forceNext);
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
         if (this.States.empty()) {
            return;
         }

         this.current = this.States.get(this.StateIndex);
         if (this.StateIndex < this.States.size()) {
            System.out.println("STATE: enter " + this.current.getClass().getName());
            this.current.enter();
         }
      }

      if (this.current != nullptr) {
    GameState var1 = nullptr;
         if (this.forceNext != nullptr) {
            System.out.println("STATE: exit " + this.current.getClass().getName());
            this.current.exit();
            var1 = this.forceNext;
            this.forceNext = nullptr;
         } else {
    StateAction var2 = this.current.update();
            if (var2 == StateAction.Continue) {
               System.out.println("STATE: exit " + this.current.getClass().getName());
               this.current.exit();
               if (!this.yieldStack.empty()) {
                  this.current = this.yieldStack.pop();
                  System.out.println("STATE: reenter " + this.current.getClass().getName());
                  this.current.reenter();
                  return;
               }

               var1 = this.current.redirectState();
            } else {
               if (var2 != StateAction.Yield) {
                  return;
               }

               System.out.println("STATE: yield " + this.current.getClass().getName());
               this.current.yield();
               this.yieldStack.push(this.current);
               var1 = this.current.redirectState();
            }
         }

         if (var1 == nullptr) {
            this.StateIndex++;
            if (this.StateIndex < this.States.size()) {
               this.current = this.States.get(this.StateIndex);
               System.out.println("STATE: enter " + this.current.getClass().getName());
               this.current.enter();
            } else {
               this.current = nullptr;
            }
         } else {
            System.out.println("STATE: enter " + var1.getClass().getName());
            var1.enter();
            this.current = var1;
         }
      }
   }

    void forceNextState(GameState var1) {
      this.forceNext = var1;
   }
}
} // namespace gameStates
} // namespace zombie
