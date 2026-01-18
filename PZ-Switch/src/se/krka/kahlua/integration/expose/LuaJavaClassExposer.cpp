#include "se/krka/kahlua/integration/expose/LuaJavaClassExposer.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {

public
LuaJavaClassExposer::LuaJavaClassExposer(
 KahluaConverterManager kahluaConverterManager, Platform platformx,
 KahluaTable table) {
 // TODO: Implement LuaJavaClassExposer
 return nullptr;
}

public
LuaJavaClassExposer::LuaJavaClassExposer(
 KahluaConverterManager kahluaConverterManager, Platform platformx,
 KahluaTable table0, KahluaTable table1) {
 // TODO: Implement LuaJavaClassExposer
 return nullptr;
}

int LuaJavaClassExposer::call(LuaCallFrame luaCallFrame, int var2) {
 // TODO: Implement call
 return 0;
}

KahluaTable LuaJavaClassExposer::getMetaTable(Class<?> clazz) {
 // TODO: Implement getMetaTable
 return nullptr;
}

KahluaTable LuaJavaClassExposer::getIndexTable(KahluaTable table) {
 // TODO: Implement getIndexTable
 return nullptr;
}

void LuaJavaClassExposer::exposeGlobalObjectFunction(KahluaTable table,
 void *object,
 Method method) {
 // TODO: Implement exposeGlobalObjectFunction
}

void LuaJavaClassExposer::exposeGlobalObjectFunction(
 KahluaTable table, void *object, Method method, const std::string &string) {
 // TODO: Implement exposeGlobalObjectFunction
}

void LuaJavaClassExposer::exposeGlobalClassFunction(KahluaTable table, Class<?> clazz, Constructor<?> constructor, const std::string& string) {
 // TODO: Implement exposeGlobalClassFunction
}

LuaJavaInvoker LuaJavaClassExposer::getMethodInvoker(Class<?> clazz, Method method, const std::string& string, void* object, bool boolean0) {
 // TODO: Implement getMethodInvoker
 return nullptr;
}

LuaJavaInvoker LuaJavaClassExposer::getConstructorInvoker(Class<?> clazz, Constructor<?> constructor, const std::string& string) {
 // TODO: Implement getConstructorInvoker
 return nullptr;
}

LuaJavaInvoker LuaJavaClassExposer::getMethodInvoker(Class<?> clazz, Method method, const std::string& string) {
 // TODO: Implement getMethodInvoker
 return nullptr;
}

LuaJavaInvoker LuaJavaClassExposer::getGlobalInvoker(Class<?> clazz, Method method, const std::string& string) {
 // TODO: Implement getGlobalInvoker
 return nullptr;
}

void LuaJavaClassExposer::exposeGlobalClassFunction(KahluaTable table, Class<?> clazz, Method method, const std::string& string) {
 // TODO: Implement exposeGlobalClassFunction
}

void LuaJavaClassExposer::exposeMethod(Class<?> clazz, Method method, KahluaTable table) {
 // TODO: Implement exposeMethod
}

void LuaJavaClassExposer::exposeMethod(Class<?> clazz, Method method, const std::string& string, KahluaTable table0) {
 // TODO: Implement exposeMethod
}

void LuaJavaClassExposer::addInvoker(KahluaTable table,
 const std::string &string,
 LuaJavaInvoker luaJavaInvoker) {
 // TODO: Implement addInvoker
}

bool LuaJavaClassExposer::shouldExpose(Class<?> clazz0) {
 // TODO: Implement shouldExpose
 return false;
}

void LuaJavaClassExposer::setupMetaTables(Class<?> clazz1, KahluaTable table0) {
 // TODO: Implement setupMetaTables
}

void LuaJavaClassExposer::addJavaEquals(KahluaTable table) {
 // TODO: Implement addJavaEquals
}

int LuaJavaClassExposer::call(LuaCallFrame luaCallFrame, int var2) {
 // TODO: Implement call
 return 0;
}

void LuaJavaClassExposer::exposeGlobalFunctions(void *object) {
 // TODO: Implement exposeGlobalFunctions
}

void LuaJavaClassExposer::exposeLikeJava(Class clazz) {
 // TODO: Implement exposeLikeJava
}

void LuaJavaClassExposer::exposeLikeJava(Class clazz, KahluaTable table) {
 // TODO: Implement exposeLikeJava
}

void LuaJavaClassExposer::exposeStatics(Class clazz, KahluaTable table1) {
 // TODO: Implement exposeStatics
}

void LuaJavaClassExposer::exposeMethods(Class clazz, KahluaTable table) {
 // TODO: Implement exposeMethods
}

KahluaTable LuaJavaClassExposer::createTableStructure(KahluaTable table,
 String[] strings) {
 // TODO: Implement createTableStructure
 return nullptr;
}

bool LuaJavaClassExposer::isExposed(Class<?> clazz) {
 // TODO: Implement isExposed
 return false;
}

ClassDebugInformation LuaJavaClassExposer::getDebugdata(Class<?> clazz) {
 // TODO: Implement getDebugdata
 return nullptr;
}

ClassDebugInformation LuaJavaClassExposer::getDebugdataA(Class<?> clazz) {
 // TODO: Implement getDebugdataA
 return nullptr;
}

void LuaJavaClassExposer::readDebugDataD(Class<?> clazz) {
 // TODO: Implement readDebugDataD
}

void LuaJavaClassExposer::readDebugData(Class<?> var1) {
 // TODO: Implement readDebugData
}

std::string LuaJavaClassExposer::getDefinition(void *object) {
 // TODO: Implement getDefinition
 return "";
}

void LuaJavaClassExposer::exposeLikeJavaRecursively(Type type) {
 // TODO: Implement exposeLikeJavaRecursively
}

void LuaJavaClassExposer::exposeLikeJavaRecursively(Type type,
 KahluaTable table) {
 // TODO: Implement exposeLikeJavaRecursively
}

void LuaJavaClassExposer::exposeLikeJava(KahluaTable table, Set<Type> set,
 Type type) {
 // TODO: Implement exposeLikeJava
}

void LuaJavaClassExposer::exposeList(KahluaTable table, Set<Type> set,
 Type[] types) {
 // TODO: Implement exposeList
}

void LuaJavaClassExposer::exposeLikeJavaByClass(KahluaTable table, Set<Type> set, Class<?> clazz) {
 // TODO: Implement exposeLikeJavaByClass
}

void LuaJavaClassExposer::destroy() {
 // TODO: Implement destroy
}

} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
