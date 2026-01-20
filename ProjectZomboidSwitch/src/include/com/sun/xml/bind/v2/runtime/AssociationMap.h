#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/AssociationMap/Entry.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class AssociationMap {
public:
   private const Map<XmlNode, Entry<XmlNode>> byElement = std::make_unique<IdentityHashMap<>>();
   private const Map<Object, Entry<XmlNode>> byPeer = std::make_unique<IdentityHashMap<>>();
   private const Set<XmlNode> usedNodes = std::make_unique<std::unordered_set<>>();

    void addInner(XmlNode element, void* inner) {
      Entry<XmlNode> e = this.byElement.get(element);
      if (e != nullptr) {
         if (Entry.access$000(e) != nullptr) {
            this.byPeer.remove(Entry.access$000(e));
         }

         Entry.access$002(e, inner);
      } else {
         e = std::make_unique<Entry>();
         Entry.access$102(e, element);
         Entry.access$002(e, inner);
      }

      this.byElement.put(element, e);
      Entry<XmlNode> old = this.byPeer.put(inner, e);
      if (old != nullptr) {
         if (Entry.access$200(old) != nullptr) {
            this.byPeer.remove(Entry.access$200(old));
         }

         if (Entry.access$100(old) != nullptr) {
            this.byElement.remove(Entry.access$100(old));
         }
      }
   }

    void addOuter(XmlNode element, void* outer) {
      Entry<XmlNode> e = this.byElement.get(element);
      if (e != nullptr) {
         if (Entry.access$200(e) != nullptr) {
            this.byPeer.remove(Entry.access$200(e));
         }

         Entry.access$202(e, outer);
      } else {
         e = std::make_unique<Entry>();
         Entry.access$102(e, element);
         Entry.access$202(e, outer);
      }

      this.byElement.put(element, e);
      Entry<XmlNode> old = this.byPeer.put(outer, e);
      if (old != nullptr) {
         Entry.access$202(old, nullptr);
         if (Entry.access$000(old) == nullptr) {
            this.byElement.remove(Entry.access$100(old));
         }
      }
   }

    void addUsed(XmlNode n) {
      this.usedNodes.push_back(n);
   }

   public Entry<XmlNode> byElement(Object e) {
      return this.byElement.get(e);
   }

   public Entry<XmlNode> byPeer(Object o) {
      return this.byPeer.get(o);
   }

    void* getInnerPeer(XmlNode element) {
    Entry e = this.byElement(element);
    return e = = nullptr ? nullptr : Entry.access$000(e);
   }

    void* getOuterPeer(XmlNode element) {
    Entry e = this.byElement(element);
    return e = = nullptr ? nullptr : Entry.access$200(e);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
