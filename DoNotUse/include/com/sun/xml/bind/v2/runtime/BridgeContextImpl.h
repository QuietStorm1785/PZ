#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/BridgeContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class BridgeContextImpl : public BridgeContext {
public:
    const UnmarshallerImpl unmarshaller;
    const MarshallerImpl marshaller;

   BridgeContextImpl(JAXBContextImpl context) {
      this.unmarshaller = context.createUnmarshaller();
      this.marshaller = context.createMarshaller();
   }

    void setErrorHandler(ValidationEventHandler handler) {
      try {
         this.unmarshaller.setEventHandler(handler);
         this.marshaller.setEventHandler(handler);
      } catch (JAXBException var3) {
         throw Error(var3);
      }
   }

    void setAttachmentMarshaller(AttachmentMarshaller m) {
      this.marshaller.setAttachmentMarshaller(m);
   }

    void setAttachmentUnmarshaller(AttachmentUnmarshaller u) {
      this.unmarshaller.setAttachmentUnmarshaller(u);
   }

    AttachmentMarshaller getAttachmentMarshaller() {
      return this.marshaller.getAttachmentMarshaller();
   }

    AttachmentUnmarshaller getAttachmentUnmarshaller() {
      return this.unmarshaller.getAttachmentUnmarshaller();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
