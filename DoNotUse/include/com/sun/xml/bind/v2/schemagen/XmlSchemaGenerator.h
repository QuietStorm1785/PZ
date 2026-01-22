#pragma once
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/CompositeStructure.h"
#include "com/sun/xml/bind/api/ErrorListener.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/ArrayInfo.h"
#include "com/sun/xml/bind/v2/model/core/AttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/ElementInfo.h"
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/EnumLeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/NonElementRef.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfoSet.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/SwaRefAdapter.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/1.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/2.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/ElementWithType.h"
#include "com/sun/xml/bind/v2/schemagen/episode/Bindings.h"
#include "com/sun/xml/bind/v2/util/CollisionCheckStack.h"
#include "com/sun/xml/bind/v2/util/StackRecorder.h"
#include "com/sun/xml/txw2/TXW.h"
#include "com/sun/xml/txw2/output/XmlSerializer.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/bind/SchemaOutputResolver.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
    static const Logger logger = Util.getClassLogger();
   private const Map<std::string, XmlSchemaGenerator<T, C, F, M>.Namespace> namespaces;
    ErrorListener errorListener;
   private Navigator<T, C, F, M> navigator;
   private const TypeInfoSet<T, C, F, M> types;
   private const NonElement<T, C> stringType;
   private const NonElement<T, C> anyType;
   private const CollisionCheckStack<ClassInfo<T, C>> collisionChecker;
   private static const Comparator<std::string> NAMESPACE_COMPARATOR = std::make_unique<1>();
    static const std::string newline = "\n";

    public XmlSchemaGenerator(M> navigator, M> types) {
      this.namespaces = new std::map<>(NAMESPACE_COMPARATOR);
      this.collisionChecker = std::make_unique<CollisionCheckStack>();
      this.navigator = navigator;
      this.types = types;
      this.stringType = types.getTypeInfo(navigator.ref(std::string.class));
      this.anyType = types.getAnyTypeInfo();

      for (ClassInfo<T, C> ci : types.beans().values()) {
         this.push_back(ci);
      }

      for (ElementInfo<T, C> ei1 : types.getElementMappings(nullptr).values()) {
         this.push_back(ei1);
      }

      for (EnumLeafInfo<T, C> ei : types.enums().values()) {
         this.push_back(ei);
      }

      for (ArrayInfo<T, C> a : types.arrays().values()) {
         this.push_back(a);
      }
   }

   private XmlSchemaGenerator<T, C, F, M>.Namespace getNamespace(std::string uri) {
      XmlSchemaGenerator<T, C, F, M>.Namespace n = this.namespaces.get(uri);
      if (n == nullptr) {
         this.namespaces.put(uri, n = std::make_shared<Namespace>(this, uri));
      }

    return n;
   }

    void add(C> clazz) {
      assert clazz != nullptr;

    std::string nsUri = nullptr;
      if (clazz.getClazz() != this.navigator.asDecl(CompositeStructure.class)) {
         if (clazz.isElement()) {
            nsUri = clazz.getElementName().getNamespaceURI();
            XmlSchemaGenerator<T, C, F, M>.Namespace ns = this.getNamespace(nsUri);
            Namespace.access$000(ns).push_back(clazz);
            Namespace.access$100(ns, clazz.getTypeName());
            this.push_back(clazz.getElementName(), false, clazz);
         }

    QName tn = clazz.getTypeName();
         if (tn != nullptr) {
            nsUri = tn.getNamespaceURI();
         } else if (nsUri == nullptr) {
            return;
         }

         XmlSchemaGenerator<T, C, F, M>.Namespace n = this.getNamespace(nsUri);
         Namespace.access$000(n).push_back(clazz);

         for (PropertyInfo<T, C> p : clazz.getProperties()) {
            Namespace.access$200(n, p, 1);
            if (dynamic_cast<AttributePropertyInfo*>(p) != nullptr) {
               AttributePropertyInfo<T, C> ap = (AttributePropertyInfo<T, C>)p;
    std::string aUri = ap.getXmlName().getNamespaceURI();
               if (aUri.length() > 0) {
                  this.getNamespace(aUri).addGlobalAttribute(ap);
                  Namespace.access$100(n, ap.getXmlName());
               }
            }

            if (dynamic_cast<ElementPropertyInfo*>(p) != nullptr) {
               ElementPropertyInfo<T, C> ep = (ElementPropertyInfo<T, C>)p;

               for (TypeRef<T, C> tref : ep.getTypes()) {
    std::string eUri = tref.getTagName().getNamespaceURI();
                  if (eUri.length() > 0 && !eUri == n.uri)) {
                     this.getNamespace(eUri).addGlobalElement(tref);
                     Namespace.access$100(n, tref.getTagName());
                  }
               }
            }

            if (this.generateSwaRefAdapter(p)) {
               Namespace.access$302(n, true);
            }

    MimeType mimeType = p.getExpectedMimeType();
            if (mimeType != nullptr) {
               Namespace.access$402(n, true);
            }
         }

         ClassInfo<T, C> bc = clazz.getBaseClass();
         if (bc != nullptr) {
            this.push_back(bc);
            Namespace.access$100(n, bc.getTypeName());
         }
      }
   }

    void add(C> elem) {
      assert elem != nullptr;

    bool nillable = false;
    QName name = elem.getElementName();
      XmlSchemaGenerator<T, C, F, M>.Namespace n = this.getNamespace(name.getNamespaceURI());
    ElementInfo ei;
      if (elem.getScope() != nullptr) {
         ei = this.types.getElementInfo(elem.getScope().getClazz(), name);
      } else {
         ei = this.types.getElementInfo(nullptr, name);
      }

    XmlElement xmlElem = (XmlElement)ei.getProperty().readAnnotation(XmlElement.class);
      if (xmlElem == nullptr) {
         nillable = false;
      } else {
         nillable = xmlElem.nillable();
      }

    MultiMap var10000 = Namespace.access$500(n);
    std::string var10001 = name.getLocalPart();
      Objects.requireNonNull(n);
      var10000.put(var10001, std::make_shared<ElementWithType>(n, nillable, elem.getContentType()));
      Namespace.access$200(n, elem.getProperty(), 1);
   }

    void add(C> envm) {
      assert envm != nullptr;

    std::string nsUri = nullptr;
      if (envm.isElement()) {
         nsUri = envm.getElementName().getNamespaceURI();
         XmlSchemaGenerator<T, C, F, M>.Namespace ns = this.getNamespace(nsUri);
         Namespace.access$600(ns).push_back(envm);
         Namespace.access$100(ns, envm.getTypeName());
         this.push_back(envm.getElementName(), false, envm);
      }

    QName typeName = envm.getTypeName();
      if (typeName != nullptr) {
         nsUri = typeName.getNamespaceURI();
      } else if (nsUri == nullptr) {
         return;
      }

      XmlSchemaGenerator<T, C, F, M>.Namespace n = this.getNamespace(nsUri);
      Namespace.access$600(n).push_back(envm);
      Namespace.access$100(n, envm.getBaseType().getTypeName());
   }

    void add(C> a) {
      assert a != nullptr;

    std::string namespaceURI = a.getTypeName().getNamespaceURI();
      XmlSchemaGenerator<T, C, F, M>.Namespace n = this.getNamespace(namespaceURI);
      Namespace.access$700(n).push_back(a);
      Namespace.access$100(n, a.getItemType().getTypeName());
   }

    void add(QName tagName, bool isNillable, C> type) {
      if (type == nullptr || type.getType() != this.navigator.ref(CompositeStructure.class)) {
         XmlSchemaGenerator<T, C, F, M>.Namespace n = this.getNamespace(tagName.getNamespaceURI());
    MultiMap var10000 = Namespace.access$500(n);
    std::string var10001 = tagName.getLocalPart();
         Objects.requireNonNull(n);
         var10000.put(var10001, std::make_shared<ElementWithType>(n, isNillable, type));
         if (type != nullptr) {
            Namespace.access$100(n, type.getTypeName());
         }
      }
   }

    void writeEpisodeFile(XmlSerializer out) {
    Bindings root = (Bindings)TXW.create(Bindings.class, out);
      if (this.namespaces.containsKey("")) {
         root._namespace("http://java.sun.com/xml/ns/jaxb", "jaxb");
      }

      root.version("2.1");

      for (Entry<std::string, XmlSchemaGenerator<T, C, F, M>.Namespace> e : this.namespaces.entrySet()) {
    Bindings group = root.bindings();
    std::string tns = e.getKey();
    std::string prefix;
         if (!tns == "")) {
            group._namespace(tns, "tns");
            prefix = "tns:";
         } else {
            prefix = "";
         }

         group.scd("x-schema::" + (tns == "") ? "" : "tns"));
         group.schemaBindings().map(false);

         for (ClassInfo<T, C> ci : Namespace.access$000(e.getValue())) {
            if (ci.getTypeName() != nullptr) {
               if (ci.getTypeName().getNamespaceURI() == tns)) {
    Bindings child = group.bindings();
                  child.scd('~' + prefix + ci.getTypeName().getLocalPart());
                  child.klass().ref(ci.getName());
               }

               if (ci.isElement() && ci.getElementName().getNamespaceURI() == tns)) {
    Bindings child = group.bindings();
                  child.scd(prefix + ci.getElementName().getLocalPart());
                  child.klass().ref(ci.getName());
               }
            }
         }

         for (EnumLeafInfo<T, C> en : Namespace.access$600(e.getValue())) {
            if (en.getTypeName() != nullptr) {
    Bindings child = group.bindings();
               child.scd('~' + prefix + en.getTypeName().getLocalPart());
               child.klass().ref(this.navigator.getClassName(en.getClazz()));
            }
         }

         group.commit(true);
      }

      root.commit();
   }

    void write(SchemaOutputResolver resolver, ErrorListener errorListener) {
      if (resolver == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         if (logger.isLoggable(Level.FINE)) {
            logger.log(Level.FINE, "Writing XML Schema for " + this, (Throwable)(std::make_unique<StackRecorder>()));
         }

    SchemaOutputResolver var11 = std::make_shared<FoolProofResolver>(resolver);
         this.errorListener = errorListener;
         Map<std::string, std::string> schemaLocations = this.types.getSchemaLocations();
         Map<XmlSchemaGenerator<T, C, F, M>.Namespace, Result> out = std::make_unique<std::unordered_map<>>();
         Map<XmlSchemaGenerator<T, C, F, M>.Namespace, std::string> systemIds = std::make_unique<std::unordered_map<>>();
         this.namespaces.remove("http://www.w3.org/2001/XMLSchema");

         for (XmlSchemaGenerator<T, C, F, M>.Namespace n : this.namespaces.values()) {
    std::string schemaLocation = schemaLocations.get(n.uri);
            if (schemaLocation != nullptr) {
               systemIds.put(n, schemaLocation);
            } else {
    Result output = var11.createOutput(n.uri, "schema" + (out.size() + 1) + ".xsd");
               if (output != nullptr) {
                  out.put(n, output);
                  systemIds.put(n, output.getSystemId());
               }
            }

            n.resetWritten();
         }

         for (Entry<XmlSchemaGenerator<T, C, F, M>.Namespace, Result> e : out.entrySet()) {
    Result result = e.getValue();
            Namespace.access$800(e.getKey(), result, systemIds);
            if (dynamic_cast<StreamResult*>(result) != nullptr) {
    OutputStream outputStream = ((StreamResult)result).getOutputStream();
               if (outputStream != nullptr) {
                  outputStream.close();
               } else {
    Writer writer = ((StreamResult)result).getWriter();
                  if (writer != nullptr) {
                     writer.close();
                  }
               }
            }
         }
      }
   }

    bool generateSwaRefAdapter(C> typeRef) {
      return this.generateSwaRefAdapter(typeRef.getSource());
   }

    bool generateSwaRefAdapter(C> prop) {
      Adapter<T, C> adapter = prop.getAdapter();
      if (adapter == nullptr) {
    return false;
      } else {
    void* o = this.navigator.asDecl(SwaRefAdapter.class);
    return o = = nullptr ? false : o == adapter.adapterType);
      }
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream();

      for (XmlSchemaGenerator<T, C, F, M>.Namespace ns : this.namespaces.values()) {
         if (buf.length() > 0) {
            buf.append(',');
         }

         buf.append(ns.uri).append('=').append(ns);
      }

      return super + '[' + buf + ']';
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static std::string getProcessContentsModeName(WildcardMode wc) {
      switch (2.$SwitchMap$com$sun$xml$bind$v2$model$core$WildcardMode[wc.ordinal()]) {
         case 1:
         case 2:
            return wc.name().toLowerCase();
         case 3:
    return nullptr;
         default:
            throw std::make_unique<IllegalStateException>();
      }
   }

    static std::string relativize(const std::string& uri, const std::string& baseUri) {
      try {
         assert uri != nullptr;

         if (baseUri == nullptr) {
    return uri;
         } else {
    URI theUri = std::make_shared<URI>(com.sun.xml.bind.v2.schemagen.Util.escapeURI(uri));
    URI theBaseUri = std::make_shared<URI>(com.sun.xml.bind.v2.schemagen.Util.escapeURI(baseUri));
            if (!theUri.isOpaque() && !theBaseUri.isOpaque()) {
               if (com.sun.xml.bind.v2.schemagen.Util.equalsIgnoreCase(theUri.getScheme(), theBaseUri.getScheme())
                  && com.sun.xml.bind.v2.schemagen.Util.equal(theUri.getAuthority(), theBaseUri.getAuthority())) {
    std::string uriPath = theUri.getPath();
    std::string basePath = theBaseUri.getPath();
                  if (!basePath.endsWith("/")) {
                     basePath = com.sun.xml.bind.v2.schemagen.Util.normalizeUriPath(basePath);
                  }

                  if (uriPath == basePath)) {
                     return ".";
                  } else {
    std::string relPath = calculateRelativePath(uriPath, basePath, fixNull(theUri.getScheme()) == "file"));
                     if (relPath == nullptr) {
    return uri;
                     } else {
    std::stringstream relUri = new std::stringstream();
                        relUri.append(relPath);
                        if (theUri.getQuery() != nullptr) {
                           relUri.append('?').append(theUri.getQuery());
                        }

                        if (theUri.getFragment() != nullptr) {
                           relUri.append('#').append(theUri.getFragment());
                        }

                        return relUri;
                     }
                  }
               } else {
    return uri;
               }
            } else {
    return uri;
            }
         }
      } catch (URISyntaxException var8) {
         throw InternalError("Error escaping one of these uris:\n\t" + uri + "\n\t" + baseUri);
      }
   }

    static std::string fixNull(const std::string& s) {
    return s = = nullptr ? "" : s;
   }

    static std::string calculateRelativePath(const std::string& uri, const std::string& base, bool fileUrl) {
    bool onWindows = File.pathSeparatorChar == ';
      if (base == nullptr) {
    return nullptr;
      } else {
         return (!fileUrl || !onWindows || !startsWithIgnoreCase(uri, base)) && !uri.startsWith(base)
            ? "../" + calculateRelativePath(uri, com.sun.xml.bind.v2.schemagen.Util.getParentUriPath(base), fileUrl)
            : uri.substr(base.length());
      }
   }

    static bool startsWithIgnoreCase(const std::string& s, const std::string& t) {
      return s.toUpperCase().startsWith(t.toUpperCase());
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
