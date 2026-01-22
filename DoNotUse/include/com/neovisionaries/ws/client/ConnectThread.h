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

class ConnectThread : public Thread {
public:
    const WebSocket mWebSocket;

    public ConnectThread(WebSocket ws) {
      super("ConnectThread");
      this.mWebSocket = ws;
   }

    void run() {
      try {
         this.mWebSocket.connect();
      } catch (WebSocketException var2) {
         this.handleError(var2);
      }
   }

    void handleError(WebSocketException cause) {
    ListenerManager manager = this.mWebSocket.getListenerManager();
      manager.callOnError(cause);
      manager.callOnConnectError(cause);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
