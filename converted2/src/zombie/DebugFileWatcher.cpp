#include "zombie/DebugFileWatcher.h"

namespace zombie {

private
DebugFileWatcher::DebugFileWatcher() {
  // TODO: Implement DebugFileWatcher
  return nullptr;
}

void DebugFileWatcher::init() {
  // TODO: Implement init
}

void DebugFileWatcher::registerDirRecursive(Path path) {
  // TODO: Implement registerDirRecursive
}

FileVisitResult DebugFileWatcher::preVisitDirectory(Path path,
                                                    BasicFileAttributes var2) {
  // TODO: Implement preVisitDirectory
  return nullptr;
}

void DebugFileWatcher::registerDir(Path path) {
  // TODO: Implement registerDir
}

void DebugFileWatcher::addWatchedFile(const std::string &string) {
  // TODO: Implement addWatchedFile
}

void DebugFileWatcher::add(PredicatedFileWatcher predicatedFileWatcher) {
  // TODO: Implement add
}

void DebugFileWatcher::addDirectory(const std::string &string) {
  // TODO: Implement addDirectory
}

void DebugFileWatcher::addDirectoryRecurse(const std::string &string) {
  // TODO: Implement addDirectoryRecurse
}

void DebugFileWatcher::remove(PredicatedFileWatcher predicatedFileWatcher) {
  // TODO: Implement remove
}

void DebugFileWatcher::update() {
  // TODO: Implement update
}

void DebugFileWatcher::swapWatcherArrays() {
  // TODO: Implement swapWatcherArrays
}

} // namespace zombie
