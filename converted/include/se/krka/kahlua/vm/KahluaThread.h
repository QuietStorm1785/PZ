#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/stdlib/BaseLib.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/ui/UIManager.h"
#include <algorithm>
#include <cstdint>
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
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KahluaThread {
public:
  static const int FIELDS_PER_FLUSH = 50;
  static const int OP_MOVE = 0;
  static const int OP_LOADK = 1;
  static const int OP_LOADBOOL = 2;
  static const int OP_LOADNIL = 3;
  static const int OP_GETUPVAL = 4;
  static const int OP_GETGLOBAL = 5;
  static const int OP_GETTABLE = 6;
  static const int OP_SETGLOBAL = 7;
  static const int OP_SETUPVAL = 8;
  static const int OP_SETTABLE = 9;
  static const int OP_NEWTABLE = 10;
  static const int OP_SELF = 11;
  static const int OP_ADD = 12;
  static const int OP_SUB = 13;
  static const int OP_MUL = 14;
  static const int OP_DIV = 15;
  static const int OP_MOD = 16;
  static const int OP_POW = 17;
  static const int OP_UNM = 18;
  static const int OP_NOT = 19;
  static const int OP_LEN = 20;
  static const int OP_CONCAT = 21;
  static const int OP_JMP = 22;
  static const int OP_EQ = 23;
  static const int OP_LT = 24;
  static const int OP_LE = 25;
  static const int OP_TEST = 26;
  static const int OP_TESTSET = 27;
  static const int OP_CALL = 28;
  static const int OP_TAILCALL = 29;
  static const int OP_RETURN = 30;
  static const int OP_FORLOOP = 31;
  static const int OP_FORPREP = 32;
  static const int OP_TFORLOOP = 33;
  static const int OP_SETLIST = 34;
  static const int OP_CLOSE = 35;
  static const int OP_CLOSURE = 36;
  static const int OP_VARARG = 37;
  static const int MAX_INDEX_RECURSION = 100;
private
  static final String[] meta_ops = new String[38];
  static LuaCallFrame LastCallFrame = null;
  const Coroutine rootCoroutine;
  Coroutine currentCoroutine;
  bool doProfiling = false;
  const PrintStream out;
  const Platform platform;
  bool bStep = false;
  std::string currentfile;
  int currentLine;
  int lastLine;
  int lastCallFrame;
  bool bReset = false;
public
  ArrayList<KahluaThread.Entry> profileEntries =
      std::make_unique<ArrayList<>>();
public
  HashMap<String, KahluaThread.Entry> profileEntryMap =
      std::make_unique<HashMap<>>();
  static int m_error_count = 0;
public
  static final ArrayList<String> m_errors_list =
      std::make_unique<ArrayList<>>();
  const StringBuilder m_stringBuilder = new StringBuilder();
  const StringWriter m_stringWriter = new StringWriter();
  const PrintWriter m_printWriter = new PrintWriter(this.m_stringWriter);
  HashMap<String, ArrayList<Long>> BreakpointMap =
      std::make_unique<HashMap<>>();
  HashMap<KahluaTable, ArrayList<Object>> BreakpointDataMap =
      std::make_unique<HashMap<>>();
  HashMap<KahluaTable, ArrayList<Object>> BreakpointReadDataMap =
      std::make_unique<HashMap<>>();
  bool bStepInto = false;

  Coroutine getCurrentCoroutine() { return this.currentCoroutine; }

public
  KahluaThread(Platform arg0, KahluaTable arg1) {
    this(System.out, arg0, arg1);
  }

public
  KahluaThread(PrintStream arg0, Platform arg1, KahluaTable arg2) {
    this.platform = arg1;
    this.out = arg0;
    this.rootCoroutine = new Coroutine(arg1, arg2, this);
    this.currentCoroutine = this.rootCoroutine;
  }

  int call(int arg0) {
    int int0 = this.currentCoroutine.getTop();
    int int1 = int0 - arg0 - 1;
    void *object = this.currentCoroutine.objectStack[int1];
    if (object == nullptr) {
      throw new RuntimeException("tried to call nil");
    } else {
      try {
        if (object instanceof JavaFunction) {
          return this.callJava((JavaFunction)object, int1 + 1, int1, arg0);
        }
      } catch (Exception exception) {
        throw new RuntimeException(exception.getClass().getName() + " " +
                                   exception.getMessage() + " in " +
                                   (JavaFunction)object);
      }

      if (!(object instanceof LuaClosure)) {
        throw new RuntimeException("tried to call a non-function");
      } else {
        LuaCallFrame luaCallFrame = this.currentCoroutine.pushNewCallFrame(
            (LuaClosure)object, null, int1 + 1, int1, arg0, false, false);
        luaCallFrame.init();
        this.luaMainloop();
        int int2 = this.currentCoroutine.getTop() - int1;
        this.currentCoroutine.stackTrace = "";
        return int2;
      }
    }
  }

  int callJava(JavaFunction javaFunction, int int0, int int1, int int2) {
    Coroutine coroutine = this.currentCoroutine;
    LuaCallFrame luaCallFrame = coroutine.pushNewCallFrame(
        null, javaFunction, int0, int1, int2, false, false);
    int int3 = javaFunction.call(luaCallFrame, int2);
    int int4 = luaCallFrame.getTop();
    int int5 = int4 - int3;
    int int6 = int1 - int0;
    luaCallFrame.stackCopy(int5, int6, int3);
    luaCallFrame.setTop(int3 + int6);
    coroutine.popCallFrame();
    return int3;
  }

  void *prepareMetatableCall(void *object) {
    return !(object instanceof JavaFunction) && !(object instanceof LuaClosure)
               ? this.getMetaOp(object, "__call")
               : object;
  }

  bool isCurrent(const std::string &arg0, int arg1) {
    return arg1 = = this.currentLine;
  }

  void luaMainloop() {
    LuaCallFrame luaCallFrame0 = this.currentCoroutine.currentCallFrame();
    LuaClosure luaClosure0 = luaCallFrame0.closure;
    Prototype prototype0 = luaClosure0.prototype;
    int[] ints = prototype0.code;
    int int0 = luaCallFrame0.returnBase;
    std::string string0 = "";
    long long0 = System.nanoTime();
    if (this.doProfiling && Core.bDebug && this == LuaManager.thread) {
      Coroutine coroutine0 = this.getCurrentCoroutine();
      std::string string1 = coroutine0.objectStack[0].toString();
      std::string string2 = coroutine0.getThread().currentfile + " " +
                            string1.substring(0, string1.indexOf(":"));
      string0 = string2;
    }

    bool boolean0 = true;

    while (!this.bReset) {
      if (Core.bDebug && this == LuaManager.thread) {
        Coroutine coroutine1 = this.getCurrentCoroutine();
        if (coroutine1 != nullptr) {
          this.lastLine = this.currentLine;
          LuaCallFrame luaCallFrame1 = coroutine1.currentCallFrame();
          if (luaCallFrame1.closure != nullptr) {
            this.currentfile = luaCallFrame1.closure.prototype.filename;
            this.currentLine =
                luaCallFrame1.closure.prototype.lines[luaCallFrame1.pc];
            if (this.bStep && this.currentLine != this.lastLine) {
              if (this.bStepInto) {
                this.bStep = false;
                UIManager.debugBreakpoint(
                    luaCallFrame1.closure.prototype.filename,
                    this.currentLine - 1L);
                this.lastCallFrame = coroutine1.getCallframeTop();
                boolean0 = true;
              } else if (coroutine1.getCallframeTop() <= this.lastCallFrame) {
                this.bStep = false;
                this.lastCallFrame = coroutine1.getCallframeTop();
                UIManager.debugBreakpoint(
                    luaCallFrame1.closure.prototype.filename,
                    this.currentLine - 1L);
                boolean0 = true;
              }
            }

            if (this.BreakpointMap.containsKey(
                    luaCallFrame1.closure.prototype.filename)) {
              std::vector arrayList = this.BreakpointMap.get(
                  luaCallFrame1.closure.prototype.filename);
              if (arrayList.contains((long)luaCallFrame1.closure.prototype
                                         .lines[luaCallFrame1.pc]) &&
                  (luaCallFrame1.pc == 0 ||
                   luaCallFrame1.closure.prototype
                           .lines[luaCallFrame1.pc - 1] !=
                       luaCallFrame1.closure.prototype
                           .lines[luaCallFrame1.pc])) {
                UIManager.debugBreakpoint(
                    luaCallFrame1.closure.prototype.filename,
                    luaCallFrame1.closure.prototype.lines[luaCallFrame1.pc]);
              }
            }
          }
        }
      }

      boolean0 = true;

      try {
        if (this.bStep) {
          bool boolean1 = false;
        }

        int int1 = ints[luaCallFrame0.pc++];
        int int2 = int1 & 63;
        switch (int2) {
        case 0:
          int int3 = getA8(int1);
          int int4 = getB9(int1);
          luaCallFrame0.set(int3, luaCallFrame0.get(int4));
          boolean0 = false;
          break;
        case 1:
          int int93 = getA8(int1);
          int int94 = getBx(int1);
          if (Core.bDebug) {
            int int95 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean16 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int95;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int95 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean16 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int95) {
              int int96 = luaCallFrame0.localsAssigned++;
              std::string string18 =
                  luaCallFrame0.closure.prototype.locvars[int96];
              luaCallFrame0.setLocalVarToStack(string18,
                                               luaCallFrame0.localBase + int93);
            }
          }

          luaCallFrame0.set(int93, prototype0.constants[int94]);
          break;
        case 2:
          int int31 = getA8(int1);
          int int32 = getB9(int1);
          int int33 = getC9(int1);
          bool boolean2 = int32 == 0 ? Boolean.FALSE : Boolean.TRUE;
          if (Core.bDebug) {
            int int34 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean3 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int34;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int34 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean3 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int34) {
              int int35 = luaCallFrame0.localsAssigned++;
              std::string string4 =
                  luaCallFrame0.closure.prototype.locvars[int35];
              if (string4 == "group")) {
    bool boolean4 = false;
                                }

              luaCallFrame0.setLocalVarToStack(string4,
                                               luaCallFrame0.localBase + int31);
            }
          }

          luaCallFrame0.set(int31, boolean2);
          if (int33 != 0) {
            luaCallFrame0.pc++;
          }
          break;
        case 3:
          int int89 = getA8(int1);
          int int90 = getB9(int1);
          if (Core.bDebug) {
            int int91 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean15 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int91;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int91 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean15 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int91) {
              int int92 = luaCallFrame0.localsAssigned++;
              std::string string17 =
                  luaCallFrame0.closure.prototype.locvars[int92];
              luaCallFrame0.setLocalVarToStack(string17,
                                               luaCallFrame0.localBase + int89);
            }
          }

          luaCallFrame0.stackClear(int89, int90);
          break;
        case 4:
          int int85 = getA8(int1);
          int int86 = getB9(int1);
          UpValue upValue1 = luaClosure0.upvalues[int86];
          if (Core.bDebug) {
            int int87 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean13 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int87;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int87 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean13 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int87) {
              int int88 = luaCallFrame0.localsAssigned++;
              std::string string16 =
                  luaCallFrame0.closure.prototype.locvars[int88];
              if (string16 == "group")) {
    bool boolean14 = false;
                                }

              luaCallFrame0.setLocalVarToStack(string16,
                                               luaCallFrame0.localBase + int85);
            }
          }

          luaCallFrame0.set(int85, upValue1.getValue());
          break;
        case 5:
          int int81 = getA8(int1);
          int int82 = getBx(int1);
          void *object39 =
              this.tableget(luaClosure0.env, prototype0.constants[int82]);
          if (Core.bDebug) {
            int int83 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean11 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int83;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int83 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean11 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int83) {
              int int84 = luaCallFrame0.localsAssigned++;
              std::string string15 =
                  luaCallFrame0.closure.prototype.locvars[int84];
              if (string15 == "group")) {
    bool boolean12 = false;
                                }

              luaCallFrame0.setLocalVarToStack(string15,
                                               luaCallFrame0.localBase + int81);
            }
          }

          luaCallFrame0.set(int81, object39);
          break;
        case 6:
          int int76 = getA8(int1);
          int int77 = getB9(int1);
          int int78 = getC9(int1);
          void *object36 = luaCallFrame0.get(int77);
          void *object37 =
              this.getRegisterOrConstant(luaCallFrame0, int78, prototype0);
          void *object38 = this.tableget(object36, object37);
          if (Core.bDebug) {
            int int79 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean10 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int79;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int79 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean10 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int79) {
              int int80 = luaCallFrame0.localsAssigned++;
              std::string string14 =
                  luaCallFrame0.closure.prototype.locvars[int80];
              luaCallFrame0.setLocalVarToStack(string14,
                                               luaCallFrame0.localBase + int76);
            }
          }

          luaCallFrame0.set(int76, object38);
          break;
        case 7:
          int int29 = getA8(int1);
          int int30 = getBx(int1);
          void *object16 = luaCallFrame0.get(int29);
          void *object17 = prototype0.constants[int30];
          if (object16 instanceof LuaClosure && object17 instanceof String) {
            ((LuaClosure)object16).debugName = object17.toString();
          }

          if (LuaCompiler.rewriteEvents) {
            void *object18 = luaClosure0.env.rawget(object17);
            if (object18 instanceof KahluaTable && object18 != object16) {
              KahluaTableImpl kahluaTableImpl = (KahluaTableImpl)object18;
              kahluaTableImpl.setRewriteTable(object16);
            }

            this.tableSet(luaClosure0.env, object17, object16);
          } else {
            this.tableSet(luaClosure0.env, object17, object16);
          }
          break;
        case 8:
          int int72 = getA8(int1);
          int int73 = getB9(int1);
          UpValue upValue0 = luaClosure0.upvalues[int73];
          if (Core.bDebug) {
            int int74 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean9 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int74;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int74 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean9 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int74) {
              int int75 = luaCallFrame0.localsAssigned++;
              std::string string13 =
                  luaCallFrame0.closure.prototype.locvars[int75];
              luaCallFrame0.setLocalVarToStack(string13,
                                               luaCallFrame0.localBase + int72);
            }
          }

          upValue0.setValue(luaCallFrame0.get(int72));
          break;
        case 9:
          int int5 = getA8(int1);
          int int6 = getB9(int1);
          int int7 = getC9(int1);
          void *object0 = luaCallFrame0.get(int5);
          void *object1 =
              this.getRegisterOrConstant(luaCallFrame0, int6, prototype0);
          void *object2 =
              this.getRegisterOrConstant(luaCallFrame0, int7, prototype0);
          this.tableSet(object0, object1, object2);
          break;
        case 10:
          int int69 = getA8(int1);
          KahluaTable table2 = this.platform.newTable();
          if (Core.bDebug) {
            int int70 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean8 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int70;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int70 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean8 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int70) {
              int int71 = luaCallFrame0.localsAssigned++;
              std::string string12 =
                  luaCallFrame0.closure.prototype.locvars[int71];
              luaCallFrame0.setLocalVarToStack(string12,
                                               luaCallFrame0.localBase + int69);
            }
          }

          luaCallFrame0.set(int69, table2);
          break;
        case 11:
          int int8 = getA8(int1);
          int int9 = getB9(int1);
          int int10 = getC9(int1);
          void *object3 =
              this.getRegisterOrConstant(luaCallFrame0, int10, prototype0);
          void *object4 = luaCallFrame0.get(int9);
          LastCallFrame = luaCallFrame0;
          void *object5 = this.tableget(object4, object3);
          luaCallFrame0.set(int8, object5);
          luaCallFrame0.set(int8 + 1, object4);
          boolean0 = false;
          break;
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
          int int64 = getA8(int1);
          int int65 = getB9(int1);
          int int66 = getC9(int1);
          void *object30 =
              this.getRegisterOrConstant(luaCallFrame0, int65, prototype0);
          void *object31 =
              this.getRegisterOrConstant(luaCallFrame0, int66, prototype0);
          void *object32 = null;
          void *object33 = null;
          void *object34 = null;
          if ((object32 = KahluaUtil.rawTonumber(object30)) != nullptr &&
              (object33 = KahluaUtil.rawTonumber(object31)) != nullptr) {
            object34 =
                this.primitiveMath((Double)object32, (Double)object33, int2);
          } else {
            std::string string9 = meta_ops[int2];
            void *object35 = this.getBinMetaOp(object30, object31, string9);
            if (object35 == nullptr) {
              this.doStacktraceProper(luaCallFrame0);
              std::string string10 = "unknown";
              if (luaClosure0.debugName != nullptr) {
                string10 = luaClosure0.debugName;
              } else if (prototype0.name != nullptr) {
                string10 = prototype0.name;
              }

              KahluaUtil.fail(string9 + " not defined for operands in " +
                              string10);
            }

            object34 = this.call(object35, object30, object31, nullptr);
          }

          if (Core.bDebug) {
            int int67 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc - 1];
            bool boolean7 =
                luaCallFrame0.closure.prototype.lines[luaCallFrame0.pc] !=
                int67;
            if (this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr) {
              while (int67 > luaCallFrame0.closure.prototype
                                 .locvarlines[luaCallFrame0.localsAssigned] &&
                     luaCallFrame0.closure.prototype
                             .locvarlines[luaCallFrame0.localsAssigned] != 0) {
                luaCallFrame0.localsAssigned++;
              }
            }

            if (boolean7 && this == LuaManager.thread &&
                luaCallFrame0.closure.prototype.locvarlines != nullptr &&
                luaCallFrame0.closure.prototype
                        .locvarlines[luaCallFrame0.localsAssigned] == int67) {
              int int68 = luaCallFrame0.localsAssigned++;
              std::string string11 =
                  luaCallFrame0.closure.prototype.locvars[int68];
              luaCallFrame0.setLocalVarToStack(string11,
                                               luaCallFrame0.localBase + int64);
            }
          }

          luaCallFrame0.set(int64, object34);
          break;
        case 18:
          int int27 = getA8(int1);
          int int28 = getB9(int1);
          void *object13 = luaCallFrame0.get(int28);
          double double2 = KahluaUtil.rawTonumber(object13);
          void *object14;
          if (double2 != nullptr) {
            object14 = KahluaUtil.toDouble(-KahluaUtil.fromDouble(double2));
          } else {
            void *object15 = this.getMetaOp(object13, "__unm");
            object14 = this.call(object15, object13, nullptr, nullptr);
          }

          luaCallFrame0.set(int27, object14);
          break;
        case 19:
          int int25 = getA8(int1);
          int int26 = getB9(int1);
          void *object12 = luaCallFrame0.get(int26);
          luaCallFrame0.set(
              int25, KahluaUtil.toBoolean(!KahluaUtil.boolEval(object12)));
          boolean0 = false;
          break;
        case 20:
          int int23 = getA8(int1);
          int int24 = getB9(int1);
          void *object9 = luaCallFrame0.get(int24);
          void *object10;
          if (object9 instanceof KahluaTable table0) {
            object10 = KahluaUtil.toDouble((long)table0.len());
          } else if (object9 instanceof String string3) {
            object10 = KahluaUtil.toDouble((long)string3.length());
          } else {
            void *object11 = this.getMetaOp(object9, "__len");
            if (object11 == nullptr) {
              this.doStacktraceProper(luaCallFrame0);
            }

            KahluaUtil.luaAssert(object11 != nullptr,
                                 "__len not defined for operand");
            object10 = this.call(object11, object9, nullptr, nullptr);
          }

          luaCallFrame0.set(int23, object10);
          boolean0 = false;
          break;
        case 21:
          int int56 = getA8(int1);
          int int57 = getB9(int1);
          int int58 = getC9(int1);
          int int59 = int57;
          void *object27 = luaCallFrame0.get(int58);
          int int60 = int58 - 1;

          while (int59 <= int60) {
            std::string string8 = KahluaUtil.rawTostring(object27);
            if (string8 != nullptr) {
              int int61 = 0;

              for (int int62 = int60; int59 <= int62; int61++) {
                void *object28 = luaCallFrame0.get(int62);
                int62--;
                if (KahluaUtil.rawTostring(object28) == nullptr) {
                  break;
                }
              }

              if (int61 > 0) {
                StringBuilder stringBuilder = new StringBuilder();

                for (int int63 = int60 - int61 + 1; int63 <= int60; int63++) {
                  stringBuilder.append(
                      KahluaUtil.rawTostring(luaCallFrame0.get(int63)));
                }

                stringBuilder.append(string8);
                object27 = stringBuilder.toString();
                int60 -= int61;
              }
            }

            if (int59 <= int60) {
              string8 = (String)luaCallFrame0.get(int60);
              void *object29 = this.getBinMetaOp(string8, object27, "__concat");
              if (object29 == nullptr) {
                KahluaUtil.fail("__concat not defined for operands: " +
                                string8 + " and " + object27);
              }

              object27 = this.call(object29, string8, object27, nullptr);
              int60--;
            }
          }

          luaCallFrame0.set(int56, object27);
          boolean0 = false;
          break;
        case 22:
          luaCallFrame0.pc = luaCallFrame0.pc + getSBx(int1);
          break;
        case 23:
        case 24:
        case 25:
          int int52 = getA8(int1);
          int int53 = getB9(int1);
          int int54 = getC9(int1);
          void *object22 =
              this.getRegisterOrConstant(luaCallFrame0, int53, prototype0);
          void *object23 =
              this.getRegisterOrConstant(luaCallFrame0, int54, prototype0);
          if (object22 instanceof Double && object23 instanceof Double) {
            double double8 = KahluaUtil.fromDouble(object22);
            double double9 = KahluaUtil.fromDouble(object23);
            if (int2 == 23) {
              if (double8 == double9 == (int52 == 0)) {
                luaCallFrame0.pc++;
              }
            } else if (int2 == 24) {
              if (double8 < double9 == (int52 == 0)) {
                luaCallFrame0.pc++;
              }
            } else if (double8 <= double9 == (int52 == 0)) {
              luaCallFrame0.pc++;
            }
          } else if (object22 instanceof String && object23 instanceof String) {
            if (int2 == 23) {
              if (object22 == object23) == (int52 == 0)) {
                                    luaCallFrame0.pc++;
                                }
            } else {
              std::string string5 = (String)object22;
              std::string string6 = (String)object23;
              int int55 = string5.compareTo(string6);
              if (int2 == 24) {
                if (int55 < 0 == (int52 == 0)) {
                  luaCallFrame0.pc++;
                }
              } else if (int55 <= 0 == (int52 == 0)) {
                luaCallFrame0.pc++;
              }
            }
          } else {
            bool boolean5;
            if (object22 == object23 && int2 == 23) {
              boolean5 = true;
            } else {
              bool boolean6 = false;
              std::string string7 = meta_ops[int2];
              void *object24 = this.getCompMetaOp(object22, object23, string7);
              if (object24 == nullptr && int2 == 25) {
                object24 = this.getCompMetaOp(object22, object23, "__lt");
                void *object25 = object22;
                object22 = object23;
                object23 = object25;
                boolean6 = true;
              }

              if (object24 == nullptr && int2 == 23) {
                boolean5 = BaseLib.luaEquals(object22, object23);
              } else {
                if (object24 == nullptr) {
                  this.doStacktraceProper(luaCallFrame0);
                  KahluaUtil.fail(string7 + " not defined for operand");
                }

                void *object26 = this.call(object24, object22, object23, null);
                boolean5 = KahluaUtil.boolEval(object26);
              }

              if (boolean6) {
                boolean5 = !boolean5;
              }
            }

            if (boolean5 == (int52 == 0)) {
              luaCallFrame0.pc++;
            }
          }

          boolean0 = false;
          break;
        case 26:
          int int21 = getA8(int1);
          int int22 = getC9(int1);
          void *object8 = luaCallFrame0.get(int21);
          if (KahluaUtil.boolEval(object8) == (int22 == 0)) {
            luaCallFrame0.pc++;
          }
          break;
        case 27:
          int int18 = getA8(int1);
          int int19 = getB9(int1);
          int int20 = getC9(int1);
          void *object7 = luaCallFrame0.get(int19);
          if (KahluaUtil.boolEval(object7) != (int20 == 0)) {
            luaCallFrame0.set(int18, object7);
          } else {
            luaCallFrame0.pc++;
          }
          break;
        case 28:
          int int100 = getA8(int1);
          int int101 = getB9(int1);
          int int102 = getC9(int1);
          int int103 = int101 - 1;
          if (int103 != -1) {
            luaCallFrame0.setTop(int100 + int103 + 1);
          } else {
            int103 = luaCallFrame0.getTop() - int100 - 1;
          }

          luaCallFrame0.restoreTop = int102 != 0;
          int int104 = luaCallFrame0.localBase;
          int int105 = int104 + int100 + 1;
          int int106 = int104 + int100;
          void *object40 = luaCallFrame0.get(int100);
          if (object40 == nullptr) {
            bool boolean17 = false;
            object40 = luaCallFrame0.get(int100);
          }

          if (object40 == nullptr) {
            this.doStacktraceProper(luaCallFrame0);
            if (luaCallFrame0.getClosure().debugName != nullptr) {
              KahluaUtil.fail("Object tried to call nil in " +
                              luaCallFrame0.getClosure().debugName);
            } else if (luaCallFrame0.getClosure().prototype != nullptr &&
                       luaCallFrame0.getClosure().prototype.name != nullptr) {
              KahluaUtil.fail("Object tried to call nil in " +
                              luaCallFrame0.getClosure().prototype.name);
            } else {
              KahluaUtil.fail("Object tried to call nil in unknown");
            }
          }

          void *object41 = this.prepareMetatableCall(object40);
          if (object41 == nullptr) {
            KahluaUtil.fail("Object " + object40 +
                            " did not have __call metatable set");
          }

          if (object41 != object40) {
            int105 = int106;
            int103++;
          }

          if (object41 instanceof LuaClosure) {
            LuaCallFrame luaCallFrame2 = this.currentCoroutine.pushNewCallFrame(
                (LuaClosure)object41, nullptr, int105, int106, int103, true,
                luaCallFrame0.canYield);
            luaCallFrame2.init();
            luaCallFrame0 = luaCallFrame2;
            luaClosure0 = luaCallFrame2.closure;
            prototype0 = luaClosure0.prototype;
            ints = prototype0.code;
            int0 = luaCallFrame2.returnBase;
            break;
          } else {
            if (!(object41 instanceof JavaFunction)) {
              throw new RuntimeException("Tried to call a non-function: " +
                                         object41);
            }

            this.callJava((JavaFunction)object41, int105, int106, int103);
            luaCallFrame0 = this.currentCoroutine.currentCallFrame();
            if (luaCallFrame0 != nullptr && !luaCallFrame0.isJava()) {
              luaClosure0 = luaCallFrame0.closure;
              prototype0 = luaClosure0.prototype;
              ints = prototype0.code;
              int0 = luaCallFrame0.returnBase;
              if (luaCallFrame0.restoreTop) {
                luaCallFrame0.setTop(prototype0.maxStacksize);
              }
              break;
            }

            long long4 = System.nanoTime();
            return;
          }
        case 29:
          int int36 = luaCallFrame0.localBase;
          this.currentCoroutine.closeUpvalues(int36);
          int int37 = getA8(int1);
          int int38 = getB9(int1);
          int int39 = int38 - 1;
          if (int39 == -1) {
            int39 = luaCallFrame0.getTop() - int37 - 1;
          }

          luaCallFrame0.restoreTop = false;
          void *object19 = luaCallFrame0.get(int37);

          try {
            KahluaUtil.luaAssert(object19 != nullptr, "Tried to call nil");
          } catch (Exception exception0) {
            if (Core.bDebug && UIManager.defaultthread == LuaManager.thread) {
              UIManager.debugBreakpoint(LuaManager.thread.currentfile,
                                        LuaManager.thread.currentLine - 1);
            }

            this.debugException(exception0);
            this.doStacktraceProper(luaCallFrame0);
            KahluaUtil.fail("");
          }

          void *object20 = this.prepareMetatableCall(object19);
          if (object20 == nullptr) {
            KahluaUtil.fail("Object did not have __call metatable set");
          }

          int int40 = int0 + 1;
          if (object20 != object19) {
            int40 = int0;
            int39++;
          }

          this.currentCoroutine.stackCopy(int36 + int37, int0, int39 + 1);
          this.currentCoroutine.setTop(int0 + int39 + 1);
          if (object20 instanceof LuaClosure) {
            luaCallFrame0.localBase = int40;
            luaCallFrame0.nArguments = int39;
            luaCallFrame0.closure = (LuaClosure)object20;
            luaCallFrame0.init();
          } else {
            if (!(object20 instanceof JavaFunction)) {
              KahluaUtil.fail("Tried to call a non-function: " + object20);
            }

            Coroutine coroutine2 = this.currentCoroutine;
            this.callJava((JavaFunction)object20, int40, int0, int39);
            luaCallFrame0 = this.currentCoroutine.currentCallFrame();
            coroutine2.popCallFrame();
            if (coroutine2 != this.currentCoroutine) {
              if (coroutine2.isDead() && coroutine2 != this.rootCoroutine &&
                  this.currentCoroutine.getParent() == coroutine2) {
                this.currentCoroutine.resume(coroutine2.getParent());
                coroutine2.destroy();
                this.currentCoroutine.getParent().currentCallFrame().push(
                    Boolean.TRUE);
              }

              luaCallFrame0 = this.currentCoroutine.currentCallFrame();
              if (luaCallFrame0.isJava()) {
                long long1 = System.nanoTime();
                return;
              }
            } else {
              if (!luaCallFrame0.fromLua) {
                long long2 = System.nanoTime();
                return;
              }

              luaCallFrame0 = this.currentCoroutine.currentCallFrame();
              if (luaCallFrame0.restoreTop) {
                luaCallFrame0.setTop(
                    luaCallFrame0.closure.prototype.maxStacksize);
              }
            }
          }

          luaClosure0 = luaCallFrame0.closure;
          prototype0 = luaClosure0.prototype;
          ints = prototype0.code;
          int0 = luaCallFrame0.returnBase;
          break;
        case 30:
          int int97 = getA8(int1);
          int int98 = getB9(int1) - 1;
          int int99 = luaCallFrame0.localBase;
          this.currentCoroutine.closeUpvalues(int99);
          if (int98 == -1) {
            int98 = luaCallFrame0.getTop() - int97;
          }

          this.currentCoroutine.stackCopy(luaCallFrame0.localBase + int97, int0,
                                          int98);
          this.currentCoroutine.setTop(int0 + int98);
          if (!luaCallFrame0.fromLua) {
            this.currentCoroutine.popCallFrame();
            long long3 = System.nanoTime();
            return;
          }

          if (luaCallFrame0.canYield && this.currentCoroutine.atBottom()) {
            luaCallFrame0.localBase = luaCallFrame0.returnBase;
            Coroutine coroutine3 = this.currentCoroutine;
            Coroutine.yieldHelper(luaCallFrame0, luaCallFrame0, int98);
            coroutine3.popCallFrame();
            luaCallFrame0 = this.currentCoroutine.currentCallFrame();
            if (luaCallFrame0 == nullptr || luaCallFrame0.isJava()) {
              return;
            }
          } else {
            this.currentCoroutine.popCallFrame();
          }

          luaCallFrame0 = this.currentCoroutine.currentCallFrame();
          luaClosure0 = luaCallFrame0.closure;
          prototype0 = luaClosure0.prototype;
          ints = prototype0.code;
          int0 = luaCallFrame0.returnBase;
          if (luaCallFrame0.restoreTop) {
            luaCallFrame0.setTop(prototype0.maxStacksize);
          }
          break;
        case 31:
          int int50 = getA8(int1);
          double double4 = KahluaUtil.fromDouble(luaCallFrame0.get(int50));
          double double5 = KahluaUtil.fromDouble(luaCallFrame0.get(int50 + 1));
          double double6 = KahluaUtil.fromDouble(luaCallFrame0.get(int50 + 2));
          double4 += double6;
          double double7 = KahluaUtil.toDouble(double4);
          luaCallFrame0.set(int50, double7);
          if (double6 > 0.0 ? !(double4 <= double5) : !(double4 >= double5)) {
            luaCallFrame0.clearFromIndex(int50);
          } else {
            int int51 = getSBx(int1);
            luaCallFrame0.pc += int51;
            luaCallFrame0.set(int50 + 3, double7);
          }
          break;
        case 32:
          int int11 = getA8(int1);
          int int12 = getSBx(int1);
          double double0 = KahluaUtil.fromDouble(luaCallFrame0.get(int11));
          double double1 = KahluaUtil.fromDouble(luaCallFrame0.get(int11 + 2));
          luaCallFrame0.set(int11, KahluaUtil.toDouble(double0 - double1));
          luaCallFrame0.pc += int12;
          break;
        case 33:
          int int16 = getA8(int1);
          int int17 = getC9(int1);
          luaCallFrame0.setTop(int16 + 6);
          luaCallFrame0.stackCopy(int16, int16 + 3, 3);
          this.call(2);
          luaCallFrame0.clearFromIndex(int16 + 3 + int17);
          luaCallFrame0.setPrototypeStacksize();
          void *object6 = luaCallFrame0.get(int16 + 3);
          if (object6 != nullptr) {
            luaCallFrame0.set(int16 + 2, object6);
          } else {
            luaCallFrame0.pc++;
          }
          break;
        case 34:
          int int45 = getA8(int1);
          int int46 = getB9(int1);
          int int47 = getC9(int1);
          if (int46 == 0) {
            int46 = luaCallFrame0.getTop() - int45 - 1;
          }

          if (int47 == 0) {
            int47 = ints[luaCallFrame0.pc++];
          }

          int int48 = (int47 - 1) * 50;
          KahluaTable table1 = (KahluaTable)luaCallFrame0.get(int45);

          for (int int49 = 1; int49 <= int46; int49++) {
            double double3 = KahluaUtil.toDouble((long)(int48 + int49));
            void *object21 = luaCallFrame0.get(int45 + int49);
            table1.rawset(double3, object21);
          }
          break;
        case 35:
          int int13 = getA8(int1);
          luaCallFrame0.closeUpvalues(int13);
          break;
        case 36:
          int int41 = getA8(int1);
          int int42 = getBx(int1);
          Prototype prototype1 = prototype0.prototypes[int42];
          LuaClosure luaClosure1 = new LuaClosure(prototype1, luaClosure0.env);
          luaCallFrame0.set(int41, luaClosure1);
          int int43 = prototype1.numUpvalues;

          for (int int44 = 0; int44 < int43; int44++) {
            int1 = ints[luaCallFrame0.pc++];
            int2 = int1 & 63;
            int42 = getB9(int1);
            switch (int2) {
            case 0:
              luaClosure1.upvalues[int44] = luaCallFrame0.findUpvalue(int42);
              break;
            case 4:
              luaClosure1.upvalues[int44] = luaClosure0.upvalues[int42];
            }
          }
          break;
        case 37:
          int int14 = getA8(int1);
          int int15 = getB9(int1) - 1;
          luaCallFrame0.pushVarargs(int14, int15);
        }
      } catch (RuntimeException runtimeException) {
        if (Core.bDebug && UIManager.defaultthread == LuaManager.thread) {
        }

        if (runtimeException.getMessage() != nullptr) {
          ExceptionLogger.logException(runtimeException);
          this.debugException(runtimeException);
        }

        this.doStacktraceProper(luaCallFrame0);
        KahluaUtil.fail("");
        bool boolean18 = true;

        do {
          luaCallFrame0 = this.currentCoroutine.currentCallFrame();
          if (luaCallFrame0 == nullptr) {
            Coroutine coroutine4 = this.currentCoroutine.getParent();
            if (coroutine4 != nullptr) {
              LuaCallFrame luaCallFrame3 = coroutine4.currentCallFrame();
              luaCallFrame3.push(Boolean.FALSE);
              luaCallFrame3.push(runtimeException.getMessage());
              luaCallFrame3.push(this.currentCoroutine.stackTrace);
              this.currentCoroutine.destroy();
              this.currentCoroutine = coroutine4;
              luaCallFrame0 = this.currentCoroutine.currentCallFrame();
              luaClosure0 = luaCallFrame0.closure;
              prototype0 = luaClosure0.prototype;
              ints = prototype0.code;
              int0 = luaCallFrame0.returnBase;
              boolean18 = false;
            }
            break;
          }

          this.currentCoroutine.addStackTrace(luaCallFrame0);
          this.currentCoroutine.popCallFrame();
        } while (luaCallFrame0.fromLua);

        if (luaCallFrame0 != nullptr) {
          luaCallFrame0.closeUpvalues(0);
        }

        if (boolean18) {
          throw runtimeException;
        }
      } catch (Exception exception1) {
        if (Core.bDebug && UIManager.defaultthread == LuaManager.thread) {
          UIManager.debugBreakpoint(LuaManager.thread.currentfile,
                                    LuaManager.thread.currentLine - 1);
        }

        if (exception1.getMessage() != nullptr) {
          System.out.printf(exception1.getMessage());
        }
      }

      if (this.bReset) {
        throw new RuntimeException("lua was reset");
      }
    }

    long long5 = System.nanoTime();
    this.DoProfileTiming(string0, long0, long5);
  }

  void DoProfileTiming(const std::string &string, long long1, long long0) {
    if (this.doProfiling) {
      double double0 = (long0 - long1) / 1000000.0;
      if (GameWindow.states.current == IngameState.instance) {
        KahluaThread.Entry entry = nullptr;
        if (this.profileEntryMap.containsKey(string)) {
          entry = this.profileEntryMap.get(string);
        } else {
          entry = new KahluaThread.Entry();
          this.profileEntryMap.put(string, entry);
          this.profileEntries.add(entry);
          entry.file = string;
        }

        entry.time += double0;
        Collections.sort(this.profileEntries,
                         new KahluaThread.ProfileEntryComparitor());
      }
    }
  }

  StringBuilder startErrorMessage() {
    this.m_stringBuilder.setLength(0);
    return this.m_stringBuilder;
  }

  void flushErrorMessage() {
    std::string string = this.m_stringBuilder.toString();
    DebugLog.log(string);

    while (m_errors_list.size() >= 40) {
      m_errors_list.remove(0);
    }

    m_errors_list.add(string);
    m_error_count++;
  }

  void doStacktraceProper(LuaCallFrame arg0) {
    if (arg0 != nullptr) {
      StringBuilder stringBuilder = this.startErrorMessage();
      stringBuilder.append("-----------------------------------------\n");
      stringBuilder.append("STACK TRACE\n");
      stringBuilder.append("-----------------------------------------\n");
      int int0 = arg0.coroutine.getCallframeTop();

      for (int int1 = int0 - 1; int1 >= 0; int1--) {
        LuaCallFrame luaCallFrame = arg0.coroutine.getCallFrame(int1);
        stringBuilder.append(luaCallFrame.toString2());
        stringBuilder.append("\n");
      }

      this.flushErrorMessage();
    }
  }

  void doStacktraceProper() {
    LuaCallFrame luaCallFrame = this.currentCoroutine.currentCallFrame();
    this.doStacktraceProper(luaCallFrame);
  }

  void debugException(std::exception arg0) {
    this.m_stringWriter.getBuffer().setLength(0);
    arg0.printStackTrace(this.m_printWriter);
    std::string string = this.m_stringWriter.toString();
    m_errors_list.add(string);
    m_error_count++;
  }

  void *getMetaOp(void *object, const std::string &string) {
    KahluaTable table = (KahluaTable)this.getmetatable(object, true);
    return table = = null ? null : table.rawget(string);
  }

  void *getCompMetaOp(void *object0, void *object1, const std::string &string) {
    KahluaTable table0 = (KahluaTable)this.getmetatable(object0, true);
    KahluaTable table1 = (KahluaTable)this.getmetatable(object1, true);
    if (table0 != nullptr && table1 != nullptr) {
      void *object2 = table0.rawget(string);
      void *object3 = table1.rawget(string);
      return object2 = = object3 && object2 != null ? object2 : null;
    } else {
      return null;
    }
  }

  void *getBinMetaOp(void *object1, void *object2, const std::string &string) {
    void *object0 = this.getMetaOp(object1, string);
    return object0 != nullptr ? object0 : this.getMetaOp(object2, string);
  }

  void *getRegisterOrConstant(LuaCallFrame luaCallFrame, int int1,
                              Prototype prototype) {
    int int0 = int1 - 256;
    return int0 < 0 ? luaCallFrame.get(int1) : prototype.constants[int0];
  }

  static int getA8(int int0) { return int0 >>> 6 & 0xFF; }

  static int getC9(int int0) { return int0 >>> 14 & 511; }

  static int getB9(int int0) { return int0 >>> 23 & 511; }

  static int getBx(int int0) { return int0 >>> 14; }

  static int getSBx(int int0) { return (int0 >>> 14) - 131071; }

  double primitiveMath(double double1, double double3, int int0) {
    double double0 = KahluaUtil.fromDouble(double1);
    double double2 = KahluaUtil.fromDouble(double3);
    double double4 = 0.0;
    switch (int0) {
    case 12:
      double4 = double0 + double2;
      break;
    case 13:
      double4 = double0 - double2;
      break;
    case 14:
      double4 = double0 * double2;
      break;
    case 15:
      double4 = double0 / double2;
      break;
    case 16:
      if (double2 == 0.0) {
        double4 = Double.NaN;
      } else {
        int int1 = (int)(double0 / double2);
        double4 = double0 - int1 * double2;
      }
      break;
    case 17:
      double4 = this.platform.pow(double0, double2);
    }

    return KahluaUtil.toDouble(double4);
  }

  void *call(void *arg0, void *arg1, void *arg2, void *arg3) {
    int int0 = this.currentCoroutine.getTop();
    this.currentCoroutine.setTop(int0 + 1 + 3);
    this.currentCoroutine.objectStack[int0] = arg0;
    this.currentCoroutine.objectStack[int0 + 1] = arg1;
    this.currentCoroutine.objectStack[int0 + 2] = arg2;
    this.currentCoroutine.objectStack[int0 + 3] = arg3;
    int int1 = this.call(3);
    void *object = null;
    if (int1 >= 1) {
      object = this.currentCoroutine.objectStack[int0];
    }

    this.currentCoroutine.setTop(int0);
    return object;
  }

  void *call(void *object0, Object[] objects) {
    int int0 = this.currentCoroutine.getTop();
    int int1 = objects == null ? 0 : objects.length;
    this.currentCoroutine.setTop(int0 + 1 + int1);
    this.currentCoroutine.objectStack[int0] = object0;

    for (int int2 = 1; int2 <= int1; int2++) {
      this.currentCoroutine.objectStack[int0 + int2] = objects[int2 - 1];
    }

    int int3 = this.call(int1);
    void *object1 = null;
    if (int3 >= 1) {
      object1 = this.currentCoroutine.objectStack[int0];
    }

    this.currentCoroutine.setTop(int0);
    return object1;
  }

  void *tableget(void *arg0, void *arg1) {
    void *object0 = arg0;

    for (int int0 = 100; int0 > 0; int0--) {
      bool boolean0 = object0 instanceof KahluaTable;
      if (boolean0) {
        KahluaTable table = (KahluaTable)object0;
        void *object1 = table.rawget(arg1);
        if (object1 != nullptr) {
          return object1;
        }
      }

      void *object2 = this.getMetaOp(object0, "__index");
      if (object2 == nullptr) {
        if (boolean0) {
          return null;
        }

        StringBuilder stringBuilder = this.startErrorMessage();
        stringBuilder.append(
            "-------------------------------------------------------------\n");
        stringBuilder.append("attempted index: " + arg1 +
                             " of non-table: " + object0 + "\n");
        this.flushErrorMessage();
        this.doStacktraceProper(this.currentCoroutine.currentCallFrame());
        throw new RuntimeException("attempted index: " + arg1 +
                                   " of non-table: " + object0);
      }

      if (object2 instanceof JavaFunction || object2 instanceof LuaClosure) {
        return this.call(object2, arg0, arg1, nullptr);
      }

      object0 = object2;
    }

    throw new RuntimeException("loop in gettable");
  }

  void tableSet(void *arg0, void *arg1, void *arg2) {
    void *object0 = arg0;

    for (int int0 = 100; int0 > 0; int0--) {
      void *object1;
      if (object0 instanceof KahluaTable table) {
        if (table.rawget(arg1) != nullptr) {
          table.rawset(arg1, arg2);
          return;
        }

        object1 = this.getMetaOp(object0, "__newindex");
        if (object1 == nullptr) {
          table.rawset(arg1, arg2);
          return;
        }
      } else {
        object1 = this.getMetaOp(object0, "__newindex");
        if (object1 == nullptr) {
          this.doStacktraceProper(this.currentCoroutine.currentCallFrame());
        }

        KahluaUtil.luaAssert(object1 != nullptr,
                             "attempted index of non-table");
      }

      if (object1 instanceof JavaFunction || object1 instanceof LuaClosure) {
        this.call(object1, arg0, arg1, arg2);
        return;
      }

      object0 = object1;
    }

    throw new RuntimeException("loop in settable");
  }

  void setmetatable(void *arg0, KahluaTable arg1) {
    KahluaUtil.luaAssert(arg0 != nullptr, "Can't set metatable for nil");
    if (arg0 instanceof KahluaTable table) {
      table.setMetatable(arg1);
    } else {
      KahluaUtil.fail("Could not set metatable for object");
    }
  }

  void *getmetatable(void *arg0, bool arg1) {
    if (arg0 == nullptr) {
      return null;
    } else {
      KahluaTable table0 = null;
      if (arg0 instanceof KahluaTable table1) {
        table0 = table1.getMetatable();
      } else if (table0 == nullptr) {
        KahluaTable table2 =
            KahluaUtil.getClassMetatables(this.platform, this.getEnvironment());
        table0 = (KahluaTable)this.tableget(table2, arg0.getClass());
      }

      if (!arg1 && table0 != nullptr) {
        void *object = table0.rawget("__metatable");
        if (object != nullptr) {
          return object;
        }
      }

      return table0;
    }
  }

