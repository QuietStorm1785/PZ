package zombie.core.skinnedmodel.runtime;

import java.util.List;
import zombie.core.math.PZMath;
import zombie.core.skinnedmodel.ModelManager;
import zombie.core.skinnedmodel.animation.AnimationClip;
import zombie.core.skinnedmodel.animation.Keyframe;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;

public final class CopyFrame implements IRuntimeAnimationCommand {
   protected int m_frame;
   protected int m_FPS = 30;
   protected String m_source;
   protected int m_sourceFrame;
   protected int m_sourceFPS = 30;

   public void parse(Block var1) {
      for (Value var3 : var1.values) {
         String var4 = var3.getKey().trim();
         String var5 = var3.getValue().trim();
         if ("source".equalsIgnoreCase(var4)) {
            this.m_source = var5;
         } else if ("frame".equalsIgnoreCase(var4)) {
            this.m_frame = PZMath.tryParseInt(var5, 1);
         } else if ("sourceFrame".equalsIgnoreCase(var4)) {
            this.m_sourceFrame = PZMath.tryParseInt(var5, 1);
         }
      }
   }

   public void exec(List<Keyframe> var1) {
      AnimationClip var2 = ModelManager.instance.getAnimationClip(this.m_source);

      for (int var3 = 0; var3 < 60; var3++) {
         Keyframe[] var4 = var2.getBoneFramesAt(var3);
         if (var4.length != 0) {
            Keyframe var5 = var4[0];
            Keyframe var6 = new Keyframe();
            var6.Bone = var5.Bone;
            var6.BoneName = var5.BoneName;
            var6.Time = (float)(this.m_frame - 1) / this.m_FPS;
            var6.Position = KeyframeUtil.GetKeyFramePosition(var4, (float)(this.m_sourceFrame - 1) / this.m_sourceFPS, var2.Duration);
            var6.Rotation = KeyframeUtil.GetKeyFrameRotation(var4, (float)(this.m_sourceFrame - 1) / this.m_sourceFPS, var2.Duration);
            var6.Scale = var5.Scale;
            var1.add(var6);
         }
      }
   }
}
