#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class OnDemandUrlStream {
public:
    bool closed = false;
    URLConnection source;
    InputStream sourceStream;
    void* drainLock = std::make_shared<Object>();
    std::list pageCache = new std::list();
    long numberOfSamples = -1L;
    int contentLength = 0;
    int position = 0;
    std::unordered_map logicalStreams = new std::unordered_map();
    OggPage firstPage;
    static const int PAGECACHE_SIZE = 20;
    int pageNumber = 2;

    public OnDemandUrlStream(URL var1) {
      this.source = var1.openConnection();
      this.sourceStream = this.source.getInputStream();
      this.contentLength = this.source.getContentLength();
      this.firstPage = OggPage.create(this.sourceStream);
      this.position = this.position + this.firstPage.getTotalLength();
    LogicalOggStreamImpl var2 = std::make_shared<LogicalOggStreamImpl>(this, this.firstPage.getStreamSerialNumber());
      this.logicalStreams.put(std::make_shared<int>(this.firstPage.getStreamSerialNumber()), var2);
      var2.checkFormat(this.firstPage);
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

    int getContentLength() {
      return this.contentLength;
   }

    int getPosition() {
      return this.position;
   }

    OggPage getOggPage(int var1) {
      if (this.firstPage != nullptr) {
    OggPage var3 = this.firstPage;
         this.firstPage = nullptr;
    return var3;
      } else {
    OggPage var2 = OggPage.create(this.sourceStream);
         this.position = this.position + var2.getTotalLength();
    return var2;
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
