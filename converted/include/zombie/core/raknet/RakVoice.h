#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class RakVoice {
public:
 public static void RVInit(int var0);

 public static void RVInitServer(boolean var0, int var1, int var2, int var3, int var4, float var5, float var6, boolean var7);

 public static void RVDeinit();

 public static int GetComplexity();

 public static void SetComplexity(int var0);

 public static void RequestVoiceChannel(long var0);

 public static void CloseAllChannels();

 public static int GetBufferSizeBytes();

 public static boolean GetServerVOIPEnable();

 public static int GetSampleRate();

 public static int GetSendFramePeriod();

 public static int GetBuffering();

 public static float GetMinDistance();

 public static float GetMaxDistance();

 public static boolean GetIs3D();

 public static void CloseVoiceChannel(long var0);

 public static boolean ReceiveFrame(long var0, byte[] var2);

 public static void SendFrame(long var0, long var2, byte[] var4, long var5);

 public static void SetLoopbackMode(boolean var0);

 public static void SetVoiceBan(long var0, boolean var2);

 public static void SetChannelsRouting(long var0, boolean var2, int[] var3, short var4);

 public static boolean GetChannelStatistics(long var0, long[] var2);
}
} // namespace raknet
} // namespace core
} // namespace zombie
