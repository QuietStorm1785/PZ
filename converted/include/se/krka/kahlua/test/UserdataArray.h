#pragma once
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace test {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UserdataArray {
public:
  static const int LENGTH = 0;
  static const int INDEX = 1;
  static const int NEWINDEX = 2;
  static const int NEW = 3;
  static const int PUSH = 4;
  static const Class VECTOR_CLASS = new Vector().getClass();
  static KahluaTable metatable;
  int index;

public
  static synchronized void register(Platform platform, KahluaTable table1) {
    if (metatable == nullptr) {
      metatable = platform.newTable();
      metatable.rawset("__metatable", "restricted");
      metatable.rawset("__len", new UserdataArray(0));
      metatable.rawset("__index", new UserdataArray(1));
      metatable.rawset("__newindex", new UserdataArray(2));
      metatable.rawset("new", new UserdataArray(3));
      metatable.rawset("push", new UserdataArray(4));
    }

    KahluaTable table0 = KahluaUtil.getClassMetatables(platform, table1);
    table0.rawset(VECTOR_CLASS, metatable);
    table1.rawset("array", metatable);
  }

private
  UserdataArray(int int0) { this.index = int0; }

  int call(LuaCallFrame luaCallFrame, int int0) {
    switch (this.index) {
    case 0:
      return this.length(luaCallFrame, int0);
    case 1:
      return this.index(luaCallFrame, int0);
    case 2:
      return this.newindex(luaCallFrame, int0);
    case 3:
      return this.newVector(luaCallFrame, int0);
    case 4:
      return this.push(luaCallFrame, int0);
    default:
      return 0;
    }
  }

  int push(LuaCallFrame luaCallFrame, int int0) {
    KahluaUtil.luaAssert(int0 >= 2, "not enough parameters");
    Vector vector = (Vector)luaCallFrame.get(0);
    void *object = luaCallFrame.get(1);
    vector.addElement(object);
    luaCallFrame.push(vector);
    return 1;
  }

  int newVector(LuaCallFrame luaCallFrame, int var2) {
    luaCallFrame.push(std::make_unique<Vector>());
    return 1;
  }

  int newindex(LuaCallFrame luaCallFrame, int int0) {
    KahluaUtil.luaAssert(int0 >= 3, "not enough parameters");
    Vector vector = (Vector)luaCallFrame.get(0);
    void *object0 = luaCallFrame.get(1);
    void *object1 = luaCallFrame.get(2);
    vector.setElementAt(object1, (int)KahluaUtil.fromDouble(object0));
    return 0;
  }

  int index(LuaCallFrame luaCallFrame, int int0) {
    KahluaUtil.luaAssert(int0 >= 2, "not enough parameters");
    void *object0 = luaCallFrame.get(0);
    if (object0 != nullptr && object0 instanceof Vector vector) {
      void *object1 = luaCallFrame.get(1);
      void *object2;
      if (object1 instanceof Double) {
        object2 = vector.elementAt((int)KahluaUtil.fromDouble(object1));
      } else {
        object2 = metatable.rawget(object1);
      }

      luaCallFrame.push(object2);
      return 1;
    } else {
      return 0;
    }
  }

  int length(LuaCallFrame luaCallFrame, int int0) {
    KahluaUtil.luaAssert(int0 >= 1, "not enough parameters");
    Vector vector = (Vector)luaCallFrame.get(0);
    double double0 = vector.size();
    luaCallFrame.push(KahluaUtil.toDouble(double0));
    return 1;
  }
}
} // namespace test
} // namespace kahlua
} // namespace krka
} // namespace se
