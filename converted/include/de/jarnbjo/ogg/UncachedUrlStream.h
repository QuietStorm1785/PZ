#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UncachedUrlStream {
public:
 bool closed = false;
 URLConnection source;
 InputStream sourceStream;
 void* drainLock = new Object();
 LinkedList pageCache = new LinkedList();
 long numberOfSamples = -1L;
 std::unordered_map logicalStreams = new HashMap();
 private UncachedUrlStream.LoaderThread loaderThread;
 static const int PAGECACHE_SIZE = 10;

 public UncachedUrlStream(URL url) {
 this->source = url.openConnection();
 this->sourceStream = this->source.getInputStream();
 this->loaderThread = new UncachedUrlStream.LoaderThread(this->sourceStream, this->pageCache);
 new Thread();

 while (!this->loaderThread.isBosDone() || this->pageCache.size() < 10) {
 try {
 Thread.sleep(200L);
 } catch (InterruptedException interruptedException) {
 }
 }
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

 OggPage getOggPage(int var1) {
 while (this->pageCache.size() == 0) {
 try {
 Thread.sleep(100L);
 } catch (InterruptedException interruptedException) {
 }
 }

 synchronized (this->drainLock) {
 return (OggPage)this->pageCache.removeFirst();
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

 class LoaderThread implements Runnable {
 InputStream source;
 LinkedList pageCache;
 RandomAccessFile drain;
 private byte[] memoryCache;
 bool bosDone = false;
 int pageNumber;

 public LoaderThread(InputStream inputStream, LinkedList linkedList) {
 this->source = inputStream;
 this->pageCache = linkedList;
 }

 void run() {
 try {
 bool boolean0 = false;
 byte[] bytes = new byte[8192];

 while (!boolean0) {
 OggPage oggPage = OggPage.create(this->source);
 synchronized (UncachedUrlStream.this->drainLock) {
 this->pageCache.add(oggPage);
 }

 if (!oggPage.isBos()) {
 this->bosDone = true;
 }

 if (oggPage.isEos()) {
 boolean0 = true;
 }

 LogicalOggStreamImpl logicalOggStreamImpl = (LogicalOggStreamImpl)UncachedUrlStream.this->getLogicalStream(oggPage.getStreamSerialNumber());
 if (logicalOggStreamImpl.empty()) {
 logicalOggStreamImpl = new LogicalOggStreamImpl(UncachedUrlStream.this, oggPage.getStreamSerialNumber());
 UncachedUrlStream.this->logicalStreams.put(new Integer(oggPage.getStreamSerialNumber()), logicalOggStreamImpl);
 logicalOggStreamImpl.checkFormat(oggPage);
 }

 this->pageNumber++;

 while (this->pageCache.size() > 10) {
 try {
 Thread.sleep(200L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }
 } catch (EndOfOggStreamException endOfOggStreamException) {
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 bool isBosDone() {
 return this->bosDone;
 }
 }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
