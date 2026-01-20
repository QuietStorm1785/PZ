#include <string>
#include "com\mashape\unirest\request\body/MultipartBody.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {
namespace body {

public MultipartBody::MultipartBody(HttpRequest httpRequest) {
    // TODO: Implement MultipartBody
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, const std::string& value) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, const std::string& value, const std::string& contentType) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, Collection<?> collection) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, void* value) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, void* value, bool file) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, void* value, bool file, const std::string& contentType) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, File file) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, File file, const std::string& contentType) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, InputStream stream, ContentType contentType, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, InputStream stream, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, byte[] bytes, ContentType contentType, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::field(const std::string& name, byte[] bytes, const std::string& fileName) {
    // TODO: Implement field
    return nullptr;
}

MultipartBody MultipartBody::basicAuth(const std::string& username, const std::string& password) {
    // TODO: Implement basicAuth
    return nullptr;
}

MultipartBody MultipartBody::mode(const std::string& mode) {
    // TODO: Implement mode
    return nullptr;
}

HttpEntity MultipartBody::getEntity() {
    // TODO: Implement getEntity
    return nullptr;
}

} // namespace body
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
