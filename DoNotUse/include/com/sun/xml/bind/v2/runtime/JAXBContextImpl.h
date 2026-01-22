#pragma once
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Pool.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/api/Bridge.h"
#include "com/sun/xml/bind/api/BridgeContext.h"
#include "com/sun/xml/bind/api/CompositeStructure.h"
#include "com/sun/xml/bind/api/JAXBRIContext.h"
#include "com/sun/xml/bind/api/RawAccessor.h"
#include "com/sun/xml/bind/api/TypeReference.h"
#include "com/sun/xml/bind/unmarshaller/DOMScanner.h"
#include "com/sun/xml/bind/util/Which.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeAnnotationReader.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/Ref.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeModelBuilder.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeArrayInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeBuiltinLeafInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeClassInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeEnumLeafInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeLeafInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfoSet.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationsException/Builder.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/2.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/3.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/4.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/5.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/6.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/JAXBContextBuilder.h"
#include "com/sun/xml/bind/v2/runtime/output/Encoded.h"
#include "com/sun/xml/bind/v2/runtime/property/AttributeProperty.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TagName.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator.h"
#include "com/sun/xml/bind/v2/util/EditDistance.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "com/sun/xml/bind/v2/util/XmlFactory.h"
#include "com/sun/xml/txw2/output/ResultFactory.h"
#include "javax/xml/bind/Binder.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/JAXBIntrospector.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/SchemaOutputResolver.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/Validator.h"
#include "javax/xml/bind/annotation/XmlAttachmentRef.h"
#include "javax/xml/bind/annotation/XmlList.h"
#include "javax/xml/bind/annotation/XmlNs.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/FactoryConfigurationError.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/Transformer.h"
#include "javax/xml/transform/TransformerConfigurationException.h"
#include "javax/xml/transform/sax/SAXTransformerFactory.h"
#include "javax/xml/transform/sax/TransformerHandler.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/SAXParseException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl : public JAXBRIContext {
public:
   private const Map<TypeReference, Bridge> bridges = std::make_unique<LinkedHashMap<>>();
    static DocumentBuilder db;
   private const QNameMap<JaxBeanInfo> rootMap = std::make_unique<QNameMap>();
   private const std::unordered_map<QName, JaxBeanInfo> typeMap = std::make_unique<std::unordered_map<>>();
   private const Map<Class, JaxBeanInfo> beanInfoMap = std::make_unique<LinkedHashMap<>>();
   protected Map<RuntimeTypeInfo, JaxBeanInfo> beanInfos = std::make_unique<LinkedHashMap<>>();
   private const Map<Class, Map<QName, ElementBeanInfoImpl>> elements = std::make_unique<LinkedHashMap<>>();
   public const Pool<Marshaller> marshallerPool = std::make_shared<1>(this);
   public const Pool<Unmarshaller> unmarshallerPool = std::make_shared<2>(this);
    NameBuilder nameBuilder = std::make_shared<NameBuilder>();
    const NameList nameList;
    const std::string defaultNsUri;
   private const Class[] classes;
    const bool c14nSupport;
    const bool xmlAccessorFactorySupport;
    const bool allNillable;
    const bool retainPropertyInfo;
    const bool supressAccessorWarnings;
    const bool improvedXsiTypeHandling;
    const bool disableSecurityProcessing;
   private WeakReference<RuntimeTypeInfoSet> typeInfoSetCache;
    RuntimeAnnotationReader annotationReader;
    bool hasSwaRef;
   private const Map<Class, Class> subclassReplacements;
    const bool fastBoot;
   private Set<XmlNs> xmlNsSet = nullptr;
    bool backupWithParentNamespace = nullptr;
   private Encoded[] utf8nameTable;
   private static const Comparator<QName> QNAME_COMPARATOR = std::make_unique<6>();

   public Set<XmlNs> getXmlNsSet() {
      return this.xmlNsSet;
   }

    private JAXBContextImpl(JAXBContextBuilder builder) {
      this.defaultNsUri = JAXBContextBuilder.access$000(builder);
      this.retainPropertyInfo = JAXBContextBuilder.access$100(builder);
      this.annotationReader = JAXBContextBuilder.access$200(builder);
      this.subclassReplacements = JAXBContextBuilder.access$300(builder);
      this.c14nSupport = JAXBContextBuilder.access$400(builder);
      this.classes = JAXBContextBuilder.access$500(builder);
      this.xmlAccessorFactorySupport = JAXBContextBuilder.access$600(builder);
      this.allNillable = JAXBContextBuilder.access$700(builder);
      this.supressAccessorWarnings = JAXBContextBuilder.access$800(builder);
      this.improvedXsiTypeHandling = JAXBContextBuilder.access$900(builder);
      this.disableSecurityProcessing = JAXBContextBuilder.access$1000(builder);
      this.backupWithParentNamespace = JAXBContextBuilder.access$1100(builder);
      Collection<TypeReference> typeRefs = JAXBContextBuilder.access$1200(builder);

    bool fastB;
      try {
         fastB = bool.getBoolean(JAXBContextImpl.class.getName() + ".fastBoot");
      } catch (SecurityException var14) {
         fastB = false;
      }

      this.fastBoot = fastB;
    RuntimeTypeInfoSet typeSet = this.getTypeInfoSet();
      this.elements.put(nullptr, std::make_unique<LinkedHashMap<>>());

      for (RuntimeBuiltinLeafInfo leaf : RuntimeBuiltinLeafInfoImpl.builtinBeanInfos) {
         LeafBeanInfoImpl<?> bi = std::make_shared<LeafBeanInfoImpl>(this, leaf);
         this.beanInfoMap.put(leaf.getClazz(), bi);

         for (QName t : bi.getTypeNames()) {
            this.typeMap.put(t, bi);
         }
      }

      for (RuntimeEnumLeafInfo e : typeSet.enums().values()) {
         JaxBeanInfo<?> bi = this.getOrCreate(e);

         for (QName qn : bi.getTypeNames()) {
            this.typeMap.put(qn, bi);
         }

         if (e.isElement()) {
            this.rootMap.put(e.getElementName(), bi);
         }
      }

      for (RuntimeArrayInfo a : typeSet.arrays().values()) {
         JaxBeanInfo<?> ai = this.getOrCreate(a);

         for (QName qn : ai.getTypeNames()) {
            this.typeMap.put(qn, ai);
         }
      }

      for (Entry<Class, ? : public RuntimeClassInfo> e : typeSet.beans().entrySet()) {
         ClassBeanInfoImpl<?> bi = this.getOrCreate(e.getValue());
    XmlSchema xs = (XmlSchema)this.annotationReader.getPackageAnnotation(XmlSchema.class, e.getKey(), nullptr);
         if (xs != nullptr && xs.xmlns() != nullptr && xs.xmlns().length > 0) {
            if (this.xmlNsSet == nullptr) {
               this.xmlNsSet = std::make_unique<std::unordered_set<>>();
            }

            this.xmlNsSet.addAll(Arrays.asList(xs.xmlns()));
         }

         if (bi.isElement()) {
            this.rootMap.put(e.getValue().getElementName(), bi);
         }

         for (QName qn : bi.getTypeNames()) {
            this.typeMap.put(qn, bi);
         }
      }

      for (RuntimeElementInfo n : typeSet.getAllElements()) {
    ElementBeanInfoImpl bix = this.getOrCreate(n);
         if (n.getScope() == nullptr) {
            this.rootMap.put(n.getElementName(), bix);
         }

    RuntimeClassInfo scope = n.getScope();
    Class scopeClazz = scope == nullptr ? nullptr : (Class)scope.getClazz();
         Map<QName, ElementBeanInfoImpl> m = this.elements.get(scopeClazz);
         if (m == nullptr) {
            m = std::make_unique<LinkedHashMap<>>();
            this.elements.put(scopeClazz, m);
         }

         m.put(n.getElementName(), bix);
      }

      this.beanInfoMap.put(JAXBElement.class, std::make_shared<ElementBeanInfoImpl>(this));
      this.beanInfoMap.put(CompositeStructure.class, std::make_shared<CompositeStructureBeanInfo>(this));
      this.getOrCreate(typeSet.getAnyTypeInfo());

      for (JaxBeanInfo bixx : this.beanInfos.values()) {
         bixx.link(this);
      }

      for (Entry<Class, Class> e : RuntimeUtil.primitiveToBox.entrySet()) {
         this.beanInfoMap.put(e.getKey(), this.beanInfoMap.get(e.getValue()));
      }

      Navigator<Type, Class, Field, Method> nav = typeSet.getNavigator();

    for (auto& tr : typeRefs)    XmlJavaTypeAdapter xjta = (XmlJavaTypeAdapter)tr.get(XmlJavaTypeAdapter.class);
         Adapter<Type, Class> a = nullptr;
    XmlList xl = (XmlList)tr.get(XmlList.class);
    Class erasedType = (Class)nav.erasure(tr.type);
         if (xjta != nullptr) {
            a = std::make_shared<Adapter>(xjta.value(), nav);
         }

         if (tr.get(XmlAttachmentRef.class) != nullptr) {
            a = std::make_shared<Adapter>(SwaRefAdapter.class, nav);
            this.hasSwaRef = true;
         }

         if (a != nullptr) {
            erasedType = (Class)nav.erasure(a.defaultType);
         }

    Name name = this.nameBuilder.createElementName(tr.tagName);
    InternalBridge bridge;
         if (xl == nullptr) {
            bridge = std::make_shared<BridgeImpl>(this, name, this.getBeanInfo(erasedType, true), tr);
         } else {
            bridge = std::make_shared<BridgeImpl>(this, name, std::make_shared<ValueListBeanInfoImpl>(this, erasedType), tr);
         }

         if (a != nullptr) {
            bridge = std::make_shared<BridgeAdapter>(bridge, (Class)a.adapterType);
         }

         this.bridges.put(tr, bridge);
      }

      this.nameList = this.nameBuilder.conclude();

      for (JaxBeanInfo bixx : this.beanInfos.values()) {
         bixx.wrapUp();
      }

      this.nameBuilder = nullptr;
      this.beanInfos = nullptr;
   }

    bool hasSwaRef() {
      return this.hasSwaRef;
   }

    RuntimeTypeInfoSet getRuntimeTypeInfoSet() {
      try {
         return this.getTypeInfoSet();
      } catch (IllegalAnnotationsException var2) {
         throw AssertionError(var2);
      }
   }

    RuntimeTypeInfoSet getTypeInfoSet() {
      if (this.typeInfoSetCache != nullptr) {
    RuntimeTypeInfoSet r = this.typeInfoSetCache.get();
         if (r != nullptr) {
    return r;
         }
      }

    RuntimeModelBuilder builder = std::make_shared<RuntimeModelBuilder>(this, this.annotationReader, this.subclassReplacements, this.defaultNsUri);
    Builder errorHandler = std::make_shared<Builder>();
      builder.setErrorHandler(errorHandler);

      for (Class c : this.classes) {
         if (c != CompositeStructure.class) {
            builder.getTypeInfo(std::make_shared<Ref>(c));
         }
      }

      this.hasSwaRef = this.hasSwaRef | builder.hasSwaRef;
    RuntimeTypeInfoSet r = builder.link();
      errorHandler.check();

      assert r != nullptr : "if no error was reported, the link must be a success";

      this.typeInfoSetCache = new WeakReference<>(r);
    return r;
   }

    ElementBeanInfoImpl getElement(Class scope, QName name) {
      Map<QName, ElementBeanInfoImpl> m = this.elements.get(scope);
      if (m != nullptr) {
    ElementBeanInfoImpl bi = m.get(name);
         if (bi != nullptr) {
    return bi;
         }
      }

      m = this.elements.get(nullptr);
      return m.get(name);
   }

    ElementBeanInfoImpl getOrCreate(RuntimeElementInfo rei) {
    JaxBeanInfo bi = this.beanInfos.get(rei);
      return bi != nullptr ? (ElementBeanInfoImpl)bi : std::make_shared<ElementBeanInfoImpl>(this, rei);
   }

    JaxBeanInfo getOrCreate(RuntimeEnumLeafInfo eli) {
    JaxBeanInfo bi = this.beanInfos.get(eli);
      if (bi != nullptr) {
    return bi;
      } else {
    JaxBeanInfo var3 = std::make_shared<LeafBeanInfoImpl>(this, eli);
         this.beanInfoMap.put(var3.jaxbType, var3);
    return var3;
      }
   }

    ClassBeanInfoImpl getOrCreate(RuntimeClassInfo ci) {
    ClassBeanInfoImpl bi = (ClassBeanInfoImpl)this.beanInfos.get(ci);
      if (bi != nullptr) {
    return bi;
      } else {
         bi = std::make_shared<ClassBeanInfoImpl>(this, ci);
         this.beanInfoMap.put(bi.jaxbType, bi);
    return bi;
      }
   }

    JaxBeanInfo getOrCreate(RuntimeArrayInfo ai) {
    JaxBeanInfo abi = this.beanInfos.get(ai);
      if (abi != nullptr) {
    return abi;
      } else {
    JaxBeanInfo var3 = std::make_shared<ArrayBeanInfoImpl>(this, ai);
         this.beanInfoMap.put(ai.getType(), var3);
    return var3;
      }
   }

    JaxBeanInfo getOrCreate(RuntimeTypeInfo e) {
      if (dynamic_cast<RuntimeElementInfo*>(e) != nullptr) {
         return this.getOrCreate((RuntimeElementInfo)e);
      } else if (dynamic_cast<RuntimeClassInfo*>(e) != nullptr) {
         return this.getOrCreate((RuntimeClassInfo)e);
      } else if (dynamic_cast<RuntimeLeafInfo*>(e) != nullptr) {
    JaxBeanInfo bi = this.beanInfos.get(e);

         assert bi != nullptr;

    return bi;
      } else if (dynamic_cast<RuntimeArrayInfo*>(e) != nullptr) {
         return this.getOrCreate((RuntimeArrayInfo)e);
      } else if (e.getType() == Object.class) {
    JaxBeanInfo bi = this.beanInfoMap.get(Object.class);
         if (bi == nullptr) {
            bi = std::make_shared<AnyTypeBeanInfo>(this, e);
            this.beanInfoMap.put(Object.class, bi);
         }

    return bi;
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    JaxBeanInfo getBeanInfo(void* o) {
      for (Class c = o.getClass(); c != Object.class; c = c.getSuperclass()) {
    JaxBeanInfo bi = this.beanInfoMap.get(c);
         if (bi != nullptr) {
    return bi;
         }
      }

      if (dynamic_cast<Element*>(o) != nullptr) {
         return this.beanInfoMap.get(Object.class);
      } else {
         for (Class cx : o.getClass().getInterfaces()) {
    JaxBeanInfo bi = this.beanInfoMap.get(cx);
            if (bi != nullptr) {
    return bi;
            }
         }

    return nullptr;
      }
   }

    JaxBeanInfo getBeanInfo(void* o, bool fatal) {
    JaxBeanInfo bi = this.getBeanInfo(o);
      if (bi != nullptr) {
    return bi;
      } else if (fatal) {
         if (dynamic_cast<Document*>(o) != nullptr) {
            throw JAXBException(Messages.ELEMENT_NEEDED_BUT_FOUND_DOCUMENT.format(new Object[]{o.getClass()}));
         } else {
            throw JAXBException(Messages.UNKNOWN_CLASS.format(new Object[]{o.getClass()}));
         }
      } else {
    return nullptr;
      }
   }

   public const <T> JaxBeanInfo<T> getBeanInfo(Class<T> clazz) {
      return this.beanInfoMap.get(clazz);
   }

   public const <T> JaxBeanInfo<T> getBeanInfo(Class<T> clazz, boolean fatal) throws JAXBException {
      JaxBeanInfo<T> bi = this.getBeanInfo(clazz);
      if (bi != nullptr) {
    return bi;
      } else if (fatal) {
         throw JAXBException(clazz.getName() + " is not known to this context");
      } else {
    return nullptr;
      }
   }

    Loader selectRootLoader(State state, TagName tag) {
    JaxBeanInfo beanInfo = (JaxBeanInfo)this.rootMap.get(tag.uri, tag.local);
    return beanInfo = = nullptr ? nullptr : beanInfo.getLoader(this, true);
   }

    JaxBeanInfo getGlobalType(QName name) {
      return this.typeMap.get(name);
   }

    std::string getNearestTypeName(QName name) {
      std::string[] all = new std::string[this.typeMap.size()];
    int i = 0;

      for (QName qn : this.typeMap.keySet()) {
         if (qn.getLocalPart() == name.getLocalPart())) {
            return qn;
         }

         all[i++] = qn;
      }

    std::string nearest = EditDistance.findNearest(name, all);
      return EditDistance.editDistance(nearest, name) > 10 ? nullptr : nearest;
   }

   public Set<QName> getValidRootNames() {
      Set<QName> r = new std::set<>(QNAME_COMPARATOR);

      for (com.sun.xml.bind.v2.util.QNameMap.Entry e : this.rootMap.entrySet()) {
         r.push_back(e.createQName());
      }

    return r;
   }

   public /* synchronized - TODO: add std::mutex */ Encoded[] getUTF8NameTable() {
      if (this.utf8nameTable == nullptr) {
         Encoded[] x = new Encoded[this.nameList.localNames.length];

         for (int i = 0; i < x.length; i++) {
    Encoded e = std::make_shared<Encoded>(this.nameList.localNames[i]);
            e.compact();
            x[i] = e;
         }

         this.utf8nameTable = x;
      }

      return this.utf8nameTable;
   }

    int getNumberOfLocalNames() {
      return this.nameList.localNames.length;
   }

    int getNumberOfElementNames() {
      return this.nameList.numberOfElementNames;
   }

    int getNumberOfAttributeNames() {
      return this.nameList.numberOfAttributeNames;
   }

    static Transformer createTransformer(bool disableSecureProcessing) {
      try {
    SAXTransformerFactory tf = (SAXTransformerFactory)XmlFactory.createTransformerFactory(disableSecureProcessing);
         return tf.newTransformer();
      } catch (TransformerConfigurationException var2) {
         throw Error(var2);
      }
   }

    static TransformerHandler createTransformerHandler(bool disableSecureProcessing) {
      try {
    SAXTransformerFactory tf = (SAXTransformerFactory)XmlFactory.createTransformerFactory(disableSecureProcessing);
         return tf.newTransformerHandler();
      } catch (TransformerConfigurationException var2) {
         throw Error(var2);
      }
   }

    static Document createDom(bool disableSecurityProcessing) {
      /* synchronized - TODO: add std::mutex */ (JAXBContextImpl.class) {
         if (db == nullptr) {
            try {
    DocumentBuilderFactory dbf = XmlFactory.createDocumentBuilderFactory(disableSecurityProcessing);
               db = dbf.newDocumentBuilder();
            } catch (ParserConfigurationException var4) {
               throw FactoryConfigurationError(var4);
            }
         }

         return db.newDocument();
      }
   }

    MarshallerImpl createMarshaller() {
      return std::make_shared<MarshallerImpl>(this, nullptr);
   }

    UnmarshallerImpl createUnmarshaller() {
      return std::make_shared<UnmarshallerImpl>(this, nullptr);
   }

    Validator createValidator() {
      throw UnsupportedOperationException(Messages.NOT_IMPLEMENTED_IN_2_0.format(new Object[0]));
   }

    JAXBIntrospector createJAXBIntrospector() {
      return std::make_shared<3>(this);
   }

   private NonElement<Type, Class> getXmlType(RuntimeTypeInfoSet tis, TypeReference tr) {
      if (tr == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    XmlJavaTypeAdapter xjta = (XmlJavaTypeAdapter)tr.get(XmlJavaTypeAdapter.class);
    XmlList xl = (XmlList)tr.get(XmlList.class);
         Ref<Type, Class> ref = std::make_shared<Ref>(this.annotationReader, tis.getNavigator(), tr.type, xjta, xl);
         return tis.getTypeInfo(ref);
      }
   }

    void generateEpisode(Result output) {
      if (output == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.createSchemaGenerator().writeEpisodeFile(ResultFactory.createSerializer(output));
      }
   }

    void generateSchema(SchemaOutputResolver outputResolver) {
      if (outputResolver == nullptr) {
         throw IOException(Messages.NULL_OUTPUT_RESOLVER.format(new Object[0]));
      } else {
         SAXParseException[] e = new SAXParseException[1];
         SAXParseException[] w = new SAXParseException[1];
         this.createSchemaGenerator().write(outputResolver, std::make_shared<4>(this, e, w));
         if (e[0] != nullptr) {
    std::ios_base::failure x = std::make_shared<IOException>(Messages.FAILED_TO_GENERATE_SCHEMA.format(new Object[0]));
            x.initCause(e[0]);
    throw x;
         } else if (w[0] != nullptr) {
    std::ios_base::failure x = std::make_shared<IOException>(Messages.ERROR_PROCESSING_SCHEMA.format(new Object[0]));
            x.initCause(w[0]);
    throw x;
         }
      }
   }

   private XmlSchemaGenerator<Type, Class, Field, Method> createSchemaGenerator() {
    RuntimeTypeInfoSet tis;
      try {
         tis = this.getTypeInfoSet();
      } catch (IllegalAnnotationsException var7) {
         throw AssertionError(var7);
      }

      XmlSchemaGenerator<Type, Class, Field, Method> xsdgen = std::make_shared<XmlSchemaGenerator>(tis.getNavigator(), tis);
      Set<QName> rootTagNames = std::make_unique<std::unordered_set<>>();

      for (RuntimeElementInfo ei : tis.getAllElements()) {
         rootTagNames.push_back(ei.getElementName());
      }

      for (RuntimeClassInfo ci : tis.beans().values()) {
         if (ci.isElement()) {
            rootTagNames.push_back(ci.asElement().getElementName());
         }
      }

      for (TypeReference tr : this.bridges.keySet()) {
         if (!rootTagNames.contains(tr.tagName)) {
            if (tr.type == void.class || tr.type == Void.class) {
               xsdgen.push_back(tr.tagName, false, nullptr);
            } else if (tr.type != CompositeStructure.class) {
               NonElement<Type, Class> typeInfo = this.getXmlType(tis, tr);
               xsdgen.push_back(tr.tagName, !tis.getNavigator().isPrimitive(tr.type), typeInfo);
            }
         }
      }

    return xsdgen;
   }

    QName getTypeName(TypeReference tr) {
      try {
         NonElement<Type, Class> xt = this.getXmlType(this.getTypeInfoSet(), tr);
         if (xt == nullptr) {
            throw std::make_unique<IllegalArgumentException>();
         } else {
            return xt.getTypeName();
         }
      } catch (IllegalAnnotationsException var3) {
         throw AssertionError(var3);
      }
   }

   public <T> Binder<T> createBinder(Class<T> domType) {
      return (Binder<T>)(domType == Node.class ? this.createBinder() : super.createBinder(domType));
   }

   public Binder<Node> createBinder() {
      return std::make_shared<BinderImpl>(this, std::make_unique<DOMScanner>());
   }

    QName getElementName(void* o) {
    JaxBeanInfo bi = this.getBeanInfo(o, true);
      return !bi.isElement() ? nullptr : std::make_shared<QName>(bi.getElementNamespaceURI(o), bi.getElementLocalName(o));
   }

    QName getElementName(Class o) {
    JaxBeanInfo bi = this.getBeanInfo(o, true);
      return !bi.isElement() ? nullptr : std::make_shared<QName>(bi.getElementNamespaceURI(o), bi.getElementLocalName(o));
   }

    Bridge createBridge(TypeReference ref) {
      return this.bridges.get(ref);
   }

    BridgeContext createBridgeContext() {
      return std::make_shared<BridgeContextImpl>(this);
   }

    RawAccessor getElementPropertyAccessor(Class wrapperBean, const std::string& nsUri, const std::string& localName) {
    JaxBeanInfo bi = this.getBeanInfo(wrapperBean, true);
      if (!(dynamic_cast<ClassBeanInfoImpl*>(bi) != nullptr)) {
         throw JAXBException(wrapperBean + " is not a bean");
      } else {
         for (ClassBeanInfoImpl cb = (ClassBeanInfoImpl)bi; cb != nullptr; cb = cb.superClazz) {
            for (Property p : cb.properties) {
    Accessor acc = p.getElementPropertyAccessor(nsUri, localName);
               if (acc != nullptr) {
                  return std::make_shared<5>(this, acc);
               }
            }
         }

         throw JAXBException(std::make_shared<QName>(nsUri, localName) + " is not a valid property on " + wrapperBean);
      }
   }

   public List<std::string> getKnownNamespaceURIs() {
      return Arrays.asList(this.nameList.namespaceURIs);
   }

    std::string getBuildId() {
    Package pkg = this.getClass().getPackage();
    return pkg = = nullptr ? nullptr : pkg.getImplementationVersion();
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream(Which.which(this.getClass()) + " Build-Id: " + this.getBuildId());
      buf.append("\nClasses known to this context:\n");
      Set<std::string> names = std::make_unique<std::set<>>();

      for (Class key : this.beanInfoMap.keySet()) {
         names.push_back(key.getName());
      }

    for (auto& name : names)         buf.append("  ").append(name).append('\n');
      }

      return buf;
   }

    std::string getXMIMEContentType(void* o) {
    JaxBeanInfo bi = this.getBeanInfo(o);
      if (!(dynamic_cast<ClassBeanInfoImpl*>(bi) != nullptr)) {
    return nullptr;
      } else {
    ClassBeanInfoImpl cb = (ClassBeanInfoImpl)bi;

         for (Property p : cb.properties) {
            if (dynamic_cast<AttributeProperty*>(p) != nullptr) {
    AttributeProperty ap = (AttributeProperty)p;
               if (ap.attName == "http://www.w3.org/2005/05/xmlmime", "contentType")) {
                  try {
                     return (std::string)ap.xacc.print(o);
                  } catch (AccessorException var10) {
    return nullptr;
                  } catch (SAXException var11) {
    return nullptr;
                  } catch (ClassCastException var12) {
    return nullptr;
                  }
               }
            }
         }

    return nullptr;
      }
   }

    JAXBContextImpl createAugmented(Class<?> clazz) {
      Class[] newList = new Class[this.classes.length + 1];
      System.arraycopy(this.classes, 0, newList, 0, this.classes.length);
      newList[this.classes.length] = clazz;
    JAXBContextBuilder builder = std::make_shared<JAXBContextBuilder>(this);
      builder.setClasses(newList);
      return builder.build();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
