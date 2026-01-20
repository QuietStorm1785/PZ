#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace unmarshaller {


class Messages {
public:
    static const std::string UNEXPECTED_ENTER_ELEMENT = "ContentHandlerEx.UnexpectedEnterElement";
    static const std::string UNEXPECTED_LEAVE_ELEMENT = "ContentHandlerEx.UnexpectedLeaveElement";
    static const std::string UNEXPECTED_ENTER_ATTRIBUTE = "ContentHandlerEx.UnexpectedEnterAttribute";
    static const std::string UNEXPECTED_LEAVE_ATTRIBUTE = "ContentHandlerEx.UnexpectedLeaveAttribute";
    static const std::string UNEXPECTED_TEXT = "ContentHandlerEx.UnexpectedText";
    static const std::string UNEXPECTED_LEAVE_CHILD = "ContentHandlerEx.UnexpectedLeaveChild";
    static const std::string UNEXPECTED_ROOT_ELEMENT = "SAXUnmarshallerHandlerImpl.UnexpectedRootElement";
    static const std::string UNDEFINED_PREFIX = "Util.UndefinedPrefix";
    static const std::string NULL_READER = "Unmarshaller.NullReader";
    static const std::string ILLEGAL_READER_STATE = "Unmarshaller.IllegalReaderState";

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
} // namespace unmarshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
