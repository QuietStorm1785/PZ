#include <string>
#include "com/neovisionaries/ws/client/ListenerManager.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

public ListenerManager::ListenerManager(WebSocket websocket) {
    // TODO: Implement ListenerManager
    return nullptr;
}

void ListenerManager::addListener(WebSocketListener listener) {
    // TODO: Implement addListener
}

void ListenerManager::addListeners(List<WebSocketListener> listeners) {
    // TODO: Implement addListeners
}

void ListenerManager::removeListener(WebSocketListener listener) {
    // TODO: Implement removeListener
}

void ListenerManager::removeListeners(List<WebSocketListener> listeners) {
    // TODO: Implement removeListeners
}

void ListenerManager::clearListeners() {
    // TODO: Implement clearListeners
}

void ListenerManager::callOnStateChanged(WebSocketState newState) {
    // TODO: Implement callOnStateChanged
}

void ListenerManager::callOnConnected(List<std::string>> headers) {
    // TODO: Implement callOnConnected
}

void ListenerManager::callOnConnectError(WebSocketException cause) {
    // TODO: Implement callOnConnectError
}

void ListenerManager::callOnDisconnected(WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
    // TODO: Implement callOnDisconnected
}

void ListenerManager::callOnFrame(WebSocketFrame frame) {
    // TODO: Implement callOnFrame
}

void ListenerManager::callOnContinuationFrame(WebSocketFrame frame) {
    // TODO: Implement callOnContinuationFrame
}

void ListenerManager::callOnTextFrame(WebSocketFrame frame) {
    // TODO: Implement callOnTextFrame
}

void ListenerManager::callOnBinaryFrame(WebSocketFrame frame) {
    // TODO: Implement callOnBinaryFrame
}

void ListenerManager::callOnCloseFrame(WebSocketFrame frame) {
    // TODO: Implement callOnCloseFrame
}

void ListenerManager::callOnPingFrame(WebSocketFrame frame) {
    // TODO: Implement callOnPingFrame
}

void ListenerManager::callOnPongFrame(WebSocketFrame frame) {
    // TODO: Implement callOnPongFrame
}

void ListenerManager::callOnTextMessage(const std::string& message) {
    // TODO: Implement callOnTextMessage
}

void ListenerManager::callOnBinaryMessage(byte[] message) {
    // TODO: Implement callOnBinaryMessage
}

void ListenerManager::callOnSendingFrame(WebSocketFrame frame) {
    // TODO: Implement callOnSendingFrame
}

void ListenerManager::callOnFrameSent(WebSocketFrame frame) {
    // TODO: Implement callOnFrameSent
}

void ListenerManager::callOnFrameUnsent(WebSocketFrame frame) {
    // TODO: Implement callOnFrameUnsent
}

void ListenerManager::callOnError(WebSocketException cause) {
    // TODO: Implement callOnError
}

void ListenerManager::callOnFrameError(WebSocketException cause, WebSocketFrame frame) {
    // TODO: Implement callOnFrameError
}

void ListenerManager::callOnMessageError(WebSocketException cause, List<WebSocketFrame> frames) {
    // TODO: Implement callOnMessageError
}

void ListenerManager::callOnMessageDecompressionError(WebSocketException cause, byte[] compressed) {
    // TODO: Implement callOnMessageDecompressionError
}

void ListenerManager::callOnTextMessageError(WebSocketException cause, byte[] data) {
    // TODO: Implement callOnTextMessageError
}

void ListenerManager::callOnSendError(WebSocketException cause, WebSocketFrame frame) {
    // TODO: Implement callOnSendError
}

void ListenerManager::callOnUnexpectedError(WebSocketException cause) {
    // TODO: Implement callOnUnexpectedError
}

void ListenerManager::callHandleCallbackError(WebSocketListener listener, std::exception cause) {
    // TODO: Implement callHandleCallbackError
}

void ListenerManager::callOnSendingHandshake(const std::string& requestLine, List<std::string[]> headers) {
    // TODO: Implement callOnSendingHandshake
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
