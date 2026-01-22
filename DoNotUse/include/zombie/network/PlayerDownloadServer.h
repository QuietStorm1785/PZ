#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/BufferUtils.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/ClientChunkRequest/Chunk.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/PlayerDownloadServer/EThreadCommand.h"
#include "zombie/network/PlayerDownloadServer/WorkerThread.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class PlayerDownloadServer {
public:
    WorkerThread workerThread;
    const UdpConnection connection;
    bool NetworkFileDebug;
    const CRC32 crc32 = std::make_shared<CRC32>();
    const ByteBuffer bb = ByteBuffer.allocate(1000000);
    const ByteBuffer sb = BufferUtils.createByteBuffer(1000000);
    const ByteBufferWriter bbw = std::make_shared<ByteBufferWriter>(this.bb);
   private const std::vector<ClientChunkRequest> ccrWaiting = std::make_unique<std::vector<>>();

    public PlayerDownloadServer(UdpConnection var1) {
      this.connection = var1;
      this.workerThread = std::make_shared<WorkerThread>(this);
      this.workerThread.setDaemon(true);
      this.workerThread.setName("PlayerDownloadServer" + Rand.Next(int.MAX_VALUE));
      this.workerThread.start();
   }

    void destroy() {
      this.workerThread.putCommand(EThreadCommand.Quit, nullptr);

      while (this.workerThread.isAlive()) {
         try {
            Thread.sleep(10L);
         } catch (InterruptedException var2) {
         }
      }

      this.workerThread = nullptr;
   }

    void startConnectionTest() {
   }

    void receiveRequestArray(ByteBuffer var1) {
    ClientChunkRequest var2 = (ClientChunkRequest)this.workerThread.freeRequests.poll();
      if (var2 == nullptr) {
         var2 = std::make_unique<ClientChunkRequest>();
      }

      var2.largeArea = false;
      this.ccrWaiting.push_back(var2);
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         if (var2.chunks.size() >= 20) {
            var2 = (ClientChunkRequest)this.workerThread.freeRequests.poll();
            if (var2 == nullptr) {
               var2 = std::make_unique<ClientChunkRequest>();
            }

            var2.largeArea = false;
            this.ccrWaiting.push_back(var2);
         }

    Chunk var5 = var2.getChunk();
         var5.requestNumber = var1.getInt();
         var5.wx = var1.getInt();
         var5.wy = var1.getInt();
         var5.crc = var1.getLong();
         var2.chunks.push_back(var5);
      }
   }

    void receiveRequestLargeArea(ByteBuffer var1) {
    ClientChunkRequest var2 = std::make_shared<ClientChunkRequest>();
      var2.unpackLargeArea(var1, this.connection);

      for (int var3 = 0; var3 < var2.chunks.size(); var3++) {
    Chunk var4 = (Chunk)var2.chunks.get(var3);
    IsoChunk var5 = ServerMap.instance.getChunk(var4.wx, var4.wy);
         if (var5 != nullptr) {
            var2.getByteBuffer(var4);

            try {
               var5.SaveLoadedChunk(var4, this.crc32);
            } catch (Exception var7) {
               var7.printStackTrace();
               LoggerManager.getLogger("map").write(var7);
               var2.releaseBuffer(var4);
            }
         }
      }

      this.workerThread.putCommand(EThreadCommand.RequestLargeArea, var2);
   }

    void receiveCancelRequest(ByteBuffer var1) {
    int var2 = var1.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
    int var4 = var1.getInt();
         this.workerThread.cancelQ.push_back(var4);
      }
   }

    int getWaitingRequests() {
      return this.ccrWaiting.size();
   }

    void update() {
      this.NetworkFileDebug = DebugType.Do(DebugType.NetworkFileDebug);
      if (this.workerThread.bReady) {
         this.removeOlderDuplicateRequests();
         if (this.ccrWaiting.empty()) {
            if (this.workerThread.cancelQ.empty() && !this.workerThread.cancelled.empty()) {
               this.workerThread.cancelled.clear();
            }
         } else {
    ClientChunkRequest var1 = this.ccrWaiting.remove(0);

            for (int var2 = 0; var2 < var1.chunks.size(); var2++) {
    Chunk var3 = (Chunk)var1.chunks.get(var2);
               if (this.workerThread.isRequestCancelled(var3)) {
                  var1.chunks.remove(var2--);
                  var1.releaseChunk(var3);
               } else {
    IsoChunk var4 = ServerMap.instance.getChunk(var3.wx, var3.wy);
                  if (var4 != nullptr) {
                     try {
                        var1.getByteBuffer(var3);
                        var4.SaveLoadedChunk(var3, this.crc32);
                     } catch (Exception var6) {
                        var6.printStackTrace();
                        LoggerManager.getLogger("map").write(var6);
                        this.workerThread.sendNotRequired(var3, false);
                        var1.chunks.remove(var2--);
                        var1.releaseChunk(var3);
                     }
                  }
               }
            }

            if (var1.chunks.empty()) {
               this.workerThread.freeRequests.push_back(var1);
            } else {
               this.workerThread.bReady = false;
               this.workerThread.putCommand(EThreadCommand.RequestZipArray, var1);
            }
         }
      }
   }

    void removeOlderDuplicateRequests() {
      for (int var1 = this.ccrWaiting.size() - 1; var1 >= 0; var1--) {
    ClientChunkRequest var2 = this.ccrWaiting.get(var1);

         for (int var3 = 0; var3 < var2.chunks.size(); var3++) {
    Chunk var4 = (Chunk)var2.chunks.get(var3);
            if (this.workerThread.isRequestCancelled(var4)) {
               var2.chunks.remove(var3--);
               var2.releaseChunk(var4);
            } else {
               for (int var5 = var1 - 1; var5 >= 0; var5--) {
    ClientChunkRequest var6 = this.ccrWaiting.get(var5);
                  if (this.cancelDuplicateChunk(var6, var4.wx, var4.wy)) {
                  }
               }
            }
         }

         if (var2.chunks.empty()) {
            this.ccrWaiting.remove(var1);
            this.workerThread.freeRequests.push_back(var2);
         }
      }
   }

    bool cancelDuplicateChunk(ClientChunkRequest var1, int var2, int var3) {
      for (int var4 = 0; var4 < var1.chunks.size(); var4++) {
    Chunk var5 = (Chunk)var1.chunks.get(var4);
         if (this.workerThread.isRequestCancelled(var5)) {
            var1.chunks.remove(var4--);
            var1.releaseChunk(var5);
         } else if (var5.wx == var2 && var5.wy == var3) {
            this.workerThread.sendNotRequired(var5, false);
            var1.chunks.remove(var4);
            var1.releaseChunk(var5);
    return true;
         }
      }

    return false;
   }

    void sendPacket(PacketType var1) {
      this.bb.flip();
      this.sb.put(this.bb);
      this.sb.flip();
      this.connection.getPeer().SendRaw(this.sb, var1.PacketPriority, var1.PacketReliability, (byte)0, this.connection.getConnectedGUID(), false);
      this.sb.clear();
   }

    ByteBufferWriter startPacket() {
      this.bb.clear();
      return this.bbw;
   }
}
} // namespace network
} // namespace zombie
