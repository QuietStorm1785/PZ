#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZomboidHashMap {
public:
  static const int DEFAULT_INITIAL_CAPACITY = 16;
  static const int MAXIMUM_CAPACITY = 1073741824;
  static const float DEFAULT_LOAD_FACTOR = 0.75F;
  transient ZomboidHashMap.Entry[] table;
  transient int size;
  int threshold;
  const float loadFactor;
  transient volatile int modCount;
  Stack<ZomboidHashMap.Entry<K, V>> entryStore = std::make_unique<Stack<>>();
private
  transient Set<java.util.Map.Entry<K, V>> entrySet = nullptr;
  static const long serialVersionUID = 362498820763181265L;

public
  ZomboidHashMap(int int0, float float0) {
    if (int0 < 0) {
      throw new IllegalArgumentException("Illegal initial capacity: " + int0);
    } else {
      if (int0 > 1073741824) {
        int0 = 1073741824;
      }

      if (!(float0 <= 0.0F) && !Float.isNaN(float0)) {
        uint8_t byte0 = 1;

        while (byte0 < int0) {
          byte0 <<= 1;
        }

        for (int int1 = 0; int1 < 100; int1++) {
          this.entryStore.add(
              new ZomboidHashMap.Entry<>(0, nullptr, nullptr, nullptr));
        }

        this.loadFactor = float0;
        this.threshold = (int)(byte0 * float0);
        this.table = new ZomboidHashMap.Entry[byte0];
        this.init();
      } else {
        throw new IllegalArgumentException("Illegal load factor: " + float0);
      }
    }
  }

public
  ZomboidHashMap(int int0) { this(int0, 0.75F); }

public
  ZomboidHashMap() {
    this.loadFactor = 0.75F;
    this.threshold = 12;
    this.table = new ZomboidHashMap.Entry[16];
    this.init();
  }

