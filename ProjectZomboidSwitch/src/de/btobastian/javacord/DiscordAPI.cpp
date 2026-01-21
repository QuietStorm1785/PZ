#include <string>
#include "de/btobastian/javacord/DiscordAPI.h"

namespace de {
namespace btobastian {
namespace javacord {

void DiscordAPI::connect(FutureCallback<DiscordAPI> var1) {
    // TODO: Implement connect
}

void DiscordAPI::connectBlocking() {
    // TODO: Implement connectBlocking
}

void DiscordAPI::setEmail(const std::string& var1) {
    // TODO: Implement setEmail
}

void DiscordAPI::setPassword(const std::string& var1) {
    // TODO: Implement setPassword
}

void DiscordAPI::setGame(const std::string& var1) {
    // TODO: Implement setGame
}

void DiscordAPI::setGame(const std::string& var1, const std::string& var2) {
    // TODO: Implement setGame
}

std::string DiscordAPI::getGame() {
    // TODO: Implement getGame
    return "";
}

std::string DiscordAPI::getStreamingUrl() {
    // TODO: Implement getStreamingUrl
    return "";
}

Server DiscordAPI::getServerById(const std::string& var1) {
    // TODO: Implement getServerById
    return nullptr;
}

Channel DiscordAPI::getChannelById(const std::string& var1) {
    // TODO: Implement getChannelById
    return nullptr;
}

VoiceChannel DiscordAPI::getVoiceChannelById(const std::string& var1) {
    // TODO: Implement getVoiceChannelById
    return nullptr;
}

User DiscordAPI::getCachedUserById(const std::string& var1) {
    // TODO: Implement getCachedUserById
    return nullptr;
}

void DiscordAPI::registerListener(Listener var1) {
    // TODO: Implement registerListener
}

Message DiscordAPI::getMessageById(const std::string& var1) {
    // TODO: Implement getMessageById
    return nullptr;
}

ThreadPool DiscordAPI::getThreadPool() {
    // TODO: Implement getThreadPool
    return nullptr;
}

void DiscordAPI::setIdle(bool var1) {
    // TODO: Implement setIdle
}

bool DiscordAPI::isIdle() {
    // TODO: Implement isIdle
    return false;
}

std::string DiscordAPI::getToken() {
    // TODO: Implement getToken
    return "";
}

void DiscordAPI::setToken(const std::string& var1, bool var2) {
    // TODO: Implement setToken
}

bool DiscordAPI::checkTokenBlocking(const std::string& var1) {
    // TODO: Implement checkTokenBlocking
    return false;
}

User DiscordAPI::getYourself() {
    // TODO: Implement getYourself
    return nullptr;
}

void DiscordAPI::setMessageCacheSize(int var1) {
    // TODO: Implement setMessageCacheSize
}

int DiscordAPI::getMessageCacheSize() {
    // TODO: Implement getMessageCacheSize
    return 0;
}

PermissionsBuilder DiscordAPI::getPermissionsBuilder() {
    // TODO: Implement getPermissionsBuilder
    return nullptr;
}

PermissionsBuilder DiscordAPI::getPermissionsBuilder(Permissions var1) {
    // TODO: Implement getPermissionsBuilder
    return nullptr;
}

void DiscordAPI::setAutoReconnect(bool var1) {
    // TODO: Implement setAutoReconnect
}

bool DiscordAPI::isAutoReconnectEnabled() {
    // TODO: Implement isAutoReconnectEnabled
    return false;
}

RateLimitManager DiscordAPI::getRateLimitManager() {
    // TODO: Implement getRateLimitManager
    return nullptr;
}

void DiscordAPI::setWaitForServersOnStartup(bool var1) {
    // TODO: Implement setWaitForServersOnStartup
}

bool DiscordAPI::isWaitingForServersOnStartup() {
    // TODO: Implement isWaitingForServersOnStartup
    return false;
}

void DiscordAPI::disconnect() {
    // TODO: Implement disconnect
}

void DiscordAPI::setReconnectRatelimit(int var1, int var2) {
    // TODO: Implement setReconnectRatelimit
}

void DiscordAPI::setLazyLoading(bool var1) {
    // TODO: Implement setLazyLoading
}

bool DiscordAPI::isLazyLoading() {
    // TODO: Implement isLazyLoading
    return false;
}

} // namespace javacord
} // namespace btobastian
} // namespace de
