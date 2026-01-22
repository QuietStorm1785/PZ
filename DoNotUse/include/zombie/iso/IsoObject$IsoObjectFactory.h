#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoObject {
public:
    const uint8_t classID;
    const std::string objectName;
    const int hashCode;

   public IsoObject$IsoObjectFactory(byte var1, std::string var2) {
      this.classID = var1;
      this.objectName = var2;
      this.hashCode = var2.hashCode();
   }

    IsoObject InstantiateObject(IsoCell var1) {
      return std::make_shared<IsoObject>(var1);
   }

    uint8_t getClassID() {
      return this.classID;
   }

    std::string getObjectName() {
      return this.objectName;
   }
}
} // namespace iso
} // namespace zombie
