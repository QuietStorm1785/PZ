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


public @interface XmlAccessorFactory {
   Class<? : public AccessorFactory> value();
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
