#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/embed/EmbedImage.h"
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


class ImplEmbedImage {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplEmbedImage.class);
    std::string url;
    std::string proxyUrl;
    int height;
    int width;

    public ImplEmbedImage(JSONObject data) {
      this.url = data.has("url") ? data.getString("url") : nullptr;
      this.proxyUrl = data.has("proxy_url") ? data.getString("proxy_url") : nullptr;
      this.height = data.has("height") ? data.getInt("height") : -1;
      this.width = data.has("width") ? data.getInt("width") : -1;
   }

    URL getUrl() {
      if (this.url == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.url);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the url of the embed image is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

    URL getProxyUrl() {
      if (this.proxyUrl == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.proxyUrl);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the proxy url of the embed image is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

    int getHeight() {
      return this.height;
   }

    int getWidth() {
      return this.width;
   }
}
} // namespace impl
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
