#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocketExtension {
public:
    static const std::string PERMESSAGE_DEFLATE = "permessage-deflate";
    const std::string mName;
   private const Map<std::string, std::string> mParameters;

    public WebSocketExtension(const std::string& name) {
      if (!Token.isValid(name)) {
         throw IllegalArgumentException("'name' is not a valid token.");
      } else {
         this.mName = name;
         this.mParameters = std::make_unique<LinkedHashMap<>>();
      }
   }

    public WebSocketExtension(WebSocketExtension source) {
      if (source == nullptr) {
         throw IllegalArgumentException("'source' is nullptr.");
      } else {
         this.mName = source.getName();
         this.mParameters = new LinkedHashMap<>(source.getParameters());
      }
   }

    std::string getName() {
      return this.mName;
   }

   public Map<std::string, std::string> getParameters() {
      return this.mParameters;
   }

    bool containsParameter(const std::string& key) {
      return this.mParameters.containsKey(key);
   }

    std::string getParameter(const std::string& key) {
      return this.mParameters.get(key);
   }

    WebSocketExtension setParameter(const std::string& key, const std::string& value) {
      if (!Token.isValid(key)) {
         throw IllegalArgumentException("'key' is not a valid token.");
      } else if (value != nullptr && !Token.isValid(value)) {
         throw IllegalArgumentException("'value' is not a valid token.");
      } else {
         this.mParameters.put(key, value);
    return this;
      }
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.mName);

      for (Entry<std::string, std::string> entry : this.mParameters.entrySet()) {
         builder.append("; ").append(entry.getKey());
    std::string value = entry.getValue();
         if (value != nullptr && value.length() != 0) {
            builder.append("=").append(value);
         }
      }

      return builder;
   }

    void validate() {
   }

    static WebSocketExtension parse(const std::string& string) {
      if (string == nullptr) {
    return nullptr;
      } else {
         std::string[] elements = string.trim().split("\\s*;\\s*");
         if (elements.length == 0) {
    return nullptr;
         } else {
    std::string name = elements[0];
            if (!Token.isValid(name)) {
    return nullptr;
            } else {
    WebSocketExtension extension = createInstance(name);

               for (int i = 1; i < elements.length; i++) {
                  std::string[] pair = elements[i].split("\\s*=\\s*", 2);
                  if (pair.length != 0 && pair[0].length() != 0) {
    std::string key = pair[0];
                     if (Token.isValid(key)) {
    std::string value = extractValue(pair);
                        if (value == nullptr || Token.isValid(value)) {
                           extension.setParameter(key, value);
                        }
                     }
                  }
               }

    return extension;
            }
         }
      }
   }

    static std::string extractValue(std::string[] pair) {
      return pair.length != 2 ? nullptr : Token.unquote(pair[1]);
   }

    static WebSocketExtension createInstance(const std::string& name) {
      return (WebSocketExtension)("permessage-deflate" == name) ? std::make_shared<PerMessageDeflateExtension>(name) : std::make_shared<WebSocketExtension>(name));
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
