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

class EnumLeafInfo {
public:
    virtual ~EnumLeafInfo() = default;
    C getClazz();

   NonElement<T, C> getBaseType();

   Iterable<? : public EnumConstant> getConstants();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
