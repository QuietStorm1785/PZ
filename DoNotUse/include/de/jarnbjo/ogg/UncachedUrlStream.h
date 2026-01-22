#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/ogg/UncachedUrlStream/LoaderThread.h"
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class UncachedUrlStream {
public:
    bool closed = false;
    URLConnection source;
    InputStream sourceStream;
    void* drainLock = std::make_shared<Object>();
    std::list pageCache = new std::list();
    long numberOfSamples = -1L;
    std::unordered_map logicalStreams = new std::unordered_map();
    LoaderThread loaderThread;
    static const int PAGECACHE_SIZE = 10;

    public UncachedUrlStream(URL var1) {
      this.source = var1.openConnection();
      this.sourceStream = this.source.getInputStream();
      this.loaderThread = std::make_shared<LoaderThread>(this, this.sourceStream, this.pageCache);
    std::make_shared<Thread>();

      while (!this.loaderThread.isBosDone() || this.pageCache.size() < 10) {
         try {
            Thread.sleep(200L);
         } catch (InterruptedException var3) {
         }
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
      this.sourceStream.close();
   }

    OggPage getOggPage(int var1) {
      while (this.pageCache.size() == 0) {
         try {
            Thread.sleep(100L);
         } catch (InterruptedException var4) {
         }
      }

      /* synchronized - TODO: add std::mutex */ (this.drainLock) {
         return (OggPage)this.pageCache.removeFirst();
      }
   }

    LogicalOggStream getLogicalStream(int var1) {
      return (LogicalOggStream)this.logicalStreams.get(std::make_shared<int>(var1));
   }

    void setTime(long var1) {
      throw UnsupportedOperationException("Method not supported by this class");
   }

    bool isSeekable() {
    return false;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
