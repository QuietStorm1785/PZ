#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/embed/EmbedFooter.h"
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


class ImplEmbedFooter {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplEmbedFooter.class);
    std::string text;
    std::string iconUrl;
    std::string proxyIconUrl;

    public ImplEmbedFooter(JSONObject data) {
      this.text = data.has("text") ? data.getString("text") : nullptr;
      this.iconUrl = data.has("icon_url") ? data.getString("icon_url") : nullptr;
      this.proxyIconUrl = data.has("proxy_icon_url") ? data.getString("proxy_icon_url") : nullptr;
   }

    std::string getText() {
      return this.text;
   }

    URL getIconUrl() {
      if (this.iconUrl == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.iconUrl);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the icon url of the embed footer is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

    URL getProxyIconUrl() {
      if (this.proxyIconUrl == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.proxyIconUrl);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the proxy icon url of the embed footer is malformed! Please contact the developer!", var2);
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
