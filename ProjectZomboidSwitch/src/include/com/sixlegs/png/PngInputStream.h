#pragma once
#include <cstdint>
#include <istream>
#include <vector>
#include <zlib.h>
#include <stdexcept>
#include <string>

namespace com {
namespace sixlegs {
namespace png {

class PngException : public std::runtime_error { using std::runtime_error::runtime_error; };

// Lightweight CRC32 wrapper using zlib
class PngCRC32 {
public:
    PngCRC32() { reset(); }
    void reset() { state_ = crc32(0L, Z_NULL, 0); }
    void update(uint8_t b) { state_ = crc32(state_, &b, 1); }
    void update(const uint8_t* buf, size_t len) { state_ = crc32(state_, buf, static_cast<uInt>(len)); }
    uint32_t getValue() const { return static_cast<uint32_t>(state_); }
private:
    uLong state_ = 0;
};

class PngInputStream {
public:
    explicit PngInputStream(std::istream& in) : in_(in), tmp_(4096), total_(0), length_(0), left_(8) {
        // verify PNG signature
        uint64_t sig = readLong();
        if (sig != 0x89504E470D0A1A0ALL) {
            throw PngException("Improper PNG signature");
        }
        total_ += 8;
    }

    int startChunk() {
        left_ = 8;
        length_ = readInt();
        if (length_ < 0) throw PngException("Bad chunk length");
        crc_.reset();
        int name = readInt();
        left_ = length_;
        total_ += 8;
        return name;
    }

    int endChunk(int name) {
        if (getRemaining() != 0) throw PngException("Chunk read length mismatch");
        left_ = 4;
        uint32_t got = crc_.getValue();
        int expected = readInt();
        if (got != static_cast<uint32_t>(expected)) throw PngException("Bad CRC in chunk");
        total_ += (length_ + 4);
        return static_cast<int>(got);
    }

    int read() {
        if (left_ == 0) return -1;
        int ch = in_.get();
        if (ch != EOF) { crc_.update(static_cast<uint8_t>(ch)); --left_; }
        return ch;
    }

    int read(uint8_t* buf, int off, int len) {
        if (len == 0) return 0;
        if (left_ == 0) return -1;
        int toRead = static_cast<int>(std::min<int64_t>(left_, len));
        in_.read(reinterpret_cast<char*>(buf + off), toRead);
        std::streamsize r = in_.gcount();
        if (r <= 0) return -1;
        crc_.update(buf + off, static_cast<size_t>(r));
        left_ -= static_cast<int>(r);
        return static_cast<int>(r);
    }

    int64_t skip(int64_t n) {
        int r = read(tmp_.data(), 0, static_cast<int>(std::min<int64_t>(tmp_.size(), n)));
        return r < 0 ? 0 : r;
    }

    void close() { /* no-op */ }

    bool readBoolean() { return readUnsignedByte() != 0; }

    int readUnsignedByte() {
        int v = read(); if (v < 0) throw std::runtime_error("EOF"); return v;
    }

    uint8_t readByte() { return static_cast<uint8_t>(readUnsignedByte()); }

    int readUnsignedShort() { int a = read(); int b = read(); if ((a|b) < 0) throw std::runtime_error("EOF"); return (a<<8) + b; }
    short readShort() { return static_cast<short>(readUnsignedShort()); }
    char readChar() { return static_cast<char>(readUnsignedShort()); }

    int readInt() { int a=read(), b=read(), c=read(), d=read(); if ((a|b|c|d)<0) throw std::runtime_error("EOF"); return (a<<24)|(b<<16)|(c<<8)|d; }

    uint64_t readLong() { uint64_t hi = static_cast<uint32_t>(readInt()); uint64_t lo = static_cast<uint32_t>(readInt()); return (hi<<32)|lo; }

    float readFloat() { uint32_t v = static_cast<uint32_t>(readInt()); float f; std::memcpy(&f, &v, sizeof(f)); return f; }
    double readDouble() { uint64_t v = readLong(); double d; std::memcpy(&d, &v, sizeof(d)); return d; }

    void readFully(uint8_t* buf, int len) { int off=0; while (off < len) { int r = read(buf, off, len-off); if (r<0) throw std::runtime_error("EOF"); off+=r; } }

    int skipBytes(int n) { return static_cast<int>(skip(n)); }
    std::string readLine() { std::string s; std::getline(in_, s); return s; }
    std::string readUTF() { return readLine(); }

    int getRemaining() const { return left_; }
    int64_t getOffset() const { return total_; }

private:
    std::istream& in_;
    PngCRC32 crc_;
    std::vector<uint8_t> tmp_;
    int64_t total_;
    int length_;
    int left_;
};

} // namespace png
} // namespace sixlegs
} // namespace com
