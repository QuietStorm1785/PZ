#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/action/ActionContext/s_performance.h"
#include "zombie/characters/action/conditions/CharacterVariableCondition/Factory.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimatable.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace action {


class ActionContext {
public:
    const IAnimatable m_owner;
    ActionGroup m_stateGroup;
    ActionState m_currentState;
   private const std::vector<ActionState> m_childStates = std::make_unique<std::vector<>>();
    std::string m_previousStateName = nullptr;
    bool m_statesChanged = false;
   public const std::vector<IActionStateChanged> onStateChanged = std::make_unique<std::vector<>>();
    const ActionContextEvents occurredEvents = std::make_shared<ActionContextEvents>();

    public ActionContext(IAnimatable var1) {
      this.m_owner = var1;
   }

    IAnimatable getOwner() {
      return this.m_owner;
   }

    void update() {
      s_performance.update.invokeAndMeasure(this, ActionContext::updateInternal);
   }

    void updateInternal() {
      if (this.m_currentState == nullptr) {
         this.logCurrentState();
      } else {
         s_performance.evaluateCurrentStateTransitions.invokeAndMeasure(this, ActionContext::evaluateCurrentStateTransitions);
         s_performance.evaluateSubStateTransitions.invokeAndMeasure(this, ActionContext::evaluateSubStateTransitions);
         this.invokeAnyStateChangedEvents();
         this.logCurrentState();
      }
   }

    ActionState getNextState() {
    ActionState var1 = nullptr;

      for (int var2 = 0; var2 < this.m_currentState.transitions.size(); var2++) {
    ActionTransition var3 = (ActionTransition)this.m_currentState.transitions.get(var2);
         if (var3.passes(this, 0) && !StringUtils.isNullOrWhitespace(var3.transitionTo)) {
    ActionState var4 = this.m_stateGroup.get(var3.transitionTo);
            if (var4 != nullptr && !this.hasChildState(var4)) {
               if (!var3.asSubstate || !this.currentStateSupportsChildState(var4)) {
                  var1 = var4;
                  break;
               }

               this.tryAddChildState(var4);
            }
         }
      }

      for (int var8 = 0; var8 < this.childStateCount(); var8++) {
    ActionState var9 = nullptr;
    ActionState var10 = this.getChildStateAt(var8);

         for (int var5 = 0; var5 < var10.transitions.size(); var5++) {
    ActionTransition var6 = (ActionTransition)var10.transitions.get(var5);
            if (var6.passes(this, 1)) {
               if (var6.transitionOut) {
                  var8--;
                  break;
               }

               if (!StringUtils.isNullOrWhitespace(var6.transitionTo)) {
    ActionState var7 = this.m_stateGroup.get(var6.transitionTo);
                  if (var7 != nullptr && !this.hasChildState(var7)) {
                     if (this.currentStateSupportsChildState(var7)) {
                        break;
                     }

                     if (var6.forceParent) {
                        var9 = var7;
                        break;
                     }
                  }
               }
            }
         }

         if (var9 != this.m_currentState && var9 != nullptr) {
            var1 = var9;
         }
      }

    return var1;
   }

    void evaluateCurrentStateTransitions() {
      for (int var1 = 0; var1 < this.m_currentState.transitions.size(); var1++) {
    ActionTransition var2 = (ActionTransition)this.m_currentState.transitions.get(var1);
         if (var2.passes(this, 0)) {
            if (StringUtils.isNullOrWhitespace(var2.transitionTo)) {
               DebugLog.ActionSystem.warn("%s> Transition's target state not specified: \"%s\"", new Object[]{this.getOwner().getUID(), var2.transitionTo});
            } else {
    ActionState var3 = this.m_stateGroup.get(var2.transitionTo);
               if (var3 == nullptr) {
                  DebugLog.ActionSystem.warn("%s> Transition's target state not found: \"%s\"", new Object[]{this.getOwner().getUID(), var2.transitionTo});
               } else if (!this.hasChildState(var3)) {
                  if (!var2.asSubstate || !this.currentStateSupportsChildState(var3)) {
                     if (this.dynamic_cast<IsoPlayer*>(m_owner) != nullptr) {
                        DebugLog.log(
                           DebugType.ActionSystem,
                           "Player '"
                              + ((IsoPlayer)this.m_owner).getUsername()
                              + "' transits from "
                              + this.m_currentState.getName()
                              + " to "
                              + var2.transitionTo
                        );
                     }

                     this.setCurrentState(var3);
                     break;
                  }

                  this.tryAddChildState(var3);
               }
            }
         }
      }
   }

