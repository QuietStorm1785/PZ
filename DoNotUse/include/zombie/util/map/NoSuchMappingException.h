#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace map {

class NoSuchMappingException : public RuntimeException {
public:
    static const long serialVersionUID = 1L;

    public NoSuchMappingException(const std::string& var1) {
      super(var1);
   }
}
} // namespace map
} // namespace util
} // namespace zombie
