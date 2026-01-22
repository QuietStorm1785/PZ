#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemContainer/CategoryPredicate.h"
#include "zombie/inventory/ItemContainer/EvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/EvalPredicate.h"
#include "zombie/inventory/ItemContainer/TagEvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/TagEvalPredicate.h"
#include "zombie/inventory/ItemContainer/TagPredicate.h"
#include "zombie/inventory/ItemContainer/TypeEvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/TypeEvalPredicate.h"
#include "zombie/inventory/ItemContainer/TypePredicate.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace inventory {


class ItemContainer {
public:
   const ObjectPool<CategoryPredicate> category = std::make_shared<ObjectPool>(CategoryPredicate::new);
   const ObjectPool<EvalPredicate> eval = std::make_shared<ObjectPool>(EvalPredicate::new);
   const ObjectPool<EvalArgPredicate> evalArg = std::make_shared<ObjectPool>(EvalArgPredicate::new);
   const ObjectPool<TagPredicate> tag = std::make_shared<ObjectPool>(TagPredicate::new);
   const ObjectPool<TagEvalPredicate> tagEval = std::make_shared<ObjectPool>(TagEvalPredicate::new);
   const ObjectPool<TagEvalArgPredicate> tagEvalArg = std::make_shared<ObjectPool>(TagEvalArgPredicate::new);
   const ObjectPool<TypePredicate> type = std::make_shared<ObjectPool>(TypePredicate::new);
   const ObjectPool<TypeEvalPredicate> typeEval = std::make_shared<ObjectPool>(TypeEvalPredicate::new);
   const ObjectPool<TypeEvalArgPredicate> typeEvalArg = std::make_shared<ObjectPool>(TypeEvalArgPredicate::new);

   private ItemContainer$Predicates() {
   }
}
} // namespace inventory
} // namespace zombie
