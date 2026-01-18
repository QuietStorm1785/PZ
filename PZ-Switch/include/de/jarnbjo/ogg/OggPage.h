#pragma once
#include "de/jarnbjo/util/io/ByteArrayBitInputStream.h"
#include "zombie/debug/DebugLog.h"
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

class OggPage {
public:
 int version;
 bool continued;
 bool bos;
 bool eos;
 long absoluteGranulePosition;
 int streamSerialNumber;
 int pageSequenceNumber;
 int pageCheckSum;
private
 int[] segmentOffsets;
private
 int[] segmentLengths;
 int totalLength;
private
 byte[] header;
private
 byte[] segmentTable;
private
 byte[] data;

protected
 OggPage() {}

private
 OggPage(int int0, boolean boolean0, boolean boolean1, boolean boolean2,
 long long0, int int1, int int2, int int3, int[] ints0, int[] ints1,
 int int4, byte[] bytes0, byte[] bytes1, byte[] bytes2) {
 this->version = int0;
 this->continued = boolean0;
 this->bos = boolean1;
 this->eos = boolean2;
 this->absoluteGranulePosition = long0;
 this->streamSerialNumber = int1;
 this->pageSequenceNumber = int2;
 this->pageCheckSum = int3;
 this->segmentOffsets = ints0;
 this->segmentLengths = ints1;
 this->totalLength = int4;
 this->header = bytes0;
 this->segmentTable = bytes1;
 this->data = bytes2;
 }

 static OggPage create(RandomAccessFile randomAccessFile) { return create(); }

 static OggPage create(RandomAccessFile randomAccessFile, bool boolean0) {
 return create();
 }

 static OggPage create(InputStream inputStream) { return create(); }

 static OggPage create(InputStream inputStream, bool boolean0) {
 return create();
 }

 static OggPage create(byte[] bytes) { return create(); }

 static OggPage create(byte[] bytes, bool boolean0) { return create(); }

 static OggPage create(void *object, bool boolean3) {
 try {
 int int0 = 27;
 byte[] bytes0 = new byte[27];
 if (object instanceof RandomAccessFile randomAccessFile) {
 if (randomAccessFile.getFilePointer() == randomAccessFile.length()) {
 return nullptr;
 }

 randomAccessFile.readFully(bytes0);
 } else if (object instanceof InputStream) {
 readFully((InputStream)object, bytes0);
 } else if (object instanceof byte[]) {
 System.arraycopy((byte[])object, 0, bytes0, 0, 27);
 }

 ByteArrayBitInputStream byteArrayBitInputStream =
 new ByteArrayBitInputStream(bytes0);
 int int1 = byteArrayBitInputStream.getInt(32);
 if (int1 != 1399285583) {
 std::string string = Integer.toHexString(int1);

 while (string.length() < 8) {
 string = "0" + string;
 }

 string = string.substring(6, 8) + string.substring(4, 6) +
 string.substring(2, 4) + string.substring(0, 2);
 char char0 =
 (char)Integer.valueOf(string.substring(0, 2), 16).intValue();
 char char1 =
 (char)Integer.valueOf(string.substring(2, 4), 16).intValue();
 char char2 =
 (char)Integer.valueOf(string.substring(4, 6), 16).intValue();
 char char3 =
 (char)Integer.valueOf(string.substring(6, 8), 16).intValue();
 DebugLog.log("Ogg packet header is 0x" + string + " (" + char0 + char1 +
 char2 + char3 + "), should be 0x4f676753 (OggS)");
 }

 int int2 = byteArrayBitInputStream.getInt(8);
 uint8_t byte0 = (byte)byteArrayBitInputStream.getInt(8);
 bool boolean0 = (byte0 & 1) != 0;
 bool boolean1 = (byte0 & 2) != 0;
 bool boolean2 = (byte0 & 4) != 0;
 long long0 = byteArrayBitInputStream.getLong(64);
 int int3 = byteArrayBitInputStream.getInt(32);
 int int4 = byteArrayBitInputStream.getInt(32);
 int int5 = byteArrayBitInputStream.getInt(32);
 int int6 = byteArrayBitInputStream.getInt(8);
 int[] ints0 = new int[int6];
 int[] ints1 = new int[int6];
 int int7 = 0;
 byte[] bytes1 = new byte[int6];
 byte[] bytes2 = new byte[1];

 for (int int8 = 0; int8 < int6; int8++) {
 int int9 = 0;
 if (object instanceof RandomAccessFile) {
 int9 = ((RandomAccessFile)object).readByte() & 255;
 } else if (object instanceof InputStream) {
 int9 = ((InputStream)object).read();
 } else if (object instanceof byte[]) {
 uint8_t byte1 = ((byte[])object)[int0++];
 int9 = byte1 & 255;
 }

 bytes1[int8] = (byte)int9;
 ints1[int8] = int9;
 ints0[int8] = int7;
 int7 += int9;
 }

 byte[] bytes3 = nullptr;
 if (!boolean3) {
 bytes3 = new byte[int7];
 if (object instanceof RandomAccessFile) {
 ((RandomAccessFile)object).readFully(bytes3);
 } else if (object instanceof InputStream) {
 readFully((InputStream)object, bytes3);
 } else if (object instanceof byte[]) {
 System.arraycopy(object, int0, bytes3, 0, int7);
 }
 }

 return new OggPage(int2, boolean0, boolean1, boolean2, long0, int3, int4,
 int5, ints0, ints1, int7, bytes0, bytes1, bytes3);
 } catch (EOFException eOFException) {
 throw std::make_unique<EndOfOggStreamException>();
 }
 }

 static void readFully(InputStream inputStream, byte[] bytes) {
 int int0 = 0;

 while (int0 < bytes.length) {
 int int1 = inputStream.read(bytes, int0, bytes.length - int0);
 if (int1 == -1) {
 throw std::make_unique<EndOfOggStreamException>();
 }

 int0 += int1;
 }
 }

 long getAbsoluteGranulePosition() { return this->absoluteGranulePosition; }

 int getStreamSerialNumber() { return this->streamSerialNumber; }

 int getPageSequenceNumber() { return this->pageSequenceNumber; }

 int getPageCheckSum() { return this->pageCheckSum; }

 int getTotalLength() {
 return this->data != nullptr
 ? 27 + this->segmentTable.length + this->data.length
 : this->totalLength;
 }

public
 byte[] getData() { return this->data; }

public
 byte[] getHeader() { return this->header; }

public
 byte[] getSegmentTable() { return this->segmentTable; }

public
 int[] getSegmentOffsets() { return this->segmentOffsets; }

public
 int[] getSegmentLengths() { return this->segmentLengths; }

 bool isContinued() { return this->continued; }

 bool isFresh() { return !this->continued; }

 bool isBos() { return this->bos; }

 bool isEos() { return this->eos; }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
