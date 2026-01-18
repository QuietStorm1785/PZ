#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix3f.h"
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"

namespace zombie {
namespace core {
namespace physics {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Transform represents translation and rotation (rigid transform). Scaling and shearing is not supported.
 */
class Transform {
public:
 /**
 * Rotation matrix of this Transform.
 */
 const Matrix3f basis = new Matrix3f();
 /**
 * Translation vector of this Transform.
 */
 const Vector3f origin = new Vector3f();

 public Transform() {
 }

 public Transform(Matrix3f mat) {
 this->basis.set(mat);
 }

 public Transform(Matrix4f mat) {
 this->set(mat);
 }

 public Transform(Transform tr) {
 this->set(tr);
 }

 void set(Transform tr) {
 this->basis.set(tr.basis);
 this->origin.set(tr.origin);
 }

 void set(Matrix3f mat) {
 this->basis.set(mat);
 this->origin.set(0.0F, 0.0F, 0.0F);
 }

 void set(Matrix4f mat) {
 mat.get3x3(this->basis);
 mat.getTranslation(this->origin);
 }

 void transform(Vector3f v) {
 this->basis.transform(v);
 v.add(this->origin);
 }

 void setIdentity() {
 this->basis.identity();
 this->origin.set(0.0F, 0.0F, 0.0F);
 }

 void inverse() {
 this->basis.transpose();
 this->origin.negate();
 this->basis.transform(this->origin);
 }

 void inverse(Transform tr) {
 this->set(tr);
 this->inverse();
 }

 Quaternionf getRotation(Quaternionf out) {
 this->basis.getUnnormalizedRotation(out);
 return out;
 }

 void setRotation(Quaternionf q) {
 this->basis.set(q);
 }

 Matrix4f getMatrix(Matrix4f out) {
 out.set(this->basis);
 out.setTranslation(this->origin);
 return out;
 }

 bool equals(void* obj) {
 return obj != nullptr && obj instanceof Transform transform ? this->basis == transform.basis) && this->origin == transform.origin) : false;
 }

 int hashCode() {
 int int0 = 3;
 int0 = 41 * int0 + this->basis.hashCode();
 return 41 * int0 + this->origin.hashCode();
 }
}
} // namespace physics
} // namespace core
} // namespace zombie
