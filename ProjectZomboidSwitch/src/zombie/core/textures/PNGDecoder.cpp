#include <cstdint>
#include "zombie/core/textures/PNGDecoder.h"

namespace zombie {
namespace core {
namespace textures {

public PNGDecoder::PNGDecoder(InputStream var1, bool var2) {
    // TODO: Implement PNGDecoder
    return nullptr;
}

int PNGDecoder::getHeight() {
    // TODO: Implement getHeight
    return 0;
}

int PNGDecoder::getWidth() {
    // TODO: Implement getWidth
    return 0;
}

bool PNGDecoder::hasAlphaChannel() {
    // TODO: Implement hasAlphaChannel
    return false;
}

bool PNGDecoder::hasAlpha() {
    // TODO: Implement hasAlpha
    return false;
}

bool PNGDecoder::isRGB() {
    // TODO: Implement isRGB
    return false;
}

void PNGDecoder::overwriteTRNS(uint8_t var1, uint8_t var2, uint8_t var3) {
    // TODO: Implement overwriteTRNS
}

Format PNGDecoder::decideTextureFormat(Format var1) {
    // TODO: Implement decideTextureFormat
    return nullptr;
}

void PNGDecoder::decode(ByteBuffer var1, int var2, Format var3) {
    // TODO: Implement decode
}

void PNGDecoder::decodeFlipped(ByteBuffer var1, int var2, Format var3) {
    // TODO: Implement decodeFlipped
}

void PNGDecoder::copy(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copy
}

void PNGDecoder::copyRGBtoABGR(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBtoABGR
}

void PNGDecoder::copyRGBtoRGBA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBtoRGBA
}

void PNGDecoder::copyRGBtoBGRA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBtoBGRA
}

void PNGDecoder::copyRGBAtoABGR(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBAtoABGR
}

void PNGDecoder::copyRGBAtoBGRA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBAtoBGRA
}

void PNGDecoder::copyRGBAtoRGB(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyRGBAtoRGB
}

void PNGDecoder::copyPALtoABGR(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyPALtoABGR
}

void PNGDecoder::copyPALtoRGBA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyPALtoRGBA
}

void PNGDecoder::copyPALtoBGRA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyPALtoBGRA
}

void PNGDecoder::copyGREYtoRGBA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyGREYtoRGBA
}

void PNGDecoder::copyGREYALPHAtoRGBA(ByteBuffer var1, byte[] var2) {
    // TODO: Implement copyGREYALPHAtoRGBA
}

void PNGDecoder::expand4(byte[] var1, byte[] var2) {
    // TODO: Implement expand4
}

void PNGDecoder::expand2(byte[] var1, byte[] var2) {
    // TODO: Implement expand2
}

void PNGDecoder::expand1(byte[] var1, byte[] var2) {
    // TODO: Implement expand1
}

void PNGDecoder::unfilter(byte[] var1, byte[] var2) {
    // TODO: Implement unfilter
}

void PNGDecoder::unfilterSub(byte[] var1) {
    // TODO: Implement unfilterSub
}

void PNGDecoder::unfilterUp(byte[] var1, byte[] var2) {
    // TODO: Implement unfilterUp
}

void PNGDecoder::unfilterAverage(byte[] var1, byte[] var2) {
    // TODO: Implement unfilterAverage
}

void PNGDecoder::unfilterPaeth(byte[] var1, byte[] var2) {
    // TODO: Implement unfilterPaeth
}

void PNGDecoder::readIHDR() {
    // TODO: Implement readIHDR
}

void PNGDecoder::readPLTE() {
    // TODO: Implement readPLTE
}

void PNGDecoder::readtRNS() {
    // TODO: Implement readtRNS
}

void PNGDecoder::closeChunk() {
    // TODO: Implement closeChunk
}

void PNGDecoder::openChunk() {
    // TODO: Implement openChunk
}

void PNGDecoder::openChunk(int var1) {
    // TODO: Implement openChunk
}

void PNGDecoder::checkChunkLength(int var1) {
    // TODO: Implement checkChunkLength
}

int PNGDecoder::readChunk(byte[] var1, int var2, int var3) {
    // TODO: Implement readChunk
    return 0;
}

void PNGDecoder::refillInflater(Inflater var1) {
    // TODO: Implement refillInflater
}

void PNGDecoder::readChunkUnzip(Inflater var1, byte[] var2, int var3, int var4) {
    // TODO: Implement readChunkUnzip
}

void PNGDecoder::readFully(byte[] var1, int var2, int var3) {
    // TODO: Implement readFully
}

int PNGDecoder::readInt(byte[] var1, int var2) {
    // TODO: Implement readInt
    return 0;
}

void PNGDecoder::skip(long var1) {
    // TODO: Implement skip
}

bool PNGDecoder::checkSignature(byte[] var0) {
    // TODO: Implement checkSignature
    return false;
}

} // namespace textures
} // namespace core
} // namespace zombie
