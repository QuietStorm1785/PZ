#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {

enum class Region {
   AMSTERDAM("amsterdam", "Amsterdam"),
   BRAZIL("brazil", "Brazil"),
   EU_CENTRAL("eu-central", "EU Central"),
   EU_WEST("eu-west", "EU West"),
   FRANKFURT("frankfurt", "Frankfurt"),
   LONDON("london", "London"),
   SINGAPORE("singapore", "Singapore"),
   SYDNEY("sydney", "Sydney"),
   US_CENTRAL("us-central", "US Central"),
   US_EAST("us-east", "US East"),
   US_SOUTH("us-south", "US South"),
   US_WEST("us-west", "US West"),
   UNKNOWN("us-west", "Unknown");

    const std::string key;
    const std::string name;

    private Region(const std::string& key, const std::string& name) {
      this.key = key;
      this.name = name;
   }

    std::string getKey() {
      return this.key;
   }

    std::string getName() {
      return this.name;
   }

    static Region getRegionByKey(const std::string& key) {
      for (Region region : values()) {
         if (region.getKey().equalsIgnoreCase(key) && region != UNKNOWN) {
    return region;
         }
      }

    return UNKNOWN;
   }
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
