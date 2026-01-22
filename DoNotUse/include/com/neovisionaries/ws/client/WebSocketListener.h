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


class WebSocketListener {
public:
    virtual ~WebSocketListener() = default;
    void onStateChanged(WebSocket var1, WebSocketState var2);

    void onConnected(WebSocket var1, List<std::string>> var2);

    void onConnectError(WebSocket var1, WebSocketException var2);

    void onDisconnected(WebSocket var1, WebSocketFrame var2, WebSocketFrame var3, bool var4);

    void onFrame(WebSocket var1, WebSocketFrame var2);

    void onContinuationFrame(WebSocket var1, WebSocketFrame var2);

    void onTextFrame(WebSocket var1, WebSocketFrame var2);

    void onBinaryFrame(WebSocket var1, WebSocketFrame var2);

    void onCloseFrame(WebSocket var1, WebSocketFrame var2);

    void onPingFrame(WebSocket var1, WebSocketFrame var2);

    void onPongFrame(WebSocket var1, WebSocketFrame var2);

    void onTextMessage(WebSocket var1, const std::string& var2);

    void onBinaryMessage(WebSocket var1, byte[] var2);

    void onSendingFrame(WebSocket var1, WebSocketFrame var2);

    void onFrameSent(WebSocket var1, WebSocketFrame var2);

    void onFrameUnsent(WebSocket var1, WebSocketFrame var2);

    void onError(WebSocket var1, WebSocketException var2);

    void onFrameError(WebSocket var1, WebSocketException var2, WebSocketFrame var3);

    void onMessageError(WebSocket var1, WebSocketException var2, List<WebSocketFrame> var3);

    void onMessageDecompressionError(WebSocket var1, WebSocketException var2, byte[] var3);

    void onTextMessageError(WebSocket var1, WebSocketException var2, byte[] var3);

    void onSendError(WebSocket var1, WebSocketException var2, WebSocketFrame var3);

    void onUnexpectedError(WebSocket var1, WebSocketException var2);

    void handleCallbackError(WebSocket var1, std::exception var2);

    void onSendingHandshake(WebSocket var1, const std::string& var2, List<std::string[]> var3);
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
