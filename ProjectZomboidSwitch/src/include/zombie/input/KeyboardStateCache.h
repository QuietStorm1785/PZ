#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace input {

class KeyboardStateCache {
public:
    const void* m_lock = "KeyboardStateCache Lock";
    int m_stateIndexUsing = 0;
    int m_stateIndexPolling = 1;
   private const KeyboardState[] m_states = new KeyboardState[]{std::make_unique<KeyboardState>(), std::make_unique<KeyboardState>()};

    void poll() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
    KeyboardState var2 = this.getStatePolling();
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

    KeyboardState getState() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexUsing];
      }
   }

    KeyboardState getStatePolling() {
      /* synchronized - TODO: add std::mutex */ (this.m_lock) {
         return this.m_states[this.m_stateIndexPolling];
      }
   }
}
} // namespace input
} // namespace zombie
