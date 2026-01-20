#include <string>
#include "com\mashape\unirest\http/HttpResponse.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {

public HttpResponse::HttpResponse(org.apache.http.HttpResponse response, Class<T> responseClass) {
    // TODO: Implement HttpResponse
    return nullptr;
}

int HttpResponse::getStatus() {
    // TODO: Implement getStatus
    return 0;
}

std::string HttpResponse::getStatusText() {
    // TODO: Implement getStatusText
    return "";
}

Headers HttpResponse::getHeaders() {
    // TODO: Implement getHeaders
    return nullptr;
}

InputStream HttpResponse::getRawBody() {
    // TODO: Implement getRawBody
    return nullptr;
}

T HttpResponse::getBody() {
    // TODO: Implement getBody
    return nullptr;
}

} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
