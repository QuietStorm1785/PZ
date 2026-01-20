#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/message/Reaction.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace message {


class ReactionAddListener {
public:
    virtual ~ReactionAddListener() = default;
    void onReactionAdd(DiscordAPI var1, Reaction var2, User var3);
}
} // namespace message
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
