#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class HelperFunctions {
public:
    const Matrix4f result;
    const Matrix4f trans;
    const Matrix4f rot;
    const Matrix4f scl;

   public HelperFunctions$TransformResult_QPS() {
      this.result = std::make_unique<Matrix4f>();
      this.trans = std::make_unique<Matrix4f>();
      this.rot = std::make_unique<Matrix4f>();
      this.scl = std::make_unique<Matrix4f>();
   }

   public HelperFunctions$TransformResult_QPS(Matrix4f var1) {
      this.result = var1;
      this.trans = std::make_unique<Matrix4f>();
      this.rot = std::make_unique<Matrix4f>();
      this.scl = std::make_unique<Matrix4f>();
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
