
#pragma once

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

// Ported from Java: RequestDataManager and all inner classes

class RequestDataManager {
public:
    RequestDataManager();
    ~RequestDataManager();
    // TODO: Port fields and methods from Java RequestDataManager

    // Inner classes from Java (RequestData)
    class RequestData {
    public:
        RequestData();
        ~RequestData();
        // TODO: Port fields and methods from Java RequestDataManager.RequestData
    };
};

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
