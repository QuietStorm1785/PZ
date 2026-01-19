#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class FileGuidPair {
public:
    std::string path;
    std::string guid;
}
} // namespace zombie
