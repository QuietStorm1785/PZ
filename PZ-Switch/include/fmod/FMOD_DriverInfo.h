#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMOD_DriverInfo {
public:
 int id;
 std::string name;
 int guid;
 int systemrate;
 int speakermode;
 int speakerchannels;

public
 FMOD_DriverInfo() {
 this->id = -1;
 this->name = "";
 this->guid = 0;
 this->systemrate = 8000;
 this->speakermode = 0;
 this->speakerchannels = 1;
 }

public
 FMOD_DriverInfo(int int0, const std::string &string) {
 this->id = int0;
 this->name = string;
 this->guid = 0;
 this->systemrate = 8000;
 this->speakermode = 0;
 this->speakerchannels = 1;
 }
}
} // namespace fmod
