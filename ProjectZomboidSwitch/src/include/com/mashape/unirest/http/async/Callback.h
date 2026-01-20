#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace async {


class Callback {
public:
    virtual ~Callback() = default;
    void completed(HttpResponse<T> var1);

    void failed(UnirestException var1);

    void cancelled();
}
} // namespace async
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
