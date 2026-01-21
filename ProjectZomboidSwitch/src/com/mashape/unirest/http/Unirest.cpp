#include <string>
#include "com/mashape/unirest/http/Unirest.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {

void Unirest::setHttpClient(HttpClient httpClient) {
    // TODO: Implement setHttpClient
}

void Unirest::setAsyncHttpClient(CloseableHttpAsyncClient asyncHttpClient) {
    // TODO: Implement setAsyncHttpClient
}

void Unirest::setProxy(HttpHost proxy) {
    // TODO: Implement setProxy
}

void Unirest::setObjectMapper(ObjectMapper objectMapper) {
    // TODO: Implement setObjectMapper
}

void Unirest::setTimeouts(long connectionTimeout, long socketTimeout) {
    // TODO: Implement setTimeouts
}

void Unirest::setConcurrency(int maxTotal, int maxPerRoute) {
    // TODO: Implement setConcurrency
}

void Unirest::clearDefaultHeaders() {
    // TODO: Implement clearDefaultHeaders
}

void Unirest::setDefaultHeader(const std::string& name, const std::string& value) {
    // TODO: Implement setDefaultHeader
}

void Unirest::shutdown() {
    // TODO: Implement shutdown
}

GetRequest Unirest::get(const std::string& url) {
    // TODO: Implement get
    return nullptr;
}

GetRequest Unirest::head(const std::string& url) {
    // TODO: Implement head
    return nullptr;
}

HttpRequestWithBody Unirest::options(const std::string& url) {
    // TODO: Implement options
    return nullptr;
}

HttpRequestWithBody Unirest::post(const std::string& url) {
    // TODO: Implement post
    return nullptr;
}

HttpRequestWithBody Unirest::delete(const std::string& url) {
    // TODO: Implement delete
    return nullptr;
}

HttpRequestWithBody Unirest::patch(const std::string& url) {
    // TODO: Implement patch
    return nullptr;
}

HttpRequestWithBody Unirest::put(const std::string& url) {
    // TODO: Implement put
    return nullptr;
}

} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
