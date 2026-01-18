#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaUtil.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaFail : public LuaReturn {
public:
 LuaFail(Object[] objects) {
 super(objects);
 }

 bool isSuccess() {
 return false;
 }

 void* getErrorObject() {
 return this->returnValues.length >= 2 ? this->returnValues[1] : nullptr;
 }

 std::string getErrorString() {
 return this->returnValues.length >= 2 && this->returnValues[1] != nullptr ? KahluaUtil.rawTostring(this->returnValues[1]) : "";
 }

 std::string getLuaStackTrace() {
 return this->returnValues.length >= 3 && this->returnValues[2] instanceof String ? (String)this->returnValues[2] : "";
 }

 std::runtime_error getJavaException() {
 return this->returnValues.length >= 4 && this->returnValues[3] instanceof RuntimeException ? (RuntimeException)this->returnValues[3] : nullptr;
 }

 int size() {
 return 0;
 }

 std::string toString() {
 return this->getErrorString() + "\n" + this->getLuaStackTrace();
 }
}
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
