#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/HelperFunctions/TransformResult_QPS.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class BoneTransform : public PooledObject {
public:
    bool m_matrixValid = true;
    const Matrix4f m_matrix = std::make_shared<Matrix4f>();
    const TransformResult_QPS m_transformResult = std::make_shared<TransformResult_QPS>(this.m_matrix);
    bool m_prsValid = true;
    const Vector3f m_pos = std::make_shared<Vector3f>();
    const Quaternion m_rot = std::make_shared<Quaternion>();
    const Vector3f m_scale = std::make_shared<Vector3f>();
   private static const Pool<BoneTransform> s_pool = std::make_shared<Pool>(BoneTransform::new);

    protected BoneTransform() {
      this.setIdentity();
   }

    void setIdentity() {
      this.m_matrixValid = true;
      this.m_matrix.setIdentity();
      this.m_prsValid = true;
      this.m_pos.set(0.0F, 0.0F, 0.0F);
      this.m_rot.setIdentity();
      this.m_scale.set(1.0F, 1.0F, 1.0F);
   }

    void set(BoneTransform var1) {
      this.m_matrixValid = var1.m_matrixValid;
      this.m_prsValid = var1.m_prsValid;
      this.m_pos.set(var1.m_pos);
      this.m_rot.set(var1.m_rot);
      this.m_scale.set(var1.m_scale);
      this.m_matrix.load(var1.m_matrix);
   }

    void set(Vector3f var1, Quaternion var2, Vector3f var3) {
      if (this.m_matrixValid || !this.m_prsValid || !this.m_pos == var1) || !this.m_rot == var2) || !this.m_scale == var3)) {
         this.m_matrixValid = false;
         this.m_prsValid = true;
         this.m_pos.set(var1);
         this.m_rot.set(var2);
         this.m_scale.set(var3);
      }
   }

    void set(Matrix4f var1) {
      this.m_matrixValid = true;
      this.m_matrix.load(var1);
      this.m_prsValid = false;
   }

    void mul(Matrix4f var1, Matrix4f var2) {
      this.m_matrixValid = true;
      this.m_prsValid = false;
      Matrix4f.mul(var1, var2, this.m_matrix);
   }

    void getMatrix(Matrix4f var1) {
      var1.load(this.getValidMatrix_Internal());
   }

    void getPRS(Vector3f var1, Quaternion var2, Vector3f var3) {
      this.validatePRS();
      var1.set(this.m_pos);
      var2.set(this.m_rot);
      var3.set(this.m_scale);
   }

    void getPosition(Vector3f var1) {
      this.validatePRS();
      var1.set(this.m_pos);
   }

    Matrix4f getValidMatrix_Internal() {
      this.validateMatrix();
      return this.m_matrix;
   }

    void validateMatrix() {
      if (!this.m_matrixValid) {
         this.validateInternal();
         this.m_matrixValid = true;
         HelperFunctions.CreateFromQuaternionPositionScale(this.m_pos, this.m_rot, this.m_scale, this.m_transformResult);
      }
   }

    void validatePRS() {
      if (!this.m_prsValid) {
         this.validateInternal();
         this.m_prsValid = true;
         HelperFunctions.getPosition(this.m_matrix, this.m_pos);
         HelperFunctions.getRotation(this.m_matrix, this.m_rot);
         this.m_scale.set(1.0F, 1.0F, 1.0F);
      }
   }

    void validateInternal() {
      if (!this.m_prsValid && !this.m_matrixValid) {
         throw RuntimeException("Neither the matrix nor the PosRotScale values in this object are listed as valid.");
      }
   }

    static void mul(BoneTransform var0, Matrix4f var1, Matrix4f var2) {
      Matrix4f.mul(var0.getValidMatrix_Internal(), var1, var2);
   }

    static BoneTransform alloc() {
      return (BoneTransform)s_pool.alloc();
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
