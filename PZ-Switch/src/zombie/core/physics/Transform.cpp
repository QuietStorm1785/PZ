#include "zombie/core/physics/Transform.h"

namespace zombie {
namespace core {
namespace physics {

public
Transform::Transform() {
 // TODO: Implement Transform
 return nullptr;
}

public
Transform::Transform(Matrix3f mat) {
 // TODO: Implement Transform
 return nullptr;
}

public
Transform::Transform(Matrix4f mat) {
 // TODO: Implement Transform
 return nullptr;
}

public
Transform::Transform(Transform tr) {
 // TODO: Implement Transform
 return nullptr;
}

void Transform::set(Transform tr) {
 // TODO: Implement set
}

void Transform::set(Matrix3f mat) {
 // TODO: Implement set
}

void Transform::set(Matrix4f mat) {
 // TODO: Implement set
}

void Transform::transform(Vector3f v) {
 // TODO: Implement transform
}

void Transform::setIdentity() {
 // TODO: Implement setIdentity
}

void Transform::inverse() {
 // TODO: Implement inverse
}

void Transform::inverse(Transform tr) {
 // TODO: Implement inverse
}

Quaternionf Transform::getRotation(Quaternionf out) {
 // TODO: Implement getRotation
 return nullptr;
}

void Transform::setRotation(Quaternionf q) {
 // TODO: Implement setRotation
}

Matrix4f Transform::getMatrix(Matrix4f out) {
 // TODO: Implement getMatrix
 return nullptr;
}

bool Transform::equals(void *obj) {
 // TODO: Implement equals
 return false;
}

int Transform::hashCode() {
 // TODO: Implement hashCode
 return 0;
}

} // namespace physics
} // namespace core
} // namespace zombie
