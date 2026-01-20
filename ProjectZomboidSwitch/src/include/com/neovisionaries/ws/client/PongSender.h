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

class PongSender : public PeriodicalFrameSender {
public:
    static const std::string TIMER_NAME = "PongSender";

    public PongSender(WebSocket webSocket, PayloadGenerator generator) {
      super(webSocket, "PongSender", generator);
   }

    WebSocketFrame createFrame(byte[] payload) {
      return WebSocketFrame.createPongFrame(payload);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
