package zombie.core.skinnedmodel.advancedanimation.debug;

import java.util.HashMap;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredNode;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor.MonitoredTrack;

class AnimatorDebugMonitor$MonitoredLayer {
   int index;
   String nodeName;
   HashMap<String, MonitoredNode> activeNodes;
   HashMap<String, MonitoredTrack> animTracks;
   boolean active;
   boolean updated;

   public AnimatorDebugMonitor$MonitoredLayer(AnimatorDebugMonitor var1, int var2) {
      this.this$0 = var1;
      this.nodeName = "";
      this.activeNodes = new HashMap<>();
      this.animTracks = new HashMap<>();
      this.active = false;
      this.updated = false;
      this.index = var2;
   }
}
