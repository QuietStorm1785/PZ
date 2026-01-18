#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class StateMachine {
public:
 static const int STATE_START = 0;
 static const int STATE_SAW_IHDR = 1;
 static const int STATE_SAW_IHDR_NO_PLTE = 2;
 static const int STATE_SAW_PLTE = 3;
 static const int STATE_IN_IDAT = 4;
 static const int STATE_AFTER_IDAT = 5;
 static const int STATE_END = 6;
 PngImage png;
 int state = 0;
 int type;

public
 StateMachine(PngImage pngImage) { this->png = pngImage; }

 int getState() { return this->state; }

 int getType() { return this->type; }

 void nextState(int int0) {
 this->state = nextState(this->png, this->state, this->type = int0);
 }

 static int nextState(PngImage pngImage, int int3, int int2) {
 for (int int0 = 0; int0 < 4; int0++) {
 int int1 = 0xFF & int2 >>> 8 * int0;
 if (int1 < 65 || int1 > 90 && int1 < 97 || int1 > 122) {
 throw PngException(
 "Corrupted chunk type: 0x" + Integer.toHexString(int2), true);
 }
 }

 if (PngConstants.isPrivate(int2) && !PngConstants.isAncillary(int2) {
 throw PngException("Private critical chunk encountered: " +
 PngConstants.getChunkName(int2),
 true);
 } else {
 switch (int3) {
 case 0:
 if (int2 == 1229472850) {
 return 1;
 }

 throw PngException("IHDR chunk must be first chunk", true);
 case 1:
 case 2:
 switch (int2) {
 case 1229209940:
 errorIfPaletted(pngImage);
 return 4;
 case 1347179589:
 return 3;
 case 1649100612:
 return 2;
 case 1749635924:
 throw PngException("PLTE must precede hIST", true);
 case 1951551059:
 errorIfPaletted(pngImage);
 return 2;
 default:
 return int3;
 }
 case 3:
 switch (int2) {
 case 1229209940:
 return 4;
 case 1229278788:
 throw PngException("Required data chunk(s) not found", true);
 case 1665684045:
 case 1732332865:
 case 1766015824:
 case 1933723988:
 case 1934772034:
 throw PngException(PngConstants.getChunkName(int2) +
 " cannot appear after PLTE",
 true);
 default:
 return 3;
 }
 default:
 switch (int2) {
 case 1229209940:
 if (int3 == 4) {
 return 4;
 }

 throw PngException("IDAT chunks must be consecutive", true);
 case 1229278788:
 return 6;
 case 1347179589:
 case 1649100612:
 case 1665684045:
 case 1732332865:
 case 1749635924:
 case 1766015824:
 case 1866876531:
 case 1883455820:
 case 1883789683:
 case 1933723988:
 case 1933787468:
 case 1934642260:
 case 1934772034:
 case 1934902610:
 case 1951551059:
 throw PngException(PngConstants.getChunkName(int2) +
 " cannot appear after IDAT",
 true);
 default:
 return 5;
 }
 }
 }
 }

 static void errorIfPaletted(PngImage pngImage) {
 if (pngImage.getColorType() == 3) {
 throw PngException("Required PLTE chunk not found", true);
 }
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
