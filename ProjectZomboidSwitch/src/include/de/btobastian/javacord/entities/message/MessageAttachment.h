#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class MessageAttachment {
public:
    virtual ~MessageAttachment() = default;
    URL getUrl();

    URL getProxyUrl();

    int getSize();

    std::string getId();

    std::string getFileName();
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
