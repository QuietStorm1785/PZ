#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/action/ActionContextEvents/Event.h"

namespace zombie {
namespace characters {
namespace action {


class ActionContextEvents {
public:
    Event m_firstEvent;
    Event m_eventPool;

    void add(const std::string& var1, int var2) {
      if (!this.contains(var1, var2, false)) {
    Event var3 = this.allocEvent();
         var3.name = var1;
         var3.layer = var2;
         var3.next = this.m_firstEvent;
         this.m_firstEvent = var3;
      }
   }

    bool contains(const std::string& var1, int var2) {
      return this.contains(var1, var2, true);
   }

    bool contains(const std::string& var1, int var2, bool var3) {
      for (Event var4 = this.m_firstEvent; var4 != nullptr; var4 = var4.next) {
         if (var4.name.equalsIgnoreCase(var1)) {
            if (var2 == -1) {
    return true;
            }

            if (var4.layer == var2) {
    return true;
            }

            if (var3 && var4.layer == -1) {
    return true;
            }
         }
      }

    return false;
   }

    void clear() {
      if (this.m_firstEvent != nullptr) {
    Event var1 = this.m_firstEvent;

         while (var1.next != nullptr) {
            var1 = var1.next;
         }

         var1.next = this.m_eventPool;
         this.m_eventPool = this.m_firstEvent;
         this.m_firstEvent = nullptr;
      }
   }

    void clearEvent(const std::string& var1) {
    Event var2 = nullptr;
    Event var3 = this.m_firstEvent;

      while (var3 != nullptr) {
    Event var4 = var3.next;
         if (var3.name.equalsIgnoreCase(var1)) {
            this.releaseEvent(var3, var2);
         } else {
            var2 = var3;
         }

         var3 = var4;
      }
   }

    Event allocEvent() {
      if (this.m_eventPool == nullptr) {
         return std::make_unique<Event>();
      } else {
    Event var1 = this.m_eventPool;
         this.m_eventPool = var1.next;
    return var1;
      }
   }

    void releaseEvent(Event var1, Event var2) {
      if (var2 == nullptr) {
    assert var1 = = this.m_firstEvent;

         this.m_firstEvent = var1.next;
      } else {
         assert var1 != this.m_firstEvent;

         assert var2.next == var1;

         var2.next = var1.next;
      }

      var1.next = this.m_eventPool;
      this.m_eventPool = var1;
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
