#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BasicStream {
public:
 bool closed = false;
 InputStream sourceStream;
 void* drainLock = new Object();
 LinkedList pageCache = new LinkedList();
 long numberOfSamples = -1L;
 int position = 0;
 std::unordered_map logicalStreams = new HashMap();
 OggPage firstPage;
 int pageNumber = 2;

 public BasicStream(InputStream inputStream) {
 this->firstPage = OggPage.create(inputStream);
 this->position = this->position + this->firstPage.getTotalLength();
 LogicalOggStreamImpl logicalOggStreamImpl = new LogicalOggStreamImpl(this, this->firstPage.getStreamSerialNumber());
 this->logicalStreams.put(new Integer(this->firstPage.getStreamSerialNumber()), logicalOggStreamImpl);
 logicalOggStreamImpl.checkFormat(this->firstPage);
 }

 Collection getLogicalStreams() {
 return this->logicalStreams.values();
 }

 bool isOpen() {
 return !this->closed;
 }

 void close() {
 this->closed = true;
 this->sourceStream.close();
 }

 int getContentLength() {
 return -1;
 }

 int getPosition() {
 return this->position;
 }

 OggPage getOggPage(int var1) {
 if (this->firstPage != nullptr) {
 OggPage oggPage0 = this->firstPage;
 this->firstPage = nullptr;
 return oggPage0;
 } else {
 OggPage oggPage1 = OggPage.create(this->sourceStream);
 this->position = this->position + oggPage1.getTotalLength();
 return oggPage1;
 }
 }

 LogicalOggStream getLogicalStream(int int0) {
 return (LogicalOggStream)this->logicalStreams.get(new Integer(int0);
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
