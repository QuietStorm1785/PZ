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
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class KahluaTableIterator {
public:
 virtual ~KahluaTableIterator() = default;
 bool advance();

 void* getKey();

 void* getValue();
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