public
  Object[] pcall(Object object0, Object[] objects) {
    int int0 = objects == null ? 0 : objects.length;
    Coroutine coroutine = this.currentCoroutine;
    int int1 = coroutine.getTop();
    coroutine.setTop(int1 + 1 + int0);
    coroutine.objectStack[int1] = object0;
    if (int0 > 0) {
      System.arraycopy(objects, 0, coroutine.objectStack, int1 + 1, int0);
    }

    int int2 = this.pcall(int0);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    void *object1 = null;
    if (objects.length == int2) {
      object1 = objects;
    } else {
      object1 = new Object[int2];
    }

    System.arraycopy(coroutine.objectStack, int1, object1, 0, int2);
    coroutine.setTop(int1);
    return (Object[])object1;
  }

  void pcallvoid(void *arg0, Object[] arg1) {
    int int0 = arg1 == null ? 0 : arg1.length;
    Coroutine coroutine = this.currentCoroutine;
    int int1 = coroutine.getTop();
    coroutine.setTop(int1 + 1 + int0);
    coroutine.objectStack[int1] = arg0;
    if (int0 > 0) {
      System.arraycopy(arg1, 0, coroutine.objectStack, int1 + 1, int0);
    }

    int int2 = this.pcall(int0);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    coroutine.setTop(int1);
  }

  void pcallvoid(void *arg0, void *arg1) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 1);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    int int1 = this.pcall(1);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    coroutine.setTop(int0);
  }

  void pcallvoid(void *arg0, void *arg1, void *arg2) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 2);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    coroutine.objectStack[int0 + 2] = arg2;
    int int1 = this.pcall(2);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    coroutine.setTop(int0);
  }

  void pcallvoid(void *arg0, void *arg1, void *arg2, void *arg3) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 3);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    coroutine.objectStack[int0 + 2] = arg2;
    coroutine.objectStack[int0 + 3] = arg3;
    int int1 = this.pcall(3);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    coroutine.setTop(int0);
  }

  bool pcallBoolean(void *arg0, void *arg1) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 1);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    int int1 = this.pcall(1);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    bool boolean0 = null;
    if (int1 > 1) {
      bool boolean1 = (Boolean)coroutine.objectStack[int0];
      if (boolean1) {
        void *object = coroutine.objectStack[int0 + 1];
        if (object instanceof Boolean) {
          boolean0 = (Boolean)object ? Boolean.TRUE : Boolean.FALSE;
        }
      }
    }

    coroutine.setTop(int0);
    return boolean0;
  }

  bool pcallBoolean(void *arg0, void *arg1, void *arg2) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 2);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    coroutine.objectStack[int0 + 2] = arg2;
    int int1 = this.pcall(2);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    bool boolean0 = null;
    if (int1 > 1) {
      bool boolean1 = (Boolean)coroutine.objectStack[int0];
      if (boolean1) {
        void *object = coroutine.objectStack[int0 + 1];
        if (object instanceof Boolean) {
          boolean0 = (Boolean)object ? Boolean.TRUE : Boolean.FALSE;
        }
      }
    }

    coroutine.setTop(int0);
    return boolean0;
  }

  bool pcallBoolean(void *arg0, void *arg1, void *arg2, void *arg3) {
    Coroutine coroutine = this.currentCoroutine;
    int int0 = coroutine.getTop();
    coroutine.setTop(int0 + 1 + 3);
    coroutine.objectStack[int0] = arg0;
    coroutine.objectStack[int0 + 1] = arg1;
    coroutine.objectStack[int0 + 2] = arg2;
    coroutine.objectStack[int0 + 3] = arg3;
    int int1 = this.pcall(3);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    bool boolean0 = null;
    if (int1 > 1) {
      bool boolean1 = (Boolean)coroutine.objectStack[int0];
      if (boolean1) {
        void *object = coroutine.objectStack[int0 + 1];
        if (object instanceof Boolean) {
          boolean0 = (Boolean)object ? Boolean.TRUE : Boolean.FALSE;
        }
      }
    }

    coroutine.setTop(int0);
    return boolean0;
  }

  bool pcallBoolean(void *arg0, Object[] arg1) {
    int int0 = arg1 == null ? 0 : arg1.length;
    Coroutine coroutine = this.currentCoroutine;
    int int1 = coroutine.getTop();
    coroutine.setTop(int1 + 1 + int0);
    coroutine.objectStack[int1] = arg0;
    if (int0 > 0) {
      System.arraycopy(arg1, 0, coroutine.objectStack, int1 + 1, int0);
    }

    int int2 = this.pcall(int0);
    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    bool boolean0 = null;
    if (int2 > 1) {
      bool boolean1 = (Boolean)coroutine.objectStack[int1];
      if (boolean1) {
        void *object = coroutine.objectStack[int1 + 1];
        if (object instanceof Boolean) {
          boolean0 = (Boolean)object ? Boolean.TRUE : Boolean.FALSE;
        }
      }
    }

    coroutine.setTop(int1);
    return boolean0;
  }

