#ifndef ORG_LWJGL_SYSTEM_MEMORYUTIL_H
#define ORG_LWJGL_SYSTEM_MEMORYUTIL_H

#include <cstdint>
#include <cstring>
#include <cstdlib>

namespace org::lwjgl::system {

class MemoryUtil {
public:
 static int64_t nmemAlloc(long size) {
 return reinterpret_cast<int64_t>(::malloc(size));
 }
 
 static void nmemFree(long address) {
 if (address != 0) {
 ::free(reinterpret_cast<void*>(address));
 }
 }
 
 static void memCopy(long src, long dst, long bytes) {
 if (src != 0 && dst != 0 && bytes > 0) {
 ::memcpy(reinterpret_cast<void*>(dst), 
 reinterpret_cast<void*>(src), 
 bytes);
 }
 }
 
 static void memSet(long mem, int value, long bytes) {
 if (mem != 0 && bytes > 0) {
 ::memset(reinterpret_cast<void*>(mem), value, bytes);
 }
 }
};

} // namespace org::lwjgl::system

#endif // ORG_LWJGL_SYSTEM_MEMORYUTIL_H
