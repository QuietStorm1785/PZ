#pragma once
#include "zombie/core/math/PZMath.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GameVersion {
public:
 const int m_major;
 const int m_minor;
 const std::string m_suffix;
 const std::string m_string;

public
 GameVersion(int major, int minor, const std::string &suffix) {
 if (major < 0) {
 throw IllegalArgumentException(
 "major version must be greater than zero");
 } else if (minor >= 0 && minor <= 999) {
 this->m_major = major;
 this->m_minor = minor;
 this->m_suffix = suffix;
 this->m_string =
 String.format(Locale.ENGLISH, "%d.%d%s", this->m_major, this->m_minor,
 this->m_suffix.empty() ? "" : this->m_suffix);
 } else {
 throw IllegalArgumentException("minor version must be from 0 to 999");
 }
 }

 int getMajor() { return this->m_major; }

 int getMinor() { return this->m_minor; }

 std::string getSuffix() { return this->m_suffix; }

 int getInt() { return this->m_major * 1000 + this->m_minor; }

 bool isGreaterThan(GameVersion rhs) { return this->getInt() > rhs.getInt(); }

 bool isGreaterThanOrEqualTo(GameVersion rhs) {
 return this->getInt() >= rhs.getInt();
 }

 bool isLessThan(GameVersion rhs) { return this->getInt() < rhs.getInt(); }

 bool isLessThanOrEqualTo(GameVersion rhs) {
 return this->getInt() <= rhs.getInt();
 }

 bool equals(void *obj) {
 if (obj == this) {
 return true;
 } else {
 return !(obj instanceof GameVersion gameVersion)
 ? false
 : gameVersion.m_major == this->m_major &&
 gameVersion.m_minor == this->m_minor;
 }
 }

 std::string toString() { return this->m_string; }

 static GameVersion parse(const std::string &str) {
 Matcher matcher = Pattern.compile("([0-9]+)\\.([0-9]+)(.*)").matcher(str);
 if (matcher.matches()) {
 int int0 = PZMath.tryParseInt(matcher.group(1), 0);
 int int1 = PZMath.tryParseInt(matcher.group(2), 0);
 std::string string = matcher.group(3);
 return new GameVersion(int0, int1, string);
 } else {
 throw IllegalArgumentException("invalid game version \"" + str +
 "\"");
 }
 }
}
} // namespace core
} // namespace zombie
