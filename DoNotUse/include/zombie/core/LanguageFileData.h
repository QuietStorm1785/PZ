#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {

class LanguageFileData {
public:
    std::string name;
    std::string text;
    std::string charset;
    std::string base;
    bool azerty;
}
} // namespace core
} // namespace zombie
