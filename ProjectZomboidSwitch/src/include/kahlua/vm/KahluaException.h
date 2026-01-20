#pragma once
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

class KahluaException : public RuntimeException {
public:
 static const long serialVersionUID = 1L;
 void *errorMessage;

public
 KahluaException(void *object) { this->errorMessage = object; }

 std::string getMessage() {
 return this->errorMessage.empty() ? "nil" : this->errorMessage.toString();
 }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
