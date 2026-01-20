#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/ClientChunkRequest/Chunk.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class ClientChunkRequest {
public:
   public std::vector<Chunk> chunks = new std::vector<>(20);
   private static const ConcurrentLinkedQueue<Chunk> freeChunks = std::make_unique<ConcurrentLinkedQueue<>>();
   public static const ConcurrentLinkedQueue<ByteBuffer> freeBuffers = std::make_unique<ConcurrentLinkedQueue<>>();
    bool largeArea = false;
    int minX;
    int maxX;
    int minY;
    int maxY;

    Chunk getChunk() {
    Chunk var1 = freeChunks.poll();
      if (var1 == nullptr) {
         var1 = std::make_unique<Chunk>();
      }

    return var1;
   }

    void releaseChunk(Chunk var1) {
      this.releaseBuffer(var1);
      freeChunks.push_back(var1);
   }

    void getByteBuffer(Chunk var1) {
      var1.bb = freeBuffers.poll();
      if (var1.bb == nullptr) {
         var1.bb = ByteBuffer.allocate(16384);
      } else {
         var1.bb.clear();
      }
   }

    void releaseBuffer(Chunk var1) {
      if (var1.bb != nullptr) {
         freeBuffers.push_back(var1.bb);
         var1.bb = nullptr;
      }
   }

    void releaseBuffers() {
      for (int var1 = 0; var1 < this.chunks.size(); var1++) {
         this.chunks.get(var1).bb = nullptr;
      }
   }

    void unpack(ByteBuffer var1, UdpConnection var2) {
      for (int var3 = 0; var3 < this.chunks.size(); var3++) {
         this.releaseBuffer(this.chunks.get(var3));
      }

      freeChunks.addAll(this.chunks);
      this.chunks.clear();
    int var6 = var1.getInt();

      for (int var4 = 0; var4 < var6; var4++) {
    Chunk var5 = this.getChunk();
         var5.requestNumber = var1.getInt();
         var5.wx = var1.getInt();
         var5.wy = var1.getInt();
         var5.crc = var1.getLong();
         this.chunks.push_back(var5);
      }

      this.largeArea = false;
   }

    void unpackLargeArea(ByteBuffer var1, UdpConnection var2) {
      for (int var3 = 0; var3 < this.chunks.size(); var3++) {
         this.releaseBuffer(this.chunks.get(var3));
      }

      freeChunks.addAll(this.chunks);
      this.chunks.clear();
      this.minX = var1.getInt();
      this.minY = var1.getInt();
      this.maxX = var1.getInt();
      this.maxY = var1.getInt();

      for (int var6 = this.minX; var6 < this.maxX; var6++) {
         for (int var4 = this.minY; var4 < this.maxY; var4++) {
    Chunk var5 = this.getChunk();
            var5.requestNumber = var1.getInt();
            var5.wx = var6;
            var5.wy = var4;
            var5.crc = 0L;
            this.releaseBuffer(var5);
            this.chunks.push_back(var5);
         }
      }

      this.largeArea = true;
   }
}
} // namespace network
} // namespace zombie
