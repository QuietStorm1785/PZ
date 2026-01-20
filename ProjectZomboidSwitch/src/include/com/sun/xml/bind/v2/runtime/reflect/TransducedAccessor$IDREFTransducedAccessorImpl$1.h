#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/SAXException2.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/IDREFTransducedAccessorImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Patcher.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
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
   TransducedAccessor$IDREFTransducedAccessorImpl$1(
      IDREFTransducedAccessorImpl this$0, Callable var2, UnmarshallingContext var3, Object var4, std::string var5, LocatorEx var6
   ) {
      this.this$0 = this$0;
      this.val$callable = var2;
      this.val$context = var3;
      this.val$bean = var4;
      this.val$idref = var5;
      this.val$loc = var6;
   }

    void run() {
      try {
    TargetT t = (TargetT)this.val$callable.call();
         if (t == nullptr) {
            this.val$context.errorUnresolvedIDREF(this.val$bean, this.val$idref, this.val$loc);
         } else {
            IDREFTransducedAccessorImpl.access$000(this.this$0, this.val$bean, t, this.val$context);
         }
      } catch (AccessorException var2) {
         this.val$context.handleError(var2);
      } catch (SAXException var3) {
    throw var3;
      } catch (RuntimeException var4) {
    throw var4;
      } catch (Exception var5) {
         throw SAXException2(var5);
      }
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
