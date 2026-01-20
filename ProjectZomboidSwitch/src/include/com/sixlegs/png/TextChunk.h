#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class TextChunk {
public:
    virtual ~TextChunk() = default;
    std::string getKeyword();

    std::string getTranslatedKeyword();

    std::string getLanguage();

    std::string getText();

    int getType();
}
} // namespace png
} // namespace sixlegs
} // namespace com