    void evaluateSubStateTransitions() {
      for (int var1 = 0; var1 < this.childStateCount(); var1++) {
    ActionState var2 = nullptr;
    ActionState var3 = this.getChildStateAt(var1);

         for (int var4 = 0; var4 < var3.transitions.size(); var4++) {
    ActionTransition var5 = (ActionTransition)var3.transitions.get(var4);
            if (var5.passes(this, 1)) {
               if (var5.transitionOut) {
                  this.removeChildStateAt(var1);
                  var1--;
                  break;
               }

               if (!StringUtils.isNullOrWhitespace(var5.transitionTo)) {
    ActionState var6 = this.m_stateGroup.get(var5.transitionTo);
                  if (var6 == nullptr) {
                     DebugLog.ActionSystem.warn("%s> Transition's target state not found: \"%s\"", new Object[]{this.getOwner().getUID(), var5.transitionTo});
                  } else if (!this.hasChildState(var6)) {
                     if (this.currentStateSupportsChildState(var6)) {
                        this.m_childStates.set(var1, var6);
                        this.onStatesChanged();
                        break;
                     }

                     if (var5.forceParent) {
                        var2 = var6;
                        break;
                     }
                  }
               }
            }
         }

         if (var2 != this.m_currentState && var2 != nullptr) {
            this.setCurrentState(var2);
         }
      }
   }

    bool currentStateSupportsChildState(ActionState var1) {
      return this.m_currentState == nullptr ? false : this.m_currentState.canHaveSubState(var1);
   }

    bool hasChildState(ActionState var1) {
    int var2 = this.indexOfChildState(var1x -> var1x == var1);
      return var2 > -1;
   }

    void setPlaybackStateSnapshot(ActionStateSnapshot var1) {
      if (this.m_stateGroup != nullptr) {
         if (var1.stateName == nullptr) {
            DebugLog.General.warn("Snapshot not valid. Missing root state name.");
         } else {
    ActionState var2 = this.m_stateGroup.get(var1.stateName);
            this.setCurrentState(var2);
            if (PZArrayUtil.isNullOrEmpty(var1.childStateNames)) {
               while (this.childStateCount() > 0) {
                  this.removeChildStateAt(0);
               }
            } else {
               for (int var3 = 0; var3 < this.childStateCount(); var3++) {
    std::string var4 = this.getChildStateAt(var3).name;
    bool var5 = StringUtils.contains(var1.childStateNames, var4, StringUtils::equalsIgnoreCase);
                  if (!var5) {
                     this.removeChildStateAt(var3);
                     var3--;
                  }
               }

               for (int var6 = 0; var6 < var1.childStateNames.length; var6++) {
    std::string var7 = var1.childStateNames[var6];
    ActionState var8 = this.m_stateGroup.get(var7);
                  this.tryAddChildState(var8);
               }
            }
         }
      }
   }

    ActionStateSnapshot getPlaybackStateSnapshot() {
      if (this.m_currentState == nullptr) {
    return nullptr;
      } else {
    ActionStateSnapshot var1 = std::make_shared<ActionStateSnapshot>();
         var1.stateName = this.m_currentState.name;
         var1.childStateNames = new std::string[this.m_childStates.size()];

         for (int var2 = 0; var2 < var1.childStateNames.length; var2++) {
            var1.childStateNames[var2] = this.m_childStates.get(var2).name;
         }

    return var1;
      }
   }

    bool setCurrentState(ActionState var1) {
      if (var1 == this.m_currentState) {
    return false;
      } else {
         this.m_previousStateName = this.m_currentState == nullptr ? "" : this.m_currentState.getName();
         this.m_currentState = var1;

         for (int var2 = 0; var2 < this.m_childStates.size(); var2++) {
    ActionState var3 = this.m_childStates.get(var2);
            if (!this.m_currentState.canHaveSubState(var3)) {
               this.removeChildStateAt(var2);
               var2--;
            }
         }

         this.onStatesChanged();
    return true;
      }
   }

    bool tryAddChildState(ActionState var1) {
      if (this.hasChildState(var1)) {
    return false;
      } else {
         this.m_childStates.push_back(var1);
         this.onStatesChanged();
    return true;
      }
   }

    void removeChildStateAt(int var1) {
      this.m_childStates.remove(var1);
      this.onStatesChanged();
   }

