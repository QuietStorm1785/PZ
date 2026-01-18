#include "zombie/core/skinnedmodel/animation/BoneTransform.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

protected BoneTransform::BoneTransform() {
 // TODO: Implement BoneTransform
 return nullptr;
}

void BoneTransform::setIdentity() {
 // TODO: Implement setIdentity
}

void BoneTransform::set(BoneTransform rhs) {
 // TODO: Implement set
}

void BoneTransform::set(Vector3f pos, Quaternion rot, Vector3f scale) {
 // TODO: Implement set
}

void BoneTransform::set(Matrix4f matrix) {
 // TODO: Implement set
}

void BoneTransform::mul(Matrix4f a, Matrix4f b) {
 // TODO: Implement mul
}

void BoneTransform::getMatrix(Matrix4f out_result) {
 // TODO: Implement getMatrix
}

void BoneTransform::getPRS(Vector3f out_pos, Quaternion out_rot, Vector3f out_scale) {
 // TODO: Implement getPRS
}

void BoneTransform::getPosition(Vector3f out_pos) {
 // TODO: Implement getPosition
}

Matrix4f BoneTransform::getValidMatrix_Internal() {
 // TODO: Implement getValidMatrix_Internal
 return nullptr;
}

void BoneTransform::validateMatrix() {
 // TODO: Implement validateMatrix
}

void BoneTransform::validatePRS() {
 // TODO: Implement validatePRS
}

void BoneTransform::validateInternal() {
 // TODO: Implement validateInternal
}

void BoneTransform::mul(BoneTransform a, Matrix4f b, Matrix4f out_result) {
 // TODO: Implement mul
}

BoneTransform BoneTransform::alloc() {
 // TODO: Implement alloc
 return nullptr;
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
