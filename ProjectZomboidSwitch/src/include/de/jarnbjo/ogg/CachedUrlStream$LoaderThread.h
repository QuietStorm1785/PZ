#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class CachedUrlStream {
public:
    InputStream source;
    RandomAccessFile drain;
   private byte[] memoryCache;
    bool bosDone;
    int pageNumber;

   public CachedUrlStream$LoaderThread(CachedUrlStream var1, InputStream var2, RandomAccessFile var3, byte[] var4) {
      this.this$0 = var1;
      this.bosDone = false;
      this.source = var2;
      this.drain = var3;
      this.memoryCache = var4;
   }

    void run() {
      try {
    bool var1 = false;
         byte[] var2 = new byte[8192];

         while (!var1) {
    OggPage var3 = OggPage.create(this.source);
            /* synchronized - TODO: add std::mutex */ (this.this$0.drainLock) {
    int var5 = this.this$0.pageOffsets.size();
    long var6 = var5 > 0 ? (int64_t)this.this$0.pageOffsets.get(var5 - 1) + (int64_t)this.this$0.pageLengths.get(var5 - 1) : 0L;
               byte[] var8 = var3.getHeader();
               byte[] var9 = var3.getSegmentTable();
               byte[] var10 = var3.getData();
               if (this.drain != nullptr) {
                  this.drain.seek(var6);
                  this.drain.write(var8);
                  this.drain.write(var9);
                  this.drain.write(var10);
               } else {
                  System.arraycopy(var8, 0, this.memoryCache, (int)var6, var8.length);
                  System.arraycopy(var9, 0, this.memoryCache, (int)var6 + var8.length, var9.length);
                  System.arraycopy(var10, 0, this.memoryCache, (int)var6 + var8.length + var9.length, var10.length);
               }

               this.this$0.pageOffsets.push_back(std::make_shared<int64_t>(var6));
               this.this$0.pageLengths.push_back(std::make_shared<int64_t>(var8.length + var9.length + var10.length));
            }

            if (!var3.isBos()) {
               this.bosDone = true;
            }

            if (var3.isEos()) {
               var1 = true;
            }

    LogicalOggStreamImpl var15 = (LogicalOggStreamImpl)this.this$0.getLogicalStream(var3.getStreamSerialNumber());
            if (var15 == nullptr) {
               var15 = std::make_shared<LogicalOggStreamImpl>(this.this$0, var3.getStreamSerialNumber());
               this.this$0.logicalStreams.put(std::make_shared<int>(var3.getStreamSerialNumber()), var15);
               var15.checkFormat(var3);
            }

            var15.addPageNumberMapping(this.pageNumber);
            var15.addGranulePosition(var3.getAbsoluteGranulePosition());
            this.pageNumber++;
            this.this$0.cacheLength = var3.getAbsoluteGranulePosition();
         }
      } catch (EndOfOggStreamException var13) {
      } catch (IOException var14) {
         var14.printStackTrace();
      }
   }

    bool isBosDone() {
      return this.bosDone;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
