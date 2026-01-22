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


class LogicalOggStreamImpl {
public:
    PhysicalOggStream source;
    int serialNumber;
    std::vector pageNumberMapping = new std::vector();
    std::vector granulePositions = new std::vector();
    int pageIndex = 0;
    OggPage currentPage;
    int currentSegmentIndex;
    bool open = true;
    std::string format = "application/octet-stream";

    public LogicalOggStreamImpl(PhysicalOggStream var1, int var2) {
      this.source = var1;
      this.serialNumber = var2;
   }

    void addPageNumberMapping(int var1) {
      this.pageNumberMapping.push_back(std::make_shared<int>(var1));
   }

    void addGranulePosition(long var1) {
      this.granulePositions.push_back(std::make_shared<int64_t>(var1));
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws OggFormatException, IOException {
      this.currentPage = nullptr;
      this.currentSegmentIndex = 0;
      this.pageIndex = 0;
   }

   public /* synchronized - TODO: add std::mutex */ OggPage getNextOggPage() throws EndOfOggStreamException, OggFormatException, IOException {
      if (this.source.isSeekable()) {
         this.currentPage = this.source.getOggPage((int)this.pageNumberMapping.get(this.pageIndex++));
      } else {
         this.currentPage = this.source.getOggPage(-1);
      }

      return this.currentPage;
   }

   public /* synchronized - TODO: add std::mutex */ byte[] getNextOggPacket() throws EndOfOggStreamException, OggFormatException, IOException {
    ByteArrayOutputStream var1 = std::make_shared<ByteArrayOutputStream>();
    int var2 = 0;
      if (this.currentPage == nullptr) {
         this.currentPage = this.getNextOggPage();
      }

      do {
         if (this.currentSegmentIndex >= this.currentPage.getSegmentOffsets().length) {
            this.currentSegmentIndex = 0;
            if (this.currentPage.isEos()) {
               throw std::make_unique<EndOfOggStreamException>();
            }

            if (this.source.isSeekable() && this.pageNumberMapping.size() <= this.pageIndex) {
               while (this.pageNumberMapping.size() <= this.pageIndex + 10) {
                  try {
                     Thread.sleep(1000L);
                  } catch (InterruptedException var4) {
                  }
               }
            }

            this.currentPage = this.getNextOggPage();
            if (var1.size() == 0 && this.currentPage.isContinued()) {
    bool var3 = false;

               while (!var3) {
                  if (this.currentPage.getSegmentLengths()[this.currentSegmentIndex++] != 255) {
                     var3 = true;
                  }

                  if (this.currentSegmentIndex > this.currentPage.getSegmentTable().length) {
                     this.currentPage = this.source.getOggPage((int)this.pageNumberMapping.get(this.pageIndex++));
                  }
               }
            }
         }

         var2 = this.currentPage.getSegmentLengths()[this.currentSegmentIndex];
         var1.write(this.currentPage.getData(), this.currentPage.getSegmentOffsets()[this.currentSegmentIndex], var2);
         this.currentSegmentIndex++;
      } while (var2 == 255);

      return var1.toByteArray();
   }

    bool isOpen() {
      return this.open;
   }

    void close() {
      this.open = false;
   }

    long getMaximumGranulePosition() {
    long var1 = (int64_t)this.granulePositions.get(this.granulePositions.size() - 1);
    return var1;
   }

   public /* synchronized - TODO: add std::mutex */ long getTime() {
      return this.currentPage != nullptr ? this.currentPage.getAbsoluteGranulePosition() : -1L;
   }

   public /* synchronized - TODO: add std::mutex */ void setTime(long var1) throws IOException {
    int var3 = 0;

      for (var3 = 0; var3 < this.granulePositions.size(); var3++) {
    long var4 = (int64_t)this.granulePositions.get(var3);
         if (var4 > var1) {
            break;
         }
      }

      this.pageIndex = var3;
      this.currentPage = this.source.getOggPage((int)this.pageNumberMapping.get(this.pageIndex++));
      this.currentSegmentIndex = 0;
    int var6 = 0;

      do {
         if (this.currentSegmentIndex >= this.currentPage.getSegmentOffsets().length) {
            this.currentSegmentIndex = 0;
            if (this.pageIndex >= this.pageNumberMapping.size()) {
               throw std::make_unique<EndOfOggStreamException>();
            }

            this.currentPage = this.source.getOggPage((int)this.pageNumberMapping.get(this.pageIndex++));
         }

         var6 = this.currentPage.getSegmentLengths()[this.currentSegmentIndex];
         this.currentSegmentIndex++;
      } while (var6 == 255);
   }

    void checkFormat(OggPage var1) {
      byte[] var2 = var1.getData();
      if (var2.length >= 7 && var2[1] == 118 && var2[2] == 111 && var2[3] == 114 && var2[4] == 98 && var2[5] == 105 && var2[6] == 115) {
         this.format = "audio/x-vorbis";
      } else if (var2.length >= 7 && var2[1] == 116 && var2[2] == 104 && var2[3] == 101 && var2[4] == 111 && var2[5] == 114 && var2[6] == 97) {
         this.format = "video/x-theora";
      } else if (var2.length == 4 && var2[0] == 102 && var2[1] == 76 && var2[2] == 97 && var2[3] == 67) {
         this.format = "audio/x-flac";
      }
   }

    std::string getFormat() {
      return this.format;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
