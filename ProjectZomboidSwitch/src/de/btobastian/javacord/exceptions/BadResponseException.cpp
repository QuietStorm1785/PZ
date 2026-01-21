#include <string>
#include "de/btobastian/javacord/exceptions/BadResponseException.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace exceptions {

public BadResponseException::BadResponseException(const std::string& message, int status, const std::string& statusText, HttpResponse<JsonNode> response) {
    // TODO: Implement BadResponseException
    return nullptr;
}

int BadResponseException::getStatus() {
    // TODO: Implement getStatus
    return 0;
}

std::string BadResponseException::getStatusText() {
    // TODO: Implement getStatusText
    return "";
}

} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
