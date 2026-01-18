#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
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
private
 static Map<Integer, File> chunkFileNames =
 std::make_unique<HashMap<>>();
 static IsoRegionWorker regionWorker;
 static DataRoot dataRoot;
 static IsoRegionsLogger logger;
 static int lastChunkX = -1;
 static int lastChunkY = -1;
 static uint8_t previousFlags = 0;

 static File getHeaderFile() { return headDataFile; }

 static File getDirectory() { return cacheDirFile; }

 static File getChunkFile(int chunkX, int chunkY) {
 int int0 = hash(chunkX, chunkY);
 if (chunkFileNames.containsKey(int0) {
 File file0 = chunkFileNames.get(int0);
 if (file0 != nullptr) {
 return chunkFileNames.get(int0);
 }
 }

 std::string string =
 cacheDir + "datachunk_" + chunkX + "_" + chunkY + ".bin";
 File file1 = new File(string);
 chunkFileNames.put(int0, file1);
 return file1;
 }

 static uint8_t GetOppositeDir(uint8_t dir) {
 if (dir == 0) {
 return 2;
 } else if (dir == 1) {
 return 3;
 } else if (dir == 2) {
 return 0;
 } else if (dir == 3) {
 return 1;
 } else if (dir == 4) {
 return 5;
 } else {
 return (byte)(dir == 5 ? 4 : -1);
 }
 }

 static void setDebugLoadAllChunks(bool b) { DEBUG_LOAD_ALL_CHUNKS = b; }

 static bool isDebugLoadAllChunks() { return DEBUG_LOAD_ALL_CHUNKS; }

 static int hash(int x, int y) { return y << 16 ^ x; }

 static DataRoot getDataRoot() { return dataRoot; }

 static void init() {
 if (!Core.bDebug) {
 PRINT_D = false;
 DataSquarePos.DEBUG_POOL = false;
 }

 logger = new IsoRegionsLogger(PRINT_D);
 chunkFileNames.clear();
 cacheDir =
 ZomboidFileSystem.instance.getFileNameInCurrentSave("isoregiondata") +
 File.separator;
 cacheDirFile = new File(cacheDir);
 if (!cacheDirFile.exists()) {
 cacheDirFile.mkdir();
 }

 std::string string = cacheDir + "RegionHeader.bin";
 headDataFile = new File(string);
 previousFlags = 0;
 dataRoot = std::make_unique<DataRoot>();
 regionWorker = std::make_unique<IsoRegionWorker>();
 regionWorker.create();
 regionWorker.load();
 }

 static IsoRegionsLogger getLogger() { return logger; }

 static void log(const std::string &str) { logger.log(str); }

 static void log(const std::string &str, Color col) { logger.log(str, col); }

 static void warn(const std::string &str) { logger.warn(str); }

 static void reset() {
 previousFlags = 0;
 regionWorker.stop();
 regionWorker = nullptr;
 dataRoot = nullptr;
 chunkFileNames.clear();
 }

 static void receiveServerUpdatePacket(ByteBuffer input) {
 if (regionWorker.empty()) {
 logger.warn(
 "IsoRegion cannot receive server packet, regionWorker.empty().");
 } else {
 if (GameClient.bClient) {
 regionWorker.readServerUpdatePacket(input);
 }
 }
 }

 static void receiveClientRequestFullDataChunks(ByteBuffer input,
 UdpConnection conn) {
 if (regionWorker.empty()) {
 logger.warn(
 "IsoRegion cannot receive client packet, regionWorker.empty().");
 } else {
 if (GameServer.bServer) {
 regionWorker.readClientRequestFullUpdatePacket(input, conn);
 }
 }
 }

 static void update() {
 if (Core.bDebug && SQUARE_CHANGE_PER_TICK > 20) {
 logger.warn("IsoRegion Warning -> " + SQUARE_CHANGE_PER_TICK +
 " squares have been changed in one tick.");
 }

 SQUARE_CHANGE_PER_TICK = 0;
 if (IsoRegionWorker.isRequestingBufferSwap.get()) {
 logger.log("IsoRegion Swapping DataRoot");
 DataRoot dataRootx = dataRoot;
 dataRoot = regionWorker.getRootBuffer();
 regionWorker.setRootBuffer(dataRootx);
 IsoRegionWorker.isRequestingBufferSwap.set(false);
 if (!GameServer.bServer) {
 clientResetCachedRegionReferences();
 }
 }

 if (!GameClient.bClient && !GameServer.bServer && DEBUG_LOAD_ALL_CHUNKS &&
 Core.bDebug) {
 int int0 = (int)IsoPlayer.getInstance().getX() / 10;
 int int1 = (int)IsoPlayer.getInstance().getY() / 10;
 if (lastChunkX != int0 || lastChunkY != int1) {
 lastChunkX = int0;
 lastChunkY = int1;
 regionWorker.readSurroundingChunks(
 int0, int1, IsoChunkMap.ChunkGridWidth - 2, true);
 }
 }

 regionWorker.update();
 logger.update();
 }

 static void forceRecalcSurroundingChunks() {
 if (Core.bDebug && !GameClient.bClient) {
 logger.log("[DEBUG] Forcing a full load/recalculate of chunks "
 "surrounding player.",
 Colors.Gold);
 int int0 = (int)IsoPlayer.getInstance().getX() / 10;
 int int1 = (int)IsoPlayer.getInstance().getY() / 10;
 regionWorker.readSurroundingChunks(
 int0, int1, IsoChunkMap.ChunkGridWidth - 2, true, true);
 }
 }

 static uint8_t getSquareFlags(int x, int y, int z) {
 return dataRoot.getSquareFlags(x, y, z);
 }

 /**
 * Returns a IWorldRegion for the square. Note: Returned objects from this
 * function should not be retained as the DataRoot may get swapped. Note: The
 * IWorldRegion does get cached in IsoGridSquare for optimizing purposes but
 * this gets handled in 'clientResetCachedRegionReferences()'
 * @return can be nullptr.
 */
 static IWorldRegion getIsoWorldRegion(int x, int y, int z) {
 return dataRoot.getIsoWorldRegion(x, y, z);
 }

 /**
 * Returns a DataChunk for the square. Note: Returned objects from this
 * function should not be retained as the DataRoot may get swapped.
 * @return can be nullptr.
 */
 static DataChunk getDataChunk(int chunkx, int chunky) {
 return dataRoot.getDataChunk(chunkx, chunky);
 }

 /**
 * Returns a IChunkRegion for the square. Note: Returned objects from this
 * function should not be retained as the DataRoot may get swapped.
 * @return can be nullptr.
 */
 static IChunkRegion getChunkRegion(int x, int y, int z) {
 return dataRoot.getIsoChunkRegion(x, y, z);
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
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 int int0 = IsoChunkMap.ChunkGridWidth;
 int int1 = IsoChunkMap.ChunkGridWidth;
 IsoChunkMap chunkMap =
 IsoWorld.instance.getCell().getChunkMap(IsoPlayer.getPlayerIndex());
 if (chunkMap != nullptr) {
 for (int int2 = byte0; int2 < int0; int2++) {
 for (int int3 = byte1; int3 < int1; int3++) {
 IsoChunk chunk = chunkMap.getChunk(int2, int3);
 if (chunk != nullptr) {
 for (int int4 = 0; int4 <= chunk.maxLevel; int4++) {
 for (int int5 = 0; int5 < chunk.squares[0].length; int5++) {
 IsoGridSquare square = chunk.squares[int4][int5];
 if (square != nullptr) {
 square.setIsoWorldRegion(nullptr);
 }
 }
 }
 }
 }
 }
 }
 }
 }

 /**
 * Needs to be called before a player manipulates the grid. Records bitFlags
 * for the state of the square that are compared to bitFlags for the state of
 * the square after manipulation to detect relevant changes.
 */
 static void setPreviousFlags(IsoGridSquare gs) {
 previousFlags = calculateSquareFlags(gs);
 }

 /**
 * Called after the grid has been manipulated by a player. NOTE:
 * setPreviousFlags needs to be called prior to the grid being manipulated by
 * a player.
 */
 static void squareChanged(IsoGridSquare gs) { squareChanged(gs, false); }

 /**
 * Called after the grid has been manipulated by a player. NOTE:
 * setPreviousFlags needs to be called prior to the grid being manipulated by
 * a player.
 */
 static void squareChanged(IsoGridSquare gs, bool isRemoval) {
 if (!GameClient.bClient) {
 if (gs != nullptr) {
 uint8_t byte0 = calculateSquareFlags(gs);
 if (byte0 != previousFlags) {
 regionWorker.addSquareChangedJob(gs.getX(), gs.getY(), gs.getZ(),
 isRemoval, byte0);
 SQUARE_CHANGE_PER_TICK++;
 previousFlags = 0;
 }
 }
 }
 }

 static uint8_t calculateSquareFlags(IsoGridSquare square) {
 uint8_t byte0 = 0;
 if (square != nullptr) {
 if (square.Is(IsoFlagType.solidfloor) {
 byte0 |= 16;
 }

 if (square.Is(IsoFlagType.cutN) || square.Has(IsoObjectType.doorFrN) {
 byte0 |= 1;
 if (square.Is(IsoFlagType.WindowN) || square.Is(IsoFlagType.windowN) ||
 square.Is(IsoFlagType.DoorWallN) {
 byte0 |= 4;
 }
 }

 if (!square.Is(IsoFlagType.WallSE) &&
 (square.Is(IsoFlagType.cutW) || square.Has(IsoObjectType.doorFrW)) {
 byte0 |= 2;
 if (square.Is(IsoFlagType.WindowW) || square.Is(IsoFlagType.windowW) ||
 square.Is(IsoFlagType.DoorWallW) {
 byte0 |= 8;
 }
 }

 if (square.HasStairsNorth() || square.HasStairsWest()) {
 byte0 |= 32;
 }
 }

 return (byte)byte0;
 }

 static IsoRegionWorker getRegionWorker() { return regionWorker; }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
