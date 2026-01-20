#pragma once
#include <list>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/LogType.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitorLogLine.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredLayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredTrack.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor/MonitoredVar.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
namespace debug {


class AnimatorDebugMonitor {
public:
   private static const std::vector<std::string> knownVariables = std::make_unique<std::vector<>>();
    static bool knownVarsDirty = false;
    std::string currentState = "nullptr";
   private MonitoredLayer[] monitoredLayers;
   private const std::unordered_map<std::string, MonitoredVar> monitoredVariables = std::make_unique<std::unordered_map<>>();
   private const std::vector<std::string> customVariables = std::make_unique<std::vector<>>();
   private const std::list<MonitorLogLine> logLines = std::make_unique<std::list<>>();
   private const std::queue<MonitorLogLine> logLineQueue = std::make_unique<std::list<>>();
    bool floatsListDirty = false;
    bool hasFilterChanges = false;
    bool hasLogUpdates = false;
    std::string logString = "";
    static const int maxLogSize = 1028;
    static const int maxOutputLines = 128;
    static const int maxFloatCache = 1024;
   private const std::vector<float> floatsOut = std::make_unique<std::vector<>>();
    MonitoredVar selectedVariable;
    int tickCount = 0;
    bool doTickStamps = false;
    static const int tickStampLength = 10;
    static const Color col_curstate = Colors.Cyan;
    static const Color col_layer_nodename = Colors.CornFlowerBlue;
    static const Color col_layer_activated = Colors.DarkTurquoise;
    static const Color col_layer_deactivated = Colors.Orange;
    static const Color col_track_activated = Colors.SandyBrown;
    static const Color col_track_deactivated = Colors.Salmon;
    static const Color col_node_activated = Colors.Pink;
    static const Color col_node_deactivated = Colors.Plum;
    static const Color col_var_activated = Colors.Chartreuse;
    static const Color col_var_changed = Colors.LimeGreen;
    static const Color col_var_deactivated = Colors.Gold;
    static const std::string TAG_VAR = "[variable]";
    static const std::string TAG_LAYER = "[layer]";
    static const std::string TAG_NODE = "[active_nodes]";
    static const std::string TAG_TRACK = "[anim_tracks]";
   private boolean[] logFlags = new boolean[LogType.MAX.value()];

    public AnimatorDebugMonitor(IsoGameCharacter var1) {
      this.logFlags[LogType.DEFAULT.value()] = true;

      for (int var2 = 0; var2 < this.logFlags.length; var2++) {
         this.logFlags[var2] = true;
      }

      for (int var5 = 0; var5 < 1024; var5++) {
         this.floatsOut.push_back(0.0F);
      }

      this.initCustomVars();
      if (var1 != nullptr && var1.advancedAnimator != nullptr) {
         for (std::string var4 : var1.advancedAnimator.debugGetVariables()) {
            registerVariable(var4);
         }
      }
   }

    void initCustomVars() {
      this.addCustomVariable("aim");
      this.addCustomVariable("bdead");
      this.addCustomVariable("bfalling");
      this.addCustomVariable("baimatfloor");
      this.addCustomVariable("battackfrombehind");
      this.addCustomVariable("attacktype");
      this.addCustomVariable("bundervehicle");
      this.addCustomVariable("reanimatetimer");
      this.addCustomVariable("isattacking");
      this.addCustomVariable("canclimbdownrope");
      this.addCustomVariable("frombehind");
      this.addCustomVariable("fallonfront");
      this.addCustomVariable("hashitreaction");
      this.addCustomVariable("hitreaction");
      this.addCustomVariable("collided");
      this.addCustomVariable("collidetype");
      this.addCustomVariable("intrees");
   }

    void addCustomVariable(const std::string& var1) {
    std::string var2 = var1.toLowerCase();
      if (!this.customVariables.contains(var2)) {
         this.customVariables.push_back(var2);
      }

      registerVariable(var1);
   }

    void removeCustomVariable(const std::string& var1) {
    std::string var2 = var1.toLowerCase();
      this.customVariables.remove(var2);
   }

    void setFilter(int var1, bool var2) {
      if (var1 >= 0 && var1 < LogType.MAX.value()) {
         this.logFlags[var1] = var2;
         this.hasFilterChanges = true;
      }
   }

    bool getFilter(int var1) {
      return var1 >= 0 && var1 < LogType.MAX.value() ? this.logFlags[var1] : false;
   }

    bool isDoTickStamps() {
      return this.doTickStamps;
   }

    void setDoTickStamps(bool var1) {
      if (this.doTickStamps != var1) {
         this.doTickStamps = var1;
         this.hasFilterChanges = true;
      }
   }

