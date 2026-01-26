
#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <mutex>
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclesDB2.h"

namespace zombie {
namespace iso {

class IsoChunk; // Forward declaration

class ChunkSaveWorker {
public:
    static std::shared_ptr<ChunkSaveWorker> instance;

    ChunkSaveWorker();
    ~ChunkSaveWorker();

    void Update(std::shared_ptr<IsoChunk> chunk);
    void SaveNow(const std::vector<std::shared_ptr<IsoChunk>>& chunks);
    void SaveNow();
    void Add(std::shared_ptr<IsoChunk> chunk);

    bool bSaving = false;

private:
    std::vector<std::shared_ptr<IsoChunk>> tempList;
    std::deque<std::shared_ptr<IsoChunk>> toSaveQueue;
    std::mutex queueMutex;
};

} // namespace iso
} // namespace zombie
