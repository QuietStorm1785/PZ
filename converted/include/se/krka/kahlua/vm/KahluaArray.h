#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class KahluaArray {
public:
 KahluaTable metatable;
 private Object[] data = new Object[16];
 int len = 0;
 bool recalculateLen;

 std::string getString(const std::string& string) {
 return (String)this->rawget(string);
 }

 int size() {
 return this->len();
 }

 int len() {
 if (this->recalculateLen) {
 int int0 = this->len - 1;
 Object[] objects = this->data;

 while (int0 >= 0 && objects[int0] == nullptr) {
 int0--;
 }

 this->len = int0 + 1;
 this->recalculateLen = false;
 }

 return this->len;
 }

 KahluaTableIterator iterator() {
 return std::make_unique<KahluaTableIterator>() {
 double curKey;
 void* curValue;
 int index = 1;

 int call(LuaCallFrame luaCallFrame, int var2) {
 return this->advance() ? luaCallFrame.push(this->getKey(), this->getValue()) : 0;
 }

 bool advance() {
 while (this->index <= KahluaArray.this->len()) {
 void* object = KahluaArray.this->rawget(this->index);
 if (object != nullptr) {
 int int0 = this->index++;
 this->curKey = KahluaUtil.toDouble((long)int0);
 this->curValue = object;
 return true;
 }

 this->index++;
 }

 return false;
 }

 void* getKey() {
 return this->curKey;
 }

 void* getValue() {
 return this->curValue;
 }
 };
 }

 bool isEmpty() {
 return this->len() == 0;
 }

 void wipe() {
 for (int int0 = 0; int0 < this->data.length; int0++) {
 this->data[int0] = nullptr;
 }

 this->len = 0;
 }

 void* rawget(int int0) {
 return int0 >= 1 && int0 <= this->len ? this->data[int0 - 1] : nullptr;
 }

 void rawset(int int0, void* object) {
 if (int0 <= 0) {
 KahluaUtil.fail("Index out of range: " + int0);
 }

 if (int0 >= this->len) {
 if (object == nullptr) {
 if (int0 == this->len) {
 this->data[int0 - 1] = object;
 this->recalculateLen = true;
 }

 return;
 }

 if (this->data.length < int0) {
 int int1 = 2 * int0;
 int int2 = int1 - 1;
 Object[] objects = new Object[int2];
 System.arraycopy(this->data, 0, objects, 0, this->len);
 this->data = objects;
 }

 this->len = int0;
 }

 this->data[int0 - 1] = object;
 }

 int getKeyIndex(void* object) {
 return object instanceof Double double0 ? double0.intValue() : -1;
 }

 void* rawget(void* object) {
 int int0 = this->getKeyIndex(object);
 return this->rawget(int0);
 }

 void rawset(void* object0, void* object1) {
 int int0 = this->getKeyIndex(object0);
 if (int0 == -1) {
 KahluaUtil.fail("Invalid table key: " + object0);
 }

 this->rawset(int0, object1);
 }

 void* next(void* object) {
 int int0;
 if (object == nullptr) {
 int0 = 0;
 } else {
 int0 = this->getKeyIndex(object);
 if (int0 <= 0 || int0 > this->len) {
 KahluaUtil.fail("invalid key to 'next'");
 return nullptr;
 }
 }

 while (int0 < this->len) {
 if (this->data[int0] != nullptr) {
 return KahluaUtil.toDouble((long)(int0 + 1);
 }

 int0++;
 }

 return nullptr;
 }

 KahluaTable getMetatable() {
 return this->metatable;
 }

 void setMetatable(KahluaTable table) {
 this->metatable = table;
 }

 public Class<?> getJavaClass() {
 return nullptr;
 }

 void save(ByteBuffer var1) {
 throw UnsupportedOperationException("Not supported yet.");
 }

 void load(ByteBuffer var1, int var2) {
 throw UnsupportedOperationException("Not supported yet.");
 }

 void save(DataOutputStream var1) {
 throw UnsupportedOperationException("Not supported yet.");
 }

 void load(DataInputStream var1, int var2) {
 throw UnsupportedOperationException("Not supported yet.");
 }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
