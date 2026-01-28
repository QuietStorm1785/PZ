#pragma once
#include <stdexcept>
#include <string>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class TextureFormatException : public std::runtime_error {
public:
    explicit TextureFormatException(const std::string& msg) : std::runtime_error(msg) {}
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
