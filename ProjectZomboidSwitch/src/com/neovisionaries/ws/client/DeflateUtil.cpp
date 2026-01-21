#include "com/neovisionaries/ws/client/DeflateUtil.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

void DeflateUtil::readDynamicTables(ByteArray input, int[] bitIndex, Huffman[] tables) {
    // TODO: Implement readDynamicTables
}

void DeflateUtil::readCodeLengths(ByteArray input, int[] bitIndex, int[] codeLengths, Huffman codeLengthHuffman) {
    // TODO: Implement readCodeLengths
}

int DeflateUtil::codeLengthOrderToIndex(int order) {
    // TODO: Implement codeLengthOrderToIndex
    return 0;
}

int DeflateUtil::readLength(ByteArray input, int[] bitIndex, int literalLength) {
    // TODO: Implement readLength
    return 0;
}

int DeflateUtil::readDistance(ByteArray input, int[] bitIndex, Huffman distanceHuffman) {
    // TODO: Implement readDistance
    return 0;
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
