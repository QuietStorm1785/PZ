#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {
namespace hash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DefaultIntHashFunction {
public:
 static const long serialVersionUID = 1L;
 static const IntHashFunction INSTANCE = new DefaultIntHashFunction();

 protected DefaultIntHashFunction() {
 }

 int hash(int int0) {
 return int0;
 }
}
} // namespace hash
} // namespace util
} // namespace zombie
