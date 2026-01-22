#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/StateManager/CloseInitiator.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class StateManager {
public:
    WebSocketState mState;
    CloseInitiator mCloseInitiator = CloseInitiator.NONE;

    public StateManager() {
      this.mState = WebSocketState.CREATED;
   }

    WebSocketState getState() {
      return this.mState;
   }

    void setState(WebSocketState state) {
      this.mState = state;
   }

    void changeToClosing(CloseInitiator closeInitiator) {
      this.mState = WebSocketState.CLOSING;
      if (this.mCloseInitiator == CloseInitiator.NONE) {
         this.mCloseInitiator = closeInitiator;
      }
   }

    bool getClosedByServer() {
      return this.mCloseInitiator == CloseInitiator.SERVER;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
