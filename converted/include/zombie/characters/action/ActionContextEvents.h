#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace action {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ActionContextEvents {
public:
 private ActionContextEvents.Event m_firstEvent;
 private ActionContextEvents.Event m_eventPool;

 void add(const std::string& name, int layer) {
 if (!this->contains(name, layer, false) {
 ActionContextEvents.Event event = this->allocEvent();
 event.name = name;
 event.layer = layer;
 event.next = this->m_firstEvent;
 this->m_firstEvent = event;
 }
 }

 bool contains(const std::string& name, int layer) {
 return this->contains(name, layer, true);
 }

 bool contains(const std::string& name, int layer, bool bAgnosticLayer) {
 for (ActionContextEvents.Event event = this->m_firstEvent; event != nullptr; event = event.next) {
 if (event.name.equalsIgnoreCase(name) {
 if (layer == -1) {
 return true;
 }

 if (event.layer == layer) {
 return true;
 }

 if (bAgnosticLayer && event.layer == -1) {
 return true;
 }
 }
 }

 return false;
 }

 void clear() {
 if (this->m_firstEvent != nullptr) {
 ActionContextEvents.Event event = this->m_firstEvent;

 while (event.next != nullptr) {
 event = event.next;
 }

 event.next = this->m_eventPool;
 this->m_eventPool = this->m_firstEvent;
 this->m_firstEvent = nullptr;
 }
 }

 void clearEvent(const std::string& name) {
 ActionContextEvents.Event event0 = nullptr;
 ActionContextEvents.Event event1 = this->m_firstEvent;

 while (event1 != nullptr) {
 ActionContextEvents.Event event2 = event1.next;
 if (event1.name.equalsIgnoreCase(name) {
 this->releaseEvent(event1, event0);
 } else {
 event0 = event1;
 }

 event1 = event2;
 }
 }

 private ActionContextEvents.Event allocEvent() {
 if (this->m_eventPool == nullptr) {
 return new ActionContextEvents.Event();
 } else {
 ActionContextEvents.Event event = this->m_eventPool;
 this->m_eventPool = event.next;
 return event;
 }
 }

 void releaseEvent(ActionContextEvents.Event event1, ActionContextEvents.Event event0) {
 if (event0 == nullptr) {
 assert event1 = = this->m_firstEvent;

 this->m_firstEvent = event1.next;
 } else {
 assert event1 != this->m_firstEvent;

 assert event0.next == event1;

 event0.next = event1.next;
 }

 event1.next = this->m_eventPool;
 this->m_eventPool = event1;
 }

 private static class Event {
 int layer;
 std::string name;
 ActionContextEvents.Event next;
 }
}
} // namespace action
} // namespace characters
} // namespace zombie
