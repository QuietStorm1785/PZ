#pragma once
#include "org/junit/Assert.h"
#include "org/junit/Test.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace secure {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZCryptTest : public Assert {
public:
  void hash() {
    std::string string = PZcrypt.hash("123456");
    assertEquals("$2a$12$O/BFHoDFPrfFaNPAACmWpuPkOtwkznuRQ7saS6/ouHjTT9KuVcKfq",
                 string);
  }

  void hashSalt() {
    std::string string0 = PZcrypt.hashSalt("1234567");
    std::string string1 = PZcrypt.hashSalt("1234567");
    assertNotEquals(string0, string1);
    bool boolean0 = PZcrypt.checkHashSalt(string0, "1234567");
    assertEquals(true, boolean0);
    boolean0 = PZcrypt.checkHashSalt(string0, "1238567");
    assertEquals(false, boolean0);
    boolean0 = PZcrypt.checkHashSalt(string1, "1234567");
    assertEquals(true, boolean0);
    boolean0 = PZcrypt.checkHashSalt(string1, "dnfgdf;godf;ogdogi;");
    assertEquals(false, boolean0);
  }
}
} // namespace secure
} // namespace core
} // namespace zombie
