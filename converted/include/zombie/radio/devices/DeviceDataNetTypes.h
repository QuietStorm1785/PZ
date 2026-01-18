#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace devices {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class DeviceDataNetTypes {
public:
 static const short TurnedOnStateChange = 0;
 static const short ChannelChange = 1;
 static const short BatteryChange = 2;
 static const short PowerChange = 3;
 static const short VolumeChange = 4;
 static const short PresetsChange = 5;
 static const short HeadPhoneChange = 6;
 static const short MediaChange = 7;
 static const short StartPlayMedia = 8;
 static const short StopPlayMedia = 9;
 static const short TransmitMediaLine = 10;
}
} // namespace devices
} // namespace radio
} // namespace zombie
