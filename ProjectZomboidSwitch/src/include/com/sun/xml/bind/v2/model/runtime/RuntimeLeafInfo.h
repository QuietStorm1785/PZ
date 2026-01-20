#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/LeafInfo.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeLeafInfo {
public:
    virtual ~RuntimeLeafInfo() = default;
   <V> Transducer<V> getTransducer();

    Class getClazz();

   QName[] getTypeNames();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
