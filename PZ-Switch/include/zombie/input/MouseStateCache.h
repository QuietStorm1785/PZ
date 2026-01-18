#pragma once
#include <mutex>
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

 // Mutexes for synchronized blocks
 std::mutex m_lock_mutex;
 const void *m_lock = "MouseStateCache Lock";
 int m_stateIndexUsing = 0;
 int m_stateIndexPolling = 1;
private
 MouseState[] m_states = new MouseState[]{
 std::make_unique<MouseState>(), std::make_unique<MouseState>()};

 void poll() {
 { std::lock_guard<std::mutex> __sync_lock__(m_lock_mutex);
 MouseState mouseState = this->getStatePolling();
 if (!mouseState.wasPolled()) {
 mouseState.poll();
 }
 }
 }

 void swap() {
 { std::lock_guard<std::mutex> __sync_lock__(m_lock_mutex);
 if (this->getStatePolling().wasPolled()) {
 this->m_stateIndexUsing = this->m_stateIndexPolling;
 this->m_stateIndexPolling = this->m_stateIndexPolling == 1 ? 0 : 1;
 this->getStatePolling().set(this->getState());
 this->getStatePolling().reset();
 }
 }
 }

 MouseState getState() {
 { std::lock_guard<std::mutex> __sync_lock__(m_lock_mutex); return this->m_states[this->m_stateIndexUsing]; }
 }

 MouseState getStatePolling() {
 { std::lock_guard<std::mutex> __sync_lock__(m_lock_mutex);
 return this->m_states[this->m_stateIndexPolling];
 }
 }
}
} // namespace input
} // namespace zombie
