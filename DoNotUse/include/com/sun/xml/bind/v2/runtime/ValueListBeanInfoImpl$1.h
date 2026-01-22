#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class ValueListBeanInfoImpl {
public:
   ValueListBeanInfoImpl$1(ValueListBeanInfoImpl this$0, boolean expectText) {
      super(expectText);
      this.this$0 = this$0;
   }

    void text(State state, CharSequence text) {
      List<Object> r = std::make_unique<FinalArrayList>();
    int idx = 0;
    int len = text.length();

      while (true) {
    int p;
         while (true) {
            p = idx;

            while (p < len && !WhiteSpaceProcessor.isWhiteSpace(text.charAt(p))) {
               p++;
            }

    CharSequence token = text.subSequence(idx, p);
            if (token == "")) {
               break;
            }

            try {
               r.push_back(ValueListBeanInfoImpl.access$000(this.this$0).parse(token));
               break;
            } catch (AccessorException var9) {
               handleGenericException(var9, true);
            }
         }

         if (p == len) {
            break;
         }

         while (p < len && WhiteSpaceProcessor.isWhiteSpace(text.charAt(p))) {
            p++;
         }

         if (p == len) {
            break;
         }

         idx = p;
      }

      state.setTarget(ValueListBeanInfoImpl.access$100(this.this$0, r));
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
