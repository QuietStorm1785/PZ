#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {


class Ban {
public:
    virtual ~Ban() = default;
    User getUser();

    Server getServer();

    std::string getReason();
}
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
