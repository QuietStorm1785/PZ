#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/message/MessageReceiver.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/URL.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class User {
public:
    virtual ~User() = default;
    std::string getId();

    Calendar getCreationDate();

    std::string getName();

    std::string getNickname(Server var1);

    bool hasNickname(Server var1);

   Future<Void> updateNickname(Server var1, std::string var2);

    bool isYourself();

   Future<byte[]> getAvatarAsByteArray();

   Future<byte[]> getAvatarAsByteArray(FutureCallback<byte[]> var1);

   Future<BufferedImage> getAvatar();

   Future<BufferedImage> getAvatar(FutureCallback<BufferedImage> var1);

    URL getAvatarUrl();

    std::string getAvatarId();

   Collection<Role> getRoles(Server var1);

    std::string getGame();

    std::string getMentionTag();

    std::string getDiscriminator();

    bool isBot();

    UserStatus getStatus();

    VoiceChannel getVoiceChannel();
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
