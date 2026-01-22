#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/embed/EmbedProvider.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {
namespace impl {


class ImplEmbedProvider {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplEmbedProvider.class);
    std::string name;
    std::string url;

    public ImplEmbedProvider(JSONObject data) {
      this.name = data.has("name") ? data.getString("name") : nullptr;
      this.url = data.has("url") ? data.getString("url") : nullptr;
   }

    std::string getName() {
      return this.name;
   }

    URL getUrl() {
      if (this.url == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.url);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the url of the embed provider is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }
}
} // namespace impl
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
