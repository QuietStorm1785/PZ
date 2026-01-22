#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include "zombie/iso/areas/isoregion/data/DataSquarePos.h"
#include "zombie/iso/areas/isoregion/regions/IChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IWorldRegion.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegions {
public:
    static const int SINGLE_CHUNK_PACKET_SIZE = 1024;
    static const int CHUNKS_DATA_PACKET_SIZE = 65536;
    static bool PRINT_D = false;
    static const int CELL_DIM = 300;
    static const int CELL_CHUNK_DIM = 30;
    static const int CHUNK_DIM = 10;
    static const int CHUNK_MAX_Z = 8;
    static const uint8_t BIT_EMPTY = 0;
    static const uint8_t BIT_WALL_N = 1;
    static const uint8_t BIT_WALL_W = 2;
    static const uint8_t BIT_PATH_WALL_N = 4;
    static const uint8_t BIT_PATH_WALL_W = 8;
    static const uint8_t BIT_HAS_FLOOR = 16;
    static const uint8_t BIT_STAIRCASE = 32;
    static const uint8_t BIT_HAS_ROOF = 64;
    static const uint8_t DIR_NONE = -1;
    static const uint8_t DIR_N = 0;
    static const uint8_t DIR_W = 1;
    static const uint8_t DIR_2D_NW = 2;
    static const uint8_t DIR_S = 2;
    static const uint8_t DIR_E = 3;
    static const uint8_t DIR_2D_MAX = 4;
    static const uint8_t DIR_TOP = 4;
    static const uint8_t DIR_BOT = 5;
    static const uint8_t DIR_MAX = 6;
    static const int CHUNK_LOAD_DIMENSIONS = 7;
    static bool DEBUG_LOAD_ALL_CHUNKS = false;
    static const std::string FILE_PRE = "datachunk_";
    static const std::string FILE_SEP = "_";
    static const std::string FILE_EXT = ".bin";
    static const std::string FILE_DIR = "isoregiondata";
    static const int SQUARE_CHANGE_WARN_THRESHOLD = 20;
    static int SQUARE_CHANGE_PER_TICK = 0;
    static std::string cacheDir;
    static File cacheDirFile;
    static File headDataFile;
   private static const Map<int, File> chunkFileNames = std::make_unique<std::unordered_map<>>();
    static IsoRegionWorker regionWorker;
    static DataRoot dataRoot;
    static IsoRegionsLogger logger;
    static int lastChunkX = -1;
    static int lastChunkY = -1;
    static uint8_t previousFlags = 0;

    static File getHeaderFile() {
    return headDataFile;
   }

    static File getDirectory() {
    return cacheDirFile;
   }

    static File getChunkFile(int var0, int var1) {
    int var2 = hash(var0, var1);
      if (chunkFileNames.containsKey(var2)) {
    File var3 = chunkFileNames.get(var2);
         if (var3 != nullptr) {
            return chunkFileNames.get(var2);
         }
      }

    std::string var5 = cacheDir + "datachunk_" + var0 + "_" + var1 + ".bin";
    File var4 = std::make_shared<File>(var5);
      chunkFileNames.put(var2, var4);
    return var4;
   }

    static uint8_t GetOppositeDir(uint8_t var0) {
      if (var0 == 0) {
    return 2;
      } else if (var0 == 1) {
    return 3;
      } else if (var0 == 2) {
    return 0;
      } else if (var0 == 3) {
    return 1;
      } else if (var0 == 4) {
    return 5;
      } else {
         return (byte)(var0 == 5 ? 4 : -1);
      }
   }

    static void setDebugLoadAllChunks(bool var0) {
      DEBUG_LOAD_ALL_CHUNKS = var0;
   }

    static bool isDebugLoadAllChunks() {
    return DEBUG_LOAD_ALL_CHUNKS;
   }

    static int hash(int var0, int var1) {
      return var1 << 16 ^ var0;
   }

    static DataRoot getDataRoot() {
    return dataRoot;
   }

    static void init() {
      if (!Core.bDebug) {
         PRINT_D = false;
         DataSquarePos.DEBUG_POOL = false;
      }

      logger = std::make_shared<IsoRegionsLogger>(PRINT_D);
      chunkFileNames.clear();
      cacheDir = ZomboidFileSystem.instance.getFileNameInCurrentSave("isoregiondata") + File.separator;
      cacheDirFile = std::make_shared<File>(cacheDir);
      if (!cacheDirFile.exists()) {
         cacheDirFile.mkdir();
      }

    std::string var0 = cacheDir + "RegionHeader.bin";
      headDataFile = std::make_shared<File>(var0);
      previousFlags = 0;
      dataRoot = std::make_unique<DataRoot>();
      regionWorker = std::make_unique<IsoRegionWorker>();
      regionWorker.create();
      regionWorker.load();
   }

    static IsoRegionsLogger getLogger() {
    return logger;
   }

    static void log(const std::string& var0) {
      logger.log(var0);
   }

    static void log(const std::string& var0, Color var1) {
      logger.log(var0, var1);
   }

    static void warn(const std::string& var0) {
      logger.warn(var0);
   }

    static void reset() {
      previousFlags = 0;
      regionWorker.stop();
      regionWorker = nullptr;
      dataRoot = nullptr;
      chunkFileNames.clear();
   }

    static void receiveServerUpdatePacket(ByteBuffer var0) {
      if (regionWorker == nullptr) {
         logger.warn("IsoRegion cannot receive server packet, regionWorker == nullptr.");
      } else {
         if (GameClient.bClient) {
            regionWorker.readServerUpdatePacket(var0);
         }
      }
   }

    static void receiveClientRequestFullDataChunks(ByteBuffer var0, UdpConnection var1) {
      if (regionWorker == nullptr) {
         logger.warn("IsoRegion cannot receive client packet, regionWorker == nullptr.");
      } else {
         if (GameServer.bServer) {
            regionWorker.readClientRequestFullUpdatePacket(var0, var1);
         }
      }
   }

    static void update() {
      if (Core.bDebug && SQUARE_CHANGE_PER_TICK > 20) {
         logger.warn("IsoRegion Warning -> " + SQUARE_CHANGE_PER_TICK + " squares have been changed in one tick.");
      }

      SQUARE_CHANGE_PER_TICK = 0;
      if (IsoRegionWorker.isRequestingBufferSwap.get()) {
         logger.log("IsoRegion Swapping DataRoot");
    DataRoot var0 = dataRoot;
         dataRoot = regionWorker.getRootBuffer();
         regionWorker.setRootBuffer(var0);
         IsoRegionWorker.isRequestingBufferSwap.set(false);
         if (!GameServer.bServer) {
            clientResetCachedRegionReferences();
         }
      }

      if (!GameClient.bClient && !GameServer.bServer && DEBUG_LOAD_ALL_CHUNKS && Core.bDebug) {
    int var2 = (int)IsoPlayer.getInstance().getX() / 10;
    int var1 = (int)IsoPlayer.getInstance().getY() / 10;
         if (lastChunkX != var2 || lastChunkY != var1) {
            lastChunkX = var2;
            lastChunkY = var1;
            regionWorker.readSurroundingChunks(var2, var1, IsoChunkMap.ChunkGridWidth - 2, true);
         }
      }

      regionWorker.update();
      logger.update();
   }

    static void forceRecalcSurroundingChunks() {
      if (Core.bDebug && !GameClient.bClient) {
         logger.log("[DEBUG] Forcing a full load/recalculate of chunks surrounding player.", Colors.Gold);
    int var0 = (int)IsoPlayer.getInstance().getX() / 10;
    int var1 = (int)IsoPlayer.getInstance().getY() / 10;
         regionWorker.readSurroundingChunks(var0, var1, IsoChunkMap.ChunkGridWidth - 2, true, true);
      }
   }

    static uint8_t getSquareFlags(int var0, int var1, int var2) {
      return dataRoot.getSquareFlags(var0, var1, var2);
   }

    static IWorldRegion getIsoWorldRegion(int var0, int var1, int var2) {
      return dataRoot.getIsoWorldRegion(var0, var1, var2);
   }

    static DataChunk getDataChunk(int var0, int var1) {
      return dataRoot.getDataChunk(var0, var1);
   }

    static IChunkRegion getChunkRegion(int var0, int var1, int var2) {
      return dataRoot.getIsoChunkRegion(var0, var1, var2);
   }

    static void ResetAllDataDebug() {
      if (Core.bDebug) {
         if (!GameServer.bServer && !GameClient.bClient) {
            regionWorker.addDebugResetJob();
         }
      }
   }

    static void clientResetCachedRegionReferences() {
      if (!GameServer.bServer) {
    uint8_t var0 = 0;
    uint8_t var1 = 0;
    int var2 = IsoChunkMap.ChunkGridWidth;
    int var3 = IsoChunkMap.ChunkGridWidth;
    IsoChunkMap var4 = IsoWorld.instance.getCell().getChunkMap(IsoPlayer.getPlayerIndex());
         if (var4 != nullptr) {
            for (int var7 = var0; var7 < var2; var7++) {
               for (int var8 = var1; var8 < var3; var8++) {
    IsoChunk var5 = var4.getChunk(var7, var8);
                  if (var5 != nullptr) {
                     for (int var9 = 0; var9 <= var5.maxLevel; var9++) {
                        for (int var10 = 0; var10 < var5.squares[0].length; var10++) {
    IsoGridSquare var6 = var5.squares[var9][var10];
                           if (var6 != nullptr) {
                              var6.setIsoWorldRegion(nullptr);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void setPreviousFlags(IsoGridSquare var0) {
      previousFlags = calculateSquareFlags(var0);
   }

    static void squareChanged(IsoGridSquare var0) {
      squareChanged(var0, false);
   }

    static void squareChanged(IsoGridSquare var0, bool var1) {
      if (!GameClient.bClient) {
         if (var0 != nullptr) {
    uint8_t var2 = calculateSquareFlags(var0);
            if (var2 != previousFlags) {
               regionWorker.addSquareChangedJob(var0.getX(), var0.getY(), var0.getZ(), var1, var2);
               SQUARE_CHANGE_PER_TICK++;
               previousFlags = 0;
            }
         }
      }
   }

    static uint8_t calculateSquareFlags(IsoGridSquare var0) {
    uint8_t var1 = 0;
      if (var0 != nullptr) {
         if (var0.Is(IsoFlagType.solidfloor)) {
            var1 |= 16;
         }

         if (var0.Is(IsoFlagType.cutN) || var0.Has(IsoObjectType.doorFrN)) {
            var1 |= 1;
            if (var0.Is(IsoFlagType.WindowN) || var0.Is(IsoFlagType.windowN) || var0.Is(IsoFlagType.DoorWallN)) {
               var1 |= 4;
            }
         }

         if (!var0.Is(IsoFlagType.WallSE) && (var0.Is(IsoFlagType.cutW) || var0.Has(IsoObjectType.doorFrW))) {
            var1 |= 2;
            if (var0.Is(IsoFlagType.WindowW) || var0.Is(IsoFlagType.windowW) || var0.Is(IsoFlagType.DoorWallW)) {
               var1 |= 8;
            }
         }

         if (var0.HasStairsNorth() || var0.HasStairsWest()) {
            var1 |= 32;
         }
      }

      return (byte)var1;
   }

    static IsoRegionWorker getRegionWorker() {
    return regionWorker;
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
