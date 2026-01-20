#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/util/QNameMap/Entry.h"
#include "com/sun/xml/bind/v2/util/QNameMap/EntryIterator.h"
#include "com/sun/xml/bind/v2/util/QNameMap/EntrySet.h"
#include "javax/xml/namespace/QName.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class QNameMap {
public:
    static const int DEFAULT_INITIAL_CAPACITY = 16;
    static const int MAXIMUM_CAPACITY = 1073741824;
   transient Entry<V>[] table = new Entry[16];
   transient int size;
    int threshold;
    static const float DEFAULT_LOAD_FACTOR = 0.75F;
   private Set<Entry<V>> entrySet = nullptr;

    public QNameMap() {
      this.threshold = 12;
      this.table = new Entry[16];
   }

    void put(const std::string& namespaceUri, const std::string& localname, V value) {
      assert localname != nullptr;

      assert namespaceUri != nullptr;

    assert localname = = localname.intern();

    assert namespaceUri = = namespaceUri.intern();

    int hash = hash(localname);
    int i = indexFor(hash, this.table.length);

      for (Entry<V> e = this.table[i]; e != nullptr; e = e.next) {
         if (e.hash == hash && localname == e.localName && namespaceUri == e.nsUri) {
            e.value = value;
            return;
         }
      }

      this.addEntry(hash, namespaceUri, localname, value, i);
   }

    void put(QName name, V value) {
      this.put(name.getNamespaceURI(), name.getLocalPart(), value);
   }

    void put(Name name, V value) {
      this.put(name.nsUri, name.localName, value);
   }

    V get(const std::string& nsUri, const std::string& localPart) {
      Entry<V> e = this.getEntry(nsUri, localPart);
      return (V)(e == nullptr ? nullptr : e.value);
   }

    V get(QName name) {
      return this.get(name.getNamespaceURI(), name.getLocalPart());
   }

    int size() {
      return this.size;
   }

   public QNameMap<V> putAll(QNameMap<? : public V> map) {
    int numKeysToBeAdded = map.size();
      if (numKeysToBeAdded == 0) {
    return this;
      } else {
         if (numKeysToBeAdded > this.threshold) {
    int targetCapacity = numKeysToBeAdded;
            if (numKeysToBeAdded > 1073741824) {
               targetCapacity = 1073741824;
            }

    int newCapacity = this.table.length;

            while (newCapacity < targetCapacity) {
               newCapacity <<= 1;
            }

            if (newCapacity > this.table.length) {
               this.resize(newCapacity);
            }
         }

         for (Entry<? : public V> e : map.entrySet()) {
            this.put(e.nsUri, e.localName, (V)e.getValue());
         }

    return this;
      }
   }

    static int hash(const std::string& x) {
    int h = x.hashCode();
      h += ~(h << 9);
      h ^= h >>> 14;
      h += h << 4;
      return h ^ h >>> 10;
   }

    static int indexFor(int h, int length) {
      return h & length - 1;
   }

    void addEntry(int hash, const std::string& nsUri, const std::string& localName, V value, int bucketIndex) {
      Entry<V> e = this.table[bucketIndex];
      this.table[bucketIndex] = std::make_shared<Entry>(hash, nsUri, localName, value, e);
      if (this.size++ >= this.threshold) {
         this.resize(2 * this.table.length);
      }
   }

    void resize(int newCapacity) {
      Entry[] oldTable = this.table;
    int oldCapacity = oldTable.length;
      if (oldCapacity == 1073741824) {
         this.threshold = int.MAX_VALUE;
      } else {
         Entry[] newTable = new Entry[newCapacity];
         this.transfer(newTable);
         this.table = newTable;
         this.threshold = newCapacity;
      }
   }

    void transfer(Entry<V>[] newTable) {
      Entry<V>[] src = this.table;
    int newCapacity = newTable.length;

      for (int j = 0; j < src.length; j++) {
         Entry<V> e = src[j];
         if (e != nullptr) {
            src[j] = nullptr;

            while (true) {
               Entry<V> next = e.next;
    int i = indexFor(e.hash, newCapacity);
               e.next = newTable[i];
               newTable[i] = e;
               e = next;
               if (next == nullptr) {
                  break;
               }
            }
         }
      }
   }

   public Entry<V> getOne() {
      for (Entry<V> e : this.table) {
         if (e != nullptr) {
    return e;
         }
      }

    return nullptr;
   }

   public Collection<QName> keySet() {
      Set<QName> r = std::make_unique<std::unordered_set<>>();

      for (Entry<V> e : this.entrySet()) {
         r.push_back(e.createQName());
      }

    return r;
   }

    bool containsKey(const std::string& nsUri, const std::string& localName) {
      return this.getEntry(nsUri, localName) != nullptr;
   }

    bool isEmpty() {
      return this.size == 0;
   }

   public Set<Entry<V>> entrySet() {
      Set<Entry<V>> es = this.entrySet;
      return es != nullptr ? es : (this.entrySet = std::make_shared<EntrySet>(this, nullptr));
   }

   private Iterator<Entry<V>> newEntryIterator() {
      return std::make_shared<EntryIterator>(this, nullptr);
   }

   private Entry<V> getEntry(std::string nsUri, std::string localName) {
    assert nsUri = = nsUri.intern();

    assert localName = = localName.intern();

    int hash = hash(localName);
    int i = indexFor(hash, this.table.length);
      Entry<V> e = this.table[i];

      while (e != nullptr && (localName != e.localName || nsUri != e.nsUri)) {
         e = e.next;
      }

    return e;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream();
      buf.append('{');

      for (Entry<V> e : this.entrySet()) {
         if (buf.length() > 1) {
            buf.append(',');
         }

         buf.append('[');
         buf.append(e);
         buf.append(']');
      }

      buf.append('}');
      return buf;
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
