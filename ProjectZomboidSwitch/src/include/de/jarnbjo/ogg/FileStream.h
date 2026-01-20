#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>

namespace de {
namespace jarnbjo {
namespace ogg {


class FileStream {
public:
    bool closed = false;
    RandomAccessFile source;
   private long[] pageOffsets;
    long numberOfSamples = -1L;
    std::unordered_map logicalStreams = new std::unordered_map();

    public FileStream(RandomAccessFile var1) {
      this.source = var1;
    std::vector var2 = new std::vector();
    int var3 = 0;

      try {
         while (true) {
            var2.push_back(std::make_shared<int64_t>(this.source.getFilePointer()));
    OggPage var4 = this.getNextPage(var3 > 0);
            if (var4 == nullptr) {
               break;
            }

    LogicalOggStreamImpl var5 = (LogicalOggStreamImpl)this.getLogicalStream(var4.getStreamSerialNumber());
            if (var5 == nullptr) {
               var5 = std::make_shared<LogicalOggStreamImpl>(this, var4.getStreamSerialNumber());
               this.logicalStreams.put(std::make_shared<int>(var4.getStreamSerialNumber()), var5);
            }

            if (var3 == 0) {
               var5.checkFormat(var4);
            }

            var5.addPageNumberMapping(var3);
            var5.addGranulePosition(var4.getAbsoluteGranulePosition());
            if (var3 > 0) {
               this.source.seek(this.source.getFilePointer() + var4.getTotalLength());
            }

            var3++;
         }
      } catch (EndOfOggStreamException var6) {
      } catch (IOException var7) {
    throw var7;
      }

      this.source.seek(0L);
      this.pageOffsets = new long[var2.size()];
    int var8 = 0;
    Iterator var9 = var2.iterator();

      while (var9.hasNext()) {
         this.pageOffsets[var8++] = (int64_t)var9.next();
      }
   }

    Collection getLogicalStreams() {
      return this.logicalStreams.values();
   }

    bool isOpen() {
      return !this.closed;
   }

    void close() {
      this.closed = true;
      this.source.close();
   }

    OggPage getNextPage() {
      return this.getNextPage(false);
   }

    OggPage getNextPage(bool var1) {
      return OggPage.create(this.source, var1);
   }

    OggPage getOggPage(int var1) {
      this.source.seek(this.pageOffsets[var1]);
      return OggPage.create(this.source);
   }

    LogicalOggStream getLogicalStream(int var1) {
      return (LogicalOggStream)this.logicalStreams.get(std::make_shared<int>(var1));
   }

    void setTime(long var1) {
      for (LogicalOggStream var4 : this.logicalStreams.values()) {
         var4.setTime(var1);
      }
   }

    bool isSeekable() {
    return true;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