    void queueLogLine(const std::string& var1) {
      this.addLogLine(LogType.DEFAULT, var1, nullptr, true);
   }

    void queueLogLine(const std::string& var1, Color var2) {
      this.addLogLine(LogType.DEFAULT, var1, var2, true);
   }

    void queueLogLine(LogType var1, const std::string& var2, Color var3) {
      this.addLogLine(var1, var2, var3, true);
   }

    void addLogLine(const std::string& var1) {
      this.addLogLine(LogType.DEFAULT, var1, nullptr, false);
   }

    void addLogLine(const std::string& var1, Color var2) {
      this.addLogLine(LogType.DEFAULT, var1, var2, false);
   }

    void addLogLine(const std::string& var1, Color var2, bool var3) {
      this.addLogLine(LogType.DEFAULT, var1, var2, var3);
   }

    void addLogLine(LogType var1, const std::string& var2, Color var3) {
      this.addLogLine(var1, var2, var3, false);
   }

    void addLogLine(LogType var1, const std::string& var2, Color var3, bool var4) {
    MonitorLogLine var5 = std::make_shared<MonitorLogLine>(this);
      var5.line = var2;
      var5.color = var3;
      var5.type = var1;
      var5.tick = this.tickCount;
      if (var4) {
         this.logLineQueue.push_back(var5);
      } else {
         this.log(var5);
      }
   }

    void log(MonitorLogLine var1) {
      this.logLines.addFirst(var1);
      if (this.logLines.size() > 1028) {
         this.logLines.removeLast();
      }

      this.hasLogUpdates = true;
   }

    void processQueue() {
      while (this.logLineQueue.size() > 0) {
    MonitorLogLine var1 = this.logLineQueue.poll();
         this.log(var1);
      }
   }

    void preUpdate() {
      for (Entry var2 : this.monitoredVariables.entrySet()) {
         ((MonitoredVar)var2.getValue()).updated = false;
      }

      for (int var5 = 0; var5 < this.monitoredLayers.length; var5++) {
    MonitoredLayer var6 = this.monitoredLayers[var5];
         var6.updated = false;

         for (Entry var4 : var6.activeNodes.entrySet()) {
            ((MonitoredNode)var4.getValue()).updated = false;
         }

         for (Entry var8 : var6.animTracks.entrySet()) {
            ((MonitoredTrack)var8.getValue()).updated = false;
         }
      }
   }

    void postUpdate() {
      for (Entry var2 : this.monitoredVariables.entrySet()) {
         if (((MonitoredVar)var2.getValue()).active && !((MonitoredVar)var2.getValue()).updated) {
            this.addLogLine(
               LogType.VAR,
               "[variable] : removed -> '" + (std::string)var2.getKey() + "', last value: '" + ((MonitoredVar)var2.getValue()).value + "'.",
               col_var_deactivated
            );
            ((MonitoredVar)var2.getValue()).active = false;
         }
      }

      for (int var5 = 0; var5 < this.monitoredLayers.length; var5++) {
    MonitoredLayer var6 = this.monitoredLayers[var5];

         for (Entry var4 : var6.activeNodes.entrySet()) {
            if (((MonitoredNode)var4.getValue()).active && !((MonitoredNode)var4.getValue()).updated) {
               this.addLogLine(
                  LogType.NODE,
                  "[layer][" + var6.index + "] [active_nodes] : deactivated -> '" + ((MonitoredNode)var4.getValue()).name + "'.",
                  col_node_deactivated
               );
               ((MonitoredNode)var4.getValue()).active = false;
            }
         }

         for (Entry var8 : var6.animTracks.entrySet()) {
            if (((MonitoredTrack)var8.getValue()).active && !((MonitoredTrack)var8.getValue()).updated) {
               this.addLogLine(
                  LogType.TRACK,
                  "[layer][" + var6.index + "] [anim_tracks] : deactivated -> '" + ((MonitoredTrack)var8.getValue()).name + "'.",
                  col_track_deactivated
               );
               ((MonitoredTrack)var8.getValue()).active = false;
            }
         }

         if (var6.active && !var6.updated) {
            this.addLogLine(LogType.LAYER, "[layer][" + var5 + "] : deactivated (last animstate: '" + var6.nodeName + "').", col_layer_deactivated);
            var6.active = false;
         }
      }
   }

