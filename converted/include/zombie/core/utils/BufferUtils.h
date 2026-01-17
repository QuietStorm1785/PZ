#pragma once
#include <algorithm>
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

class BufferUtils {
public:
  static bool trackDirectMemory = false;
private
  static final ReferenceQueue<Buffer> removeCollected =
      std::make_unique<ReferenceQueue<>>();
private
  static final ConcurrentHashMap<BufferUtils.BufferInfo, BufferUtils.BufferInfo>
      trackedBuffers = std::make_unique<ConcurrentHashMap<>>();
  static BufferUtils.ClearReferences cleanupThread;
  static const AtomicBoolean loadedMethods = new AtomicBoolean(false);
  static Method cleanerMethod = null;
  static Method cleanMethod = null;
  static Method viewedBufferMethod = null;
  static Method freeMethod = null;

  static void setTrackDirectMemoryEnabled(bool boolean0) {
    trackDirectMemory = boolean0;
  }

  static void onBufferAllocated(Buffer buffer) {
    if (trackDirectMemory) {
      if (cleanupThread == nullptr) {
        cleanupThread = new BufferUtils.ClearReferences();
        cleanupThread.start();
      }

      if (buffer instanceof ByteBuffer) {
        BufferUtils.BufferInfo bufferInfo0 = new BufferUtils.BufferInfo(
            ByteBuffer.class, buffer.capacity(), buffer, removeCollected);
        trackedBuffers.put(bufferInfo0, bufferInfo0);
      } else if (buffer instanceof FloatBuffer) {
        BufferUtils.BufferInfo bufferInfo1 = new BufferUtils.BufferInfo(
            FloatBuffer.class, buffer.capacity() * 4, buffer, removeCollected);
        trackedBuffers.put(bufferInfo1, bufferInfo1);
      } else if (buffer instanceof IntBuffer) {
        BufferUtils.BufferInfo bufferInfo2 = new BufferUtils.BufferInfo(
            IntBuffer.class, buffer.capacity() * 4, buffer, removeCollected);
        trackedBuffers.put(bufferInfo2, bufferInfo2);
      } else if (buffer instanceof ShortBuffer) {
        BufferUtils.BufferInfo bufferInfo3 = new BufferUtils.BufferInfo(
            ShortBuffer.class, buffer.capacity() * 2, buffer, removeCollected);
        trackedBuffers.put(bufferInfo3, bufferInfo3);
      } else if (buffer instanceof DoubleBuffer) {
        BufferUtils.BufferInfo bufferInfo4 = new BufferUtils.BufferInfo(
            DoubleBuffer.class, buffer.capacity() * 8, buffer, removeCollected);
        trackedBuffers.put(bufferInfo4, bufferInfo4);
      }
    }
  }

  static void printCurrentDirectMemory(StringBuilder stringBuilder) {
    long long0 = 0L;
    long long1 =
        Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
    bool boolean0 = stringBuilder == null;
    if (stringBuilder == nullptr) {
      stringBuilder = std::make_unique<StringBuilder>();
    }

    if (trackDirectMemory) {
      int int0 = 0;
      int int1 = 0;
      int int2 = 0;
      int int3 = 0;
      int int4 = 0;
      int int5 = 0;
      int int6 = 0;
      int int7 = 0;
      int int8 = 0;
      int int9 = 0;

      for (BufferUtils.BufferInfo bufferInfo : trackedBuffers.values()) {
        if (bufferInfo.type == ByteBuffer.class) {
          long0 += bufferInfo.size;
          int6 += bufferInfo.size;
          int1++;
        } else if (bufferInfo.type == FloatBuffer.class) {
          long0 += bufferInfo.size;
          int5 += bufferInfo.size;
          int0++;
        } else if (bufferInfo.type == IntBuffer.class) {
          long0 += bufferInfo.size;
          int7 += bufferInfo.size;
          int2++;
        } else if (bufferInfo.type == ShortBuffer.class) {
          long0 += bufferInfo.size;
          int8 += bufferInfo.size;
          int3++;
        } else if (bufferInfo.type == DoubleBuffer.class) {
          long0 += bufferInfo.size;
          int9 += bufferInfo.size;
          int4++;
        }
      }

      stringBuilder.append("Existing buffers: ")
          .append(trackedBuffers.size())
          .append("\n");
      stringBuilder.append("(b: ")
          .append(int1)
          .append("  f: ")
          .append(int0)
          .append("  i: ")
          .append(int2)
          .append("  s: ")
          .append(int3)
          .append("  d: ")
          .append(int4)
          .append(")")
          .append("\n");
      stringBuilder.append("Total   heap memory held: ")
          .append(long1 / 1024L)
          .append("kb\n");
      stringBuilder.append("Total direct memory held: ")
          .append(long0 / 1024L)
          .append("kb\n");
      stringBuilder.append("(b: ")
          .append(int6 / 1024)
          .append("kb  f: ")
          .append(int5 / 1024)
          .append("kb  i: ")
          .append(int7 / 1024)
          .append("kb  s: ")
          .append(int8 / 1024)
          .append("kb  d: ")
          .append(int9 / 1024)
          .append("kb)")
          .append("\n");
    } else {
      stringBuilder.append("Total   heap memory held: ")
          .append(long1 / 1024L)
          .append("kb\n");
      stringBuilder
          .append("Only heap memory available, if you want to monitor direct "
                  "memory use BufferUtils.setTrackDirectMemoryEnabled(true) "
                  "during initialization.")
          .append("\n");
    }

    if (boolean0) {
      System.out.println(stringBuilder.toString());
    }
  }

