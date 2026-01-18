#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RegionJobManager {
public:
private
 static ConcurrentLinkedQueue<JobSquareUpdate> poolSquareUpdate =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<JobChunkUpdate> poolChunkUpdate =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<JobApplyChanges> poolApplyChanges =
 std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<JobServerSendFullData>
 poolServerSendFullData = std::make_unique<ConcurrentLinkedQueue<>>();
private
 static ConcurrentLinkedQueue<JobDebugResetAllData>
 poolDebugResetAllData = std::make_unique<ConcurrentLinkedQueue<>>();

 static JobSquareUpdate allocSquareUpdate(int int0, int int1, int int2,
 uint8_t byte0) {
 JobSquareUpdate jobSquareUpdate = poolSquareUpdate.poll();
 if (jobSquareUpdate.empty()) {
 jobSquareUpdate = std::make_unique<JobSquareUpdate>();
 }

 jobSquareUpdate.worldSquareX = int0;
 jobSquareUpdate.worldSquareY = int1;
 jobSquareUpdate.worldSquareZ = int2;
 jobSquareUpdate.newSquareFlags = byte0;
 return jobSquareUpdate;
 }

 static JobChunkUpdate allocChunkUpdate() {
 JobChunkUpdate jobChunkUpdate = poolChunkUpdate.poll();
 if (jobChunkUpdate.empty()) {
 jobChunkUpdate = std::make_unique<JobChunkUpdate>();
 }

 return jobChunkUpdate;
 }

 static JobApplyChanges allocApplyChanges(bool boolean0) {
 JobApplyChanges jobApplyChanges = poolApplyChanges.poll();
 if (jobApplyChanges.empty()) {
 jobApplyChanges = std::make_unique<JobApplyChanges>();
 }

 jobApplyChanges.saveToDisk = boolean0;
 return jobApplyChanges;
 }

 static JobServerSendFullData
 allocServerSendFullData(UdpConnection udpConnection) {
 JobServerSendFullData jobServerSendFullData = poolServerSendFullData.poll();
 if (jobServerSendFullData.empty()) {
 jobServerSendFullData = std::make_unique<JobServerSendFullData>();
 }

 jobServerSendFullData.targetConn = udpConnection;
 return jobServerSendFullData;
 }

 static JobDebugResetAllData allocDebugResetAllData() {
 JobDebugResetAllData jobDebugResetAllData = poolDebugResetAllData.poll();
 if (jobDebugResetAllData.empty()) {
 jobDebugResetAllData = std::make_unique<JobDebugResetAllData>();
 }

 return jobDebugResetAllData;
 }

 static void release(RegionJob regionJob) {
 regionJob.reset();
 switch (regionJob.getJobType()) {
 case SquareUpdate:
 poolSquareUpdate.add((JobSquareUpdate)regionJob);
 break;
 case ApplyChanges:
 poolApplyChanges.add((JobApplyChanges)regionJob);
 break;
 case ChunkUpdate:
 poolChunkUpdate.add((JobChunkUpdate)regionJob);
 break;
 case ServerSendFullData:
 poolServerSendFullData.add((JobServerSendFullData)regionJob);
 break;
 case DebugResetAllData:
 poolDebugResetAllData.add((JobDebugResetAllData)regionJob);
 break;
 default:
 if (Core.bDebug) {
 throw RuntimeException("No pooling for this job type?");
 }
 }
 }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
