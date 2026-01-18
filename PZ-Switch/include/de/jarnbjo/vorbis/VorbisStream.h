#pragma once
#include <mutex>
#include "de/jarnbjo/ogg/LogicalOggStream.h"
#include "de/jarnbjo/util/io/ByteArrayBitInputStream.h"
#include <algorithm>
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
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VorbisStream {
public:

 // Mutexes for synchronized blocks
 std::mutex streamLock_mutex;
 LogicalOggStream oggStream;
 IdentificationHeader identificationHeader;
 CommentHeader commentHeader;
 SetupHeader setupHeader;
 AudioPacket lastAudioPacket;
 AudioPacket nextAudioPacket;
 LinkedList audioPackets = new LinkedList();
private
 byte[] currentPcm;
 int currentPcmIndex;
 int currentPcmLimit;
 static const int IDENTIFICATION_HEADER = 1;
 static const int COMMENT_HEADER = 3;
 static const int SETUP_HEADER = 5;
 int bitIndex = 0;
 uint8_t lastByte = 0;
 bool initialized = false;
 void *streamLock = new Object();
 int pageCounter = 0;
 int currentBitRate = 0;
 long currentGranulePosition;
 static const int BIG_ENDIAN = 0;
 static const int LITTLE_ENDIAN = 1;

public
 VorbisStream() {}

public
 VorbisStream(LogicalOggStream logicalOggStream) {
 this->oggStream = logicalOggStream;

 for (int int0 = 0; int0 < 3; int0++) {
 ByteArrayBitInputStream byteArrayBitInputStream =
 new ByteArrayBitInputStream(logicalOggStream.getNextOggPacket());
 int int1 = byteArrayBitInputStream.getInt(8);
 switch (int1) {
 case 1:
 this->identificationHeader =
 new IdentificationHeader(byteArrayBitInputStream);
 case 2:
 case 4:
 default:
 break;
 case 3:
 this->commentHeader = new CommentHeader(byteArrayBitInputStream);
 break;
 case 5:
 this->setupHeader = new SetupHeader(this, byteArrayBitInputStream);
 }
 }

 if (this->identificationHeader.empty()) {
 throw VorbisFormatException("The file has no identification header.");
 } else if (this->commentHeader.empty()) {
 throw VorbisFormatException("The file has no commentHeader.");
 } else if (this->setupHeader.empty()) {
 throw VorbisFormatException("The file has no setup header.");
 } else {
 this->currentPcm = new byte[this->identificationHeader.getChannels() *
 this->identificationHeader.getBlockSize1() * 2];
 }
 }

 IdentificationHeader getIdentificationHeader() {
 return this->identificationHeader;
 }

 CommentHeader getCommentHeader() { return this->commentHeader; }

 SetupHeader getSetupHeader() { return this->setupHeader; }

 bool isOpen() { return this->oggStream.isOpen(); }

 void close() { this->oggStream.close(); }

 int readPcm(byte[] bytes, int int5, int int4) {
 { std::lock_guard<std::mutex> __sync_lock__(streamLock_mutex);
 int int0 = this->identificationHeader.getChannels();
 if (this->lastAudioPacket.empty()) {
 this->lastAudioPacket = this->getNextAudioPacket();
 }

 if (this->currentPcm.empty() ||
 this->currentPcmIndex >= this->currentPcmLimit) {
 AudioPacket audioPacket = this->getNextAudioPacket();

 try {
 audioPacket.getPcm(this->lastAudioPacket, this->currentPcm);
 this->currentPcmLimit = audioPacket.getNumberOfSamples() *
 this->identificationHeader.getChannels() * 2;
 } catch (
 ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {
 return 0;
 }

 this->currentPcmIndex = 0;
 this->lastAudioPacket = audioPacket;
 }

 int int1 = 0;
 int int2 = 0;
 int int3 = 0;

 for (int2 = this->currentPcmIndex;
 int2 < this->currentPcmLimit && int3 < int4; int2++) {
 bytes[int5 + int3++] = this->currentPcm[int2];
 int1++;
 }

 this->currentPcmIndex = int2;
 return int1;
 }
 }

 AudioPacket getNextAudioPacket() {
 this->pageCounter++;
 byte[] bytes = this->oggStream.getNextOggPacket();
 AudioPacket audioPacket = nullptr;

 while (audioPacket.empty()) {
 try {
 audioPacket = new AudioPacket(this, new ByteArrayBitInputStream(bytes);
 } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {
 }
 }

 this->currentGranulePosition =
 this->currentGranulePosition + audioPacket.getNumberOfSamples();
 this->currentBitRate = bytes.length * 8 *
 this->identificationHeader.getSampleRate() /
 audioPacket.getNumberOfSamples();
 return audioPacket;
 }

 long getCurrentGranulePosition() { return this->currentGranulePosition; }

 int getCurrentBitRate() { return this->currentBitRate; }

public
 byte[] processPacket(byte[] bytes0) throws VorbisFormatException,
 IOException {
 if (bytes0.length == 0) {
 throw VorbisFormatException(
 "Cannot decode a vorbis packet with length = 0");
 } else if ((bytes0[0] & 1) == 1) {
 ByteArrayBitInputStream byteArrayBitInputStream =
 new ByteArrayBitInputStream(bytes0);
 switch (byteArrayBitInputStream.getInt(8) {
 case 1:
 this->identificationHeader =
 new IdentificationHeader(byteArrayBitInputStream);
 case 2:
 case 4:
 default:
 break;
 case 3:
 this->commentHeader = new CommentHeader(byteArrayBitInputStream);
 break;
 case 5:
 this->setupHeader = new SetupHeader(this, byteArrayBitInputStream);
 }

 return nullptr;
 } else if (this->identificationHeader != nullptr &&
 this->commentHeader != nullptr && this->setupHeader != nullptr) {
 AudioPacket audioPacket =
 new AudioPacket(this, new ByteArrayBitInputStream(bytes0);
 this->currentGranulePosition =
 this->currentGranulePosition + audioPacket.getNumberOfSamples();
 if (this->lastAudioPacket.empty()) {
 this->lastAudioPacket = audioPacket;
 return nullptr;
 } else {
 byte[] bytes1 = new byte[this->identificationHeader.getChannels() *
 audioPacket.getNumberOfSamples() * 2];

 try {
 audioPacket.getPcm(this->lastAudioPacket, bytes1);
 } catch (IndexOutOfBoundsException indexOutOfBoundsException) {
 Arrays.fill(bytes1, (byte)0);
 }

 this->lastAudioPacket = audioPacket;
 return bytes1;
 }
 } else {
 throw VorbisFormatException(
 "Cannot decode audio packet before all three header packets have "
 "been decoded.");
 }
 }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
