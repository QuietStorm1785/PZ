#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/activation/DataHandler.h"

namespace javax {
namespace xml {
namespace bind {
namespace attachment {


class AttachmentUnmarshaller {
public:
   public abstract DataHandler getAttachmentAsDataHandler(std::string var1);

   public abstract byte[] getAttachmentAsByteArray(std::string var1);

    bool isXOPPackage() {
    return false;
   }
}
} // namespace attachment
} // namespace bind
} // namespace xml
} // namespace javax
