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

class Unmarshaller {
public:
    void beforeUnmarshal(void* target, void* parent) {
   }

    void afterUnmarshal(void* target, void* parent) {
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
