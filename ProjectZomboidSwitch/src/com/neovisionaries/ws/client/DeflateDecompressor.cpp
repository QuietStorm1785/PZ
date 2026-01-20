#include "com\neovisionaries\ws\client/DeflateDecompressor.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

void DeflateDecompressor::decompress(ByteArray input, ByteArray output) {
    // TODO: Implement decompress
}

void DeflateDecompressor::decompress(ByteArray input, int index, ByteArray output) {
    // TODO: Implement decompress
}

bool DeflateDecompressor::inflateBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    // TODO: Implement inflateBlock
    return false;
}

void DeflateDecompressor::inflatePlainBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    // TODO: Implement inflatePlainBlock
}

void DeflateDecompressor::inflateFixedBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    // TODO: Implement inflateFixedBlock
}

void DeflateDecompressor::inflateDynamicBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    // TODO: Implement inflateDynamicBlock
}

void DeflateDecompressor::inflateData(ByteArray input, int[] bitIndex, ByteArray output, Huffman literalLengthHuffman, Huffman distanceHuffman) {
    // TODO: Implement inflateData
}

void DeflateDecompressor::duplicate(int length, int distance, ByteArray output) {
    // TODO: Implement duplicate
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
