#include <string>
#include "com\mashape\unirest\request/HttpRequestWithBody.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {

public HttpRequestWithBody::HttpRequestWithBody(HttpMethod method, const std::string& url) {
    // TODO: Implement HttpRequestWithBody
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::routeParam(const std::string& name, const std::string& value) {
    // TODO: Implement routeParam
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::header(const std::string& name, const std::string& value) {
    // TODO: Implement header
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::headers(std::string> headers) {
    // TODO: Implement headers
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::basicAuth(const std::string& username, const std::string& password) {
    // TODO: Implement basicAuth
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::queryString(Object> parameters) {
    // TODO: Implement queryString
    return nullptr;
}

HttpRequestWithBody HttpRequestWithBody::queryString(const std::string& name, void* value) {
    // TODO: Implement queryString
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, Collection<?> value) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, void* value) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, File file) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, void* value, const std::string& contentType) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, File file, const std::string& contentType) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::fields(Object> parameters) {
    // TODO: Implement fields
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, InputStream stream, ContentType contentType, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody HttpRequestWithBody::field(const std::string& name, InputStream stream, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

RequestBodyEntity HttpRequestWithBody::body(JsonNode body) {
    // TODO: Implement body
    return nullptr;
}

RequestBodyEntity HttpRequestWithBody::body(const std::string& body) {
    // TODO: Implement body
    return nullptr;
}

RequestBodyEntity HttpRequestWithBody::body(void* body) {
    // TODO: Implement body
    return nullptr;
}

RawBody HttpRequestWithBody::body(byte[] body) {
    // TODO: Implement body
    return nullptr;
}

RequestBodyEntity HttpRequestWithBody::body(JSONObject body) {
    // TODO: Implement body
    return nullptr;
}

RequestBodyEntity HttpRequestWithBody::body(JSONArray body) {
    // TODO: Implement body
    return nullptr;
}

} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
