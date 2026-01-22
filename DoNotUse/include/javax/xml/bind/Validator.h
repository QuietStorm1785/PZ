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

/** @deprecated */
class Validator {
public:
    virtual ~Validator() = default;
   /** @deprecated */
    void setEventHandler(ValidationEventHandler var1);

   /** @deprecated */
    ValidationEventHandler getEventHandler();

   /** @deprecated */
    bool validate(void* var1);

   /** @deprecated */
    bool validateRoot(void* var1);

   /** @deprecated */
    void setProperty(const std::string& var1, void* var2);

   /** @deprecated */
    void* getProperty(const std::string& var1);
}
} // namespace bind
} // namespace xml
} // namespace javax
