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

class CompositeStructure {
public:
   public Bridge[] bridges;
   public Object[] values;
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
