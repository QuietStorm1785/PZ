package zombie.core.skinnedmodel;

import org.lwjgl.util.vector.Matrix4f;

public class HelperFunctions$TransformResult_QPS {
   public final Matrix4f result;
   final Matrix4f trans;
   final Matrix4f rot;
   final Matrix4f scl;

   public HelperFunctions$TransformResult_QPS() {
      this.result = new Matrix4f();
      this.trans = new Matrix4f();
      this.rot = new Matrix4f();
      this.scl = new Matrix4f();
   }

   public HelperFunctions$TransformResult_QPS(Matrix4f var1) {
      this.result = var1;
      this.trans = new Matrix4f();
      this.rot = new Matrix4f();
      this.scl = new Matrix4f();
   }
}
