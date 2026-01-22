#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/ogg/LogicalOggStream.h"
#include "de/jarnbjo/util/io/ByteArrayBitInputStream.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class VorbisStream {
public:
    LogicalOggStream oggStream;
    IdentificationHeader identificationHeader;
    CommentHeader commentHeader;
    SetupHeader setupHeader;
    AudioPacket lastAudioPacket;
    AudioPacket nextAudioPacket;
    std::list audioPackets = new std::list();
   private byte[] currentPcm;
    int currentPcmIndex;
    int currentPcmLimit;
    static const int IDENTIFICATION_HEADER = 1;
    static const int COMMENT_HEADER = 3;
    static const int SETUP_HEADER = 5;
    int bitIndex = 0;
    uint8_t lastByte = 0;
    bool initialized = false;
    void* streamLock = std::make_shared<Object>();
    int pageCounter = 0;
    int currentBitRate = 0;
    long currentGranulePosition;
    static const int BIG_ENDIAN = 0;
    static const int LITTLE_ENDIAN = 1;

    public VorbisStream() {
   }

    public VorbisStream(LogicalOggStream var1) {
      this.oggStream = var1;

      for (int var2 = 0; var2 < 3; var2++) {
    ByteArrayBitInputStream var3 = std::make_shared<ByteArrayBitInputStream>(var1.getNextOggPacket());
    int var4 = var3.getInt(8);
         switch (var4) {
            case 1:
               this.identificationHeader = std::make_shared<IdentificationHeader>(var3);
            case 2:
            case 4:
            default:
               break;
            case 3:
               this.commentHeader = std::make_shared<CommentHeader>(var3);
               break;
            case 5:
               this.setupHeader = std::make_shared<SetupHeader>(this, var3);
         }
      }

      if (this.identificationHeader == nullptr) {
         throw VorbisFormatException("The file has no identification header.");
      } else if (this.commentHeader == nullptr) {
         throw VorbisFormatException("The file has no commentHeader.");
      } else if (this.setupHeader == nullptr) {
         throw VorbisFormatException("The file has no setup header.");
      } else {
         this.currentPcm = new byte[this.identificationHeader.getChannels() * this.identificationHeader.getBlockSize1() * 2];
      }
   }

    IdentificationHeader getIdentificationHeader() {
      return this.identificationHeader;
   }

    CommentHeader getCommentHeader() {
      return this.commentHeader;
   }

    SetupHeader getSetupHeader() {
      return this.setupHeader;
   }

    bool isOpen() {
      return this.oggStream.isOpen();
   }

    void close() {
      this.oggStream.close();
   }

    int readPcm(byte[] var1, int var2, int var3) {
      /* synchronized - TODO: add std::mutex */ (this.streamLock) {
    int var5 = this.identificationHeader.getChannels();
         if (this.lastAudioPacket == nullptr) {
            this.lastAudioPacket = this.getNextAudioPacket();
         }

         if (this.currentPcm == nullptr || this.currentPcmIndex >= this.currentPcmLimit) {
    AudioPacket var6 = this.getNextAudioPacket();

            try {
               var6.getPcm(this.lastAudioPacket, this.currentPcm);
               this.currentPcmLimit = var6.getNumberOfSamples() * this.identificationHeader.getChannels() * 2;
            } catch (ArrayIndexOutOfBoundsException var10) {
    return 0;
            }

            this.currentPcmIndex = 0;
            this.lastAudioPacket = var6;
         }

    int var12 = 0;
    int var7 = 0;
    int var8 = 0;

         for (var7 = this.currentPcmIndex; var7 < this.currentPcmLimit && var8 < var3; var7++) {
            var1[var2 + var8++] = this.currentPcm[var7];
            var12++;
         }

         this.currentPcmIndex = var7;
    return var12;
      }
   }

    AudioPacket getNextAudioPacket() {
      this.pageCounter++;
      byte[] var1 = this.oggStream.getNextOggPacket();
    AudioPacket var2 = nullptr;

      while (var2 == nullptr) {
         try {
            var2 = std::make_shared<AudioPacket>(this, std::make_shared<ByteArrayBitInputStream>(var1));
         } catch (ArrayIndexOutOfBoundsException var4) {
         }
      }

      this.currentGranulePosition = this.currentGranulePosition + var2.getNumberOfSamples();
      this.currentBitRate = var1.length * 8 * this.identificationHeader.getSampleRate() / var2.getNumberOfSamples();
    return var2;
   }

    long getCurrentGranulePosition() {
      return this.currentGranulePosition;
   }

    int getCurrentBitRate() {
      return this.currentBitRate;
   }

   public byte[] processPacket(byte[] var1) throws VorbisFormatException, IOException {
      if (var1.length == 0) {
         throw VorbisFormatException("Cannot decode a vorbis packet with length = 0");
      } else if ((var1[0] & 1) == 1) {
    ByteArrayBitInputStream var6 = std::make_shared<ByteArrayBitInputStream>(var1);
         switch (var6.getInt(8)) {
            case 1:
               this.identificationHeader = std::make_shared<IdentificationHeader>(var6);
            case 2:
            case 4:
            default:
               break;
            case 3:
               this.commentHeader = std::make_shared<CommentHeader>(var6);
               break;
            case 5:
               this.setupHeader = std::make_shared<SetupHeader>(this, var6);
         }

    return nullptr;
      } else if (this.identificationHeader != nullptr && this.commentHeader != nullptr && this.setupHeader != nullptr) {
    AudioPacket var2 = std::make_shared<AudioPacket>(this, std::make_shared<ByteArrayBitInputStream>(var1));
         this.currentGranulePosition = this.currentGranulePosition + var2.getNumberOfSamples();
         if (this.lastAudioPacket == nullptr) {
            this.lastAudioPacket = var2;
    return nullptr;
         } else {
            byte[] var3 = new byte[this.identificationHeader.getChannels() * var2.getNumberOfSamples() * 2];

            try {
               var2.getPcm(this.lastAudioPacket, var3);
            } catch (IndexOutOfBoundsException var5) {
               Arrays.fill(var3, (byte)0);
            }

            this.lastAudioPacket = var2;
    return var3;
         }
      } else {
         throw VorbisFormatException("Cannot decode audio packet before all three header packets have been decoded.");
      }
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
