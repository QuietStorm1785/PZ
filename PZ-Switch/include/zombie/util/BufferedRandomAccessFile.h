#pragma once
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BufferedRandomAccessFile : public RandomAccessFile {
public:
private
 byte[] buffer;
 int buf_end = 0;
 int buf_pos = 0;
 long real_pos = 0L;
 const int BUF_SIZE;

public
 BufferedRandomAccessFile(const std::string &filename, const std::string &mode,
 int bufsize) {
 super(filename, mode);
 this->invalidate();
 this->BUF_SIZE = bufsize;
 this->buffer = new byte[this->BUF_SIZE];
 }

public
 BufferedRandomAccessFile(File file, const std::string &mode, int bufsize) {
 super(file, mode);
 this->invalidate();
 this->BUF_SIZE = bufsize;
 this->buffer = new byte[this->BUF_SIZE];
 }

 int read() {
 if (this->buf_pos >= this->buf_end && this->fillBuffer() < 0) {
 return -1;
 } else {
 return this->buf_end == 0 ? -1 : this->buffer[this->buf_pos++] & 0xFF;
 }
 }

 int fillBuffer() {
 int int0 = super.read(this->buffer, 0, this->BUF_SIZE);
 if (int0 >= 0) {
 this->real_pos += int0;
 this->buf_end = int0;
 this->buf_pos = 0;
 }

 return int0;
 }

 void invalidate() {
 this->buf_end = 0;
 this->buf_pos = 0;
 this->real_pos = super.getFilePointer();
 }

 int read(byte[] bytes, int int2, int int1) {
 int int0 = this->buf_end - this->buf_pos;
 if (int1 <= int0) {
 System.arraycopy(this->buffer, this->buf_pos, bytes, int2, int1);
 this->buf_pos += int1;
 return int1;
 } else {
 for (int int3 = 0; int3 < int1; int3++) {
 int int4 = this->read();
 if (int4 == -1) {
 return int3;
 }

 bytes[int2 + int3] = (byte)int4;
 }

 return int1;
 }
 }

 long getFilePointer() {
 long long0 = this->real_pos;
 return long0 - this->buf_end + this->buf_pos;
 }

 void seek(long pos) {
 int int0 = (int)(this->real_pos - pos);
 if (int0 >= 0 && int0 <= this->buf_end) {
 this->buf_pos = this->buf_end - int0;
 } else {
 super.seek(pos);
 this->invalidate();
 }
 }

 std::string getNextLine() {
 std::string string = nullptr;
 if (this->buf_end - this->buf_pos <= 0 && this->fillBuffer() < 0) {
 throw IOException("error in filling buffer!");
 } else {
 int int0 = -1;

 for (int int1 = this->buf_pos; int1 < this->buf_end; int1++) {
 if (this->buffer[int1] == 10) {
 int0 = int1;
 break;
 }
 }

 if (int0 < 0) {
 StringBuilder stringBuilder = new StringBuilder(128);

 int int2;
 while ((int2 = this->read()) != -1 && int2 != 10) {
 stringBuilder.append((char)int2);
 }

 return int2 = = -1 && stringBuilder.length() == 0
 ? nullptr
 : stringBuilder.toString();
 } else {
 if (int0 > 0 && this->buffer[int0 - 1] == 13) {
 string = new String(this->buffer, this->buf_pos,
 int0 - this->buf_pos - 1, StandardCharsets.UTF_8);
 } else {
 string = new String(this->buffer, this->buf_pos, int0 - this->buf_pos,
 StandardCharsets.UTF_8);
 }

 this->buf_pos = int0 + 1;
 return string;
 }
 }
 }
}
} // namespace util
} // namespace zombie
