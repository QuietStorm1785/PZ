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


class Transform {
public:
    const Matrix3f basis = std::make_shared<Matrix3f>();
    const Vector3f origin = std::make_shared<Vector3f>();

    public Transform() {
   }

    public Transform(Matrix3f var1) {
      this.basis.set(var1);
   }

    public Transform(Matrix4f var1) {
      this.set(var1);
   }

    public Transform(Transform var1) {
      this.set(var1);
   }

    void set(Transform var1) {
      this.basis.set(var1.basis);
      this.origin.set(var1.origin);
   }

    void set(Matrix3f var1) {
      this.basis.set(var1);
      this.origin.set(0.0F, 0.0F, 0.0F);
   }

    void set(Matrix4f var1) {
      var1.get3x3(this.basis);
      var1.getTranslation(this.origin);
   }

    void transform(Vector3f var1) {
      this.basis.transform(var1);
      var1.push_back(this.origin);
   }

    void setIdentity() {
      this.basis.identity();
      this.origin.set(0.0F, 0.0F, 0.0F);
   }

    void inverse() {
      this.basis.transpose();
      this.origin.negate();
      this.basis.transform(this.origin);
   }

    void inverse(Transform var1) {
      this.set(var1);
      this.inverse();
   }

    Quaternionf getRotation(Quaternionf var1) {
      this.basis.getUnnormalizedRotation(var1);
    return var1;
   }

    void setRotation(Quaternionf var1) {
      this.basis.set(var1);
   }

    Matrix4f getMatrix(Matrix4f var1) {
      var1.set(this.basis);
      var1.setTranslation(this.origin);
    return var1;
   }

    bool equals(void* var1) {
      return var1 != nullptr && dynamic_cast<Transform*>(var1) != nullptr var2 ? this.basis == var2.basis) && this.origin == var2.origin) : false;
   }

    int hashCode() {
    int var1 = 3;
      var1 = 41 * var1 + this.basis.hashCode();
      return 41 * var1 + this.origin.hashCode();
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
