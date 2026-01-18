#ifndef ORG_LWJGL_SYSTEM_MEMORYSTACK_H
#define ORG_LWJGL_SYSTEM_MEMORYSTACK_H

#include <cstddef>
#include <vector>

namespace org::lwjgl::system {

class MemoryStack {
public:
 static MemoryStack* stack() { static MemoryStack s; return &s; }
 void push() { frames.push_back(offset); }
 void pop() { if (!frames.empty()) { offset = frames.back(); frames.pop_back(); } }

 void* malloc(size_t size) {
 buffer.resize(offset + size);
 void* ptr = buffer.data() + offset;
 offset += size;
 return ptr;
 }

private:
 std::vector<char> buffer;
 size_t offset = 0;
 std::vector<size_t> frames;
};

} // namespace org::lwjgl::system

#endif // ORG_LWJGL_SYSTEM_MEMORYSTACK_H
