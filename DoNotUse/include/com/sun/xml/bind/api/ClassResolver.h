#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


class ClassResolver {
public:
   public abstract Class<?> resolveElementName(@NotNull std::string var1, @NotNull std::string var2) throws Exception;
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
