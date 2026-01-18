#pragma once
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace bucket {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Bucket {
public:
 std::string m_name;
private
 HashMap<Path, Texture> m_textures = std::make_unique<HashMap<>>();
 static const FileSystem m_fs = FileSystems.getDefault();
private
 PredicatedFileWatcher m_fileWatcher = new PredicatedFileWatcher(
 string->this->HasTexture(string), string->{
 Texture texture = this->getTexture(string);
 texture.reloadFromFile(string);
 ModelManager.instance.reloadAllOutfits();
 });

public
 Bucket() { DebugFileWatcher.instance.add(this->m_fileWatcher); }

 void AddTexture(Path path, Texture texture) {
 if (texture != nullptr) {
 this->m_textures.put(path, texture);
 }
 }

 void AddTexture(const std::string &string, Texture texture) {
 if (texture != nullptr) {
 this->AddTexture(m_fs.getPath(string), texture);
 }
 }

 void Dispose() {
 for (Texture texture : this->m_textures.values()) {
 texture.destroy();
 }

 this->m_textures.clear();
 }

 Texture getTexture(Path path) { return this->m_textures.get(path); }

 Texture getTexture(const std::string &string) {
 return this->getTexture(m_fs.getPath(string);
 }

 bool HasTexture(Path path) { return this->m_textures.containsKey(path); }

 bool HasTexture(const std::string &string) {
 return this->HasTexture(m_fs.getPath(string);
 }

 std::string getName() { return this->m_name; }

 void setName(const std::string &string) { this->m_name = string; }

 void forgetTexture(const std::string &string) {
 this->m_textures.remove(string);
 }
}
} // namespace bucket
} // namespace core
} // namespace zombie
