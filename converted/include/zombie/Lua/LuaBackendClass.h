#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaBackendClass {
public:
 KahluaTable table;
 KahluaTable typeTable;

 std::string getString(const std::string& string) {
 return (String)this->rawget(string);
 }

 public LuaBackendClass(const std::string& string) {
 this->typeTable = (KahluaTable)LuaManager.env.rawget(string);
 }

 void callVoid(const std::string& string) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), this->table);
 }

 void callVoid(const std::string& string, void* object) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), new Object[]{this->table, object});
 }

 void callVoid(const std::string& string, void* object0, void* object1) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), new Object[]{this->table, object0, object1});
 }

 void callVoid(const std::string& string, void* object0, void* object1, void* object2) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), new Object[]{this->table, object0, object1, object2});
 }

 void callVoid(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), new Object[]{this->table, object0, object1, object2, object3});
 }

 void callVoid(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 LuaManager.caller.pcallvoid(LuaManager.thread, this->typeTable.rawget(string), new Object[]{this->table, object0, object1, object2, object3, object4});
 }

 void* call(const std::string& string) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table)[1];
 }

 void* call(const std::string& string, void* object) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object)[1];
 }

 void* call(const std::string& string, void* object0, void* object1) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1)[1];
 }

 void* call(const std::string& string, void* object0, void* object1, void* object2) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2)[1];
 }

 void* call(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3)[1];
 }

 void* call(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 return LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3, object4)[1];
 }

 int callInt(const std::string& string) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table)[1]).intValue();
 }

 int callInt(const std::string& string, void* object) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object)[1]).intValue();
 }

 int callInt(const std::string& string, void* object0, void* object1) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1)[1]).intValue();
 }

 int callInt(const std::string& string, void* object0, void* object1, void* object2) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2)[1]).intValue();
 }

 int callInt(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3)[1])
 .intValue();
 }

 int callInt(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3, object4)[1])
 .intValue();
 }

 float callFloat(const std::string& string) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table)[1]).floatValue();
 }

 float callFloat(const std::string& string, void* object) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object)[1]).floatValue();
 }

 float callFloat(const std::string& string, void* object0, void* object1) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1)[1]).floatValue();
 }

 float callFloat(const std::string& string, void* object0, void* object1, void* object2) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2)[1]).floatValue();
 }

 float callFloat(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3)[1])
 .floatValue();
 }

 float callFloat(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 return ((Double)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3, object4)[1])
 .floatValue();
 }

 bool callBool(const std::string& string) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table)[1];
 }

 bool callBool(const std::string& string, void* object) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object)[1];
 }

 bool callBool(const std::string& string, void* object0, void* object1) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1)[1];
 }

 bool callBool(const std::string& string, void* object0, void* object1, void* object2) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2)[1];
 }

 bool callBool(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3)[1];
 }

 bool callBool(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 return (Boolean)LuaManager.caller.pcall(LuaManager.thread, this->typeTable.rawget(string), this->table, object0, object1, object2, object3, object4)[1];
 }

 void setMetatable(KahluaTable tablex) {
 this->table.setMetatable(tablex);
 }

 KahluaTable getMetatable() {
 return this->table.getMetatable();
 }

 void rawset(void* object0, void* object1) {
 this->table.rawset(object0, object1);
 }

 void* rawget(void* object) {
 return this->table.rawget(object);
 }

 void rawset(int int0, void* object) {
 this->table.rawset(int0, object);
 }

 void* rawget(int int0) {
 return this->table.rawget(int0);
 }

 int len() {
 return this->table.len();
 }

 int size() {
 return this->table.len();
 }

 KahluaTableIterator iterator() {
 return this->table.iterator();
 }

 bool isEmpty() {
 return this->table.empty();
 }

 void wipe() {
 this->table.wipe();
 }

 void save(ByteBuffer byteBuffer) {
 this->table.save(byteBuffer);
 }

 void load(ByteBuffer byteBuffer, int int0) {
 this->table.load(byteBuffer, int0);
 }

 void save(DataOutputStream dataOutputStream) {
 this->table.save(dataOutputStream);
 }

 void load(DataInputStream dataInputStream, int int0) {
 this->table.load(dataInputStream, int0);
 }
}
} // namespace Lua
} // namespace zombie
