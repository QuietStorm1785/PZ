#pragma once
#include "zombie/debug/DebugLog.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * PredicatedFileWatcher An advanced form of the regular DebugFileWatcher
 */
class PredicatedFileWatcher {
public:
 const std::string m_path;
private
 Predicate<String> m_predicate;
private
 PredicatedFileWatcher.IPredicatedFileWatcherCallback m_callback;

public
 PredicatedFileWatcher(
 Predicate<String> predicate,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 this(nullptr, predicate, callback);
 }

public
 PredicatedFileWatcher(
 std::string_view path,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 this(path, nullptr, callback);
 }

 public<T> PredicatedFileWatcher(
 String path, Class<T> clazz,
 PredicatedFileWatcher.IPredicatedDataPacketFileWatcherCallback<T>
 callback) {
 this(path, nullptr,
 new PredicatedFileWatcher.GenericPredicatedFileWatcherCallback(
 clazz, callback);
 }

public
 PredicatedFileWatcher(
 std::string_view path, Predicate<String> predicate,
 PredicatedFileWatcher.IPredicatedFileWatcherCallback callback) {
 this->m_path = this->processPath(path);
 this->m_predicate = predicate != nullptr ? predicate : this ::pathsEqual;
 this->m_callback = callback;
 }

 std::string getPath() { return this->m_path; }

 std::string processPath(std::string_view string) {
 return string != nullptr
 ? ZomboidFileSystem.processFilePath(string, File.separatorChar)
 : nullptr;
 }

 bool pathsEqual(std::string_view string) {
 return string == this->m_path);
 }

 void onModified(std::string_view entryKey) {
 if (this->m_predicate.test(entryKey) {
 this->m_callback.call(entryKey);
 }
 }

public
 static class GenericPredicatedFileWatcherCallback<T> implements
 PredicatedFileWatcher.IPredicatedFileWatcherCallback {
 private
 Class<T> m_class;
 private
 PredicatedFileWatcher.IPredicatedDataPacketFileWatcherCallback<T>
 m_callback;

 public
 GenericPredicatedFileWatcherCallback(
 Class<T> clazz,
 PredicatedFileWatcher.IPredicatedDataPacketFileWatcherCallback<T>
 iPredicatedDataPacketFileWatcherCallback) {
 this->m_class = clazz;
 this->m_callback = iPredicatedDataPacketFileWatcherCallback;
 }

 void call(std::string_view string) {
 void *object;
 try {
 object = PZXmlUtil.parse(this->m_class, string);
 } catch (PZXmlParserException pZXmlParserException) {
 DebugLog.General.error("Exception thrown. " + pZXmlParserException);
 return;
 }

 this->m_callback.call((T)object);
 }
 }

 public interface IPredicatedDataPacketFileWatcherCallback<T> {
 void call(T var1);
 }

public
 interface IPredicatedFileWatcherCallback {
 void call(std::string_view entryKey);
 }
}
} // namespace zombie
