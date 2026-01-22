#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/mindrot/jbcrypt/BCrypt.h"

namespace zombie {
namespace core {
namespace secure {


class PZcrypt {
public:
    static std::string salt = "$2a$12$O/BFHoDFPrfFaNPAACmWpu";

    static std::string hash(const std::string& var0, bool var1) {
      return var1 && var0.empty() ? var0 : BCrypt.hashpw(var0, salt);
   }

    static std::string hash(const std::string& var0) {
    return hash();
   }

    static std::string hashSalt(const std::string& var0) {
      return BCrypt.hashpw(var0, BCrypt.gensalt(12));
   }

    static bool checkHashSalt(const std::string& var0, const std::string& var1) {
      return BCrypt.checkpw(var1, var0);
   }
}
} // namespace secure
} // namespace core
} // namespace zombie
