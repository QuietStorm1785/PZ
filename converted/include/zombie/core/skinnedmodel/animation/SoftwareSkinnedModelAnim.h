#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/vecmath/Point3f.h"
#include "org/lwjgl/opengl/GL13.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/SoftwareModelMesh.h"
#include "zombie/core/skinnedmodel/model/UInt4.h"
#include "zombie/core/skinnedmodel/model/Vbo.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject.h"
#include "zombie/core/skinnedmodel/model/VertexPositionNormalTangentTextureSkin.h"
#include "zombie/core/skinnedmodel/model/VertexStride.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/iso/Vector2.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SoftwareSkinnedModelAnim {
public:
 long animOffset;
 private VertexBufferObject.BeginMode _beginMode;
 private VertexStride[] _vertexStride;
 const Vbo _handle;
 public static Matrix4f[] boneTransforms;
 public static Matrix4f[] worldTransforms;
 public static Matrix4f[] skinTransforms;
 ByteBuffer softwareSkinBufferInt;
 public HashMap<String, Integer> AnimationOffset = std::make_unique<HashMap<>>();
 public HashMap<String, Integer> AnimationLength = std::make_unique<HashMap<>>();
 int vertCount = 0;
 int elementCount;
 static Matrix4f Identity = std::make_unique<Matrix4f>();
 static Vector3f tempVec3f = new Vector3f();
 static javax.vecmath.Matrix4f m = new javax.vecmath.Matrix4f();
 static Point3f tempop = std::make_unique<Point3f>();
 static javax.vecmath.Vector3f temponor = new javax.vecmath.Vector3f();
 static Vector3f tot = std::make_unique<Vector3f>();
 static Vector3f totn = std::make_unique<Vector3f>();
 static Vector3f vec = std::make_unique<Vector3f>();

 void UpdateWorldTransforms(Matrix4f var1, float var2, SkinningData skinningData) {
 Identity.setIdentity();
 tempVec3f.set(0.0F, 1.0F, 0.0F);
 Matrix4f.mul(boneTransforms[0], Identity, worldTransforms[0]);

 for (int int0 = 1; int0 < worldTransforms.length; int0++) {
 int int1 = skinningData.SkeletonHierarchy.get(int0);
 Matrix4f.mul(boneTransforms[int0], worldTransforms[int1], worldTransforms[int0]);
 }
 }

 void UpdateSkinTransforms(SkinningData skinningData) {
 for (int int0 = 0; int0 < worldTransforms.length; int0++) {
 Matrix4f.mul(skinningData.BoneOffset.get(int0), worldTransforms[int0], skinTransforms[int0]);
 }
 }

 public SoftwareSkinnedModelAnim(StaticAnimation[] staticAnimations, SoftwareModelMesh softwareModelMesh, SkinningData skinningData) {
 this->vertCount = softwareModelMesh.verticesUnskinned.length;
 this->elementCount = softwareModelMesh.indicesUnskinned.length;
 Vbo vbo = new Vbo();
 if (boneTransforms == nullptr) {
 boneTransforms = new Matrix4f[skinningData.BindPose.size()];
 worldTransforms = new Matrix4f[skinningData.BindPose.size()];
 skinTransforms = new Matrix4f[skinningData.BindPose.size()];

 for (int int0 = 0; int0 < skinningData.BindPose.size(); int0++) {
 boneTransforms[int0] = HelperFunctions.getMatrix();
 boneTransforms[int0].setIdentity();
 worldTransforms[int0] = HelperFunctions.getMatrix();
 worldTransforms[int0].setIdentity();
 skinTransforms[int0] = HelperFunctions.getMatrix();
 skinTransforms[int0].setIdentity();
 }
 }

 int int1 = 0;
 std::vector arrayList0 = new ArrayList();
 std::vector arrayList1 = new ArrayList();
 int int2 = 0;

 for (int int3 = 0; int3 < staticAnimations.length; int3++) {
 StaticAnimation staticAnimation = staticAnimations[int3];
 this->AnimationOffset.put(staticAnimation.Clip.Name, int1);
 this->AnimationLength.put(staticAnimation.Clip.Name, staticAnimation.Matrices.length);

 for (int int4 = 0; int4 < staticAnimation.Matrices.length; int4++) {
 int[] ints = softwareModelMesh.indicesUnskinned;

 for (int int5 = 0; int5 < ints.length; int5++) {
 int int6 = ints[int5];
 arrayList1.add(int6 + int2);
 }

 int2 += this->vertCount;
 Matrix4f[] matrix4fs = staticAnimation.Matrices[int4];
 boneTransforms = matrix4fs;
 this->UpdateWorldTransforms(nullptr, 0.0F, skinningData);
 this->UpdateSkinTransforms(skinningData);

 for (int int7 = 0; int7 < softwareModelMesh.verticesUnskinned.length; int7++) {
 VertexPositionNormalTangentTextureSkin vertexPositionNormalTangentTextureSkin0 = this->updateSkin(
 skinTransforms, softwareModelMesh.verticesUnskinned, int7
 );
 arrayList0.add(vertexPositionNormalTangentTextureSkin0);
 }

 int1 += softwareModelMesh.indicesUnskinned.length;
 }
 }

 this->_vertexStride = new VertexStride[4];

 for (int int8 = 0; int8 < this->_vertexStride.length; int8++) {
 this->_vertexStride[int8] = std::make_unique<VertexStride>();
 }

 this->_vertexStride[0].Type = VertexBufferObject.VertexType.VertexArray;
 this->_vertexStride[0].Offset = 0;
 this->_vertexStride[1].Type = VertexBufferObject.VertexType.NormalArray;
 this->_vertexStride[1].Offset = 12;
 this->_vertexStride[2].Type = VertexBufferObject.VertexType.ColorArray;
 this->_vertexStride[2].Offset = 24;
 this->_vertexStride[3].Type = VertexBufferObject.VertexType.TextureCoordArray;
 this->_vertexStride[3].Offset = 28;
 this->_beginMode = VertexBufferObject.BeginMode.Triangles;
 bool boolean0 = false;
 void* object = nullptr;
 vbo.VboID = VertexBufferObject.funcs.glGenBuffers();
 ByteBuffer byteBuffer0 = BufferUtils.createByteBuffer(arrayList0.size() * 36);
 ByteBuffer byteBuffer1 = BufferUtils.createByteBuffer(arrayList1.size() * 4);

 for (int int9 = 0; int9 < arrayList0.size(); int9++) {
 VertexPositionNormalTangentTextureSkin vertexPositionNormalTangentTextureSkin1 = (VertexPositionNormalTangentTextureSkin)arrayList0.get(int9);
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Position.x());
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Position.y());
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Position.z());
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Normal.x());
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Normal.y());
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.Normal.z());
 byteBuffer0.putInt(-1);
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.TextureCoordinates.x);
 byteBuffer0.putFloat(vertexPositionNormalTangentTextureSkin1.TextureCoordinates.y);
 }

 for (int int10 = 0; int10 < arrayList1.size(); int10++) {
 byteBuffer1.putInt((Integer)arrayList1.get(int10);
 }

 byteBuffer1.flip();
 byteBuffer0.flip();
 vbo.VertexStride = 36;
 vbo.NumElements = arrayList1.size();
 bool boolean1 = false;
 uint8_t byte0 = 44;
 vbo.FaceDataOnly = false;
 VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), vbo.VboID);
 VertexBufferObject.funcs.glBufferData(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), byteBuffer0, VertexBufferObject.funcs.GL_STATIC_DRAW());
 VertexBufferObject.funcs.glGetBufferParameter(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), VertexBufferObject.funcs.GL_BUFFER_SIZE(), vbo.b);
 vbo.EboID = VertexBufferObject.funcs.glGenBuffers();
 VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
 VertexBufferObject.funcs.glBufferData(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), byteBuffer1, VertexBufferObject.funcs.GL_STATIC_DRAW());
 this->_handle = vbo;
 }

 public VertexPositionNormalTangentTextureSkin updateSkin(
 Matrix4f[] matrix4fs, VertexPositionNormalTangentTextureSkin[] vertexPositionNormalTangentTextureSkins, int int0
 ) {
 tot.set(0.0F, 0.0F, 0.0F);
 totn.set(0.0F, 0.0F, 0.0F);
 VertexPositionNormalTangentTextureSkin vertexPositionNormalTangentTextureSkin0 = vertexPositionNormalTangentTextureSkins[int0];
 Matrix4f matrix4f0 = HelperFunctions.getMatrix();
 Matrix4f matrix4f1 = HelperFunctions.getMatrix();
 matrix4f0.setIdentity();
 Matrix4f matrix4f2 = HelperFunctions.getMatrix();
 UInt4 uInt4 = vertexPositionNormalTangentTextureSkin0.BlendIndices;
 float float0 = 1.0F;
 if (vertexPositionNormalTangentTextureSkin0.BlendWeights.x > 0.0F) {
 matrix4f1.load(matrix4fs[uInt4.X]);
 set(matrix4f1, m);
 Point3f point3f0 = tempop;
 tempop.set(
 vertexPositionNormalTangentTextureSkin0.Position.x(),
 vertexPositionNormalTangentTextureSkin0.Position.y(),
 vertexPositionNormalTangentTextureSkin0.Position.z()
 );
 m.transform(point3f0);
 point3f0.x = point3f0.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 point3f0.y = point3f0.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 point3f0.z = point3f0.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 tot.x = tot.x + point3f0.x;
 tot.y = tot.y + point3f0.y;
 tot.z = tot.z + point3f0.z;
 javax.vecmath.Vector3f vector3f0 = temponor;
 temponor.set(
 vertexPositionNormalTangentTextureSkin0.Normal.x(),
 vertexPositionNormalTangentTextureSkin0.Normal.y(),
 vertexPositionNormalTangentTextureSkin0.Normal.z()
 );
 m.transform(vector3f0);
 vector3f0.x = vector3f0.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 vector3f0.y = vector3f0.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 vector3f0.z = vector3f0.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.x;
 totn.x = totn.x + vector3f0.x;
 totn.y = totn.y + vector3f0.y;
 totn.z = totn.z + vector3f0.z;
 }

 if (vertexPositionNormalTangentTextureSkin0.BlendWeights.y > 0.0F) {
 matrix4f1.load(matrix4fs[uInt4.Y]);
 set(matrix4f1, m);
 Point3f point3f1 = tempop;
 tempop.set(
 vertexPositionNormalTangentTextureSkin0.Position.x(),
 vertexPositionNormalTangentTextureSkin0.Position.y(),
 vertexPositionNormalTangentTextureSkin0.Position.z()
 );
 m.transform(point3f1);
 point3f1.x = point3f1.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 point3f1.y = point3f1.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 point3f1.z = point3f1.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 tot.x = tot.x + point3f1.x;
 tot.y = tot.y + point3f1.y;
 tot.z = tot.z + point3f1.z;
 javax.vecmath.Vector3f vector3f1 = temponor;
 temponor.set(
 vertexPositionNormalTangentTextureSkin0.Normal.x(),
 vertexPositionNormalTangentTextureSkin0.Normal.y(),
 vertexPositionNormalTangentTextureSkin0.Normal.z()
 );
 m.transform(vector3f1);
 vector3f1.x = vector3f1.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 vector3f1.y = vector3f1.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 vector3f1.z = vector3f1.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.y;
 totn.x = totn.x + vector3f1.x;
 totn.y = totn.y + vector3f1.y;
 totn.z = totn.z + vector3f1.z;
 }

 if (vertexPositionNormalTangentTextureSkin0.BlendWeights.z > 0.0F) {
 matrix4f1.load(matrix4fs[uInt4.Z]);
 set(matrix4f1, m);
 Point3f point3f2 = tempop;
 tempop.set(
 vertexPositionNormalTangentTextureSkin0.Position.x(),
 vertexPositionNormalTangentTextureSkin0.Position.y(),
 vertexPositionNormalTangentTextureSkin0.Position.z()
 );
 m.transform(point3f2);
 point3f2.x = point3f2.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 point3f2.y = point3f2.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 point3f2.z = point3f2.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 tot.x = tot.x + point3f2.x;
 tot.y = tot.y + point3f2.y;
 tot.z = tot.z + point3f2.z;
 javax.vecmath.Vector3f vector3f2 = temponor;
 temponor.set(
 vertexPositionNormalTangentTextureSkin0.Normal.x(),
 vertexPositionNormalTangentTextureSkin0.Normal.y(),
 vertexPositionNormalTangentTextureSkin0.Normal.z()
 );
 m.transform(vector3f2);
 vector3f2.x = vector3f2.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 vector3f2.y = vector3f2.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 vector3f2.z = vector3f2.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.z;
 totn.x = totn.x + vector3f2.x;
 totn.y = totn.y + vector3f2.y;
 totn.z = totn.z + vector3f2.z;
 }

 if (vertexPositionNormalTangentTextureSkin0.BlendWeights.w > 0.0F) {
 matrix4f1.load(matrix4fs[uInt4.W]);
 set(matrix4f1, m);
 Point3f point3f3 = tempop;
 tempop.set(
 vertexPositionNormalTangentTextureSkin0.Position.x(),
 vertexPositionNormalTangentTextureSkin0.Position.y(),
 vertexPositionNormalTangentTextureSkin0.Position.z()
 );
 m.transform(point3f3);
 point3f3.x = point3f3.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 point3f3.y = point3f3.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 point3f3.z = point3f3.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 tot.x = tot.x + point3f3.x;
 tot.y = tot.y + point3f3.y;
 tot.z = tot.z + point3f3.z;
 javax.vecmath.Vector3f vector3f3 = temponor;
 temponor.set(
 vertexPositionNormalTangentTextureSkin0.Normal.x(),
 vertexPositionNormalTangentTextureSkin0.Normal.y(),
 vertexPositionNormalTangentTextureSkin0.Normal.z()
 );
 m.transform(vector3f3);
 vector3f3.x = vector3f3.x * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 vector3f3.y = vector3f3.y * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 vector3f3.z = vector3f3.z * vertexPositionNormalTangentTextureSkin0.BlendWeights.w;
 totn.x = totn.x + vector3f3.x;
 totn.y = totn.y + vector3f3.y;
 totn.z = totn.z + vector3f3.z;
 }

 matrix4f2.setIdentity();
 vec.x = tot.x;
 vec.y = tot.y;
 vec.z = tot.z;
 VertexPositionNormalTangentTextureSkin vertexPositionNormalTangentTextureSkin1 = new VertexPositionNormalTangentTextureSkin();
 vertexPositionNormalTangentTextureSkin1.Position = std::make_unique<Vector3>();
 vertexPositionNormalTangentTextureSkin1.Position.set(vec.getX(), vec.getY(), vec.getZ());
 javax.vecmath.Vector3f vector3f4 = temponor;
 vector3f4.x = totn.x;
 vector3f4.y = totn.y;
 vector3f4.z = totn.z;
 vector3f4.normalize();
 vertexPositionNormalTangentTextureSkin1.Normal = std::make_unique<Vector3>();
 vertexPositionNormalTangentTextureSkin1.Normal.set(vector3f4.getX(), vector3f4.getY(), vector3f4.getZ());
 vertexPositionNormalTangentTextureSkin1.TextureCoordinates = std::make_unique<Vector2>();
 vertexPositionNormalTangentTextureSkin1.TextureCoordinates.x = vertexPositionNormalTangentTextureSkin0.TextureCoordinates.x;
 vertexPositionNormalTangentTextureSkin1.TextureCoordinates.y = vertexPositionNormalTangentTextureSkin0.TextureCoordinates.y;
 HelperFunctions.returnMatrix(matrix4f0);
 HelperFunctions.returnMatrix(matrix4f2);
 HelperFunctions.returnMatrix(matrix4f1);
 return vertexPositionNormalTangentTextureSkin1;
 }

 void Draw(int int0, int int1, const std::string& string) {
 this->Draw(this->_handle, this->_vertexStride, this->_beginMode, nullptr, int0, int1, string);
 }

 static void set(Matrix4f matrix4f0, javax.vecmath.Matrix4f matrix4f1) {
 matrix4f1.m00 = matrix4f0.m00;
 matrix4f1.m01 = matrix4f0.m01;
 matrix4f1.m02 = matrix4f0.m02;
 matrix4f1.m03 = matrix4f0.m03;
 matrix4f1.m10 = matrix4f0.m10;
 matrix4f1.m11 = matrix4f0.m11;
 matrix4f1.m12 = matrix4f0.m12;
 matrix4f1.m13 = matrix4f0.m13;
 matrix4f1.m20 = matrix4f0.m20;
 matrix4f1.m21 = matrix4f0.m21;
 matrix4f1.m22 = matrix4f0.m22;
 matrix4f1.m23 = matrix4f0.m23;
 matrix4f1.m30 = matrix4f0.m30;
 matrix4f1.m31 = matrix4f0.m31;
 matrix4f1.m32 = matrix4f0.m32;
 matrix4f1.m33 = matrix4f0.m33;
 }

 void Draw(Vbo vbo, VertexStride[] vertexStrides, VertexBufferObject.BeginMode var3, Shader shader, int int1, int int0, const std::string& var7) {
 this->animOffset = int0 + this->elementCount * int1;
 int int2 = this->elementCount;
 int int3 = 33984;
 if (!vbo.FaceDataOnly) {
 VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ARRAY_BUFFER(), vbo.VboID);

 for (int int4 = vertexStrides.length - 1; int4 >= 0; int4--) {
 switch (vertexStrides[int4].Type) {
 case VertexArray:
 GL20.glVertexPointer(3, 5126, vbo.VertexStride, vertexStrides[int4].Offset);
 GL20.glEnableClientState(32884);
 break;
 case NormalArray:
 GL20.glNormalPointer(5126, vbo.VertexStride, vertexStrides[int4].Offset);
 GL20.glEnableClientState(32885);
 break;
 case ColorArray:
 GL20.glColorPointer(3, 5121, vbo.VertexStride, vertexStrides[int4].Offset);
 GL20.glEnableClientState(32886);
 break;
 case TextureCoordArray:
 GL13.glActiveTexture(int3);
 GL13.glClientActiveTexture(int3);
 GL20.glTexCoordPointer(2, 5126, vbo.VertexStride, vertexStrides[int4].Offset);
 int3++;
 GL20.glEnableClientState(32888);
 break;
 case TangentArray:
 GL20.glNormalPointer(5126, vbo.VertexStride, vertexStrides[int4].Offset);
 break;
 case BlendWeightArray:
 int int5 = GL20.glGetAttribLocation(shader.getID(), "boneWeights");
 GL20.glVertexAttribPointer(int5, 4, 5126, false, vbo.VertexStride, vertexStrides[int4].Offset);
 GL20.glEnableVertexAttribArray(int5);
 break;
 case BlendIndexArray:
 int int6 = GL20.glGetAttribLocation(shader.getID(), "boneIndices");
 GL20.glVertexAttribPointer(int6, 4, 5126, false, vbo.VertexStride, vertexStrides[int4].Offset);
 GL20.glEnableVertexAttribArray(int6);
 }
 }
 }

 VertexBufferObject.funcs.glBindBuffer(VertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), vbo.EboID);
 GL20.glDrawElements(4, int2, 5125, this->animOffset * 4L);
 GL20.glDisableClientState(32885);
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
