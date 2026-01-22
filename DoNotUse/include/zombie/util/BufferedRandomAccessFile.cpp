#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {

class BufferedRandomAccessFile {
public:
    BufferedRandomAccessFile(const std::string& path, std::ios::openmode mode, int bufSize)
        : buffer_(bufSize), buf_end_(0), buf_pos_(0), real_pos_(0), BUF_SIZE(bufSize) {
        file_.open(path, mode | std::ios::binary);
        if (!file_.is_open()) throw std::runtime_error("Failed to open file: " + path);
        invalidate();
    }

    ~BufferedRandomAccessFile() { if (file_.is_open()) file_.close(); }

    int read() {
        if (buf_pos_ >= buf_end_ && fillBuffer() < 0) return -1;
        return buf_end_ == 0 ? -1 : static_cast<uint8_t>(buffer_[buf_pos_++]);
    }

    int fillBuffer() {
        if (!file_.is_open()) return -1;
        file_.read(buffer_.data(), static_cast<std::streamsize>(BUF_SIZE));
        std::streamsize r = file_.gcount();
        if (r <= 0) return -1;
        real_pos_ += r;
        buf_end_ = static_cast<int>(r);
        buf_pos_ = 0;
        return buf_end_;
    }

    void invalidate() {
        buf_end_ = 0;
        buf_pos_ = 0;
        if (file_.is_open()) real_pos_ = static_cast<int64_t>(file_.tellg());
    }

    int read(char* out, int offset, int len) {
        int available = buf_end_ - buf_pos_;
        if (len <= available) {
            std::memcpy(out + offset, buffer_.data() + buf_pos_, static_cast<size_t>(len));
            buf_pos_ += len;
            return len;
        } else {
            int i;
            for (i = 0; i < len; ++i) {
                int r = read();
                if (r == -1) return i;
                out[offset + i] = static_cast<char>(r);
            }
            return len;
        }
    }

    int64_t getFilePointer() const {
        return real_pos_ - buf_end_ + buf_pos_;
    }

    void seek(int64_t pos) {
        int64_t diff = real_pos_ - pos;
        if (diff >= 0 && diff <= buf_end_) {
            buf_pos_ = static_cast<int>(buf_end_ - diff);
        } else {
            file_.clear();
            file_.seekg(pos, std::ios::beg);
            invalidate();
        }
    }

    // Return next line or empty string on EOF
    std::string getNextLine() {
        if (buf_end_ - buf_pos_ <= 0 && fillBuffer() < 0) return std::string();
        int newline = -1;
        for (int i = buf_pos_; i < buf_end_; ++i) if (buffer_[i] == '\n') { newline = i; break; }
        if (newline < 0) {
            std::stringstream ss;
            int c;
            while ((c = read()) != -1 && c != '\n') ss.put(static_cast<char>(c));
            return ss.str();
        } else {
            int start = buf_pos_;
            int len = (newline > 0 && buffer_[newline - 1] == '\r') ? (newline - start - 1) : (newline - start);
            std::string res(buffer_.data() + start, buffer_.data() + start + len);
            buf_pos_ = newline + 1;
            return res;
        }
    }

private:
    std::vector<char> buffer_;
    int buf_end_ = 0;
    int buf_pos_ = 0;
    int64_t real_pos_ = 0;
    const int BUF_SIZE;
    std::fstream file_;
};

} // namespace util
} // namespace zombie