    void update(IsoGameCharacter var1, AnimLayer[] var2) {
      if (var1 != nullptr) {
         this.ensureLayers(var2);
         this.preUpdate();

         for (IAnimationVariableSlot var4 : var1.getGameVariables()) {
            this.updateVariable(var4.getKey(), var4.getValueString());
         }

         for (std::string var5 : this.customVariables) {
    std::string var6 = var1.getVariableString(var5);
            if (var6 != nullptr) {
               this.updateVariable(var5, var6);
            }
         }

         this.updateCurrentState(var1.getCurrentState() == nullptr ? "nullptr" : var1.getCurrentState().getClass().getSimpleName());

         for (int var8 = 0; var8 < var2.length; var8++) {
            if (var2[var8] != nullptr) {
               this.updateLayer(var8, var2[var8]);
            }
         }

         this.postUpdate();
         this.processQueue();
         this.tickCount++;
      }
   }

    void updateCurrentState(const std::string& var1) {
      if (!this.currentState == var1)) {
         this.queueLogLine("char.currentState changed from '" + this.currentState + "' to: '" + var1 + "'.", col_curstate);
         this.currentState = var1;
      }
   }

    void updateLayer(int var1, AnimLayer var2) {
    MonitoredLayer var3 = this.monitoredLayers[var1];
    std::string var4 = var2.getDebugNodeName();
      if (!var3.active) {
         var3.active = true;
         this.queueLogLine(LogType.LAYER, "[layer][" + var1 + "] activated -> animstate: '" + var4 + "'.", col_layer_activated);
      }

      if (!var3.nodeName == var4)) {
         this.queueLogLine(LogType.LAYER, "[layer][" + var1 + "] changed -> animstate from '" + var3.nodeName + "' to: '" + var4 + "'.", col_layer_nodename);
         var3.nodeName = var4;
      }

      for (LiveAnimNode var6 : var2.getLiveAnimNodes()) {
         this.updateActiveNode(var3, var6.getSourceNode().m_Name);
      }

      if (var2.getAnimationTrack() != nullptr) {
         for (AnimationTrack var8 : var2.getAnimationTrack().getTracks()) {
            if (var8.getLayerIdx() == var1) {
               this.updateAnimTrack(var3, var8.name, var8.BlendDelta);
            }
         }
      }

