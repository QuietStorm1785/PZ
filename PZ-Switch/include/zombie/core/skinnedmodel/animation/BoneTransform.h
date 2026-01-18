#pragma once
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BoneTransform : public PooledObject {
public:
 bool m_matrixValid = true;
 const Matrix4f m_matrix = new Matrix4f();
private
 HelperFunctions.TransformResult_QPS m_transformResult =
 new HelperFunctions.TransformResult_QPS(this->m_matrix);
 bool m_prsValid = true;
 const Vector3f m_pos = new Vector3f();
 const Quaternion m_rot = new Quaternion();
 const Vector3f m_scale = new Vector3f();
private
 static Pool<BoneTransform> s_pool = new Pool<>(BoneTransform::new);

protected
 BoneTransform() { this->setIdentity(); }

 void setIdentity() {
 this->m_matrixValid = true;
 this->m_matrix.setIdentity();
 this->m_prsValid = true;
 this->m_pos.set(0.0F, 0.0F, 0.0F);
 this->m_rot.setIdentity();
 this->m_scale.set(1.0F, 1.0F, 1.0F);
 }

 void set(BoneTransform rhs) {
 this->m_matrixValid = rhs.m_matrixValid;
 this->m_prsValid = rhs.m_prsValid;
 this->m_pos.set(rhs.m_pos);
 this->m_rot.set(rhs.m_rot);
 this->m_scale.set(rhs.m_scale);
 this->m_matrix.load(rhs.m_matrix);
 }

 void set(Vector3f pos, Quaternion rot, Vector3f scale) {
 if (this->m_matrixValid || !this->m_prsValid || !this->m_pos == pos) || !this->m_rot == rot) || !this->m_scale == scale) {
 this->m_matrixValid = false;
 this->m_prsValid = true;
 this->m_pos.set(pos);
 this->m_rot.set(rot);
 this->m_scale.set(scale);
 }
 }

 void set(Matrix4f matrix) {
 this->m_matrixValid = true;
 this->m_matrix.load(matrix);
 this->m_prsValid = false;
 }

 void mul(Matrix4f a, Matrix4f b) {
 this->m_matrixValid = true;
 this->m_prsValid = false;
 Matrix4f.mul(a, b, this->m_matrix);
 }

 void getMatrix(Matrix4f out_result) {
 out_result.load(this->getValidMatrix_Internal());
 }

 void getPRS(Vector3f out_pos, Quaternion out_rot, Vector3f out_scale) {
 this->validatePRS();
 out_pos.set(this->m_pos);
 out_rot.set(this->m_rot);
 out_scale.set(this->m_scale);
 }

 void getPosition(Vector3f out_pos) {
 this->validatePRS();
 out_pos.set(this->m_pos);
 }

 Matrix4f getValidMatrix_Internal() {
 this->validateMatrix();
 return this->m_matrix;
 }

 void validateMatrix() {
 if (!this->m_matrixValid) {
 this->validateInternal();
 this->m_matrixValid = true;
 HelperFunctions.CreateFromQuaternionPositionScale(
 this->m_pos, this->m_rot, this->m_scale, this->m_transformResult);
 }
 }

 void validatePRS() {
 if (!this->m_prsValid) {
 this->validateInternal();
 this->m_prsValid = true;
 HelperFunctions.getPosition(this->m_matrix, this->m_pos);
 HelperFunctions.getRotation(this->m_matrix, this->m_rot);
 this->m_scale.set(1.0F, 1.0F, 1.0F);
 }
 }

 void validateInternal() {
 if (!this->m_prsValid && !this->m_matrixValid) {
 throw RuntimeException("Neither the matrix nor the PosRotScale "
 "values in this object are listed as valid.");
 }
 }

 static void mul(BoneTransform a, Matrix4f b, Matrix4f out_result) {
 Matrix4f.mul(a.getValidMatrix_Internal(), b, out_result);
 }

 static BoneTransform alloc() { return s_pool.alloc(); }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
