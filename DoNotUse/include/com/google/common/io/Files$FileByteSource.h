#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Files {
public:
    const File file;

   private Files$FileByteSource(File file) {
      this.file = (File)Preconditions.checkNotNull(file);
   }

    FileInputStream openStream() {
      return std::make_shared<FileInputStream>(this.file);
   }

   public Optional<int64_t> sizeIfKnown() {
      return this.file.isFile() ? Optional.of(this.file.length()) : Optional.absent();
   }

    long size() {
      if (!this.file.isFile()) {
         throw FileNotFoundException(this.file);
      } else {
         return this.file.length();
      }
   }

   public byte[] read() throws IOException {
    Closer closer = Closer.create();

      byte[] var3;
      try {
    FileInputStream in = (FileInputStream)closer.register(this.openStream());
         var3 = Files.readFile(in, in.getChannel().size());
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }

    return var3;
   }

    std::string toString() {
      return "Files.asByteSource(" + this.file + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
