#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemContainer/ConditionComparator.h"
#include "zombie/inventory/ItemContainer/EvalArgComparator.h"
#include "zombie/inventory/ItemContainer/EvalComparator.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace inventory {


class ItemContainer {
public:
   ObjectPool<ConditionComparator> condition = std::make_shared<ObjectPool>(ConditionComparator::new);
   ObjectPool<EvalComparator> eval = std::make_shared<ObjectPool>(EvalComparator::new);
   ObjectPool<EvalArgComparator> evalArg = std::make_shared<ObjectPool>(EvalArgComparator::new);

   private ItemContainer$Comparators() {
   }
}
} // namespace inventory
} // namespace zombie
