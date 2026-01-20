#include <string>
#include "com\mashape\unirest\request/GetRequest.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {

public GetRequest::GetRequest(HttpMethod method, const std::string& url) {
    // TODO: Implement GetRequest
    return nullptr;
}

GetRequest GetRequest::routeParam(const std::string& name, const std::string& value) {
    // TODO: Implement routeParam
    return nullptr;
}

GetRequest GetRequest::header(const std::string& name, const std::string& value) {
    // TODO: Implement header
    return nullptr;
}

GetRequest GetRequest::headers(std::string> headers) {
    // TODO: Implement headers
    return nullptr;
}

GetRequest GetRequest::basicAuth(const std::string& username, const std::string& password) {
    // TODO: Implement basicAuth
    return nullptr;
}

} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
