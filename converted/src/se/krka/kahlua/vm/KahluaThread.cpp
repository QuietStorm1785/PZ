#include "se/krka/kahlua/vm/KahluaThread.h"

namespace se {
namespace krka {
namespace kahlua {
namespace vm {

Coroutine KahluaThread::getCurrentCoroutine() {
 // TODO: Implement getCurrentCoroutine
 return nullptr;
}

public KahluaThread::KahluaThread(Platform arg0, KahluaTable arg1) {
 // TODO: Implement KahluaThread
 return nullptr;
}

public KahluaThread::KahluaThread(PrintStream arg0, Platform arg1, KahluaTable arg2) {
 // TODO: Implement KahluaThread
 return nullptr;
}

int KahluaThread::call(int arg0) {
 // TODO: Implement call
 return 0;
}

int KahluaThread::callJava(JavaFunction javaFunction, int int0, int int1, int int2) {
 // TODO: Implement callJava
 return 0;
}

void* KahluaThread::prepareMetatableCall(void* object) {
 // TODO: Implement prepareMetatableCall
 return nullptr;
}

bool KahluaThread::isCurrent(const std::string& arg0, int arg1) {
 // TODO: Implement isCurrent
 return false;
}

void KahluaThread::luaMainloop() {
 // TODO: Implement luaMainloop
}

void KahluaThread::DoProfileTiming(const std::string& string, long long1, long long0) {
 // TODO: Implement DoProfileTiming
}

StringBuilder KahluaThread::startErrorMessage() {
 // TODO: Implement startErrorMessage
 return nullptr;
}

void KahluaThread::flushErrorMessage() {
 // TODO: Implement flushErrorMessage
}

void KahluaThread::doStacktraceProper(LuaCallFrame arg0) {
 // TODO: Implement doStacktraceProper
}

void KahluaThread::doStacktraceProper() {
 // TODO: Implement doStacktraceProper
}

void KahluaThread::debugException(std::exception arg0) {
 // TODO: Implement debugException
}

void* KahluaThread::getMetaOp(void* object, const std::string& string) {
 // TODO: Implement getMetaOp
 return nullptr;
}

void* KahluaThread::getCompMetaOp(void* object0, void* object1, const std::string& string) {
 // TODO: Implement getCompMetaOp
 return nullptr;
}

void* KahluaThread::getBinMetaOp(void* object1, void* object2, const std::string& string) {
 // TODO: Implement getBinMetaOp
 return nullptr;
}

void* KahluaThread::getRegisterOrConstant(LuaCallFrame luaCallFrame, int int1, Prototype prototype) {
 // TODO: Implement getRegisterOrConstant
 return nullptr;
}

int KahluaThread::getA8(int int0) {
 // TODO: Implement getA8
 return 0;
}

int KahluaThread::getC9(int int0) {
 // TODO: Implement getC9
 return 0;
}

int KahluaThread::getB9(int int0) {
 // TODO: Implement getB9
 return 0;
}

int KahluaThread::getBx(int int0) {
 // TODO: Implement getBx
 return 0;
}

int KahluaThread::getSBx(int int0) {
 // TODO: Implement getSBx
 return 0;
}

double KahluaThread::primitiveMath(double double1, double double3, int int0) {
 // TODO: Implement primitiveMath
 return 0;
}

void* KahluaThread::call(void* arg0, void* arg1, void* arg2, void* arg3) {
 // TODO: Implement call
 return nullptr;
}

void* KahluaThread::call(void* object0, Object[] objects) {
 // TODO: Implement call
 return nullptr;
}

void* KahluaThread::tableget(void* arg0, void* arg1) {
 // TODO: Implement tableget
 return nullptr;
}

void KahluaThread::tableSet(void* arg0, void* arg1, void* arg2) {
 // TODO: Implement tableSet
}

void KahluaThread::setmetatable(void* arg0, KahluaTable arg1) {
 // TODO: Implement setmetatable
}

void* KahluaThread::getmetatable(void* arg0, bool arg1) {
 // TODO: Implement getmetatable
 return nullptr;
}

void KahluaThread::pcallvoid(void* arg0, Object[] arg1) {
 // TODO: Implement pcallvoid
}

void KahluaThread::pcallvoid(void* arg0, void* arg1) {
 // TODO: Implement pcallvoid
}

void KahluaThread::pcallvoid(void* arg0, void* arg1, void* arg2) {
 // TODO: Implement pcallvoid
}

void KahluaThread::pcallvoid(void* arg0, void* arg1, void* arg2, void* arg3) {
 // TODO: Implement pcallvoid
}

bool KahluaThread::pcallBoolean(void* arg0, void* arg1) {
 // TODO: Implement pcallBoolean
 return false;
}

bool KahluaThread::pcallBoolean(void* arg0, void* arg1, void* arg2) {
 // TODO: Implement pcallBoolean
 return false;
}

bool KahluaThread::pcallBoolean(void* arg0, void* arg1, void* arg2, void* arg3) {
 // TODO: Implement pcallBoolean
 return false;
}

bool KahluaThread::pcallBoolean(void* arg0, Object[] arg1) {
 // TODO: Implement pcallBoolean
 return false;
}

int KahluaThread::pcall(int arg0) {
 // TODO: Implement pcall
 return 0;
}

KahluaTable KahluaThread::getEnvironment() {
 // TODO: Implement getEnvironment
 return nullptr;
}

PrintStream KahluaThread::getOut() {
 // TODO: Implement getOut
 return nullptr;
}

Platform KahluaThread::getPlatform() {
 // TODO: Implement getPlatform
 return nullptr;
}

void KahluaThread::breakpointToggle(const std::string& arg0, int arg1) {
 // TODO: Implement breakpointToggle
}

bool KahluaThread::hasBreakpoint(const std::string& arg0, int arg1) {
 // TODO: Implement hasBreakpoint
 return false;
}

void KahluaThread::toggleBreakOnChange(KahluaTable arg0, void* arg1) {
 // TODO: Implement toggleBreakOnChange
}

void KahluaThread::toggleBreakOnRead(KahluaTable arg0, void* arg1) {
 // TODO: Implement toggleBreakOnRead
}

bool KahluaThread::hasDataBreakpoint(KahluaTable arg0, void* arg1) {
 // TODO: Implement hasDataBreakpoint
 return false;
}

bool KahluaThread::hasReadDataBreakpoint(KahluaTable arg0, void* arg1) {
 // TODO: Implement hasReadDataBreakpoint
 return false;
}

public KahluaThread::ProfileEntryComparitor() {
 // TODO: Implement ProfileEntryComparitor
 return nullptr;
}

int KahluaThread::compare(KahluaThread.Entry entry0, KahluaThread.Entry entry1) {
 // TODO: Implement compare
 return 0;
}

} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
