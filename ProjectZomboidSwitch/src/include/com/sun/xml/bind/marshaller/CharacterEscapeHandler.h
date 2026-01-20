#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {


class CharacterEscapeHandler {
public:
    virtual ~CharacterEscapeHandler() = default;
    void escape(char[] var1, int var2, int var3, bool var4, Writer var5);
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
