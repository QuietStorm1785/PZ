#pragma once
#include "org/mindrot/jbcrypt/BCrypt.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace secure {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZcrypt {
public:
 static std::string salt = "$2a$12$O/BFHoDFPrfFaNPAACmWpu";

 static std::string hash(std::string_view string, bool boolean0) {
 return boolean0 && string.empty() ? string : BCrypt.hashpw(string, salt);
 }

 static std::string hash(std::string_view string) { return hash(); }

 static std::string hashSalt(std::string_view string) {
 return BCrypt.hashpw(string, BCrypt.gensalt(12);
 }

 static bool checkHashSalt(std::string_view string1,
 std::string_view string0) {
 return BCrypt.checkpw(string0, string1);
 }
}
} // namespace secure
} // namespace core
} // namespace zombie
