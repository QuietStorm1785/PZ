
#include "zombie/iso/ChunkSaveWorker.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/core/Core.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <iostream>

namespace zombie {
namespace iso {

std::shared_ptr<ChunkSaveWorker> ChunkSaveWorker::instance = std::make_shared<ChunkSaveWorker>();

ChunkSaveWorker::ChunkSaveWorker() : bSaving(false) {}
ChunkSaveWorker::~ChunkSaveWorker() {}

void ChunkSaveWorker::Update(std::shared_ptr<IsoChunk> chunk) {
    if (GameServer::bServer) return;
    std::lock_guard<std::mutex> lock(queueMutex);
    std::shared_ptr<IsoChunk> found = nullptr;
    bSaving = !toSaveQueue.empty();
    if (bSaving) {
        if (chunk) {
            for (const auto& c : toSaveQueue) {
                if (c && c->wx == chunk->wx && c->wy == chunk->wy) {
                    found = c;
                    break;
                }
            }
        }
        if (!found && !toSaveQueue.empty()) {
            found = toSaveQueue.front();
            toSaveQueue.pop_front();
        } else if (found) {
            toSaveQueue.erase(std::remove(toSaveQueue.begin(), toSaveQueue.end(), found), toSaveQueue.end());
        }
        if (found) {
            try {
                found->Save(false);
            } catch (const std::exception& e) {
                std::cerr << "ChunkSaveWorker::Update exception: " << e.what() << std::endl;
            }
        }
    }
}

void ChunkSaveWorker::SaveNow(const std::vector<std::shared_ptr<IsoChunk>>& chunks) {
    std::lock_guard<std::mutex> lock(queueMutex);
    tempList.clear();
    while (!toSaveQueue.empty()) {
        auto c = toSaveQueue.front();
        toSaveQueue.pop_front();
        bool matched = false;
        for (const auto& chk : chunks) {
            if (c && chk && c->wx == chk->wx && c->wy == chk->wy) {
                try {
                    c->Save(false);
                } catch (const std::exception& e) {
                    std::cerr << "ChunkSaveWorker::SaveNow exception: " << e.what() << std::endl;
                }
                matched = true;
                break;
            }
        }
        if (!matched) tempList.push_back(c);
    }
    for (const auto& c : tempList) {
        toSaveQueue.push_back(c);
    }
    tempList.clear();
}

void ChunkSaveWorker::SaveNow() {
    DebugLog::log("EXITDEBUG: ChunkSaveWorker.SaveNow 1");
    std::lock_guard<std::mutex> lock(queueMutex);
    while (!toSaveQueue.empty()) {
        auto c = toSaveQueue.front();
        toSaveQueue.pop_front();
        try {
            DebugLog::log("EXITDEBUG: ChunkSaveWorker.SaveNow 2 (ch=" + std::to_string(c->wx) + ", " + std::to_string(c->wy) + ")");
            c->Save(false);
        } catch (const std::exception& e) {
            std::cerr << "ChunkSaveWorker::SaveNow exception: " << e.what() << std::endl;
        }
    }
    bSaving = false;
    DebugLog::log("EXITDEBUG: ChunkSaveWorker.SaveNow 3");
}

void ChunkSaveWorker::Add(std::shared_ptr<IsoChunk> chunk) {
    if (Core::getInstance()->isNoSave()) {
        for (const auto& v : chunk->vehicles) {
            VehiclesDB2::instance->updateVehicle(std::dynamic_pointer_cast<BaseVehicle>(v));
        }
    }
    std::lock_guard<std::mutex> lock(queueMutex);
    auto it = std::find(toSaveQueue.begin(), toSaveQueue.end(), chunk);
    if (it == toSaveQueue.end()) {
        toSaveQueue.push_back(chunk);
    }
}

} // namespace iso
} // namespace zombie
