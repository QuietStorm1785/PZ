#pragma once
#include "se/krka/kahlua/integration/expose/ReturnValues.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
namespace caller {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Caller {
public:
  virtual ~Caller() = default;
  void call(void *var1, ReturnValues var2, Object[] var3);

  Class < ? > [] getParameterTypes();

  bool needsMultipleReturnValues();

  bool hasSelf();

  Class < ? > getVarargType();

  bool hasVararg();

  std::string getDescriptor();
}
} // namespace caller
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
