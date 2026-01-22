#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/SAXException2.h"
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/IDREFTransducedAccessorImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx/Snapshot.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class TransducedAccessor {
public:
   private const Accessor<BeanT, TargetT> acc;
   private const Class<TargetT> targetType;

   public TransducedAccessor$IDREFTransducedAccessorImpl(Accessor<BeanT, TargetT> acc) {
      this.acc = acc;
      this.targetType = acc.getValueType();
   }

    std::string print(BeanT bean) {
    TargetT target = (TargetT)this.acc.get(bean);
      if (target == nullptr) {
    return nullptr;
      } else {
    XMLSerializer w = XMLSerializer.getInstance();

         try {
    std::string id = w.grammar.getBeanInfo(target, true).getId(target, w);
            if (id == nullptr) {
               w.errorMissingId(target);
            }

    return id;
         } catch (JAXBException var5) {
            w.reportError(nullptr, var5);
    return nullptr;
         }
      }
   }

    void assign(BeanT bean, TargetT t, UnmarshallingContext context) {
      if (!this.targetType.isInstance(t)) {
         context.handleError(Messages.UNASSIGNABLE_TYPE.format(new Object[]{this.targetType, t.getClass()}));
      } else {
         this.acc.set(bean, t);
      }
   }

    void parse(BeanT bean, CharSequence lexical) {
    std::string idref = WhiteSpaceProcessor.trim(lexical);
    UnmarshallingContext context = UnmarshallingContext.getInstance();
    Callable callable = context.getObjectFromId(idref, this.acc.valueType);
      if (callable == nullptr) {
         context.errorUnresolvedIDREF(bean, idref, context.getLocator());
      } else {
    TargetT t;
         try {
            t = (TargetT)callable.call();
         } catch (SAXException var8) {
    throw var8;
         } catch (RuntimeException var9) {
    throw var9;
         } catch (Exception var10) {
            throw SAXException2(var10);
         }

         if (t != nullptr) {
            this.assign(bean, t, context);
         } else {
    LocatorEx loc = std::make_shared<Snapshot>(context.getLocator());
            context.addPatcher(std::make_shared<1>(this, callable, context, bean, idref, loc));
         }
      }
   }

    bool hasValue(BeanT bean) {
      return this.acc.get(bean) != nullptr;
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
