#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/ByteArrayDataSource.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/PcdataImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/util/ByteArrayOutputStreamEx.h"
#include "com/sun/xml/bind/v2/util/DataSourceSource.h"
#include "javax/activation/DataHandler.h"
#include "javax/activation/DataSource.h"
#include "javax/activation/MimeType.h"
#include "javax/activation/MimeTypeParseException.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/Transformer.h"
#include "javax/xml/transform/TransformerException.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$12(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    Source parse(CharSequence text) {
      try {
         return dynamic_cast<Base64Data*>(text) != nullptr
            ? std::make_shared<DataSourceSource>(((Base64Data)text).getDataHandler())
            : std::make_shared<DataSourceSource>(
    std::make_shared<ByteArrayDataSource>();
            );
      } catch (MimeTypeParseException var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    Base64Data print(Source v) {
    XMLSerializer xs = XMLSerializer.getInstance();
    Base64Data bd = std::make_shared<Base64Data>();
    std::string contentType = xs.getXMIMEContentType();
    MimeType mt = nullptr;
      if (contentType != nullptr) {
         try {
            mt = std::make_shared<MimeType>(contentType);
         } catch (MimeTypeParseException var12) {
            xs.handleError(var12);
         }
      }

      if (dynamic_cast<DataSourceSource*>(v) != nullptr) {
    DataSource ds = ((DataSourceSource)v).getDataSource();
    std::string dsct = ds.getContentType();
         if (dsct != nullptr && (contentType == nullptr || contentType == dsct))) {
            bd.set(std::make_shared<DataHandler>(ds));
    return bd;
         }
      }

    std::string charset = nullptr;
      if (mt != nullptr) {
         charset = mt.getParameter("charset");
      }

      if (charset == nullptr) {
         charset = "UTF-8";
      }

      try {
    ByteArrayOutputStreamEx baos = std::make_shared<ByteArrayOutputStreamEx>();
    Transformer tr = xs.getIdentityTransformer();
    std::string defaultEncoding = tr.getOutputProperty("encoding");
         tr.setOutputProperty("encoding", charset);
         tr.transform(v, std::make_shared<StreamResult>(std::make_shared<OutputStreamWriter>(baos, charset)));
         tr.setOutputProperty("encoding", defaultEncoding);
         baos.set(bd, "application/xml; charset=" + charset);
    return bd;
      } catch (TransformerException var10) {
         xs.handleError(var10);
      } catch (UnsupportedEncodingException var11) {
         xs.handleError(var11);
      }

      bd.set(new byte[0], "application/xml");
    return bd;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
