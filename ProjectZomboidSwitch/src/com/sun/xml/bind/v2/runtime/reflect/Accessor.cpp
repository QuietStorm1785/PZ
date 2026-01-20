#include "com\sun\xml\bind\v2\runtime\reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {

protected Accessor::Accessor(Class<ValueT> valueType) {
    // TODO: Implement Accessor
    return nullptr;
}

void* Accessor::getUnadapted(BeanT bean) {
    // TODO: Implement getUnadapted
    return nullptr;
}

bool Accessor::isAdapted() {
    // TODO: Implement isAdapted
    return false;
}

void Accessor::setUnadapted(BeanT bean, void* value) {
    // TODO: Implement setUnadapted
}

void Accessor::receive(State state, void* o) {
    // TODO: Implement receive
}

bool Accessor::isValueTypeAbstractable() {
    // TODO: Implement isValueTypeAbstractable
    return false;
}

bool Accessor::isAbstractable(Class clazz) {
    // TODO: Implement isAbstractable
    return false;
}

} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
