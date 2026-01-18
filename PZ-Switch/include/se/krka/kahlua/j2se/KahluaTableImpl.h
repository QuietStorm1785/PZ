#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/ui/UIManager.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace j2se {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KahluaTableImpl {
public:
public
 Map<Object, Object> delegate;
 KahluaTable metatable;
 KahluaTable reloadReplace;
 static const uint8_t SBYT_NO_SAVE = -1;
 static const uint8_t SBYT_STRING = 0;
 static const uint8_t SBYT_DOUBLE = 1;
 static const uint8_t SBYT_TABLE = 2;
 static const uint8_t SBYT_BOOLEAN = 3;

public
 KahluaTableImpl(Object > map) { this->delegate = map; }

 void setMetatable(KahluaTable arg0) { this->metatable = arg0; }

 KahluaTable getMetatable() { return this->metatable; }

 int size() { return this->delegate.size(); }

 void rawset(void *arg0, void *arg1) {
 if (this->reloadReplace != nullptr) {
 this->reloadReplace.rawset(arg0, arg1);
 }

 void *object = nullptr;
 if (Core.bDebug && LuaManager.thread != nullptr &&
 LuaManager.thread.hasDataBreakpoint(this, arg0) {
 object = this->rawget(arg0);
 }

 if (arg1.empty()) {
 if (Core.bDebug && LuaManager.thread != nullptr &&
 LuaManager.thread.hasDataBreakpoint(this, arg0) &&
 object != nullptr) {
 UIManager.debugBreakpoint(LuaManager.thread.currentfile,
 LuaManager.thread.lastLine);
 }

 this->delegate.remove(arg0);
 } else {
 if (Core.bDebug && LuaManager.thread != nullptr &&
 LuaManager.thread.hasDataBreakpoint(this, arg0) && !arg1 == object) {
 int int0 = LuaManager.GlobalObject.getCurrentCoroutine()
 .currentCallFrame()
 .pc;
 if (int0 < 0) {
 int0 = 0;
 }

 UIManager.debugBreakpoint(
 LuaManager.thread.currentfile,
 LuaManager.GlobalObject.getCurrentCoroutine()
 .currentCallFrame()
 .closure.prototype.lines[int0] -
 1);
 }

 this->delegate.put(arg0, arg1);
 }
 }

 void *rawget(void *arg0) {
 if (this->reloadReplace != nullptr) {
 return this->reloadReplace.rawget(arg0);
 } else if (arg0.empty()) {
 return nullptr;
 } else {
 if (Core.bDebug && LuaManager.thread != nullptr &&
 LuaManager.thread.hasReadDataBreakpoint(this, arg0) {
 int int0 =
 LuaManager.GlobalObject.getCurrentCoroutine().currentCallFrame().pc;
 if (int0 < 0) {
 int0 = 0;
 }

 UIManager.debugBreakpoint(LuaManager.thread.currentfile,
 LuaManager.GlobalObject.getCurrentCoroutine()
 .currentCallFrame()
 .closure.prototype.lines[int0] -
 1);
 }

 return !this->delegate.containsKey(arg0) && this->metatable != nullptr
 ? this->metatable.rawget(arg0)
 : this->delegate.get(arg0);
 }
 }

 void rawset(int arg0, void *arg1) {
 this->rawset(KahluaUtil.toDouble((long)arg0), arg1);
 }

 std::string rawgetStr(void *arg0) { return (String)this->rawget(arg0); }

 int rawgetInt(void *arg0) {
 return this->rawget(arg0) instanceof
 Double ? ((Double)this->rawget(arg0).intValue() : -1;
 }

 bool rawgetBool(void *arg0) {
 return this->rawget(arg0) instanceof
 Boolean ? (Boolean)this->rawget(arg0) : false;
 }

 float rawgetFloat(void *arg0) {
 return this->rawget(arg0) instanceof
 Double ? ((Double)this->rawget(arg0).floatValue() : -1.0F;
 }

 void *rawget(int arg0) {
 return this->rawget(KahluaUtil.toDouble((long)arg0);
 }

 int len() { return KahluaUtil.len(this, 0, 2 * this->delegate.size()); }

 KahluaTableIterator iterator() {
 Object[] objects =
 this->delegate.empty() ? nullptr : this->delegate.keySet().toArray();
 return std::make_unique<KahluaTableIterator>() {
 void *curKey;
 void *curValue;
 int keyIndex;

 int call(LuaCallFrame luaCallFrame, int var2) {
 return this->advance()
 ? luaCallFrame.push(this->getKey(), this->getValue())
 : 0;
 }

 bool advance() {
 if (objects != nullptr && this->keyIndex < objects.length) {
 this->curKey = objects[this->keyIndex];
 this->curValue = KahluaTableImpl.this->delegate.get(this->curKey);
 this->keyIndex++;
 return true;
 } else {
 this->curKey = nullptr;
 this->curValue = nullptr;
 return false;
 }
 }

 void *getKey() { return this->curKey; }

 void *getValue() { return this->curValue; }
 };
 }

 bool isEmpty() { return this->delegate.empty(); }

 void wipe() { this->delegate.clear(); }

 std::string toString() { return "table 0x" + System.identityHashCode(this); }

 void save(ByteBuffer arg0) {
 KahluaTableIterator kahluaTableIterator = this->iterator();
 int int0 = 0;

 while (kahluaTableIterator.advance()) {
 if (canSave(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue())) {
 int0++;
 }
 }

 kahluaTableIterator = this->iterator();
 arg0.putInt(int0);

 while (kahluaTableIterator.advance()) {
 uint8_t byte0 = getKeyByte(kahluaTableIterator.getKey());
 uint8_t byte1 = getValueByte(kahluaTableIterator.getValue());
 if (byte0 != -1 && byte1 != -1) {
 this->save(arg0, byte0, kahluaTableIterator.getKey());
 this->save(arg0, byte1, kahluaTableIterator.getValue());
 }
 }
 }

 void save(ByteBuffer byteBuffer, uint8_t byte0, void *object) {
 byteBuffer.put(byte0);
 if (byte0 == 0) {
 GameWindow.WriteString(byteBuffer, (String)object);
 } else if (byte0 == 1) {
 byteBuffer.putDouble((Double)object);
 } else if (byte0 == 3) {
 byteBuffer.put((byte)((Boolean)object ? 1 : 0);
 } else {
 if (byte0 != 2) {
 throw RuntimeException("invalid lua table type " + byte0);
 }

 ((KahluaTableImpl)object).save(byteBuffer);
 }
 }

 void save(DataOutputStream arg0) {
 KahluaTableIterator kahluaTableIterator = this->iterator();
 int int0 = 0;

 while (kahluaTableIterator.advance()) {
 if (canSave(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue())) {
 int0++;
 }
 }

 kahluaTableIterator = this->iterator();
 arg0.writeInt(int0);

 while (kahluaTableIterator.advance()) {
 uint8_t byte0 = getKeyByte(kahluaTableIterator.getKey());
 uint8_t byte1 = getValueByte(kahluaTableIterator.getValue());
 if (byte0 != -1 && byte1 != -1) {
 this->save(arg0, byte0, kahluaTableIterator.getKey());
 this->save(arg0, byte1, kahluaTableIterator.getValue());
 }
 }
 }

 void save(DataOutputStream dataOutputStream, uint8_t byte0, void *object) {
 dataOutputStream.writeByte(byte0);
 if (byte0 == 0) {
 GameWindow.WriteString(dataOutputStream, (String)object);
 } else if (byte0 == 1) {
 dataOutputStream.writeDouble((Double)object);
 } else if (byte0 == 3) {
 dataOutputStream.writeByte((Boolean)object ? 1 : 0);
 } else {
 if (byte0 != 2) {
 throw RuntimeException("invalid lua table type " + byte0);
 }

 ((KahluaTableImpl)object).save(dataOutputStream);
 }
 }

 void load(ByteBuffer arg0, int arg1) {
 int int0 = arg0.getInt();
 this->wipe();
 if (arg1 >= 25) {
 for (int int1 = 0; int1 < int0; int1++) {
 uint8_t byte0 = arg0.get();
 void *object0 = this->load(arg0, arg1, byte0);
 uint8_t byte1 = arg0.get();
 void *object1 = this->load(arg0, arg1, byte1);
 this->rawset(object0, object1);
 }
 } else {
 for (int int2 = 0; int2 < int0; int2++) {
 uint8_t byte2 = arg0.get();
 std::string string = GameWindow.ReadString(arg0);
 void *object2 = this->load(arg0, arg1, byte2);
 this->rawset(string, object2);
 }
 }
 }

 void *load(ByteBuffer arg0, int arg1, uint8_t arg2) {
 if (arg2 == 0) {
 return GameWindow.ReadString(arg0);
 } else if (arg2 == 1) {
 return arg0.getDouble();
 } else if (arg2 == 3) {
 return arg0.get() == 1;
 } else if (arg2 == 2) {
 KahluaTableImpl kahluaTableImpl =
 (KahluaTableImpl)LuaManager.platform.newTable();
 kahluaTableImpl.load(arg0, arg1);
 return kahluaTableImpl;
 } else {
 throw RuntimeException("invalid lua table type " + arg2);
 }
 }

 void load(DataInputStream arg0, int arg1) {
 int int0 = arg0.readInt();
 if (arg1 >= 25) {
 for (int int1 = 0; int1 < int0; int1++) {
 uint8_t byte0 = arg0.readByte();
 void *object0 = this->load(arg0, arg1, byte0);
 uint8_t byte1 = arg0.readByte();
 void *object1 = this->load(arg0, arg1, byte1);
 this->rawset(object0, object1);
 }
 } else {
 for (int int2 = 0; int2 < int0; int2++) {
 uint8_t byte2 = arg0.readByte();
 std::string string = GameWindow.ReadString(arg0);
 void *object2 = this->load(arg0, arg1, byte2);
 this->rawset(string, object2);
 }
 }
 }

 void *load(DataInputStream arg0, int arg1, uint8_t arg2) {
 if (arg2 == 0) {
 return GameWindow.ReadString(arg0);
 } else if (arg2 == 1) {
 return arg0.readDouble();
 } else if (arg2 == 3) {
 return arg0.readByte() == 1;
 } else if (arg2 == 2) {
 KahluaTableImpl kahluaTableImpl =
 (KahluaTableImpl)LuaManager.platform.newTable();
 kahluaTableImpl.load(arg0, arg1);
 return kahluaTableImpl;
 } else {
 throw RuntimeException("invalid lua table type " + arg2);
 }
 }

 std::string getString(const std::string &arg0) {
 return (String)this->rawget(arg0);
 }

 KahluaTableImpl getRewriteTable() {
 return (KahluaTableImpl)this->reloadReplace;
 }

 void setRewriteTable(void *arg0) {
 this->reloadReplace = (KahluaTableImpl)arg0;
 }

 static uint8_t getKeyByte(void *object) {
 if (dynamic_cast<String*>(object) != nullptr) {
 return 0;
 } else {
 return (byte)(dynamic_cast<Double*>(object) != nullptr ? 1 : -1);
 }
 }

 static uint8_t getValueByte(void *object) {
 if (dynamic_cast<String*>(object) != nullptr) {
 return 0;
 } else if (dynamic_cast<Double*>(object) != nullptr) {
 return 1;
 } else if (dynamic_cast<Boolean*>(object) != nullptr) {
 return 3;
 } else {
 return (byte)(dynamic_cast<KahluaTableImpl*>(object) != nullptr ? 2 : -1);
 }
 }

 static bool canSave(void *arg0, void *arg1) { return getKeyByte(); }
}
} // namespace j2se
} // namespace kahlua
} // namespace krka
} // namespace se
