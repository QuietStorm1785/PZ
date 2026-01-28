#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/vecmath/Point3f.h"
#include <GL/glew.h>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/core/skinnedmodel/animation/SoftwareSkinnedModelAnim/1.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/SoftwareModelMesh.h"
#include "zombie/core/skinnedmodel/model/UInt4.h"
#include "zombie/core/skinnedmodel/model/Vbo.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/BeginMode.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTextureSkin.h"
#include "zombie/core/skinnedmodel/model/VertexStride.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/iso/Vector2.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class SoftwareSkinnedModelAnim {
public:
    long animOffset;
    const BeginMode _beginMode;
   private const VertexStride[] _vertexStride;
    const Vbo _handle;
   public static Matrix4f[] boneTransforms;
   public static Matrix4f[] worldTransforms;
   public static Matrix4f[] skinTransforms;
    ByteBuffer softwareSkinBufferInt;
   public std::unordered_map<std::string, int> AnimationOffset = std::make_unique<std::unordered_map<>>();
   public std::unordered_map<std::string, int> AnimationLength = std::make_unique<std::unordered_map<>>();
    int vertCount = 0;
    int elementCount;
    static Matrix4f Identity = std::make_shared<Matrix4f>();
    static Vector3f tempVec3f = std::make_shared<Vector3f>();
   static javax.vecmath.Matrix4f m = new javax.vecmath.Matrix4f();
    static Point3f tempop = std::make_shared<Point3f>();
   static javax.vecmath.Vector3f temponor = new javax.vecmath.Vector3f();
    static Vector3f tot = std::make_shared<Vector3f>();
    static Vector3f totn = std::make_shared<Vector3f>();
    static Vector3f vec = std::make_shared<Vector3f>();

    void UpdateWorldTransforms(Matrix4f var1, float var2, SkinningData var3) {
      Identity.setIdentity();
      tempVec3f.set(0.0F, 1.0F, 0.0F);
      Matrix4f.mul(boneTransforms[0], Identity, worldTransforms[0]);

      for (int var4 = 1; var4 < worldTransforms.length; var4++) {
    int var5 = (int)var3.SkeletonHierarchy.get(var4);
         Matrix4f.mul(boneTransforms[var4], worldTransforms[var5], worldTransforms[var4]);
      }
   }

    void UpdateSkinTransforms(SkinningData var1) {
      for (int var2 = 0; var2 < worldTransforms.length; var2++) {
         Matrix4f.mul((Matrix4f)var1.BoneOffset.get(var2), worldTransforms[var2], skinTransforms[var2]);
      }
   }

    public SoftwareSkinnedModelAnim(StaticAnimation[] var1, SoftwareModelMesh var2, SkinningData var3) {
      this.vertCount = var2.verticesUnskinned.length;
      this.elementCount = var2.indicesUnskinned.length;
    Vbo var4 = std::make_shared<Vbo>();
      if (boneTransforms == nullptr) {
         boneTransforms = new Matrix4f[var3.BindPose.size()];
         worldTransforms = new Matrix4f[var3.BindPose.size()];
         skinTransforms = new Matrix4f[var3.BindPose.size()];

         for (int var5 = 0; var5 < var3.BindPose.size(); var5++) {
            boneTransforms[var5] = HelperFunctions.getMatrix();
            boneTransforms[var5].setIdentity();
            worldTransforms[var5] = HelperFunctions.getMatrix();
            worldTransforms[var5].setIdentity();
            skinTransforms[var5] = HelperFunctions.getMatrix();
            skinTransforms[var5].setIdentity();
         }
      }

    int var16 = 0;
    std::vector var6 = new std::vector();
    std::vector var7 = new std::vector();
    int var8 = 0;

      for (int var9 = 0; var9 < var1.length; var9++) {
    StaticAnimation var10 = var1[var9];
         this.AnimationOffset.put(var10.Clip.Name, var16);
         this.AnimationLength.put(var10.Clip.Name, var10.Matrices.length);

         for (int var11 = 0; var11 < var10.Matrices.length; var11++) {
            int[] var12 = var2.indicesUnskinned;

            for (int var13 = 0; var13 < var12.length; var13++) {
    int var14 = var12[var13];
               var7.push_back(var14 + var8);
            }

            var8 += this.vertCount;
            Matrix4f[] var22 = var10.Matrices[var11];
            boneTransforms = var22;
            this.UpdateWorldTransforms(nullptr, 0.0F, var3);
            this.UpdateSkinTransforms(var3);

            for (int var26 = 0; var26 < var2.verticesUnskinned.length; var26++) {
    VertexPositionNormalTangentTextureSkin var15 = this.updateSkin(skinTransforms, var2.verticesUnskinned, var26);
               var6.push_back(var15);
            }

            var16 += var2.indicesUnskinned.length;
         }
      }

      this._vertexStride = new VertexStride[4];

      for (int var17 = 0; var17 < this._vertexStride.length; var17++) {
         this._vertexStride[var17] = std::make_unique<VertexStride>();
      }

      this._vertexStride[0].Type = VertexType.VertexArray;
      this._vertexStride[0].Offset = 0;
      this._vertexStride[1].Type = VertexType.NormalArray;
      this._vertexStride[1].Offset = 12;
      this._vertexStride[2].Type = VertexType.ColorArray;
      this._vertexStride[2].Offset = 24;
      this._vertexStride[3].Type = VertexType.TextureCoordArray;
      this._vertexStride[3].Offset = 28;
      this._beginMode = BeginMode.Triangles;
    bool var18 = false;
    void* var19 = nullptr;
      var4.VboID = VertexBufferObject.funcs.glGenBuffers();
    ByteBuffer var20 = BufferUtils.createByteBuffer(var6.size() * 36);
    ByteBuffer var21 = BufferUtils.createByteBuffer(var7.size() * 4);

      for (int var23 = 0; var23 < var6.size(); var23++) {
    VertexPositionNormalTangentTextureSkin var27 = (VertexPositionNormalTangentTextureSkin)var6.get(var23);
         var20.putFloat(var27.Position.x());
         var20.putFloat(var27.Position.y());
         var20.putFloat(var27.Position.z());
         var20.putFloat(var27.Normal.x());
         var20.putFloat(var27.Normal.y());
         var20.putFloat(var27.Normal.z());
         var20.putInt(-1);
         var20.putFloat(var27.TextureCoordinates.x);
         var20.putFloat(var27.TextureCoordinates.y);
      }

      for (int var24 = 0; var24 < var7.size(); var24++) {
         var21.putInt((int)var7.get(var24));
      }

      var21.flip();
      var20.flip();
      var4.VertexStride = 36;
      var4.NumElements = var7.size();
    bool var25 = false;
    uint8_t var28 = 44;
      var4.FaceDataOnly = false;
      VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), var4.VboID);
      VertexBufferObject.funcs.glBufferData(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), var20, VertexBufferObject.funcs.GL_STATIC_DRAW());
      VertexBufferObject.funcs.glGetBufferParameter(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), VertexBufferObject.funcs.GL_BUFFER_SIZE(), var4.b);
      var4.EboID = VertexBufferObject.funcs.glGenBuffers();
      VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), var4.EboID);
      VertexBufferObject.funcs.glBufferData(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), var21, VertexBufferObject.funcs.GL_STATIC_DRAW());
      this._handle = var4;
   }

    VertexPositionNormalTangentTextureSkin updateSkin(Matrix4f[] var1, VertexPositionNormalTangentTextureSkin[] var2, int var3) {
      tot.set(0.0F, 0.0F, 0.0F);
      totn.set(0.0F, 0.0F, 0.0F);
    VertexPositionNormalTangentTextureSkin var4 = var2[var3];
    Matrix4f var5 = HelperFunctions.getMatrix();
    Matrix4f var6 = HelperFunctions.getMatrix();
      var5.setIdentity();
    Matrix4f var7 = HelperFunctions.getMatrix();
    UInt4 var8 = var4.BlendIndices;
    float var9 = 1.0F;
      if (var4.BlendWeights.x > 0.0F) {
         var6.load(var1[var8.X]);
         set(var6, m);
    Point3f var10 = tempop;
         tempop.set(var4.Position.x(), var4.Position.y(), var4.Position.z());
         m.transform(var10);
         var10.x = var10.x * var4.BlendWeights.x;
         var10.y = var10.y * var4.BlendWeights.x;
         var10.z = var10.z * var4.BlendWeights.x;
         tot.x = tot.x + var10.x;
         tot.y = tot.y + var10.y;
         tot.z = tot.z + var10.z;
         javax.vecmath.Vector3f var11 = temponor;
         temponor.set(var4.Normal.x(), var4.Normal.y(), var4.Normal.z());
         m.transform(var11);
         var11.x = var11.x * var4.BlendWeights.x;
         var11.y = var11.y * var4.BlendWeights.x;
         var11.z = var11.z * var4.BlendWeights.x;
         totn.x = totn.x + var11.x;
         totn.y = totn.y + var11.y;
         totn.z = totn.z + var11.z;
      }

      if (var4.BlendWeights.y > 0.0F) {
         var6.load(var1[var8.Y]);
         set(var6, m);
    Point3f var12 = tempop;
         tempop.set(var4.Position.x(), var4.Position.y(), var4.Position.z());
         m.transform(var12);
         var12.x = var12.x * var4.BlendWeights.y;
         var12.y = var12.y * var4.BlendWeights.y;
         var12.z = var12.z * var4.BlendWeights.y;
         tot.x = tot.x + var12.x;
         tot.y = tot.y + var12.y;
         tot.z = tot.z + var12.z;
         javax.vecmath.Vector3f var16 = temponor;
         temponor.set(var4.Normal.x(), var4.Normal.y(), var4.Normal.z());
         m.transform(var16);
         var16.x = var16.x * var4.BlendWeights.y;
         var16.y = var16.y * var4.BlendWeights.y;
         var16.z = var16.z * var4.BlendWeights.y;
         totn.x = totn.x + var16.x;
         totn.y = totn.y + var16.y;
         totn.z = totn.z + var16.z;
      }

      if (var4.BlendWeights.z > 0.0F) {
         var6.load(var1[var8.Z]);
         set(var6, m);
    Point3f var13 = tempop;
         tempop.set(var4.Position.x(), var4.Position.y(), var4.Position.z());
         m.transform(var13);
         var13.x = var13.x * var4.BlendWeights.z;
         var13.y = var13.y * var4.BlendWeights.z;
         var13.z = var13.z * var4.BlendWeights.z;
         tot.x = tot.x + var13.x;
         tot.y = tot.y + var13.y;
         tot.z = tot.z + var13.z;
         javax.vecmath.Vector3f var17 = temponor;
         temponor.set(var4.Normal.x(), var4.Normal.y(), var4.Normal.z());
         m.transform(var17);
         var17.x = var17.x * var4.BlendWeights.z;
         var17.y = var17.y * var4.BlendWeights.z;
         var17.z = var17.z * var4.BlendWeights.z;
         totn.x = totn.x + var17.x;
         totn.y = totn.y + var17.y;
         totn.z = totn.z + var17.z;
      }

      if (var4.BlendWeights.w > 0.0F) {
         var6.load(var1[var8.W]);
         set(var6, m);
    Point3f var14 = tempop;
         tempop.set(var4.Position.x(), var4.Position.y(), var4.Position.z());
         m.transform(var14);
         var14.x = var14.x * var4.BlendWeights.w;
         var14.y = var14.y * var4.BlendWeights.w;
         var14.z = var14.z * var4.BlendWeights.w;
         tot.x = tot.x + var14.x;
         tot.y = tot.y + var14.y;
         tot.z = tot.z + var14.z;
         javax.vecmath.Vector3f var18 = temponor;
         temponor.set(var4.Normal.x(), var4.Normal.y(), var4.Normal.z());
         m.transform(var18);
         var18.x = var18.x * var4.BlendWeights.w;
         var18.y = var18.y * var4.BlendWeights.w;
         var18.z = var18.z * var4.BlendWeights.w;
         totn.x = totn.x + var18.x;
         totn.y = totn.y + var18.y;
         totn.z = totn.z + var18.z;
      }

      var7.setIdentity();
      vec.x = tot.x;
      vec.y = tot.y;
      vec.z = tot.z;
    VertexPositionNormalTangentTextureSkin var15 = std::make_shared<VertexPositionNormalTangentTextureSkin>();
      var15.Position = std::make_unique<Vector3>();
      var15.Position.set(vec.getX(), vec.getY(), vec.getZ());
      javax.vecmath.Vector3f var19 = temponor;
      var19.x = totn.x;
      var19.y = totn.y;
      var19.z = totn.z;
      var19.normalize();
      var15.Normal = std::make_unique<Vector3>();
      var15.Normal.set(var19.getX(), var19.getY(), var19.getZ());
      var15.TextureCoordinates = std::make_unique<Vector2>();
      var15.TextureCoordinates.x = var4.TextureCoordinates.x;
      var15.TextureCoordinates.y = var4.TextureCoordinates.y;
      HelperFunctions.returnMatrix(var5);
      HelperFunctions.returnMatrix(var7);
      HelperFunctions.returnMatrix(var6);
    return var15;
   }

    void Draw(int var1, int var2, const std::string& var3) {
      this.Draw(this._handle, this._vertexStride, this._beginMode, nullptr, var1, var2, var3);
   }

    static void set(Matrix4f var0, javax.vecmath.Matrix4f var1) {
      var1.m00 = var0.m00;
      var1.m01 = var0.m01;
      var1.m02 = var0.m02;
      var1.m03 = var0.m03;
      var1.m10 = var0.m10;
      var1.m11 = var0.m11;
      var1.m12 = var0.m12;
      var1.m13 = var0.m13;
      var1.m20 = var0.m20;
      var1.m21 = var0.m21;
      var1.m22 = var0.m22;
      var1.m23 = var0.m23;
      var1.m30 = var0.m30;
      var1.m31 = var0.m31;
      var1.m32 = var0.m32;
      var1.m33 = var0.m33;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void Draw(Vbo var1, VertexStride[] var2, BeginMode var3, Shader var4, int var5, int var6, const std::string& var7) {
      this.animOffset = var6 + this.elementCount * var5;
    int var8 = this.elementCount;
    int var9 = 33984;
      if (!var1.FaceDataOnly) {
         VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), var1.VboID);

         for (int var10 = var2.length - 1; var10 >= 0; var10--) {
            switch (1.$SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[var2[var10].Type.ordinal()]) {
               case 1:
                  GL20.glVertexPointer(3, 5126, var1.VertexStride, var2[var10].Offset);
                  GL20.glEnableClientState(32884);
                  break;
               case 2:
                  GL20.glNormalPointer(5126, var1.VertexStride, var2[var10].Offset);
                  GL20.glEnableClientState(32885);
                  break;
               case 3:
                  GL20.glColorPointer(3, 5121, var1.VertexStride, var2[var10].Offset);
                  GL20.glEnableClientState(32886);
                  break;
               case 4:
                  GL13.glActiveTexture(var9);
                  GL13.glClientActiveTexture(var9);
                  GL20.glTexCoordPointer(2, 5126, var1.VertexStride, var2[var10].Offset);
                  var9++;
                  GL20.glEnableClientState(32888);
                  break;
               case 5:
                  GL20.glNormalPointer(5126, var1.VertexStride, var2[var10].Offset);
                  break;
               case 6:
    int var11 = GL20.glGetAttribLocation(var4.getID(), "boneWeights");
                  GL20.glVertexAttribPointer(var11, 4, 5126, false, var1.VertexStride, var2[var10].Offset);
                  GL20.glEnableVertexAttribArray(var11);
                  break;
               case 7:
    int var12 = GL20.glGetAttribLocation(var4.getID(), "boneIndices");
                  GL20.glVertexAttribPointer(var12, 4, 5126, false, var1.VertexStride, var2[var10].Offset);
                  GL20.glEnableVertexAttribArray(var12);
            }
         }
      }

      VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), var1.EboID);
      GL20.glDrawElements(4, var8, 5125, this.animOffset * 4L);
      GL20.glDisableClientState(32885);
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
