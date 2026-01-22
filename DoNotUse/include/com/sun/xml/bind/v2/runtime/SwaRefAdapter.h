#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/activation/DataHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class SwaRefAdapter : public XmlAdapter {
public:
    DataHandler unmarshal(const std::string& cid) {
    AttachmentUnmarshaller au = UnmarshallingContext.getInstance().parent.getAttachmentUnmarshaller();
      return au.getAttachmentAsDataHandler(cid);
   }

    std::string marshal(DataHandler data) {
      if (data == nullptr) {
    return nullptr;
      } else {
    AttachmentMarshaller am = XMLSerializer.getInstance().attachmentMarshaller;
         return am.addSwaRefAttachment(data);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
