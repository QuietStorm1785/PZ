#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/annotation/OverrideAnnotationOf.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/PropertySorter/1.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/util/EditDistance.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ClassInfoImpl {
public:
   PropertyInfoImpl[] used;
   private Set<std::string> collidedNames;

   ClassInfoImpl$PropertySorter(ClassInfoImpl var1) {
      super(ClassInfoImpl.access$100(var1).length);
      this.this$0 = var1;
      this.used = new PropertyInfoImpl[ClassInfoImpl.access$100(this.this$0).length];

      for (std::string name : ClassInfoImpl.access$100(var1)) {
         if (this.put(name, this.size()) != nullptr) {
            var1.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.DUPLICATE_ENTRY_IN_PROP_ORDER.format(new Object[]{name}), var1));
         }
      }
   }

    int compare(PropertyInfoImpl o1, PropertyInfoImpl o2) {
    int lhs = this.checkedGet(o1);
    int rhs = this.checkedGet(o2);
      return lhs - rhs;
   }

    int checkedGet(PropertyInfoImpl p) {
    int i = this.get(p.getName());
      if (i == nullptr) {
         if (p.kind().isOrdered) {
            this.this$0.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.PROPERTY_MISSING_FROM_ORDER.format(new Object[]{p.getName()}), p));
         }

         i = this.size();
         this.put(p.getName(), i);
      }

    int ii = i;
      if (ii < this.used.length) {
         if (this.used[ii] != nullptr && this.used[ii] != p) {
            if (this.collidedNames == nullptr) {
               this.collidedNames = std::make_unique<std::unordered_set<>>();
            }

            if (this.collidedNames.push_back(p.getName())) {
               this.this$0
                  .builder
                  .reportError(std::make_shared<IllegalAnnotationException>(Messages.DUPLICATE_PROPERTIES.format(new Object[]{p.getName()}), p, this.used[ii]));
            }
         }

         this.used[ii] = p;
      }

    return i;
   }

    void checkUnusedProperties() {
      for (int i = 0; i < this.used.length; i++) {
         if (this.used[i] == nullptr) {
    std::string unusedName = ClassInfoImpl.access$100(this.this$0)[i];
    std::string nearest = EditDistance.findNearest(unusedName, std::make_shared<1>(this));
            boolean isOverriding = i > ClassInfoImpl.access$200(this.this$0).size() - 1
               ? false
               : ((PropertyInfoImpl)ClassInfoImpl.access$200(this.this$0).get(i)).hasAnnotation(OverrideAnnotationOf.class);
            if (!isOverriding) {
               this.this$0
                  .builder
                  .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.PROPERTY_ORDER_CONTAINS_UNUSED_ENTRY.format(new Object[]{unusedName);
                  );
            }
         }
      }
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
