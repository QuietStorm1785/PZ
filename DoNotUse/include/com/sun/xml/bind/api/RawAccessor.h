#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {

class RawAccessor {
public:
   public abstract V get(B var1) throws AccessorException;

   public abstract void set(B var1, V var2) throws AccessorException;
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
