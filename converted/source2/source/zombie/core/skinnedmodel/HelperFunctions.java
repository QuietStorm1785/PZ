package zombie.core.skinnedmodel;

import java.util.List;
import java.util.Stack;
import java.util.concurrent.atomic.AtomicBoolean;
import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector3f;
import org.lwjgl.util.vector.Vector4f;
import zombie.core.Color;
import zombie.core.math.PZMath;
import zombie.core.skinnedmodel.HelperFunctions.TransformResult_QPS;
import zombie.core.skinnedmodel.HelperFunctions.UnitTests;
import zombie.core.skinnedmodel.model.VertexPositionNormalTangentTextureSkin;
import zombie.popman.ObjectPool;

public final class HelperFunctions {
   private static final Vector3f s_zero3 = new Vector3f(0.0F, 0.0F, 0.0F);
   private static final Quaternion s_identityQ = new Quaternion();
   private static final Stack<Matrix4f> MatrixStack = new Stack<>();
   private static final AtomicBoolean MatrixLock = new AtomicBoolean(false);
   private static final ObjectPool<Vector3f> VectorPool = new ObjectPool(Vector3f::new);

   public static int ToRgba(Color var0) {
      return (int)var0.a << 24 | (int)var0.b << 16 | (int)var0.g << 8 | (int)var0.r;
   }

