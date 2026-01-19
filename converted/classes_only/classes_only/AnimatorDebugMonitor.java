package zombie.core.skinnedmodel.advancedanimation.debug;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Queue;
import java.util.Map.Entry;
import zombie.characters.IsoGameCharacter;
import zombie.core.Color;
import zombie.core.Colors;
import zombie.core.skinnedmodel.advancedanimation.AnimLayer;
import zombie.core.skinnedmodel.advancedanimation.IAnimationVariableSlot;
import zombie.core.skinnedmodel.advancedanimation.LiveAnimNode;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.LogType;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitorLogLine;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredLayer;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredNode;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredTrack;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredVar;
import zombie.core.skinnedmodel.animation.AnimationTrack;

public final class AnimatorDebugMonitor {
   private static final ArrayList<String> knownVariables = new ArrayList<>();
   private static boolean knownVarsDirty = false;
   private String currentState = "null";
   private MonitoredLayer[] monitoredLayers;
   private final HashMap<String, MonitoredVar> monitoredVariables = new HashMap<>();
   private final ArrayList<String> customVariables = new ArrayList<>();
   private final LinkedList<MonitorLogLine> logLines = new LinkedList<>();
   private final Queue<MonitorLogLine> logLineQueue = new LinkedList<>();
   private boolean floatsListDirty = false;
   private boolean hasFilterChanges = false;
   private boolean hasLogUpdates = false;
   private String logString = "";
   private static final int maxLogSize = 1028;
   private static final int maxOutputLines = 128;
   private static final int maxFloatCache = 1024;
   private final ArrayList<Float> floatsOut = new ArrayList<>();
   private MonitoredVar selectedVariable;
   private int tickCount = 0;
   private boolean doTickStamps = false;
   private static final int tickStampLength = 10;
   private static final Color col_curstate = Colors.Cyan;
   private static final Color col_layer_nodename = Colors.CornFlowerBlue;
   private static final Color col_layer_activated = Colors.DarkTurquoise;
   private static final Color col_layer_deactivated = Colors.Orange;
   private static final Color col_track_activated = Colors.SandyBrown;
   private static final Color col_track_deactivated = Colors.Salmon;
   private static final Color col_node_activated = Colors.Pink;
   private static final Color col_node_deactivated = Colors.Plum;
   private static final Color col_var_activated = Colors.Chartreuse;
   private static final Color col_var_changed = Colors.LimeGreen;
   private static final Color col_var_deactivated = Colors.Gold;
   private static final String TAG_VAR = "[variable]";
   private static final String TAG_LAYER = "[layer]";
   private static final String TAG_NODE = "[active_nodes]";
   private static final String TAG_TRACK = "[anim_tracks]";
   private boolean[] logFlags = new boolean[LogType.MAX.value()];

   public AnimatorDebugMonitor(IsoGameCharacter var1) {
      this.logFlags[LogType.DEFAULT.value()] = true;

      for (int var2 = 0; var2 < this.logFlags.length; var2++) {
         this.logFlags[var2] = true;
      }

      for (int var5 = 0; var5 < 1024; var5++) {
         this.floatsOut.add(0.0F);
      }

      this.initCustomVars();
      if (var1 != null && var1.advancedAnimator != null) {
         for (String var4 : var1.advancedAnimator.debugGetVariables()) {
            registerVariable(var4);
         }
      }
   }

