#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {

class ServiceLoaderUtil {
public:
   public abstract T createException(Throwable var1, std::string var2);
}
} // namespace bind
} // namespace xml
} // namespace javax
