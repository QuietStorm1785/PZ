#pragma once
#include "zombie/radio/ChannelCategory.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class DynamicRadioChannel : public RadioChannel {
public:
public
 DynamicRadioChannel(std::string_view n, int freq, ChannelCategory c) {
 super(n, freq, c);
 }

public
 DynamicRadioChannel(std::string_view n, int freq, ChannelCategory c,
 std::string_view guid) {
 super(n, freq, c, guid);
 }

 void LoadAiringBroadcast(std::string_view guid, int line) {}
}
} // namespace scripting
} // namespace radio
} // namespace zombie
