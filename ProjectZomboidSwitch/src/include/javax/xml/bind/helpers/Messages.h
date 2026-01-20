#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class Messages {
public:
    static const std::string INPUTSTREAM_NOT_NULL = "AbstractUnmarshallerImpl.ISNotNull";
    static const std::string MUST_BE_BOOLEAN = "AbstractMarshallerImpl.MustBeBoolean";
    static const std::string MUST_BE_STRING = "AbstractMarshallerImpl.MustBeString";
    static const std::string SEVERITY_MESSAGE = "DefaultValidationEventHandler.SeverityMessage";
    static const std::string LOCATION_UNAVAILABLE = "DefaultValidationEventHandler.LocationUnavailable";
    static const std::string UNRECOGNIZED_SEVERITY = "DefaultValidationEventHandler.UnrecognizedSeverity";
    static const std::string WARNING = "DefaultValidationEventHandler.Warning";
    static const std::string ERROR = "DefaultValidationEventHandler.Error";
    static const std::string FATAL_ERROR = "DefaultValidationEventHandler.FatalError";
    static const std::string ILLEGAL_SEVERITY = "ValidationEventImpl.IllegalSeverity";
    static const std::string MUST_NOT_BE_NULL = "Shared.MustNotBeNull";

    static std::string format(const std::string& property) {
    return format();
   }

    static std::string format(const std::string& property, void* arg1) {
    return format(new Object[]{arg1});
   }

    static std::string format(const std::string& property, void* arg1, void* arg2) {
    return format(new Object[]{arg1);
   }

    static std::string format(const std::string& property, void* arg1, void* arg2, void* arg3) {
    return format(new Object[]{arg1);
   }

    static std::string format(const std::string& property, Object[] args) {
    std::string text = ResourceBundle.getBundle(Messages.class.getName()).getString(property);
      return MessageFormat.format(text, args);
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
