package zombie.core.skinnedmodel.animation;

import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector3f;
import org.lwjgl.util.vector.Vector4f;

final class AnimationPlayer$L_updateBoneAnimationTransform {
   static final Quaternion rot = new Quaternion();
   static final Vector3f pos = new Vector3f();
   static final Vector3f scale = new Vector3f();
   static final Keyframe key = new Keyframe(new Vector3f(0.0F, 0.0F, 0.0F), new Quaternion(0.0F, 0.0F, 0.0F, 1.0F), new Vector3f(1.0F, 1.0F, 1.0F));
   static final Matrix4f boneMat = new Matrix4f();
   static final Matrix4f rotMat = new Matrix4f();
   static final Vector3f rotAxis = new Vector3f(1.0F, 0.0F, 0.0F);
   static final Quaternion crRot = new Quaternion();
   static final Vector4f crRotAA = new Vector4f();
   static final Matrix4f crMat = new Matrix4f();
   static final Vector3f rotEulers = new Vector3f();
   static final Vector3f deferredPos = new Vector3f();

   private AnimationPlayer$L_updateBoneAnimationTransform() {
   }
}
