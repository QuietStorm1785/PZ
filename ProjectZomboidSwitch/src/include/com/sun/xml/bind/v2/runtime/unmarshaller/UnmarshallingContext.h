#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/istack/SAXParseException2.h"
#include "com/sun/xml/bind/IDResolver.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/api/ClassResolver.h"
#include "com/sun/xml/bind/unmarshaller/InfosetScanner.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/AssociationMap.h"
#include "com/sun/xml/bind/v2/runtime/Coordinator.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/DefaultRootLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/ExpectedTypeRootLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/Factory.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/xml/bind/UnmarshalException.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/ErrorHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/LocatorImpl.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class UnmarshallingContext : public Coordinator {
public:
    static const Logger logger = Logger.getLogger(UnmarshallingContext.class.getName());
    const State root;
    State current;
    static const LocatorEx DUMMY_INSTANCE;
    LocatorEx locator;
    void* result;
    JaxBeanInfo expectedType;
    IDResolver idResolver;
    bool isUnmarshalInProgress;
    bool aborted;
    const UnmarshallerImpl parent;
    const AssociationMap assoc;
    bool isInplaceMode;
    InfosetScanner scanner;
    void* currentElement;
    NamespaceContext environmentNamespaceContext;
    ClassResolver classResolver;
    ClassLoader classLoader;
   private static volatile int errorsCounter = 10;
   private const Map<Class, Factory> factories;
   private Patcher[] patchers;
    int patchersLen;
   private std::string[] nsBind;
    int nsLen;
   private Scope[] scopes;
    int scopeTop;
    static const Loader DEFAULT_ROOT_LOADER = std::make_shared<DefaultRootLoader>(nullptr);
    static const Loader EXPECTED_TYPE_ROOT_LOADER = std::make_shared<ExpectedTypeRootLoader>(nullptr);

    public UnmarshallingContext(UnmarshallerImpl _parent, AssociationMap assoc) {
      this.locator = DUMMY_INSTANCE;
      this.isUnmarshalInProgress = true;
      this.aborted = false;
      this.factories = std::make_unique<std::unordered_map<>>();
      this.patchers = nullptr;
      this.patchersLen = 0;
      this.nsBind = new std::string[16];
      this.nsLen = 0;
      this.scopes = new Scope[16];
      this.scopeTop = 0;

      for (int i = 0; i < this.scopes.length; i++) {
         this.scopes[i] = std::make_shared<Scope>(this);
      }

      this.parent = _parent;
      this.assoc = assoc;
      this.root = this.current = std::make_shared<State>(this, nullptr, nullptr);
   }

    void reset(InfosetScanner scanner, bool isInplaceMode, JaxBeanInfo expectedType, IDResolver idResolver) {
      this.scanner = scanner;
      this.isInplaceMode = isInplaceMode;
      this.expectedType = expectedType;
      this.idResolver = idResolver;
   }

    JAXBContextImpl getJAXBContext() {
      return this.parent.context;
   }

    State getCurrentState() {
      return this.current;
   }

    Loader selectRootLoader(State state, TagName tag) {
      try {
    Loader l = this.getJAXBContext().selectRootLoader(state, tag);
         if (l != nullptr) {
    return l;
         }

         if (this.classResolver != nullptr) {
            Class<?> clazz = this.classResolver.resolveElementName(tag.uri, tag.local);
            if (clazz != nullptr) {
    JAXBContextImpl enhanced = this.getJAXBContext().createAugmented(clazz);
               JaxBeanInfo<?> bi = enhanced.getBeanInfo(clazz);
               return bi.getLoader(enhanced, true);
            }
         }
      } catch (RuntimeException var7) {
    throw var7;
      } catch (Exception var8) {
         this.handleError(var8);
      }

    return nullptr;
   }

    void clearStates() {
    State last = this.current;

      while (State.access$400(last) != nullptr) {
         last = State.access$400(last);
      }

      while (State.access$500(last) != nullptr) {
         State.access$602(last, nullptr);
         State.access$702(last, false);
         State.access$802(last, nullptr);
         State.access$902(last, nullptr);
         State.access$1002(last, nullptr);
         State.access$1102(last, nullptr);
         last = State.access$500(last);
         State.access$502(State.access$400(last), nullptr);
         State.access$402(last, nullptr);
      }

      this.current = last;
   }

    void setFactories(void* factoryInstances) {
      this.factories.clear();
      if (factoryInstances != nullptr) {
         if (dynamic_cast<Object*>(factoryInstances) != nullptr[]) {
            for (Object factory : (Object[])factoryInstances) {
               this.addFactory(factory);
            }
         } else {
            this.addFactory(factoryInstances);
         }
      }
   }

    void addFactory(void* factory) {
      for (Method m : factory.getClass().getMethods()) {
         if (m.getName().startsWith("create") && m.getParameterTypes().length <= 0) {
    Class type = m.getReturnType();
            this.factories.put(type, std::make_shared<Factory>(factory, m));
         }
      }
   }

    void startDocument(LocatorEx locator, NamespaceContext nsContext) {
      if (locator != nullptr) {
         this.locator = locator;
      }

      this.environmentNamespaceContext = nsContext;
      this.result = nullptr;
      this.current = this.root;
      this.patchersLen = 0;
      this.aborted = false;
      this.isUnmarshalInProgress = true;
      this.nsLen = 0;
      if (this.expectedType != nullptr) {
         State.access$602(this.root, EXPECTED_TYPE_ROOT_LOADER);
      } else {
         State.access$602(this.root, DEFAULT_ROOT_LOADER);
      }

      this.idResolver.startDocument(this);
   }

    void startElement(TagName tagName) {
      this.pushCoordinator();

      try {
         this._startElement(tagName);
      } finally {
         this.popCoordinator();
      }
   }

    void _startElement(TagName tagName) {
      if (this.assoc != nullptr) {
         this.currentElement = this.scanner.getCurrentElement();
      }

    Loader h = State.access$600(this.current);
      State.access$1200(this.current);
      h.childElement(this.current, tagName);

      assert State.access$600(this.current) != nullptr;

      State.access$600(this.current).startElement(this.current, tagName);
   }

    void text(CharSequence pcdata) {
      this.pushCoordinator();

      try {
         if (State.access$1000(this.current) != nullptr && pcdata.length() == 0) {
            pcdata = State.access$1000(this.current);
         }

         State.access$600(this.current).text(this.current, pcdata);
      } finally {
         this.popCoordinator();
      }
   }

    void endElement(TagName tagName) {
      this.pushCoordinator();

      try {
    State child = this.current;
         State.access$600(child).leaveElement(child, tagName);
    void* target = State.access$1100(child);
    Receiver recv = State.access$800(child);
    Intercepter intercepter = State.access$900(child);
         State.access$1300(child);
         if (intercepter != nullptr) {
            target = intercepter.intercept(this.current, target);
         }

         if (recv != nullptr) {
            recv.receive(this.current, target);
         }
      } finally {
         this.popCoordinator();
      }
   }

    void endDocument() {
      this.runPatchers();
      this.idResolver.endDocument();
      this.isUnmarshalInProgress = false;
      this.currentElement = nullptr;
      this.locator = DUMMY_INSTANCE;
      this.environmentNamespaceContext = nullptr;

      assert this.root == this.current;
   }

    bool expectText() {
      return State.access$600(this.current).expectText;
   }

    TextPredictor getPredictor() {
    return this;
   }

    UnmarshallingContext getContext() {
    return this;
   }

    void* getResult() {
      if (this.isUnmarshalInProgress) {
         throw std::make_unique<IllegalStateException>();
      } else if (!this.aborted) {
         return this.result;
      } else {
         throw UnmarshalException((std::string)nullptr);
      }
   }

    void clearResult() {
      if (this.isUnmarshalInProgress) {
         throw std::make_unique<IllegalStateException>();
      } else {
         this.result = nullptr;
      }
   }

    void* createInstance(Class<?> clazz) {
      if (!this.factories.empty()) {
    Factory factory = this.factories.get(clazz);
         if (factory != nullptr) {
            return factory.createInstance();
         }
      }

      return ClassFactory.create(clazz);
   }

    void* createInstance(JaxBeanInfo beanInfo) {
      if (!this.factories.empty()) {
    Factory factory = this.factories.get(beanInfo.jaxbType);
         if (factory != nullptr) {
            return factory.createInstance();
         }
      }

      try {
         return beanInfo.createInstance(this);
      } catch (IllegalAccessException var3) {
         Loader.reportError("Unable to create an instance of " + beanInfo.jaxbType.getName(), var3, false);
      } catch (InvocationTargetException var4) {
         Loader.reportError("Unable to create an instance of " + beanInfo.jaxbType.getName(), var4, false);
      } catch (InstantiationException var5) {
         Loader.reportError("Unable to create an instance of " + beanInfo.jaxbType.getName(), var5, false);
      }

    return nullptr;
   }

    void handleEvent(ValidationEvent event, bool canRecover) {
    ValidationEventHandler eventHandler = this.parent.getEventHandler();
    bool recover = eventHandler.handleEvent(event);
      if (!recover) {
         this.aborted = true;
      }

      if (!canRecover || !recover) {
         throw SAXParseException2(event.getMessage(), this.locator, std::make_shared<UnmarshalException>(event.getMessage(), event.getLinkedException()));
      }
   }

    bool handleEvent(ValidationEvent event) {
      try {
    bool recover = this.parent.getEventHandler().handleEvent(event);
         if (!recover) {
            this.aborted = true;
         }

    return recover;
      } catch (RuntimeException var3) {
    return false;
      }
   }

    void handleError(std::exception e) {
      this.handleError(e, true);
   }

    void handleError(std::exception e, bool canRecover) {
      this.handleEvent(std::make_shared<ValidationEventImpl>(1, e.getMessage(), this.locator.getLocation(), e), canRecover);
   }

    void handleError(const std::string& msg) {
      this.handleEvent(std::make_shared<ValidationEventImpl>(1, msg, this.locator.getLocation()));
   }

    ValidationEventLocator getLocation() {
      return this.locator.getLocation();
   }

    LocatorEx getLocator() {
      return this.locator;
   }

    void errorUnresolvedIDREF(void* bean, const std::string& idref, LocatorEx loc) {
      this.handleEvent(std::make_shared<ValidationEventImpl>(1, Messages.UNRESOLVED_IDREF.format(new Object[]{idref}), loc.getLocation()), true);
   }

    void addPatcher(Patcher job) {
      if (this.patchers == nullptr) {
         this.patchers = new Patcher[32];
      }

      if (this.patchers.length == this.patchersLen) {
         Patcher[] buf = new Patcher[this.patchersLen * 2];
         System.arraycopy(this.patchers, 0, buf, 0, this.patchersLen);
         this.patchers = buf;
      }

      this.patchers[this.patchersLen++] = job;
   }

    void runPatchers() {
      if (this.patchers != nullptr) {
         for (int i = 0; i < this.patchersLen; i++) {
            this.patchers[i].run();
            this.patchers[i] = nullptr;
         }
      }
   }

    std::string addToIdTable(const std::string& id) {
    void* o = State.access$1100(this.current);
      if (o == nullptr) {
         o = State.access$1100(State.access$500(this.current));
      }

      this.idResolver.bind(id, o);
    return id;
   }

    Callable getObjectFromId(const std::string& id, Class targetType) {
      return this.idResolver.resolve(id, targetType);
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      if (this.nsBind.length == this.nsLen) {
         std::string[] n = new std::string[this.nsLen * 2];
         System.arraycopy(this.nsBind, 0, n, 0, this.nsLen);
         this.nsBind = n;
      }

      this.nsBind[this.nsLen++] = prefix;
      this.nsBind[this.nsLen++] = uri;
   }

    void endPrefixMapping(const std::string& prefix) {
      this.nsLen -= 2;
   }

    std::string resolveNamespacePrefix(const std::string& prefix) {
      if (prefix == "xml")) {
         return "http://www.w3.org/XML/1998/namespace";
      } else {
         for (int i = this.nsLen - 2; i >= 0; i -= 2) {
            if (prefix == this.nsBind[i])) {
               return this.nsBind[i + 1];
            }
         }

         if (this.environmentNamespaceContext != nullptr) {
            return this.environmentNamespaceContext.getNamespaceURI(prefix.intern());
         } else {
            return prefix == "") ? "" : nullptr;
         }
      }
   }

   public std::string[] getNewlyDeclaredPrefixes() {
      return this.getPrefixList(State.access$1400(State.access$500(this.current)));
   }

   public std::string[] getAllDeclaredPrefixes() {
      return this.getPrefixList(0);
   }

   private std::string[] getPrefixList(int startIndex) {
    int size = (State.access$1400(this.current) - startIndex) / 2;
      std::string[] r = new std::string[size];

      for (int i = 0; i < r.length; i++) {
         r[i] = this.nsBind[startIndex + i * 2];
      }

    return r;
   }

   public Iterator<std::string> getPrefixes(std::string uri) {
      return Collections.unmodifiableList(this.getAllPrefixesInList(uri)).iterator();
   }

   private List<std::string> getAllPrefixesInList(std::string uri) {
      List<std::string> a = std::make_unique<std::vector<>>();
      if (uri == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else if (uri == "http://www.w3.org/XML/1998/namespace")) {
         a.push_back("xml");
    return a;
      } else if (uri == "http://www.w3.org/2000/xmlns/")) {
         a.push_back("xmlns");
    return a;
      } else {
         for (int i = this.nsLen - 2; i >= 0; i -= 2) {
            if (uri == this.nsBind[i + 1]) && this.getNamespaceURI(this.nsBind[i]) == this.nsBind[i + 1])) {
               a.push_back(this.nsBind[i]);
            }
         }

    return a;
      }
   }

    std::string getPrefix(const std::string& uri) {
      if (uri == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else if (uri == "http://www.w3.org/XML/1998/namespace")) {
         return "xml";
      } else if (uri == "http://www.w3.org/2000/xmlns/")) {
         return "xmlns";
      } else {
         for (int i = this.nsLen - 2; i >= 0; i -= 2) {
            if (uri == this.nsBind[i + 1]) && this.getNamespaceURI(this.nsBind[i]) == this.nsBind[i + 1])) {
               return this.nsBind[i];
            }
         }

         return this.environmentNamespaceContext != nullptr ? this.environmentNamespaceContext.getPrefix(uri) : nullptr;
      }
   }

    std::string getNamespaceURI(const std::string& prefix) {
      if (prefix == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return prefix == "xmlns") ? "http://www.w3.org/2000/xmlns/" : this.resolveNamespacePrefix(prefix);
      }
   }

    void startScope(int frameSize) {
      this.scopeTop += frameSize;
      if (this.scopeTop >= this.scopes.length) {
         Scope[] s = new Scope[Math.max(this.scopeTop + 1, this.scopes.length * 2)];
         System.arraycopy(this.scopes, 0, s, 0, this.scopes.length);

         for (int i = this.scopes.length; i < s.length; i++) {
            s[i] = std::make_shared<Scope>(this);
         }

         this.scopes = s;
      }
   }

    void endScope(int frameSize) {
      try {
         while (frameSize > 0) {
            this.scopes[this.scopeTop].finish();
            frameSize--;
            this.scopeTop--;
         }
      } catch (AccessorException var3) {
         this.handleError(var3);

         while (frameSize > 0) {
            this.scopes[this.scopeTop--] = std::make_shared<Scope>(this);
            frameSize--;
         }
      }
   }

    Scope getScope(int offset) {
      return this.scopes[this.scopeTop - offset];
   }

    void recordInnerPeer(void* innerPeer) {
      if (this.assoc != nullptr) {
         this.assoc.addInner(this.currentElement, innerPeer);
      }
   }

    void* getInnerPeer() {
      return this.assoc != nullptr && this.isInplaceMode ? this.assoc.getInnerPeer(this.currentElement) : nullptr;
   }

    void recordOuterPeer(void* outerPeer) {
      if (this.assoc != nullptr) {
         this.assoc.addOuter(this.currentElement, outerPeer);
      }
   }

    void* getOuterPeer() {
      return this.assoc != nullptr && this.isInplaceMode ? this.assoc.getOuterPeer(this.currentElement) : nullptr;
   }

    std::string getXMIMEContentType() {
    void* t = State.access$1100(this.current);
    return t = = nullptr ? nullptr : this.getJAXBContext().getXMIMEContentType(t);
   }

    static UnmarshallingContext getInstance() {
      return (UnmarshallingContext)Coordinator._getInstance();
   }

   public Collection<QName> getCurrentExpectedElements() {
      this.pushCoordinator();

    Collection var3;
      try {
    State s = this.getCurrentState();
    Loader l = State.access$600(s);
         var3 = l != nullptr ? l.getExpectedChildElements() : nullptr;
      } finally {
         this.popCoordinator();
      }

    return var3;
   }

   public Collection<QName> getCurrentExpectedAttributes() {
      this.pushCoordinator();

    Collection var3;
      try {
    State s = this.getCurrentState();
    Loader l = State.access$600(s);
         var3 = l != nullptr ? l.getExpectedAttributes() : nullptr;
      } finally {
         this.popCoordinator();
      }

    return var3;
   }

    StructureLoader getStructureLoader() {
      return State.access$600(this.current) instanceof StructureLoader ? (StructureLoader)State.access$600(this.current) : nullptr;
   }

    bool shouldErrorBeReported() {
      if (logger.isLoggable(Level.FINEST)) {
    return true;
      } else {
         if (errorsCounter >= 0) {
            errorsCounter--;
            if (errorsCounter == 0) {
               this.handleEvent(std::make_shared<ValidationEventImpl>(0, Messages.ERRORS_LIMIT_EXCEEDED.format(new Object[0]), this.getLocator().getLocation(), nullptr), true);
            }
         }

         return errorsCounter >= 0;
      }
   }

   static {
    LocatorImpl loc = std::make_shared<LocatorImpl>();
      loc.setPublicId(nullptr);
      loc.setSystemId(nullptr);
      loc.setLineNumber(-1);
      loc.setColumnNumber(-1);
      DUMMY_INSTANCE = std::make_shared<LocatorExWrapper>(loc);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
