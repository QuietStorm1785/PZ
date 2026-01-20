#include <string>
#include "com\mashape\unirest\http\utils/ResponseUtils.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {

std::string ResponseUtils::getCharsetFromContentType(const std::string& contentType) {
    // TODO: Implement getCharsetFromContentType
    return "";
}

bool ResponseUtils::isGzipped(Header contentEncoding) {
    // TODO: Implement isGzipped
    return false;
}

} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
