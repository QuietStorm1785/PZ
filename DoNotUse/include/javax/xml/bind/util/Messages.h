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
namespace util {


class Messages {
public:
    static const std::string UNRECOGNIZED_SEVERITY = "ValidationEventCollector.UnrecognizedSeverity";
    static const std::string RESULT_NULL_CONTEXT = "JAXBResult.NullContext";
    static const std::string RESULT_NULL_UNMARSHALLER = "JAXBResult.NullUnmarshaller";
    static const std::string SOURCE_NULL_CONTEXT = "JAXBSource.NullContext";
    static const std::string SOURCE_NULL_CONTENT = "JAXBSource.NullContent";
    static const std::string SOURCE_NULL_MARSHALLER = "JAXBSource.NullMarshaller";

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
} // namespace util
} // namespace bind
} // namespace xml
} // namespace javax
