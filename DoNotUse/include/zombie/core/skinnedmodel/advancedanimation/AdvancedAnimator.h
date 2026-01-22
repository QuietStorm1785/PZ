#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameProfiler.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator/SubLayerSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimCondition/Type.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AdvancedAnimator {
public:
    IAnimatable character;
    AnimationSet animSet;
   public const std::vector<IAnimEventCallback> animCallbackHandlers = std::make_unique<std::vector<>>();
    AnimLayer m_rootLayer = nullptr;
   private const List<SubLayerSlot> m_subLayers = std::make_unique<std::vector<>>();
    static float s_MotionScale = 0.76F;
    static float s_RotationScale = 0.76F;
    AnimatorDebugMonitor debugMonitor;
    static long animSetModificationTime = -1L;
    static long actionGroupModificationTime = -1L;
    AnimationPlayerRecorder m_recorder = nullptr;

    static void systemInit() {
      DebugFileWatcher.instance
         .push_back(std::make_shared<PredicatedFileWatcher>("media/AnimSets", AdvancedAnimator::isAnimSetFilePath, AdvancedAnimator::onAnimSetsRefreshTriggered));
      DebugFileWatcher.instance
         .push_back(std::make_shared<PredicatedFileWatcher>("media/actiongroups", AdvancedAnimator::isActionGroupFilePath, AdvancedAnimator::onActionGroupsRefreshTriggered));
      LoadDefaults();
   }

    static bool isAnimSetFilePath(const std::string& var0) {
      if (var0 == nullptr) {
    return false;
      } else if (!var0.endsWith(".xml")) {
    return false;
      } else {
    std::vector var1 = ZomboidFileSystem.instance.getModIDs();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = (std::string)var1.get(var2);
    Mod var4 = ChooseGameInfo.getModDetails(var3);
            if (var4 != nullptr && var4.animSetsFile != nullptr && var0.startsWith(var4.animSetsFile.getPath())) {
    return true;
            }
         }

    std::string var5 = ZomboidFileSystem.instance.getAnimSetsPath();
         return var0.startsWith(var5);
      }
   }

    static bool isActionGroupFilePath(const std::string& var0) {
      if (var0 == nullptr) {
    return false;
      } else if (!var0.endsWith(".xml")) {
    return false;
      } else {
    std::vector var1 = ZomboidFileSystem.instance.getModIDs();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = (std::string)var1.get(var2);
    Mod var4 = ChooseGameInfo.getModDetails(var3);
            if (var4 != nullptr && var4.actionGroupsFile != nullptr && var0.startsWith(var4.actionGroupsFile.getPath())) {
    return true;
            }
         }

    std::string var5 = ZomboidFileSystem.instance.getActionGroupsPath();
         return var0.startsWith(var5);
      }
   }

    static void onActionGroupsRefreshTriggered(const std::string& var0) {
      DebugLog.General.println("DebugFileWatcher Hit. ActionGroups: " + var0);
      actionGroupModificationTime = System.currentTimeMillis() + 1000L;
   }

    static void onAnimSetsRefreshTriggered(const std::string& var0) {
      DebugLog.General.println("DebugFileWatcher Hit. AnimSets: " + var0);
      animSetModificationTime = System.currentTimeMillis() + 1000L;
   }

    static void checkModifiedFiles() {
      if (animSetModificationTime != -1L && animSetModificationTime < System.currentTimeMillis()) {
         DebugLog.General.println("Refreshing AnimSets.");
         animSetModificationTime = -1L;
         LoadDefaults();
         GlobalObject.refreshAnimSets(true);
      }

      if (actionGroupModificationTime != -1L && actionGroupModificationTime < System.currentTimeMillis()) {
         DebugLog.General.println("Refreshing action groups.");
         actionGroupModificationTime = -1L;
         GlobalObject.reloadActionGroups();
      }
   }

    static void LoadDefaults() {
      try {
    Element var0 = PZXmlUtil.parseXml("media/AnimSets/Defaults.xml");
    std::string var1 = var0.getElementsByTagName("MotionScale").item(0).getTextContent();
         s_MotionScale = float.parseFloat(var1);
    std::string var2 = var0.getElementsByTagName("RotationScale").item(0).getTextContent();
         s_RotationScale = float.parseFloat(var2);
      } catch (PZXmlParserException var3) {
         DebugLog.General.error("Exception thrown: " + var3);
         var3.printStackTrace();
      }
   }

    std::string GetDebug() {
    std::stringstream var1 = new std::stringstream();
      var1.append("GameState: ");
      if (this.dynamic_cast<IsoGameCharacter*>(character) != nullptr var2) {
         var1.append(var2.getCurrentState() == nullptr ? "nullptr" : var2.getCurrentState().getClass().getSimpleName()).append("\n");
      }

      if (this.m_rootLayer != nullptr) {
         var1.append("Layer: ").append(0).append("\n");
         var1.append(this.m_rootLayer.GetDebugString()).append("\n");
      }

      var1.append("Variables:\n");
      var1.append("Weapon: ").append(this.character.getVariableString("weapon")).append("\n");
      var1.append("Aim: ").append(this.character.getVariableString("aim")).append("\n");

      for (IAnimationVariableSlot var3 : this.character.getGameVariables()) {
         var1.append("  ").append(var3.getKey()).append(" : ").append(var3.getValueString()).append("\n");
      }

      return var1;
   }

    void OnAnimDataChanged(bool var1) {
      if (var1 && this.dynamic_cast<IsoGameCharacter*>(character) != nullptr var2) {
         var2.getStateMachine().activeStateChanged++;
         var2.setDefaultState();
         if (dynamic_cast<IsoZombie*>(var2) != nullptr) {
            var2.setOnFloor(false);
         }

         var2.getStateMachine().activeStateChanged--;
      }

      this.SetAnimSet(AnimationSet.GetAnimationSet(this.character.GetAnimSetName(), false));
      if (this.character.getAnimationPlayer() != nullptr) {
         this.character.getAnimationPlayer().reset();
      }

      if (this.m_rootLayer != nullptr) {
         this.m_rootLayer.Reset();
      }

      for (int var4 = 0; var4 < this.m_subLayers.size(); var4++) {
    SubLayerSlot var3 = this.m_subLayers.get(var4);
         var3.animLayer.Reset();
      }
   }

    void Reload() {
   }

    void init(IAnimatable var1) {
      this.character = var1;
      this.m_rootLayer = std::make_shared<AnimLayer>(var1, this);
   }

    void SetAnimSet(AnimationSet var1) {
      this.animSet = var1;
   }

    void OnAnimEvent(AnimLayer var1, AnimEvent var2) {
      for (int var3 = 0; var3 < this.animCallbackHandlers.size(); var3++) {
    IAnimEventCallback var4 = this.animCallbackHandlers.get(var3);
         var4.OnAnimEvent(var1, var2);
      }
   }

    std::string getCurrentStateName() {
      return this.m_rootLayer == nullptr ? nullptr : this.m_rootLayer.getCurrentStateName();
   }

    bool containsState(const std::string& var1) {
      return this.animSet != nullptr && this.animSet.containsState(var1);
   }

    void SetState(const std::string& var1) {
      this.SetState(var1, PZArrayList.emptyList());
   }

    void SetState(const std::string& var1, List<std::string> var2) {
      if (this.animSet == nullptr) {
         DebugLog.Animation.error("(" + var1 + ") Cannot set state. AnimSet is nullptr.");
      } else {
         if (!this.animSet.containsState(var1)) {
            DebugLog.Animation.error("State not found: " + var1);
         }

         this.m_rootLayer.TransitionTo(this.animSet.GetState(var1), false);
         PZArrayUtil.forEach(this.m_subLayers, var0 -> var0.shouldBeActive = false);
         Lambda.forEachFrom(PZArrayUtil::forEach, var2, this, (var0, var1x) -> {
    SubLayerSlot var2x = var1x.getOrCreateSlot(var0);
            var2x.transitionTo(var1x.animSet.GetState(var0), false);
         });
         PZArrayUtil.forEach(this.m_subLayers, SubLayerSlot::applyTransition);
      }
   }

    SubLayerSlot getOrCreateSlot(const std::string& var1) {
    SubLayerSlot var2 = nullptr;
    int var3 = 0;

      for (int var4 = this.m_subLayers.size(); var3 < var4; var3++) {
    SubLayerSlot var5 = this.m_subLayers.get(var3);
         if (var5.animLayer.isCurrentState(var1)) {
            var2 = var5;
            break;
         }
      }

      if (var2 != nullptr) {
    return var2;
      } else {
         var3 = 0;

         for (int var8 = this.m_subLayers.size(); var3 < var8; var3++) {
    SubLayerSlot var9 = this.m_subLayers.get(var3);
            if (var9.animLayer.isStateless()) {
               var2 = var9;
               break;
            }
         }

         if (var2 != nullptr) {
    return var2;
         } else {
    SubLayerSlot var7 = std::make_shared<SubLayerSlot>(this.m_rootLayer, this.character, this);
            this.m_subLayers.push_back(var7);
    return var7;
         }
      }
   }

    void update() {
      GameProfiler.getInstance().invokeAndMeasure("AdvancedAnimator.Update", this, AdvancedAnimator::updateInternal);
   }

    void updateInternal() {
      if (this.character.getAnimationPlayer() != nullptr) {
         if (this.character.getAnimationPlayer().isReady()) {
            if (this.animSet != nullptr) {
               if (!this.m_rootLayer.hasState()) {
                  this.m_rootLayer.TransitionTo(this.animSet.GetState("Idle"), true);
               }

               this.m_rootLayer.Update();

               for (int var1 = 0; var1 < this.m_subLayers.size(); var1++) {
    SubLayerSlot var2 = this.m_subLayers.get(var1);
                  var2.update();
               }

               if (this.debugMonitor != nullptr && this.dynamic_cast<IsoGameCharacter*>(character) != nullptr) {
    int var5 = 1 + this.getActiveSubLayerCount();
                  AnimLayer[] var7 = new AnimLayer[var5];
                  var7[0] = this.m_rootLayer;
                  var5 = 0;

                  for (int var3 = 0; var3 < this.m_subLayers.size(); var3++) {
    SubLayerSlot var4 = this.m_subLayers.get(var3);
                     if (var4.shouldBeActive) {
                        var7[1 + var5] = var4.animLayer;
                        var5++;
                     }
                  }

                  this.debugMonitor.update((IsoGameCharacter)this.character, var7);
               }
            }
         }
      }
   }

    void render() {
      if (this.character.getAnimationPlayer() != nullptr) {
         if (this.character.getAnimationPlayer().isReady()) {
            if (this.animSet != nullptr) {
               if (this.m_rootLayer.hasState()) {
                  this.m_rootLayer.render();
               }
            }
         }
      }
   }

    void printDebugCharacterActions(const std::string& var1) {
      if (this.animSet != nullptr) {
    AnimState var2 = this.animSet.GetState("actions");
         if (var2 != nullptr) {
    bool var4 = false;
    bool var5 = false;

            for (CharacterActionAnims var10 : CharacterActionAnims.values()) {
               var4 = false;
    std::string var6;
               if (var10 == CharacterActionAnims.None) {
                  var6 = var1;
                  var4 = true;
               } else {
                  var6 = var10;
               }

    bool var3 = false;

               for (AnimNode var12 : var2.m_Nodes) {
                  for (AnimCondition var14 : var12.m_Conditions) {
                     if (var14.m_Type == Type.STRING && var14.m_Name.toLowerCase() == "performingaction") && var14.m_StringValue.equalsIgnoreCase(var6)) {
                        var3 = true;
                        break;
                     }
                  }

                  if (var3) {
                     break;
                  }
               }

               if (var3) {
                  if (var4) {
                     var5 = true;
                  }
               } else {
                  DebugLog.log("WARNING: did not find node with condition 'PerformingAction = " + var6 + "' in player/actions/");
               }
            }

            if (var5) {
               if (DebugLog.isEnabled(DebugType.Animation)) {
                  DebugLog.Animation.debugln("SUCCESS - Current 'actions' TargetNode: '" + var1 + "' was found.");
               }
            } else if (DebugLog.isEnabled(DebugType.Animation)) {
               DebugLog.Animation.debugln("FAIL - Current 'actions' TargetNode: '" + var1 + "' not found.");
            }
         }
      }
   }

   public std::vector<std::string> debugGetVariables() {
    std::vector var1 = new std::vector();
      if (this.animSet != nullptr) {
         for (Entry var3 : this.animSet.states.entrySet()) {
    AnimState var4 = (AnimState)var3.getValue();

            for (AnimNode var6 : var4.m_Nodes) {
               for (AnimCondition var8 : var6.m_Conditions) {
                  if (var8.m_Name != nullptr && !var1.contains(var8.m_Name.toLowerCase())) {
                     var1.push_back(var8.m_Name.toLowerCase());
                  }
               }
            }
         }
      }

    return var1;
   }

    AnimatorDebugMonitor getDebugMonitor() {
      return this.debugMonitor;
   }

    void setDebugMonitor(AnimatorDebugMonitor var1) {
      this.debugMonitor = var1;
   }

    IAnimatable getCharacter() {
      return this.character;
   }

    void updateSpeedScale(const std::string& var1, float var2) {
      if (this.m_rootLayer != nullptr) {
    std::vector var3 = this.m_rootLayer.getLiveAnimNodes();

         for (int var4 = 0; var4 < var3.size(); var4++) {
    LiveAnimNode var5 = (LiveAnimNode)var3.get(var4);
            if (var5.isActive() && var5.getSourceNode() != nullptr && var1 == var5.getSourceNode().m_SpeedScaleVariable)) {
               var5.getSourceNode().m_SpeedScale = var2 + "";

               for (int var6 = 0; var6 < var5.m_AnimationTracks.size(); var6++) {
                  ((AnimationTrack)var5.m_AnimationTracks.get(var6)).SpeedDelta = var2;
               }
            }
         }
      }
   }

    bool containsAnyIdleNodes() {
      if (this.m_rootLayer == nullptr) {
    return false;
      } else {
    bool var1 = false;
    std::vector var2 = this.m_rootLayer.getLiveAnimNodes();

         for (int var3 = 0; var3 < var2.size() && !var1; var3++) {
            var1 = ((LiveAnimNode)var2.get(var3)).isIdleAnimActive();
         }

         for (int var7 = 0; var7 < this.getSubLayerCount(); var7++) {
    AnimLayer var4 = this.getSubLayerAt(var7);
            var2 = var4.getLiveAnimNodes();

            for (int var5 = 0; var5 < var2.size(); var5++) {
               var1 = ((LiveAnimNode)var2.get(var5)).isIdleAnimActive();
               if (!var1) {
                  break;
               }
            }
         }

    return var1;
      }
   }

    AnimLayer getRootLayer() {
      return this.m_rootLayer;
   }

    int getSubLayerCount() {
      return this.m_subLayers.size();
   }

    AnimLayer getSubLayerAt(int var1) {
      return this.m_subLayers.get(var1).animLayer;
   }

    int getActiveSubLayerCount() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.m_subLayers.size(); var2++) {
    SubLayerSlot var3 = this.m_subLayers.get(var2);
         if (var3.shouldBeActive) {
            var1++;
         }
      }

    return var1;
   }

    void setRecorder(AnimationPlayerRecorder var1) {
      this.m_recorder = var1;
   }

    bool isRecording() {
      return this.m_recorder != nullptr && this.m_recorder.isRecording();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
