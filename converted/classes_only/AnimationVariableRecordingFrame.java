package zombie.core.skinnedmodel.animation.debug;

import zombie.core.skinnedmodel.advancedanimation.IAnimationVariableSlot;
import zombie.core.skinnedmodel.advancedanimation.IAnimationVariableSource;
import zombie.debug.DebugLog;
import zombie.util.list.PZArrayUtil;

public final class AnimationVariableRecordingFrame extends GenericNameValueRecordingFrame {
   private String[] m_variableValues = new String[0];

   public AnimationVariableRecordingFrame(String var1) {
      super(var1, "_values");
   }

   public void logVariables(IAnimationVariableSource var1) {
      for (IAnimationVariableSlot var3 : var1.getGameVariables()) {
         this.logVariable(var3.getKey(), var3.getValueString());
      }
   }

   protected void onColumnAdded() {
      this.m_variableValues = (String[])PZArrayUtil.add(this.m_variableValues, null);
   }

   public void logVariable(String var1, String var2) {
      int var3 = this.getOrCreateColumn(var1);
      if (this.m_variableValues[var3] != null) {
         DebugLog.General.error("Value for %s already set: %f, new value: %f", new Object[]{var1, this.m_variableValues[var3], var2});
      }

      this.m_variableValues[var3] = var2;
   }

   public String getValueAt(int var1) {
      return this.m_variableValues[var1];
   }

   public void reset() {
      int var1 = 0;

      for (int var2 = this.m_variableValues.length; var1 < var2; var1++) {
         this.m_variableValues[var1] = null;
      }
   }
}