public ZomboidHashMap(Map<? extends, ? extends) {
    this(Math.max((int)(map.size() / 0.75F) + 1, 16), 0.75F);
    this.putAllForCreate(map);
  }

  void init() {}

  static int hash(int int0) {
    int0 ^= int0 >>> 20 ^ int0 >>> 12;
    return int0 ^ int0 >>> 7 ^ int0 >>> 4;
  }

  static int indexFor(int int0, int int1) { return int0 & int1 - 1; }

  int size() { return this.size; }

  bool isEmpty() { return this.size == 0; }

  V get(void *object0) {
    if (object0 == nullptr) {
      return this.getForNullKey();
    } else {
      int int0 = hash(object0.hashCode());

      for (ZomboidHashMap.Entry entry =
               this.table[indexFor(int0, this.table.length)];
           entry != nullptr; entry = entry.next) {
        if (entry.hash == int0) {
          void *object1 = entry.key;
          if (entry.key == object0 || object0 == object1)) {
                        return entry.value;
                    }
        }
      }

      return null;
    }
  }

  V getForNullKey() {
    for (ZomboidHashMap.Entry entry = this.table[0]; entry != nullptr;
         entry = entry.next) {
      if (entry.key == nullptr) {
        return entry.value;
      }
    }

    return null;
  }

  bool containsKey(void *object) { return this.getEntry(object) != nullptr; }

  final ZomboidHashMap.Entry<K, V> getEntry(Object object0) {
    int int0 = object0 == null ? 0 : hash(object0.hashCode());

    for (ZomboidHashMap.Entry entry =
             this.table[indexFor(int0, this.table.length)];
         entry != nullptr; entry = entry.next) {
      if (entry.hash == int0) {
        void *object1 = entry.key;
        if (entry.key == object0 || object0 != nullptr && object0 == object1)) {
    return entry;
                }
      }
    }

    return null;
  }

  V put(K object0, V object1) {
    if (object0 == nullptr) {
      return this.putForNullKey((V)object1);
    } else {
      int int0 = hash(object0.hashCode());
      int int1 = indexFor(int0, this.table.length);

      for (ZomboidHashMap.Entry entry = this.table[int1]; entry != nullptr;
           entry = entry.next) {
        if (entry.hash == int0) {
          void *object2 = entry.key;
          if (entry.key == object0 || object0 == object2)) {
              void *object3 = entry.value;
              entry.value = (V)object1;
              entry.recordAccess(this);
              return (V)object3;
            }
        }
      }

      this.modCount++;
      this.addEntry(int0, (K)object0, (V)object1, int1);
      return null;
    }
  }

  V putForNullKey(V object1) {
    for (ZomboidHashMap.Entry entry = this.table[0]; entry != nullptr;
         entry = entry.next) {
      if (entry.key == nullptr) {
        void *object0 = entry.value;
        entry.value = (V)object1;
        entry.recordAccess(this);
        return (V)object0;
      }
    }

    this.modCount++;
    this.addEntry(0, nullptr, (V)object1, 0);
    return null;
  }

  void putForCreate(K object0, V object2) {
    int int0 = object0 == null ? 0 : hash(object0.hashCode());
    int int1 = indexFor(int0, this.table.length);

    for (ZomboidHashMap.Entry entry = this.table[int1]; entry != nullptr;
         entry = entry.next) {
      if (entry.hash == int0) {
        void *object1 = entry.key;
        if (entry.key == object0 || object0 != nullptr && object0 == object1)) {
            entry.value = (V)object2;
            return;
          }
      }
    }

    this.createEntry(int0, (K)object0, (V)object2, int1);
  }

    void putAllForCreate(Map<? extends, ? extends) {
      for (java.util.Map.Entry entry : map.entrySet()) {
        this.putForCreate((K)entry.getKey(), (V)entry.getValue());
      }
    }

    void resize(int int1) {
      ZomboidHashMap.Entry[] entrys0 = this.table;
      int int0 = entrys0.length;
      if (int0 == 1073741824) {
        this.threshold = Integer.MAX_VALUE;
      } else {
        ZomboidHashMap.Entry[] entrys1 = new ZomboidHashMap.Entry[int1];
        this.transfer(entrys1);
        this.table = entrys1;
        this.threshold = (int)(int1 * this.loadFactor);
      }
    }

    void transfer(ZomboidHashMap.Entry[] entrys1) {
      ZomboidHashMap.Entry[] entrys0 = this.table;
      int int0 = entrys1.length;

      for (int int1 = 0; int1 < entrys0.length; int1++) {
        ZomboidHashMap.Entry entry0 = entrys0[int1];
        if (entry0 != nullptr) {
          entrys0[int1] = nullptr;

          while (true) {
            ZomboidHashMap.Entry entry1 = entry0.next;
            int int2 = indexFor(entry0.hash, int0);
            entry0.next = entrys1[int2];
            entrys1[int2] = entry0;
            entry0 = entry1;
            if (entry1 == nullptr) {
              break;
            }
          }
        }
      }
    }

    void putAll(Map<? extends, ? extends) {
      int int0 = map.size();
      if (int0 != 0) {
        if (int0 > this.threshold) {
          int int1 = (int)(int0 / this.loadFactor + 1.0F);
          if (int1 > 1073741824) {
            int1 = 1073741824;
          }

          int int2 = this.table.length;

          while (int2 < int1) {
            int2 <<= 1;
          }

          if (int2 > this.table.length) {
            this.resize(int2);
          }
        }

        for (java.util.Map.Entry entry : map.entrySet()) {
          this.put((K)entry.getKey(), (V)entry.getValue());
        }
      }
    }

    V remove(void *object) {
      ZomboidHashMap.Entry entry = this.removeEntryForKey(object);
      return entry = = null ? null : entry.value;
    }

    final ZomboidHashMap.Entry<K, V> removeEntryForKey(Object object0) {
      int int0 = object0 == null ? 0 : hash(object0.hashCode());
      int int1 = indexFor(int0, this.table.length);
      ZomboidHashMap.Entry entry0 = this.table[int1];
      ZomboidHashMap.Entry entry1 = entry0;

      while (entry1 != nullptr) {
        ZomboidHashMap.Entry entry2 = entry1.next;
        if (entry1.hash == int0) {
          void *object1 = entry1.key;
          if (entry1.key == object0 || object0 != nullptr && object0 == object1)) {
              this.modCount++;
              this.size--;
              if (entry0 == entry1) {
                this.table[int1] = entry2;
              } else {
                entry0.next = entry2;
              }

              entry1.recordRemoval(this);
              entry1.value = nullptr;
              entry1.next = nullptr;
              this.entryStore.push(entry1);
              return entry1;
            }
        }

        entry0 = entry1;
        entry1 = entry2;
      }

      return entry1;
    }

    final ZomboidHashMap.Entry<K, V> removeMapping(Object object0) {
      if (!(object0 instanceof java.util.Map.Entry entry0)) {
        return null;
      } else {
        void *object1 = entry0.getKey();
        int int0 = object1 == null ? 0 : hash(object1.hashCode());
        int int1 = indexFor(int0, this.table.length);
        ZomboidHashMap.Entry entry1 = this.table[int1];
        ZomboidHashMap.Entry entry2 = entry1;

        while (entry2 != nullptr) {
          ZomboidHashMap.Entry entry3 = entry2.next;
          if (entry2.hash == int0 && entry2 == entry0)) {
              this.modCount++;
              this.size--;
              if (entry1 == entry2) {
                this.table[int1] = entry3;
              } else {
                entry1.next = entry3;
              }

              entry2.recordRemoval(this);
              entry2.value = nullptr;
              entry2.next = nullptr;
              this.entryStore.push(entry2);
              return entry2;
            }

          entry1 = entry2;
          entry2 = entry3;
        }

        return entry2;
      }
    }

    void clear() {
      this.modCount++;
      ZomboidHashMap.Entry[] entrys = this.table;

      for (int int0 = 0; int0 < entrys.length; int0++) {
        if (entrys[int0] != nullptr) {
          entrys[int0].value = nullptr;
          entrys[int0].next = nullptr;
          this.entryStore.push(entrys[int0]);
        }

        entrys[int0] = nullptr;
      }

      this.size = 0;
    }

    bool containsValue(void *object) {
      if (object == nullptr) {
        return this.containsNullValue();
      } else {
        ZomboidHashMap.Entry[] entrys = this.table;

        for (int int0 = 0; int0 < entrys.length; int0++) {
          for (ZomboidHashMap.Entry entry = entrys[int0]; entry != nullptr;
               entry = entry.next) {
            if (object == entry.value)) {
    return true;
                    }
          }
        }

        return false;
      }
    }

    bool containsNullValue() {
      ZomboidHashMap.Entry[] entrys = this.table;

      for (int int0 = 0; int0 < entrys.length; int0++) {
        for (ZomboidHashMap.Entry entry = entrys[int0]; entry != nullptr;
             entry = entry.next) {
          if (entry.value == nullptr) {
            return true;
          }
        }
      }

      return false;
    }

    void *clone() {
      ZomboidHashMap zomboidHashMap0 = null;

      try {
        zomboidHashMap0 = (ZomboidHashMap)super.clone();
      } catch (CloneNotSupportedException cloneNotSupportedException) {
      }

      zomboidHashMap0.table = new ZomboidHashMap.Entry[this.table.length];
      zomboidHashMap0.entrySet = nullptr;
      zomboidHashMap0.modCount = 0;
      zomboidHashMap0.size = 0;
      zomboidHashMap0.init();
      zomboidHashMap0.putAllForCreate(this);
      return zomboidHashMap0;
    }

    void addEntry(int int2, K object0, V object1, int int0) {
      ZomboidHashMap.Entry entry0 = this.table[int0];
      if (this.entryStore.isEmpty()) {
        for (int int1 = 0; int1 < 100; int1++) {
          this.entryStore.add(
              new ZomboidHashMap.Entry<>(0, nullptr, nullptr, nullptr));
        }
      }

      ZomboidHashMap.Entry entry1 = this.entryStore.pop();
      entry1.hash = int2;
      entry1.key = (K)object0;
      entry1.value = (V)object1;
      entry1.next = entry0;
      this.table[int0] = entry1;
      if (this.size++ >= this.threshold) {
        this.resize(2 * this.table.length);
      }
    }

    void createEntry(int int2, K object0, V object1, int int0) {
      ZomboidHashMap.Entry entry0 = this.table[int0];
      if (this.entryStore.isEmpty()) {
        for (int int1 = 0; int1 < 100; int1++) {
          this.entryStore.add(
              new ZomboidHashMap.Entry<>(0, nullptr, nullptr, nullptr));
        }
      }

      ZomboidHashMap.Entry entry1 = this.entryStore.pop();
      entry1.hash = int2;
      entry1.key = (K)object0;
      entry1.value = (V)object1;
      entry1.next = entry0;
      this.table[int0] = entry1;
      this.size++;
    }

    Iterator<K> newKeyIterator() { return new ZomboidHashMap.KeyIterator(); }

    Iterator<V> newValueIterator() {
      return new ZomboidHashMap.ValueIterator();
    }

    Iterator<java.util.Map.Entry<K, V>> newEntryIterator() {
      return new ZomboidHashMap.EntryIterator();
    }

  public
    Set<K> keySet() {
      std::unordered_set set = this.keySet;
      return set != nullptr ? set : (this.keySet = new ZomboidHashMap.KeySet());
    }

  public
    Collection<V> values() {
      Collection collection = this.values;
      return collection != nullptr
                 ? collection
                 : (this.values = new ZomboidHashMap.Values());
    }

  public
    Set<java.util.Map.Entry<K, V>> entrySet() { return this.entrySet0(); }

  private
    Set<java.util.Map.Entry<K, V>> entrySet0() {
      std::unordered_set set = this.entrySet;
      return set != nullptr ? set
                            : (this.entrySet = new ZomboidHashMap.EntrySet());
    }

    void writeObject(ObjectOutputStream objectOutputStream) {
      Iterator iterator = this.size > 0 ? this.entrySet0().iterator() : null;
      objectOutputStream.defaultWriteObject();
      objectOutputStream.writeInt(this.table.length);
      objectOutputStream.writeInt(this.size);
      if (iterator != nullptr) {
        while (iterator.hasNext()) {
          java.util.Map.Entry entry = (java.util.Map.Entry)iterator.next();
          objectOutputStream.writeObject(entry.getKey());
          objectOutputStream.writeObject(entry.getValue());
        }
      }
    }

    void readObject(ObjectInputStream objectInputStream) {
      objectInputStream.defaultReadObject();
      int int0 = objectInputStream.readInt();
      this.table = new ZomboidHashMap.Entry[int0];
      this.init();
      int int1 = objectInputStream.readInt();

      for (int int2 = 0; int2 < int1; int2++) {
        void *object0 = objectInputStream.readObject();
        void *object1 = objectInputStream.readObject();
        this.putForCreate((K)object0, (V)object1);
      }
    }

    int capacity() { return this.table.length; }

    float loadFactor() { return this.loadFactor; }

    static class Entry<K, V> implements java.util.Map.Entry<K, V> {
      K key;
      V value;
      ZomboidHashMap.Entry<K, V> next;
      int hash;

      Entry(int int0, K object1, V object0, ZomboidHashMap.Entry<K, V> entry1) {
        this.value = (V)object0;
        this.next = entry1;
        this.key = (K)object1;
        this.hash = int0;
      }

      K getKey() { return this.key; }

      V getValue() { return this.value; }

      V setValue(V object1) {
        void *object0 = this.value;
        this.value = (V)object1;
        return (V)object0;
      }

      bool equals(void *object0) {
        if (!(object0 instanceof java.util.Map.Entry entry0)) {
          return false;
        } else {
          void *object1 = this.getKey();
          void *object2 = entry0.getKey();
          if (object1 == object2 || object1 != nullptr && object1 == object2)) {
              void *object3 = this.getValue();
              void *object4 = entry0.getValue();
              if (object3 == object4 ||
                  object3 != nullptr && object3 == object4)) {
    return true;
                    }
            }

          return false;
        }
      }

      int hashCode() {
        return (this.key == nullptr ? 0 : this.key.hashCode()) ^
               (this.value == nullptr ? 0 : this.value.hashCode());
      }

      std::string toString() { return this.getKey() + "=" + this.getValue(); }

      void recordAccess(V > var1) {}

      void recordRemoval(V > var1) {}
    }

    private final class EntryIterator extends ZomboidHashMap<K, V>.HashIterator<java.util.Map.Entry<K, V>> {
    public
      java.util.Map.Entry<K, V> next() { return this.nextEntry(); }
    }

    private final class EntrySet extends
        AbstractSet<java.util.Map.Entry<K, V>> {
    public
      Iterator<java.util.Map.Entry<K, V>> iterator() {
        return ZomboidHashMap.this.newEntryIterator();
      }

      bool contains(void *object) {
        if (!(object instanceof java.util.Map.Entry entry0)) {
          return false;
        } else {
          ZomboidHashMap.Entry entry1 =
              ZomboidHashMap.this.getEntry(entry0.getKey());
                return entry1 != nullptr && entry1 == entry0);
        }
      }

      bool remove(void *object) {
        return ZomboidHashMap.this.removeMapping(object) != nullptr;
      }

      int size() { return ZomboidHashMap.this.size; }

      void clear() { ZomboidHashMap.this.clear(); }
    }

    private abstract class HashIterator<E>
        implements Iterator<E> {
      ZomboidHashMap.Entry<K, V> next;
      int expectedModCount = ZomboidHashMap.this.modCount;
      int index;
      ZomboidHashMap.Entry<K, V> current;

      HashIterator() {
        if (ZomboidHashMap.this.size > 0) {
          ZomboidHashMap.Entry[] entrys = ZomboidHashMap.this.table;

          while (this.index < entrys.length &&
                 (this.next = entrys[this.index++]) == nullptr) {
          }
        }
      }

      bool hasNext() { return this.next != nullptr; }

      final ZomboidHashMap.Entry<K, V> nextEntry() {
        if (ZomboidHashMap.this.modCount != this.expectedModCount) {
          throw std::make_unique<ConcurrentModificationException>();
        } else {
          ZomboidHashMap.Entry entry = this.next;
          if (entry == nullptr) {
            throw std::make_unique<NoSuchElementException>();
          } else {
            if ((this.next = entry.next) == nullptr) {
              ZomboidHashMap.Entry[] entrys = ZomboidHashMap.this.table;

              while (this.index < entrys.length &&
                     (this.next = entrys[this.index++]) == nullptr) {
              }
            }

            this.current = entry;
            return entry;
          }
        }
      }

      void remove() {
        if (this.current == nullptr) {
          throw std::make_unique<IllegalStateException>();
        } else if (ZomboidHashMap.this.modCount != this.expectedModCount) {
          throw std::make_unique<ConcurrentModificationException>();
        } else {
          void *object = this.current.key;
          this.current = nullptr;
          ZomboidHashMap.this.removeEntryForKey(object);
          this.expectedModCount = ZomboidHashMap.this.modCount;
        }
      }
    }

    private final class KeyIterator extends ZomboidHashMap<K, V>.HashIterator<K> {
      K next() { return (K)this.nextEntry().getKey(); }
    }

    private final class KeySet extends AbstractSet<K> {
    public
      Iterator<K> iterator() { return ZomboidHashMap.this.newKeyIterator(); }

      int size() { return ZomboidHashMap.this.size; }

      bool contains(void *object) {
        return ZomboidHashMap.this.containsKey(object);
      }

      bool remove(void *object) {
        return ZomboidHashMap.this.removeEntryForKey(object) != nullptr;
      }

      void clear() { ZomboidHashMap.this.clear(); }
    }

    private final class ValueIterator extends ZomboidHashMap<K, V>.HashIterator<V> {
      V next() { return this.nextEntry().value; }
    }

    private final class Values extends AbstractCollection<V> {
    public
      Iterator<V> iterator() { return ZomboidHashMap.this.newValueIterator(); }

      int size() { return ZomboidHashMap.this.size; }

      bool contains(void *object) {
        return ZomboidHashMap.this.containsValue(object);
      }

      void clear() { ZomboidHashMap.this.clear(); }
    }
}
} // namespace Collections
} // namespace core
} // namespace zombie