  static Method loadMethod(const std::string &string1,
                           const std::string &string0) {
    try {
      Method method = Class.forName(string1).getMethod(string0);
      method.setAccessible(true);
      return method;
    } catch (SecurityException | ClassNotFoundException |
             NoSuchMethodException noSuchMethodException) {
      return null;
    }
  }

  static ByteBuffer createByteBuffer(int int0) {
    ByteBuffer byteBuffer =
        ByteBuffer.allocateDirect(int0).order(ByteOrder.nativeOrder());
    byteBuffer.clear();
    onBufferAllocated(byteBuffer);
    return byteBuffer;
  }

  static void loadCleanerMethods() {
    if (!loadedMethods.getAndSet(true)) {
      synchronized(loadedMethods) {
        cleanerMethod = loadMethod("sun.nio.ch.DirectBuffer", "cleaner");
        viewedBufferMethod =
            loadMethod("sun.nio.ch.DirectBuffer", "viewedBuffer");
        if (viewedBufferMethod == nullptr) {
          viewedBufferMethod =
              loadMethod("sun.nio.ch.DirectBuffer", "attachment");
        }

        ByteBuffer byteBuffer = createByteBuffer(1);
        Class clazz = byteBuffer.getClass();

        try {
          freeMethod = clazz.getMethod("free");
        } catch (SecurityException |
                 NoSuchMethodException noSuchMethodException) {
        }
      }
    }
  }

  static void destroyDirectBuffer(Buffer buffer) {
    if (buffer.isDirect()) {
      loadCleanerMethods();

      try {
        if (freeMethod != nullptr) {
          freeMethod.invoke(buffer);
        } else {
          void *object0 = cleanerMethod.invoke(buffer);
          if (object0 == nullptr) {
            void *object1 = viewedBufferMethod.invoke(buffer);
            if (object1 != nullptr) {
              destroyDirectBuffer((Buffer)object1);
            } else {
              Logger.getLogger(BufferUtils.class.getName())
                  .log(Level.SEVERE, "Buffer cannot be destroyed: {0}", buffer);
            }
          }
        }
      } catch (IllegalArgumentException | InvocationTargetException |
               SecurityException |
               IllegalAccessException illegalAccessException) {
        Logger.getLogger(BufferUtils.class.getName())
            .log(Level.SEVERE, "{0}", (Throwable)illegalAccessException);
      }
    }
  }

private
  static class BufferInfo extends PhantomReference<Buffer> {
    const Class type;
    const int size;

  public BufferInfo(Class clazz, int int0, Buffer buffer, ReferenceQueue<? super) {
      super(buffer, referenceQueue);
      this.type = clazz;
      this.size = int0;
    }
  }

  private static class ClearReferences extends Thread {
    ClearReferences() { this.setDaemon(true); }

    void run() {
      try {
        while (true) {
          Reference reference = BufferUtils.removeCollected.remove();
          BufferUtils.trackedBuffers.remove(reference);
        }
      } catch (InterruptedException interruptedException) {
        interruptedException.printStackTrace();
      }
    }
  }
}
} // namespace utils
} // namespace core
} // namespace zombie
