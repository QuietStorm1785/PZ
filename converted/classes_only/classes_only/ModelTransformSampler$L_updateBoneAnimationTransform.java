package zombie.core.skinnedmodel.animation;

import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector3f;

public class ModelTransformSampler$L_updateBoneAnimationTransform {
   public static final Vector3f pos = new Vector3f();
   public static final Quaternion rot = new Quaternion();
   public static final Vector3f scale = new Vector3f();
   public static final Keyframe key = new Keyframe(new Vector3f(0.0F, 0.0F, 0.0F), new Quaternion(0.0F, 0.0F, 0.0F, 1.0F), new Vector3f(1.0F, 1.0F, 1.0F));
   public static final Vector3f rotAxis = new Vector3f();
   public static final Matrix4f rotMat = new Matrix4f();
   public static final Vector3f rotEulers = new Vector3f();
   public static final Vector3f deferredPos = new Vector3f();
}