      var3.updated = true;
   }

    void updateActiveNode(MonitoredLayer var1, const std::string& var2) {
    MonitoredNode var3 = (MonitoredNode)var1.activeNodes.get(var2);
      if (var3 == nullptr) {
         var3 = std::make_shared<MonitoredNode>(this);
         var3.name = var2;
         var1.activeNodes.put(var2, var3);
      }

      if (!var3.active) {
         var3.active = true;
         this.queueLogLine(LogType.NODE, "[layer][" + var1.index + "] [active_nodes] : activated -> '" + var2 + "'.", col_node_activated);
      }

      var3.updated = true;
   }

    void updateAnimTrack(MonitoredLayer var1, const std::string& var2, float var3) {
    MonitoredTrack var4 = (MonitoredTrack)var1.animTracks.get(var2);
      if (var4 == nullptr) {
         var4 = std::make_shared<MonitoredTrack>(this);
         var4.name = var2;
         var4.blendDelta = var3;
         var1.animTracks.put(var2, var4);
      }

      if (!var4.active) {
         var4.active = true;
         this.queueLogLine(LogType.TRACK, "[layer][" + var1.index + "] [anim_tracks] : activated -> '" + var2 + "'.", col_track_activated);
      }

      if (var4.blendDelta != var3) {
         var4.blendDelta = var3;
      }

      var4.updated = true;
   }

    void updateVariable(const std::string& var1, const std::string& var2) {
    MonitoredVar var3 = this.monitoredVariables.get(var1);
    bool var4 = false;
      if (var3 == nullptr) {
         var3 = std::make_shared<MonitoredVar>(this);
         this.monitoredVariables.put(var1, var3);
         var4 = true;
      }

      if (!var3.active) {
         var3.active = true;
         var3.key = var1;
         var3.value = var2;
         this.queueLogLine(LogType.VAR, "[variable] : added -> '" + var1 + "', value: '" + var2 + "'.", col_var_activated);
         if (var4) {
            registerVariable(var1);
         }
      } else if (var2 == nullptr) {
         if (var3.isFloat) {
            var3.isFloat = false;
            this.floatsListDirty = true;
         }

         var3.value = nullptr;
      } else if (var3.value == nullptr || !var3.value == var2)) {
         try {
    float var5 = float.parseFloat(var2);
            var3.logFloat(var5);
            if (!var3.isFloat) {
               var3.isFloat = true;
               this.floatsListDirty = true;
            }
         } catch (NumberFormatException var6) {
            if (var3.isFloat) {
               var3.isFloat = false;
               this.floatsListDirty = true;
            }
         }

         if (!var3.isFloat) {
            this.queueLogLine(LogType.VAR, "[variable] : updated -> '" + var1 + "' changed from '" + var3.value + "' to: '" + var2 + "'.", col_var_changed);
         }

         var3.value = var2;
      }

      var3.updated = true;
   }

    void buildLogString() {
    ListIterator var1 = this.logLines.listIterator(0);
    int var2 = 0;
    int var3 = 0;

      while (var1.hasNext()) {
    MonitorLogLine var4 = (MonitorLogLine)var1.next();
         var3++;
         if (this.logFlags[var4.type.value()]) {
            if (++var2 >= 128) {
               break;
            }
         }
      }

      if (var3 == 0) {
         this.logString = "";
      } else {
         var1 = this.logLines.listIterator(var3);
    std::stringstream var7 = new std::stringstream();

         while (var1.hasPrevious()) {
    MonitorLogLine var5 = (MonitorLogLine)var1.previous();
            if (this.logFlags[var5.type.value()]) {
               var7.append(" <TEXT> ");
               if (this.doTickStamps) {
                  var7.append("[");
                  var7.append(std::string.format("%010d", var5.tick));
                  var7.append("]");
               }

               if (var5.color != nullptr) {
                  var7.append(" <RGB:");
                  var7.append(var5.color.r);
                  var7.append(",");
                  var7.append(var5.color.g);
                  var7.append(",");
                  var7.append(var5.color.b);
                  var7.append("> ");
               }

               var7.append(var5.line);
               var7.append(" <LINE> ");
            }
         }

         this.logString = var7;
         this.hasLogUpdates = false;
         this.hasFilterChanges = false;
      }
   }

    bool IsDirty() {
      return this.hasLogUpdates || this.hasFilterChanges;
   }

    std::string getLogString() {
      if (this.hasLogUpdates || this.hasFilterChanges) {
         this.buildLogString();
      }

      return this.logString;
   }

    bool IsDirtyFloatList() {
      return this.floatsListDirty;
   }

   public std::vector<std::string> getFloatNames() {
      this.floatsListDirty = false;
    std::vector var1 = new std::vector();

      for (Entry var3 : this.monitoredVariables.entrySet()) {
         if (((MonitoredVar)var3.getValue()).isFloat) {
            var1.push_back(((MonitoredVar)var3.getValue()).key);
         }
      }

      Collections.sort(var1);
    return var1;
   }

    static bool isKnownVarsDirty() {
    return knownVarsDirty;
   }

   public static List<std::string> getKnownVariables() {
      knownVarsDirty = false;
      Collections.sort(knownVariables);
    return knownVariables;
   }

    void setSelectedVariable(const std::string& var1) {
      if (var1 == nullptr) {
         this.selectedVariable = nullptr;
      } else {
         this.selectedVariable = this.monitoredVariables.get(var1);
      }
   }

    std::string getSelectedVariable() {
      return this.selectedVariable != nullptr ? this.selectedVariable.key : nullptr;
   }

    float getSelectedVariableFloat() {
      return this.selectedVariable != nullptr ? this.selectedVariable.valFloat : 0.0F;
   }

    std::string getSelectedVarMinFloat() {
      return this.selectedVariable != nullptr && this.selectedVariable.isFloat && this.selectedVariable.f_min != -1.0F ? this.selectedVariable.f_min + "" : "-1.0";
   }

    std::string getSelectedVarMaxFloat() {
      return this.selectedVariable != nullptr && this.selectedVariable.isFloat && this.selectedVariable.f_max != -1.0F ? this.selectedVariable.f_max + "" : "1.0";
   }

   public std::vector<float> getSelectedVarFloatList() {
      if (this.selectedVariable != nullptr && this.selectedVariable.isFloat) {
    MonitoredVar var1 = this.selectedVariable;
    int var2 = var1.f_index - 1;
         if (var2 < 0) {
            var2 = 0;
         }

    float var3 = var1.f_max - var1.f_min;

         for (int var5 = 0; var5 < 1024; var5++) {
    float var4 = (var1.f_floats[var2--] - var1.f_min) / var3;
            this.floatsOut.set(var5, var4);
            if (var2 < 0) {
               var2 = var1.f_floats.length - 1;
            }
         }

         return this.floatsOut;
      } else {
    return nullptr;
      }
   }

    static void registerVariable(const std::string& var0) {
      if (var0 != nullptr) {
         var0 = var0.toLowerCase();
         if (!knownVariables.contains(var0)) {
            knownVariables.push_back(var0);
            knownVarsDirty = true;
         }
      }
   }

    void ensureLayers(AnimLayer[] var1) {
    int var2 = var1.length;
      if (this.monitoredLayers == nullptr || this.monitoredLayers.length != var2) {
         this.monitoredLayers = new MonitoredLayer[var2];

         for (int var3 = 0; var3 < var2; var3++) {
            this.monitoredLayers[var3] = std::make_shared<MonitoredLayer>(this, var3);
         }
      }
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
