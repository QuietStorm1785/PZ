#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class QNameMap {
public:
    const std::string nsUri;
    const std::string localName;
    V value;
    const int hash;
   QNameMap$Entry<V> next;

   QNameMap$Entry(int h, std::string nsUri, std::string localName, V v, QNameMap$Entry<V> n) {
      this.value = v;
      this.next = n;
      this.nsUri = nsUri;
      this.localName = localName;
      this.hash = h;
   }

    QName createQName() {
      return std::make_shared<QName>(this.nsUri, this.localName);
   }

    V getValue() {
      return this.value;
   }

    V setValue(V newValue) {
    V oldValue = this.value;
      this.value = newValue;
    return oldValue;
   }

    bool equals(void* o) {
      if (!(dynamic_cast<QNameMap*>(o) != nullptr$Entry)) {
    return false;
      } else {
         QNameMap$Entry e = (QNameMap$Entry)o;
    std::string k1 = this.nsUri;
    std::string k2 = e.nsUri;
    std::string k3 = this.localName;
    std::string k4 = e.localName;
         if (k1 == k2 || k1 != nullptr && k1 == k2) && (k3 == k4 || k3 != nullptr && k3 == k4))) {
    void* v1 = this.getValue();
    void* v2 = e.getValue();
            if (v1 == v2 || v1 != nullptr && v1 == v2)) {
    return true;
            }
         }

    return false;
      }
   }

    int hashCode() {
      return this.localName.hashCode() ^ (this.value == nullptr ? 0 : this.value.hashCode());
   }

    std::string toString() {
      return '"' + this.nsUri + "\",\"" + this.localName + "\"=" + this.getValue();
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
