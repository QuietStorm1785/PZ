#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeMultiset/AvlNode.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


enum class TreeMultiset {
   SIZE,
   DISTINCT;

   private TreeMultiset$Aggregate() {
   }

   abstract int nodeAggregate(AvlNode<?> var1);

   abstract long treeAggregate(@Nullable AvlNode<?> var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
