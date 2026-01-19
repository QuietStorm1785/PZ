package zombie.core.skinnedmodel.animation;

import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector3f;
import zombie.core.skinnedmodel.HelperFunctions;
import zombie.core.skinnedmodel.animation.ModelTransformSampler.L_updateBoneAnimationTransform;
import zombie.core.skinnedmodel.model.SkinningBone;
import zombie.core.skinnedmodel.model.SkinningData;
import zombie.debug.DebugOptions;
import zombie.util.Pool;
import zombie.util.PooledObject;
import zombie.util.list.PZArrayUtil;

public class ModelTransformSampler extends PooledObject implements AnimTrackSampler {
   private AnimationPlayer m_sourceAnimPlayer;
   private AnimationTrack m_track;
   private float m_currentTime = 0.0F;
   private SkinningData m_skinningData;
   private BoneTransform[] m_boneTransforms;
   private Matrix4f[] m_boneModelTransforms;
   private static final Pool<ModelTransformSampler> s_pool = new Pool(ModelTransformSampler::new);

   private void init(AnimationPlayer var1, AnimationTrack var2) {
      this.m_sourceAnimPlayer = var1;
      this.m_track = AnimationTrack.createClone(var2, AnimationTrack::alloc);
      SkinningData var3 = this.m_sourceAnimPlayer.getSkinningData();
      int var4 = var3.numBones();
      this.m_skinningData = var3;
      this.m_boneModelTransforms = (Matrix4f[])PZArrayUtil.newInstance(Matrix4f.class, this.m_boneModelTransforms, var4, Matrix4f::new);
      this.m_boneTransforms = (BoneTransform[])PZArrayUtil.newInstance(BoneTransform.class, this.m_boneTransforms, var4, BoneTransform::alloc);
   }

   public static ModelTransformSampler alloc(AnimationPlayer var0, AnimationTrack var1) {
      ModelTransformSampler var2 = (ModelTransformSampler)s_pool.alloc();
      var2.init(var0, var1);
      return var2;
   }

   public void onReleased() {
      this.m_sourceAnimPlayer = null;
      this.m_track = (AnimationTrack)Pool.tryRelease(this.m_track);
      this.m_skinningData = null;
      this.m_boneTransforms = (BoneTransform[])Pool.tryRelease(this.m_boneTransforms);
   }

   public float getTotalTime() {
      return this.m_track.getDuration();
   }

   public boolean isLooped() {
      return this.m_track.isLooping();
   }

   public void moveToTime(float var1) {
      this.m_currentTime = var1;
      this.m_track.setCurrentTimeValue(var1);
      this.m_track.Update(0.0F);

      for (int var2 = 0; var2 < this.m_boneTransforms.length; var2++) {
         this.updateBoneAnimationTransform(var2);
      }
   }

   private void updateBoneAnimationTransform(int var1) {
      Vector3f var2 = L_updateBoneAnimationTransform.pos;
      Quaternion var3 = L_updateBoneAnimationTransform.rot;
      Vector3f var4 = L_updateBoneAnimationTransform.scale;
      Keyframe var5 = L_updateBoneAnimationTransform.key;
      AnimationBoneBinding var6 = this.m_sourceAnimPlayer.getCounterRotationBone();
      boolean var7 = var6 != null && var6.getBone() != null && var6.getBone().Index == var1;
      var5.setIdentity();
      AnimationTrack var8 = this.m_track;
      this.getTrackTransform(var1, var8, var2, var3, var4);
      if (var7 && var8.getUseDeferredRotation()) {
         if (DebugOptions.instance.Character.Debug.Animate.ZeroCounterRotationBone.getValue()) {
            Vector3f var9 = L_updateBoneAnimationTransform.rotAxis;
            Matrix4f var10 = L_updateBoneAnimationTransform.rotMat;
            var10.setIdentity();
            var9.set(0.0F, 1.0F, 0.0F);
            var10.rotate((float) (-Math.PI / 2), var9);
            var9.set(1.0F, 0.0F, 0.0F);
            var10.rotate((float) (-Math.PI / 2), var9);
            HelperFunctions.getRotation(var10, var3);
         } else {
            Vector3f var11 = HelperFunctions.ToEulerAngles(var3, L_updateBoneAnimationTransform.rotEulers);
            HelperFunctions.ToQuaternion(var11.x, var11.y, (float) (Math.PI / 2), var3);
         }
      }

      boolean var12 = var8.getDeferredMovementBoneIdx() == var1;
      if (var12) {
         Vector3f var13 = var8.getCurrentDeferredCounterPosition(L_updateBoneAnimationTransform.deferredPos);
         var2.x = var2.x + var13.x;
         var2.y = var2.y + var13.y;
         var2.z = var2.z + var13.z;
      }

      var5.Position.set(var2);
      var5.Rotation.set(var3);
      var5.Scale.set(var4);
      this.m_boneTransforms[var1].set(var5.Position, var5.Rotation, var5.Scale);
   }

   private void getTrackTransform(int var1, AnimationTrack var2, Vector3f var3, Quaternion var4, Vector3f var5) {
      var2.get(var1, var3, var4, var5);
   }

   public float getCurrentTime() {
      return this.m_currentTime;
   }

   public void getBoneMatrix(int var1, Matrix4f var2) {
      if (var1 == 0) {
         this.m_boneTransforms[0].getMatrix(this.m_boneModelTransforms[0]);
         var2.load(this.m_boneModelTransforms[0]);
      } else {
         SkinningBone var3 = this.m_skinningData.getBoneAt(var1);
         SkinningBone var4 = var3.Parent;
         BoneTransform.mul(this.m_boneTransforms[var3.Index], this.m_boneModelTransforms[var4.Index], this.m_boneModelTransforms[var3.Index]);
         var2.load(this.m_boneModelTransforms[var3.Index]);
      }
   }

   public int getNumBones() {
      return this.m_skinningData.numBones();
   }
}
