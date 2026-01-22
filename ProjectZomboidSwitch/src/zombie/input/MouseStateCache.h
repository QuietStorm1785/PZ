#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace input {

class MouseStateCache {
public:
    const void* m_lock = "MouseStateCache Lock";
    int m_stateIndexUsing = 0;
    int m_stateIndexPolling = 1;
   private const MouseState[] m_states = new MouseState[]{std::make_unique<MouseState>(), std::make_unique<MouseState>()};

    void poll() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
    MouseState var2 = this.getStatePolling();
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

    MouseState getState() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexUsing];
      }
   }

    MouseState getStatePolling() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexPolling];
      }
   }
}
} // namespace input
} // namespace zombie
