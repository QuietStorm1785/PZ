#pragma once
#include <exception>
#include <string>

class GLUSException : public std::exception {
public:
    explicit GLUSException(const std::string& message)
        : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};
