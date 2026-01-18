#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace ogg {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileStream {
public:
 bool closed = false;
 RandomAccessFile source;
private
 long[] pageOffsets;
 long numberOfSamples = -1L;
 std::unordered_map logicalStreams = new HashMap();

public
 FileStream(RandomAccessFile randomAccessFile) {
 this->source = randomAccessFile;
 std::vector arrayList = new ArrayList();
 int int0 = 0;

 try {
 while (true) {
 arrayList.add(new Long(this->source.getFilePointer()));
 OggPage oggPage = this->getNextPage(int0 > 0);
 if (oggPage.empty()) {
 break;
 }

 LogicalOggStreamImpl logicalOggStreamImpl =
 (LogicalOggStreamImpl)this->getLogicalStream(
 oggPage.getStreamSerialNumber());
 if (logicalOggStreamImpl.empty()) {
 logicalOggStreamImpl =
 new LogicalOggStreamImpl(this, oggPage.getStreamSerialNumber());
 this->logicalStreams.put(new Integer(oggPage.getStreamSerialNumber()),
 logicalOggStreamImpl);
 }

 if (int0 == 0) {
 logicalOggStreamImpl.checkFormat(oggPage);
 }

 logicalOggStreamImpl.addPageNumberMapping(int0);
 logicalOggStreamImpl.addGranulePosition(
 oggPage.getAbsoluteGranulePosition());
 if (int0 > 0) {
 this->source.seek(this->source.getFilePointer() +
 oggPage.getTotalLength());
 }

 int0++;
 }
 } catch (EndOfOggStreamException endOfOggStreamException) {
 } catch (IOException iOException) {
 throw iOException;
 }

 this->source.seek(0L);
 this->pageOffsets = new long[arrayList.size()];
 int int1 = 0;
 Iterator iterator = arrayList.iterator();

 while (iterator.hasNext()) {
 this->pageOffsets[int1++] = (Long)iterator.next();
 }
 }

 Collection getLogicalStreams() { return this->logicalStreams.values(); }

 bool isOpen() { return !this->closed; }

 void close() {
 this->closed = true;
 this->source.close();
 }

 OggPage getNextPage() { return this->getNextPage(false); }

 OggPage getNextPage(bool boolean0) {
 return OggPage.create(this->source, boolean0);
 }

 OggPage getOggPage(int int0) {
 this->source.seek(this->pageOffsets[int0]);
 return OggPage.create(this->source);
 }

 LogicalOggStream getLogicalStream(int int0) {
 return (LogicalOggStream)this->logicalStreams.get(new Integer(int0);
 }

 void setTime(long long0) {
 for (LogicalOggStream logicalOggStream : this->logicalStreams.values()) {
 logicalOggStream.setTime(long0);
 }
 }

 bool isSeekable() { return true; }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
