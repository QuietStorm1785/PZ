#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {

class IAnimatable {
public:
    virtual ~IAnimatable() = default;
    void Play(const std::string& var1);

    void Update(float var1);
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
