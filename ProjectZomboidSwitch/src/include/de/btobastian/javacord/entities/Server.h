#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/permissions/Ban.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/URL.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class Server {
public:
    virtual ~Server() = default;
    std::string getId();

    Calendar getCreationDate();

    std::string getName();

   Future<Void> delete();

   Future<Void> leave();

    Channel getChannelById(const std::string& var1);

   Collection<Channel> getChannels();

    VoiceChannel getVoiceChannelById(const std::string& var1);

   Collection<VoiceChannel> getVoiceChannels();

    User getMemberById(const std::string& var1);

   Collection<User> getMembers();

    bool isMember(User var1);

    bool isMember(const std::string& var1);

   Collection<Role> getRoles();

    Role getRoleById(const std::string& var1);

   Future<Channel> createChannel(std::string var1);

   Future<Channel> createChannel(std::string var1, FutureCallback<Channel> var2);

   Future<VoiceChannel> createVoiceChannel(std::string var1);

   Future<VoiceChannel> createVoiceChannel(std::string var1, FutureCallback<VoiceChannel> var2);

   Future<Invite[]> getInvites();

   Future<Invite[]> getInvites(FutureCallback<Invite[]> var1);

   Future<Void> updateRoles(User var1, Role[] var2);

   Future<Void> banUser(User var1);

   Future<Void> banUser(std::string var1);

   Future<Void> banUser(User var1, int var2);

   Future<Void> banUser(std::string var1, int var2);

   Future<Void> unbanUser(std::string var1);

   Future<Ban[]> getBans();

   Future<Ban[]> getBans(FutureCallback<Ban[]> var1);

   Future<Void> kickUser(User var1);

   Future<Void> kickUser(std::string var1);

   Future<Role> createRole();

   Future<Role> createRole(FutureCallback<Role> var1);

   Future<Void> updateName(std::string var1);

   Future<Void> updateRegion(Region var1);

   Future<Void> updateIcon(BufferedImage var1);

   Future<Void> update(std::string var1, Region var2, BufferedImage var3);

    Region getRegion();

    int getMemberCount();

    bool isLarge();

    std::string getOwnerId();

   Future<User> getOwner();

   Collection<CustomEmoji> getCustomEmojis();

    CustomEmoji getCustomEmojiById(const std::string& var1);

    CustomEmoji getCustomEmojiByName(const std::string& var1);

    std::string getNickname(User var1);

    bool hasNickname(User var1);

   Future<Void> updateNickname(User var1, std::string var2);

    URL getIconUrl();

   Future<byte[]> getIcon();

   Future<byte[]> getIcon(FutureCallback<byte[]> var1);
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
