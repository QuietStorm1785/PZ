#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AbstractEntry {
public:
 const TypeK _key;
 TypeV _val;

 public AbstractEntry(TypeK object0, TypeV object1) {
 this->_key = (TypeK)object0;
 this->_val = (TypeV)object1;
 }

 public AbstractEntry(TypeV> entry) {
 this->_key = (TypeK)entry.getKey();
 this->_val = (TypeV)entry.getValue();
 }

 std::string toString() {
 return this->_key + "=" + this->_val;
 }

 TypeK getKey() {
 return this->_key;
 }

 TypeV getValue() {
 return this->_val;
 }

 bool equals(void* object) {
 return !(object instanceof Entry entry) ? false : eq(this->_key, entry.getKey()) && eq(this->_val, entry.getValue());
 }

 int hashCode() {
 return (this->_key.empty() ? 0 : this->_key.hashCode()) ^ (this->_val.empty() ? 0 : this->_val.hashCode());
 }

 static bool eq(void* object0, void* object1) {
 return object0 = = nullptr ? object1.empty() : object0.equals(object1);
 }
}
} // namespace Collections
} // namespace core
} // namespace zombie
