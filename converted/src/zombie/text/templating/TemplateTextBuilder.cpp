#include "zombie/text/templating/TemplateTextBuilder.h"

namespace zombie {
namespace text {
namespace templating {

protected TemplateTextBuilder::TemplateTextBuilder() {
 // TODO: Implement TemplateTextBuilder
 return nullptr;
}

void TemplateTextBuilder::Reset() {
 // TODO: Implement Reset
}

std::string TemplateTextBuilder::Build(const std::string& string) {
 // TODO: Implement Build
 return "";
}

std::string TemplateTextBuilder::Build(const std::string& string, IReplaceProvider iReplaceProvider) {
 // TODO: Implement Build
 return "";
}

std::string TemplateTextBuilder::Build(const std::string& string1, KahluaTableImpl kahluaTableImpl) {
 // TODO: Implement Build
 return "";
}

std::string TemplateTextBuilder::format(const std::string& string0, IReplaceProvider iReplaceProvider) {
 // TODO: Implement format
 return "";
}

void TemplateTextBuilder::RegisterKey(const std::string& string, KahluaTableImpl kahluaTableImpl) {
 // TODO: Implement RegisterKey
}

void TemplateTextBuilder::RegisterKey(const std::string& string, IReplace iReplace) {
 // TODO: Implement RegisterKey
}

void TemplateTextBuilder::localRegisterKey(const std::string& string, IReplace iReplace) {
 // TODO: Implement localRegisterKey
}

} // namespace templating
} // namespace text
} // namespace zombie
