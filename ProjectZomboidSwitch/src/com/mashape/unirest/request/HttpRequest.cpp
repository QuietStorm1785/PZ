#include <string>
#include "com/mashape/unirest/request/HttpRequest.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {

public HttpRequest::HttpRequest(HttpMethod method, const std::string& url) {
    // TODO: Implement HttpRequest
    return nullptr;
}

HttpRequest HttpRequest::routeParam(const std::string& name, const std::string& value) {
    // TODO: Implement routeParam
    return nullptr;
}

HttpRequest HttpRequest::basicAuth(const std::string& username, const std::string& password) {
    // TODO: Implement basicAuth
    return nullptr;
}

HttpRequest HttpRequest::header(const std::string& name, const std::string& value) {
    // TODO: Implement header
    return nullptr;
}

HttpRequest HttpRequest::headers(std::string> headers) {
    // TODO: Implement headers
    return nullptr;
}

HttpRequest HttpRequest::queryString(const std::string& name, Collection<?> value) {
    // TODO: Implement queryString
    return nullptr;
}

HttpRequest HttpRequest::queryString(const std::string& name, void* value) {
    // TODO: Implement queryString
    return nullptr;
}

HttpRequest HttpRequest::queryString(Object> parameters) {
    // TODO: Implement queryString
    return nullptr;
}

HttpMethod HttpRequest::getHttpMethod() {
    // TODO: Implement getHttpMethod
    return nullptr;
}

std::string HttpRequest::getUrl() {
    // TODO: Implement getUrl
    return "";
}

Body HttpRequest::getBody() {
    // TODO: Implement getBody
    return nullptr;
}

} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
