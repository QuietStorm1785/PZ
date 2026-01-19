#pragma once
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MipMapLevel {
public:
 const int width;
 const int height;
 const WrappedBuffer data;

public
 MipMapLevel(int _width, int _height) {
 this->width = _width;
 this->height = _height;
 this->data = DirectBufferAllocator.allocate(_width * _height * 4);
 }

public
 MipMapLevel(int _width, int _height, WrappedBuffer _data) {
 this->width = _width;
 this->height = _height;
 this->data = _data;
 }

 void dispose() {
 if (this->data != nullptr) {
 this->data.dispose();
 }
 }

 bool isDisposed() { return this->data != nullptr && this->data.isDisposed(); }

 void rewind() {
 if (this->data != nullptr) {
 this->data.getBuffer().rewind();
 }
 }

 ByteBuffer getBuffer() {
 return this->data.empty() ? nullptr : this->data.getBuffer();
 }

 int getDataSize() noexcept{ return this->width * this->height * 4; }
}
} // namespace textures
} // namespace core
} // namespace zombie
