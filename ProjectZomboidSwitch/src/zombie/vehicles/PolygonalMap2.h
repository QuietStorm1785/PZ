#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"
#if __has_include(<absl/container/flat_hash_map.h>)
#  include <absl/container/flat_hash_map.h>
#  define INT_HASH_MAP boost::unordered_map
#elif __has_include(<boost/unordered_map.hpp>)
#  include <boost/unordered_map.hpp>
#  define INT_HASH_MAP boost::unordered_map
#else
#  include <unordered_map>
#  define INT_HASH_MAP std::unordered_map
#endif
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ai/KnownBlockedEdges.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/vehicles/PathFindBehavior2/PointOnPath.h"
#include "zombie/vehicles/PolygonalMap2/1.h"
#include "zombie/vehicles/PolygonalMap2/AdjustStartEndNodeData.h"
#include "zombie/vehicles/PolygonalMap2/Cell.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/ChunkDataZ.h"
#include "zombie/vehicles/PolygonalMap2/ChunkRemoveTask.h"
#include "zombie/vehicles/PolygonalMap2/ChunkUpdateTask.h"
#include "zombie/vehicles/PolygonalMap2/ClosestPointOnEdge.h"
#include "zombie/vehicles/PolygonalMap2/Connection.h"
#include "zombie/vehicles/PolygonalMap2/Edge.h"
#include "zombie/vehicles/PolygonalMap2/IChunkTask.h"
#include "zombie/vehicles/PolygonalMap2/IPathfinder.h"
#include "zombie/vehicles/PolygonalMap2/IVehicleTask.h"
#include "zombie/vehicles/PolygonalMap2/L_render.h"
#include "zombie/vehicles/PolygonalMap2/LineClearCollide.h"
#include "zombie/vehicles/PolygonalMap2/LineClearCollideMain.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/Obstacle.h"
#include "zombie/vehicles/PolygonalMap2/PMThread.h"
#include "zombie/vehicles/PolygonalMap2/Path.h"
#include "zombie/vehicles/PolygonalMap2/PathFindRequest.h"
#include "zombie/vehicles/PolygonalMap2/PathNode.h"
#include "zombie/vehicles/PolygonalMap2/PathRequestTask.h"
#include "zombie/vehicles/PolygonalMap2/Point.h"
#include "zombie/vehicles/PolygonalMap2/PointPool.h"
#include "zombie/vehicles/PolygonalMap2/RequestQueue.h"
#include "zombie/vehicles/PolygonalMap2/SearchNode.h"
#include "zombie/vehicles/PolygonalMap2/Square.h"
#include "zombie/vehicles/PolygonalMap2/SquareUpdateTask.h"
#include "zombie/vehicles/PolygonalMap2/Sync.h"
#include "zombie/vehicles/PolygonalMap2/TestRequest.h"
#include "zombie/vehicles/PolygonalMap2/VGAStar.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
#include "zombie/vehicles/PolygonalMap2/VehicleAddTask.h"
#include "zombie/vehicles/PolygonalMap2/VehicleCluster.h"
#include "zombie/vehicles/PolygonalMap2/VehicleRect.h"
#include "zombie/vehicles/PolygonalMap2/VehicleRemoveTask.h"
#include "zombie/vehicles/PolygonalMap2/VehicleState.h"
#include "zombie/vehicles/PolygonalMap2/VehicleUpdateTask.h"
#include "zombie/vehicles/PolygonalMap2/VisibilityGraph.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    static const float RADIUS = 0.3F;
    static const float RADIUS_DIAGONAL = (float)Math.sqrt(0.18F);
    static const bool CLOSE_TO_WALLS = true;
    static const bool PATHS_UNDER_VEHICLES = true;
    static const bool COLLIDE_CLIPPER = false;
    static const bool COLLIDE_BEVEL = false;
    static const int CXN_FLAG_CAN_PATH = 1;
    static const int CXN_FLAG_THUMP = 2;
    static const int NODE_FLAG_CRAWL = 1;
    static const int NODE_FLAG_CRAWL_INTERIOR = 2;
    static const int NODE_FLAG_IN_CHUNK_DATA = 4;
    static const int NODE_FLAG_PERIMETER = 8;
    static const int NODE_FLAG_KEEP = 65536;
    static const Vector2 temp = std::make_shared<Vector2>();
    static const Vector3f tempVec3f_1 = std::make_shared<Vector3f>();
   private const std::vector<VehicleCluster> clusters = std::make_unique<std::vector<>>();
    ClosestPointOnEdge closestPointOnEdge = std::make_shared<ClosestPointOnEdge>();
   private const TIntObjectHashMap<Node> squareToNode = std::make_unique<TIntObjectHashMap>();
   private const std::vector<Square> tempSquares = std::make_unique<std::vector<>>();
    static const PolygonalMap2 instance = std::make_shared<PolygonalMap2>();
   private const std::vector<VisibilityGraph> graphs = std::make_unique<std::vector<>>();
    Clipper clipperThread;
    const ByteBuffer xyBufferThread = ByteBuffer.allocateDirect(8192);
    const AdjustStartEndNodeData adjustStartData = std::make_shared<AdjustStartEndNodeData>();
    const AdjustStartEndNodeData adjustGoalData = std::make_shared<AdjustStartEndNodeData>();
    const LineClearCollide lcc = std::make_shared<LineClearCollide>();
    const VGAStar astar = std::make_shared<VGAStar>();
    const TestRequest testRequest = std::make_shared<TestRequest>();
    int testZ = 0;
    const PointOnPath pointOnPath = std::make_shared<PointOnPath>();
    static const int SQUARES_PER_CHUNK = 10;
    static const int LEVELS_PER_CHUNK = 8;
    static const int SQUARES_PER_CELL = 300;
    static const int CHUNKS_PER_CELL = 30;
    static const int BIT_SOLID = 1;
    static const int BIT_COLLIDE_W = 2;
    static const int BIT_COLLIDE_N = 4;
    static const int BIT_STAIR_TW = 8;
    static const int BIT_STAIR_MW = 16;
    static const int BIT_STAIR_BW = 32;
    static const int BIT_STAIR_TN = 64;
    static const int BIT_STAIR_MN = 128;
    static const int BIT_STAIR_BN = 256;
    static const int BIT_SOLID_FLOOR = 512;
    static const int BIT_SOLID_TRANS = 1024;
    static const int BIT_WINDOW_W = 2048;
    static const int BIT_WINDOW_N = 4096;
    static const int BIT_CAN_PATH_W = 8192;
    static const int BIT_CAN_PATH_N = 16384;
    static const int BIT_THUMP_W = 32768;
    static const int BIT_THUMP_N = 65536;
    static const int BIT_THUMPABLE = 131072;
    static const int BIT_DOOR_E = 262144;
    static const int BIT_DOOR_S = 524288;
    static const int BIT_WINDOW_W_UNBLOCKED = 1048576;
    static const int BIT_WINDOW_N_UNBLOCKED = 2097152;
    static const int ALL_SOLID_BITS = 1025;
    static const int ALL_STAIR_BITS = 504;
   private const ConcurrentLinkedQueue<IChunkTask> chunkTaskQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<SquareUpdateTask> squareTaskQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<IVehicleTask> vehicleTaskQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const std::vector<Vehicle> vehicles = std::make_unique<std::vector<>>();
   private const std::unordered_map<BaseVehicle, Vehicle> vehicleMap = std::make_unique<std::unordered_map<>>();
    int minX;
    int minY;
    int width;
    int height;
   private Cell[][] cells;
   private const std::unordered_map<BaseVehicle, VehicleState> vehicleState = std::make_unique<std::unordered_map<>>();
   private const TObjectProcedure<Node> releaseNodeProc = std::make_shared<1>(this);
    bool rebuild;
    const Path shortestPath = std::make_shared<Path>();
    const Sync sync = std::make_shared<Sync>();
    const void* renderLock = std::make_shared<Object>();
    PMThread thread;
    const RequestQueue requests = std::make_shared<RequestQueue>();
   private const ConcurrentLinkedQueue<PathFindRequest> requestToMain = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<PathRequestTask> requestTaskQueue = std::make_unique<ConcurrentLinkedQueue<>>();
   private const std::unordered_map<Mover, PathFindRequest> requestMap = std::make_unique<std::unordered_map<>>();
    static const int LCC_ZERO = 0;
    static const int LCC_IGNORE_DOORS = 1;
    static const int LCC_CLOSE_TO_WALLS = 2;
    static const int LCC_CHECK_COST = 4;
    static const int LCC_RENDER = 8;
    static const int LCC_ALLOW_ON_EDGE = 16;
    const LineClearCollideMain lccMain = std::make_shared<LineClearCollideMain>();
   private const float[] tempFloats = new float[8];
    const CollideWithObstacles collideWithObstacles = std::make_shared<CollideWithObstacles>();
    const CollideWithObstaclesPoly collideWithObstaclesPoly = std::make_shared<CollideWithObstaclesPoly>();

    void createVehicleCluster(VehicleRect var1, std::vector<VehicleRect> var2, std::vector<VehicleCluster> var3) {
      for (int var4 = 0; var4 < var2.size(); var4++) {
    VehicleRect var5 = (VehicleRect)var2.get(var4);
         if (var1 != var5 && var1.z == var5.z && (var1.cluster == nullptr || var1.cluster != var5.cluster) && var1.isAdjacent(var5)) {
            if (var1.cluster != nullptr) {
               if (var5.cluster == nullptr) {
                  var5.cluster = var1.cluster;
                  var5.cluster.rects.push_back(var5);
               } else {
                  var3.remove(var5.cluster);
                  var1.cluster.merge(var5.cluster);
               }
            } else if (var5.cluster != nullptr) {
               if (var1.cluster == nullptr) {
                  var1.cluster = var5.cluster;
                  var1.cluster.rects.push_back(var1);
               } else {
                  var3.remove(var1.cluster);
                  var5.cluster.merge(var1.cluster);
               }
            } else {
    VehicleCluster var6 = VehicleCluster.alloc().init();
               var1.cluster = var6;
               var5.cluster = var6;
               var6.rects.push_back(var1);
               var6.rects.push_back(var5);
               var3.push_back(var6);
            }
         }
      }

      if (var1.cluster == nullptr) {
    VehicleCluster var7 = VehicleCluster.alloc().init();
         var1.cluster = var7;
         var7.rects.push_back(var1);
         var3.push_back(var7);
      }
   }

    void createVehicleClusters() {
      this.clusters.clear();
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < this.vehicles.size(); var2++) {
    Vehicle var3 = this.vehicles.get(var2);
    VehicleRect var4 = VehicleRect.alloc();
         var3.polyPlusRadius.getAABB(var4);
         var4.vehicle = var3;
         var1.push_back(var4);
      }

      if (!var1.empty()) {
         for (int var5 = 0; var5 < var1.size(); var5++) {
    VehicleRect var6 = (VehicleRect)var1.get(var5);
            this.createVehicleCluster(var6, var1, this.clusters);
         }
      }
   }

    Node getNodeForSquare(Square var1) {
    Node var2 = (Node)this.squareToNode.get(var1.ID);
      if (var2 == nullptr) {
         var2 = Node.alloc().init(var1);
         this.squareToNode.put(var1.ID, var2);
      }

    return var2;
   }

    VisibilityGraph getVisGraphAt(float var1, float var2, int var3) {
      for (int var4 = 0; var4 < this.graphs.size(); var4++) {
    VisibilityGraph var5 = this.graphs.get(var4);
         if (var5.contains(var1, var2, var3)) {
    return var5;
         }
      }

    return nullptr;
   }

    VisibilityGraph getVisGraphAt(float var1, float var2, int var3, int var4) {
      for (int var5 = 0; var5 < this.graphs.size(); var5++) {
    VisibilityGraph var6 = this.graphs.get(var5);
         if (var6.contains(var1, var2, var3, var4)) {
    return var6;
         }
      }

    return nullptr;
   }

    VisibilityGraph getVisGraphForSquare(Square var1) {
      for (int var2 = 0; var2 < this.graphs.size(); var2++) {
    VisibilityGraph var3 = this.graphs.get(var2);
         if (var3.contains(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    Connection connectTwoNodes(Node var1, Node var2, int var3) {
    Connection var4 = Connection.alloc().init(var1, var2, var3);
      var1.visible.push_back(var4);
      var2.visible.push_back(var4);
    return var4;
   }

    Connection connectTwoNodes(Node var1, Node var2) {
      return this.connectTwoNodes(var1, var2, 0);
   }

    void breakConnection(Connection var1) {
      var1.node1.visible.remove(var1);
      var1.node2.visible.remove(var1);
      var1.release();
   }

    void breakConnection(Node var1, Node var2) {
      for (int var3 = 0; var3 < var1.visible.size(); var3++) {
    Connection var4 = (Connection)var1.visible.get(var3);
         if (var4.otherNode(var1) == var2) {
            this.breakConnection(var4);
            break;
         }
      }
   }

    void addStairNodes() {
    std::vector var1 = this.tempSquares;
      var1.clear();

      for (int var2 = 0; var2 < this.graphs.size(); var2++) {
    VisibilityGraph var3 = this.graphs.get(var2);
         var3.getStairSquares(var1);
      }

      for (int var15 = 0; var15 < var1.size(); var15++) {
    Square var16 = (Square)var1.get(var15);
    Square var4 = nullptr;
    Square var5 = nullptr;
    Square var6 = nullptr;
    Square var7 = nullptr;
    Square var8 = nullptr;
         if (var16.has(8)) {
            var4 = this.getSquare(var16.x - 1, var16.y, var16.z + 1);
            var5 = var16;
            var6 = this.getSquare(var16.x + 1, var16.y, var16.z);
            var7 = this.getSquare(var16.x + 2, var16.y, var16.z);
            var8 = this.getSquare(var16.x + 3, var16.y, var16.z);
         }

         if (var16.has(64)) {
            var4 = this.getSquare(var16.x, var16.y - 1, var16.z + 1);
            var5 = var16;
            var6 = this.getSquare(var16.x, var16.y + 1, var16.z);
            var7 = this.getSquare(var16.x, var16.y + 2, var16.z);
            var8 = this.getSquare(var16.x, var16.y + 3, var16.z);
         }

         if (var4 != nullptr && var5 != nullptr && var6 != nullptr && var7 != nullptr && var8 != nullptr) {
    Node var9 = nullptr;
    Node var10 = nullptr;
    VisibilityGraph var11 = this.getVisGraphForSquare(var4);
            if (var11 == nullptr) {
               var9 = this.getNodeForSquare(var4);
            } else {
               var9 = Node.alloc().init(var4);

               for (Obstacle var13 : var11.obstacles) {
                  if (var13.isNodeInsideOf(var9)) {
                     var9.ignore = true;
                  }
               }

               var9.addGraph(var11);
               var11.addNode(var9);
               this.squareToNode.put(var4.ID, var9);
            }

            var11 = this.getVisGraphForSquare(var8);
            if (var11 == nullptr) {
               var10 = this.getNodeForSquare(var8);
            } else {
               var10 = Node.alloc().init(var8);

               for (Obstacle var22 : var11.obstacles) {
                  if (var22.isNodeInsideOf(var10)) {
                     var10.ignore = true;
                  }
               }

               var10.addGraph(var11);
               var11.addNode(var10);
               this.squareToNode.put(var8.ID, var10);
            }

            if (var9 != nullptr && var10 != nullptr) {
    Node var21 = this.getNodeForSquare(var5);
    Node var23 = this.getNodeForSquare(var6);
    Node var14 = this.getNodeForSquare(var7);
               this.connectTwoNodes(var9, var21);
               this.connectTwoNodes(var21, var23);
               this.connectTwoNodes(var23, var14);
               this.connectTwoNodes(var14, var10);
            }
         }
      }
   }

    void addCanPathNodes() {
    std::vector var1 = this.tempSquares;
      var1.clear();

      for (int var2 = 0; var2 < this.graphs.size(); var2++) {
    VisibilityGraph var3 = this.graphs.get(var2);
         var3.getCanPathSquares(var1);
      }

      for (int var10 = 0; var10 < var1.size(); var10++) {
    Square var11 = (Square)var1.get(var10);
         if (!var11.isNonThumpableSolid() && !var11.has(504) && var11.has(512)) {
            if (var11.isCanPathW()) {
    int var4 = var11.x - 1;
    int var5 = var11.y;
    Square var6 = this.getSquare(var4, var5, var11.z);
               if (var6 != nullptr && !var6.isNonThumpableSolid() && !var6.has(504) && var6.has(512)) {
    Node var7 = this.getOrCreateCanPathNode(var11);
    Node var8 = this.getOrCreateCanPathNode(var6);
    uint8_t var9 = 1;
                  if (var11.has(163840) || var6.has(131072)) {
                     var9 |= 2;
                  }

                  this.connectTwoNodes(var7, var8, var9);
               }
            }

            if (var11.isCanPathN()) {
    int var12 = var11.x;
    int var13 = var11.y - 1;
    Square var14 = this.getSquare(var12, var13, var11.z);
               if (var14 != nullptr && !var14.isNonThumpableSolid() && !var14.has(504) && var14.has(512)) {
    Node var15 = this.getOrCreateCanPathNode(var11);
    Node var16 = this.getOrCreateCanPathNode(var14);
    uint8_t var17 = 1;
                  if (var11.has(196608) || var14.has(131072)) {
                     var17 |= 2;
                  }

                  this.connectTwoNodes(var15, var16, var17);
               }
            }
         }
      }
   }

    Node getOrCreateCanPathNode(Square var1) {
    VisibilityGraph var2 = this.getVisGraphForSquare(var1);
    Node var3 = this.getNodeForSquare(var1);
      if (var2 != nullptr && !var2.nodes.contains(var3)) {
         for (Obstacle var5 : var2.obstacles) {
            if (var5.isNodeInsideOf(var3)) {
               var3.ignore = true;
               break;
            }
         }

         var2.addNode(var3);
      }

    return var3;
   }

    Node getPointOutsideObjects(Square var1, float var2, float var3) {
    Square var4 = instance.getSquare(var1.x - 1, var1.y, var1.z);
    Square var5 = instance.getSquare(var1.x - 1, var1.y - 1, var1.z);
    Square var6 = instance.getSquare(var1.x, var1.y - 1, var1.z);
    Square var7 = instance.getSquare(var1.x + 1, var1.y - 1, var1.z);
    Square var8 = instance.getSquare(var1.x + 1, var1.y, var1.z);
    Square var9 = instance.getSquare(var1.x + 1, var1.y + 1, var1.z);
    Square var10 = instance.getSquare(var1.x, var1.y + 1, var1.z);
    Square var11 = instance.getSquare(var1.x - 1, var1.y + 1, var1.z);
    float var12 = var1.x;
    float var13 = var1.y;
    float var14 = var1.x + 1;
    float var15 = var1.y + 1;
      if (var1.isCollideW()) {
         var12 += 0.35000002F;
      }

      if (var1.isCollideN()) {
         var13 += 0.35000002F;
      }

      if (var8 != nullptr && (var8.has(2) || var8.has(504) || var8.isReallySolid())) {
         var14 -= 0.35000002F;
      }

      if (var10 != nullptr && (var10.has(4) || var10.has(504) || var10.isReallySolid())) {
         var15 -= 0.35000002F;
      }

    float var16 = PZMath.clamp(var2, var12, var14);
    float var17 = PZMath.clamp(var3, var13, var15);
      if (var16 <= var1.x + 0.3F && var17 <= var1.y + 0.3F) {
    bool var18 = var5 != nullptr && (var5.has(504) || var5.isReallySolid());
         var18 |= var6 != nullptr && var6.has(2);
         var18 |= var4 != nullptr && var4.has(4);
         if (var18) {
    float var19 = var1.x + 0.3F + 0.05F;
    float var20 = var1.y + 0.3F + 0.05F;
            if (var19 - var16 <= var20 - var17) {
               var16 = var19;
            } else {
               var17 = var20;
            }
         }
      }

      if (var16 >= var1.x + 1 - 0.3F && var17 <= var1.y + 0.3F) {
    bool var23 = var7 != nullptr && (var7.has(2) || var7.has(504) || var7.isReallySolid());
         var23 |= var8 != nullptr && var8.has(4);
         if (var23) {
    float var28 = var1.x + 1 - 0.3F - 0.05F;
    float var31 = var1.y + 0.3F + 0.05F;
            if (var16 - var28 <= var31 - var17) {
               var16 = var28;
            } else {
               var17 = var31;
            }
         }
      }

      if (var16 <= var1.x + 0.3F && var17 >= var1.y + 1 - 0.3F) {
    bool var25 = var11 != nullptr && (var11.has(4) || var11.has(504) || var11.isReallySolid());
         var25 |= var10 != nullptr && var10.has(2);
         if (var25) {
    float var29 = var1.x + 0.3F + 0.05F;
    float var32 = var1.y + 1 - 0.3F - 0.05F;
            if (var29 - var16 <= var17 - var32) {
               var16 = var29;
            } else {
               var17 = var32;
            }
         }
      }

      if (var16 >= var1.x + 1 - 0.3F && var17 >= var1.y + 1 - 0.3F) {
    bool var27 = var9 != nullptr && (var9.has(2) || var9.has(4) || var9.has(504) || var9.isReallySolid());
         if (var27) {
    float var30 = var1.x + 1 - 0.3F - 0.05F;
    float var33 = var1.y + 1 - 0.3F - 0.05F;
            if (var16 - var30 <= var17 - var33) {
               var16 = var30;
            } else {
               var17 = var33;
            }
         }
      }

      return Node.alloc().init(var16, var17, var1.z);
   }

    void createVisibilityGraph(VehicleCluster var1) {
    VisibilityGraph var2 = VisibilityGraph.alloc().init(var1);
      var2.addPerimeterEdges();
      this.graphs.push_back(var2);
   }

    void createVisibilityGraphs() {
      this.createVehicleClusters();
      this.graphs.clear();
      this.squareToNode.clear();

      for (int var1 = 0; var1 < this.clusters.size(); var1++) {
    VehicleCluster var2 = this.clusters.get(var1);
         this.createVisibilityGraph(var2);
      }

      this.addStairNodes();
      this.addCanPathNodes();
   }

   // $VF: Could not verify finally blocks. A semaphore variable has been added to preserve control flow.
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool findPath(PathFindRequest var1, bool var2) {
    uint8_t var3 = 16;
      if (!(var1.dynamic_cast<IsoZombie*>(mover) != nullptr)) {
         var3 |= 4;
      }

      if ((int)var1.startZ == (int)var1.targetZ && !this.lcc.isNotClear(this, var1.startX, var1.startY, var1.targetX, var1.targetY, (int)var1.startZ, var3)) {
         var1.path.addNode(var1.startX, var1.startY, var1.startZ);
         var1.path.addNode(var1.targetX, var1.targetY, var1.targetZ);
         if (var2) {
            for (VisibilityGraph var26 : this.graphs) {
               var26.render();
            }
         }

    return true;
      } else {
         this.astar.init(this.graphs, this.squareToNode);
         this.astar.knownBlockedEdges.clear();

         for (int var4 = 0; var4 < var1.knownBlockedEdges.size(); var4++) {
    KnownBlockedEdges var5 = (KnownBlockedEdges)var1.knownBlockedEdges.get(var4);
    Square var6 = this.getSquare(var5.x, var5.y, var5.z);
            if (var6 != nullptr) {
               this.astar.knownBlockedEdges.put(var6.ID, var5);
            }
         }

    VisibilityGraph var23 = nullptr;
    VisibilityGraph var25 = nullptr;
    SearchNode var27 = nullptr;
    SearchNode var7 = nullptr;
    bool var8 = false;
    bool var9 = false;
    bool var21 = false /* VF: Semaphore variable */;

    bool var80;
         label1216: {
    bool var40;
            label1217: {
               label1218: {
                  label1219: {
    int var66;
                     label1220: {
    bool var48;
                        label1221: {
                           label1222: {
                              try {
                                 var21 = true;
    Square var10 = this.getSquare((int)var1.startX, (int)var1.startY, (int)var1.startZ);
                                 if (var10 != nullptr && !var10.isReallySolid()) {
                                    if (var10.has(504)) {
                                       var27 = this.astar.getSearchNode(var10);
                                    } else {
    VisibilityGraph var33 = this.astar.getVisGraphForSquare(var10);
                                       if (var33 != nullptr) {
                                          if (!var33.created) {
                                             var33.create();
                                          }

    Node var45 = nullptr;
                                          var66 = var33.getPointOutsideObstacles(var1.startX, var1.startY, var1.startZ, this.adjustStartData);
                                          if (var66 == -1) {
                                             var80 = false;
                                             var21 = false;
    break label1216;
                                          }

                                          if (var66 == 1) {
                                             var8 = true;
                                             var45 = this.adjustStartData.node;
                                             if (this.adjustStartData.isNodeNew) {
                                                var23 = var33;
                                             }
                                          }

                                          if (var45 == nullptr) {
                                             var45 = Node.alloc().init(var1.startX, var1.startY, (int)var1.startZ);
                                             var33.addNode(var45);
                                             var23 = var33;
                                          }

                                          var27 = this.astar.getSearchNode(var45);
                                       }
                                    }

                                    if (var27 == nullptr) {
                                       var27 = this.astar.getSearchNode(var10);
                                    }

                                    if (!(var1.targetX < 0.0F)
                                       && !(var1.targetY < 0.0F)
                                       && this.getChunkFromSquarePos((int)var1.targetX, (int)var1.targetY) != nullptr) {
                                       var10 = this.getSquare((int)var1.targetX, (int)var1.targetY, (int)var1.targetZ);
                                       if (var10 == nullptr || var10.isReallySolid()) {
                                          var40 = false;
                                          var21 = false;
    break label1219;
                                       }

                                       if ((
                                             (int)var1.startX != (int)var1.targetX
                                                || (int)var1.startY != (int)var1.targetY
                                                || (int)var1.startZ != (int)var1.targetZ
                                          )
                                          && this.isBlockedInAllDirections((int)var1.targetX, (int)var1.targetY, (int)var1.targetZ)) {
                                          var40 = false;
                                          var21 = false;
    break label1217;
                                       }

                                       if (var10.has(504)) {
                                          var7 = this.astar.getSearchNode(var10);
                                       } else {
    VisibilityGraph var34 = this.astar.getVisGraphForSquare(var10);
                                          if (var34 != nullptr) {
                                             if (!var34.created) {
                                                var34.create();
                                             }

    Node var46 = nullptr;
                                             var66 = var34.getPointOutsideObstacles(var1.targetX, var1.targetY, var1.targetZ, this.adjustGoalData);
                                             if (var66 == -1) {
                                                var80 = false;
                                                var21 = false;
    break label1218;
                                             }

                                             if (var66 == 1) {
                                                var9 = true;
                                                var46 = this.adjustGoalData.node;
                                                if (this.adjustGoalData.isNodeNew) {
                                                   var25 = var34;
                                                }
                                             }

                                             if (var46 == nullptr) {
                                                var46 = Node.alloc().init(var1.targetX, var1.targetY, (int)var1.targetZ);
                                                var34.addNode(var46);
                                                var25 = var34;
                                             }

                                             var7 = this.astar.getSearchNode(var46);
                                          } else {
                                             for (int var47 = 0; var47 < this.graphs.size(); var47++) {
    VisibilityGraph var35 = this.graphs.get(var47);
                                                if (var35.contains(var10, 1)) {
    Node var61 = this.getPointOutsideObjects(var10, var1.targetX, var1.targetY);
                                                   var35.addNode(var61);
                                                   if (var61.x != var1.targetX || var61.y != var1.targetY) {
                                                      var9 = true;
                                                      this.adjustGoalData.isNodeNew = false;
                                                   }

                                                   var25 = var35;
                                                   var7 = this.astar.getSearchNode(var61);
                                                   break;
                                                }
                                             }
                                          }
                                       }

                                       if (var7 == nullptr) {
                                          var7 = this.astar.getSearchNode(var10);
                                       }
                                    } else {
                                       var7 = this.astar.getSearchNode((int)var1.targetX, (int)var1.targetY);
                                    }

    std::vector var36 = this.astar.shortestPath(var1, var27, var7);
                                    if (var36 != nullptr) {
                                       if (var36.size() == 1) {
                                          var1.path.addNode(var27);
                                          if (!var9 && var7.square != nullptr && var7.square.x + 0.5F != var1.targetX && var7.square.y + 0.5F != var1.targetY) {
                                             var1.path.addNode(var1.targetX, var1.targetY, var1.targetZ, 0);
                                          } else {
                                             var1.path.addNode(var7);
                                          }

                                          var66 = 1;
                                          var21 = false;
    break label1220;
                                       }

                                       this.cleanPath(var36, var1, var8, var9, var7);
                                       if (var1.dynamic_cast<IsoPlayer*>(mover) != nullptr && !((IsoPlayer)var1.mover).isNPC()) {
                                          this.smoothPath(var1.path);
                                       }

                                       var48 = true;
                                       var21 = false;
    break label1221;
                                    }

                                    var21 = false;
    break label1222;
                                 }

                                 var40 = false;
                                 var21 = false;
                              } finally {
                                 if (var21) {
                                    if (var2) {
                                       for (VisibilityGraph var19 : this.graphs) {
                                          var19.render();
                                       }
                                    }

                                    if (var23 != nullptr) {
                                       var23.removeNode(var27.vgNode);
                                    }

                                    if (var25 != nullptr) {
                                       var25.removeNode(var7.vgNode);
                                    }

                                    for (int var96 = 0; var96 < this.astar.searchNodes.size(); var96++) {
                                       ((SearchNode)this.astar.searchNodes.get(var96)).release();
                                    }

                                    if (var8 && this.adjustStartData.isNodeNew) {
                                       for (int var97 = 0; var97 < this.adjustStartData.node.edges.size(); var97++) {
    Edge var99 = (Edge)this.adjustStartData.node.edges.get(var97);
                                          var99.obstacle.unsplit(this.adjustStartData.node, var99.edgeRing);
                                       }

                                       this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                                    }

                                    if (var9 && this.adjustGoalData.isNodeNew) {
                                       for (int var98 = 0; var98 < this.adjustGoalData.node.edges.size(); var98++) {
    Edge var100 = (Edge)this.adjustGoalData.node.edges.get(var98);
                                          var100.obstacle.unsplit(this.adjustGoalData.node, var100.edgeRing);
                                       }

                                       this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                                    }
                                 }
                              }

                              if (var2) {
                                 for (VisibilityGraph var13 : this.graphs) {
                                    var13.render();
                                 }
                              }

                              if (var23 != nullptr) {
                                 var23.removeNode(var27.vgNode);
                              }

                              if (var25 != nullptr) {
                                 var25.removeNode(var7.vgNode);
                              }

                              for (int var42 = 0; var42 < this.astar.searchNodes.size(); var42++) {
                                 ((SearchNode)this.astar.searchNodes.get(var42)).release();
                              }

                              if (var8 && this.adjustStartData.isNodeNew) {
                                 for (int var43 = 0; var43 < this.adjustStartData.node.edges.size(); var43++) {
    Edge var57 = (Edge)this.adjustStartData.node.edges.get(var43);
                                    var57.obstacle.unsplit(this.adjustStartData.node, var57.edgeRing);
                                 }

                                 this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                              }

                              if (var9 && this.adjustGoalData.isNodeNew) {
                                 for (int var44 = 0; var44 < this.adjustGoalData.node.edges.size(); var44++) {
    Edge var58 = (Edge)this.adjustGoalData.node.edges.get(var44);
                                    var58.obstacle.unsplit(this.adjustGoalData.node, var58.edgeRing);
                                 }

                                 this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                              }

    return var40;
                           }

                           if (var2) {
                              for (VisibilityGraph var37 : this.graphs) {
                                 var37.render();
                              }
                           }

                           if (var23 != nullptr) {
                              var23.removeNode(var27.vgNode);
                           }

                           if (var25 != nullptr) {
                              var25.removeNode(var7.vgNode);
                           }

                           for (int var30 = 0; var30 < this.astar.searchNodes.size(); var30++) {
                              ((SearchNode)this.astar.searchNodes.get(var30)).release();
                           }

                           if (var8 && this.adjustStartData.isNodeNew) {
                              for (int var31 = 0; var31 < this.adjustStartData.node.edges.size(); var31++) {
    Edge var38 = (Edge)this.adjustStartData.node.edges.get(var31);
                                 var38.obstacle.unsplit(this.adjustStartData.node, var38.edgeRing);
                              }

                              this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                           }

                           if (var9 && this.adjustGoalData.isNodeNew) {
                              for (int var32 = 0; var32 < this.adjustGoalData.node.edges.size(); var32++) {
    Edge var39 = (Edge)this.adjustGoalData.node.edges.get(var32);
                                 var39.obstacle.unsplit(this.adjustGoalData.node, var39.edgeRing);
                              }

                              this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                           }

    return false;
                        }

                        if (var2) {
                           for (VisibilityGraph var73 : this.graphs) {
                              var73.render();
                           }
                        }

                        if (var23 != nullptr) {
                           var23.removeNode(var27.vgNode);
                        }

                        if (var25 != nullptr) {
                           var25.removeNode(var7.vgNode);
                        }

                        for (int var63 = 0; var63 < this.astar.searchNodes.size(); var63++) {
                           ((SearchNode)this.astar.searchNodes.get(var63)).release();
                        }

                        if (var8 && this.adjustStartData.isNodeNew) {
                           for (int var64 = 0; var64 < this.adjustStartData.node.edges.size(); var64++) {
    Edge var74 = (Edge)this.adjustStartData.node.edges.get(var64);
                              var74.obstacle.unsplit(this.adjustStartData.node, var74.edgeRing);
                           }

                           this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                        }

                        if (var9 && this.adjustGoalData.isNodeNew) {
                           for (int var65 = 0; var65 < this.adjustGoalData.node.edges.size(); var65++) {
    Edge var75 = (Edge)this.adjustGoalData.node.edges.get(var65);
                              var75.obstacle.unsplit(this.adjustGoalData.node, var75.edgeRing);
                           }

                           this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                        }

    return var48;
                     }

                     if (var2) {
                        for (VisibilityGraph var84 : this.graphs) {
                           var84.render();
                        }
                     }

                     if (var23 != nullptr) {
                        var23.removeNode(var27.vgNode);
                     }

                     if (var25 != nullptr) {
                        var25.removeNode(var7.vgNode);
                     }

                     for (int var77 = 0; var77 < this.astar.searchNodes.size(); var77++) {
                        ((SearchNode)this.astar.searchNodes.get(var77)).release();
                     }

                     if (var8 && this.adjustStartData.isNodeNew) {
                        for (int var78 = 0; var78 < this.adjustStartData.node.edges.size(); var78++) {
    Edge var85 = (Edge)this.adjustStartData.node.edges.get(var78);
                           var85.obstacle.unsplit(this.adjustStartData.node, var85.edgeRing);
                        }

                        this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                     }

                     if (var9 && this.adjustGoalData.isNodeNew) {
                        for (int var79 = 0; var79 < this.adjustGoalData.node.edges.size(); var79++) {
    Edge var86 = (Edge)this.adjustGoalData.node.edges.get(var79);
                           var86.obstacle.unsplit(this.adjustGoalData.node, var86.edgeRing);
                        }

                        this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                     }

                     return (boolean)var66;
                  }

                  if (var2) {
                     for (VisibilityGraph var70 : this.graphs) {
                        var70.render();
                     }
                  }

                  if (var23 != nullptr) {
                     var23.removeNode(var27.vgNode);
                  }

                  if (var25 != nullptr) {
                     var25.removeNode(var7.vgNode);
                  }

                  for (int var54 = 0; var54 < this.astar.searchNodes.size(); var54++) {
                     ((SearchNode)this.astar.searchNodes.get(var54)).release();
                  }

                  if (var8 && this.adjustStartData.isNodeNew) {
                     for (int var55 = 0; var55 < this.adjustStartData.node.edges.size(); var55++) {
    Edge var71 = (Edge)this.adjustStartData.node.edges.get(var55);
                        var71.obstacle.unsplit(this.adjustStartData.node, var71.edgeRing);
                     }

                     this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
                  }

                  if (var9 && this.adjustGoalData.isNodeNew) {
                     for (int var56 = 0; var56 < this.adjustGoalData.node.edges.size(); var56++) {
    Edge var72 = (Edge)this.adjustGoalData.node.edges.get(var56);
                        var72.obstacle.unsplit(this.adjustGoalData.node, var72.edgeRing);
                     }

                     this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
                  }

    return var40;
               }

               if (var2) {
                  for (VisibilityGraph var16 : this.graphs) {
                     var16.render();
                  }
               }

               if (var23 != nullptr) {
                  var23.removeNode(var27.vgNode);
               }

               if (var25 != nullptr) {
                  var25.removeNode(var7.vgNode);
               }

               for (int var81 = 0; var81 < this.astar.searchNodes.size(); var81++) {
                  ((SearchNode)this.astar.searchNodes.get(var81)).release();
               }

               if (var8 && this.adjustStartData.isNodeNew) {
                  for (int var82 = 0; var82 < this.adjustStartData.node.edges.size(); var82++) {
    Edge var91 = (Edge)this.adjustStartData.node.edges.get(var82);
                     var91.obstacle.unsplit(this.adjustStartData.node, var91.edgeRing);
                  }

                  this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
               }

               if (var9 && this.adjustGoalData.isNodeNew) {
                  for (int var83 = 0; var83 < this.adjustGoalData.node.edges.size(); var83++) {
    Edge var92 = (Edge)this.adjustGoalData.node.edges.get(var83);
                     var92.obstacle.unsplit(this.adjustGoalData.node, var92.edgeRing);
                  }

                  this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
               }

    return var80;
            }

            if (var2) {
               for (VisibilityGraph var67 : this.graphs) {
                  var67.render();
               }
            }

            if (var23 != nullptr) {
               var23.removeNode(var27.vgNode);
            }

            if (var25 != nullptr) {
               var25.removeNode(var7.vgNode);
            }

            for (int var50 = 0; var50 < this.astar.searchNodes.size(); var50++) {
               ((SearchNode)this.astar.searchNodes.get(var50)).release();
            }

            if (var8 && this.adjustStartData.isNodeNew) {
               for (int var51 = 0; var51 < this.adjustStartData.node.edges.size(); var51++) {
    Edge var68 = (Edge)this.adjustStartData.node.edges.get(var51);
                  var68.obstacle.unsplit(this.adjustStartData.node, var68.edgeRing);
               }

               this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
            }

            if (var9 && this.adjustGoalData.isNodeNew) {
               for (int var52 = 0; var52 < this.adjustGoalData.node.edges.size(); var52++) {
    Edge var69 = (Edge)this.adjustGoalData.node.edges.get(var52);
                  var69.obstacle.unsplit(this.adjustGoalData.node, var69.edgeRing);
               }

               this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
            }

    return var40;
         }

         if (var2) {
            for (VisibilityGraph var93 : this.graphs) {
               var93.render();
            }
         }

         if (var23 != nullptr) {
            var23.removeNode(var27.vgNode);
         }

         if (var25 != nullptr) {
            var25.removeNode(var7.vgNode);
         }

         for (int var88 = 0; var88 < this.astar.searchNodes.size(); var88++) {
            ((SearchNode)this.astar.searchNodes.get(var88)).release();
         }

         if (var8 && this.adjustStartData.isNodeNew) {
            for (int var89 = 0; var89 < this.adjustStartData.node.edges.size(); var89++) {
    Edge var94 = (Edge)this.adjustStartData.node.edges.get(var89);
               var94.obstacle.unsplit(this.adjustStartData.node, var94.edgeRing);
            }

            this.adjustStartData.graph.edges.remove(this.adjustStartData.newEdge);
         }

         if (var9 && this.adjustGoalData.isNodeNew) {
            for (int var90 = 0; var90 < this.adjustGoalData.node.edges.size(); var90++) {
    Edge var95 = (Edge)this.adjustGoalData.node.edges.get(var90);
               var95.obstacle.unsplit(this.adjustGoalData.node, var95.edgeRing);
            }

            this.adjustGoalData.graph.edges.remove(this.adjustGoalData.newEdge);
         }

    return var80;
      }
   }

    void cleanPath(std::vector<ISearchNode> var1, PathFindRequest var2, bool var3, bool var4, SearchNode var5) {
    bool var6 = var2.dynamic_cast<IsoPlayer*>(mover) != nullptr && ((IsoPlayer)var2.mover).isNPC();
    Square var7 = nullptr;
    int var8 = -123;
    int var9 = -123;

      for (int var10 = 0; var10 < var1.size(); var10++) {
    SearchNode var11 = (SearchNode)var1.get(var10);
    float var12 = var11.getX();
    float var13 = var11.getY();
    float var14 = var11.getZ();
    int var15 = var11.vgNode == nullptr ? 0 : var11.vgNode.flags;
    Square var16 = var11.square;
    bool var17 = false;
         if (var16 != nullptr && var7 != nullptr && var16.z == var7.z) {
    int var18 = var16.x - var7.x;
    int var19 = var16.y - var7.y;
            if (var18 == var8 && var19 == var9) {
               if (var2.path.nodes.size() > 1) {
                  var17 = true;
                  if (var2.path.getLastNode().hasFlag(65536)) {
                     var17 = false;
                  }
               }

               if (var18 == 0 && var19 == -1 && var7.has(16384)) {
                  var17 = false;
               } else if (var18 == 0 && var19 == 1 && var16.has(16384)) {
                  var17 = false;
               } else if (var18 == -1 && var19 == 0 && var7.has(8192)) {
                  var17 = false;
               } else if (var18 == 1 && var19 == 0 && var16.has(8192)) {
                  var17 = false;
               }
            } else {
               var8 = var18;
               var9 = var19;
            }
         } else {
            var9 = -123;
            var8 = -123;
         }

         if (var16 != nullptr) {
            var7 = var16;
         } else {
            var7 = nullptr;
         }

         if (var6) {
            var17 = false;
         }

         if (var17) {
    PathNode var26 = var2.path.getLastNode();
            var26.x = var16.x + 0.5F;
            var26.y = var16.y + 0.5F;
         } else {
            if (var2.path.nodes.size() > 1) {
    PathNode var27 = var2.path.getLastNode();
               if (Math.abs(var27.x - var12) < 0.01F && Math.abs(var27.y - var13) < 0.01F && Math.abs(var27.z - var14) < 0.01F) {
                  var27.x = var12;
                  var27.y = var13;
                  var27.z = var14;
                  continue;
               }
            }

            if (var10 > 0 && var11.square != nullptr) {
    SearchNode var28 = (SearchNode)var1.get(var10 - 1);
               if (var28.square != nullptr) {
    int var29 = var11.square.x - var28.square.x;
    int var20 = var11.square.y - var28.square.y;
                  if (var29 == 0 && var20 == -1 && var28.square.has(16384)) {
                     var15 |= 65536;
                  } else if (var29 == 0 && var20 == 1 && var11.square.has(16384)) {
                     var15 |= 65536;
                  } else if (var29 == -1 && var20 == 0 && var28.square.has(8192)) {
                     var15 |= 65536;
                  } else if (var29 == 1 && var20 == 0 && var11.square.has(8192)) {
                     var15 |= 65536;
                  }
               }
            }

            var2.path.addNode(var12, var13, var14, var15);
         }
      }

      if (var2.dynamic_cast<IsoPlayer*>(mover) != nullptr && !var6) {
         if (var2.path.empty()) {
    void* var10000 = nullptr;
         } else {
            var2.path.getNode(0);
         }

         if (!var4
            && var5.square != nullptr
            && IsoUtils.DistanceToSquared(var5.square.x + 0.5F, var5.square.y + 0.5F, var2.targetX, var2.targetY) > 0.010000000000000002) {
            var2.path.addNode(var2.targetX, var2.targetY, var2.targetZ, 0);
         }
      }

    PathNode var21 = nullptr;

      for (int var22 = 0; var22 < var2.path.nodes.size(); var22++) {
    PathNode var23 = (PathNode)var2.path.nodes.get(var22);
    PathNode var24 = var22 < var2.path.nodes.size() - 1 ? (PathNode)var2.path.nodes.get(var22 + 1) : nullptr;
         if (var23.hasFlag(1)) {
    bool var25 = var21 != nullptr && var21.hasFlag(2) || var24 != nullptr && var24.hasFlag(2);
            if (!var25) {
               var23.flags &= -4;
            }
         }

         var21 = var23;
      }
   }

    void smoothPath(Path var1) {
    int var2 = 0;

      while (var2 < var1.nodes.size() - 2) {
    PathNode var3 = (PathNode)var1.nodes.get(var2);
    PathNode var4 = (PathNode)var1.nodes.get(var2 + 1);
    PathNode var5 = (PathNode)var1.nodes.get(var2 + 2);
         if ((int)var3.z != (int)var4.z || (int)var3.z != (int)var5.z) {
            var2++;
         } else if (!this.lcc.isNotClear(this, var3.x, var3.y, var5.x, var5.y, (int)var3.z, 20)) {
            var1.nodes.remove(var2 + 1);
            var1.nodePool.push(var4);
         } else {
            var2++;
         }
      }
   }

    float getApparentZ(IsoGridSquare var1) {
      if (var1.Has(IsoObjectType.stairsTW) || var1.Has(IsoObjectType.stairsTN)) {
         return var1.z + 0.75F;
      } else if (var1.Has(IsoObjectType.stairsMW) || var1.Has(IsoObjectType.stairsMN)) {
         return var1.z + 0.5F;
      } else {
         return !var1.Has(IsoObjectType.stairsBW) && !var1.Has(IsoObjectType.stairsBN) ? var1.z : var1.z + 0.25F;
      }
   }

    void render() {
      if (Core.bDebug) {
    bool var1 = DebugOptions.instance.PathfindPathToMouseEnable.getValue() && !this.testRequest.done && IsoPlayer.getInstance().getPath2() == nullptr;
         if (DebugOptions.instance.PolymapRenderClusters.getValue()) {
            /* synchronized - TODO: add std::mutex */ (this.renderLock) {
               for (VehicleCluster var4 : this.clusters) {
                  for (VehicleRect var6 : var4.rects) {
                     LineDrawer.addLine(var6.x, var6.y, var6.z, var6.right(), var6.bottom(), var6.z, 0.0F, 0.0F, 1.0F, nullptr, false);
                  }

    VehicleRect var38 = var4.bounds();
                  var38.release();
               }

               if (!var1) {
                  for (VisibilityGraph var33 : this.graphs) {
                     var33.render();
                  }
               }
            }
         }

         if (DebugOptions.instance.PolymapRenderLineClearCollide.getValue()) {
    float var24 = Mouse.getX();
    float var29 = Mouse.getY();
    int var34 = (int)IsoPlayer.getInstance().getZ();
    float var39 = IsoUtils.XToIso(var24, var29, var34);
    float var43 = IsoUtils.YToIso(var24, var29, var34);
            LineDrawer.addLine(IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, var34, var39, var43, var34, 1, 1, 1, nullptr);
    int var7 = 9;
            var7 |= 2;
            if (this.lccMain.isNotClear(this, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, var39, var43, var34, nullptr, var7)) {
    Vector2f var8 = this.resolveCollision(IsoPlayer.getInstance(), var39, var43, L_render.vector2f);
               LineDrawer.addLine(var8.x - 0.05F, var8.y - 0.05F, var34, var8.x + 0.05F, var8.y + 0.05F, var34, 1.0F, 1.0F, 0.0F, nullptr, false);
            }
         }

         if (GameKeyboard.isKeyDown(209) && !GameKeyboard.wasKeyDown(209)) {
            this.testZ = Math.max(this.testZ - 1, 0);
         }

         if (GameKeyboard.isKeyDown(201) && !GameKeyboard.wasKeyDown(201)) {
            this.testZ = Math.min(this.testZ + 1, 7);
         }

         if (var1) {
    float var25 = Mouse.getX();
    float var30 = Mouse.getY();
    int var35 = this.testZ;
    float var40 = IsoUtils.XToIso(var25, var30, var35);
    float var44 = IsoUtils.YToIso(var25, var30, var35);
    float var48 = var35;

            for (int var51 = -1; var51 <= 2; var51++) {
               LineDrawer.addLine((int)var40 - 1, (int)var44 + var51, (int)var48, (int)var40 + 2, (int)var44 + var51, (int)var48, 0.3F, 0.3F, 0.3F, nullptr, false);
            }

            for (int var52 = -1; var52 <= 2; var52++) {
               LineDrawer.addLine((int)var40 + var52, (int)var44 - 1, (int)var48, (int)var40 + var52, (int)var44 + 2, (int)var48, 0.3F, 0.3F, 0.3F, nullptr, false);
            }

            for (int var53 = -1; var53 <= 1; var53++) {
               for (int var9 = -1; var9 <= 1; var9++) {
    float var10 = 0.3F;
    float var11 = 0.0F;
    float var12 = 0.0F;
    IsoGridSquare var13 = IsoWorld.instance.CurrentCell.getGridSquare((int)var40 + var9, (int)var44 + var53, (int)var48);
                  if (var13 == nullptr || var13.isSolid() || var13.isSolidTrans() || var13.HasStairs()) {
                     LineDrawer.addLine(
                        (int)var40 + var9,
                        (int)var44 + var53,
                        (int)var48,
                        (int)var40 + var9 + 1,
                        (int)var44 + var53 + 1,
                        (int)var48,
                        var10,
                        var11,
                        var12,
                        nullptr,
                        false
                     );
                  }
               }
            }

            if (var35 < (int)IsoPlayer.getInstance().getZ()) {
               LineDrawer.addLine((int)var40, (int)var44, (int)var48, (int)var40, (int)var44, (int)IsoPlayer.getInstance().getZ(), 0.3F, 0.3F, 0.3F, nullptr, true);
            } else if (var35 > (int)IsoPlayer.getInstance().getZ()) {
               LineDrawer.addLine((int)var40, (int)var44, (int)var48, (int)var40, (int)var44, (int)IsoPlayer.getInstance().getZ(), 0.3F, 0.3F, 0.3F, nullptr, true);
            }

            PathFindRequest var54 = PathFindRequest.alloc()
               .init(
                  this.testRequest,
                  IsoPlayer.getInstance(),
                  IsoPlayer.getInstance().x,
                  IsoPlayer.getInstance().y,
                  IsoPlayer.getInstance().z,
                  var40,
                  var44,
                  var48
               );
            if (DebugOptions.instance.PathfindPathToMouseAllowCrawl.getValue()) {
               var54.bCanCrawl = true;
               if (DebugOptions.instance.PathfindPathToMouseIgnoreCrawlCost.getValue()) {
                  var54.bIgnoreCrawlCost = true;
               }
            }

            if (DebugOptions.instance.PathfindPathToMouseAllowThump.getValue()) {
               var54.bCanThump = true;
            }

            this.testRequest.done = false;
            /* synchronized - TODO: add std::mutex */ (this.renderLock) {
    bool var58 = DebugOptions.instance.PolymapRenderClusters.getValue();
               if (this.findPath(var54, var58) && !var54.path.empty()) {
                  for (int var60 = 0; var60 < var54.path.nodes.size() - 1; var60++) {
    PathNode var64 = (PathNode)var54.path.nodes.get(var60);
    PathNode var66 = (PathNode)var54.path.nodes.get(var60 + 1);
    IsoGridSquare var14 = IsoWorld.instance.CurrentCell.getGridSquare(var64.x, var64.y, var64.z);
    IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var66.x, var66.y, var66.z);
    float var16 = var14 == nullptr ? var64.z : this.getApparentZ(var14);
    float var17 = var15 == nullptr ? var66.z : this.getApparentZ(var15);
    float var18 = 1.0F;
    float var19 = 1.0F;
    float var20 = 0.0F;
                     if (var16 != (int)var16 || var17 != (int)var17) {
                        var19 = 0.0F;
                     }

                     LineDrawer.addLine(var64.x, var64.y, var16, var66.x, var66.y, var17, var18, var19, var20, nullptr, true);
                     LineDrawer.addRect(var64.x - 0.05F, var64.y - 0.05F, var16, 0.1F, 0.1F, var18, var19, var20);
                  }

                  PathFindBehavior2.closestPointOnPath(
                     IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, IsoPlayer.getInstance().z, IsoPlayer.getInstance(), var54.path, this.pointOnPath
                  );
    PathNode var61 = (PathNode)var54.path.nodes.get(this.pointOnPath.pathIndex);
    PathNode var65 = (PathNode)var54.path.nodes.get(this.pointOnPath.pathIndex + 1);
    IsoGridSquare var67 = IsoWorld.instance.CurrentCell.getGridSquare(var61.x, var61.y, var61.z);
    IsoGridSquare var68 = IsoWorld.instance.CurrentCell.getGridSquare(var65.x, var65.y, var65.z);
    float var69 = var67 == nullptr ? var61.z : this.getApparentZ(var67);
    float var70 = var68 == nullptr ? var65.z : this.getApparentZ(var68);
    float var71 = var69 + (var70 - var69) * this.pointOnPath.dist;
                  LineDrawer.addLine(
                     this.pointOnPath.x - 0.05F,
                     this.pointOnPath.y - 0.05F,
                     var71,
                     this.pointOnPath.x + 0.05F,
                     this.pointOnPath.y + 0.05F,
                     var71,
                     0.0F,
                     1.0F,
                     0.0F,
                     nullptr,
                     true
                  );
                  LineDrawer.addLine(
                     this.pointOnPath.x - 0.05F,
                     this.pointOnPath.y + 0.05F,
                     var71,
                     this.pointOnPath.x + 0.05F,
                     this.pointOnPath.y - 0.05F,
                     var71,
                     0.0F,
                     1.0F,
                     0.0F,
                     nullptr,
                     true
                  );
                  if (GameKeyboard.isKeyDown(207) && !GameKeyboard.wasKeyDown(207)) {
    void* var62 = LuaManager.env.rawget("ISPathFindAction_pathToLocationF");
                     if (var62 != nullptr) {
                        LuaManager.caller.pcall(LuaManager.thread, var62, new Object[]{var40, var44, var48});
                     }
                  }
               }

               var54.release();
            }
         } else {
            for (int var26 = 0; var26 < this.testRequest.path.nodes.size() - 1; var26++) {
    PathNode var31 = (PathNode)this.testRequest.path.nodes.get(var26);
    PathNode var36 = (PathNode)this.testRequest.path.nodes.get(var26 + 1);
    float var41 = 1.0F;
    float var45 = 1.0F;
    float var49 = 0.0F;
               if (var31.z != (int)var31.z || var36.z != (int)var36.z) {
                  var45 = 0.0F;
               }

               LineDrawer.addLine(var31.x, var31.y, var31.z, var36.x, var36.y, var36.z, var41, var45, var49, nullptr, true);
            }

            this.testRequest.done = false;
         }

         if (DebugOptions.instance.PolymapRenderConnections.getValue()) {
    float var27 = Mouse.getX();
    float var32 = Mouse.getY();
    int var37 = this.testZ;
    float var42 = IsoUtils.XToIso(var27, var32, var37);
    float var46 = IsoUtils.YToIso(var27, var32, var37);
    VisibilityGraph var50 = this.getVisGraphAt(var42, var46, var37, 1);
            if (var50 != nullptr) {
    Node var55 = var50.getClosestNodeTo(var42, var46);
               if (var55 != nullptr) {
                  for (Connection var59 : var55.visible) {
    Node var63 = var59.otherNode(var55);
                     LineDrawer.addLine(var55.x, var55.y, var37, var63.x, var63.y, var37, 1.0F, 0.0F, 0.0F, nullptr, true);
                  }
               }
            }
         }

         this.updateMain();
      }
   }

    void squareChanged(IsoGridSquare var1) {
    SquareUpdateTask var2 = SquareUpdateTask.alloc().init(this, var1);
      this.squareTaskQueue.push_back(var2);
      this.thread.wake();
   }

    void addChunkToWorld(IsoChunk var1) {
    ChunkUpdateTask var2 = ChunkUpdateTask.alloc().init(this, var1);
      this.chunkTaskQueue.push_back(var2);
      this.thread.wake();
   }

    void removeChunkFromWorld(IsoChunk var1) {
      if (this.thread != nullptr) {
    ChunkRemoveTask var2 = ChunkRemoveTask.alloc().init(this, var1);
         this.chunkTaskQueue.push_back(var2);
         this.thread.wake();
      }
   }

    void addVehicleToWorld(BaseVehicle var1) {
    VehicleAddTask var2 = VehicleAddTask.alloc();
      var2.init(this, var1);
      this.vehicleTaskQueue.push_back(var2);
    VehicleState var3 = VehicleState.alloc().init(var1);
      this.vehicleState.put(var1, var3);
      this.thread.wake();
   }

    void updateVehicle(BaseVehicle var1) {
    VehicleUpdateTask var2 = VehicleUpdateTask.alloc();
      var2.init(this, var1);
      this.vehicleTaskQueue.push_back(var2);
      this.thread.wake();
   }

    void removeVehicleFromWorld(BaseVehicle var1) {
      if (this.thread != nullptr) {
    VehicleRemoveTask var2 = VehicleRemoveTask.alloc();
         var2.init(this, var1);
         this.vehicleTaskQueue.push_back(var2);
    VehicleState var3 = this.vehicleState.remove(var1);
         if (var3 != nullptr) {
            var3.vehicle = nullptr;
            var3.release();
         }

         this.thread.wake();
      }
   }

    Cell getCellFromSquarePos(int var1, int var2) {
      var1 -= this.minX * 300;
      var2 -= this.minY * 300;
      if (var1 >= 0 && var2 >= 0) {
    int var3 = var1 / 300;
    int var4 = var2 / 300;
         return var3 < this.width && var4 < this.height ? this.cells[var3][var4] : nullptr;
      } else {
    return nullptr;
      }
   }

    Cell getCellFromChunkPos(int var1, int var2) {
      return this.getCellFromSquarePos(var1 * 10, var2 * 10);
   }

    Chunk allocChunkIfNeeded(int var1, int var2) {
    Cell var3 = this.getCellFromChunkPos(var1, var2);
    return var3 = = nullptr ? nullptr : var3.allocChunkIfNeeded(var1, var2);
   }

    Chunk getChunkFromChunkPos(int var1, int var2) {
    Cell var3 = this.getCellFromChunkPos(var1, var2);
    return var3 = = nullptr ? nullptr : var3.getChunkFromChunkPos(var1, var2);
   }

    Chunk getChunkFromSquarePos(int var1, int var2) {
    Cell var3 = this.getCellFromSquarePos(var1, var2);
    return var3 = = nullptr ? nullptr : var3.getChunkFromChunkPos(var1 / 10, var2 / 10);
   }

    Square getSquare(int var1, int var2, int var3) {
    Chunk var4 = this.getChunkFromSquarePos(var1, var2);
    return var4 = = nullptr ? nullptr : var4.getSquare(var1, var2, var3);
   }

    bool isBlockedInAllDirections(int var1, int var2, int var3) {
    Square var4 = this.getSquare(var1, var2, var3);
      if (var4 == nullptr) {
    return false;
      } else {
    Square var5 = this.getSquare(var1, var2 - 1, var3);
    Square var6 = this.getSquare(var1, var2 + 1, var3);
    Square var7 = this.getSquare(var1 - 1, var2, var3);
    Square var8 = this.getSquare(var1 + 1, var2, var3);
    bool var9 = var5 != nullptr && this.astar.canNotMoveBetween(var4, var5, false);
    bool var10 = var6 != nullptr && this.astar.canNotMoveBetween(var4, var6, false);
    bool var11 = var7 != nullptr && this.astar.canNotMoveBetween(var4, var7, false);
    bool var12 = var8 != nullptr && this.astar.canNotMoveBetween(var4, var8, false);
         return var9 && var10 && var11 && var12;
      }
   }

    void init(IsoMetaGrid var1) {
      this.minX = var1.getMinX();
      this.minY = var1.getMinY();
      this.width = var1.getWidth();
      this.height = var1.getHeight();
      this.cells = new Cell[this.width][this.height];

      for (int var2 = 0; var2 < this.height; var2++) {
         for (int var3 = 0; var3 < this.width; var3++) {
            this.cells[var3][var2] = Cell.alloc().init(this, this.minX + var3, this.minY + var2);
         }
      }

      this.thread = std::make_shared<PMThread>(this);
      this.thread.setName("PolyPathThread");
      this.thread.setDaemon(true);
      this.thread.start();
   }

    void stop() {
      this.thread.bStop = true;
      this.thread.wake();

      while (this.thread.isAlive()) {
         try {
            Thread.sleep(5L);
         } catch (InterruptedException var3) {
         }
      }

      for (int var1 = 0; var1 < this.height; var1++) {
         for (int var2 = 0; var2 < this.width; var2++) {
            if (this.cells[var2][var1] != nullptr) {
               this.cells[var2][var1].release();
            }
         }
      }

      for (IChunkTask var4 = this.chunkTaskQueue.poll(); var4 != nullptr; var4 = this.chunkTaskQueue.poll()) {
         var4.release();
      }

      for (SquareUpdateTask var5 = this.squareTaskQueue.poll(); var5 != nullptr; var5 = this.squareTaskQueue.poll()) {
         var5.release();
      }

      for (IVehicleTask var6 = this.vehicleTaskQueue.poll(); var6 != nullptr; var6 = this.vehicleTaskQueue.poll()) {
         var6.release();
      }

      for (PathRequestTask var7 = this.requestTaskQueue.poll(); var7 != nullptr; var7 = this.requestTaskQueue.poll()) {
         var7.release();
      }

      while (!this.requests.empty()) {
         this.requests.removeLast().release();
      }

      while (!this.requestToMain.empty()) {
         this.requestToMain.remove().release();
      }

      for (int var8 = 0; var8 < this.vehicles.size(); var8++) {
    Vehicle var10 = this.vehicles.get(var8);
         var10.release();
      }

      for (VehicleState var11 : this.vehicleState.values()) {
         var11.release();
      }

      this.requestMap.clear();
      this.vehicles.clear();
      this.vehicleState.clear();
      this.vehicleMap.clear();
      this.cells = nullptr;
      this.thread = nullptr;
      this.rebuild = true;
   }

    void updateMain() {
    std::vector var1 = IsoWorld.instance.CurrentCell.getVehicles();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    BaseVehicle var3 = (BaseVehicle)var1.get(var2);
    VehicleState var4 = this.vehicleState.get(var3);
         if (var4 != nullptr && var4.check()) {
            this.updateVehicle(var3);
         }
      }

      for (PathFindRequest var5 = this.requestToMain.poll(); var5 != nullptr; var5 = this.requestToMain.poll()) {
         if (this.requestMap.get(var5.mover) == var5) {
            this.requestMap.remove(var5.mover);
         }

         if (!var5.cancel) {
            if (var5.path.empty()) {
               var5.finder.Failed(var5.mover);
            } else {
               var5.finder.Succeeded(var5.path, var5.mover);
            }
         }

         var5.release();
      }
   }

    void updateThread() {
      for (IChunkTask var1 = this.chunkTaskQueue.poll(); var1 != nullptr; var1 = this.chunkTaskQueue.poll()) {
         var1.execute();
         var1.release();
         this.rebuild = true;
      }

      for (SquareUpdateTask var10 = this.squareTaskQueue.poll(); var10 != nullptr; var10 = this.squareTaskQueue.poll()) {
         var10.execute();
         var10.release();
      }

      for (IVehicleTask var11 = this.vehicleTaskQueue.poll(); var11 != nullptr; var11 = this.vehicleTaskQueue.poll()) {
         var11.execute();
         var11.release();
         this.rebuild = true;
      }

      for (PathRequestTask var12 = this.requestTaskQueue.poll(); var12 != nullptr; var12 = this.requestTaskQueue.poll()) {
         var12.execute();
         var12.release();
      }

      if (this.rebuild) {
         for (int var13 = 0; var13 < this.graphs.size(); var13++) {
    VisibilityGraph var2 = this.graphs.get(var13);
            var2.release();
         }

         this.squareToNode.forEachValue(this.releaseNodeProc);
         this.createVisibilityGraphs();
         this.rebuild = false;
         ChunkDataZ.EPOCH++;
      }

    int var14 = 2;

      while (!this.requests.empty()) {
    PathFindRequest var15 = this.requests.removeFirst();
         if (var15.cancel) {
            this.requestToMain.push_back(var15);
         } else {
            try {
               this.findPath(var15, false);
            } catch (Exception var9) {
               ExceptionLogger.logException(var9);
            }

            if (!var15.targetXYZ.empty()) {
               this.shortestPath.copyFrom(var15.path);
    float var3 = var15.targetX;
    float var4 = var15.targetY;
    float var5 = var15.targetZ;
    float var6 = this.shortestPath.empty() ? float.MAX_VALUE : this.shortestPath.length();

               for (byte var7 = 0; var7 < var15.targetXYZ.size(); var7 += 3) {
                  var15.targetX = var15.targetXYZ.get(var7);
                  var15.targetY = var15.targetXYZ.get(var7 + 1);
                  var15.targetZ = var15.targetXYZ.get(var7 + 2);
                  var15.path.clear();
                  this.findPath(var15, false);
                  if (!var15.path.empty()) {
    float var8 = var15.path.length();
                     if (var8 < var6) {
                        var6 = var8;
                        this.shortestPath.copyFrom(var15.path);
                        var3 = var15.targetX;
                        var4 = var15.targetY;
                        var5 = var15.targetZ;
                     }
                  }
               }

               var15.path.copyFrom(this.shortestPath);
               var15.targetX = var3;
               var15.targetY = var4;
               var15.targetZ = var5;
            }

            this.requestToMain.push_back(var15);
            if (--var14 == 0) {
               break;
            }
         }
      }
   }

    PathFindRequest addRequest(IPathfinder var1, Mover var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.cancelRequest(var2);
    PathFindRequest var9 = PathFindRequest.alloc().init(var1, var2, var3, var4, var5, var6, var7, var8);
      this.requestMap.put(var2, var9);
    PathRequestTask var10 = PathRequestTask.alloc().init(this, var9);
      this.requestTaskQueue.push_back(var10);
      this.thread.wake();
    return var9;
   }

    void cancelRequest(Mover var1) {
    PathFindRequest var2 = this.requestMap.remove(var1);
      if (var2 != nullptr) {
         var2.cancel = true;
      }
   }

   public std::vector<Point> getPointInLine(float var1, float var2, float var3, float var4, int var5) {
    PointPool var6 = std::make_shared<PointPool>();
    std::vector var7 = new std::vector();
      this.supercover(var1, var2, var3, var4, var5, var6, var7);
    return var7;
   }

    void supercover(float var1, float var2, float var3, float var4, int var5, PointPool var6, std::vector<Point> var7) {
    double var8 = Math.abs(var3 - var1);
    double var10 = Math.abs(var4 - var2);
    int var12 = (int)Math.floor(var1);
    int var13 = (int)Math.floor(var2);
    int var14 = 1;
    uint8_t var15;
    double var17;
      if (var8 == 0.0) {
         var15 = 0;
         var17 = double.POSITIVE_INFINITY;
      } else if (var3 > var1) {
         var15 = 1;
         var14 += (int)Math.floor(var3) - var12;
         var17 = (Math.floor(var1) + 1.0 - var1) * var10;
      } else {
         var15 = -1;
         var14 += var12 - (int)Math.floor(var3);
         var17 = (var1 - Math.floor(var1)) * var10;
      }

    uint8_t var16;
      if (var10 == 0.0) {
         var16 = 0;
         var17 -= double.POSITIVE_INFINITY;
      } else if (var4 > var2) {
         var16 = 1;
         var14 += (int)Math.floor(var4) - var13;
         var17 -= (Math.floor(var2) + 1.0 - var2) * var8;
      } else {
         var16 = -1;
         var14 += var13 - (int)Math.floor(var4);
         var17 -= (var2 - Math.floor(var2)) * var8;
      }

      for (; var14 > 0; var14--) {
    Point var19 = var6.alloc().init(var12, var13);
         if (var7.contains(var19)) {
            var6.release(var19);
         } else {
            var7.push_back(var19);
         }

         if (var17 > 0.0) {
            var13 += var16;
            var17 -= var8;
         } else {
            var12 += var15;
            var17 += var10;
         }
      }
   }

    bool lineClearCollide(float var1, float var2, float var3, float var4, int var5) {
      return this.lineClearCollide(var1, var2, var3, var4, var5, nullptr);
   }

    bool lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6) {
      return this.lineClearCollide(var1, var2, var3, var4, var5, var6, true, true);
   }

    bool lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, bool var7, bool var8) {
    uint8_t var9 = 0;
      if (var7) {
         var9 |= 1;
      }

      if (var8) {
         var9 |= 2;
      }

      if (Core.bDebug && DebugOptions.instance.PolymapRenderLineClearCollide.getValue()) {
         var9 |= 8;
      }

      return this.lineClearCollide(var1, var2, var3, var4, var5, var6, var9);
   }

    bool lineClearCollide(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, int var7) {
    BaseVehicle var8 = nullptr;
      if (dynamic_cast<IsoGameCharacter*>(var6) != nullptr) {
         var8 = ((IsoGameCharacter)var6).getVehicle();
      } else if (dynamic_cast<BaseVehicle*>(var6) != nullptr) {
         var8 = (BaseVehicle)var6;
      }

      return this.lccMain.isNotClear(this, var1, var2, var3, var4, var5, var8, var7);
   }

    Vector2 getCollidepoint(float var1, float var2, float var3, float var4, int var5, IsoMovingObject var6, int var7) {
    BaseVehicle var8 = nullptr;
      if (dynamic_cast<IsoGameCharacter*>(var6) != nullptr) {
         var8 = ((IsoGameCharacter)var6).getVehicle();
      } else if (dynamic_cast<BaseVehicle*>(var6) != nullptr) {
         var8 = (BaseVehicle)var6;
      }

      return this.lccMain.getCollidepoint(this, var1, var2, var3, var4, var5, var8, var7);
   }

    bool canStandAt(float var1, float var2, int var3, IsoMovingObject var4, bool var5, bool var6) {
    BaseVehicle var7 = nullptr;
      if (dynamic_cast<IsoGameCharacter*>(var4) != nullptr) {
         var7 = ((IsoGameCharacter)var4).getVehicle();
      } else if (dynamic_cast<BaseVehicle*>(var4) != nullptr) {
         var7 = (BaseVehicle)var4;
      }

    uint8_t var8 = 0;
      if (var5) {
         var8 |= 1;
      }

      if (var6) {
         var8 |= 2;
      }

      if (Core.bDebug && DebugOptions.instance.PolymapRenderLineClearCollide.getValue()) {
         var8 |= 8;
      }

      return this.canStandAt(var1, var2, var3, var7, var8);
   }

    bool canStandAt(float var1, float var2, int var3, BaseVehicle var4, int var5) {
      return this.lccMain.canStandAtOld(this, var1, var2, var3, var4, var5);
   }

    bool intersectLineWithVehicle(float var1, float var2, float var3, float var4, BaseVehicle var5, Vector2 var6) {
      if (var5 != nullptr && var5.getScript() != nullptr) {
         float[] var7 = this.tempFloats;
         var7[0] = var5.getPoly().x1;
         var7[1] = var5.getPoly().y1;
         var7[2] = var5.getPoly().x2;
         var7[3] = var5.getPoly().y2;
         var7[4] = var5.getPoly().x3;
         var7[5] = var5.getPoly().y3;
         var7[6] = var5.getPoly().x4;
         var7[7] = var5.getPoly().y4;
    float var8 = float.MAX_VALUE;

         for (byte var9 = 0; var9 < 8; var9 += 2) {
    float var10 = var7[var9 % 8];
    float var11 = var7[(var9 + 1) % 8];
    float var12 = var7[(var9 + 2) % 8];
    float var13 = var7[(var9 + 3) % 8];
    double var14 = (var13 - var11) * (var3 - var1) - (var12 - var10) * (var4 - var2);
            if (var14 == 0.0) {
    return false;
            }

    double var16 = ((var12 - var10) * (var2 - var11) - (var13 - var11) * (var1 - var10)) / var14;
    double var18 = ((var3 - var1) * (var2 - var11) - (var4 - var2) * (var1 - var10)) / var14;
            if (var16 >= 0.0 && var16 <= 1.0 && var18 >= 0.0 && var18 <= 1.0) {
    float var20 = (float)(var1 + var16 * (var3 - var1));
    float var21 = (float)(var2 + var16 * (var4 - var2));
    float var22 = IsoUtils.DistanceTo(var1, var2, var20, var21);
               if (var22 < var8) {
                  var6.set(var20, var21);
                  var8 = var22;
               }
            }
         }

         return var8 < float.MAX_VALUE;
      } else {
    return false;
      }
   }

    Vector2f resolveCollision(IsoGameCharacter var1, float var2, float var3, Vector2f var4) {
      return GameClient.bClient && var1.isSkipResolveCollision() ? var4.set(var2, var3) : this.collideWithObstacles.resolveCollision(var1, var2, var3, var4);
   }
}
} // namespace vehicles
} // namespace zombie
