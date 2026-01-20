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
namespace marshaller {


class Messages {
public:
    static const std::string NOT_MARSHALLABLE = "MarshallerImpl.NotMarshallable";
    static const std::string UNSUPPORTED_RESULT = "MarshallerImpl.UnsupportedResult";
    static const std::string UNSUPPORTED_ENCODING = "MarshallerImpl.UnsupportedEncoding";
    static const std::string NULL_WRITER = "MarshallerImpl.NullWriterParam";
    static const std::string ASSERT_FAILED = "SAXMarshaller.AssertFailed";
   /** @deprecated */
    static const std::string ERR_MISSING_OBJECT = "SAXMarshaller.MissingObject";
   /** @deprecated */
    static const std::string ERR_DANGLING_IDREF = "SAXMarshaller.DanglingIDREF";
   /** @deprecated */
    static const std::string ERR_NOT_IDENTIFIABLE = "SAXMarshaller.NotIdentifiable";
    static const std::string DOM_IMPL_DOESNT_SUPPORT_CREATELEMENTNS = "SAX2DOMEx.DomImplDoesntSupportCreateElementNs";

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
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
