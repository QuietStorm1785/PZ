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
namespace annotation {
namespace adapters {


public @interface XmlJavaTypeAdapters {
   XmlJavaTypeAdapter[] value();
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
