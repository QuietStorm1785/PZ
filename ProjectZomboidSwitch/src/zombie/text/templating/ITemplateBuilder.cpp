#include <string>
#include "zombie\text\templating/ITemplateBuilder.h"

namespace zombie {
namespace text {
namespace templating {

std::string ITemplateBuilder::Build(const std::string& var1) {
    // TODO: Implement Build
    return "";
}

std::string ITemplateBuilder::Build(const std::string& var1, IReplaceProvider var2) {
    // TODO: Implement Build
    return "";
}

std::string ITemplateBuilder::Build(const std::string& var1, KahluaTableImpl var2) {
    // TODO: Implement Build
    return "";
}

void ITemplateBuilder::RegisterKey(const std::string& var1, KahluaTableImpl var2) {
    // TODO: Implement RegisterKey
}

void ITemplateBuilder::RegisterKey(const std::string& var1, IReplace var2) {
    // TODO: Implement RegisterKey
}

void ITemplateBuilder::Reset() {
    // TODO: Implement Reset
}

} // namespace templating
} // namespace text
} // namespace zombie
