#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace util {
namespace io {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ByteArrayBitInputStream {
public:
 private byte[] source;
 uint8_t currentByte;
 int endian;
 int byteIndex = 0;
 int bitIndex = 0;

 public ByteArrayBitInputStream(byte[] bytes) {
 this(bytes, 0);
 }

 public ByteArrayBitInputStream(byte[] bytes, int int0) {
 this->endian = int0;
 this->source = bytes;
 this->currentByte = bytes[0];
 this->bitIndex = int0 == 0 ? 0 : 7;
 }

 bool getBit() {
 if (this->endian == 0) {
 if (this->bitIndex > 7) {
 this->bitIndex = 0;
 this->currentByte = this->source[++this->byteIndex];
 }

 return (this->currentByte & 1 << this->bitIndex++) != 0;
 } else {
 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->currentByte = this->source[++this->byteIndex];
 }

 return (this->currentByte & 1 << this->bitIndex--) != 0;
 }
 }

 int getInt(int int0) {
 if (int0 > 32) {
 throw IllegalArgumentException("Argument \"bits\" must be <= 32");
 } else {
 int int1 = 0;
 if (this->endian == 0) {
 for (int int2 = 0; int2 < int0; int2++) {
 if (this->getBit()) {
 int1 |= 1 << int2;
 }
 }
 } else {
 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->currentByte = this->source[++this->byteIndex];
 }

 if (int0 <= this->bitIndex + 1) {
 int int3 = this->currentByte & 255;
 int int4 = 1 + this->bitIndex - int0;
 int int5 = (1 << int0) - 1 << int4;
 int1 = (int3 & int5) >> int4;
 this->bitIndex -= int0;
 } else {
 int1 = (this->currentByte & 255 & (1 << this->bitIndex + 1) - 1) << int0 - this->bitIndex - 1;
 int0 -= this->bitIndex + 1;

 for (this->currentByte = this->source[++this->byteIndex]; int0 >= 8; this->currentByte = this->source[++this->byteIndex]) {
 int0 -= 8;
 int1 |= (this->source[this->byteIndex] & 255) << int0;
 }

 if (int0 > 0) {
 int int6 = this->source[this->byteIndex] & 255;
 int1 |= int6 >> 8 - int0 & (1 << int0) - 1;
 this->bitIndex = 7 - int0;
 } else {
 this->currentByte = this->source[--this->byteIndex];
 this->bitIndex = -1;
 }
 }
 }

 return int1;
 }
 }

 int getSignedInt(int int1) {
 int int0 = this->getInt(int1);
 if (int0 >= 1 << int1 - 1) {
 int0 -= 1 << int1;
 }

 return int0;
 }

 int getInt(HuffmanNode huffmanNode) {
 while (huffmanNode.value == nullptr) {
 if (this->bitIndex > 7) {
 this->bitIndex = 0;
 this->currentByte = this->source[++this->byteIndex];
 }

 huffmanNode = (this->currentByte & 1 << this->bitIndex++) != 0 ? huffmanNode.o1 : huffmanNode.o0;
 }

 return huffmanNode.value;
 }

 long getLong(int int0) {
 if (int0 > 64) {
 throw IllegalArgumentException("Argument \"bits\" must be <= 64");
 } else {
 long long0 = 0L;
 if (this->endian == 0) {
 for (int int1 = 0; int1 < int0; int1++) {
 if (this->getBit()) {
 long0 |= 1L << int1;
 }
 }
 } else {
 for (int int2 = int0 - 1; int2 >= 0; int2--) {
 if (this->getBit()) {
 long0 |= 1L << int2;
 }
 }
 }

 return long0;
 }
 }

 int readSignedRice(int int3) {
 int int0 = -1;
 int int1 = 0;
 int int2 = 0;
 if (this->endian == 0) {
 throw UnsupportedOperationException("ByteArrayBitInputStream.readSignedRice() is only supported in big endian mode");
 } else {
 uint8_t byte0 = this->source[this->byteIndex];

 do {
 int0++;
 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->byteIndex++;
 byte0 = this->source[this->byteIndex];
 }
 } while ((byte0 & 1 << this->bitIndex--) == 0);

 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->byteIndex++;
 }

 if (int3 <= this->bitIndex + 1) {
 int int4 = this->source[this->byteIndex] & 255;
 int int5 = 1 + this->bitIndex - int3;
 int int6 = (1 << int3) - 1 << int5;
 int1 = (int4 & int6) >> int5;
 this->bitIndex -= int3;
 } else {
 int1 = (this->source[this->byteIndex] & 255 & (1 << this->bitIndex + 1) - 1) << int3 - this->bitIndex - 1;
 int int7 = int3 - (this->bitIndex + 1);
 this->byteIndex++;

 while (int7 >= 8) {
 int7 -= 8;
 int1 |= (this->source[this->byteIndex] & 255) << int7;
 this->byteIndex++;
 }

 if (int7 > 0) {
 int int8 = this->source[this->byteIndex] & 255;
 int1 |= int8 >> 8 - int7 & (1 << int7) - 1;
 this->bitIndex = 7 - int7;
 } else {
 this->byteIndex--;
 this->bitIndex = -1;
 }
 }

 int2 = int0 << int3 | int1;
 return (int2 & 1) == 1 ? -(int2 >> 1) - 1 : int2 >> 1;
 }
 }

 void readSignedRice(int int5, int[] ints, int int1, int int2) {
 if (this->endian == 0) {
 throw UnsupportedOperationException("ByteArrayBitInputStream.readSignedRice() is only supported in big endian mode");
 } else {
 for (int int0 = int1; int0 < int1 + int2; int0++) {
 int int3 = -1;
 int int4 = 0;
 uint8_t byte0 = this->source[this->byteIndex];

 do {
 int3++;
 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->byteIndex++;
 byte0 = this->source[this->byteIndex];
 }
 } while ((byte0 & 1 << this->bitIndex--) == 0);

 if (this->bitIndex < 0) {
 this->bitIndex = 7;
 this->byteIndex++;
 }

 if (int5 <= this->bitIndex + 1) {
 int int6 = this->source[this->byteIndex] & 255;
 int int7 = 1 + this->bitIndex - int5;
 int int8 = (1 << int5) - 1 << int7;
 int4 = (int6 & int8) >> int7;
 this->bitIndex -= int5;
 } else {
 int4 = (this->source[this->byteIndex] & 255 & (1 << this->bitIndex + 1) - 1) << int5 - this->bitIndex - 1;
 int int9 = int5 - (this->bitIndex + 1);
 this->byteIndex++;

 while (int9 >= 8) {
 int9 -= 8;
 int4 |= (this->source[this->byteIndex] & 255) << int9;
 this->byteIndex++;
 }

 if (int9 > 0) {
 int int10 = this->source[this->byteIndex] & 255;
 int4 |= int10 >> 8 - int9 & (1 << int9) - 1;
 this->bitIndex = 7 - int9;
 } else {
 this->byteIndex--;
 this->bitIndex = -1;
 }
 }

 int int11 = int3 << int5 | int4;
 ints[int0] = (int11 & 1) == 1 ? -(int11 >> 1) - 1 : int11 >> 1;
 }
 }
 }

 void align() {
 if (this->endian == 1 && this->bitIndex >= 0) {
 this->bitIndex = 7;
 this->byteIndex++;
 } else if (this->endian == 0 && this->bitIndex <= 7) {
 this->bitIndex = 0;
 this->byteIndex++;
 }
 }

 void setEndian(int int0) {
 if (this->endian == 1 && int0 == 0) {
 this->bitIndex = 0;
 this->byteIndex++;
 } else if (this->endian == 0 && int0 == 1) {
 this->bitIndex = 7;
 this->byteIndex++;
 }

 this->endian = int0;
 }

 public byte[] getSource() {
 return this->source;
 }
}
} // namespace io
} // namespace util
} // namespace jarnbjo
} // namespace de
