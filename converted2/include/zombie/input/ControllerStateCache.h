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

class ControllerStateCache {
public:
  const void *m_lock = "ControllerStateCache Lock";
  int m_stateIndexUsing = 0;
  int m_stateIndexPolling = 1;
private
  final ControllerState[] m_states = new ControllerState[]{
      std::make_unique<ControllerState>(), std::make_unique<ControllerState>()};

  void poll() {
    synchronized(this.m_lock) {
      ControllerState controllerState = this.getStatePolling();
      if (!controllerState.wasPolled()) {
        controllerState.poll();
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

  ControllerState getState() {
    synchronized(this.m_lock) { return this.m_states[this.m_stateIndexUsing]; }
  }

  ControllerState getStatePolling() {
    synchronized(this.m_lock) {
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
