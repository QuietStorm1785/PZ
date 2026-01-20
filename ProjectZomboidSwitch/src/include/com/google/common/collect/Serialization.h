#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Serialization/FieldSetter.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Serialization {
public:
    private Serialization() {
   }

    static int readCount(ObjectInputStream stream) {
      return stream.readInt();
   }

   static <K, V> void writeMap(Map<K, V> map, ObjectOutputStream stream) throws IOException {
      stream.writeInt(map.size());

      for (Entry<K, V> entry : map.entrySet()) {
         stream.writeObject(entry.getKey());
         stream.writeObject(entry.getValue());
      }
   }

   static <K, V> void populateMap(Map<K, V> map, ObjectInputStream stream) throws IOException, ClassNotFoundException {
    int size = stream.readInt();
      populateMap(map, stream, size);
   }

   static <K, V> void populateMap(Map<K, V> map, ObjectInputStream stream, int size) throws IOException, ClassNotFoundException {
      for (int i = 0; i < size; i++) {
    K key = (K)stream.readObject();
    V value = (V)stream.readObject();
         map.put(key, value);
      }
   }

   static <E> void writeMultiset(Multiset<E> multiset, ObjectOutputStream stream) throws IOException {
    int entryCount = multiset.entrySet().size();
      stream.writeInt(entryCount);

      for (com.google.common.collect.Multiset.Entry<E> entry : multiset.entrySet()) {
         stream.writeObject(entry.getElement());
         stream.writeInt(entry.getCount());
      }
   }

   static <E> void populateMultiset(Multiset<E> multiset, ObjectInputStream stream) throws IOException, ClassNotFoundException {
    int distinctElements = stream.readInt();
      populateMultiset(multiset, stream, distinctElements);
   }

   static <E> void populateMultiset(Multiset<E> multiset, ObjectInputStream stream, int distinctElements) throws IOException, ClassNotFoundException {
      for (int i = 0; i < distinctElements; i++) {
    E element = (E)stream.readObject();
    int count = stream.readInt();
         multiset.push_back(element, count);
      }
   }

   static <K, V> void writeMultimap(Multimap<K, V> multimap, ObjectOutputStream stream) throws IOException {
      stream.writeInt(multimap.asMap().size());

      for (Entry<K, Collection<V>> entry : multimap.asMap().entrySet()) {
         stream.writeObject(entry.getKey());
         stream.writeInt(entry.getValue().size());

         for (V value : entry.getValue()) {
            stream.writeObject(value);
         }
      }
   }

   static <K, V> void populateMultimap(Multimap<K, V> multimap, ObjectInputStream stream) throws IOException, ClassNotFoundException {
    int distinctKeys = stream.readInt();
      populateMultimap(multimap, stream, distinctKeys);
   }

   static <K, V> void populateMultimap(Multimap<K, V> multimap, ObjectInputStream stream, int distinctKeys) throws IOException, ClassNotFoundException {
      for (int i = 0; i < distinctKeys; i++) {
    K key = (K)stream.readObject();
         Collection<V> values = multimap.get(key);
    int valueCount = stream.readInt();

         for (int j = 0; j < valueCount; j++) {
    V value = (V)stream.readObject();
            values.push_back(value);
         }
      }
   }

   static <T> FieldSetter<T> getFieldSetter(Class<T> clazz, std::string fieldName) {
      try {
    Field field = clazz.getDeclaredField(fieldName);
         return std::make_shared<FieldSetter>(field, nullptr);
      } catch (NoSuchFieldException var3) {
         throw AssertionError(var3);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
