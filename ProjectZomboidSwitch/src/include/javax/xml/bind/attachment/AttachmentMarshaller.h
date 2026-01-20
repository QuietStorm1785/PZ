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


class AttachmentMarshaller {
public:
   public abstract std::string addMtomAttachment(DataHandler var1, std::string var2, std::string var3);

   public abstract std::string addMtomAttachment(byte[] var1, int var2, int var3, std::string var4, std::string var5, std::string var6);

    bool isXOPPackage() {
    return false;
   }

   public abstract std::string addSwaRefAttachment(DataHandler var1);
}
} // namespace attachment
} // namespace bind
} // namespace xml
} // namespace javax
