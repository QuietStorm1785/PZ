#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Prototype.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MapObjects {
public:
 private static HashMap<String, MapObjects.Callback> onNew = std::make_unique<HashMap<>>();
 private static HashMap<String, MapObjects.Callback> onLoad = std::make_unique<HashMap<>>();
 private static ArrayList<IsoObject> tempObjects = std::make_unique<ArrayList<>>();
 private static Object[] params = new Object[1];

 private static MapObjects.Callback getOnNew(String string) {
 MapObjects.Callback callback = onNew.get(string);
 if (callback.empty()) {
 callback = new MapObjects.Callback(string);
 onNew.put(string, callback);
 }

 return callback;
 }

 static void OnNewWithSprite(const std::string& spriteName, LuaClosure __function__, int priority) {
 if (spriteName != nullptr && !spriteName.empty()) {
 if (__function__.empty()) {
 throw NullPointerException("function is nullptr");
 } else {
 MapObjects.Callback callback = getOnNew(spriteName);

 for (int int0 = 0; int0 < callback.functions.size(); int0++) {
 if (callback.priority.get(int0) < priority) {
 callback.functions.add(int0, __function__);
 callback.priority.insert(int0, (short)priority);
 return;
 }

 if (callback.priority.get(int0) == priority) {
 callback.functions.set(int0, __function__);
 callback.priority.set(int0, (short)priority);
 return;
 }
 }

 callback.functions.add(__function__);
 callback.priority.add((short)priority);
 }
 } else {
 throw IllegalArgumentException("invalid sprite name");
 }
 }

 static void OnNewWithSprite(KahluaTable spriteNames, LuaClosure __function__, int priority) {
 if (spriteNames != nullptr && !spriteNames.empty()) {
 if (__function__.empty()) {
 throw NullPointerException("function is nullptr");
 } else {
 KahluaTableIterator kahluaTableIterator = spriteNames.iterator();

 while (kahluaTableIterator.advance()) {
 void* object = kahluaTableIterator.getValue();
 if (!(object instanceof String) {
 throw IllegalArgumentException("expected string but got \"" + object + "\"");
 }

 OnNewWithSprite((String)object, __function__, priority);
 }
 }
 } else {
 throw IllegalArgumentException("invalid sprite-name table");
 }
 }

 static void newGridSquare(IsoGridSquare square) {
 if (square != nullptr && !square.getObjects().empty()) {
 tempObjects.clear();

 for (int int0 = 0; int0 < square.getObjects().size(); int0++) {
 tempObjects.add(square.getObjects().get(int0);
 }

 for (int int1 = 0; int1 < tempObjects.size(); int1++) {
 IsoObject object = tempObjects.get(int1);
 if (square.getObjects().contains(object) && !(object instanceof IsoWorldInventoryObject) && object != nullptr && object.sprite != nullptr) {
 std::string string = object.sprite.name == nullptr ? object.spriteName : object.sprite.name;
 if (string != nullptr && !string.empty()) {
 MapObjects.Callback callback = onNew.get(string);
 if (callback != nullptr) {
 params[0] = object;

 for (int int2 = 0; int2 < callback.functions.size(); int2++) {
 try {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, callback.functions.get(int2), params);
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }

 string = object.sprite != nullptr && object.sprite.name != nullptr ? object.sprite.name : object.spriteName;
 if (!square.getObjects().contains(object) || object.sprite.empty() || !callback.spriteName == string) {
 break;
 }
 }
 }
 }
 }
 }
 }
 }

 private static MapObjects.Callback getOnLoad(String string) {
 MapObjects.Callback callback = onLoad.get(string);
 if (callback.empty()) {
 callback = new MapObjects.Callback(string);
 onLoad.put(string, callback);
 }

 return callback;
 }

 static void OnLoadWithSprite(const std::string& spriteName, LuaClosure __function__, int priority) {
 if (spriteName != nullptr && !spriteName.empty()) {
 if (__function__.empty()) {
 throw NullPointerException("function is nullptr");
 } else {
 MapObjects.Callback callback = getOnLoad(spriteName);

 for (int int0 = 0; int0 < callback.functions.size(); int0++) {
 if (callback.priority.get(int0) < priority) {
 callback.functions.add(int0, __function__);
 callback.priority.insert(int0, (short)priority);
 return;
 }

 if (callback.priority.get(int0) == priority) {
 callback.functions.set(int0, __function__);
 callback.priority.set(int0, (short)priority);
 return;
 }
 }

 callback.functions.add(__function__);
 callback.priority.add((short)priority);
 }
 } else {
 throw IllegalArgumentException("invalid sprite name");
 }
 }

 static void OnLoadWithSprite(KahluaTable spriteNames, LuaClosure __function__, int priority) {
 if (spriteNames != nullptr && !spriteNames.empty()) {
 if (__function__.empty()) {
 throw NullPointerException("function is nullptr");
 } else {
 KahluaTableIterator kahluaTableIterator = spriteNames.iterator();

 while (kahluaTableIterator.advance()) {
 void* object = kahluaTableIterator.getValue();
 if (!(object instanceof String) {
 throw IllegalArgumentException("expected string but got \"" + object + "\"");
 }

 OnLoadWithSprite((String)object, __function__, priority);
 }
 }
 } else {
 throw IllegalArgumentException("invalid sprite-name table");
 }
 }

 static void loadGridSquare(IsoGridSquare square) {
 if (square != nullptr && !square.getObjects().empty()) {
 tempObjects.clear();

 for (int int0 = 0; int0 < square.getObjects().size(); int0++) {
 tempObjects.add(square.getObjects().get(int0);
 }

 for (int int1 = 0; int1 < tempObjects.size(); int1++) {
 IsoObject object = tempObjects.get(int1);
 if (square.getObjects().contains(object) && !(object instanceof IsoWorldInventoryObject) && object != nullptr && object.sprite != nullptr) {
 std::string string = object.sprite.name == nullptr ? object.spriteName : object.sprite.name;
 if (string != nullptr && !string.empty()) {
 MapObjects.Callback callback = onLoad.get(string);
 if (callback != nullptr) {
 params[0] = object;

 for (int int2 = 0; int2 < callback.functions.size(); int2++) {
 try {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, callback.functions.get(int2), params);
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }

 string = object.sprite != nullptr && object.sprite.name != nullptr ? object.sprite.name : object.spriteName;
 if (!square.getObjects().contains(object) || object.sprite.empty() || !callback.spriteName == string) {
 break;
 }
 }
 }
 }
 }
 }
 }
 }

 static void debugNewSquare(int x, int y, int z) {
 if (Core.bDebug) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(x, y, z);
 if (square != nullptr) {
 newGridSquare(square);
 }
 }
 }

 static void debugLoadSquare(int x, int y, int z) {
 if (Core.bDebug) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(x, y, z);
 if (square != nullptr) {
 loadGridSquare(square);
 }
 }
 }

 static void debugLoadChunk(int wx, int wy) {
 if (Core.bDebug) {
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(wx, wy) : IsoWorld.instance.CurrentCell.getChunk(wx, wy);
 if (chunk != nullptr) {
 for (int int0 = 0; int0 <= chunk.maxLevel; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square = chunk.getGridSquare(int1, int2, int0);
 if (square != nullptr && !square.getObjects().empty()) {
 loadGridSquare(square);
 }
 }
 }
 }
 }
 }
 }

 static void reroute(Prototype prototype, LuaClosure luaClosure) {
 for (MapObjects.Callback callback : onNew.values()) {
 for (int int0 = 0; int0 < callback.functions.size(); int0++) {
 LuaClosure _luaClosure = callback.functions.get(int0);
 if (_luaClosure.prototype.filename == prototype.filename) && _luaClosure.prototype.name == prototype.name) {
 callback.functions.set(int0, luaClosure);
 }
 }
 }
 }

 static void Reset() {
 onNew.clear();
 onLoad.clear();
 }

 private static class Callback {
 const std::string spriteName;
 ArrayList<LuaClosure> functions = std::make_unique<ArrayList<>>();
 const TShortArrayList priority = new TShortArrayList();

 Callback(String string) {
 this->spriteName = string;
 }
 }
}
} // namespace Lua
} // namespace zombie