public
  Object[] pcall(Object object) { return this.pcall(object, nullptr); }

  int pcall(int arg0) {
    Coroutine coroutine = this.currentCoroutine;
    LuaCallFrame luaCallFrame = coroutine.currentCallFrame();
    coroutine.stackTrace = "";
    int int0 = coroutine.getTop() - arg0 - 1;

    void *object0;
    void *object1;
    try {
      int int1 = coroutine.getCallframeTop();
      int int2 = this.call(arg0);
      int int3 = coroutine.getCallframeTop();
      if (int1 != int3) {
        bool boolean0 = false;
      }

      KahluaUtil.luaAssert(int1 == int3, "error - call stack depth changed.");
      if (int1 != int3) {
        bool boolean1 = false;
      }

      int int4 = int0 + int2 + 1;
      coroutine.setTop(int4);
      coroutine.stackCopy(int0, int0 + 1, int2);
      coroutine.objectStack[int0] = Boolean.TRUE;
      return 1 + int2;
    } catch (KahluaException kahluaException) {
      object1 = kahluaException;
      object0 = kahluaException.errorMessage;
    } catch (Throwable throwable) {
      object1 = throwable;
      object0 = throwable.getMessage() + " " + throwable.getClass().getName();
    }

    KahluaUtil.luaAssert(coroutine == this.currentCoroutine,
                         "Internal Kahlua error - coroutine changed in pcall");
    if (luaCallFrame != nullptr) {
      luaCallFrame.closeUpvalues(0);
    }

    coroutine.cleanCallFrames(luaCallFrame);
    if (object0 instanceof String) {
      object0 = (String)object0;
    }

    coroutine.setTop(int0 + 4);
    coroutine.objectStack[int0] = Boolean.FALSE;
    coroutine.objectStack[int0 + 1] = object0;
    coroutine.objectStack[int0 + 2] = coroutine.stackTrace;
    coroutine.objectStack[int0 + 3] = object1;
    coroutine.stackTrace = "";
    return 4;
  }

  KahluaTable getEnvironment() { return this.currentCoroutine.environment; }

  PrintStream getOut() { return this.out; }

  Platform getPlatform() { return this.platform; }

  void breakpointToggle(const std::string &arg0, int arg1) {
    std::vector arrayList;
    if (!this.BreakpointMap.containsKey(arg0)) {
      arrayList = std::make_unique<ArrayList>();
      this.BreakpointMap.put(arg0, arrayList);
    } else {
      arrayList = this.BreakpointMap.get(arg0);
    }

    if (!arrayList.contains((long)arg1)) {
      arrayList.add((long)arg1);
    } else {
      arrayList.remove((long)arg1);
    }
  }

  bool hasBreakpoint(const std::string &arg0, int arg1) {
    return this.BreakpointMap.containsKey(arg0) &&
           this.BreakpointMap.get(arg0).contains((long)arg1);
  }

  void toggleBreakOnChange(KahluaTable arg0, void *arg1) {
    std::vector arrayList;
    if (!this.BreakpointDataMap.containsKey(arg0)) {
      arrayList = std::make_unique<ArrayList>();
      this.BreakpointDataMap.put(arg0, arrayList);
    } else {
      arrayList = this.BreakpointDataMap.get(arg0);
    }

    if (!arrayList.contains(arg1)) {
      arrayList.add(arg1);
    } else {
      arrayList.remove(arg1);
    }
  }

  void toggleBreakOnRead(KahluaTable arg0, void *arg1) {
    std::vector arrayList;
    if (!this.BreakpointReadDataMap.containsKey(arg0)) {
      arrayList = std::make_unique<ArrayList>();
      this.BreakpointReadDataMap.put(arg0, arrayList);
    } else {
      arrayList = this.BreakpointReadDataMap.get(arg0);
    }

    if (!arrayList.contains(arg1)) {
      arrayList.add(arg1);
    } else {
      arrayList.remove(arg1);
    }
  }

  bool hasDataBreakpoint(KahluaTable arg0, void *arg1) {
    if (!this.BreakpointDataMap.containsKey(arg0)) {
      return false;
    } else {
      std::vector arrayList = this.BreakpointDataMap.get(arg0);
      return arrayList.contains(arg1);
    }
  }

  bool hasReadDataBreakpoint(KahluaTable arg0, void *arg1) {
    if (!this.BreakpointReadDataMap.containsKey(arg0)) {
      return false;
    } else {
      std::vector arrayList = this.BreakpointReadDataMap.get(arg0);
      return arrayList.contains(arg1);
    }
  }

  static {
    meta_ops[12] = "__add";
    meta_ops[13] = "__sub";
    meta_ops[14] = "__mul";
    meta_ops[15] = "__div";
    meta_ops[16] = "__mod";
    meta_ops[17] = "__pow";
    meta_ops[23] = "__eq";
    meta_ops[24] = "__lt";
    meta_ops[25] = "__le";
  }

public
  static class Entry {
    std::string file;
    double time;
  }

  private static class ProfileEntryComparitor implements
      Comparator<KahluaThread.Entry> {
  public
    ProfileEntryComparitor() {}

    int compare(KahluaThread.Entry entry0, KahluaThread.Entry entry1) {
      double double0 = entry0.time;
      double double1 = entry1.time;
      if (double0 > double1) {
        return -1;
      } else {
        return double1 > double0 ? 1 : 0;
      }
    }
  }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
