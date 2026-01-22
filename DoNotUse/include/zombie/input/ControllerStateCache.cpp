#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace input {

class ControllerStateCache {
public:
    const void* m_lock = "ControllerStateCache Lock";
    int m_stateIndexUsing = 0;
    int m_stateIndexPolling = 1;
   private const ControllerState[] m_states = new ControllerState[]{std::make_unique<ControllerState>(), std::make_unique<ControllerState>()};

    void poll() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
    ControllerState var2 = this.getStatePolling();
         if (!var2.wasPolled()) {
            var2.poll();
         }
      }
   }

    void swap() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         if (this.getStatePolling().wasPolled()) {
            this.m_stateIndexUsing = this.m_stateIndexPolling;
            this.m_stateIndexPolling = this.m_stateIndexPolling == 1 ? 0 : 1;
            this.getStatePolling().set(this.getState());
            this.getStatePolling().reset();
         }
      }
   }

    ControllerState getState() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexUsing];
      }
   }

    ControllerState getStatePolling() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexPolling];
      }
   }

    void quit() {
      this.m_states[0].quit();
      this.m_states[1].quit();
   }
}
} // namespace input
} // namespace zombie