    void onStatesChanged() {
      this.m_statesChanged = true;
   }

    void logCurrentState() {
      if (this.m_owner.isAnimationRecorderActive()) {
         this.m_owner.getAnimationPlayerRecorder().logActionState(this.m_currentState, this.m_childStates);
      }
   }

    void invokeAnyStateChangedEvents() {
      if (this.m_statesChanged) {
         this.m_statesChanged = false;
         this.occurredEvents.clear();

         for (int var1 = 0; var1 < this.onStateChanged.size(); var1++) {
    IActionStateChanged var2 = this.onStateChanged.get(var1);
            var2.actionStateChanged(this);
         }

         if (this.dynamic_cast<IsoZombie*>(m_owner) != nullptr) {
            ((IsoZombie)this.m_owner).networkAI.extraUpdate();
         }
      }
   }

    ActionState getCurrentState() {
      return this.m_currentState;
   }

    void setGroup(ActionGroup var1) {
    std::string var2 = this.m_currentState == nullptr ? nullptr : this.m_currentState.name;
      this.m_stateGroup = var1;
    ActionState var3 = var1.getInitialState();
      if (!StringUtils.equalsIgnoreCase(var2, var3.name)) {
         this.setCurrentState(var3);
      } else {
         this.m_currentState = var3;
      }
   }

    ActionGroup getGroup() {
      return this.m_stateGroup;
   }

    void reportEvent(const std::string& var1) {
      this.reportEvent(-1, var1);
   }

    void reportEvent(int var1, const std::string& var2) {
      this.occurredEvents.push_back(var2, var1);
      if (GameClient.bClient && var1 == -1 && this.dynamic_cast<IsoPlayer*>(m_owner) != nullptr && ((IsoPlayer)this.m_owner).isLocalPlayer()) {
         GameClient.sendEvent((IsoPlayer)this.m_owner, var2);
      }
   }

    bool hasChildStates() {
      return this.childStateCount() > 0;
   }

    int childStateCount() {
      return this.m_childStates != nullptr ? this.m_childStates.size() : 0;
   }

    void foreachChildState(Consumer<ActionState> var1) {
      for (int var2 = 0; var2 < this.childStateCount(); var2++) {
    ActionState var3 = this.getChildStateAt(var2);
         var1.accept(var3);
      }
   }

    int indexOfChildState(Predicate<ActionState> var1) {
    int var2 = -1;

      for (int var3 = 0; var3 < this.childStateCount(); var3++) {
    ActionState var4 = this.getChildStateAt(var3);
         if (var1.test(var4)) {
            var2 = var3;
            break;
         }
      }

    return var2;
   }

    ActionState getChildStateAt(int var1) {
      if (var1 >= 0 && var1 < this.childStateCount()) {
         return this.m_childStates.get(var1);
      } else {
         throw IndexOutOfBoundsException(std::string.format("Index %d out of bounds. childCount: %d", var1, this.childStateCount()));
      }
   }

   public List<ActionState> getChildStates() {
      return this.m_childStates;
   }

    std::string getCurrentStateName() {
      return this.m_currentState.name;
   }

    std::string getPreviousStateName() {
      return this.m_previousStateName;
   }

    bool hasEventOccurred(const std::string& var1) {
      return this.hasEventOccurred(var1, -1);
   }

    bool hasEventOccurred(const std::string& var1, int var2) {
      return this.occurredEvents.contains(var1, var2);
   }

    void clearEvent(const std::string& var1) {
      this.occurredEvents.clearEvent(var1);
   }

   static {
    Factory var0 = std::make_shared<Factory>();
      IActionCondition.registerFactory("isTrue", var0);
      IActionCondition.registerFactory("isFalse", var0);
      IActionCondition.registerFactory("compare", var0);
      IActionCondition.registerFactory("gtr", var0);
      IActionCondition.registerFactory("less", var0);
      IActionCondition.registerFactory("equals", var0);
      IActionCondition.registerFactory("lessEqual", var0);
      IActionCondition.registerFactory("gtrEqual", var0);
      IActionCondition.registerFactory("notEquals", var0);
      IActionCondition.registerFactory("eventOccurred", new zombie.characters.action.conditions.EventOccurred.Factory());
      IActionCondition.registerFactory("eventNotOccurred", new zombie.characters.action.conditions.EventNotOccurred.Factory());
      IActionCondition.registerFactory("lua", new zombie.characters.action.conditions.LuaCall.Factory());
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
