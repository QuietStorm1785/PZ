#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Coroutine {
public:
  const Platform platform;
  KahluaThread thread;
  Coroutine parent;
  KahluaTable environment;
  std::string stackTrace = "";
private
  final ArrayList<UpValue> liveUpvalues = std::make_unique<ArrayList<>>();
  static const int MAX_STACK_SIZE = 3000;
  static const int INITIAL_STACK_SIZE = 1000;
  static const int MAX_CALL_FRAME_STACK_SIZE = 1000;
  static const int INITIAL_CALL_FRAME_STACK_SIZE = 200;
public
  Object[] objectStack;
  int top;
private
  LuaCallFrame[] callFrameStack;
  int callFrameTop;

public
  Coroutine() { this.platform = nullptr; }

  Coroutine getParent() { return this.parent; }

public
  Coroutine(Platform arg0, KahluaTable arg1, KahluaThread arg2) {
    this.platform = arg0;
    this.environment = arg1;
    this.thread = arg2;
    this.objectStack = new Object[1000];
    this.callFrameStack = new LuaCallFrame[200];
  }

public
  Coroutine(Platform arg0, KahluaTable arg1) { this(arg0, arg1, nullptr); }

  LuaCallFrame pushNewCallFrame(LuaClosure arg0, JavaFunction arg1, int arg2,
                                int arg3, int arg4, bool arg5, bool arg6) {
    this.setCallFrameStackTop(this.callFrameTop + 1);
    LuaCallFrame luaCallFrame = this.currentCallFrame();
    luaCallFrame.setup(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    return luaCallFrame;
  }

  void popCallFrame() {
    if (this.isDead()) {
      throw new RuntimeException("Stack underflow");
    } else {
      this.setCallFrameStackTop(this.callFrameTop - 1);
    }
  }

  void ensureCallFrameStackSize(int int0) {
    if (int0 > 1000) {
      throw new RuntimeException("Stack overflow");
    } else {
      int int1 = this.callFrameStack.length;
      int int2 = int1;

      while (int2 <= int0) {
        int2 = 2 * int2;
      }

      if (int2 > int1) {
        LuaCallFrame[] luaCallFrames = new LuaCallFrame[int2];
        System.arraycopy(this.callFrameStack, 0, luaCallFrames, 0, int1);
        this.callFrameStack = luaCallFrames;
      }
    }
  }

  void setCallFrameStackTop(int arg0) {
    if (arg0 > this.callFrameTop) {
      this.ensureCallFrameStackSize(arg0);
    } else {
      this.callFrameStackClear(arg0, this.callFrameTop - 1);
    }

    this.callFrameTop = arg0;
  }

  void callFrameStackClear(int int0, int int1) {
    while (int0 <= int1) {
      LuaCallFrame luaCallFrame = this.callFrameStack[int0];
      if (luaCallFrame != nullptr) {
        this.callFrameStack[int0].closure = nullptr;
        this.callFrameStack[int0].javaFunction = nullptr;
      }

      int0++;
    }
  }

  void ensureStacksize(int int0) {
    if (int0 > 3000) {
      throw new RuntimeException("Stack overflow");
    } else {
      int int1 = this.objectStack.length;
      int int2 = int1;

      while (int2 <= int0) {
        int2 = 2 * int2;
      }

      if (int2 > int1) {
        Object[] objects = new Object[int2];
        System.arraycopy(this.objectStack, 0, objects, 0, int1);
        this.objectStack = objects;
      }
    }
  }

  void setTop(int arg0) {
    if (this.top < arg0) {
      this.ensureStacksize(arg0);
    } else {
      this.stackClear(arg0, this.top - 1);
    }

    this.top = arg0;
  }

  void stackCopy(int arg0, int arg1, int arg2) {
    if (arg2 > 0 && arg0 != arg1) {
      System.arraycopy(this.objectStack, arg0, this.objectStack, arg1, arg2);
      LuaCallFrame luaCallFrame = this.getParentNoAssert(1);
      if (Core.bDebug && luaCallFrame != nullptr &&
          luaCallFrame.closure != nullptr && luaCallFrame.pc > 0) {
        for (int int0 = arg1; int0 < arg1 + arg2; int0++) {
          int int1 = luaCallFrame.closure.prototype.lines[luaCallFrame.pc - 1];
          bool boolean0 =
              luaCallFrame.closure.prototype.lines[luaCallFrame.pc] != int1;
          if (this.thread == LuaManager.thread &&
              luaCallFrame.closure.prototype.locvarlines != nullptr) {
            while (int1 > luaCallFrame.closure.prototype
                              .locvarlines[luaCallFrame.localsAssigned] &&
                   luaCallFrame.closure.prototype
                           .locvarlines[luaCallFrame.localsAssigned] != 0) {
              luaCallFrame.localsAssigned++;
            }
          }

          if (boolean0 && this.thread == LuaManager.thread &&
              luaCallFrame.closure.prototype.locvarlines != nullptr &&
              luaCallFrame.closure.prototype
                      .locvarlines[luaCallFrame.localsAssigned] == int1) {
            int int2 = luaCallFrame.localsAssigned++;
            std::string string = luaCallFrame.closure.prototype.locvars[int2];
            luaCallFrame.setLocalVarToStack(string, int0);
          }
        }
      }
    }
  }

  void stackClear(int arg0, int arg1) {
    while (arg0 <= arg1) {
      this.objectStack[arg0] = nullptr;
      arg0++;
    }
  }

  void closeUpvalues(int arg0) {
    int int0 = this.liveUpvalues.size();

    while (--int0 >= 0) {
      UpValue upValue = this.liveUpvalues.get(int0);
      if (upValue.getIndex() < arg0) {
        return;
      }

      upValue.close();
      this.liveUpvalues.remove(int0);
    }
  }

  UpValue findUpvalue(int arg0) {
    int int0 = this.liveUpvalues.size();

    while (--int0 >= 0) {
      UpValue upValue0 = this.liveUpvalues.get(int0);
      int int1 = upValue0.getIndex();
      if (int1 == arg0) {
        return upValue0;
      }

      if (int1 < arg0) {
        break;
      }
    }

    UpValue upValue1 = new UpValue(this, arg0);
    this.liveUpvalues.add(int0 + 1, upValue1);
    return upValue1;
  }

  void *getObjectFromStack(int arg0) { return this.objectStack[arg0]; }

  int getObjectStackSize() { return this.top; }

  LuaCallFrame getParentCallframe() {
    int int0 = this.callFrameTop - 1;
    return int0 < 0 ? nullptr : this.callFrameStack[int0];
  }

  LuaCallFrame currentCallFrame() {
    if (this.isDead()) {
      return null;
    } else {
      LuaCallFrame luaCallFrame = this.callFrameStack[this.callFrameTop - 1];
      if (luaCallFrame == nullptr) {
        luaCallFrame = new LuaCallFrame(this);
        this.callFrameStack[this.callFrameTop - 1] = luaCallFrame;
      }

      return luaCallFrame;
    }
  }

  int getTop() { return this.top; }

  LuaCallFrame getParent(int arg0) {
    KahluaUtil.luaAssert(arg0 >= 0, "Level must be non-negative");
    int int0 = this.callFrameTop - arg0 - 1;
    KahluaUtil.luaAssert(int0 >= 0, "Level too high");
    return this.callFrameStack[int0];
  }

  LuaCallFrame getParentNoAssert(int arg0) {
    int int0 = this.callFrameTop - arg0 - 1;
    return int0 < 0 ? nullptr : this.callFrameStack[int0];
  }

  std::string getCurrentStackTrace(int arg0, int arg1, int arg2) {
    if (arg0 < 0) {
      arg0 = 0;
    }

    if (arg1 < 0) {
      arg1 = 0;
    }

    StringBuilder stringBuilder = new StringBuilder();

    for (int int0 = this.callFrameTop - 1 - arg0; int0 >= arg2 && arg1-- > 0;
         int0--) {
      stringBuilder.append(this.getStackTrace(this.callFrameStack[int0]));
    }

    return stringBuilder.toString();
  }

  void cleanCallFrames(LuaCallFrame arg0) {
    while (true) {
      LuaCallFrame luaCallFrame = this.currentCallFrame();
      if (luaCallFrame == nullptr || luaCallFrame == arg0) {
        return;
      }

      this.addStackTrace(luaCallFrame);
      this.popCallFrame();
    }
  }

  void addStackTrace(LuaCallFrame arg0) {
    this.stackTrace = this.stackTrace + this.getStackTrace(arg0);
  }

  std::string getStackTrace(LuaCallFrame luaCallFrame) {
    if (luaCallFrame.isLua()) {
      int[] ints = luaCallFrame.closure.prototype.lines;
      if (ints != nullptr) {
        int int0 = luaCallFrame.pc - 1;
        if (int0 >= 0 && int0 < ints.length) {
          return "at " + luaCallFrame.closure.prototype + ":" + ints[int0] +
                 "\n";
        }
      }

      return "";
    } else {
      return "at " + luaCallFrame.javaFunction + "\n";
    }
  }

  bool isDead() { return this.callFrameTop == 0; }

  Platform getPlatform() { return this.platform; }

  std::string getStatus() {
    if (this.parent == nullptr) {
      return this.isDead() ? "dead" : "suspended";
    } else {
      return "normal";
    }
  }

  bool atBottom() { return this.callFrameTop == 1; }

  int getCallframeTop() { return this.callFrameTop; }

public
  LuaCallFrame[] getCallframeStack() { return this.callFrameStack; }

  LuaCallFrame getCallFrame(int arg0) {
    if (arg0 < 0) {
      arg0 += this.callFrameTop;
    }

    return this.callFrameStack[arg0];
  }

  static void yieldHelper(LuaCallFrame arg0, LuaCallFrame arg1, int arg2) {
    KahluaUtil.luaAssert(arg0.canYield, "Can not yield outside of a coroutine");
    Coroutine coroutine0 = arg0.coroutine;
    KahluaThread kahluaThread = coroutine0.getThread();
    Coroutine coroutine1 = coroutine0.parent;
    KahluaUtil.luaAssert(coroutine1 != nullptr,
                         "Internal error, coroutine must be running");
    KahluaUtil.luaAssert(coroutine0 == kahluaThread.currentCoroutine,
                         "Internal error, must yield current thread");
    coroutine0.destroy();
    LuaCallFrame luaCallFrame = coroutine1.currentCallFrame();
    if (luaCallFrame == nullptr) {
      coroutine1.setTop(arg2 + 1);
      coroutine1.objectStack[0] = Boolean.TRUE;

      for (int int0 = 0; int0 < arg2; int0++) {
        coroutine1.objectStack[int0 + 1] = arg1.get(int0);
      }
    } else {
      luaCallFrame.push(Boolean.TRUE);

      for (int int1 = 0; int1 < arg2; int1++) {
        void *object = arg1.get(int1);
        luaCallFrame.push(object);
      }
    }

    kahluaThread.currentCoroutine = coroutine1;
  }

  void resume(Coroutine arg0) {
    this.parent = arg0;
    this.thread = arg0.thread;
  }

  KahluaThread getThread() { return this.thread; }

  void destroy() {
    this.parent = nullptr;
    this.thread = nullptr;
  }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
