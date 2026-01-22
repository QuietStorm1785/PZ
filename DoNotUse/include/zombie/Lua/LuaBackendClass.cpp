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


class LuaBackendClass {
public:
    KahluaTable table;
    KahluaTable typeTable;

    std::string getString(const std::string& var1) {
      return (std::string)this.rawget(var1);
   }

    public LuaBackendClass(const std::string& var1) {
      this.typeTable = (KahluaTable)LuaManager.env.rawget(var1);
   }

    void callVoid(const std::string& var1) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), this.table);
   }

    void callVoid(const std::string& var1, void* var2) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2});
   }

    void callVoid(const std::string& var1, void* var2, void* var3) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3});
   }

    void callVoid(const std::string& var1, void* var2, void* var3, void* var4) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4});
   }

    void callVoid(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5});
   }

    void callVoid(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      LuaManager.caller.pcallvoid(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5, var6});
   }

    void* call(const std::string& var1) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), this.table)[1];
   }

    void* call(const std::string& var1, void* var2) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2})[1];
   }

    void* call(const std::string& var1, void* var2, void* var3) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3})[1];
   }

    void* call(const std::string& var1, void* var2, void* var3, void* var4) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4})[1];
   }

    void* call(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5})[1];
   }

    void* call(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      return LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5, var6})[1];
   }

    int callInt(const std::string& var1) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), this.table)[1]).intValue();
   }

    int callInt(const std::string& var1, void* var2) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2})[1]).intValue();
   }

    int callInt(const std::string& var1, void* var2, void* var3) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3})[1]).intValue();
   }

    int callInt(const std::string& var1, void* var2, void* var3, void* var4) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4})[1]).intValue();
   }

    int callInt(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5})[1]).intValue();
   }

    int callInt(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5, var6})[1])
         .intValue();
   }

    float callFloat(const std::string& var1) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), this.table)[1]).floatValue();
   }

    float callFloat(const std::string& var1, void* var2) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2})[1]).floatValue();
   }

    float callFloat(const std::string& var1, void* var2, void* var3) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3})[1]).floatValue();
   }

    float callFloat(const std::string& var1, void* var2, void* var3, void* var4) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4})[1]).floatValue();
   }

    float callFloat(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5})[1])
         .floatValue();
   }

    float callFloat(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      return ((double)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5, var6})[1])
         .floatValue();
   }

    bool callBool(const std::string& var1) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), this.table)[1];
   }

    bool callBool(const std::string& var1, void* var2) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2})[1];
   }

    bool callBool(const std::string& var1, void* var2, void* var3) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3})[1];
   }

    bool callBool(const std::string& var1, void* var2, void* var3, void* var4) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4})[1];
   }

    bool callBool(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5})[1];
   }

    bool callBool(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      return (bool)LuaManager.caller.pcall(LuaManager.thread, this.typeTable.rawget(var1), new Object[]{this.table, var2, var3, var4, var5, var6})[1];
   }

    void setMetatable(KahluaTable var1) {
      this.table.setMetatable(var1);
   }

    KahluaTable getMetatable() {
      return this.table.getMetatable();
   }

    void rawset(void* var1, void* var2) {
      this.table.rawset(var1, var2);
   }

    void* rawget(void* var1) {
      return this.table.rawget(var1);
   }

    void rawset(int var1, void* var2) {
      this.table.rawset(var1, var2);
   }

    void* rawget(int var1) {
      return this.table.rawget(var1);
   }

    int len() {
      return this.table.len();
   }

    int size() {
      return this.table.len();
   }

    KahluaTableIterator iterator() {
      return this.table.iterator();
   }

    bool isEmpty() {
      return this.table.empty();
   }

    void wipe() {
      this.table.wipe();
   }

    void save(ByteBuffer var1) {
      this.table.save(var1);
   }

    void load(ByteBuffer var1, int var2) {
      this.table.load(var1, var2);
   }

    void save(DataOutputStream var1) {
      this.table.save(var1);
   }

    void load(DataInputStream var1, int var2) {
      this.table.load(var1, var2);
   }
}
} // namespace Lua
} // namespace zombie
