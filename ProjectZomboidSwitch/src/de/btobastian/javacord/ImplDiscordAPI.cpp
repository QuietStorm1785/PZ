#include <string>
#include "de\btobastian\javacord/ImplDiscordAPI.h"

namespace de {
namespace btobastian {
namespace javacord {

public ImplDiscordAPI::ImplDiscordAPI(ThreadPool pool) {
    // TODO: Implement ImplDiscordAPI
    return nullptr;
}

void ImplDiscordAPI::connect(FutureCallback<DiscordAPI> callback) {
    // TODO: Implement connect
}

void ImplDiscordAPI::connectBlocking() {
    // TODO: Implement connectBlocking
}

void ImplDiscordAPI::setEmail(const std::string& email) {
    // TODO: Implement setEmail
}

void ImplDiscordAPI::setPassword(const std::string& password) {
    // TODO: Implement setPassword
}

void ImplDiscordAPI::setGame(const std::string& game) {
    // TODO: Implement setGame
}

void ImplDiscordAPI::setGame(const std::string& game, const std::string& streamingUrl) {
    // TODO: Implement setGame
}

std::string ImplDiscordAPI::getGame() {
    // TODO: Implement getGame
    return "";
}

std::string ImplDiscordAPI::getStreamingUrl() {
    // TODO: Implement getStreamingUrl
    return "";
}

Server ImplDiscordAPI::getServerById(const std::string& id) {
    // TODO: Implement getServerById
    return nullptr;
}

Channel ImplDiscordAPI::getChannelById(const std::string& id) {
    // TODO: Implement getChannelById
    return nullptr;
}

VoiceChannel ImplDiscordAPI::getVoiceChannelById(const std::string& id) {
    // TODO: Implement getVoiceChannelById
    return nullptr;
}

User ImplDiscordAPI::getCachedUserById(const std::string& id) {
    // TODO: Implement getCachedUserById
    return nullptr;
}

void ImplDiscordAPI::registerListener(Listener listener) {
    // TODO: Implement registerListener
}

Message ImplDiscordAPI::getMessageById(const std::string& id) {
    // TODO: Implement getMessageById
    return nullptr;
}

ThreadPool ImplDiscordAPI::getThreadPool() {
    // TODO: Implement getThreadPool
    return nullptr;
}

void ImplDiscordAPI::setIdle(bool idle) {
    // TODO: Implement setIdle
}

bool ImplDiscordAPI::isIdle() {
    // TODO: Implement isIdle
    return false;
}

std::string ImplDiscordAPI::getToken() {
    // TODO: Implement getToken
    return "";
}

void ImplDiscordAPI::setToken(const std::string& token, bool bot) {
    // TODO: Implement setToken
}

bool ImplDiscordAPI::checkTokenBlocking(const std::string& token) {
    // TODO: Implement checkTokenBlocking
    return false;
}

User ImplDiscordAPI::getYourself() {
    // TODO: Implement getYourself
    return nullptr;
}

void ImplDiscordAPI::setMessageCacheSize(int size) {
    // TODO: Implement setMessageCacheSize
}

int ImplDiscordAPI::getMessageCacheSize() {
    // TODO: Implement getMessageCacheSize
    return 0;
}

PermissionsBuilder ImplDiscordAPI::getPermissionsBuilder() {
    // TODO: Implement getPermissionsBuilder
    return nullptr;
}

PermissionsBuilder ImplDiscordAPI::getPermissionsBuilder(Permissions permissions) {
    // TODO: Implement getPermissionsBuilder
    return nullptr;
}

void ImplDiscordAPI::setAutoReconnect(bool autoReconnect) {
    // TODO: Implement setAutoReconnect
}

bool ImplDiscordAPI::isAutoReconnectEnabled() {
    // TODO: Implement isAutoReconnectEnabled
    return false;
}

RateLimitManager ImplDiscordAPI::getRateLimitManager() {
    // TODO: Implement getRateLimitManager
    return nullptr;
}

void ImplDiscordAPI::setWaitForServersOnStartup(bool wait) {
    // TODO: Implement setWaitForServersOnStartup
}

bool ImplDiscordAPI::isWaitingForServersOnStartup() {
    // TODO: Implement isWaitingForServersOnStartup
    return false;
}

void ImplDiscordAPI::disconnect() {
    // TODO: Implement disconnect
}

void ImplDiscordAPI::setReconnectRatelimit(int attempts, int seconds) {
    // TODO: Implement setReconnectRatelimit
}

void ImplDiscordAPI::setLazyLoading(bool enabled) {
    // TODO: Implement setLazyLoading
}

bool ImplDiscordAPI::isLazyLoading() {
    // TODO: Implement isLazyLoading
    return false;
}

void ImplDiscordAPI::setYourself(User user) {
    // TODO: Implement setYourself
}

User ImplDiscordAPI::getOrCreateUser(JSONObject data) {
    // TODO: Implement getOrCreateUser
    return nullptr;
}

DiscordWebsocketAdapter ImplDiscordAPI::getSocketAdapter() {
    // TODO: Implement getSocketAdapter
    return nullptr;
}

std::string ImplDiscordAPI::requestTokenBlocking() {
    // TODO: Implement requestTokenBlocking
    return "";
}

std::string ImplDiscordAPI::requestGatewayBlocking() {
    // TODO: Implement requestGatewayBlocking
    return "";
}

void ImplDiscordAPI::addMessage(Message message) {
    // TODO: Implement addMessage
}

void ImplDiscordAPI::removeMessage(Message message) {
    // TODO: Implement removeMessage
}

void ImplDiscordAPI::addHistory(MessageHistory history) {
    // TODO: Implement addHistory
}

void ImplDiscordAPI::checkResponse(HttpResponse<JsonNode> response) {
    // TODO: Implement checkResponse
}

void ImplDiscordAPI::checkRateLimit(HttpResponse<JsonNode> response, RateLimitType type, Server server, Channel channel) {
    // TODO: Implement checkRateLimit
}

ServerJoinListener ImplDiscordAPI::getInternalServerJoinListener() {
    // TODO: Implement getInternalServerJoinListener
    return nullptr;
}

void ImplDiscordAPI::setSocketAdapter(DiscordWebsocketAdapter socketAdapter) {
    // TODO: Implement setSocketAdapter
}

} // namespace javacord
} // namespace btobastian
} // namespace de
