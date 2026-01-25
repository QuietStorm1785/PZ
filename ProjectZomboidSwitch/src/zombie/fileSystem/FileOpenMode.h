
#pragma once
#include <string>
#include <sstream>

namespace zombie::fileSystem {

enum FileOpenMode : uint32_t {
    None  = 0,
    Read  = 1 << 0,
    Write = 1 << 1,
    Open  = 1 << 2,
    Create = 1 << 3,
    Stream = 1 << 4,
    CreateAndWrite = Create | Write, // 8 | 2 = 10
    OpenAndRead = Open | Read        // 4 | 1 = 5
};

inline std::string toStringMode(uint32_t mode) {
    std::string result;
    if (mode & FileOpenMode::Read) result += 'r';
    if (mode & FileOpenMode::Write) result += 'w';
    if (mode & FileOpenMode::Open) result += 'o';
    if (mode & FileOpenMode::Create) result += 'c';
    if (mode & FileOpenMode::Stream) result += 's';
    return result;
}

} // namespace zombie::fileSystem
