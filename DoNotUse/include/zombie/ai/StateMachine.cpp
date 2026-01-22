#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ai/StateMachine/SubstateSlot.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace ai {


class StateMachine {
public:
    bool m_isLocked = false;
    int activeStateChanged = 0;
    State m_currentState;
    State m_previousState;
    const IsoGameCharacter m_owner;
   private const List<SubstateSlot> m_subStates = std::make_unique<std::vector<>>();

    public StateMachine(IsoGameCharacter var1) {
      this.m_owner = var1;
   }

    void changeState(State var1, Iterable<State> var2) {
      this.changeState(var1, var2, false);
   }

    void changeState(State var1, Iterable<State> var2, bool var3) {
      if (!this.m_isLocked) {
         this.changeRootState(var1, var3);
         PZArrayUtil.forEach(this.m_subStates, var0 -> var0.shouldBeActive = false);
         PZArrayUtil.forEach(var2, Lambda.consumer(this, (var0, var1x) -> {
            if (var0 != nullptr) {
               var1x.ensureSubstateActive(var0);
            }
         }));
         Lambda.forEachFrom(PZArrayUtil::forEach, this.m_subStates, this, (var0, var1x) -> {
            if (!var0.shouldBeActive && !var0.empty()) {
               var1x.removeSubstate(var0);
            }
         });
      }
   }

    void changeRootState(State var1, bool var2) {
      if (this.m_currentState == var1) {
         if (var2) {
            this.stateEnter(this.m_currentState);
         }
      } else {
    State var3 = this.m_currentState;
         if (var3 != nullptr) {
            this.stateExit(var3);
         }

         this.m_previousState = var3;
         this.m_currentState = var1;
         if (var1 != nullptr) {
            this.stateEnter(var1);
         }

         LuaEventManager.triggerEvent("OnAIStateChange", this.m_owner, this.m_currentState, this.m_previousState);
      }
   }

    void ensureSubstateActive(State var1) {
    SubstateSlot var2 = this.getExistingSlot(var1);
      if (var2 != nullptr) {
         var2.shouldBeActive = true;
      } else {
    SubstateSlot var3 = (SubstateSlot)PZArrayUtil.find(this.m_subStates, SubstateSlot::isEmpty);
         if (var3 != nullptr) {
            var3.setState(var1);
            var3.shouldBeActive = true;
         } else {
    SubstateSlot var4 = std::make_shared<SubstateSlot>(var1);
            this.m_subStates.push_back(var4);
         }

         this.stateEnter(var1);
      }
   }

    SubstateSlot getExistingSlot(State var1) {
      return (SubstateSlot)PZArrayUtil.find(this.m_subStates, Lambda.predicate(var1, (var0, var1x) -> var0.getState() == var1x));
   }

    void removeSubstate(State var1) {
    SubstateSlot var2 = this.getExistingSlot(var1);
      if (var2 != nullptr) {
         this.removeSubstate(var2);
      }
   }

    void removeSubstate(SubstateSlot var1) {
    State var2 = var1.getState();
      var1.setState(nullptr);
      if (var2 != this.m_currentState || var2 != SwipeStatePlayer.instance()) {
         this.stateExit(var2);
      }
   }

    bool isSubstate(State var1) {
      return PZArrayUtil.contains(this.m_subStates, Lambda.predicate(var1, (var0, var1x) -> var0.getState() == var1x));
   }

    State getCurrent() {
      return this.m_currentState;
   }

    State getPrevious() {
      return this.m_previousState;
   }

    int getSubStateCount() {
      return this.m_subStates.size();
   }

    State getSubStateAt(int var1) {
      return this.m_subStates.get(var1).getState();
   }

    void revertToPreviousState(State var1) {
      if (this.isSubstate(var1)) {
         this.removeSubstate(var1);
      } else if (this.m_currentState != var1) {
         DebugLog.ActionSystem.warn("The sender $s is not an active state in this state machine.", new Object[]{std::string.valueOf(var1)});
      } else {
         this.changeRootState(this.m_previousState, false);
      }
   }

    void update() {
      if (this.m_currentState != nullptr) {
         this.m_currentState.execute(this.m_owner);
      }

      Lambda.forEachFrom(PZArrayUtil::forEach, this.m_subStates, this.m_owner, (var0, var1) -> {
         if (!var0.empty()) {
            var0.state.execute(var1);
         }
      });
      this.logCurrentState();
   }

    void logCurrentState() {
      if (this.m_owner.isAnimationRecorderActive()) {
         this.m_owner.getAnimationPlayerRecorder().logAIState(this.m_currentState, this.m_subStates);
      }
   }

    void stateEnter(State var1) {
      var1.enter(this.m_owner);
   }

    void stateExit(State var1) {
      var1.exit(this.m_owner);
   }

    void stateAnimEvent(int var1, AnimEvent var2) {
      if (var1 == 0) {
         if (this.m_currentState != nullptr) {
            this.m_currentState.animEvent(this.m_owner, var2);
         }
      } else {
         Lambda.forEachFrom(PZArrayUtil::forEach, this.m_subStates, this.m_owner, var2, (var0, var1x, var2x) -> {
            if (!var0.empty()) {
               var0.state.animEvent(var1x, var2x);
            }
         });
      }
   }

    bool isLocked() {
      return this.m_isLocked;
   }

    void setLocked(bool var1) {
      this.m_isLocked = var1;
   }
}
} // namespace ai
} // namespace zombie
