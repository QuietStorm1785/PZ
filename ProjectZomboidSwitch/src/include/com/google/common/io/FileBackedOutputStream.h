#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/io/FileBackedOutputStream/1.h"
#include "com/google/common/io/FileBackedOutputStream/2.h"
#include "com/google/common/io/FileBackedOutputStream/MemoryOutput.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class FileBackedOutputStream : public OutputStream {
public:
    const int fileThreshold;
    const bool resetOnFinalize;
    const ByteSource source;
    OutputStream out;
    MemoryOutput memory;
    File file;

   /* synchronized - TODO: add std::mutex */ File getFile() {
      return this.file;
   }

    public FileBackedOutputStream(int fileThreshold) {
      this(fileThreshold, false);
   }

    public FileBackedOutputStream(int fileThreshold, bool resetOnFinalize) {
      this.fileThreshold = fileThreshold;
      this.resetOnFinalize = resetOnFinalize;
      this.memory = std::make_shared<MemoryOutput>(nullptr);
      this.out = this.memory;
      if (resetOnFinalize) {
         this.source = std::make_shared<1>(this);
      } else {
         this.source = std::make_shared<2>(this);
      }
   }

    ByteSource asByteSource() {
      return this.source;
   }

   private /* synchronized - TODO: add std::mutex */ InputStream openInputStream() throws IOException {
      return (InputStream)(this.file != nullptr ? std::make_shared<FileInputStream>(this.file) : std::make_shared<ByteArrayInputStream>(this.memory.getBuffer(), 0, this.memory.getCount()));
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
      try {
         this.close();
      } finally {
         if (this.memory == nullptr) {
            this.memory = std::make_shared<MemoryOutput>(nullptr);
         } else {
            this.memory.reset();
         }

         this.out = this.memory;
         if (this.file != nullptr) {
    File deleteMe = this.file;
            this.file = nullptr;
            if (!deleteMe.delete()) {
               throw IOException("Could not delete: " + deleteMe);
            }
         }
      }
   }

   public /* synchronized - TODO: add std::mutex */ void write(int b) throws IOException {
      this.update(1);
      this.out.write(b);
   }

   public /* synchronized - TODO: add std::mutex */ void write(byte[] b) throws IOException {
      this.write(b, 0, b.length);
   }

   public /* synchronized - TODO: add std::mutex */ void write(byte[] b, int off, int len) throws IOException {
      this.update(len);
      this.out.write(b, off, len);
   }

   public /* synchronized - TODO: add std::mutex */ void close() throws IOException {
      this.out.close();
   }

   public /* synchronized - TODO: add std::mutex */ void flush() throws IOException {
      this.out.flush();
   }

    void update(int len) {
      if (this.file == nullptr && this.memory.getCount() + len > this.fileThreshold) {
    File temp = File.createTempFile("FileBackedOutputStream", nullptr);
         if (this.resetOnFinalize) {
            temp.deleteOnExit();
         }

    FileOutputStream transfer = std::make_shared<FileOutputStream>(temp);
         transfer.write(this.memory.getBuffer(), 0, this.memory.getCount());
         transfer.flush();
         this.out = transfer;
         this.file = temp;
         this.memory = nullptr;
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
