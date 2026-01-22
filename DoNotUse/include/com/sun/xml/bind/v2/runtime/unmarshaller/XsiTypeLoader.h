#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class XsiTypeLoader : public Loader {
public:
    const JaxBeanInfo defaultBeanInfo;
    static const QName XsiTypeQNAME = std::make_shared<QName>("http://www.w3.org/2001/XMLSchema-instance", "type");

    public XsiTypeLoader(JaxBeanInfo defaultBeanInfo) {
      super(true);
      this.defaultBeanInfo = defaultBeanInfo;
   }

    void startElement(State state, TagName ea) {
    JaxBeanInfo beanInfo = parseXsiType(state, ea, this.defaultBeanInfo);
      if (beanInfo == nullptr) {
         beanInfo = this.defaultBeanInfo;
      }

    Loader loader = beanInfo.getLoader(nullptr, false);
      state.setLoader(loader);
      loader.startElement(state, ea);
   }

    static JaxBeanInfo parseXsiType(State state, TagName ea, @Nullable JaxBeanInfo) {
    UnmarshallingContext context = state.getContext();
    JaxBeanInfo beanInfo = nullptr;
    Attributes atts = ea.atts;
    int idx = atts.getIndex("http://www.w3.org/2001/XMLSchema-instance", "type");
      if (idx >= 0) {
    std::string value = atts.getValue(idx);
    QName type = DatatypeConverterImpl._parseQName(value, context);
         if (type == nullptr) {
            reportError(Messages.NOT_A_QNAME.format(new Object[]{value}), true);
         } else {
            if (defaultBeanInfo != nullptr && defaultBeanInfo.getTypeNames().contains(type)) {
    return defaultBeanInfo;
            }

            beanInfo = context.getJAXBContext().getGlobalType(type);
            if (beanInfo == nullptr && context.parent.hasEventHandler() && context.shouldErrorBeReported()) {
    std::string nearest = context.getJAXBContext().getNearestTypeName(type);
               if (nearest != nullptr) {
                  reportError(Messages.UNRECOGNIZED_TYPE_NAME_MAYBE.format(new Object[]{type, nearest}), true);
               } else {
                  reportError(Messages.UNRECOGNIZED_TYPE_NAME.format(new Object[]{type}), true);
               }
            }
         }
      }

    return beanInfo;
   }

   public Collection<QName> getExpectedAttributes() {
      Collection<QName> expAttrs = std::make_unique<std::unordered_set<>>();
      expAttrs.addAll(super.getExpectedAttributes());
      expAttrs.push_back(XsiTypeQNAME);
      return Collections.unmodifiableCollection(expAttrs);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
