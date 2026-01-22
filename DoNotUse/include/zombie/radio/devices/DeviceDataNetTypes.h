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
