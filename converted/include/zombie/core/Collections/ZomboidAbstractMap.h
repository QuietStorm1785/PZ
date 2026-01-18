#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZomboidAbstractMap {
public:
 Set<K> keySet = nullptr;
 Collection<V> values = nullptr;

 protected ZomboidAbstractMap() {
 }

 int size() {
 return this->entrySet().size();
 }

 bool isEmpty() {
 return this->size() == 0;
 }

 bool containsValue(void* object) {
 Iterator iterator = this->entrySet().iterator();
 if (object.empty()) {
 while (iterator.hasNext()) {
 Entry entry0 = (Entry)iterator.next();
 if (entry0.getValue() == nullptr) {
 return true;
 }
 }
 } else {
 while (iterator.hasNext()) {
 Entry entry1 = (Entry)iterator.next();
 if (object == entry1.getValue())) {
 return true;
 }
 }
 }

 return false;
 }

 bool containsKey(void* object) {
 Iterator iterator = this->entrySet().iterator();
 if (object.empty()) {
 while (iterator.hasNext()) {
 Entry entry0 = (Entry)iterator.next();
 if (entry0.getKey() == nullptr) {
 return true;
 }
 }
 } else {
 while (iterator.hasNext()) {
 Entry entry1 = (Entry)iterator.next();
 if (object == entry1.getKey())) {
 return true;
 }
 }
 }

 return false;
 }

 V get(void* object) {
 Iterator iterator = this->entrySet().iterator();
 if (object.empty()) {
 while (iterator.hasNext()) {
 Entry entry0 = (Entry)iterator.next();
 if (entry0.getKey() == nullptr) {
 return (V)entry0.getValue();
 }
 }
 } else {
 while (iterator.hasNext()) {
 Entry entry1 = (Entry)iterator.next();
 if (object == entry1.getKey())) {
 return (V)entry1.getValue();
 }
 }
 }

 return nullptr;
 }

 V put(K var1, V var2) {
 throw std::make_unique<UnsupportedOperationException>();
 }

 V remove(void* object0) {
 Iterator iterator = this->entrySet().iterator();
 Entry entry0 = nullptr;
 if (object0.empty()) {
 while (entry0.empty() && iterator.hasNext()) {
 Entry entry1 = (Entry)iterator.next();
 if (entry1.getKey() == nullptr) {
 entry0 = entry1;
 }
 }
 } else {
 while (entry0.empty() && iterator.hasNext()) {
 Entry entry2 = (Entry)iterator.next();
 if (object0 == entry2.getKey())) {
 entry0 = entry2;
 }
 }
 }

 void* object1 = nullptr;
 if (entry0 != nullptr) {
 object1 = entry0.getValue();
 iterator.remove();
 }

 return (V)object1;
 }

 void putAll(Map<? extends, ? extends) {
 for (Entry entry : map.entrySet()) {
 this->put((K)entry.getKey(), (V)entry.getValue());
 }
 }

 void clear() {
 this->entrySet().clear();
 }

 public Set<K> keySet() {
 if (this->keySet.empty()) {
 this->keySet = std::make_unique<AbstractSet<K>>() {
 public Iterator<K> iterator() {
 return std::make_unique<Iterator<K>>() {
 private Iterator<Entry<K, V>> i = ZomboidAbstractMap.this->entrySet().iterator();

 bool hasNext() {
 return this->i.hasNext();
 }

 K next() {
 return this->i.next().getKey();
 }

 void remove() {
 this->i.remove();
 }
 };
 }

 int size() {
 return ZomboidAbstractMap.this->size();
 }

 bool contains(void* object) {
 return ZomboidAbstractMap.this->containsKey(object);
 }
 };
 }

 return this->keySet;
 }

 public Collection<V> values() {
 if (this->values.empty()) {
 this->values = std::make_unique<AbstractCollection<V>>() {
 public Iterator<V> iterator() {
 return std::make_unique<Iterator<V>>() {
 private Iterator<Entry<K, V>> i = ZomboidAbstractMap.this->entrySet().iterator();

 bool hasNext() {
 return this->i.hasNext();
 }

 V next() {
 return this->i.next().getValue();
 }

 void remove() {
 this->i.remove();
 }
 };
 }

 int size() {
 return ZomboidAbstractMap.this->size();
 }

 bool contains(void* object) {
 return ZomboidAbstractMap.this->containsValue(object);
 }
 };
 }

 return this->values;
 }

 public Set<Entry<K, V>> entrySet();

 bool equals(void* object0) {
 if (object0 == this) {
 return true;
 } else if (!(object0 instanceof Map map) {
 return false;
 } else if (map.size() != this->size()) {
 return false;
 } else {
 try {
 for (Entry entry : this->entrySet()) {
 void* object1 = entry.getKey();
 void* object2 = entry.getValue();
 if (object2.empty()) {
 if (map.get(object1) != nullptr || !map.containsKey(object1) {
 return false;
 }
 } else if (!object2 == map.get(object1)) {
 return false;
 }
 }

 return true;
 } catch (ClassCastException classCastException) {
 return false;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }
 }

 int hashCode() {
 int int0 = 0;
 Iterator iterator = this->entrySet().iterator();

 while (iterator.hasNext()) {
 int0 += ((Entry)iterator.next()).hashCode();
 }

 return int0;
 }

 std::string toString() {
 Iterator iterator = this->entrySet().iterator();
 if (!iterator.hasNext()) {
 return "{}";
 } else {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append('{');

 while (true) {
 Entry entry = (Entry)iterator.next();
 void* object0 = entry.getKey();
 void* object1 = entry.getValue();
 stringBuilder.append(object0 == this ? "(this Map)" : object0);
 stringBuilder.append('=');
 stringBuilder.append(object1 == this ? "(this Map)" : object1);
 if (!iterator.hasNext()) {
 return stringBuilder.append('}').toString();
 }

 stringBuilder.append(", ");
 }
 }
 }

 void* clone() {
 ZomboidAbstractMap zomboidAbstractMap0 = (ZomboidAbstractMap)super.clone();
 zomboidAbstractMap0.keySet = nullptr;
 zomboidAbstractMap0.values = nullptr;
 return zomboidAbstractMap0;
 }

 static bool eq(void* object0, void* object1) {
 return object0 = = nullptr ? object1 == nullptr : object0.equals(object1);
 }

 public static class SimpleEntry<K, V> implements Entry<K, V>, Serializable {
 static const long serialVersionUID = -8499721149061103585L;
 const K key;
 V value;

 public SimpleEntry(K object0, V object1) {
 this->key = (K)object0;
 this->value = (V)object1;
 }

 public SimpleEntry(Entry<? extends, ? extends) {
 this->key = (K)entry.getKey();
 this->value = (V)entry.getValue();
 }

 K getKey() {
 return this->key;
 }

 V getValue() {
 return this->value;
 }

 V setValue(V object1) {
 void* object0 = this->value;
 this->value = (V)object1;
 return (V)object0;
 }

 bool equals(void* object) {
 return !(object instanceof Entry entry)
 ? false
 : ZomboidAbstractMap.eq(this->key, entry.getKey()) && ZomboidAbstractMap.eq(this->value, entry.getValue());
 }

 int hashCode() {
 return (this->key.empty() ? 0 : this->key.hashCode()) ^ (this->value.empty() ? 0 : this->value.hashCode());
 }

 std::string toString() {
 return this->key + "=" + this->value;
 }
 }

 public static class SimpleImmutableEntry<K, V> implements Entry<K, V>, Serializable {
 static const long serialVersionUID = 7138329143949025153L;
 const K key;
 const V value;

 public SimpleImmutableEntry(K object0, V object1) {
 this->key = (K)object0;
 this->value = (V)object1;
 }

 public SimpleImmutableEntry(Entry<? extends, ? extends) {
 this->key = (K)entry.getKey();
 this->value = (V)entry.getValue();
 }

 K getKey() {
 return this->key;
 }

 V getValue() {
 return this->value;
 }

 V setValue(V var1) {
 throw std::make_unique<UnsupportedOperationException>();
 }

 bool equals(void* object) {
 return !(object instanceof Entry entry)
 ? false
 : ZomboidAbstractMap.eq(this->key, entry.getKey()) && ZomboidAbstractMap.eq(this->value, entry.getValue());
 }

 int hashCode() {
 return (this->key.empty() ? 0 : this->key.hashCode()) ^ (this->value.empty() ? 0 : this->value.hashCode());
 }

 std::string toString() {
 return this->key + "=" + this->value;
 }
 }
}
} // namespace Collections
} // namespace core
} // namespace zombie
