#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace luaj {
namespace kahluafork {
namespace compiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Token {
public:
 int token;
 double r;
 std::string ts;

 void set(Token token0) {
 this->token = token0.token;
 this->r = token0.r;
 this->ts = token0.ts;
 }
}
} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
