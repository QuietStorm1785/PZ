#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace zombie {
namespace core {
namespace math {


class Matrix4 {
public:
    glm::mat4 data;

   Matrix4(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33
   ) : data(
      m00, m01, m02, m03,
      m10, m11, m12, m13,
      m20, m21, m22, m23,
      m30, m31, m32, m33
   ) {}

    Matrix4(const Matrix4& var1) : data(var1.data) {}
    
    Matrix4() : data(1.0f) {} // Identity matrix
    
    Matrix4(const glm::mat4& mat) : data(mat) {}

   glm::mat4 Get() const {
      return data;
   }

    void Set(const glm::mat4& var1) {
      data = var1;
   }
    
    // Element accessors using GLM notation [col][row]
    float m00() const { return data[0][0]; }
    float m01() const { return data[1][0]; }
    float m02() const { return data[2][0]; }
    float m03() const { return data[3][0]; }
    float m10() const { return data[0][1]; }
    float m11() const { return data[1][1]; }
    float m12() const { return data[2][1]; }
    float m13() const { return data[3][1]; }
    float m20() const { return data[0][2]; }
    float m21() const { return data[1][2]; }
    float m22() const { return data[2][2]; }
    float m23() const { return data[3][2]; }
    float m30() const { return data[0][3]; }
    float m31() const { return data[1][3]; }
    float m32() const { return data[2][3]; }
    float m33() const { return data[3][3]; }
}
} // namespace math
} // namespace core
} // namespace zombie
