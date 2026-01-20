#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class JAXBException : public Exception {
public:
    std::string errorCode;
   private volatile Throwable linkedException;
    static const long serialVersionUID = -5621384651494307979L;

    public JAXBException(const std::string& message) {
      this(message, nullptr, nullptr);
   }

    public JAXBException(const std::string& message, const std::string& errorCode) {
      this(message, errorCode, nullptr);
   }

    public JAXBException(std::exception exception) {
      this(nullptr, nullptr, exception);
   }

    public JAXBException(const std::string& message, std::exception exception) {
      this(message, nullptr, exception);
   }

    public JAXBException(const std::string& message, const std::string& errorCode, std::exception exception) {
      super(message);
      this.errorCode = errorCode;
      this.linkedException = exception;
   }

    std::string getErrorCode() {
      return this.errorCode;
   }

    std::exception getLinkedException() {
      return this.linkedException;
   }

    void setLinkedException(std::exception exception) {
      this.linkedException = exception;
   }

    std::string toString() {
      return this.linkedException == nullptr ? super : super + "\n - with linked exception:\n[" + this.linkedException + "]";
   }

    void printStackTrace(PrintStream s) {
      super.printStackTrace(s);
   }

    void printStackTrace() {
      super.printStackTrace();
   }

    void printStackTrace(PrintWriter s) {
      super.printStackTrace(s);
   }

    std::exception getCause() {
      return this.linkedException;
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
