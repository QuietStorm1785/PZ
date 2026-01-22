#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace radio {
namespace media {


class RecordedMedia {
public:
    int compare(MediaData var1, MediaData var2) {
      return var1.getTranslatedItemDisplayName().compareToIgnoreCase(var2.getTranslatedItemDisplayName());
   }
}
} // namespace media
} // namespace radio
} // namespace zombie
