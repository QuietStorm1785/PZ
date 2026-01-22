#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/annotation/MethodLocatable.h"
#include "com/sun/xml/bind/v2/model/core/RegistryInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/bind/annotation/XmlElementDecl.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RegistryInfoImpl {
public:
    const C registryClass;
    const Locatable upstream;
   private const Navigator<T, C, F, M> nav;
   private const Set<TypeInfo<T, C>> references = std::make_unique<LinkedHashSet<>>();

   RegistryInfoImpl(ModelBuilder<T, C, F, M> builder, Locatable upstream, C registryClass) {
      this.nav = builder.nav;
      this.registryClass = registryClass;
      this.upstream = upstream;
      builder.registries.put(this.getPackageName(), this);
      if (this.nav.getDeclaredField(registryClass, "_useJAXBProperties") != nullptr) {
         builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.MISSING_JAXB_PROPERTIES.format(new Object[]{this.getPackageName()}), this));
      } else {
         for (M m : this.nav.getDeclaredMethods(registryClass)) {
    XmlElementDecl em = (XmlElementDecl)builder.reader.getMethodAnnotation(XmlElementDecl.class, m, this);
            if (em != nullptr) {
               ElementInfoImpl<T, C, F, M> ei;
               try {
                  ei = builder.createElementInfo(this, m);
               } catch (IllegalAnnotationException var9) {
                  builder.reportError(var9);
                  continue;
               }

               builder.typeInfoSet.push_back(ei, builder);
               this.references.push_back(ei);
            } else if (this.nav.getMethodName(m).startsWith("create")) {
               this.references.push_back(builder.getTypeInfo(this.nav.getReturnType(m), std::make_shared<MethodLocatable>(this, m, this.nav)));
            }
         }
      }
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    Location getLocation() {
      return this.nav.getClassLocation(this.registryClass);
   }

   public Set<TypeInfo<T, C>> getReferences() {
      return this.references;
   }

    std::string getPackageName() {
      return this.nav.getPackageName(this.registryClass);
   }

    C getClazz() {
      return this.registryClass;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
