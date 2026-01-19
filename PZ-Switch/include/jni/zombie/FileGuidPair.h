#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class FileGuidPair {
:
    std::string path;
    std::string guid;
}
} // namespace zombie
