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
namespace embed {


class EmbedAuthor {
public:
    virtual ~EmbedAuthor() = default;
    std::string getName();

    URL getUrl();

    URL getIconUrl();

    URL getProxyIconUrl();
}
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
