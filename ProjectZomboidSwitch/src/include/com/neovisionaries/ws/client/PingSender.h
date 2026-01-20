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

class PingSender : public PeriodicalFrameSender {
public:
    static const std::string TIMER_NAME = "PingSender";

    public PingSender(WebSocket webSocket, PayloadGenerator generator) {
      super(webSocket, "PingSender", generator);
   }

    WebSocketFrame createFrame(byte[] payload) {
      return WebSocketFrame.createPingFrame(payload);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
