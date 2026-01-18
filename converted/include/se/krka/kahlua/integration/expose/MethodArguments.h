#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/ui/UIManager.h"
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

class MethodArguments {
public:
  ReturnValues returnValues;
  void *self;
private
  Object[] params;
  std::string failure;
  bool bValid = true;
  static ArrayList[] Lists = new ArrayList[30];

  static MethodArguments get(int int0) {
    MethodArguments methodArguments = null;
    if (Lists[int0].isEmpty()) {
      methodArguments = new MethodArguments(int0);
    } else {
      methodArguments = (MethodArguments)Lists[int0].get(0);
      Lists[int0].remove(methodArguments);
    }

    return methodArguments;
  }

  static void put(MethodArguments methodArguments) {
    if (!Lists[methodArguments.params.length].contains(methodArguments)) {
      Lists[methodArguments.params.length].add(methodArguments);
      methodArguments.bValid = true;
      methodArguments.self = nullptr;
      methodArguments.failure = nullptr;
      methodArguments.returnValues = nullptr;

      for (int int0 = 0; int0 < methodArguments.params.length; int0++) {
        methodArguments.params[int0] = nullptr;
      }
    }
  }

public
  MethodArguments(int int0) { this.params = new Object[int0]; }

  ReturnValues getReturnValues() { return this.returnValues; }

  void *getSelf() { return this.self; }

public
  Object[] getParams() { return this.params; }

  void fail(const std::string &string) {
    this.failure = string;
    this.bValid = false;
  }

  void setSelf(void *object) { this.self = object; }

  std::string getFailure() { return this.failure; }

  void setReturnValues(ReturnValues returnValuesx) {
    this.returnValues = returnValuesx;
  }

  void assertValid() {
    if (!this.isValid()) {
      if (Core.bDebug && UIManager.defaultthread == LuaManager.thread) {
        UIManager.debugBreakpoint(LuaManager.thread.currentfile,
                                  LuaManager.thread.currentLine - 1);
      }

      throw new RuntimeException(this.failure);
    }
  }

  bool isValid() { return this.bValid; }

  static {
    for (int int0 = 0; int0 < 30; int0++) {
      Lists[int0] = new ArrayList(1000);

      for (int int1 = 0; int1 < 1000; int1++) {
        Lists[int0].add(new MethodArguments(int0));
      }
    }
  }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
