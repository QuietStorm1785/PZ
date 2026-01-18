#include "zombie/iso/areas/isoregion/jobs/RegionJobManager.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {

JobSquareUpdate RegionJobManager::allocSquareUpdate(int int0, int int1, int int2, uint8_t byte0) {
 // TODO: Implement allocSquareUpdate
 return nullptr;
}

JobChunkUpdate RegionJobManager::allocChunkUpdate() {
 // TODO: Implement allocChunkUpdate
 return nullptr;
}

JobApplyChanges RegionJobManager::allocApplyChanges(bool boolean0) {
 // TODO: Implement allocApplyChanges
 return nullptr;
}

JobServerSendFullData RegionJobManager::allocServerSendFullData(UdpConnection udpConnection) {
 // TODO: Implement allocServerSendFullData
 return nullptr;
}

JobDebugResetAllData RegionJobManager::allocDebugResetAllData() {
 // TODO: Implement allocDebugResetAllData
 return {};
}

void RegionJobManager::release(RegionJob regionJob) {
 // TODO: Implement release
}

} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
