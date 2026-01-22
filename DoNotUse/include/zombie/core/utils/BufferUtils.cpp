#pragma once
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/BufferUtils/BufferInfo.h"
#include "zombie/core/utils/BufferUtils/ClearReferences.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace utils {


class BufferUtils {
public:
    static bool trackDirectMemory = false;
   private static const ReferenceQueue<Buffer> removeCollected = std::make_unique<ReferenceQueue<>>();
   private static const ConcurrentHashMap<BufferInfo, BufferInfo> trackedBuffers = std::make_unique<ConcurrentHashMap<>>();
    static ClearReferences cleanupThread;
    static const AtomicBoolean loadedMethods = std::make_shared<AtomicBoolean>(false);
    static Method cleanerMethod = nullptr;
    static Method cleanMethod = nullptr;
    static Method viewedBufferMethod = nullptr;
    static Method freeMethod = nullptr;

    static void setTrackDirectMemoryEnabled(bool var0) {
      trackDirectMemory = var0;
   }

    static void onBufferAllocated(Buffer var0) {
      if (trackDirectMemory) {
         if (cleanupThread == nullptr) {
            cleanupThread = std::make_unique<ClearReferences>();
            cleanupThread.start();
         }

         if (dynamic_cast<ByteBuffer*>(var0) != nullptr) {
    BufferInfo var1 = std::make_shared<BufferInfo>(ByteBuffer.class, var0.capacity(), var0, removeCollected);
            trackedBuffers.put(var1, var1);
         } else if (dynamic_cast<FloatBuffer*>(var0) != nullptr) {
    BufferInfo var2 = std::make_shared<BufferInfo>(FloatBuffer.class, var0.capacity() * 4, var0, removeCollected);
            trackedBuffers.put(var2, var2);
         } else if (dynamic_cast<IntBuffer*>(var0) != nullptr) {
    BufferInfo var3 = std::make_shared<BufferInfo>(IntBuffer.class, var0.capacity() * 4, var0, removeCollected);
            trackedBuffers.put(var3, var3);
         } else if (dynamic_cast<ShortBuffer*>(var0) != nullptr) {
    BufferInfo var4 = std::make_shared<BufferInfo>(ShortBuffer.class, var0.capacity() * 2, var0, removeCollected);
            trackedBuffers.put(var4, var4);
         } else if (dynamic_cast<DoubleBuffer*>(var0) != nullptr) {
    BufferInfo var5 = std::make_shared<BufferInfo>(DoubleBuffer.class, var0.capacity() * 8, var0, removeCollected);
            trackedBuffers.put(var5, var5);
         }
      }
   }

    static void printCurrentDirectMemory(std::stringstream var0) {
    long var1 = 0L;
    long var3 = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
    bool var5 = var0 == nullptr;
      if (var0 == nullptr) {
         var0 = std::make_unique<std::stringstream>();
      }

      if (trackDirectMemory) {
    int var6 = 0;
    int var7 = 0;
    int var8 = 0;
    int var9 = 0;
    int var10 = 0;
    int var11 = 0;
    int var12 = 0;
    int var13 = 0;
    int var14 = 0;
    int var15 = 0;

         for (BufferInfo var17 : trackedBuffers.values()) {
            if (var17.type == ByteBuffer.class) {
               var1 += var17.size;
               var12 += var17.size;
               var7++;
            } else if (var17.type == FloatBuffer.class) {
               var1 += var17.size;
               var11 += var17.size;
               var6++;
            } else if (var17.type == IntBuffer.class) {
               var1 += var17.size;
               var13 += var17.size;
               var8++;
            } else if (var17.type == ShortBuffer.class) {
               var1 += var17.size;
               var14 += var17.size;
               var9++;
            } else if (var17.type == DoubleBuffer.class) {
               var1 += var17.size;
               var15 += var17.size;
               var10++;
            }
         }

         var0.append("Existing buffers: ").append(trackedBuffers.size()).append("\n");
         var0.append("(b: ")
            .append(var7)
            .append("  f: ")
            .append(var6)
            .append("  i: ")
            .append(var8)
            .append("  s: ")
            .append(var9)
            .append("  d: ")
            .append(var10)
            .append(")")
            .append("\n");
         var0.append("Total   heap memory held: ").append(var3 / 1024L).append("kb\n");
         var0.append("Total direct memory held: ").append(var1 / 1024L).append("kb\n");
         var0.append("(b: ")
            .append(var12 / 1024)
            .append("kb  f: ")
            .append(var11 / 1024)
            .append("kb  i: ")
            .append(var13 / 1024)
            .append("kb  s: ")
            .append(var14 / 1024)
            .append("kb  d: ")
            .append(var15 / 1024)
            .append("kb)")
            .append("\n");
      } else {
         var0.append("Total   heap memory held: ").append(var3 / 1024L).append("kb\n");
         var0.append(
               "Only heap memory available, if you want to monitor direct memory use BufferUtils.setTrackDirectMemoryEnabled(true) during initialization."
            )
            .append("\n");
      }

      if (var5) {
         System.out.println(var0);
      }
   }

    static Method loadMethod(const std::string& var0, const std::string& var1) {
      try {
    Method var2 = Class.forName(var0).getMethod(var1);
         var2.setAccessible(true);
    return var2;
      } catch (SecurityException | ClassNotFoundException | NoSuchMethodException var3) {
    return nullptr;
      }
   }

    static ByteBuffer createByteBuffer(int var0) {
    ByteBuffer var1 = ByteBuffer.allocateDirect(var0).order(ByteOrder.nativeOrder());
      var1.clear();
      onBufferAllocated(var1);
    return var1;
   }

    static void loadCleanerMethods() {
      if (!loadedMethods.getAndSet(true)) {
         /* synchronized - TODO: add std::mutex */ (loadedMethods) {
            cleanerMethod = loadMethod("sun.nio.ch.DirectBuffer", "cleaner");
            viewedBufferMethod = loadMethod("sun.nio.ch.DirectBuffer", "viewedBuffer");
            if (viewedBufferMethod == nullptr) {
               viewedBufferMethod = loadMethod("sun.nio.ch.DirectBuffer", "attachment");
            }

    ByteBuffer var1 = createByteBuffer(1);
    Class var2 = var1.getClass();

            try {
               freeMethod = var2.getMethod("free");
            } catch (SecurityException | NoSuchMethodException var5) {
            }
         }
      }
   }

    static void destroyDirectBuffer(Buffer var0) {
      if (var0.isDirect()) {
         loadCleanerMethods();

         try {
            if (freeMethod != nullptr) {
               freeMethod.invoke(var0);
            } else {
    void* var1 = cleanerMethod.invoke(var0);
               if (var1 == nullptr) {
    void* var2 = viewedBufferMethod.invoke(var0);
                  if (var2 != nullptr) {
                     destroyDirectBuffer((Buffer)var2);
                  } else {
                     Logger.getLogger(BufferUtils.class.getName()).log(Level.SEVERE, "Buffer cannot be destroyed: {0}", var0);
                  }
               }
            }
         } catch (IllegalArgumentException | InvocationTargetException | SecurityException | IllegalAccessException var3) {
            Logger.getLogger(BufferUtils.class.getName()).log(Level.SEVERE, "{0}", (Throwable)var3);
         }
      }
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
