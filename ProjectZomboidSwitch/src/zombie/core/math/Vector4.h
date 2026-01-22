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


class Vector4 {
public:
    glm::vec4 data;

    Vector4() : data(0.0f, 0.0f, 0.0f, 0.0f) {}

    Vector4(float var1, float var2, float var3, float var4) : data(var1, var2, var3, var4) {}

    Vector4(const glm::vec4& var1) : data(var1) {}

    // Accessors
    float x() const { return data.x; }
    float y() const { return data.y; }
    float z() const { return data.z; }
    float w() const { return data.w; }
    
    float& x() { return data.x; }
    float& y() { return data.y; }
    float& z() { return data.z; }
    float& w() { return data.w; }

   glm::vec4 Get() const {
      return data;
   }

    void Set(const glm::vec4& var1) {
      data = var1;
   }
}
} // namespace math
} // namespace core
} // namespace zombie
