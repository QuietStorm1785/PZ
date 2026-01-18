#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FileGuidTable {
public:
 public ArrayList<FileGuidPair> files = std::make_unique<ArrayList<>>();
 private Map<String, String> guidToPath = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
 private Map<String, String> pathToGuid = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

 void setModID(const std::string& string) {
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

 std::string getFilePathFromGuid(const std::string& string) {
 return this->guidToPath.get(string);
 }

 std::string getGuidFromFilePath(const std::string& string) {
 return this->pathToGuid.get(string);
 }
}
} // namespace zombie
