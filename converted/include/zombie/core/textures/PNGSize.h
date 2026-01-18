#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PNGSize {
public:
 private static byte[] SIGNATURE = new byte[]{-119, 80, 78, 71, 13, 10, 26, 10};
 static const int IHDR = 1229472850;
 int width;
 int height;
 int bitdepth;
 int colorType;
 int bytesPerPixel;
 InputStream input;
 const CRC32 crc = new CRC32();
 private byte[] buffer = new byte[4096];
 int chunkLength;
 int chunkType;
 int chunkRemaining;

 void readSize(const std::string& string) {
 try (
 FileInputStream fileInputStream = new FileInputStream(string);
 BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
 ) {
 this->readSize(bufferedInputStream);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void readSize(InputStream inputStream) {
 this->input = inputStream;
 this->readFully(this->buffer, 0, SIGNATURE.length);
 if (!this->checkSignature(this->buffer) {
 throw IOException("Not a valid PNG file");
 } else {
 this->openChunk(1229472850);
 this->readIHDR();
 this->closeChunk();
 }
 }

 void readIHDR() {
 this->checkChunkLength(13);
 this->readChunk(this->buffer, 0, 13);
 this->width = this->readInt(this->buffer, 0);
 this->height = this->readInt(this->buffer, 4);
 this->bitdepth = this->buffer[8] & 255;
 this->colorType = this->buffer[9] & 255;
 }

 void openChunk() {
 this->readFully(this->buffer, 0, 8);
 this->chunkLength = this->readInt(this->buffer, 0);
 this->chunkType = this->readInt(this->buffer, 4);
 this->chunkRemaining = this->chunkLength;
 this->crc.reset();
 this->crc.update(this->buffer, 4, 4);
 }

 void openChunk(int int0) {
 this->openChunk();
 if (this->chunkType != int0) {
 throw IOException("Expected chunk: " + Integer.toHexString(int0);
 }
 }

 void closeChunk() {
 if (this->chunkRemaining > 0) {
 this->skip(this->chunkRemaining + 4);
 } else {
 this->readFully(this->buffer, 0, 4);
 int int0 = this->readInt(this->buffer, 0);
 int int1 = (int)this->crc.getValue();
 if (int1 != int0) {
 throw IOException("Invalid CRC");
 }
 }

 this->chunkRemaining = 0;
 this->chunkLength = 0;
 this->chunkType = 0;
 }

 void checkChunkLength(int int0) {
 if (this->chunkLength != int0) {
 throw IOException("Chunk has wrong size");
 }
 }

 int readChunk(byte[] bytes, int int1, int int0) {
 if (int0 > this->chunkRemaining) {
 int0 = this->chunkRemaining;
 }

 this->readFully(bytes, int1, int0);
 this->crc.update(bytes, int1, int0);
 this->chunkRemaining -= int0;
 return int0;
 }

 void readFully(byte[] bytes, int int1, int int2) {
 do {
 int int0 = this->input.read(bytes, int1, int2);
 if (int0 < 0) {
 throw std::make_unique<EOFException>();
 }

 int1 += int0;
 int2 -= int0;
 } while (int2 > 0);
 }

 int readInt(byte[] bytes, int int0) {
 return bytes[int0] << 24 | (bytes[int0 + 1] & 0xFF) << 16 | (bytes[int0 + 2] & 0xFF) << 8 | bytes[int0 + 3] & 0xFF;
 }

 void skip(long long0) {
 while (long0 > 0L) {
 long long1 = this->input.skip(long0);
 if (long1 < 0L) {
 throw std::make_unique<EOFException>();
 }

 long0 -= long1;
 }
 }

 bool checkSignature(byte[] bytes) {
 for (int int0 = 0; int0 < SIGNATURE.length; int0++) {
 if (bytes[int0] != SIGNATURE[int0]) {
 return false;
 }
 }

 return true;
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
