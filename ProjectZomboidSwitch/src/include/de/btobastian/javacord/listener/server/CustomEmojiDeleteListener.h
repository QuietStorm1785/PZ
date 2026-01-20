#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace server {


class CustomEmojiDeleteListener {
public:
    virtual ~CustomEmojiDeleteListener() = default;
    void onCustomEmojiDelete(DiscordAPI var1, CustomEmoji var2);
}
} // namespace server
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
