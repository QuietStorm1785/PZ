#include <string>
#include "de\btobastian\javacord\utils/DiscordWebsocketAdapter.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {

public DiscordWebsocketAdapter::DiscordWebsocketAdapter(ImplDiscordAPI api, const std::string& gateway) {
    // TODO: Implement DiscordWebsocketAdapter
    return nullptr;
}

void DiscordWebsocketAdapter::disconnect() {
    // TODO: Implement disconnect
}

void DiscordWebsocketAdapter::connect() {
    // TODO: Implement connect
}

void DiscordWebsocketAdapter::onConnected(WebSocket websocket, List<std::string>> headers) {
    // TODO: Implement onConnected
}

void DiscordWebsocketAdapter::onDisconnected(WebSocket websocket, WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
    // TODO: Implement onDisconnected
}

void DiscordWebsocketAdapter::onTextMessage(WebSocket websocket, const std::string& text) {
    // TODO: Implement onTextMessage
}

void DiscordWebsocketAdapter::onBinaryMessage(WebSocket websocket, byte[] binary) {
    // TODO: Implement onBinaryMessage
}

Timer DiscordWebsocketAdapter::startHeartbeat(WebSocket websocket, int heartbeatInterval) {
    // TODO: Implement startHeartbeat
    return nullptr;
}

void DiscordWebsocketAdapter::sendHeartbeat(WebSocket websocket) {
    // TODO: Implement sendHeartbeat
}

void DiscordWebsocketAdapter::sendResume(WebSocket websocket) {
    // TODO: Implement sendResume
}

void DiscordWebsocketAdapter::sendIdentify(WebSocket websocket) {
    // TODO: Implement sendIdentify
}

new DiscordWebsocketAdapter::JSONObject() {
    // TODO: Implement JSONObject
    return nullptr;
}

new DiscordWebsocketAdapter::JSONObject() {
    // TODO: Implement JSONObject
    return nullptr;
}

void DiscordWebsocketAdapter::registerHandlers() {
    // TODO: Implement registerHandlers
}

void DiscordWebsocketAdapter::addHandler(PacketHandler handler) {
    // TODO: Implement addHandler
}

WebSocket DiscordWebsocketAdapter::getWebSocket() {
    // TODO: Implement getWebSocket
    return nullptr;
}

void DiscordWebsocketAdapter::updateStatus() {
    // TODO: Implement updateStatus
}

void DiscordWebsocketAdapter::setRatelimitResetIntervalInSeconds(int ratelimitResetIntervalInSeconds) {
    // TODO: Implement setRatelimitResetIntervalInSeconds
}

void DiscordWebsocketAdapter::setReconnectAttempts(int reconnectAttempts) {
    // TODO: Implement setReconnectAttempts
}

void DiscordWebsocketAdapter::onError(WebSocket websocket, WebSocketException cause) {
    // TODO: Implement onError
}

void DiscordWebsocketAdapter::onUnexpectedError(WebSocket websocket, WebSocketException cause) {
    // TODO: Implement onUnexpectedError
}

void DiscordWebsocketAdapter::onConnectError(WebSocket websocket, WebSocketException exception) {
    // TODO: Implement onConnectError
}

} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
