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


class Vector3 {
public:
    glm::vec3 data;

    Vector3() : data(0.0f, 0.0f, 0.0f) {}

    Vector3(float var1, float var2, float var3) : data(var1, var2, var3) {}

    Vector3(const glm::vec3& var1) : data(var1) {}

    Vector3(const Vector3& var1) : data(var1.data) {}

    // Accessors
    float x() const { return data.x; }
    float y() const { return data.y; }
    float z() const { return data.z; }
    
    float& x() { return data.x; }
    float& y() { return data.y; }
    float& z() { return data.z; }

   static glm::vec3 addScaled(const glm::vec3& var0, const glm::vec3& var1, float var2) {
      return glm::vec3(var0.x + var1.x * var2, var0.y + var1.y * var2, var0.z + var1.z * var2);
   }

   static glm::vec3 setScaled(const glm::vec3& var0, float var1) {
      return glm::vec3(var0.x * var1, var0.y * var1, var0.z * var1);
   }

   glm::vec3 Get() const {
      return data;
   }

    void Set(const glm::vec3& var1) {
      data = var1;
   }

    Vector3& reset() {
      data = glm::vec3(0.0f, 0.0f, 0.0f);
      return *this;
   }

    float dot(const Vector3& var1) const {
      return glm::dot(data, var1.data);
   }

    Vector3 cross(const Vector3& var1) const {
      return Vector3(glm::cross(data, var1.data));
   }
}
} // namespace math
} // namespace core
} // namespace zombie
