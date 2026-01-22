#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/PermissionsBuilder.h"
#include "de/btobastian/javacord/listener/Listener.h"
#include "de/btobastian/javacord/utils/ThreadPool.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitManager.h"
#include "java/awt/image/BufferedImage.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {


class DiscordAPI {
public:
    virtual ~DiscordAPI() = default;

    // Use std::function for callbacks, std::future for async results, STL containers for collections
    void connect(std::function<void(DiscordAPI&)> callback);
    void connectBlocking();

    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    void setGame(const std::string& game);
    void setGame(const std::string& game, const std::string& details);
    std::string getGame() const;
    std::string getStreamingUrl() const;

    Server getServerById(const std::string& id) const;
    std::vector<Server> getServers() const;
    std::vector<Channel> getChannels() const;
    Channel getChannelById(const std::string& id) const;
    std::vector<VoiceChannel> getVoiceChannels() const;
    VoiceChannel getVoiceChannelById(const std::string& id) const;

    std::future<User> getUserById(const std::string& id);
    User getCachedUserById(const std::string& id) const;
    std::vector<User> getUsers() const;

    void registerListener(const Listener& listener);
    Message getMessageById(const std::string& id) const;
    ThreadPool& getThreadPool();

    void setIdle(bool idle);
    bool isIdle() const;
    std::string getToken() const;
    void setToken(const std::string& token, bool bot);
    bool checkTokenBlocking(const std::string& token) const;

    std::future<Server> acceptInvite(const std::string& inviteCode);
    std::future<Server> createServer(const std::string& name);
    std::future<Server> createServer(const std::string& name, const Region& region);
    std::future<Server> createServer(const std::string& name, const Region& region, const std::string& iconPath);

    User getYourself() const;
    std::future<void> updateUsername(const std::string& username);
    std::future<void> updateEmail(const std::string& email);
    std::future<void> updatePassword(const std::string& password);
    std::future<void> updateAvatar(const std::string& avatarPath);
    std::future<void> updateProfile(const std::string& username, const std::string& email, const std::string& password, const std::string& avatarPath);

    std::future<Invite> parseInvite(const std::string& inviteCode);
    std::future<void> deleteInvite(const std::string& inviteCode);

    void setMessageCacheSize(int size);
    int getMessageCacheSize() const;
    PermissionsBuilder getPermissionsBuilder() const;
    PermissionsBuilder getPermissionsBuilder(const Permissions& permissions) const;
    void setAutoReconnect(bool enabled);
    bool isAutoReconnectEnabled() const;
    RateLimitManager& getRateLimitManager();
    void setWaitForServersOnStartup(bool wait);
    bool isWaitingForServersOnStartup() const;
    void disconnect();
    void setReconnectRatelimit(int min, int max);
    void setLazyLoading(bool lazy);
    bool isLazyLoading() const;
};
} // namespace javacord
} // namespace btobastian
} // namespace de
