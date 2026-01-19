#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class FMOD_DriverInfo {
:
    int id;
    std::string name;
    int guid;
    int systemrate;
    int speakermode;
    int speakerchannels;

     FMOD_DriverInfo() {
      this.id = -1;
      this.name = "";
      this.guid = 0;
      this.systemrate = 8000;
      this.speakermode = 0;
      this.speakerchannels = 1;
   }

     FMOD_DriverInfo(int var1, const std::string& var2) {
      this.id = var1;
      this.name = var2;
      this.guid = 0;
      this.systemrate = 8000;
      this.speakermode = 0;
      this.speakerchannels = 1;
   }
}
} // namespace fmod
