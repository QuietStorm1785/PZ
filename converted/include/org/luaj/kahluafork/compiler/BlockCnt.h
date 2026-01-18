#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace luaj {
namespace kahluafork {
namespace compiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class BlockCnt {
public:
 BlockCnt previous;
 int breaklist;
 int nactvar;
 bool upval;
 bool isbreakable;
}
} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
