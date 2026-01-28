#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <istream>

namespace zombie {
namespace io {

class BufferedInputStream {
public:
    BufferedInputStream(std::istream& stream) : stream_(stream) {}
    // Add methods as needed for your use case
private:
    std::istream& stream_;
};

using BufferedInputStreamPtr = std::shared_ptr<BufferedInputStream>;

} // namespace io
} // namespace zombie
