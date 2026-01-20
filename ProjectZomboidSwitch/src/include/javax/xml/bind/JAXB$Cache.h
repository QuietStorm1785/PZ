#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {

class JAXB {
public:
    const Class type;
    const JAXBContext context;

   public JAXB$Cache(Class type) throws JAXBException {
      this.type = type;
      this.context = JAXBContext.newInstance(new Class[]{type});
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
