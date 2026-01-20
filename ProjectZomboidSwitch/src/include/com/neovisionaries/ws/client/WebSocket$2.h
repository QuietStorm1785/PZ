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

// $VF: synthetic class
class WebSocket {
public:
   static {
      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketState[WebSocketState.CREATED.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketState[WebSocketState.OPEN.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
