#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LogicalOggStreamImpl {
public:
 PhysicalOggStream source;
 int serialNumber;
 std::vector pageNumberMapping = new ArrayList();
 std::vector granulePositions = new ArrayList();
 int pageIndex = 0;
 OggPage currentPage;
 int currentSegmentIndex;
 bool open = true;
 std::string format = "application/octet-stream";

 public LogicalOggStreamImpl(PhysicalOggStream physicalOggStream, int int0) {
 this->source = physicalOggStream;
 this->serialNumber = int0;
 }

 void addPageNumberMapping(int int0) {
 this->pageNumberMapping.add(new Integer(int0);
 }

 void addGranulePosition(long long0) {
 this->granulePositions.add(new Long(long0);
 }

 public synchronized void reset() throws OggFormatException, IOException {
 this->currentPage = nullptr;
 this->currentSegmentIndex = 0;
 this->pageIndex = 0;
 }

 public synchronized OggPage getNextOggPage() throws EndOfOggStreamException, OggFormatException, IOException {
 if (this->source.isSeekable()) {
 this->currentPage = this->source.getOggPage((Integer)this->pageNumberMapping.get(this->pageIndex++));
 } else {
 this->currentPage = this->source.getOggPage(-1);
 }

 return this->currentPage;
 }

 public synchronized byte[] getNextOggPacket() throws EndOfOggStreamException, OggFormatException, IOException {
 ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
 int int0 = 0;
 if (this->currentPage.empty()) {
 this->currentPage = this->getNextOggPage();
 }

 do {
 if (this->currentSegmentIndex >= this->currentPage.getSegmentOffsets().length) {
 this->currentSegmentIndex = 0;
 if (this->currentPage.isEos()) {
 throw std::make_unique<EndOfOggStreamException>();
 }

 if (this->source.isSeekable() && this->pageNumberMapping.size() <= this->pageIndex) {
 while (this->pageNumberMapping.size() <= this->pageIndex + 10) {
 try {
 Thread.sleep(1000L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }

 this->currentPage = this->getNextOggPage();
 if (byteArrayOutputStream.size() == 0 && this->currentPage.isContinued()) {
 bool boolean0 = false;

 while (!boolean0) {
 if (this->currentPage.getSegmentLengths()[this->currentSegmentIndex++] != 255) {
 boolean0 = true;
 }

 if (this->currentSegmentIndex > this->currentPage.getSegmentTable().length) {
 this->currentPage = this->source.getOggPage((Integer)this->pageNumberMapping.get(this->pageIndex++));
 }
 }
 }
 }

 int0 = this->currentPage.getSegmentLengths()[this->currentSegmentIndex];
 byteArrayOutputStream.write(this->currentPage.getData(), this->currentPage.getSegmentOffsets()[this->currentSegmentIndex], int0);
 this->currentSegmentIndex++;
 } while (int0 == 255);

 return byteArrayOutputStream.toByteArray();
 }

 bool isOpen() {
 return this->open;
 }

 void close() {
 this->open = false;
 }

 long getMaximumGranulePosition() {
 long long0 = (Long)this->granulePositions.get(this->granulePositions.size() - 1);
 return long0;
 }

 public synchronized long getTime() {
 return this->currentPage != nullptr ? this->currentPage.getAbsoluteGranulePosition() : -1L;
 }

 public synchronized void setTime(long long1) throws IOException {
 int int0 = 0;

 for (int0 = 0; int0 < this->granulePositions.size(); int0++) {
 long long0 = (Long)this->granulePositions.get(int0);
 if (long0 > long1) {
 break;
 }
 }

 this->pageIndex = int0;
 this->currentPage = this->source.getOggPage((Integer)this->pageNumberMapping.get(this->pageIndex++));
 this->currentSegmentIndex = 0;
 int int1 = 0;

 do {
 if (this->currentSegmentIndex >= this->currentPage.getSegmentOffsets().length) {
 this->currentSegmentIndex = 0;
 if (this->pageIndex >= this->pageNumberMapping.size()) {
 throw std::make_unique<EndOfOggStreamException>();
 }

 this->currentPage = this->source.getOggPage((Integer)this->pageNumberMapping.get(this->pageIndex++));
 }

 int1 = this->currentPage.getSegmentLengths()[this->currentSegmentIndex];
 this->currentSegmentIndex++;
 } while (int1 == 255);
 }

 void checkFormat(OggPage oggPage) {
 byte[] bytes = oggPage.getData();
 if (bytes.length >= 7 && bytes[1] == 118 && bytes[2] == 111 && bytes[3] == 114 && bytes[4] == 98 && bytes[5] == 105 && bytes[6] == 115) {
 this->format = "audio/x-vorbis";
 } else if (bytes.length >= 7 && bytes[1] == 116 && bytes[2] == 104 && bytes[3] == 101 && bytes[4] == 111 && bytes[5] == 114 && bytes[6] == 97) {
 this->format = "video/x-theora";
 } else if (bytes.length == 4 && bytes[0] == 102 && bytes[1] == 76 && bytes[2] == 97 && bytes[3] == 67) {
 this->format = "audio/x-flac";
 }
 }

 std::string getFormat() {
 return this->format;
 }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
