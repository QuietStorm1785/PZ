#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Floor0 : public Floor {
public:
 int order;
 int rate;
 int barkMapSize;
 int amplitudeBits;
 int amplitudeOffset;
 private int[] bookList;

 protected Floor0(BitInputStream bitInputStream, SetupHeader setupHeader) {
 this->order = bitInputStream.getInt(8);
 this->rate = bitInputStream.getInt(16);
 this->barkMapSize = bitInputStream.getInt(16);
 this->amplitudeBits = bitInputStream.getInt(6);
 this->amplitudeOffset = bitInputStream.getInt(8);
 int int0 = bitInputStream.getInt(4) + 1;
 this->bookList = new int[int0];

 for (int int1 = 0; int1 < this->bookList.length; int1++) {
 this->bookList[int1] = bitInputStream.getInt(8);
 if (this->bookList[int1] > setupHeader.getCodeBooks().length) {
 throw VorbisFormatException("A floor0_book_list entry is higher than the code book count.");
 }
 }
 }

 int getType() {
 return 0;
 }

 Floor decodeFloor(VorbisStream var1, BitInputStream var2) {
 throw std::make_unique<UnsupportedOperationException>();
 }

 void computeFloor(float[] var1) {
 throw std::make_unique<UnsupportedOperationException>();
 }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
