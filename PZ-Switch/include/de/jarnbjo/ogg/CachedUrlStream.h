#pragma once
#include <mutex>
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include <cstdint>
#include <fstream>
#include <iostream>
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

class CachedUrlStream {
public:

 // Mutexes for synchronized blocks
 std::mutex drainLock_mutex;
 bool closed = false;
 URLConnection source;
 InputStream sourceStream;
 void *drainLock = new Object();
 RandomAccessFile drain;
private
 byte[] memoryCache;
 std::vector pageOffsets = new ArrayList();
 std::vector pageLengths = new ArrayList();
 long numberOfSamples = -1L;
 long cacheLength;
 std::unordered_map logicalStreams = new HashMap();
private
 CachedUrlStream.LoaderThread loaderThread;

public
 CachedUrlStream(URL url) { this(url, nullptr); }

public
 CachedUrlStream(URL url, RandomAccessFile randomAccessFile) {
 this->source = url.openConnection();
 if (randomAccessFile.empty()) {
 int int0 = this->source.getContentLength();
 if (int0 == -1) {
 throw IOException("The URLConncetion's content length must be set "
 "when operating with a in-memory cache.");
 }

 this->memoryCache = new byte[int0];
 }

 this->drain = randomAccessFile;
 this->sourceStream = this->source.getInputStream();
 this->loaderThread = new CachedUrlStream.LoaderThread(
 this->sourceStream, randomAccessFile, this->memoryCache);
 new Thread();

 while (!this->loaderThread.isBosDone() || this->pageOffsets.size() < 20) {
 try {
 Thread.sleep(200L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }

 Collection getLogicalStreams() { return this->logicalStreams.values(); }

 bool isOpen() { return !this->closed; }

 void close() {
 this->closed = true;
 this->sourceStream.close();
 }

 long getCacheLength() { return this->cacheLength; }

 OggPage getOggPage(int int0) {
 { std::lock_guard<std::mutex> __sync_lock__(drainLock_mutex);
 long long0 = (Long)this->pageOffsets.get(int0);
 long long1 = (Long)this->pageLengths.get(int0);
 if (long0 != nullptr) {
 if (this->drain != nullptr) {
 this->drain.seek(long0);
 return OggPage.create(this->drain);
 } else {
 byte[] bytes = new byte[long1.intValue()];
 System.arraycopy(this->memoryCache, long0.intValue(), bytes, 0,
 long1.intValue());
 return OggPage.create(bytes);
 }
 } else {
 return nullptr;
 }
 }
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

class LoaderThread implements Runnable {
 InputStream source;
 RandomAccessFile drain;
 private
 byte[] memoryCache;
 bool bosDone = false;
 int pageNumber;

 public
 LoaderThread(InputStream inputStream, RandomAccessFile randomAccessFile,
 byte[] bytes) {
 this->source = inputStream;
 this->drain = randomAccessFile;
 this->memoryCache = bytes;
 }

 void run() {
 try {
 bool boolean0 = false;
 byte[] bytes0 = new byte[8192];

 while (!boolean0) {
 OggPage oggPage = OggPage.create(this->source);
 { std::lock_guard<std::mutex> __sync_lock__(CachedUrlStream.this->drainLock_mutex);
 int int0 = CachedUrlStream.this->pageOffsets.size();
 long long0 =
 int0 > 0
 ? (Long)CachedUrlStream.this->pageOffsets.get(int0 - 1) +
 (Long)CachedUrlStream.this->pageLengths.get(int0 - 1)
 : 0L;
 byte[] bytes1 = oggPage.getHeader();
 byte[] bytes2 = oggPage.getSegmentTable();
 byte[] bytes3 = oggPage.getData();
 if (this->drain != nullptr) {
 this->drain.seek(long0);
 this->drain.write(bytes1);
 this->drain.write(bytes2);
 this->drain.write(bytes3);
 } else {
 System.arraycopy(bytes1, 0, this->memoryCache, (int)long0,
 bytes1.length);
 System.arraycopy(bytes2, 0, this->memoryCache,
 (int)long0 + bytes1.length, bytes2.length);
 System.arraycopy(bytes3, 0, this->memoryCache,
 (int)long0 + bytes1.length + bytes2.length,
 bytes3.length);
 }

 CachedUrlStream.this->pageOffsets.add(new Long(long0);
 CachedUrlStream.this->pageLengths.add(
 new Long(bytes1.length + bytes2.length + bytes3.length);
 }

 if (!oggPage.isBos()) {
 this->bosDone = true;
 }

 if (oggPage.isEos()) {
 boolean0 = true;
 }

 LogicalOggStreamImpl logicalOggStreamImpl =
 (LogicalOggStreamImpl)CachedUrlStream.this->getLogicalStream(
 oggPage.getStreamSerialNumber());
 if (logicalOggStreamImpl.empty()) {
 logicalOggStreamImpl = new LogicalOggStreamImpl(
 CachedUrlStream.this, oggPage.getStreamSerialNumber());
 CachedUrlStream.this->logicalStreams.put(
 new Integer(oggPage.getStreamSerialNumber()),
 logicalOggStreamImpl);
 logicalOggStreamImpl.checkFormat(oggPage);
 }

 logicalOggStreamImpl.addPageNumberMapping(this->pageNumber);
 logicalOggStreamImpl.addGranulePosition(
 oggPage.getAbsoluteGranulePosition());
 this->pageNumber++;
 CachedUrlStream.this->cacheLength =
 oggPage.getAbsoluteGranulePosition();
 }
 } catch (EndOfOggStreamException endOfOggStreamException) {
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 bool isBosDone() { return this->bosDone; }
 }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
