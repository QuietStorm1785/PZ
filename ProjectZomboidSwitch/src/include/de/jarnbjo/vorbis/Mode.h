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


class Mode {
public:
    bool blockFlag;
    int windowType;
    int transformType;
    int mapping;

    protected Mode(BitInputStream var1, SetupHeader var2) {
      this.blockFlag = var1.getBit();
      this.windowType = var1.getInt(16);
      this.transformType = var1.getInt(16);
      this.mapping = var1.getInt(8);
      if (this.windowType != 0) {
         throw VorbisFormatException("Window type = " + this.windowType + ", != 0");
      } else if (this.transformType != 0) {
         throw VorbisFormatException("Transform type = " + this.transformType + ", != 0");
      } else if (this.mapping > var2.getMappings().length) {
         throw VorbisFormatException("Mode mapping number is higher than total number of mappings.");
      }
   }

    bool getBlockFlag() {
      return this.blockFlag;
   }

    int getWindowType() {
      return this.windowType;
   }

    int getTransformType() {
      return this.transformType;
   }

    int getMapping() {
      return this.mapping;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
