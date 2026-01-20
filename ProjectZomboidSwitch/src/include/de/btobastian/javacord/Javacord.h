#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/utils/ThreadPool.h"

namespace de {
namespace btobastian {
namespace javacord {


class Javacord {
public:
    static constexpr const char* VERSION = "2.0.17";
    static constexpr const char* GITHUB_URL = "https://github.com/BtoBastian/Javacord";
    static constexpr const char* USER_AGENT = "DiscordBot (https://github.com/BtoBastian/Javacord, v2.0.17)";

    Javacord() = delete;

    static std::shared_ptr<DiscordAPI> getApi() {
        // TODO: Replace with actual C++ implementation
        return std::make_shared<ImplDiscordAPI>(std::make_unique<ThreadPool>());
    }

    static std::shared_ptr<DiscordAPI> getApi(const std::string& email, const std::string& password) {
        auto api = getApi();
        api->setEmail(email);
        api->setPassword(password);
        return api;
    }

    static std::shared_ptr<DiscordAPI> getApi(const std::string& token, bool bot) {
        auto api = getApi();
        api->setToken(token, bot);
        return api;
    }

    // In C++, set default headers in your HTTP client initialization, not in a static block
};
} // namespace javacord
} // namespace btobastian
} // namespace de
