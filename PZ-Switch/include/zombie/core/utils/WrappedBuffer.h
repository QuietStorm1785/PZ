#pragma once
#include "org/lwjgl/system/MemoryUtil.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Tracks allocated buffers
 */
class WrappedBuffer {
public:
 ByteBuffer buf;
 const int capacity;
 bool disposed;

public
 WrappedBuffer(int size) {
 this->buf = MemoryUtil.memAlloc(size);
 MemoryUtil.memSet(this->buf, 0);
 this->capacity = this->buf.capacity();
 }

 ByteBuffer getBuffer() {
 if (this->disposed) {
 throw IllegalStateException("Can't get buffer after disposal");
 } else {
 return this->buf;
 }
 }

 int capacity() { return this->capacity; }

 void dispose() {
 if (this->disposed) {
 throw IllegalStateException("WrappedBuffer was already disposed");
 } else {
 this->disposed = true;
 MemoryUtil.memFree(this->buf);
 this->buf = nullptr;
 }
 }

 bool isDisposed() { return this->disposed; }
}
} // namespace utils
} // namespace core
} // namespace zombie
