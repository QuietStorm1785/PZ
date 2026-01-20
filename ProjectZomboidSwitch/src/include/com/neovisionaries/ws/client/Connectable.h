#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class Connectable {
public:
    const WebSocket mWebSocket;

    public Connectable(WebSocket ws) {
      this.mWebSocket = ws;
   }

    WebSocket call() {
      return this.mWebSocket.connect();
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
