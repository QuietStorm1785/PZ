#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AssetPath {
public:
 std::string m_path;

 public AssetPath(const std::string& path) {
 this->m_path = path;
 }

 bool isValid() {
 return !StringUtils.isNullOrEmpty(this->m_path);
 }

 int getHash() {
 return this->m_path.hashCode();
 }

 std::string getPath() {
 return this->m_path;
 }

 std::string toString() {
 return this->getClass().getSimpleName() + "{ \"" + this->getPath() + "\" }";
 }
}
} // namespace asset
} // namespace zombie
