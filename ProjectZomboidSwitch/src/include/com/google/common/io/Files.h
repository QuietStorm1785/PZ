#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/collect/TreeTraverser.h"
#include "com/google/common/hash/HashCode.h"
#include "com/google/common/hash/HashFunction.h"
#include "com/google/common/io/Files/1.h"
#include "com/google/common/io/Files/2.h"
#include "com/google/common/io/Files/FileByteSink.h"
#include "com/google/common/io/Files/FileByteSource.h"
#include "com/google/common/io/Files/FilePredicate.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Files {
public:
    static const int TEMP_DIR_ATTEMPTS = 10000;
   private static const TreeTraverser<File> FILE_TREE_TRAVERSER = std::make_unique<2>();

    private Files() {
   }

    static BufferedReader newReader(File file, Charset charset) {
      Preconditions.checkNotNull(file);
      Preconditions.checkNotNull(charset);
      return std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(std::make_shared<FileInputStream>(file), charset));
   }

    static BufferedWriter newWriter(File file, Charset charset) {
      Preconditions.checkNotNull(file);
      Preconditions.checkNotNull(charset);
      return std::make_shared<BufferedWriter>(std::make_shared<OutputStreamWriter>(std::make_shared<FileOutputStream>(file), charset));
   }

    static ByteSource asByteSource(File file) {
      return std::make_shared<FileByteSource>(file, nullptr);
   }

   static byte[] readFile(InputStream in, long expectedSize) throws IOException {
      if (expectedSize > 2147483647L) {
         throw OutOfMemoryError("file is too large to fit in a byte array: " + expectedSize + " bytes");
      } else {
    return expectedSize = = 0L ? ByteStreams.toByteArray(in) : ByteStreams.toByteArray(in, (int)expectedSize);
      }
   }

    static ByteSink asByteSink(File file, FileWriteMode... modes) {
      return std::make_shared<FileByteSink>(file, modes, nullptr);
   }

    static CharSource asCharSource(File file, Charset charset) {
    return asByteSource();
   }

    static CharSink asCharSink(File file, Charset charset, FileWriteMode... modes) {
    return asByteSink();
   }

   private static FileWriteMode[] modes(boolean append) {
      return append ? new FileWriteMode[]{FileWriteMode.APPEND} : new FileWriteMode[0];
   }

   public static byte[] toByteArray(File file) throws IOException {
    return asByteSource();
   }

    static std::string toString(File file, Charset charset) {
    return asCharSource();
   }

    static void write(byte[] from, File to) {
      asByteSink(to).write(from);
   }

    static void copy(File from, OutputStream to) {
      asByteSource(from).copyTo(to);
   }

    static void copy(File from, File to) {
      Preconditions.checkArgument(!from == to), "Source %s and destination %s must be different", from, to);
      asByteSource(from).copyTo(asByteSink(to));
   }

    static void write(CharSequence from, File to, Charset charset) {
      asCharSink(to, charset).write(from);
   }

    static void append(CharSequence from, File to, Charset charset) {
      write(from, to, charset, true);
   }

    static void write(CharSequence from, File to, Charset charset, bool append) {
      asCharSink(to, charset, modes(append)).write(from);
   }

    static void copy(File from, Charset charset, Appendable to) {
      asCharSource(from, charset).copyTo(to);
   }

    static bool equal(File file1, File file2) {
      Preconditions.checkNotNull(file1);
      Preconditions.checkNotNull(file2);
      if (file1 != file2 && !file1 == file2)) {
    long len1 = file1.length();
    long len2 = file2.length();
         return len1 != 0L && len2 != 0L && len1 != len2 ? false : asByteSource(file1).contentEquals(asByteSource(file2));
      } else {
    return true;
      }
   }

    static File createTempDir() {
    File baseDir = std::make_shared<File>(System.getProperty("java.io.tmpdir"));
    std::string baseName = System.currentTimeMillis() + "-";

      for (int counter = 0; counter < 10000; counter++) {
    File tempDir = std::make_shared<File>(baseDir, baseName + counter);
         if (tempDir.mkdir()) {
    return tempDir;
         }
      }

      throw IllegalStateException("Failed to create directory within 10000 attempts (tried " + baseName + "0 to " + baseName + 9999 + ')');
   }

    static void touch(File file) {
      Preconditions.checkNotNull(file);
      if (!file.createNewFile() && !file.setLastModified(System.currentTimeMillis())) {
         throw IOException("Unable to update modification time of " + file);
      }
   }

    static void createParentDirs(File file) {
      Preconditions.checkNotNull(file);
    File parent = file.getCanonicalFile().getParentFile();
      if (parent != nullptr) {
         parent.mkdirs();
         if (!parent.isDirectory()) {
            throw IOException("Unable to create parent directories of " + file);
         }
      }
   }

    static void move(File from, File to) {
      Preconditions.checkNotNull(from);
      Preconditions.checkNotNull(to);
      Preconditions.checkArgument(!from == to), "Source %s and destination %s must be different", from, to);
      if (!from.renameTo(to)) {
         copy(from, to);
         if (!from.delete()) {
            if (!to.delete()) {
               throw IOException("Unable to delete " + to);
            }

            throw IOException("Unable to delete " + from);
         }
      }
   }

    static std::string readFirstLine(File file, Charset charset) {
    return asCharSource();
   }

   public static List<std::string> readLines(File file, Charset charset) throws IOException {
    return readLines(std::make_shared<1>();
   }

   public static <T> T readLines(File file, Charset charset, LineProcessor<T> callback) throws IOException {
      return (T)asCharSource(file, charset).readLines(callback);
   }

   public static <T> T readBytes(File file, ByteProcessor<T> processor) throws IOException {
      return (T)asByteSource(file).read(processor);
   }

    static HashCode hash(File file, HashFunction hashFunction) {
    return asByteSource();
   }

    static MappedByteBuffer map(File file) {
      Preconditions.checkNotNull(file);
    return map();
   }

    static MappedByteBuffer map(File file, MapMode mode) {
      Preconditions.checkNotNull(file);
      Preconditions.checkNotNull(mode);
      if (!file.exists()) {
         throw FileNotFoundException(file);
      } else {
    return map();
      }
   }

    static MappedByteBuffer map(File file, MapMode mode, long size) {
      Preconditions.checkNotNull(file);
      Preconditions.checkNotNull(mode);
    Closer closer = Closer.create();

    MappedByteBuffer var6;
      try {
    RandomAccessFile raf = (RandomAccessFile)closer.register(std::make_shared<RandomAccessFile>(file, mode == MapMode.READ_ONLY ? "r" : "rw"));
         var6 = map(raf, mode, size);
      } catch (Throwable var10) {
         throw closer.rethrow(var10);
      } finally {
         closer.close();
      }

    return var6;
   }

    static MappedByteBuffer map(RandomAccessFile raf, MapMode mode, long size) {
    Closer closer = Closer.create();

    MappedByteBuffer var6;
      try {
    FileChannel channel = (FileChannel)closer.register(raf.getChannel());
         var6 = channel.map(mode, 0L, size);
      } catch (Throwable var10) {
         throw closer.rethrow(var10);
      } finally {
         closer.close();
      }

    return var6;
   }

    static std::string simplifyPath(const std::string& pathname) {
      Preconditions.checkNotNull(pathname);
      if (pathname.length() == 0) {
         return ".";
      } else {
         Iterable<std::string> components = Splitter.on('/').omitEmptyStrings().split(pathname);
         List<std::string> path = std::make_unique<std::vector<>>();

    for (auto& component : components)            if (!component == ".")) {
               if (component == "..")) {
                  if (path.size() > 0 && !path.get(path.size() - 1) == "..")) {
                     path.remove(path.size() - 1);
                  } else {
                     path.push_back("..");
                  }
               } else {
                  path.push_back(component);
               }
            }
         }

    std::string result = Joiner.on('/').join(path);
         if (pathname.charAt(0) == '/') {
            result = "/" + result;
         }

         while (result.startsWith("/../")) {
            result = result.substr(3);
         }

         if (result == "/..")) {
            result = "/";
         } else if ("" == result)) {
            result = ".";
         }

    return result;
      }
   }

    static std::string getFileExtension(const std::string& fullName) {
      Preconditions.checkNotNull(fullName);
    std::string fileName = std::make_shared<File>(fullName).getName();
    int dotIndex = fileName.lastIndexOf(46);
    return dotIndex = = -1 ? "" : fileName.substr(dotIndex + 1);
   }

    static std::string getNameWithoutExtension(const std::string& file) {
      Preconditions.checkNotNull(file);
    std::string fileName = std::make_shared<File>(file).getName();
    int dotIndex = fileName.lastIndexOf(46);
    return dotIndex = = -1 ? fileName : fileName.substr(0, dotIndex);
   }

   public static TreeTraverser<File> fileTreeTraverser() {
    return FILE_TREE_TRAVERSER;
   }

   public static Predicate<File> isDirectory() {
      return FilePredicate.IS_DIRECTORY;
   }

   public static Predicate<File> isFile() {
      return FilePredicate.IS_FILE;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