   private void initCustomVars() {
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

   public void addCustomVariable(String var1) {
      String var2 = var1.toLowerCase();
      if (!this.customVariables.contains(var2)) {
         this.customVariables.add(var2);
      }

      registerVariable(var1);
   }

   public void removeCustomVariable(String var1) {
      String var2 = var1.toLowerCase();
      this.customVariables.remove(var2);
   }

   public void setFilter(int var1, boolean var2) {
      if (var1 >= 0 && var1 < LogType.MAX.value()) {
         this.logFlags[var1] = var2;
         this.hasFilterChanges = true;
      }
   }

   public boolean getFilter(int var1) {
      return var1 >= 0 && var1 < LogType.MAX.value() ? this.logFlags[var1] : false;
   }

   public boolean isDoTickStamps() {
      return this.doTickStamps;
   }

   public void setDoTickStamps(boolean var1) {
      if (this.doTickStamps != var1) {
         this.doTickStamps = var1;
         this.hasFilterChanges = true;
      }
   }

   private void queueLogLine(String var1) {
      this.addLogLine(LogType.DEFAULT, var1, null, true);
   }

   private void queueLogLine(String var1, Color var2) {
      this.addLogLine(LogType.DEFAULT, var1, var2, true);
   }

   private void queueLogLine(LogType var1, String var2, Color var3) {
      this.addLogLine(var1, var2, var3, true);
   }

   private void addLogLine(String var1) {
      this.addLogLine(LogType.DEFAULT, var1, null, false);
   }

   private void addLogLine(String var1, Color var2) {
      this.addLogLine(LogType.DEFAULT, var1, var2, false);
   }

   private void addLogLine(String var1, Color var2, boolean var3) {
      this.addLogLine(LogType.DEFAULT, var1, var2, var3);
   }

   private void addLogLine(LogType var1, String var2, Color var3) {
      this.addLogLine(var1, var2, var3, false);
   }

   private void addLogLine(LogType var1, String var2, Color var3, boolean var4) {
      MonitorLogLine var5 = new MonitorLogLine(this);
      var5.line = var2;
      var5.color = var3;
      var5.type = var1;
      var5.tick = this.tickCount;
      if (var4) {
         this.logLineQueue.add(var5);
      } else {
         this.log(var5);
      }
   }

   private void log(MonitorLogLine var1) {
      this.logLines.addFirst(var1);
      if (this.logLines.size() > 1028) {
         this.logLines.removeLast();
      }

      this.hasLogUpdates = true;
   }

   private void processQueue() {
      while (this.logLineQueue.size() > 0) {
         MonitorLogLine var1 = this.logLineQueue.poll();
         this.log(var1);
      }
   }

   private void preUpdate() {
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

   private void postUpdate() {
      for (Entry var2 : this.monitoredVariables.entrySet()) {
         if (((MonitoredVar)var2.getValue()).active && !((MonitoredVar)var2.getValue()).updated) {
            this.addLogLine(
               LogType.VAR,
               "[variable] : removed -> '" + (String)var2.getKey() + "', last value: '" + ((MonitoredVar)var2.getValue()).value + "'.",
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

   public void update(IsoGameCharacter var1, AnimLayer[] var2) {
      if (var1 != null) {
         this.ensureLayers(var2);
         this.preUpdate();

         for (IAnimationVariableSlot var4 : var1.getGameVariables()) {
            this.updateVariable(var4.getKey(), var4.getValueString());
         }

         for (String var5 : this.customVariables) {
            String var6 = var1.getVariableString(var5);
            if (var6 != null) {
               this.updateVariable(var5, var6);
            }
         }

         this.updateCurrentState(var1.getCurrentState() == null ? "null" : var1.getCurrentState().getClass().getSimpleName());

         for (int var8 = 0; var8 < var2.length; var8++) {
            if (var2[var8] != null) {
               this.updateLayer(var8, var2[var8]);
            }
         }

         this.postUpdate();
         this.processQueue();
         this.tickCount++;
      }
   }

   private void updateCurrentState(String var1) {
      if (!this.currentState.equals(var1)) {
         this.queueLogLine("Character.currentState changed from '" + this.currentState + "' to: '" + var1 + "'.", col_curstate);
         this.currentState = var1;
      }
   }

   private void updateLayer(int var1, AnimLayer var2) {
      MonitoredLayer var3 = this.monitoredLayers[var1];
      String var4 = var2.getDebugNodeName();
      if (!var3.active) {
         var3.active = true;
         this.queueLogLine(LogType.LAYER, "[layer][" + var1 + "] activated -> animstate: '" + var4 + "'.", col_layer_activated);
      }

      if (!var3.nodeName.equals(var4)) {
         this.queueLogLine(LogType.LAYER, "[layer][" + var1 + "] changed -> animstate from '" + var3.nodeName + "' to: '" + var4 + "'.", col_layer_nodename);
         var3.nodeName = var4;
      }

      for (LiveAnimNode var6 : var2.getLiveAnimNodes()) {
         this.updateActiveNode(var3, var6.getSourceNode().m_Name);
      }

      if (var2.getAnimationTrack() != null) {
         for (AnimationTrack var8 : var2.getAnimationTrack().getTracks()) {
            if (var8.getLayerIdx() == var1) {
               this.updateAnimTrack(var3, var8.name, var8.BlendDelta);
            }
         }
      }

      var3.updated = true;
   }

   private void updateActiveNode(MonitoredLayer var1, String var2) {
      MonitoredNode var3 = (MonitoredNode)var1.activeNodes.get(var2);
      if (var3 == null) {
         var3 = new MonitoredNode(this);
         var3.name = var2;
         var1.activeNodes.put(var2, var3);
      }

      if (!var3.active) {
         var3.active = true;
         this.queueLogLine(LogType.NODE, "[layer][" + var1.index + "] [active_nodes] : activated -> '" + var2 + "'.", col_node_activated);
      }

      var3.updated = true;
   }

   private void updateAnimTrack(MonitoredLayer var1, String var2, float var3) {
      MonitoredTrack var4 = (MonitoredTrack)var1.animTracks.get(var2);
      if (var4 == null) {
         var4 = new MonitoredTrack(this);
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

   private void updateVariable(String var1, String var2) {
      MonitoredVar var3 = this.monitoredVariables.get(var1);
      boolean var4 = false;
      if (var3 == null) {
         var3 = new MonitoredVar(this);
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
      } else if (var2 == null) {
         if (var3.isFloat) {
            var3.isFloat = false;
            this.floatsListDirty = true;
         }

         var3.value = null;
      } else if (var3.value == null || !var3.value.equals(var2)) {
         try {
            float var5 = Float.parseFloat(var2);
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

   private void buildLogString() {
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
         StringBuilder var7 = new StringBuilder();

         while (var1.hasPrevious()) {
            MonitorLogLine var5 = (MonitorLogLine)var1.previous();
            if (this.logFlags[var5.type.value()]) {
               var7.append(" <TEXT> ");
               if (this.doTickStamps) {
                  var7.append("[");
                  var7.append(String.format("%010d", var5.tick));
                  var7.append("]");
               }

               if (var5.color != null) {
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

         this.logString = var7.toString();
         this.hasLogUpdates = false;
         this.hasFilterChanges = false;
      }
   }

   public boolean IsDirty() {
      return this.hasLogUpdates || this.hasFilterChanges;
   }

   public String getLogString() {
      if (this.hasLogUpdates || this.hasFilterChanges) {
         this.buildLogString();
      }

      return this.logString;
   }

   public boolean IsDirtyFloatList() {
      return this.floatsListDirty;
   }

   public ArrayList<String> getFloatNames() {
      this.floatsListDirty = false;
      ArrayList var1 = new ArrayList();

      for (Entry var3 : this.monitoredVariables.entrySet()) {
         if (((MonitoredVar)var3.getValue()).isFloat) {
            var1.add(((MonitoredVar)var3.getValue()).key);
         }
      }

      Collections.sort(var1);
      return var1;
   }

   public static boolean isKnownVarsDirty() {
      return knownVarsDirty;
   }

   public static List<String> getKnownVariables() {
      knownVarsDirty = false;
      Collections.sort(knownVariables);
      return knownVariables;
   }

   public void setSelectedVariable(String var1) {
      if (var1 == null) {
         this.selectedVariable = null;
      } else {
         this.selectedVariable = this.monitoredVariables.get(var1);
      }
   }

   public String getSelectedVariable() {
      return this.selectedVariable != null ? this.selectedVariable.key : null;
   }

   public float getSelectedVariableFloat() {
      return this.selectedVariable != null ? this.selectedVariable.valFloat : 0.0F;
   }

   public String getSelectedVarMinFloat() {
      return this.selectedVariable != null && this.selectedVariable.isFloat && this.selectedVariable.f_min != -1.0F ? this.selectedVariable.f_min + "" : "-1.0";
   }

   public String getSelectedVarMaxFloat() {
      return this.selectedVariable != null && this.selectedVariable.isFloat && this.selectedVariable.f_max != -1.0F ? this.selectedVariable.f_max + "" : "1.0";
   }

   public ArrayList<Float> getSelectedVarFloatList() {
      if (this.selectedVariable != null && this.selectedVariable.isFloat) {
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
         return null;
      }
   }

   public static void registerVariable(String var0) {
      if (var0 != null) {
         var0 = var0.toLowerCase();
         if (!knownVariables.contains(var0)) {
            knownVariables.add(var0);
            knownVarsDirty = true;
         }
      }
   }

   private void ensureLayers(AnimLayer[] var1) {
      int var2 = var1.length;
      if (this.monitoredLayers == null || this.monitoredLayers.length != var2) {
         this.monitoredLayers = new MonitoredLayer[var2];

         for (int var3 = 0; var3 < var2; var3++) {
            this.monitoredLayers[var3] = new MonitoredLayer(this, var3);
         }
      }
   }
}
