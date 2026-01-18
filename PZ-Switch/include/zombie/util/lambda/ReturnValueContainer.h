#pragma once
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace lambda {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReturnValueContainer {
public:
 T ReturnVal;
private
 static Pool<ReturnValueContainer<Object>> s_pool =
 new Pool<>(ReturnValueContainer::new);

 void onReleased() { this->ReturnVal = nullptr; }

public
 static<E> ReturnValueContainer<E> alloc() {
 return (ReturnValueContainer<E>)s_pool.alloc();
 }
}
} // namespace lambda
} // namespace util
} // namespace zombie
