#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "java/net/URL.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class Invite {
public:
    virtual ~Invite() = default;
    std::string getCode();

    URL getInviteUrl();

    std::string getServerId();

    std::string getServerName();

    Server getServer();

    std::string getChannelId();

    std::string getChannelName();

    Channel getChannel();

    VoiceChannel getVoiceChannel();

    bool isVoiceChannel();

    int getMaxAge();

    bool isRevoked();

    Calendar getCreationDate();

    int getUses();

    int getMaxUses();

    bool isTemporary();

    User getCreator();

   Future<Server> acceptInvite();

   Future<Server> acceptInvite(FutureCallback<Server> var1);

   Future<Void> delete();
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
