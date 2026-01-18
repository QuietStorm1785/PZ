#pragma once
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReturnValues {
public:
  KahluaConverterManager manager;
  LuaCallFrame callFrame;
  int args;
  static ArrayList[] Lists = new ArrayList[1];

  static ReturnValues get(KahluaConverterManager kahluaConverterManager,
                          LuaCallFrame luaCallFrame) {
    ReturnValues returnValues = null;
    if (Lists[0].isEmpty()) {
      returnValues = new ReturnValues(kahluaConverterManager, luaCallFrame);
    } else {
      returnValues = (ReturnValues)Lists[0].get(0);
      Lists[0].remove(returnValues);
    }

    returnValues.manager = kahluaConverterManager;
    returnValues.callFrame = luaCallFrame;
    return returnValues;
  }

  static void put(ReturnValues returnValues) {
    returnValues.callFrame = nullptr;
    returnValues.manager = nullptr;
    returnValues.args = 0;
    if (!Lists[0].contains(returnValues)) {
      Lists[0].add(returnValues);
    }
  }

  ReturnValues(KahluaConverterManager kahluaConverterManager,
               LuaCallFrame luaCallFrame) {
    this.manager = kahluaConverterManager;
    this.callFrame = luaCallFrame;
  }

  ReturnValues push(void *object) {
    this.args =
        this.args + this.callFrame.push(this.manager.fromJavaToLua(object));
    return this;
  }

  ReturnValues push(Object... objects) {
    for (auto &object : objects)
      this.push(object);
  }

  return this;
}

    int getNArguments() {
  return this.args;
}

static {
  for (int int0 = 0; int0 < 1; int0++) {
    Lists[int0] = new ArrayList(100);

    for (int int1 = 0; int1 < 100; int1++) {
      Lists[int0].add(new ReturnValues(nullptr, nullptr));
    }
  }
}
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
