#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClientChunkRequest {
public:
 public ArrayList<ClientChunkRequest.Chunk> chunks = new ArrayList<>(20);
 private static ConcurrentLinkedQueue<ClientChunkRequest.Chunk> freeChunks = std::make_unique<ConcurrentLinkedQueue<>>();
 public static ConcurrentLinkedQueue<ByteBuffer> freeBuffers = std::make_unique<ConcurrentLinkedQueue<>>();
 bool largeArea = false;
 int minX;
 int maxX;
 int minY;
 int maxY;

 public ClientChunkRequest.Chunk getChunk() {
 ClientChunkRequest.Chunk chunk = freeChunks.poll();
 if (chunk == nullptr) {
 chunk = new ClientChunkRequest.Chunk();
 }

 return chunk;
 }

 void releaseChunk(ClientChunkRequest.Chunk chunk) {
 this->releaseBuffer(chunk);
 freeChunks.add(chunk);
 }

 void getByteBuffer(ClientChunkRequest.Chunk chunk) {
 chunk.bb = freeBuffers.poll();
 if (chunk.bb == nullptr) {
 chunk.bb = ByteBuffer.allocate(16384);
 } else {
 chunk.bb.clear();
 }
 }

 void releaseBuffer(ClientChunkRequest.Chunk chunk) {
 if (chunk.bb != nullptr) {
 freeBuffers.add(chunk.bb);
 chunk.bb = nullptr;
 }
 }

 void releaseBuffers() {
 for (int int0 = 0; int0 < this->chunks.size(); int0++) {
 this->chunks.get(int0).bb = nullptr;
 }
 }

 void unpack(ByteBuffer bb, UdpConnection connection) {
 for (int int0 = 0; int0 < this->chunks.size(); int0++) {
 this->releaseBuffer(this->chunks.get(int0);
 }

 freeChunks.addAll(this->chunks);
 this->chunks.clear();
 int int1 = bb.getInt();

 for (int int2 = 0; int2 < int1; int2++) {
 ClientChunkRequest.Chunk chunk = this->getChunk();
 chunk.requestNumber = bb.getInt();
 chunk.wx = bb.getInt();
 chunk.wy = bb.getInt();
 chunk.crc = bb.getLong();
 this->chunks.add(chunk);
 }

 this->largeArea = false;
 }

 void unpackLargeArea(ByteBuffer bb, UdpConnection connection) {
 for (int int0 = 0; int0 < this->chunks.size(); int0++) {
 this->releaseBuffer(this->chunks.get(int0);
 }

 freeChunks.addAll(this->chunks);
 this->chunks.clear();
 this->minX = bb.getInt();
 this->minY = bb.getInt();
 this->maxX = bb.getInt();
 this->maxY = bb.getInt();

 for (int int1 = this->minX; int1 < this->maxX; int1++) {
 for (int int2 = this->minY; int2 < this->maxY; int2++) {
 ClientChunkRequest.Chunk chunk = this->getChunk();
 chunk.requestNumber = bb.getInt();
 chunk.wx = int1;
 chunk.wy = int2;
 chunk.crc = 0L;
 this->releaseBuffer(chunk);
 this->chunks.add(chunk);
 }
 }

 this->largeArea = true;
 }

 public static class Chunk {
 int requestNumber;
 int wx;
 int wy;
 long crc;
 ByteBuffer bb;
 }
}
} // namespace network
} // namespace zombie
