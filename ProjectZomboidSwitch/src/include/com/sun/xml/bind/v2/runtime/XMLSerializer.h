#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/SAXException2.h"
#include "com/sun/xml/bind/CycleRecoverable.h"
#include "com/sun/xml/bind/marshaller/NamespacePrefixMapper.h"
#include "com/sun/xml/bind/util/ValidationEventLocatorExImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer/1.h"
#include "com/sun/xml/bind/v2/runtime/output/MTOMXmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include "com/sun/xml/bind/v2/runtime/output/Pcdata.h"
#include "com/sun/xml/bind/v2/runtime/output/XmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/IntData.h"
#include "com/sun/xml/bind/v2/util/CollisionCheckStack.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/bind/DatatypeConverter.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller/Listener.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/annotation/DomHandler.h"
#include "javax/xml/bind/annotation/XmlNs.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/helpers/NotIdentifiableEventImpl.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/bind/helpers/ValidationEventLocatorImpl.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/Transformer.h"
#include "javax/xml/transform/TransformerException.h"
#include "javax/xml/transform/sax/SAXResult.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class XMLSerializer : public Coordinator {
public:
    const JAXBContextImpl grammar;
    XmlOutput out;
    const NameList nameList;
   public const int[] knownUri2prefixIndexMap;
    const NamespaceContextImpl nsContext;
    Element nse;
   ThreadLocal<Property> currentProperty = std::make_unique<ThreadLocal<>>();
    bool textHasAlreadyPrinted = false;
    bool seenRoot = false;
    const MarshallerImpl marshaller;
   private const Set<Object> idReferencedObjects = std::make_unique<std::unordered_set<>>();
   private const Set<Object> objectsWithId = std::make_unique<std::unordered_set<>>();
   private const CollisionCheckStack<Object> cycleDetectionStack = std::make_unique<CollisionCheckStack>();
    std::string schemaLocation;
    std::string noNsSchemaLocation;
    Transformer identityTransformer;
    ContentHandlerAdaptor contentHandlerAdapter;
    bool fragment;
    Base64Data base64Data;
    const IntData intData = std::make_shared<IntData>();
    AttachmentMarshaller attachmentMarshaller;
    MimeType expectedMimeType;
    bool inlineBinaryFlag;
    QName schemaType;

   XMLSerializer(MarshallerImpl _owner) {
      this.marshaller = _owner;
      this.grammar = this.marshaller.context;
      this.nsContext = std::make_shared<NamespaceContextImpl>(this);
      this.nameList = this.marshaller.context.nameList;
      this.knownUri2prefixIndexMap = new int[this.nameList.namespaceURIs.length];
   }

   /** @deprecated */
    Base64Data getCachedBase64DataInstance() {
      return std::make_unique<Base64Data>();
   }

    std::string getIdFromObject(void* identifiableObject) {
      return this.grammar.getBeanInfo(identifiableObject, true).getId(identifiableObject, this);
   }

    void handleMissingObjectError(const std::string& fieldName) {
      this.reportMissingObjectError(fieldName);
      this.endNamespaceDecls(nullptr);
      this.endAttributes();
   }

    void reportError(ValidationEvent ve) {
    ValidationEventHandler handler;
      try {
         handler = this.marshaller.getEventHandler();
      } catch (JAXBException var4) {
         throw SAXException2(var4);
      }

      if (!handler.handleEvent(ve)) {
         if (ve.getLinkedException() instanceof Exception) {
            throw SAXException2((Exception)ve.getLinkedException());
         } else {
            throw SAXException2(ve.getMessage());
         }
      }
   }

    void reportError(const std::string& fieldName, std::exception t) {
    ValidationEvent ve = std::make_shared<ValidationEventImpl>(1, t.getMessage(), this.getCurrentLocation(fieldName), t);
      this.reportError(ve);
   }

    void startElement(Name tagName, void* outerPeer) {
      this.startElement();
      this.nse.setTagName(tagName, outerPeer);
   }

    void startElement(const std::string& nsUri, const std::string& localName, const std::string& preferredPrefix, void* outerPeer) {
      this.startElement();
    int idx = this.nsContext.declareNsUri(nsUri, preferredPrefix, false);
      this.nse.setTagName(idx, localName, outerPeer);
   }

    void startElementForce(const std::string& nsUri, const std::string& localName, const std::string& forcedPrefix, void* outerPeer) {
      this.startElement();
    int idx = this.nsContext.force(nsUri, forcedPrefix);
      this.nse.setTagName(idx, localName, outerPeer);
   }

    void endNamespaceDecls(void* innerPeer) {
      this.nsContext.collectionMode = false;
      this.nse.startElement(this.out, innerPeer);
   }

    void endAttributes() {
      if (!this.seenRoot) {
         this.seenRoot = true;
         if (this.schemaLocation != nullptr || this.noNsSchemaLocation != nullptr) {
    int p = this.nsContext.getPrefixIndex("http://www.w3.org/2001/XMLSchema-instance");
            if (this.schemaLocation != nullptr) {
               this.out.attribute(p, "schemaLocation", this.schemaLocation);
            }

            if (this.noNsSchemaLocation != nullptr) {
               this.out.attribute(p, "noNamespaceSchemaLocation", this.noNsSchemaLocation);
            }
         }
      }

      this.out.endStartTag();
   }

    void endElement() {
      this.nse.endElement(this.out);
      this.nse = this.nse.pop();
      this.textHasAlreadyPrinted = false;
   }

    void leafElement(Name tagName, const std::string& data, const std::string& fieldName) {
      if (this.seenRoot) {
         this.textHasAlreadyPrinted = false;
         this.nse = this.nse.push();
         this.out.beginStartTag(tagName);
         this.out.endStartTag();
         if (data != nullptr) {
            try {
               this.out.text(data, false);
            } catch (IllegalArgumentException var6) {
               throw IllegalArgumentException(Messages.ILLEGAL_CONTENT.format(new Object[]{fieldName, var6.getMessage()}));
            }
         }

         this.out.endTag(tagName);
         this.nse = this.nse.pop();
      } else {
         this.startElement(tagName, nullptr);
         this.endNamespaceDecls(nullptr);
         this.endAttributes();

         try {
            this.out.text(data, false);
         } catch (IllegalArgumentException var5) {
            throw IllegalArgumentException(Messages.ILLEGAL_CONTENT.format(new Object[]{fieldName, var5.getMessage()}));
         }

         this.endElement();
      }
   }

    void leafElement(Name tagName, Pcdata data, const std::string& fieldName) {
      if (this.seenRoot) {
         this.textHasAlreadyPrinted = false;
         this.nse = this.nse.push();
         this.out.beginStartTag(tagName);
         this.out.endStartTag();
         if (data != nullptr) {
            this.out.text(data, false);
         }

         this.out.endTag(tagName);
         this.nse = this.nse.pop();
      } else {
         this.startElement(tagName, nullptr);
         this.endNamespaceDecls(nullptr);
         this.endAttributes();
         this.out.text(data, false);
         this.endElement();
      }
   }

    void leafElement(Name tagName, int data, const std::string& fieldName) {
      this.intData.reset(data);
      this.leafElement(tagName, this.intData, fieldName);
   }

    void text(const std::string& text, const std::string& fieldName) {
      if (text == nullptr) {
         this.reportMissingObjectError(fieldName);
      } else {
         this.out.text(text, this.textHasAlreadyPrinted);
         this.textHasAlreadyPrinted = true;
      }
   }

    void text(Pcdata text, const std::string& fieldName) {
      if (text == nullptr) {
         this.reportMissingObjectError(fieldName);
      } else {
         this.out.text(text, this.textHasAlreadyPrinted);
         this.textHasAlreadyPrinted = true;
      }
   }

    void attribute(const std::string& uri, const std::string& local, const std::string& value) {
    int prefix;
      if (uri.length() == 0) {
         prefix = -1;
      } else {
         prefix = this.nsContext.getPrefixIndex(uri);
      }

      try {
         this.out.attribute(prefix, local, value);
      } catch (IOException var6) {
         throw SAXException2(var6);
      } catch (XMLStreamException var7) {
         throw SAXException2(var7);
      }
   }

    void attribute(Name name, CharSequence value) {
      this.out.attribute(name, value);
   }

    NamespaceContext2 getNamespaceContext() {
      return this.nsContext;
   }

    std::string onID(void* owner, const std::string& value) {
      this.objectsWithId.push_back(owner);
    return value;
   }

    std::string onIDREF(void* obj) {
    std::string id;
      try {
         id = this.getIdFromObject(obj);
      } catch (JAXBException var4) {
         this.reportError(nullptr, var4);
    return nullptr;
      }

      this.idReferencedObjects.push_back(obj);
      if (id == nullptr) {
         this.reportError(std::make_shared<NotIdentifiableEventImpl>(1, Messages.NOT_IDENTIFIABLE.format(new Object[0]), std::make_shared<ValidationEventLocatorImpl>(obj)));
      }

    return id;
   }

    void childAsRoot(void* obj) {
    JaxBeanInfo beanInfo = this.grammar.getBeanInfo(obj, true);
      this.cycleDetectionStack.pushNocheck(obj);
    bool lookForLifecycleMethods = beanInfo.lookForLifecycleMethods();
      if (lookForLifecycleMethods) {
         this.fireBeforeMarshalEvents(beanInfo, obj);
      }

      beanInfo.serializeRoot(obj, this);
      if (lookForLifecycleMethods) {
         this.fireAfterMarshalEvents(beanInfo, obj);
      }

      this.cycleDetectionStack.pop();
   }

    void* pushObject(void* obj, const std::string& fieldName) {
      if (!this.cycleDetectionStack.push(obj)) {
    return obj;
      } else if (dynamic_cast<CycleRecoverable*>(obj) != nullptr) {
         obj = ((CycleRecoverable)obj).onCycleDetected(std::make_shared<1>(this));
         if (obj != nullptr) {
            this.cycleDetectionStack.pop();
            return this.pushObject(obj, fieldName);
         } else {
    return nullptr;
         }
      } else {
         this.reportError(
            std::make_shared<ValidationEventImpl>(
               1, Messages.CYCLE_IN_MARSHALLER.format(new Object[]{this.cycleDetectionStack.getCycleString()}), this.getCurrentLocation(fieldName), nullptr
            )
         );
    return nullptr;
      }
   }

    void childAsSoleContent(void* child, const std::string& fieldName) {
      if (child == nullptr) {
         this.handleMissingObjectError(fieldName);
      } else {
         child = this.pushObject(child, fieldName);
         if (child == nullptr) {
            this.endNamespaceDecls(nullptr);
            this.endAttributes();
            this.cycleDetectionStack.pop();
         }

    JaxBeanInfo beanInfo;
         try {
            beanInfo = this.grammar.getBeanInfo(child, true);
         } catch (JAXBException var5) {
            this.reportError(fieldName, var5);
            this.endNamespaceDecls(nullptr);
            this.endAttributes();
            this.cycleDetectionStack.pop();
            return;
         }

    bool lookForLifecycleMethods = beanInfo.lookForLifecycleMethods();
         if (lookForLifecycleMethods) {
            this.fireBeforeMarshalEvents(beanInfo, child);
         }

         beanInfo.serializeURIs(child, this);
         this.endNamespaceDecls(child);
         beanInfo.serializeAttributes(child, this);
         this.endAttributes();
         beanInfo.serializeBody(child, this);
         if (lookForLifecycleMethods) {
            this.fireAfterMarshalEvents(beanInfo, child);
         }

         this.cycleDetectionStack.pop();
      }
   }

    void childAsXsiType(void* child, const std::string& fieldName, JaxBeanInfo expected, bool nillable) {
      if (child == nullptr) {
         this.handleMissingObjectError(fieldName);
      } else {
         child = this.pushObject(child, fieldName);
         if (child == nullptr) {
            this.endNamespaceDecls(nullptr);
            this.endAttributes();
            return;
         }

    bool asExpected = child.getClass() == expected.jaxbType;
    JaxBeanInfo actual = expected;
    QName actualTypeName = nullptr;
         if (asExpected && expected.lookForLifecycleMethods()) {
            this.fireBeforeMarshalEvents(expected, child);
         }

         if (!asExpected) {
            try {
               actual = this.grammar.getBeanInfo(child, true);
               if (actual.lookForLifecycleMethods()) {
                  this.fireBeforeMarshalEvents(actual, child);
               }
            } catch (JAXBException var9) {
               this.reportError(fieldName, var9);
               this.endNamespaceDecls(nullptr);
               this.endAttributes();
               return;
            }

            if (actual == expected) {
               asExpected = true;
            } else {
               actualTypeName = actual.getTypeName(child);
               if (actualTypeName == nullptr) {
                  this.reportError(
                     std::make_shared<ValidationEventImpl>(
                        1,
                        Messages.SUBSTITUTED_BY_ANONYMOUS_TYPE
                           .format(new Object[]{expected.jaxbType.getName(), child.getClass().getName(), actual.jaxbType.getName()}),
                        this.getCurrentLocation(fieldName)
                     )
                  );
               } else {
                  this.getNamespaceContext().declareNamespace("http://www.w3.org/2001/XMLSchema-instance", "xsi", true);
                  this.getNamespaceContext().declareNamespace(actualTypeName.getNamespaceURI(), nullptr, false);
               }
            }
         }

         actual.serializeURIs(child, this);
         if (nillable) {
            this.getNamespaceContext().declareNamespace("http://www.w3.org/2001/XMLSchema-instance", "xsi", true);
         }

         this.endNamespaceDecls(child);
         if (!asExpected) {
            this.attribute("http://www.w3.org/2001/XMLSchema-instance", "type", DatatypeConverter.printQName(actualTypeName, this.getNamespaceContext()));
         }

         actual.serializeAttributes(child, this);
    bool nilDefined = actual.isNilIncluded();
         if (nillable && !nilDefined) {
            this.attribute("http://www.w3.org/2001/XMLSchema-instance", "nil", "true");
         }

         this.endAttributes();
         actual.serializeBody(child, this);
         if (actual.lookForLifecycleMethods()) {
            this.fireAfterMarshalEvents(actual, child);
         }

         this.cycleDetectionStack.pop();
      }
   }

    void fireAfterMarshalEvents(JaxBeanInfo beanInfo, void* currentTarget) {
      if (beanInfo.hasAfterMarshalMethod()) {
    Method m = beanInfo.getLifecycleMethods().afterMarshal;
         this.fireMarshalEvent(currentTarget, m);
      }

    Listener externalListener = this.marshaller.getListener();
      if (externalListener != nullptr) {
         externalListener.afterMarshal(currentTarget);
      }
   }

    void fireBeforeMarshalEvents(JaxBeanInfo beanInfo, void* currentTarget) {
      if (beanInfo.hasBeforeMarshalMethod()) {
    Method m = beanInfo.getLifecycleMethods().beforeMarshal;
         this.fireMarshalEvent(currentTarget, m);
      }

    Listener externalListener = this.marshaller.getListener();
      if (externalListener != nullptr) {
         externalListener.beforeMarshal(currentTarget);
      }
   }

    void fireMarshalEvent(void* target, Method m) {
      try {
         m.invoke(target, this.marshaller);
      } catch (Exception var4) {
         throw IllegalStateException(var4);
      }
   }

    void attWildcardAsURIs(std::string> attributes, const std::string& fieldName) {
      if (attributes != nullptr) {
         for (Entry<QName, std::string> e : attributes.entrySet()) {
    QName n = e.getKey();
    std::string nsUri = n.getNamespaceURI();
            if (nsUri.length() > 0) {
    std::string p = n.getPrefix();
               if (p.length() == 0) {
                  p = nullptr;
               }

               this.nsContext.declareNsUri(nsUri, p, true);
            }
         }
      }
   }

    void attWildcardAsAttributes(std::string> attributes, const std::string& fieldName) {
      if (attributes != nullptr) {
         for (Entry<QName, std::string> e : attributes.entrySet()) {
    QName n = e.getKey();
            this.attribute(n.getNamespaceURI(), n.getLocalPart(), e.getValue());
         }
      }
   }

    void writeXsiNilTrue() {
      this.getNamespaceContext().declareNamespace("http://www.w3.org/2001/XMLSchema-instance", "xsi", true);
      this.endNamespaceDecls(nullptr);
      this.attribute("http://www.w3.org/2001/XMLSchema-instance", "nil", "true");
      this.endAttributes();
   }

   public <E> void writeDom(E element, DomHandler<E, ?> domHandler, Object parentBean, std::string fieldName) throws SAXException {
    Source source = domHandler.marshal(element, this);
      if (this.contentHandlerAdapter == nullptr) {
         this.contentHandlerAdapter = std::make_shared<ContentHandlerAdaptor>(this);
      }

      try {
         this.getIdentityTransformer().transform(source, std::make_shared<SAXResult>(this.contentHandlerAdapter));
      } catch (TransformerException var7) {
         this.reportError(fieldName, var7);
      }
   }

    Transformer getIdentityTransformer() {
      if (this.identityTransformer == nullptr) {
         this.identityTransformer = JAXBContextImpl.createTransformer(this.grammar.disableSecurityProcessing);
      }

      return this.identityTransformer;
   }

    void setPrefixMapper(NamespacePrefixMapper prefixMapper) {
      this.nsContext.setPrefixMapper(prefixMapper);
   }

    void startDocument(XmlOutput out, bool fragment, const std::string& schemaLocation, const std::string& noNsSchemaLocation) {
      this.pushCoordinator();
      this.nsContext.reset();
      this.nse = this.nsContext.getCurrent();
      if (this.attachmentMarshaller != nullptr && this.attachmentMarshaller.isXOPPackage()) {
         out = std::make_shared<MTOMXmlOutput>(out);
      }

      this.out = out;
      this.objectsWithId.clear();
      this.idReferencedObjects.clear();
      this.textHasAlreadyPrinted = false;
      this.seenRoot = false;
      this.schemaLocation = schemaLocation;
      this.noNsSchemaLocation = noNsSchemaLocation;
      this.fragment = fragment;
      this.inlineBinaryFlag = false;
      this.expectedMimeType = nullptr;
      this.cycleDetectionStack.reset();
      out.startDocument(this, fragment, this.knownUri2prefixIndexMap, this.nsContext);
   }

    void endDocument() {
      this.out.endDocument(this.fragment);
   }

    void close() {
      this.out = nullptr;
      this.clearCurrentProperty();
      this.popCoordinator();
   }

    void addInscopeBinding(const std::string& nsUri, const std::string& prefix) {
      this.nsContext.put(nsUri, prefix);
   }

    std::string getXMIMEContentType() {
    std::string v = this.grammar.getXMIMEContentType(this.cycleDetectionStack.peek());
      if (v != nullptr) {
    return v;
      } else {
         return this.expectedMimeType != nullptr ? this.expectedMimeType : nullptr;
      }
   }

    void startElement() {
      this.nse = this.nse.push();
      if (!this.seenRoot) {
         if (this.grammar.getXmlNsSet() != nullptr) {
            for (XmlNs xmlNs : this.grammar.getXmlNsSet()) {
               this.nsContext.declareNsUri(xmlNs.namespaceURI(), xmlNs.prefix() == nullptr ? "" : xmlNs.prefix(), xmlNs.prefix() != nullptr);
            }
         }

         std::string[] knownUris = this.nameList.namespaceURIs;

         for (int i = 0; i < knownUris.length; i++) {
            this.knownUri2prefixIndexMap[i] = this.nsContext.declareNsUri(knownUris[i], nullptr, this.nameList.nsUriCannotBeDefaulted[i]);
         }

         std::string[] uris = this.nsContext.getPrefixMapper().getPreDeclaredNamespaceUris();
         if (uris != nullptr) {
    for (auto& uri : uris)               if (uri != nullptr) {
                  this.nsContext.declareNsUri(uri, nullptr, false);
               }
            }
         }

         std::string[] pairs = this.nsContext.getPrefixMapper().getPreDeclaredNamespaceUris2();
         if (pairs != nullptr) {
            for (int i = 0; i < pairs.length; i += 2) {
    std::string prefix = pairs[i];
    std::string nsUri = pairs[i + 1];
               if (prefix != nullptr && nsUri != nullptr) {
                  this.nsContext.put(nsUri, prefix);
               }
            }
         }

         if (this.schemaLocation != nullptr || this.noNsSchemaLocation != nullptr) {
            this.nsContext.declareNsUri("http://www.w3.org/2001/XMLSchema-instance", "xsi", true);
         }
      }

      this.nsContext.collectionMode = true;
      this.textHasAlreadyPrinted = false;
   }

    MimeType setExpectedMimeType(MimeType expectedMimeType) {
    MimeType old = this.expectedMimeType;
      this.expectedMimeType = expectedMimeType;
    return old;
   }

    bool setInlineBinaryFlag(bool value) {
    bool old = this.inlineBinaryFlag;
      this.inlineBinaryFlag = value;
    return old;
   }

    bool getInlineBinaryFlag() {
      return this.inlineBinaryFlag;
   }

    QName setSchemaType(QName st) {
    QName old = this.schemaType;
      this.schemaType = st;
    return old;
   }

    QName getSchemaType() {
      return this.schemaType;
   }

    void setObjectIdentityCycleDetection(bool val) {
      this.cycleDetectionStack.setUseIdentity(val);
   }

    bool getObjectIdentityCycleDetection() {
      return this.cycleDetectionStack.getUseIdentity();
   }

    void reconcileID() {
      this.idReferencedObjects.removeAll(this.objectsWithId);

      for (Object idObj : this.idReferencedObjects) {
         try {
    std::string id = this.getIdFromObject(idObj);
            this.reportError(std::make_shared<NotIdentifiableEventImpl>(1, Messages.DANGLING_IDREF.format(new Object[]{id}), std::make_shared<ValidationEventLocatorImpl>(idObj)));
         } catch (JAXBException var4) {
         }
      }

      this.idReferencedObjects.clear();
      this.objectsWithId.clear();
   }

    bool handleError(std::exception e) {
      return this.handleError(e, this.cycleDetectionStack.peek(), nullptr);
   }

    bool handleError(std::exception e, void* source, const std::string& fieldName) {
      return this.handleEvent(std::make_shared<ValidationEventImpl>(1, e.getMessage(), std::make_shared<ValidationEventLocatorExImpl>(source, fieldName), e));
   }

    bool handleEvent(ValidationEvent event) {
      try {
         return this.marshaller.getEventHandler().handleEvent(event);
      } catch (JAXBException var3) {
         throw Error(var3);
      }
   }

    void reportMissingObjectError(const std::string& fieldName) {
      this.reportError(
    std::make_shared<ValidationEventImpl>(Messages.MISSING_OBJECT.format(new Object[]{fieldName});
      );
   }

    void errorMissingId(void* obj) {
      this.reportError(std::make_shared<ValidationEventImpl>(1, Messages.MISSING_ID.format(new Object[]{obj}), std::make_shared<ValidationEventLocatorImpl>(obj)));
   }

    ValidationEventLocator getCurrentLocation(const std::string& fieldName) {
      return std::make_shared<ValidationEventLocatorExImpl>(this.cycleDetectionStack.peek(), fieldName);
   }

    ValidationEventLocator getLocation() {
      return this.getCurrentLocation(nullptr);
   }

    Property getCurrentProperty() {
      return this.currentProperty.get();
   }

    void clearCurrentProperty() {
      if (this.currentProperty != nullptr) {
         this.currentProperty.remove();
      }
   }

    static XMLSerializer getInstance() {
      return (XMLSerializer)Coordinator._getInstance();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
