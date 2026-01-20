#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/ConfigOption.h"

namespace zombie {
namespace network {


class ServerOptions {
public:
    virtual ~ServerOptions() = default;
    ConfigOption asConfigOption();

    std::string getTooltip();
}
} // namespace network
} // namespace zombie
