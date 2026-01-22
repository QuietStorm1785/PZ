#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace exceptions {


class BadResponseException : public Exception {
public:
    const int status;
    const std::string statusText;
   private const HttpResponse<JsonNode> response;

    public BadResponseException(const std::string& message, int status, const std::string& statusText, HttpResponse<JsonNode> response) {
      super(message);
      this.status = status;
      this.statusText = statusText;
      this.response = response;
   }

    int getStatus() {
      return this.status;
   }

    std::string getStatusText() {
      return this.statusText;
   }

   public HttpResponse<JsonNode> getResponse() {
      return this.response;
   }
}
} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
