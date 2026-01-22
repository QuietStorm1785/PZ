#pragma once
#include "zombie/inventory/CompressIdenticalItems$PerThreadData.h"

namespace zombie {
namespace inventory {

class ThreadLocalInitializer {
public:
    static std::shared_ptr<PerThreadData> initialValue() {
        return std::make_shared<PerThreadData>();
    }
};

} // namespace inventory
} // namespace zombie
