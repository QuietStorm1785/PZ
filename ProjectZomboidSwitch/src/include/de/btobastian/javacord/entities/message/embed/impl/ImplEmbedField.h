#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/embed/EmbedField.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {
namespace impl {


class ImplEmbedField {
public:
    std::string name;
    std::string value;
    bool inline;

    public ImplEmbedField(JSONObject data) {
      this.name = data.has("name") ? data.getString("name") : nullptr;
      this.value = data.has("value") ? data.getString("value") : nullptr;
      this.inline = data.has("inline") && data.getBoolean("inline");
   }

    std::string getName() {
      return this.name;
   }

    std::string getValue() {
      return this.value;
   }

    bool isInline() {
      return this.inline;
   }
}
} // namespace impl
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
