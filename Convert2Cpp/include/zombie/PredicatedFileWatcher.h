#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PredicatedFileWatcher/GenericPredicatedFileWatcherCallback.h"
#include "zombie/PredicatedFileWatcher/IPredicatedDataPacketFileWatcherCallback.h"
#include "zombie/PredicatedFileWatcher/IPredicatedFileWatcherCallback.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {


class PredicatedFileWatcher {
public:
    const std::string m_path;
   private final Predicate<String> m_predicate;
    const IPredicatedFileWatcherCallback m_callback;

    public PredicatedFileWatcher(Predicate<String> var1, IPredicatedFileWatcherCallback var2) {
      this(nullptr, var1, var2);
   }

    public PredicatedFileWatcher(const std::string& var1, IPredicatedFileWatcherCallback var2) {
      this(var1, nullptr, var2);
   }

   public <T> PredicatedFileWatcher(String var1, Class<T> var2, IPredicatedDataPacketFileWatcherCallback<T> var3) {
      this(var1, nullptr, new GenericPredicatedFileWatcherCallback(var2, var3));
   }

    public PredicatedFileWatcher(const std::string& var1, Predicate<String> var2, IPredicatedFileWatcherCallback var3) {
      this.m_path = this.processPath(var1);
      this.m_predicate = var2 != nullptr ? var2 : this::pathsEqual;
      this.m_callback = var3;
   }

    std::string getPath() {
      return this.m_path;
   }

    std::string processPath(const std::string& var1) {
      return var1 != nullptr ? ZomboidFileSystem.processFilePath(var1, File.separatorChar) : nullptr;
   }

    bool pathsEqual(const std::string& var1) {
      return var1 == this.m_path);
   }

    void onModified(const std::string& var1) {
      if (this.m_predicate.test(var1)) {
         this.m_callback.call(var1);
      }
   }
}
} // namespace zombie
