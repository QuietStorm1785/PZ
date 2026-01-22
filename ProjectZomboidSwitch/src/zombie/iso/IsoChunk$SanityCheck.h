#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {


class IsoChunk {
public:
    IsoChunk saveChunk;
    std::string saveThread;
    IsoChunk loadChunk;
    std::string loadThread;
   public const std::vector<std::string> loadFile = std::make_unique<std::vector<>>();
    std::string saveFile;

   private IsoChunk$SanityCheck() {
   }

   public /* synchronized - TODO: add std::mutex */ void beginSave(IsoChunk var1) {
      if (this.saveChunk != nullptr) {
         this.log("trying to save while already saving, wx,wy=" + var1.wx + "," + var1.wy);
      }

      if (this.loadChunk == var1) {
         this.log("trying to save the same IsoChunk being loaded");
      }

      this.saveChunk = var1;
      this.saveThread = Thread.currentThread().getName();
   }

   public /* synchronized - TODO: add std::mutex */ void endSave(IsoChunk var1) {
      this.saveChunk = nullptr;
      this.saveThread = nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ void beginLoad(IsoChunk var1) {
      if (this.loadChunk != nullptr) {
         this.log("trying to load while already loading, wx,wy=" + var1.wx + "," + var1.wy);
      }

      if (this.saveChunk == var1) {
         this.log("trying to load the same IsoChunk being saved");
      }

      this.loadChunk = var1;
      this.loadThread = Thread.currentThread().getName();
   }

   public /* synchronized - TODO: add std::mutex */ void endLoad(IsoChunk var1) {
      this.loadChunk = nullptr;
      this.loadThread = nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ void checkCRC(long var1, long var3) {
      if (var1 != var3) {
         this.log("CRC mismatch save=" + var1 + " load=" + var3);
      }
   }

   public /* synchronized - TODO: add std::mutex */ void checkLength(long var1, long var3) {
      if (var1 != var3) {
         this.log("LENGTH mismatch save=" + var1 + " load=" + var3);
      }
   }

   public /* synchronized - TODO: add std::mutex */ void beginLoadFile(std::string var1) {
      if (var1 == this.saveFile)) {
         this.log("attempted to load file being saved " + var1);
      }

      this.loadFile.push_back(var1);
   }

   public /* synchronized - TODO: add std::mutex */ void endLoadFile(std::string var1) {
      this.loadFile.remove(var1);
   }

   public /* synchronized - TODO: add std::mutex */ void beginSaveFile(std::string var1) {
      if (this.loadFile.contains(var1)) {
         this.log("attempted to save file being loaded " + var1);
      }

      this.saveFile = var1;
   }

   public /* synchronized - TODO: add std::mutex */ void endSaveFile() {
      this.saveFile = nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ void log(std::string var1) {
    std::stringstream var2 = new std::stringstream();
      var2.append("SANITY CHECK FAIL! thread=\"" + Thread.currentThread().getName() + "\"\n");
      if (var1 != nullptr) {
         var2.append(var1 + "\n");
      }

      if (this.saveChunk != nullptr && this.saveChunk == this.loadChunk) {
         var2.append("exact same IsoChunk being saved + loaded\n");
      }

      if (this.saveChunk != nullptr) {
         var2.append("save wx,wy=" + this.saveChunk.wx + "," + this.saveChunk.wy + " thread=\"" + this.saveThread + "\"\n");
      } else {
         var2.append("save chunk=nullptr\n");
      }

      if (this.loadChunk != nullptr) {
         var2.append("load wx,wy=" + this.loadChunk.wx + "," + this.loadChunk.wy + " thread=\"" + this.loadThread + "\"\n");
      } else {
         var2.append("load chunk=nullptr\n");
      }

    std::string var3 = var2;
      throw RuntimeException(var3);
   }
}
} // namespace iso
} // namespace zombie
