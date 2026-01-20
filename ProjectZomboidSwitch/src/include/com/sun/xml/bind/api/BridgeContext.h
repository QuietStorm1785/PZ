#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


/** @deprecated */
class BridgeContext {
public:
    protected BridgeContext() {
   }

   public abstract void setErrorHandler(ValidationEventHandler var1);

   public abstract void setAttachmentMarshaller(AttachmentMarshaller var1);

   public abstract void setAttachmentUnmarshaller(AttachmentUnmarshaller var1);

   public abstract AttachmentMarshaller getAttachmentMarshaller();

   public abstract AttachmentUnmarshaller getAttachmentUnmarshaller();
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
