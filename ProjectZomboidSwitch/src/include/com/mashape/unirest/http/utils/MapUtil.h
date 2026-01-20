#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/apache/http/NameValuePair.h"
#include "org/apache/http/message/BasicNameValuePair.h"
#include <algorithm>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {


class MapUtil {
public:
   public static List<NameValuePair> getList(Map<std::string, List<Object>> parameters) {
      List<NameValuePair> result = std::make_unique<std::vector<>>();
      if (parameters != nullptr) {
         std::map<std::string, List<Object>> sortedParameters = new std::map<>(parameters);

         for (Entry<std::string, List<Object>> entry : sortedParameters.entrySet()) {
            List<Object> entryValue = entry.getValue();
            if (entryValue != nullptr) {
    for (auto& cur : entryValue)                  if (cur != nullptr) {
                     result.push_back(std::make_shared<BasicNameValuePair>(entry.getKey(), cur));
                  }
               }
            }
         }
      }

    return result;
   }
}
} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
