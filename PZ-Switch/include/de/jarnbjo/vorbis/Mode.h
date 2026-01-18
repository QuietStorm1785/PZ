#pragma once
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Mode {
public:
 bool blockFlag;
 int windowType;
 int transformType;
 int mapping;

protected
 Mode(BitInputStream bitInputStream, SetupHeader setupHeader) {
 this->blockFlag = bitInputStream.getBit();
 this->windowType = bitInputStream.getInt(16);
 this->transformType = bitInputStream.getInt(16);
 this->mapping = bitInputStream.getInt(8);
 if (this->windowType != 0) {
 throw VorbisFormatException("Window type = " + this->windowType +
 ", != 0");
 } else if (this->transformType != 0) {
 throw VorbisFormatException("Transform type = " + this->transformType +
 ", != 0");
 } else if (this->mapping > setupHeader.getMappings().length) {
 throw VorbisFormatException(
 "Mode mapping number is higher than total number of mappings.");
 }
 }

 bool getBlockFlag() { return this->blockFlag; }

 int getWindowType() { return this->windowType; }

 int getTransformType() { return this->transformType; }

 int getMapping() { return this->mapping; }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
