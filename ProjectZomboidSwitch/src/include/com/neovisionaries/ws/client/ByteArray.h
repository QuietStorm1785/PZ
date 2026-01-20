#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ByteArray {
public:
    static const int ADDITIONAL_BUFFER_SIZE = 1024;
    ByteBuffer mBuffer;
    int mLength;

    public ByteArray(int capacity) {
      this.mBuffer = ByteBuffer.allocate(capacity);
      this.mLength = 0;
   }

    public ByteArray(byte[] data) {
      this.mBuffer = ByteBuffer.wrap(data);
      this.mLength = data.length;
   }

    int length() {
      return this.mLength;
   }

    uint8_t get(int index) {
      if (index >= 0 && this.mLength > index) {
         return this.mBuffer.get(index);
      } else {
         throw IndexOutOfBoundsException(std::string.format("Bad index: index=%d, length=%d", index, this.mLength));
      }
   }

    void expandBuffer(int newBufferSize) {
    ByteBuffer newBuffer = ByteBuffer.allocate(newBufferSize);
    int oldPosition = this.mBuffer.position();
      ((Buffer)this.mBuffer).position(0);
      newBuffer.put(this.mBuffer);
      ((Buffer)newBuffer).position(oldPosition);
      this.mBuffer = newBuffer;
   }

    void put(int data) {
      if (this.mBuffer.capacity() < this.mLength + 1) {
         this.expandBuffer(this.mLength + 1024);
      }

      this.mBuffer.put((byte)data);
      this.mLength++;
   }

    void put(byte[] source) {
      if (this.mBuffer.capacity() < this.mLength + source.length) {
         this.expandBuffer(this.mLength + source.length + 1024);
      }

      this.mBuffer.put(source);
      this.mLength += source.length;
   }

    void put(byte[] source, int index, int length) {
      if (this.mBuffer.capacity() < this.mLength + length) {
         this.expandBuffer(this.mLength + length + 1024);
      }

      this.mBuffer.put(source, index, length);
      this.mLength += length;
   }

    void put(ByteArray source, int index, int length) {
      this.put(source.mBuffer.array(), index, length);
   }

   public byte[] toBytes() {
      return this.toBytes(0);
   }

   public byte[] toBytes(int beginIndex) {
      return this.toBytes(beginIndex, this.length());
   }

   public byte[] toBytes(int beginIndex, int endIndex) {
    int len = endIndex - beginIndex;
      if (len >= 0 && beginIndex >= 0 && this.mLength >= endIndex) {
         byte[] bytes = new byte[len];
         if (len != 0) {
            System.arraycopy(this.mBuffer.array(), beginIndex, bytes, 0, len);
         }

    return bytes;
      } else {
         throw IllegalArgumentException(std::string.format("Bad range: beginIndex=%d, endIndex=%d, length=%d", beginIndex, endIndex, this.mLength));
      }
   }

    void clear() {
      ((Buffer)this.mBuffer).clear();
      ((Buffer)this.mBuffer).position(0);
      this.mLength = 0;
   }

    void shrink(int size) {
      if (this.mBuffer.capacity() > size) {
    int endIndex = this.mLength;
    int beginIndex = this.mLength - size;
         byte[] bytes = this.toBytes(beginIndex, endIndex);
         this.mBuffer = ByteBuffer.wrap(bytes);
         ((Buffer)this.mBuffer).position(bytes.length);
         this.mLength = bytes.length;
      }
   }

    bool getBit(int bitIndex) {
    int index = bitIndex / 8;
    int shift = bitIndex % 8;
    int value = this.get(index);
      return (value & 1 << shift) != 0;
   }

    int getBits(int bitIndex, int nBits) {
    int number = 0;
    int weight = 1;

      for (int i = 0; i < nBits; weight *= 2) {
         if (this.getBit(bitIndex + i)) {
            number += weight;
         }

         i++;
      }

    return number;
   }

    int getHuffmanBits(int bitIndex, int nBits) {
    int number = 0;
    int weight = 1;

      for (int i = nBits - 1; 0 <= i; weight *= 2) {
         if (this.getBit(bitIndex + i)) {
            number += weight;
         }

         i--;
      }

    return number;
   }

    bool readBit(int[] bitIndex) {
    bool result = this.getBit(bitIndex[0]);
      bitIndex[0]++;
    return result;
   }

    int readBits(int[] bitIndex, int nBits) {
    int number = this.getBits(bitIndex[0], nBits);
      bitIndex[0] += nBits;
    return number;
   }

    void setBit(int bitIndex, bool bit) {
    int index = bitIndex / 8;
    int shift = bitIndex % 8;
    int value = this.get(index);
      if (bit) {
         value |= 1 << shift;
      } else {
         value &= ~(1 << shift);
      }

      this.mBuffer.put(index, (byte)value);
   }

    void clearBit(int bitIndex) {
      this.setBit(bitIndex, false);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
