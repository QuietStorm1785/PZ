#include "zombie/text/templating/ITemplateBuilder.h"

namespace zombie {
namespace text {
namespace templating {

std::string ITemplateBuilder::Build(const std::string& input) {
 // TODO: Implement Build
 return "";
}

std::string ITemplateBuilder::Build(const std::string& input, IReplaceProvider replaceProvider) {
 // TODO: Implement Build
 return "";
}

std::string ITemplateBuilder::Build(const std::string& input, KahluaTableImpl table) {
 // TODO: Implement Build
 return "";
}

void ITemplateBuilder::RegisterKey(const std::string& key, KahluaTableImpl table) {
 // TODO: Implement RegisterKey
}

void ITemplateBuilder::RegisterKey(const std::string& key, IReplace replace) {
 // TODO: Implement RegisterKey
}

void ITemplateBuilder::Reset() {
 // TODO: Implement Reset
}

} // namespace templating
} // namespace text
} // namespace zombie
