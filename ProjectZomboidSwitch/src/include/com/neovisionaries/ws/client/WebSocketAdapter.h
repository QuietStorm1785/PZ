#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocketAdapter {
public:
    void onStateChanged(WebSocket websocket, WebSocketState newState) {
   }

    void onConnected(WebSocket websocket, List<std::string>> headers) {
   }

    void onConnectError(WebSocket websocket, WebSocketException exception) {
   }

    void onDisconnected(WebSocket websocket, WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
   }

    void onFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onContinuationFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onTextFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onBinaryFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onCloseFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onPingFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onPongFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onTextMessage(WebSocket websocket, const std::string& text) {
   }

    void onBinaryMessage(WebSocket websocket, byte[] binary) {
   }

    void onSendingFrame(WebSocket websocket, WebSocketFrame frame) {
   }

    void onFrameSent(WebSocket websocket, WebSocketFrame frame) {
   }

    void onFrameUnsent(WebSocket websocket, WebSocketFrame frame) {
   }

    void onError(WebSocket websocket, WebSocketException cause) {
   }

    void onFrameError(WebSocket websocket, WebSocketException cause, WebSocketFrame frame) {
   }

    void onMessageError(WebSocket websocket, WebSocketException cause, List<WebSocketFrame> frames) {
   }

    void onMessageDecompressionError(WebSocket websocket, WebSocketException cause, byte[] compressed) {
   }

    void onTextMessageError(WebSocket websocket, WebSocketException cause, byte[] data) {
   }

    void onSendError(WebSocket websocket, WebSocketException cause, WebSocketFrame frame) {
   }

    void onUnexpectedError(WebSocket websocket, WebSocketException cause) {
   }

    void handleCallbackError(WebSocket websocket, std::exception cause) {
   }

    void onSendingHandshake(WebSocket websocket, const std::string& requestLine, List<std::string[]> headers) {
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
