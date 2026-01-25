#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class PositionInputStream : public InputStream {
public:
    std::shared_ptr<TexturePackDevice> m_device;
    std::shared_ptr<InputStream> m_stream;
    int64_t pos;
    int64_t mark;

    PositionInputStream(std::shared_ptr<TexturePackDevice> device, std::shared_ptr<InputStream> stream)
        : m_device(device), m_stream(stream), pos(0), mark(0) {}

    int64_t getPosition() const { return pos; }

    int read() override {
        int value = m_stream->read();
        if (value >= 0) ++pos;
        return value;
    }

    int read(uint8_t* buffer, int offset, int length) override {
        int n = m_stream->read(buffer, offset, length);
        if (n > 0) pos += n;
        return n;
    }

    int64_t skip(int64_t n) override {
        int64_t skipped = m_stream->skip(n);
        if (skipped > 0) pos += skipped;
        return skipped;
    }

    void mark(int readlimit) override {
        m_stream->mark(readlimit);
        mark = pos;
    }

    void reset() override {
        if (!m_stream->markSupported()) {
            throw std::runtime_error("Mark not supported.");
        }
        m_stream->reset();
        pos = mark;
    }
};
} // namespace fileSystem
} // namespace zombie
