#pragma once
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class UncachedUrlStream {
public:
    InputStream source;
    std::list pageCache;
    RandomAccessFile drain;
   private byte[] memoryCache;
    bool bosDone;
    int pageNumber;

   public UncachedUrlStream$LoaderThread(UncachedUrlStream var1, InputStream var2, std::list var3) {
      this.this$0 = var1;
      this.bosDone = false;
      this.source = var2;
      this.pageCache = var3;
   }

    void run() {
      try {
    bool var1 = false;
         byte[] var2 = new byte[8192];

         while (!var1) {
    OggPage var3 = OggPage.create(this.source);
            /* synchronized - TODO: add std::mutex */ (this.this$0.drainLock) {
               this.pageCache.push_back(var3);
            }

            if (!var3.isBos()) {
               this.bosDone = true;
            }

            if (var3.isEos()) {
               var1 = true;
            }

    LogicalOggStreamImpl var10 = (LogicalOggStreamImpl)this.this$0.getLogicalStream(var3.getStreamSerialNumber());
            if (var10 == nullptr) {
               var10 = std::make_shared<LogicalOggStreamImpl>(this.this$0, var3.getStreamSerialNumber());
               this.this$0.logicalStreams.put(std::make_shared<int>(var3.getStreamSerialNumber()), var10);
               var10.checkFormat(var3);
            }

            this.pageNumber++;

            while (this.pageCache.size() > 10) {
               try {
                  Thread.sleep(200L);
               } catch (InterruptedException var6) {
               }
            }
         }
      } catch (EndOfOggStreamException var8) {
      } catch (IOException var9) {
         var9.printStackTrace();
      }
   }

    bool isBosDone() {
      return this.bosDone;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
