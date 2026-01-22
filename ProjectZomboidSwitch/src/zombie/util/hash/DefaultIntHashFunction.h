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


class DefaultIntHashFunction {
public:
    static const long serialVersionUID = 1L;
    static const IntHashFunction INSTANCE = std::make_shared<DefaultIntHashFunction>();

    protected DefaultIntHashFunction() {
   }

    int hash(int var1) {
    return var1;
   }
}
} // namespace hash
} // namespace util
} // namespace zombie
