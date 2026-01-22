#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/DebugFileWatcher/1.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class DebugFileWatcher {
public:
   private const std::unordered_map<Path, std::string> m_watchedFiles = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<WatchKey, Path> m_watchkeyMapping = std::make_unique<std::unordered_map<>>();
   private const std::vector<PredicatedFileWatcher> m_predicateWatchers = std::make_unique<std::vector<>>();
   private const std::vector<PredicatedFileWatcher> m_predicateWatchersInvoking = std::make_unique<std::vector<>>();
    const FileSystem m_fs = FileSystems.getDefault();
    WatchService m_watcher;
    bool m_predicateWatchersInvokingDirty = true;
    long m_modificationTime = -1L;
   private const std::vector<std::string> m_modifiedFiles = std::make_unique<std::vector<>>();
    static const DebugFileWatcher instance = std::make_shared<DebugFileWatcher>();

    private DebugFileWatcher() {
   }

    void init() {
      try {
         this.m_watcher = this.m_fs.newWatchService();
         this.registerDirRecursive(this.m_fs.getPath(ZomboidFileSystem.instance.getMediaRootPath()));
         this.registerDirRecursive(this.m_fs.getPath(ZomboidFileSystem.instance.getMessagingDir()));
      } catch (IOException var2) {
         this.m_watcher = nullptr;
      }
   }

    void registerDirRecursive(Path var1) {
      try {
         Files.walkFileTree(var1, std::make_shared<1>(this));
      } catch (IOException var3) {
         ExceptionLogger.logException(var3);
         this.m_watcher = nullptr;
      }
   }

    void registerDir(Path var1) {
      try {
    WatchKey var2 = var1.register(this.m_watcher, StandardWatchEventKinds.ENTRY_MODIFY, StandardWatchEventKinds.ENTRY_CREATE);
         this.m_watchkeyMapping.put(var2, var1);
      } catch (IOException var3) {
         ExceptionLogger.logException(var3);
         this.m_watcher = nullptr;
      }
   }

    void addWatchedFile(const std::string& var1) {
      if (var1 != nullptr) {
         this.m_watchedFiles.put(this.m_fs.getPath(var1), var1);
      }
   }

    void add(PredicatedFileWatcher var1) {
      if (!this.m_predicateWatchers.contains(var1)) {
         this.addWatchedFile(var1.getPath());
         this.m_predicateWatchers.push_back(var1);
         this.m_predicateWatchersInvokingDirty = true;
      }
   }

    void addDirectory(const std::string& var1) {
      if (var1 != nullptr) {
         this.registerDir(this.m_fs.getPath(var1));
      }
   }

    void addDirectoryRecurse(const std::string& var1) {
      if (var1 != nullptr) {
         this.registerDirRecursive(this.m_fs.getPath(var1));
      }
   }

    void remove(PredicatedFileWatcher var1) {
      this.m_predicateWatchers.remove(var1);
   }

    void update() {
      if (this.m_watcher != nullptr) {
         for (WatchKey var1 = this.m_watcher.poll(); var1 != nullptr; var1 = this.m_watcher.poll()) {
            try {
    Path var2 = this.m_watchkeyMapping.getOrDefault(var1, nullptr);

               for (WatchEvent var4 : var1.pollEvents()) {
                  if (var4.kind() == StandardWatchEventKinds.ENTRY_MODIFY) {
    Path var6 = (Path)var4.context();
    Path var7 = var2.resolve(var6);
    std::string var8 = this.m_watchedFiles.getOrDefault(var7, var7);
                     this.m_modificationTime = System.currentTimeMillis();
                     if (!this.m_modifiedFiles.contains(var8)) {
                        this.m_modifiedFiles.push_back(var8);
                     }
                  } else if (var4.kind() == StandardWatchEventKinds.ENTRY_CREATE) {
    Path var16 = (Path)var4.context();
    Path var17 = var2.resolve(var16);
                     if (Files.isDirectory(var17)) {
                        this.registerDirRecursive(var17);
                     } else {
    std::string var18 = this.m_watchedFiles.getOrDefault(var17, var17);
                        this.m_modificationTime = System.currentTimeMillis();
                        if (!this.m_modifiedFiles.contains(var18)) {
                           this.m_modifiedFiles.push_back(var18);
                        }
                     }
                  }
               }
            } finally {
               if (!var1.reset()) {
                  this.m_watchkeyMapping.remove(var1);
               }
            }
         }

         if (!this.m_modifiedFiles.empty()) {
            if (this.m_modificationTime + 2000L <= System.currentTimeMillis()) {
               for (int var12 = this.m_modifiedFiles.size() - 1; var12 >= 0; var12--) {
    std::string var13 = this.m_modifiedFiles.remove(var12);
                  this.swapWatcherArrays();

                  for (PredicatedFileWatcher var15 : this.m_predicateWatchersInvoking) {
                     var15.onModified(var13);
                  }
               }
            }
         }
      }
   }

    void swapWatcherArrays() {
      if (this.m_predicateWatchersInvokingDirty) {
         this.m_predicateWatchersInvoking.clear();
         this.m_predicateWatchersInvoking.addAll(this.m_predicateWatchers);
         this.m_predicateWatchersInvokingDirty = false;
      }
   }
}
} // namespace zombie
