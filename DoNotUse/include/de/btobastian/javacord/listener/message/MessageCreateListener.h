#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace message {


class MessageCreateListener {
public:
    virtual ~MessageCreateListener() = default;
    void onMessageCreate(DiscordAPI var1, Message var2);
}
} // namespace message
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
