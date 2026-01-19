#pragma once
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileGuidTable {
public:
public
 ArrayList<FileGuidPair> files = std::make_unique<ArrayList<>>();
private
 Map<String, String> guidToPath =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
private
 Map<String, String> pathToGuid =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

 void setModID(std::string_view string) {
 for (FileGuidPair fileGuidPair : this->files) {
 fileGuidPair.guid = string + "-" + fileGuidPair.guid;
 }
 }

 void mergeFrom(FileGuidTable fileGuidTable0) {
 this->files.addAll(fileGuidTable0.files);
 }

 void loaded() {
 for (FileGuidPair fileGuidPair : this->files) {
 this->guidToPath.put(fileGuidPair.guid, fileGuidPair.path);
 this->pathToGuid.put(fileGuidPair.path, fileGuidPair.guid);
 }
 }

 void clear() {
 this->files.clear();
 this->guidToPath.clear();
 this->pathToGuid.clear();
 }

 std::string getFilePathFromGuid(std::string_view string) {
 return this->guidToPath.get(string);
 }

 std::string getGuidFromFilePath(std::string_view string) {
 return this->pathToGuid.get(string);
 }
}
} // namespace zombie
