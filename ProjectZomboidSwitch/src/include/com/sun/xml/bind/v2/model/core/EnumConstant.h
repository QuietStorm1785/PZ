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

class EnumConstant {
public:
    virtual ~EnumConstant() = default;
   EnumLeafInfo<T, C> getEnclosingClass();

    std::string getLexicalValue();

    std::string getName();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
