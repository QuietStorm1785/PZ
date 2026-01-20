#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class PayloadGenerator {
public:
    virtual ~PayloadGenerator() = default;
   byte[] generate();
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
