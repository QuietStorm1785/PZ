
#include "zombie/fileSystem/FileOpenMode.h"

namespace zombie::fileSystem {

std::string toStringMode(uint32_t mode) {
    std::string result;
    if (mode & FileOpenMode::Read) result += 'r';
    if (mode & FileOpenMode::Write) result += 'w';
    if (mode & FileOpenMode::Open) result += 'o';
    if (mode & FileOpenMode::Create) result += 'c';
    if (mode & FileOpenMode::Stream) result += 's';
    return result;
}

} // namespace zombie::fileSystem
