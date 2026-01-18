#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/stdlib/BaseLib.h"
#include "se/krka/kahlua/stdlib/CoroutineLib.h"
#include "se/krka/kahlua/stdlib/OsLib.h"
#include "se/krka/kahlua/stdlib/RandomLib.h"
#include "se/krka/kahlua/stdlib/StringLib.h"
#include "se/krka/kahlua/stdlib/TableLib.h"
#include "se/krka/kahlua/test/UserdataArray.h"
#include "se/krka/kahlua/threading/BlockingKahluaThread.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace j2se {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class J2SEPlatform {
public:
 static J2SEPlatform INSTANCE = new J2SEPlatform();

 static J2SEPlatform getInstance() {
 return INSTANCE;
 }

 double pow(double arg0, double arg1) {
 return Math.pow(arg0, arg1);
 }

 KahluaTable newTable() {
 return new KahluaTableImpl(std::make_unique<LinkedHashMap<>>());
 }

 KahluaTable newEnvironment() {
 KahluaTable table = this->newTable();
 this->setupEnvironment(table);
 return table;
 }

 void setupEnvironment(KahluaTable arg0) {
 arg0.wipe();
 arg0.rawset("_G", arg0);
 arg0.rawset("_VERSION", "Kahlua kahlua.major.kahlua.minor.kahlua.fix for Lua lua.version (J2SE)");
 MathLib.register(this, arg0);
 BaseLib.register(arg0);
 RandomLib.register(this, arg0);
 UserdataArray.register(this, arg0);
 StringLib.register(this, arg0);
 CoroutineLib.register(this, arg0);
 OsLib.register(this, arg0);
 TableLib.register(this, arg0);
 LuaCompiler.register(arg0);
 KahluaThread kahluaThread = this->setupWorkerThread(arg0);
 KahluaUtil.setupLibrary(arg0, kahluaThread, "/stdlib");
 File file = new File("serialize.lua").getAbsoluteFile();

 try {
 try (FileInputStream fileInputStream = new FileInputStream(file) {
 LuaClosure luaClosure = LuaCompiler.loadis(fileInputStream, "serialize.lua", arg0);
 kahluaThread.call(luaClosure, nullptr, nullptr, nullptr);
 }
 } catch (IOException iOException) {
 throw RuntimeException(iOException);
 }
 }

 KahluaThread setupWorkerThread(KahluaTable table) {
 BlockingKahluaThread blockingKahluaThread = new BlockingKahluaThread(this, table);
 KahluaUtil.setWorkerThread(table, blockingKahluaThread);
 return blockingKahluaThread;
 }
}
} // namespace j2se
} // namespace kahlua
} // namespace krka
} // namespace se
