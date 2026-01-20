#include <string>
#include "com\sun\xml\bind\v2\runtime\unmarshaller/Loader.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {

protected Loader::Loader(bool expectText) {
    // TODO: Implement Loader
    return nullptr;
}

protected Loader::Loader() {
    // TODO: Implement Loader
    return nullptr;
}

void Loader::startElement(State state, TagName ea) {
    // TODO: Implement startElement
}

void Loader::childElement(State state, TagName ea) {
    // TODO: Implement childElement
}

void Loader::reportUnexpectedChildElement(TagName ea, bool canRecover) {
    // TODO: Implement reportUnexpectedChildElement
}

void Loader::text(State state, CharSequence text) {
    // TODO: Implement text
}

bool Loader::expectText() {
    // TODO: Implement expectText
    return false;
}

void Loader::leaveElement(State state, TagName ea) {
    // TODO: Implement leaveElement
}

std::string Loader::computeExpectedElements() {
    // TODO: Implement computeExpectedElements
    return "";
}

void Loader::fireBeforeUnmarshal(JaxBeanInfo beanInfo, void* child, State state) {
    // TODO: Implement fireBeforeUnmarshal
}

void Loader::fireAfterUnmarshal(JaxBeanInfo beanInfo, void* child, State state) {
    // TODO: Implement fireAfterUnmarshal
}

void Loader::handleGenericException(std::exception e) {
    // TODO: Implement handleGenericException
}

void Loader::handleGenericException(std::exception e, bool canRecover) {
    // TODO: Implement handleGenericException
}

void Loader::handleGenericError(Error e) {
    // TODO: Implement handleGenericError
}

void Loader::reportError(const std::string& msg, bool canRecover) {
    // TODO: Implement reportError
}

void Loader::reportError(const std::string& msg, std::exception nested, bool canRecover) {
    // TODO: Implement reportError
}

void Loader::handleParseConversionException(State state, std::exception e) {
    // TODO: Implement handleParseConversionException
}

} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
