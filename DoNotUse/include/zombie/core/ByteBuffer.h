#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <cstring>

namespace zombie {
namespace core {

class ByteBuffer {
private:
    std::vector<char> buffer_;
    size_t position_;
    size_t limit_;
    size_t capacity_;

public:
    ByteBuffer(size_t capacity) : buffer_(capacity), position_(0), limit_(capacity), capacity_(capacity) {}

    static std::shared_ptr<ByteBuffer> allocate(size_t capacity) {
        return std::make_shared<ByteBuffer>(capacity);
    }

    size_t capacity() const { return capacity_; }
    size_t position() const { return position_; }
    size_t limit() const { return limit_; }
    size_t remaining() const { return limit_ - position_; }

    ByteBuffer& position(size_t pos) {
        if (pos > limit_) throw std::out_of_range("Position exceeds limit");
        position_ = pos;
        return *this;
    }

    ByteBuffer& limit(size_t lim) {
        if (lim > capacity_) throw std::out_of_range("Limit exceeds capacity");
        if (position_ > lim) position_ = lim;
        limit_ = lim;
        return *this;
    }

    ByteBuffer& clear() {
        position_ = 0;
        limit_ = capacity_;
        return *this;
    }

    // Put methods
    ByteBuffer& put(char value) {
        if (position_ >= limit_) throw std::out_of_range("Buffer overflow");
        buffer_[position_++] = value;
        return *this;
    }

    ByteBuffer& putShort(int16_t value) {
        if (position_ + 1 >= limit_) throw std::out_of_range("Buffer overflow");
        *reinterpret_cast<int16_t*>(&buffer_[position_]) = value;
        position_ += 2;
        return *this;
    }

    ByteBuffer& putInt(int32_t value) {
        if (position_ + 3 >= limit_) throw std::out_of_range("Buffer overflow");
        *reinterpret_cast<int32_t*>(&buffer_[position_]) = value;
        position_ += 4;
        return *this;
    }

    ByteBuffer& put(const char* data, size_t offset, size_t length) {
        if (position_ + length > limit_) throw std::out_of_range("Buffer overflow");
        std::memcpy(&buffer_[position_], data + offset, length);
        position_ += length;
        return *this;
    }

    // Get methods
    char get() {
        if (position_ >= limit_) throw std::out_of_range("Buffer underflow");
        return buffer_[position_++];
    }

    int16_t getShort() {
        if (position_ + 1 >= limit_) throw std::out_of_range("Buffer underflow");
        int16_t value = *reinterpret_cast<int16_t*>(&buffer_[position_]);
        position_ += 2;
        return value;
    }

    int32_t getInt() {
        if (position_ + 3 >= limit_) throw std::out_of_range("Buffer underflow");
        int32_t value = *reinterpret_cast<int32_t*>(&buffer_[position_]);
        position_ += 4;
        return value;
    }

    const char* array() const { return buffer_.data(); }
};

} // namespace core
} // namespace zombie