   public static void returnMatrix(Matrix4f var0) {
      while (!MatrixLock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      assert !MatrixStack.contains(var0);

      MatrixStack.push(var0);
      MatrixLock.set(false);
   }

   public static Matrix4f getMatrix() {
      Matrix4f var0 = null;

      while (!MatrixLock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      if (MatrixStack.isEmpty()) {
         var0 = new Matrix4f();
      } else {
         var0 = MatrixStack.pop();
      }

      MatrixLock.set(false);
      return var0;
   }

   public static Matrix4f getMatrix(Matrix4f var0) {
      Matrix4f var1 = getMatrix();
      var1.load(var0);
      return var1;
   }

   public static Vector3f getVector3f() {
      while (!MatrixLock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      Vector3f var0 = (Vector3f)VectorPool.alloc();
      MatrixLock.set(false);
      return var0;
   }

   public static void returnVector3f(Vector3f var0) {
      while (!MatrixLock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      VectorPool.release(var0);
      MatrixLock.set(false);
   }

   public static Matrix4f CreateFromQuaternion(Quaternion var0) {
      Matrix4f var1 = getMatrix();
      CreateFromQuaternion(var0, var1);
      return var1;
   }

   public static Matrix4f CreateFromQuaternion(Quaternion var0, Matrix4f var1) {
      var1.setIdentity();
      float var2 = var0.lengthSquared();
      if (var2 > 0.0F && var2 < 0.99999F || var2 > 1.00001F) {
         float var3 = (float)Math.sqrt(var2);
         float var4 = 1.0F / var3;
         var0.scale(var4);
      }

      float var12 = var0.x * var0.x;
      float var13 = var0.x * var0.y;
      float var5 = var0.x * var0.z;
      float var6 = var0.x * var0.w;
      float var7 = var0.y * var0.y;
      float var8 = var0.y * var0.z;
      float var9 = var0.y * var0.w;
      float var10 = var0.z * var0.z;
      float var11 = var0.z * var0.w;
      var1.m00 = 1.0F - 2.0F * (var7 + var10);
      var1.m10 = 2.0F * (var13 - var11);
      var1.m20 = 2.0F * (var5 + var9);
      var1.m30 = 0.0F;
      var1.m01 = 2.0F * (var13 + var11);
      var1.m11 = 1.0F - 2.0F * (var12 + var10);
      var1.m21 = 2.0F * (var8 - var6) * 1.0F;
      var1.m31 = 0.0F;
      var1.m02 = 2.0F * (var5 - var9);
      var1.m12 = 2.0F * (var8 + var6);
      var1.m22 = 1.0F - 2.0F * (var12 + var7);
      var1.m32 = 0.0F;
      var1.m03 = 0.0F;
      var1.m13 = 0.0F;
      var1.m23 = 0.0F;
      var1.m33 = 1.0F;
      var1.m30 = 0.0F;
      var1.m31 = 0.0F;
      var1.m32 = 0.0F;
      var1.transpose();
      return var1;
   }

   public static Matrix4f CreateFromQuaternionPositionScale(Vector3f var0, Quaternion var1, Vector3f var2, Matrix4f var3) {
      Matrix4f var4 = getMatrix();
      Matrix4f var5 = getMatrix();
      Matrix4f var6 = getMatrix();
      CreateFromQuaternionPositionScale(var0, var1, var2, var3, var5, var6, var4);
      returnMatrix(var4);
      returnMatrix(var5);
      returnMatrix(var6);
      return var3;
   }

   public static void CreateFromQuaternionPositionScale(Vector3f var0, Quaternion var1, Vector3f var2, TransformResult_QPS var3) {
      CreateFromQuaternionPositionScale(var0, var1, var2, var3.result, var3.trans, var3.rot, var3.scl);
   }

   private static void CreateFromQuaternionPositionScale(
      Vector3f var0, Quaternion var1, Vector3f var2, Matrix4f var3, Matrix4f var4, Matrix4f var5, Matrix4f var6
   ) {
      var6.setIdentity();
      var6.scale(var2);
      var4.setIdentity();
      var4.translate(var0);
      var4.transpose();
      CreateFromQuaternion(var1, var5);
      Matrix4f.mul(var6, var5, var5);
      Matrix4f.mul(var5, var4, var3);
   }

   public static void TransformVertices(VertexPositionNormalTangentTextureSkin[] var0, List<Matrix4f> var1) {
      Vector3 var2 = new Vector3();
      Vector3 var3 = new Vector3();
      Vector4f var4 = new Vector4f();

      for (VertexPositionNormalTangentTextureSkin var8 : var0) {
         var2.reset();
         var3.reset();
         Vector3 var9 = var8.Position;
         Vector3 var10 = var8.Normal;
         ApplyBlendBone(var8.BlendWeights.x, (Matrix4f)var1.get(var8.BlendIndices.X), var9, var10, var4, var2, var3);
         ApplyBlendBone(var8.BlendWeights.y, (Matrix4f)var1.get(var8.BlendIndices.Y), var9, var10, var4, var2, var3);
         ApplyBlendBone(var8.BlendWeights.z, (Matrix4f)var1.get(var8.BlendIndices.Z), var9, var10, var4, var2, var3);
         ApplyBlendBone(var8.BlendWeights.w, (Matrix4f)var1.get(var8.BlendIndices.W), var9, var10, var4, var2, var3);
         var9.set(var2);
         var10.set(var3);
      }
   }

   public static void ApplyBlendBone(float var0, Matrix4f var1, Vector3 var2, Vector3 var3, Vector4f var4, Vector3 var5, Vector3 var6) {
      if (var0 > 0.0F) {
         float var10 = var2.x();
         float var11 = var2.y();
         float var12 = var2.z();
         float var7 = var1.m00 * var10 + var1.m01 * var11 + var1.m02 * var12 + var1.m03;
         float var8 = var1.m10 * var10 + var1.m11 * var11 + var1.m12 * var12 + var1.m13;
         float var9 = var1.m20 * var10 + var1.m21 * var11 + var1.m22 * var12 + var1.m23;
         var5.add(var7 * var0, var8 * var0, var9 * var0);
         var10 = var3.x();
         var11 = var3.y();
         var12 = var3.z();
         var7 = var1.m00 * var10 + var1.m01 * var11 + var1.m02 * var12;
         var8 = var1.m10 * var10 + var1.m11 * var11 + var1.m12 * var12;
         var9 = var1.m20 * var10 + var1.m21 * var11 + var1.m22 * var12;
         var6.add(var7 * var0, var8 * var0, var9 * var0);
      }
   }

   public static Vector3f getPosition(Matrix4f var0, Vector3f var1) {
      var1.set(var0.m03, var0.m13, var0.m23);
      return var1;
   }

   public static void setPosition(Matrix4f var0, Vector3f var1) {
      var0.m03 = var1.x;
      var0.m13 = var1.y;
      var0.m23 = var1.z;
   }

   public static Quaternion getRotation(Matrix4f var0, Quaternion var1) {
      return Quaternion.setFromMatrix(var0, var1);
   }

   public static void transform(Quaternion var0, Vector3f var1, Vector3f var2) {
      var0.normalise();
      float var3 = var0.w;
      float var4 = var0.x;
      float var5 = var0.y;
      float var6 = var0.z;
      float var7 = var3 * var3;
      float var8 = var4 * var4 + var5 * var5 + var6 * var6;
      float var9 = var1.x;
      float var10 = var1.y;
      float var11 = var1.z;
      float var12 = var5 * var11 - var6 * var10;
      float var13 = var6 * var9 - var4 * var11;
      float var14 = var4 * var10 - var5 * var9;
      float var15 = var9 * var4 + var10 * var5 + var11 * var6;
      float var16 = (var7 - var8) * var9 + 2.0F * var3 * var12 + 2.0F * var4 * var15;
      float var17 = (var7 - var8) * var10 + 2.0F * var3 * var13 + 2.0F * var5 * var15;
      float var18 = (var7 - var8) * var11 + 2.0F * var3 * var14 + 2.0F * var6 * var15;
      var2.set(var16, var17, var18);
   }

   private static Vector4f transform(Matrix4f var0, Vector4f var1, Vector4f var2) {
      float var3 = var0.m00 * var1.x + var0.m01 * var1.y + var0.m02 * var1.z + var0.m30 * var1.w;
      float var4 = var0.m10 * var1.x + var0.m11 * var1.y + var0.m12 * var1.z + var0.m31 * var1.w;
      float var5 = var0.m20 * var1.x + var0.m21 * var1.y + var0.m22 * var1.z + var0.m32 * var1.w;
      float var6 = var0.m03 * var1.x + var0.m13 * var1.y + var0.m23 * var1.z + var0.m33 * var1.w;
      var2.x = var3;
      var2.y = var4;
      var2.z = var5;
      var2.w = var6;
      return var2;
   }

   public static float getRotationY(Quaternion var0) {
      var0.normalise();
      float var1 = var0.w;
      float var2 = var0.x;
      float var3 = var0.y;
      float var4 = var0.z;
      float var5 = var1 * var1;
      float var6 = var2 * var2 + var3 * var3 + var4 * var4;
      float var7 = var3 * 0.0F - var4 * 0.0F;
      float var8 = var2 * 0.0F - var3 * 1.0F;
      float var9 = 1.0F * var2 + 0.0F * var3 + 0.0F * var4;
      float var10 = (var5 - var6) * 1.0F + 2.0F * var1 * var7 + 2.0F * var2 * var9;
      float var11 = (var5 - var6) * 0.0F + 2.0F * var1 * var8 + 2.0F * var4 * var9;
      float var12 = (float)Math.atan2(-var11, var10);
      return PZMath.wrap(var12, (float) -Math.PI, (float) Math.PI);
   }

   public static float getRotationZ(Quaternion var0) {
      float var1 = var0.w;
      float var2 = var0.x;
      float var3 = var0.y;
      float var4 = var0.z;
      float var5 = var1 * var1;
      float var6 = var2 * var2 + var3 * var3 + var4 * var4;
      float var7 = var4 * 1.0F;
      float var8 = 1.0F * var2;
      float var9 = (var5 - var6) * 1.0F + 2.0F * var2 * var8;
      float var10 = 2.0F * var1 * var7 + 2.0F * var3 * var8;
      return (float)Math.atan2(var10, var9);
   }

   public static Vector3f ToEulerAngles(Quaternion var0, Vector3f var1) {
      double var2 = 2.0 * (var0.w * var0.x + var0.y * var0.z);
      double var4 = 1.0 - 2.0 * (var0.x * var0.x + var0.y * var0.y);
      var1.x = (float)Math.atan2(var2, var4);
      double var6 = 2.0 * (var0.w * var0.y - var0.z * var0.x);
      if (Math.abs(var6) >= 1.0) {
         var1.y = (float)Math.copySign((float) (Math.PI / 2), var6);
      } else {
         var1.y = (float)Math.asin(var6);
      }

      double var8 = 2.0 * (var0.w * var0.z + var0.x * var0.y);
      double var10 = 1.0 - 2.0 * (var0.y * var0.y + var0.z * var0.z);
      var1.z = (float)Math.atan2(var8, var10);
      return var1;
   }

   public static Quaternion ToQuaternion(double var0, double var2, double var4, Quaternion var6) {
      double var7 = Math.cos(var4 * 0.5);
      double var9 = Math.sin(var4 * 0.5);
      double var11 = Math.cos(var2 * 0.5);
      double var13 = Math.sin(var2 * 0.5);
      double var15 = Math.cos(var0 * 0.5);
      double var17 = Math.sin(var0 * 0.5);
      var6.w = (float)(var7 * var11 * var15 + var9 * var13 * var17);
      var6.x = (float)(var7 * var11 * var17 - var9 * var13 * var15);
      var6.y = (float)(var9 * var11 * var17 + var7 * var13 * var15);
      var6.z = (float)(var9 * var11 * var15 - var7 * var13 * var17);
      return var6;
   }

   public static Vector3f getZero3() {
      s_zero3.set(0.0F, 0.0F, 0.0F);
      return s_zero3;
   }

   public static Quaternion getIdentityQ() {
      s_identityQ.setIdentity();
      return s_identityQ;
   }

   static {
      UnitTests.runAll();
   }
}
