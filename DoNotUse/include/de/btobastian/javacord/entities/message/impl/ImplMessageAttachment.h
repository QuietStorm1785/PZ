#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/MessageAttachment.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessageAttachment {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplMessageAttachment.class);
    const std::string url;
    const std::string proxyUrl;
    const int size;
    const std::string id;
    const std::string name;

    public ImplMessageAttachment(const std::string& url, const std::string& proxyUrl, int size, const std::string& id, const std::string& name) {
      this.url = url;
      this.proxyUrl = proxyUrl;
      this.size = size;
      this.id = id;
      this.name = name;
   }

    URL getUrl() {
      try {
         return this.url == nullptr ? nullptr : std::make_shared<URL>(this.url);
      } catch (MalformedURLException var2) {
         logger.warn("Malformed url of message attachment! Please contact the developer!", var2);
    return nullptr;
      }
   }

    URL getProxyUrl() {
      try {
         return this.proxyUrl == nullptr ? nullptr : std::make_shared<URL>(this.proxyUrl);
      } catch (MalformedURLException var2) {
         logger.warn("Malformed proxy url of message attachment! Please contact the developer!", var2);
    return nullptr;
      }
   }

    int getSize() {
      return this.size;
   }

    std::string getId() {
      return this.id;
   }

    std::string getFileName() {
      return this.name;
   }

    std::string toString() {
      return this.getFileName() + " (id: " + this.getId() + ", url: " + this.getUrl() + ")";
   }

    int hashCode() {
      return this.getId().hashCode();
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
