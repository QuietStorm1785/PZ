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

class InstructionPtr {
public:
  final int[] code;
  const int idx;

  InstructionPtr(int[] ints, int int0) {
    this.code = ints;
    this.idx = int0;
  }

  int get() { return this.code[this.idx]; }

  void set(int int0) { this.code[this.idx] = int0; }
}
} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
