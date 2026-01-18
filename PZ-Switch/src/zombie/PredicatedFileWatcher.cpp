#include "zombie/PredicatedFileWatcher.h"

namespace zombie {

public
PredicatedFileWatcher::PredicatedFileWatcher(
 Predicate<String> predicate,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 // TODO: Implement PredicatedFileWatcher
 return nullptr;
}

public
PredicatedFileWatcher::PredicatedFileWatcher(
 const std::string &path,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 // TODO: Implement PredicatedFileWatcher
 return nullptr;
}

public
PredicatedFileWatcher::PredicatedFileWatcher(
 const std::string &path, Predicate<String> predicate,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 // TODO: Implement PredicatedFileWatcher
 return nullptr;
}

std::string PredicatedFileWatcher::getPath() {
 // TODO: Implement getPath
 return "";
}

std::string PredicatedFileWatcher::processPath(const std::string &string) {
 // TODO: Implement processPath
 return "";
}

bool PredicatedFileWatcher::pathsEqual(const std::string &string) {
 // TODO: Implement pathsEqual
 return false;
}

void PredicatedFileWatcher::onModified(const std::string &entryKey) {
 // TODO: Implement onModified
}

void PredicatedFileWatcher::call(const std::string &string) {
 // TODO: Implement call
}

void PredicatedFileWatcher::call(T var1) {
 // TODO: Implement call
}

void PredicatedFileWatcher::call(const std::string &entryKey) {
 // TODO: Implement call
}

} // namespace zombie
