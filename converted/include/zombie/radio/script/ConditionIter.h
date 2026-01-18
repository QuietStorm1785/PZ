#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/CompareResult.h"

namespace zombie {
namespace radio {
namespace script {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ConditionIter {
public:
 virtual ~ConditionIter() = default;
 CompareResult Evaluate();

 OperatorType getNextOperator();

 void setNextOperator(OperatorType var1);
}
} // namespace script
} // namespace radio
} // namespace zombie
