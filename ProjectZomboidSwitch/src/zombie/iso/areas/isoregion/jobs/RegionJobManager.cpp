#include <cstdint>
#include "zombie\iso\areas\isoregion\jobs/RegionJobManager.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {

JobSquareUpdate RegionJobManager::allocSquareUpdate(int var0, int var1, int var2, uint8_t var3) {
    // TODO: Implement allocSquareUpdate
    return nullptr;
}

JobChunkUpdate RegionJobManager::allocChunkUpdate() {
    // TODO: Implement allocChunkUpdate
    return nullptr;
}

JobApplyChanges RegionJobManager::allocApplyChanges(bool var0) {
    // TODO: Implement allocApplyChanges
    return nullptr;
}

JobServerSendFullData RegionJobManager::allocServerSendFullData(UdpConnection var0) {
    // TODO: Implement allocServerSendFullData
    return nullptr;
}

JobDebugResetAllData RegionJobManager::allocDebugResetAllData() {
    // TODO: Implement allocDebugResetAllData
    return {};
}

void RegionJobManager::release(RegionJob var0) {
    // TODO: Implement release
}

} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
