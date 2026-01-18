#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/expose/ReturnValues.h"
#include "se/krka/kahlua/integration/processor/DescriptorUtil.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/ui/UIManager.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
namespace caller {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MethodCaller : public AbstractCaller {
public:
 const Method method;
 const void* owner;
 const bool hasSelf;
 const bool hasReturnValue;

 public MethodCaller(Method methodx, void* object, bool boolean0) {
 super(methodx.getParameterTypes(), methodx.isVarArgs());
 this->method = methodx;
 this->owner = object;
 this->hasSelf = boolean0;
 methodx.setAccessible(true);
 this->hasReturnValue = !methodx.getReturnType() == void.class);
 if (this->hasReturnValue && this->needsMultipleReturnValues()) {
 throw IllegalArgumentException("Must have a void return type if first argument is a ReturnValues: got: " + methodx.getReturnType());
 }
 }

 void call(void* object0, ReturnValues returnValues, Object[] objects) {
 if (!this->hasSelf) {
 object0 = this->owner;
 }

 try {
 void* object1 = this->method.invoke(object0, objects);
 if (this->hasReturnValue) {
 returnValues.push(object1);
 }
 } catch (Exception exception) {
 UIManager.defaultthread.doStacktraceProper();
 UIManager.defaultthread.debugException(exception);
 ExceptionLogger.logException(exception);
 }
 }

 bool hasSelf() {
 return this->hasSelf;
 }

 std::string getDescriptor() {
 return DescriptorUtil.getDescriptor(this->method);
 }

 bool equals(void* object) {
 if (this == object) {
 return true;
 } else if (object != nullptr && this->getClass() == object.getClass()) {
 MethodCaller methodCaller1 = (MethodCaller)object;
 if (!this->method == methodCaller1.method) {
 return false;
 } else {
 return this->owner != nullptr ? this->owner == methodCaller1.owner) : methodCaller1.owner.empty();
 }
 } else {
 return false;
 }
 }

 int hashCode() {
 int int0 = this->method.hashCode();
 return 31 * int0 + (this->owner != nullptr ? this->owner.hashCode() : 0);
 }
}
} // namespace caller
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
