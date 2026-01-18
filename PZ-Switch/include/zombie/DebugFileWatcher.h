#pragma once
#include "zombie/core/logger/ExceptionLogger.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugFileWatcher {
public:
private
 HashMap<Path, String> m_watchedFiles = std::make_unique<HashMap<>>();
private
 HashMap<WatchKey, Path> m_watchkeyMapping =
 std::make_unique<HashMap<>>();
private
 ArrayList<PredicatedFileWatcher> m_predicateWatchers =
 std::make_unique<ArrayList<>>();
private
 ArrayList<PredicatedFileWatcher> m_predicateWatchersInvoking =
 std::make_unique<ArrayList<>>();
 const FileSystem m_fs = FileSystems.getDefault();
 WatchService m_watcher;
 bool m_predicateWatchersInvokingDirty = true;
 long m_modificationTime = -1L;
private
 ArrayList<String> m_modifiedFiles = std::make_unique<ArrayList<>>();
 static const DebugFileWatcher instance = new DebugFileWatcher();

private
 DebugFileWatcher() {}

 void init() {
 try {
 this->m_watcher = this->m_fs.newWatchService();
 this->registerDirRecursive(
 this->m_fs.getPath(ZomboidFileSystem.instance.getMediaRootPath()));
 this->registerDirRecursive(
 this->m_fs.getPath(ZomboidFileSystem.instance.getMessagingDir()));
 } catch (IOException iOException) {
 this->m_watcher = nullptr;
 }
 }

 void registerDirRecursive(Path path) {
 try {
 Files.walkFileTree(path, std::make_unique<SimpleFileVisitor<Path>>() {
 FileVisitResult preVisitDirectory(Path path, BasicFileAttributes var2) {
 DebugFileWatcher.this->registerDir(path);
 return FileVisitResult.CONTINUE;
 }
 });
} catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 this->m_watcher = nullptr;
}
} // namespace zombie

void registerDir(Path path) {
 try {
 WatchKey watchKey =
 path.register(this->m_watcher, StandardWatchEventKinds.ENTRY_MODIFY,
 StandardWatchEventKinds.ENTRY_CREATE);
 this->m_watchkeyMapping.put(watchKey, path);
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 this->m_watcher = nullptr;
 }
}

void addWatchedFile(const std::string &string) {
 if (string != nullptr) {
 this->m_watchedFiles.put(this->m_fs.getPath(string), string);
 }
}

void add(PredicatedFileWatcher predicatedFileWatcher) {
 if (!this->m_predicateWatchers.contains(predicatedFileWatcher) {
 this->addWatchedFile(predicatedFileWatcher.getPath());
 this->m_predicateWatchers.add(predicatedFileWatcher);
 this->m_predicateWatchersInvokingDirty = true;
 }
}

void addDirectory(const std::string &string) {
 if (string != nullptr) {
 this->registerDir(this->m_fs.getPath(string);
 }
}

void addDirectoryRecurse(const std::string &string) {
 if (string != nullptr) {
 this->registerDirRecursive(this->m_fs.getPath(string);
 }
}

void remove(PredicatedFileWatcher predicatedFileWatcher) {
 this->m_predicateWatchers.remove(predicatedFileWatcher);
}

void update() {
 if (this->m_watcher != nullptr) {
 for (WatchKey watchKey = this->m_watcher.poll(); watchKey != nullptr;
 watchKey = this->m_watcher.poll()) {
 try {
 Path path0 = this->m_watchkeyMapping.getOrDefault(watchKey, nullptr);

 for (WatchEvent watchEvent : watchKey.pollEvents()) {
 if (watchEvent.kind() == StandardWatchEventKinds.ENTRY_MODIFY) {
 Path path1 = (Path)watchEvent.context();
 Path path2 = path0.resolve(path1);
 std::string string0 =
 this->m_watchedFiles.getOrDefault(path2, path2.toString());
 this->m_modificationTime = System.currentTimeMillis();
 if (!this->m_modifiedFiles.contains(string0) {
 this->m_modifiedFiles.add(string0);
 }
 } else if (watchEvent.kind() ==
 StandardWatchEventKinds.ENTRY_CREATE) {
 Path path3 = (Path)watchEvent.context();
 Path path4 = path0.resolve(path3);
 if (Files.isDirectory(path4) {
 this->registerDirRecursive(path4);
 } else {
 std::string string1 =
 this->m_watchedFiles.getOrDefault(path4, path4.toString());
 this->m_modificationTime = System.currentTimeMillis();
 if (!this->m_modifiedFiles.contains(string1) {
 this->m_modifiedFiles.add(string1);
 }
 }
 }
 }
 } finally {
 if (!watchKey.reset()) {
 this->m_watchkeyMapping.remove(watchKey);
 }
 }
 }

 if (!this->m_modifiedFiles.empty()) {
 if (this->m_modificationTime + 2000L <= System.currentTimeMillis()) {
 for (int int0 = this->m_modifiedFiles.size() - 1; int0 >= 0; int0--) {
 std::string string2 = this->m_modifiedFiles.remove(int0);
 this->swapWatcherArrays();

 for (PredicatedFileWatcher predicatedFileWatcher :
 this->m_predicateWatchersInvoking) {
 predicatedFileWatcher.onModified(string2);
 }
 }
 }
 }
 }
}

void swapWatcherArrays() {
 if (this->m_predicateWatchersInvokingDirty) {
 this->m_predicateWatchersInvoking.clear();
 this->m_predicateWatchersInvoking.addAll(this->m_predicateWatchers);
 this->m_predicateWatchersInvokingDirty = false;
 }
}
}
} // namespace zombie
