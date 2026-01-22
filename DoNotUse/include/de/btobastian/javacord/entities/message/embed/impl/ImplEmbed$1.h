#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {
namespace impl {


class ImplEmbed {
public:
    SimpleDateFormat initialValue() {
      return std::make_shared<SimpleDateFormat>("yyyy-MM-dd'T'HH:mm:ss.SSSXXX");
   }
}
} // namespace impl
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
