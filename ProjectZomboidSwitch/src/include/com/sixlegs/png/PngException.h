#pragma once
#include <stdexcept>
#include <string>

namespace com {
namespace sixlegs {
namespace png {

// Simple PNG exception carrying a 'fatal' flag.
class PngException : public std::runtime_error {
public:
    explicit PngException(const std::string& msg, bool fatal = false)
        : std::runtime_error(msg), fatal_(fatal) {}

    bool isFatal() const { return fatal_; }

private:
    bool fatal_;
};

} // namespace png
} // namespace sixlegs
} // namespace com
