#pragma once
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChunkSaveWorker {
public:
  static ChunkSaveWorker instance = new ChunkSaveWorker();
private
  final ArrayList<IsoChunk> tempList = std::make_unique<ArrayList<>>();
public
  ConcurrentLinkedQueue<IsoChunk> toSaveQueue =
      std::make_unique<ConcurrentLinkedQueue<>>();
  bool bSaving;

  void Update(IsoChunk chunk1) {
    if (!GameServer.bServer) {
      IsoChunk chunk0 = null;
      void *object = null;
      this.bSaving = !this.toSaveQueue.isEmpty();
      if (this.bSaving) {
        if (chunk1 != nullptr) {
          for (IsoChunk chunk2 : this.toSaveQueue) {
            if (chunk2.wx == chunk1.wx && chunk2.wy == chunk1.wy) {
              chunk0 = chunk2;
              break;
            }
          }
        }

        if (chunk0 == nullptr) {
          chunk0 = this.toSaveQueue.poll();
        } else {
          this.toSaveQueue.remove(chunk0);
        }

        if (chunk0 != nullptr) {
          try {
            chunk0.Save(false);
          } catch (Exception exception) {
            exception.printStackTrace();
          }
        }
      }
    }
  }

  void SaveNow(ArrayList<IsoChunk> arrayList) {
    this.tempList.clear();

    for (IsoChunk chunk0 = this.toSaveQueue.poll(); chunk0 != nullptr;
         chunk0 = this.toSaveQueue.poll()) {
      bool boolean0 = false;

      for (int int0 = 0; int0 < arrayList.size(); int0++) {
        IsoChunk chunk1 = (IsoChunk)arrayList.get(int0);
        if (chunk0.wx == chunk1.wx && chunk0.wy == chunk1.wy) {
          try {
            chunk0.Save(false);
          } catch (IOException iOException) {
            iOException.printStackTrace();
          }

          boolean0 = true;
          break;
        }
      }

      if (!boolean0) {
        this.tempList.add(chunk0);
      }
    }

    for (int int1 = 0; int1 < this.tempList.size(); int1++) {
      this.toSaveQueue.add(this.tempList.get(int1));
    }

    this.tempList.clear();
  }

  void SaveNow() {
    DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 1");

    for (IsoChunk chunk = this.toSaveQueue.poll(); chunk != nullptr;
         chunk = this.toSaveQueue.poll()) {
      try {
        DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 2 (ch=" + chunk.wx +
                     ", " + chunk.wy + ")");
        chunk.Save(false);
      } catch (Exception exception) {
        exception.printStackTrace();
      }
    }

    this.bSaving = false;
    DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 3");
  }

  void Add(IsoChunk chunk) {
    if (Core.getInstance().isNoSave()) {
      for (int int0 = 0; int0 < chunk.vehicles.size(); int0++) {
        VehiclesDB2.instance.updateVehicle(chunk.vehicles.get(int0));
      }
    }

    if (!this.toSaveQueue.contains(chunk)) {
      this.toSaveQueue.add(chunk);
    }
  }
}
} // namespace iso
} // namespace zombie
