#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KeyboardStateCache {
public:
  const void *m_lock = "KeyboardStateCache Lock";
  int m_stateIndexUsing = 0;
  int m_stateIndexPolling = 1;
private
  final KeyboardState[] m_states = new KeyboardState[]{
      std::make_unique<KeyboardState>(), std::make_unique<KeyboardState>()};

  void poll() {
    synchronized(this.m_lock) {
      KeyboardState keyboardState = this.getStatePolling();
      if (!keyboardState.wasPolled()) {
        keyboardState.poll();
      }
    }
  }

  void swap() {
    synchronized(this.m_lock) {
      if (this.getStatePolling().wasPolled()) {
        this.m_stateIndexUsing = this.m_stateIndexPolling;
        this.m_stateIndexPolling = this.m_stateIndexPolling == 1 ? 0 : 1;
        this.getStatePolling().set(this.getState());
        this.getStatePolling().reset();
      }
    }
  }

  KeyboardState getState() {
    synchronized(this.m_lock) { return this.m_states[this.m_stateIndexUsing]; }
  }

  KeyboardState getStatePolling() {
    synchronized(this.m_lock) {
      return this.m_states[this.m_stateIndexPolling];
    }
  }
}
} // namespace input
} // namespace zombie
