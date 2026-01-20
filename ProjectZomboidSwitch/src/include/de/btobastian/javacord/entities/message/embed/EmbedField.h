#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {

class EmbedField {
public:
    virtual ~EmbedField() = default;
    std::string getName();

    std::string getValue();

    bool isInline();
}
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
