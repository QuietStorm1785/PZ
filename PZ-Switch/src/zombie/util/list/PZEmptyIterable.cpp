#include "zombie/util/list/PZEmptyIterable.h"

namespace zombie {
namespace util {
namespace list {

bool PZEmptyIterable::hasNext() {
 // TODO: Implement hasNext
 return false;
}

T PZEmptyIterable::next() {
 // TODO: Implement next
 return nullptr;
}

private
PZEmptyIterable::PZEmptyIterable() {
 // TODO: Implement PZEmptyIterable
 return nullptr;
}

} // namespace list
} // namespace util
} // namespace zombie
