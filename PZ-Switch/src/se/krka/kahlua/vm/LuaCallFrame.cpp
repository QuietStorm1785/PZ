#include "se/krka/kahlua/vm/LuaCallFrame.h"

namespace se {
namespace krka {
namespace kahlua {
namespace vm {

public
LuaCallFrame::LuaCallFrame(Coroutine arg0) {
 // TODO: Implement LuaCallFrame
 return nullptr;
}

std::string LuaCallFrame::getFilename() {
 // TODO: Implement getFilename
 return "";
}

void LuaCallFrame::set(int arg0, void *arg1) {
 // TODO: Implement set
}

void *LuaCallFrame::get(int arg0) {
 // TODO: Implement get
 return nullptr;
}

int LuaCallFrame::push(void *arg0) {
 // TODO: Implement push
 return 0;
}

int LuaCallFrame::push(void *arg0, void *arg1) {
 // TODO: Implement push
 return 0;
}

int LuaCallFrame::pushNil() {
 // TODO: Implement pushNil
 return 0;
}

void LuaCallFrame::stackCopy(int arg0, int arg1, int arg2) {
 // TODO: Implement stackCopy
}

void LuaCallFrame::stackClear(int arg0, int arg1) {
 // TODO: Implement stackClear
}

void LuaCallFrame::clearFromIndex(int arg0) {
 // TODO: Implement clearFromIndex
}

void LuaCallFrame::setTop(int arg0) {
 // TODO: Implement setTop
}

void LuaCallFrame::closeUpvalues(int arg0) {
 // TODO: Implement closeUpvalues
}

UpValue LuaCallFrame::findUpvalue(int arg0) {
 // TODO: Implement findUpvalue
 return nullptr;
}

int LuaCallFrame::getTop() {
 // TODO: Implement getTop
 return 0;
}

void LuaCallFrame::init() {
 // TODO: Implement init
}

void LuaCallFrame::setPrototypeStacksize() {
 // TODO: Implement setPrototypeStacksize
}

void LuaCallFrame::pushVarargs(int arg0, int arg1) {
 // TODO: Implement pushVarargs
}

KahluaTable LuaCallFrame::getEnvironment() {
 // TODO: Implement getEnvironment
 return nullptr;
}

bool LuaCallFrame::isJava() {
 // TODO: Implement isJava
 return false;
}

bool LuaCallFrame::isLua() {
 // TODO: Implement isLua
 return false;
}

std::string LuaCallFrame::toString2() {
 // TODO: Implement toString2
 return "";
}

std::string LuaCallFrame::toString() {
 // TODO: Implement toString
 return "";
}

Platform LuaCallFrame::getPlatform() {
 // TODO: Implement getPlatform
 return nullptr;
}

void LuaCallFrame::setup(LuaClosure luaClosure, JavaFunction javaFunctionx,
 int int0, int int1, int int2, bool boolean0,
 bool boolean1) {
 // TODO: Implement setup
}

KahluaThread LuaCallFrame::getThread() {
 // TODO: Implement getThread
 return nullptr;
}

LuaClosure LuaCallFrame::getClosure() {
 // TODO: Implement getClosure
 return nullptr;
}

void LuaCallFrame::setLocalVarToStack(const std::string &arg0, int arg1) {
 // TODO: Implement setLocalVarToStack
}

std::string LuaCallFrame::getNameOfStack(int arg0) {
 // TODO: Implement getNameOfStack
 return "";
}

void LuaCallFrame::printoutLocalVars() {
 // TODO: Implement printoutLocalVars
}

} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
