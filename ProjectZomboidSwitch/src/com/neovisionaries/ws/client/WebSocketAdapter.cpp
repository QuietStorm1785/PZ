#include <string>
#include "com\neovisionaries\ws\client/WebSocketAdapter.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

void WebSocketAdapter::onStateChanged(WebSocket websocket, WebSocketState newState) {
    // TODO: Implement onStateChanged
}

void WebSocketAdapter::onConnected(WebSocket websocket, List<std::string>> headers) {
    // TODO: Implement onConnected
}

void WebSocketAdapter::onConnectError(WebSocket websocket, WebSocketException exception) {
    // TODO: Implement onConnectError
}

void WebSocketAdapter::onDisconnected(WebSocket websocket, WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
    // TODO: Implement onDisconnected
}

void WebSocketAdapter::onFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onFrame
}

void WebSocketAdapter::onContinuationFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onContinuationFrame
}

void WebSocketAdapter::onTextFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onTextFrame
}

void WebSocketAdapter::onBinaryFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onBinaryFrame
}

void WebSocketAdapter::onCloseFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onCloseFrame
}

void WebSocketAdapter::onPingFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onPingFrame
}

void WebSocketAdapter::onPongFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onPongFrame
}

void WebSocketAdapter::onTextMessage(WebSocket websocket, const std::string& text) {
    // TODO: Implement onTextMessage
}

void WebSocketAdapter::onBinaryMessage(WebSocket websocket, byte[] binary) {
    // TODO: Implement onBinaryMessage
}

void WebSocketAdapter::onSendingFrame(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onSendingFrame
}

void WebSocketAdapter::onFrameSent(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onFrameSent
}

void WebSocketAdapter::onFrameUnsent(WebSocket websocket, WebSocketFrame frame) {
    // TODO: Implement onFrameUnsent
}

void WebSocketAdapter::onError(WebSocket websocket, WebSocketException cause) {
    // TODO: Implement onError
}

void WebSocketAdapter::onFrameError(WebSocket websocket, WebSocketException cause, WebSocketFrame frame) {
    // TODO: Implement onFrameError
}

void WebSocketAdapter::onMessageError(WebSocket websocket, WebSocketException cause, List<WebSocketFrame> frames) {
    // TODO: Implement onMessageError
}

void WebSocketAdapter::onMessageDecompressionError(WebSocket websocket, WebSocketException cause, byte[] compressed) {
    // TODO: Implement onMessageDecompressionError
}

void WebSocketAdapter::onTextMessageError(WebSocket websocket, WebSocketException cause, byte[] data) {
    // TODO: Implement onTextMessageError
}

void WebSocketAdapter::onSendError(WebSocket websocket, WebSocketException cause, WebSocketFrame frame) {
    // TODO: Implement onSendError
}

void WebSocketAdapter::onUnexpectedError(WebSocket websocket, WebSocketException cause) {
    // TODO: Implement onUnexpectedError
}

void WebSocketAdapter::handleCallbackError(WebSocket websocket, std::exception cause) {
    // TODO: Implement handleCallbackError
}

void WebSocketAdapter::onSendingHandshake(WebSocket websocket, const std::string& requestLine, List<std::string[]> headers) {
    // TODO: Implement onSendingHandshake
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
