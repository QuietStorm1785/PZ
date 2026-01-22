#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/junit/Assert.h"
#include "org/junit/Test.h"

namespace zombie {
namespace core {
namespace secure {


class PZCryptTest : public Assert {
public:
    void hash() {
    std::string var1 = PZcrypt.hash("123456");
      assertEquals("$2a$12$O/BFHoDFPrfFaNPAACmWpuPkOtwkznuRQ7saS6/ouHjTT9KuVcKfq", var1);
   }

    void hashSalt() {
    std::string var1 = PZcrypt.hashSalt("1234567");
    std::string var2 = PZcrypt.hashSalt("1234567");
      assertNotEquals(var1, var2);
    bool var3 = PZcrypt.checkHashSalt(var1, "1234567");
      assertEquals(true, var3);
      var3 = PZcrypt.checkHashSalt(var1, "1238567");
      assertEquals(false, var3);
      var3 = PZcrypt.checkHashSalt(var2, "1234567");
      assertEquals(true, var3);
      var3 = PZcrypt.checkHashSalt(var2, "dnfgdf;godf;ogdogi;");
      assertEquals(false, var3);
   }
}
} // namespace secure
} // namespace core
} // namespace zombie
