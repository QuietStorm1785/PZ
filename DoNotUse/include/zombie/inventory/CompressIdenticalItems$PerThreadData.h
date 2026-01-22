#pragma once
#include <memory>
#include "zombie/core/ByteBuffer.h"
#include "zombie/inventory/CompressIdenticalItems$PerCallData.h"

namespace zombie {
namespace inventory {

class PerThreadData {
public:
    std::shared_ptr<PerCallData> saveVars;
    std::shared_ptr<ByteBuffer> itemCompareBuffer;

    PerThreadData() : itemCompareBuffer(ByteBuffer::allocate(1024)) {}

    std::shared_ptr<PerCallData> allocSaveVars() {
        if (saveVars == nullptr) {
            return std::make_shared<PerCallData>();
        } else {
            std::shared_ptr<PerCallData> result = saveVars;
            result->reset();
            saveVars = saveVars->next;
            return result;
        }
    }
};

} // namespace inventory
} // namespace zombie
