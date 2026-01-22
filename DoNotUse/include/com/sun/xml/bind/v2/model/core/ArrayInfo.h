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
namespace v2 {
namespace model {
namespace core {

class ArrayInfo {
public:
    virtual ~ArrayInfo() = default;
   NonElement<T, C> getItemType();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
