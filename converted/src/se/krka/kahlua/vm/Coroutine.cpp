#include "se/krka/kahlua/vm/Coroutine.h"

namespace se {
namespace krka {
namespace kahlua {
namespace vm {

public Coroutine::Coroutine() {
 // TODO: Implement Coroutine
 return nullptr;
}

Coroutine Coroutine::getParent() {
 // TODO: Implement getParent
 return nullptr;
}

public Coroutine::Coroutine(Platform arg0, KahluaTable arg1, KahluaThread arg2) {
 // TODO: Implement Coroutine
 return nullptr;
}

public Coroutine::Coroutine(Platform arg0, KahluaTable arg1) {
 // TODO: Implement Coroutine
 return nullptr;
}

LuaCallFrame Coroutine::pushNewCallFrame(LuaClosure arg0, JavaFunction arg1, int arg2, int arg3, int arg4, bool arg5, bool arg6) {
 // TODO: Implement pushNewCallFrame
 return nullptr;
}

void Coroutine::popCallFrame() {
 // TODO: Implement popCallFrame
}

void Coroutine::ensureCallFrameStackSize(int int0) {
 // TODO: Implement ensureCallFrameStackSize
}

void Coroutine::setCallFrameStackTop(int arg0) {
 // TODO: Implement setCallFrameStackTop
}

void Coroutine::callFrameStackClear(int int0, int int1) {
 // TODO: Implement callFrameStackClear
}

void Coroutine::ensureStacksize(int int0) {
 // TODO: Implement ensureStacksize
}

void Coroutine::setTop(int arg0) {
 // TODO: Implement setTop
}

void Coroutine::stackCopy(int arg0, int arg1, int arg2) {
 // TODO: Implement stackCopy
}

void Coroutine::stackClear(int arg0, int arg1) {
 // TODO: Implement stackClear
}

void Coroutine::closeUpvalues(int arg0) {
 // TODO: Implement closeUpvalues
}

UpValue Coroutine::findUpvalue(int arg0) {
 // TODO: Implement findUpvalue
 return nullptr;
}

void* Coroutine::getObjectFromStack(int arg0) {
 // TODO: Implement getObjectFromStack
 return nullptr;
}

int Coroutine::getObjectStackSize() {
 // TODO: Implement getObjectStackSize
 return 0;
}

LuaCallFrame Coroutine::getParentCallframe() {
 // TODO: Implement getParentCallframe
 return nullptr;
}

LuaCallFrame Coroutine::currentCallFrame() {
 // TODO: Implement currentCallFrame
 return nullptr;
}

int Coroutine::getTop() {
 // TODO: Implement getTop
 return 0;
}

LuaCallFrame Coroutine::getParent(int arg0) {
 // TODO: Implement getParent
 return nullptr;
}

LuaCallFrame Coroutine::getParentNoAssert(int arg0) {
 // TODO: Implement getParentNoAssert
 return nullptr;
}

std::string Coroutine::getCurrentStackTrace(int arg0, int arg1, int arg2) {
 // TODO: Implement getCurrentStackTrace
 return "";
}

void Coroutine::cleanCallFrames(LuaCallFrame arg0) {
 // TODO: Implement cleanCallFrames
}

void Coroutine::addStackTrace(LuaCallFrame arg0) {
 // TODO: Implement addStackTrace
}

std::string Coroutine::getStackTrace(LuaCallFrame luaCallFrame) {
 // TODO: Implement getStackTrace
 return "";
}

bool Coroutine::isDead() {
 // TODO: Implement isDead
 return false;
}

Platform Coroutine::getPlatform() {
 // TODO: Implement getPlatform
 return nullptr;
}

std::string Coroutine::getStatus() {
 // TODO: Implement getStatus
 return "";
}

bool Coroutine::atBottom() {
 // TODO: Implement atBottom
 return false;
}

int Coroutine::getCallframeTop() {
 // TODO: Implement getCallframeTop
 return 0;
}

LuaCallFrame Coroutine::getCallFrame(int arg0) {
 // TODO: Implement getCallFrame
 return nullptr;
}

void Coroutine::yieldHelper(LuaCallFrame arg0, LuaCallFrame arg1, int arg2) {
 // TODO: Implement yieldHelper
}

void Coroutine::resume(Coroutine arg0) {
 // TODO: Implement resume
}

KahluaThread Coroutine::getThread() {
 // TODO: Implement getThread
 return nullptr;
}

void Coroutine::destroy() {
 // TODO: Implement destroy
}

} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
