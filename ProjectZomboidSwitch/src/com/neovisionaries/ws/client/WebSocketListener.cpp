#include <string>
#include "com/neovisionaries/ws/client/WebSocketListener.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

void WebSocketListener::onStateChanged(WebSocket var1, WebSocketState var2) {
    // TODO: Implement onStateChanged
}

void WebSocketListener::onConnected(WebSocket var1, List<std::string>> var2) {
    // TODO: Implement onConnected
}

void WebSocketListener::onConnectError(WebSocket var1, WebSocketException var2) {
    // TODO: Implement onConnectError
}

void WebSocketListener::onDisconnected(WebSocket var1, WebSocketFrame var2, WebSocketFrame var3, bool var4) {
    // TODO: Implement onDisconnected
}

void WebSocketListener::onFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onFrame
}

void WebSocketListener::onContinuationFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onContinuationFrame
}

void WebSocketListener::onTextFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onTextFrame
}

void WebSocketListener::onBinaryFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onBinaryFrame
}

void WebSocketListener::onCloseFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onCloseFrame
}

void WebSocketListener::onPingFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onPingFrame
}

void WebSocketListener::onPongFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onPongFrame
}

void WebSocketListener::onTextMessage(WebSocket var1, const std::string& var2) {
    // TODO: Implement onTextMessage
}

void WebSocketListener::onBinaryMessage(WebSocket var1, byte[] var2) {
    // TODO: Implement onBinaryMessage
}

void WebSocketListener::onSendingFrame(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onSendingFrame
}

void WebSocketListener::onFrameSent(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onFrameSent
}

void WebSocketListener::onFrameUnsent(WebSocket var1, WebSocketFrame var2) {
    // TODO: Implement onFrameUnsent
}

void WebSocketListener::onError(WebSocket var1, WebSocketException var2) {
    // TODO: Implement onError
}

void WebSocketListener::onFrameError(WebSocket var1, WebSocketException var2, WebSocketFrame var3) {
    // TODO: Implement onFrameError
}

void WebSocketListener::onMessageError(WebSocket var1, WebSocketException var2, List<WebSocketFrame> var3) {
    // TODO: Implement onMessageError
}

void WebSocketListener::onMessageDecompressionError(WebSocket var1, WebSocketException var2, byte[] var3) {
    // TODO: Implement onMessageDecompressionError
}

void WebSocketListener::onTextMessageError(WebSocket var1, WebSocketException var2, byte[] var3) {
    // TODO: Implement onTextMessageError
}

void WebSocketListener::onSendError(WebSocket var1, WebSocketException var2, WebSocketFrame var3) {
    // TODO: Implement onSendError
}

void WebSocketListener::onUnexpectedError(WebSocket var1, WebSocketException var2) {
    // TODO: Implement onUnexpectedError
}

void WebSocketListener::handleCallbackError(WebSocket var1, std::exception var2) {
    // TODO: Implement handleCallbackError
}

void WebSocketListener::onSendingHandshake(WebSocket var1, const std::string& var2, List<std::string[]> var3) {
    // TODO: Implement onSendingHandshake
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
