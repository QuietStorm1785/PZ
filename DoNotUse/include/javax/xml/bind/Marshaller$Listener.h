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

class Marshaller {
public:
    void beforeMarshal(void* source) {
   }

    void afterMarshal(void* source) {
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
