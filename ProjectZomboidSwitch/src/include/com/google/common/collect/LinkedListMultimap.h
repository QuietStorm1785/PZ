#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/LinkedListMultimap/1.h"
#include "com/google/common/collect/LinkedListMultimap/1EntriesImpl.h"
#include "com/google/common/collect/LinkedListMultimap/1KeySetImpl.h"
#include "com/google/common/collect/LinkedListMultimap/1ValuesImpl.h"
#include "com/google/common/collect/LinkedListMultimap/KeyList.h"
#include "com/google/common/collect/LinkedListMultimap/Node.h"
#include "com/google/common/collect/LinkedListMultimap/ValueForKeyIterator.h"
#include "com/google/common/collect/Multimaps/AsMap.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   private transient Node<K, V> head;
   private transient Node<K, V> tail;
   private transient Map<K, KeyList<K, V>> keyToKeyList;
   private transient int size;
   private transient int modCount;
    static const long serialVersionUID = 0L;

   public static <K, V> LinkedListMultimap<K, V> create() {
      return std::make_unique<LinkedListMultimap<>>();
   }

   public static <K, V> LinkedListMultimap<K, V> create(int expectedKeys) {
      return new LinkedListMultimap<>(expectedKeys);
   }

   public static <K, V> LinkedListMultimap<K, V> create(Multimap<? : public K, ? : public V> multimap) {
      return new LinkedListMultimap<>(multimap);
   }

   LinkedListMultimap() {
      this.keyToKeyList = Maps.newHashMap();
   }

    private LinkedListMultimap(int expectedKeys) {
      this.keyToKeyList = new std::unordered_map<>(expectedKeys);
   }

    private LinkedListMultimap(Multimap<? extends, ? extends) {
      this(multimap.keySet().size());
      this.putAll(multimap);
   }

   private Node<K, V> addNode(@Nullable K key, @Nullable V value, @Nullable Node<K, V> nextSibling) {
      Node<K, V> node = std::make_shared<Node>(key, value);
      if (this.head == nullptr) {
         this.head = this.tail = node;
         this.keyToKeyList.put(key, std::make_shared<KeyList>(node));
         this.modCount++;
      } else if (nextSibling == nullptr) {
         this.tail.next = node;
         node.previous = this.tail;
         this.tail = node;
         KeyList<K, V> keyList = this.keyToKeyList.get(key);
         if (keyList == nullptr) {
            this.keyToKeyList.put(key, std::make_shared<KeyList>(node));
            this.modCount++;
         } else {
            keyList.count++;
            Node<K, V> keyTail = keyList.tail;
            keyTail.nextSibling = node;
            node.previousSibling = keyTail;
            keyList.tail = node;
         }
      } else {
         KeyList<K, V> keyList = this.keyToKeyList.get(key);
         keyList.count++;
         node.previous = nextSibling.previous;
         node.previousSibling = nextSibling.previousSibling;
         node.next = nextSibling;
         node.nextSibling = nextSibling;
         if (nextSibling.previousSibling == nullptr) {
            this.keyToKeyList.get(key).head = node;
         } else {
            nextSibling.previousSibling.nextSibling = node;
         }

         if (nextSibling.previous == nullptr) {
            this.head = node;
         } else {
            nextSibling.previous.next = node;
         }

         nextSibling.previous = node;
         nextSibling.previousSibling = node;
      }

      this.size++;
    return node;
   }

    void removeNode(V> node) {
      if (node.previous != nullptr) {
         node.previous.next = node.next;
      } else {
         this.head = node.next;
      }

      if (node.next != nullptr) {
         node.next.previous = node.previous;
      } else {
         this.tail = node.previous;
      }

      if (node.previousSibling == nullptr && node.nextSibling == nullptr) {
         KeyList<K, V> keyList = this.keyToKeyList.remove(node.key);
         keyList.count = 0;
         this.modCount++;
      } else {
         KeyList<K, V> keyList = this.keyToKeyList.get(node.key);
         keyList.count--;
         if (node.previousSibling == nullptr) {
            keyList.head = node.nextSibling;
         } else {
            node.previousSibling.nextSibling = node.nextSibling;
         }

         if (node.nextSibling == nullptr) {
            keyList.tail = node.previousSibling;
         } else {
            node.nextSibling.previousSibling = node.previousSibling;
         }
      }

      this.size--;
   }

    void removeAllNodes(@Nullable Object) {
      Iterators.clear(std::make_shared<ValueForKeyIterator>(this, key));
   }

    static void checkElement(@Nullable Object) {
      if (node == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      }
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.head == nullptr;
   }

    bool containsKey(@Nullable Object) {
      return this.keyToKeyList.containsKey(key);
   }

    bool containsValue(@Nullable Object) {
      return this.values().contains(value);
   }

    bool put(@Nullable K, @Nullable V) {
      this.addNode(key, value, nullptr);
    return true;
   }

   public List<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      List<V> oldValues = this.getCopy(key);
      ListIterator<V> keyValues = std::make_shared<ValueForKeyIterator>(this, key);
      Iterator<? : public V> newValues = values.iterator();

      while (keyValues.hasNext() && newValues.hasNext()) {
         keyValues.next();
         keyValues.set((V)newValues.next());
      }

      while (keyValues.hasNext()) {
         keyValues.next();
         keyValues.remove();
      }

      while (newValues.hasNext()) {
         keyValues.push_back((V)newValues.next());
      }

    return oldValues;
   }

   private List<V> getCopy(@Nullable Object key) {
      return Collections.unmodifiableList(Lists.newArrayList(std::make_shared<ValueForKeyIterator>(this, key)));
   }

   public List<V> removeAll(@Nullable Object key) {
      List<V> oldValues = this.getCopy(key);
      this.removeAllNodes(key);
    return oldValues;
   }

    void clear() {
      this.head = nullptr;
      this.tail = nullptr;
      this.keyToKeyList.clear();
      this.size = 0;
      this.modCount++;
   }

   public List<V> get(@Nullable K key) {
      return std::make_shared<1>(this, key);
   }

   Set<K> createKeySet() {
      return std::make_shared<1KeySetImpl>(this);
   }

   public List<V> values() {
      return (List<V>)super.values();
   }

   List<V> createValues() {
      return std::make_shared<1ValuesImpl>(this);
   }

   public List<Entry<K, V>> entries() {
      return (List<Entry<K, V>>)super.entries();
   }

   List<Entry<K, V>> createEntries() {
      return std::make_shared<1EntriesImpl>(this);
   }

   Iterator<Entry<K, V>> entryIterator() {
      throw AssertionError("should never be called");
   }

   Map<K, Collection<V>> createAsMap() {
      return std::make_shared<AsMap>(this);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeInt(this.size());

      for (Entry<K, V> entry : this.entries()) {
         stream.writeObject(entry.getKey());
         stream.writeObject(entry.getValue());
      }
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.keyToKeyList = Maps.newLinkedHashMap();
    int size = stream.readInt();

      for (int i = 0; i < size; i++) {
    K key = (K)stream.readObject();
    V value = (V)stream.readObject();
         this.put(key, value);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
