package zombie.core.skinnedmodel.animation;

import org.lwjgl.util.vector.Matrix4f;
import zombie.core.skinnedmodel.model.SkinningData;
import zombie.util.Pool;
import zombie.util.PooledObject;
import zombie.util.list.PZArrayUtil;

class AnimationPlayer$SkinTransformData extends PooledObject {
   public Matrix4f[] transforms;
   private SkinningData m_skinnedTo;
   public boolean dirty;
   private AnimationPlayer$SkinTransformData m_next;
   private static Pool<AnimationPlayer$SkinTransformData> s_pool = new Pool(AnimationPlayer$SkinTransformData::new);

   private AnimationPlayer$SkinTransformData() {
   }

   public void setSkinnedTo(SkinningData var1) {
      if (this.m_skinnedTo != var1) {
         this.dirty = true;
         this.m_skinnedTo = var1;
         this.transforms = (Matrix4f[])PZArrayUtil.newInstance(Matrix4f.class, this.transforms, var1.numBones(), Matrix4f::new);
      }
   }

   public static AnimationPlayer$SkinTransformData alloc(SkinningData var0) {
      AnimationPlayer$SkinTransformData var1 = (AnimationPlayer$SkinTransformData)s_pool.alloc();
      var1.setSkinnedTo(var0);
      var1.dirty = true;
      return var1;
   }
}
