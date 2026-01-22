#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/impl/ModelBuilderI.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "javax/xml/bind/annotation/XmlList.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class Ref {
public:
    const T type;
   public const Adapter<T, C> adapter;
    const bool valueList;

    public Ref(T type) {
      this(type, nullptr, false);
   }

    public Ref(T type, C> adapter, bool valueList) {
      this.adapter = adapter;
      if (adapter != nullptr) {
         type = (T)adapter.defaultType;
      }

      this.type = type;
      this.valueList = valueList;
   }

    public Ref(?> builder, T type, XmlJavaTypeAdapter xjta, XmlList xl) {
      this(builder.getReader(), builder.getNavigator(), type, xjta, xl);
   }

    public Ref(?> reader, ?> nav, T type, XmlJavaTypeAdapter xjta, XmlList xl) {
      Adapter<T, C> adapter = nullptr;
      if (xjta != nullptr) {
         adapter = std::make_shared<Adapter>(xjta, reader, nav);
         type = (T)adapter.defaultType;
      }

      this.type = type;
      this.adapter = adapter;
      this.valueList = xl != nullptr;
   }
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
