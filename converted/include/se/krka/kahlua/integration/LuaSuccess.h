#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class LuaSuccess : public LuaReturn {
public:
 LuaSuccess(Object[] objects) {
 super(objects);
 }

 bool isSuccess() {
 return true;
 }

 void* getErrorObject() {
 throw UnsupportedOperationException("Not valid when isSuccess is true");
 }

 std::string getErrorString() {
 throw UnsupportedOperationException("Not valid when isSuccess is true");
 }

 std::string getLuaStackTrace() {
 throw UnsupportedOperationException("Not valid when isSuccess is true");
 }

 std::runtime_error getJavaException() {
 throw UnsupportedOperationException("Not valid when isSuccess is true");
 }
}
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
