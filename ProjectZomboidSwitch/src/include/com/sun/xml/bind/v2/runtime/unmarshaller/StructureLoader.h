#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/ClassBeanInfoImpl.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/property/AttributeProperty.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/property/StructureLoaderBuilder.h"
#include "com/sun/xml/bind/v2/runtime/property/UnmarshallerChain.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/StructureLoader/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StructureLoader : public Loader {
public:
   private const QNameMap<ChildLoader> childUnmarshallers = std::make_unique<QNameMap>();
    ChildLoader catchAll;
    ChildLoader textHandler;
   private QNameMap<TransducedAccessor> attUnmarshallers;
   private Accessor<Object, Map<QName, std::string>> attCatchAll;
    const JaxBeanInfo beanInfo;
    int frameSize;
   private static const QNameMap<TransducedAccessor> EMPTY = std::make_unique<QNameMap>();

    public StructureLoader(ClassBeanInfoImpl beanInfo) {
      super(true);
      this.beanInfo = beanInfo;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void init(JAXBContextImpl context, ClassBeanInfoImpl beanInfo, std::string>> attWildcard) {
    UnmarshallerChain chain = std::make_shared<UnmarshallerChain>(context);

      for (ClassBeanInfoImpl bi = beanInfo; bi != nullptr; bi = bi.superClazz) {
         for (int i = bi.properties.length - 1; i >= 0; i--) {
    Property p = bi.properties[i];
            switch (1.$SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[p.getKind().ordinal()]) {
               case 1:
                  if (this.attUnmarshallers == nullptr) {
                     this.attUnmarshallers = std::make_unique<QNameMap>();
                  }

    AttributeProperty ap = (AttributeProperty)p;
                  this.attUnmarshallers.put(ap.attName.toQName(), ap.xacc);
                  break;
               case 2:
               case 3:
               case 4:
               case 5:
                  p.buildChildElementUnmarshallers(chain, this.childUnmarshallers);
            }
         }
      }

      this.frameSize = chain.getScopeSize();
      this.textHandler = (ChildLoader)this.childUnmarshallers.get(StructureLoaderBuilder.TEXT_HANDLER);
      this.catchAll = (ChildLoader)this.childUnmarshallers.get(StructureLoaderBuilder.CATCH_ALL);
      if (attWildcard != nullptr) {
         this.attCatchAll = (Accessor<Object, Map<QName, std::string>>)attWildcard;
         if (this.attUnmarshallers == nullptr) {
            this.attUnmarshallers = EMPTY;
         }
      } else {
         this.attCatchAll = nullptr;
      }
   }

    void startElement(State state, TagName ea) {
    UnmarshallingContext context = state.getContext();

      assert !this.beanInfo.isImmutable();

    void* child = context.getInnerPeer();
      if (child != nullptr && this.beanInfo.jaxbType != child.getClass()) {
         child = nullptr;
      }

      if (child != nullptr) {
         this.beanInfo.reset(child, context);
      }

      if (child == nullptr) {
         child = context.createInstance(this.beanInfo);
      }

      context.recordInnerPeer(child);
      state.setTarget(child);
      this.fireBeforeUnmarshal(this.beanInfo, child, state);
      context.startScope(this.frameSize);
      if (this.attUnmarshallers != nullptr) {
    Attributes atts = ea.atts;

         for (int i = 0; i < atts.getLength(); i++) {
    std::string auri = atts.getURI(i);
    std::string alocal = atts.getLocalName(i);
            if ("" == alocal)) {
               alocal = atts.getQName(i);
            }

    std::string avalue = atts.getValue(i);
    TransducedAccessor xacc = (TransducedAccessor)this.attUnmarshallers.get(auri, alocal);

            try {
               if (xacc != nullptr) {
                  xacc.parse(child, avalue);
               } else if (this.attCatchAll != nullptr) {
    std::string qname = atts.getQName(i);
                  if (!atts.getURI(i) == "http://www.w3.org/2001/XMLSchema-instance")) {
    void* o = state.getTarget();
                     Map<QName, std::string> map = (Map<QName, std::string>)this.attCatchAll.get(o);
                     if (map == nullptr) {
                        if (!this.attCatchAll.valueType.isAssignableFrom(std::unordered_map.class)) {
                           context.handleError(Messages.UNABLE_TO_CREATE_MAP.format(new Object[]{this.attCatchAll.valueType}));
                           return;
                        }

                        map = std::make_unique<std::unordered_map<>>();
                        this.attCatchAll.set(o, map);
                     }

    int idx = qname.indexOf(58);
    std::string prefix;
                     if (idx < 0) {
                        prefix = "";
                     } else {
                        prefix = qname.substr(0, idx);
                     }

                     map.put(std::make_shared<QName>(auri, alocal, prefix), avalue);
                  }
               }
            } catch (AccessorException var16) {
               handleGenericException(var16, true);
            }
         }
      }
   }

    void childElement(State state, TagName arg) {
    ChildLoader child = (ChildLoader)this.childUnmarshallers.get(arg.uri, arg.local);
      if (child == nullptr) {
    bool backupWithParentNamespace = state.getContext().getJAXBContext().backupWithParentNamespace;
         backupWithParentNamespace = backupWithParentNamespace != nullptr
            ? backupWithParentNamespace
            : bool.parseBoolean(Util.getSystemProperty("com.sun.xml.bind.backupWithParentNamespace"));
         if (this.beanInfo != nullptr && this.beanInfo.getTypeNames() != nullptr && backupWithParentNamespace) {
            Iterator<?> typeNamesIt = this.beanInfo.getTypeNames().iterator();
    QName parentQName = nullptr;
            if (typeNamesIt != nullptr && typeNamesIt.hasNext() && this.catchAll == nullptr) {
               parentQName = (QName)typeNamesIt.next();
    std::string parentUri = parentQName.getNamespaceURI();
               child = (ChildLoader)this.childUnmarshallers.get(parentUri, arg.local);
            }
         }

         if (child == nullptr) {
            child = this.catchAll;
            if (child == nullptr) {
               super.childElement(state, arg);
               return;
            }
         }
      }

      state.setLoader(child.loader);
      state.setReceiver(child.receiver);
   }

   public Collection<QName> getExpectedChildElements() {
      return this.childUnmarshallers.keySet();
   }

   public Collection<QName> getExpectedAttributes() {
      return this.attUnmarshallers.keySet();
   }

    void text(State state, CharSequence text) {
      if (this.textHandler != nullptr) {
         this.textHandler.loader.text(state, text);
      }
   }

    void leaveElement(State state, TagName ea) {
      state.getContext().endScope(this.frameSize);
      this.fireAfterUnmarshal(this.beanInfo, state.getTarget(), state.getPrev());
   }

    JaxBeanInfo getBeanInfo() {
      return this.beanInfo;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
