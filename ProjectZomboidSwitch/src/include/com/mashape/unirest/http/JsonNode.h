#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/json/JSONArray.h"
#include "org/json/JSONException.h"
#include "org/json/JSONObject.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class JsonNode {
public:
    JSONObject jsonObject;
    JSONArray jsonArray;
    bool array;

    public JsonNode(const std::string& json) {
      if (json != nullptr && !"" == json.trim())) {
         try {
            this.jsonObject = std::make_shared<JSONObject>(json);
         } catch (JSONException var5) {
            try {
               this.jsonArray = std::make_shared<JSONArray>(json);
               this.array = true;
            } catch (JSONException var4) {
               throw RuntimeException(var4);
            }
         }
      } else {
         this.jsonObject = std::make_unique<JSONObject>();
      }
   }

    JSONObject getObject() {
      return this.jsonObject;
   }

    JSONArray getArray() {
    JSONArray result = this.jsonArray;
      if (!this.array) {
         result = std::make_unique<JSONArray>();
         result.put(this.jsonObject);
      }

    return result;
   }

    bool isArray() {
      return this.array;
   }

    std::string toString() {
      if (this.isArray()) {
         return this.jsonArray == nullptr ? nullptr : this.jsonArray;
      } else {
         return this.jsonObject == nullptr ? nullptr : this.jsonObject;
      }
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
