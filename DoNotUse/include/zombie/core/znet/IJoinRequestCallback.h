#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {

class IJoinRequestCallback {
public:
    virtual ~IJoinRequestCallback() = default;
    void onJoinRequest(long var1, const std::string& var3);
}
} // namespace znet
} // namespace core
} // namespace zombie
