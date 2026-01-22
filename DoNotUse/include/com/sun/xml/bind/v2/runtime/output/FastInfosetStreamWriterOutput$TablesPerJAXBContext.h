#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class FastInfosetStreamWriterOutput {
public:
   const int[] elementIndexes;
   const int[] elementIndexPrefixes;
   const int[] attributeIndexes;
   const int[] localNameIndexes;
    int indexOffset;
    int maxIndex;
    bool requiresClear;

   FastInfosetStreamWriterOutput$TablesPerJAXBContext(JAXBContextImpl context, int initialIndexOffset) {
      this.elementIndexes = new int[context.getNumberOfElementNames()];
      this.elementIndexPrefixes = new int[context.getNumberOfElementNames()];
      this.attributeIndexes = new int[context.getNumberOfAttributeNames()];
      this.localNameIndexes = new int[context.getNumberOfLocalNames()];
      this.indexOffset = 1;
      this.maxIndex = initialIndexOffset + this.elementIndexes.length + this.attributeIndexes.length;
   }

    void requireClearTables() {
      this.requiresClear = true;
   }

    void clearOrResetTables(int intialIndexOffset) {
      if (this.requiresClear) {
         this.requiresClear = false;
         this.indexOffset = this.indexOffset + this.maxIndex;
         this.maxIndex = intialIndexOffset + this.elementIndexes.length + this.attributeIndexes.length;
         if (this.indexOffset + this.maxIndex < 0) {
            this.clearAll();
         }
      } else {
         this.maxIndex = intialIndexOffset + this.elementIndexes.length + this.attributeIndexes.length;
         if (this.indexOffset + this.maxIndex < 0) {
            this.resetAll();
         }
      }
   }

    void clearAll() {
      this.clear(this.elementIndexes);
      this.clear(this.attributeIndexes);
      this.clear(this.localNameIndexes);
      this.indexOffset = 1;
   }

    void clear(int[] array) {
      for (int i = 0; i < array.length; i++) {
         array[i] = 0;
      }
   }

    void incrementMaxIndexValue() {
      this.maxIndex++;
      if (this.indexOffset + this.maxIndex < 0) {
         this.resetAll();
      }
   }

    void resetAll() {
      this.clear(this.elementIndexes);
      this.clear(this.attributeIndexes);
      this.clear(this.localNameIndexes);
      this.indexOffset = 1;
   }

    void reset(int[] array) {
      for (int i = 0; i < array.length; i++) {
         if (array[i] > this.indexOffset) {
            array[i] = array[i] - this.indexOffset + 1;
         } else {
            array[i] = 0;
         }
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
