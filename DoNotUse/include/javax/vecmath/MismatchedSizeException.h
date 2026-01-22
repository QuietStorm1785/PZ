#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace vecmath {

class MismatchedSizeException : public RuntimeException {
public:
    public MismatchedSizeException() {
   }

    public MismatchedSizeException(const std::string& var1) {
      super(var1);
   }
}
} // namespace vecmath
} // namespace javax
