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

class MouseStateCache {
public:
  const void *m_lock = "MouseStateCache Lock";
  int m_stateIndexUsing = 0;
  int m_stateIndexPolling = 1;
private
  final MouseState[] m_states = new MouseState[]{
      std::make_unique<MouseState>(), std::make_unique<MouseState>()};

  void poll() {
    synchronized(this.m_lock) {
      MouseState mouseState = this.getStatePolling();
      if (!mouseState.wasPolled()) {
        mouseState.poll();
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

  MouseState getState() {
    synchronized(this.m_lock) { return this.m_states[this.m_stateIndexUsing]; }
  }

  MouseState getStatePolling() {
    synchronized(this.m_lock) {
      return this.m_states[this.m_stateIndexPolling];
    }
  }
}
} // namespace input
} // namespace zombie
