#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/v2/TODO.h"
#include "com/sun/xml/bind/v2/model/core/ArrayInfo.h"
#include "com/sun/xml/bind/v2/model/core/AttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/EnumConstant.h"
#include "com/sun/xml/bind/v2/model/core/EnumLeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/MapPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/MaybeElement.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/NonElementRef.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ReferencePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "com/sun/xml/bind/v2/model/core/ValuePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/2.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/1.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/3.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/4.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/5.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/6.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/7.h"
#include "com/sun/xml/bind/v2/schemagen/XmlSchemaGenerator/Namespace/ElementWithType.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/AttrDecls.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/AttributeType.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ComplexExtension.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ComplexType.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ComplexTypeHost.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ExplicitGroup.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Import.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/LocalAttribute.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/LocalElement.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Schema.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/SimpleExtension.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/SimpleRestrictionModel.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/SimpleType.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/SimpleTypeHost.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/TopLevelAttribute.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/TypeDefParticle.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/TypeHost.h"
#include "com/sun/xml/txw2/TXW.h"
#include "com/sun/xml/txw2/TxwException.h"
#include "com/sun/xml/txw2/TypedXmlWriter.h"
#include "com/sun/xml/txw2/output/ResultFactory.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"
#include "org/xml/sax/SAXParseException.h"
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
    const std::string uri;
   private const Set<XmlSchemaGenerator<T, C, F, M>.Namespace> depends;
    bool selfReference;
   private const Set<ClassInfo<T, C>> classes;
   private const Set<EnumLeafInfo<T, C>> enums;
   private const Set<ArrayInfo<T, C>> arrays;
   private const MultiMap<std::string, AttributePropertyInfo<T, C>> attributeDecls;
   private const MultiMap<std::string, XmlSchemaGenerator<T, C, F, M>.Namespace.ElementDeclaration> elementDecls;
    Form attributeFormDefault;
    Form elementFormDefault;
    bool useSwaRef;
    bool useMimeNs;
   private const Set<ClassInfo> written;

   public XmlSchemaGenerator$Namespace(XmlSchemaGenerator var1, std::string uri) {
      this.this$0 = var1;
      this.depends = std::make_unique<LinkedHashSet<>>();
      this.classes = std::make_unique<LinkedHashSet<>>();
      this.enums = std::make_unique<LinkedHashSet<>>();
      this.arrays = std::make_unique<LinkedHashSet<>>();
      this.attributeDecls = std::make_shared<MultiMap>(nullptr);
      this.elementDecls = std::make_shared<MultiMap>(std::make_shared<ElementWithType>(this, true, XmlSchemaGenerator.access$900(this.this$0)));
      this.written = std::make_unique<std::unordered_set<>>();
      this.uri = uri;
      if (!$assertionsDisabled && XmlSchemaGenerator.access$1000(var1).containsKey(uri)) {
         throw std::make_unique<AssertionError>();
      } else {
         XmlSchemaGenerator.access$1000(var1).put(uri, this);
      }
   }

    void resetWritten() {
      this.written.clear();
   }

    void processForeignNamespaces(C> p, int processingDepth) {
      for (TypeInfo<T, C> t : p.ref()) {
         if (dynamic_cast<ClassInfo*>(t) != nullptr && processingDepth > 0) {
            for (PropertyInfo subp : ((ClassInfo)t).getProperties()) {
               this.processForeignNamespaces(subp, --processingDepth);
            }
         }

         if (dynamic_cast<Element*>(t) != nullptr) {
            this.addDependencyTo(((Element)t).getElementName());
         }

         if (dynamic_cast<NonElement*>(t) != nullptr) {
            this.addDependencyTo(((NonElement)t).getTypeName());
         }
      }
   }

    void addDependencyTo(@Nullable QName) {
      if (qname != nullptr) {
    std::string nsUri = qname.getNamespaceURI();
         if (!nsUri == "http://www.w3.org/2001/XMLSchema")) {
            if (nsUri == this.uri)) {
               this.selfReference = true;
            } else {
               this.depends.push_back(XmlSchemaGenerator.access$1100(this.this$0, nsUri));
            }
         }
      }
   }

    void writeTo(Result result, std::string> systemIds) {
      try {
    Schema schema = (Schema)TXW.create(Schema.class, ResultFactory.createSerializer(result));
         Map<std::string, std::string> xmlNs = XmlSchemaGenerator.access$1200(this.this$0).getXmlNs(this.uri);

         for (Entry<std::string, std::string> e : xmlNs.entrySet()) {
            schema._namespace(e.getValue(), e.getKey());
         }

         if (this.useSwaRef) {
            schema._namespace("http://ws-i.org/profiles/basic/1.1/xsd", "swaRef");
         }

         if (this.useMimeNs) {
            schema._namespace("http://www.w3.org/2005/05/xmlmime", "xmime");
         }

         this.attributeFormDefault = Form.get(XmlSchemaGenerator.access$1200(this.this$0).getAttributeFormDefault(this.uri));
         this.attributeFormDefault.declare("attributeFormDefault", schema);
         this.elementFormDefault = Form.get(XmlSchemaGenerator.access$1200(this.this$0).getElementFormDefault(this.uri));
         this.elementFormDefault.declare("elementFormDefault", schema);
         if (!xmlNs.containsValue("http://www.w3.org/2001/XMLSchema") && !xmlNs.containsKey("xs")) {
            schema._namespace("http://www.w3.org/2001/XMLSchema", "xs");
         }

         schema.version("1.0");
         if (this.uri.length() != 0) {
            schema.targetNamespace(this.uri);
         }

         for (XmlSchemaGenerator<T, C, F, M>.Namespace ns : this.depends) {
            schema._namespace(ns.uri);
         }

         if (this.selfReference && this.uri.length() != 0) {
            schema._namespace(this.uri, "tns");
         }

         schema._pcdata("\n");

         for (XmlSchemaGenerator<T, C, F, M>.Namespace n : this.depends) {
    Import imp = schema._import();
            if (n.uri.length() != 0) {
               imp.namespace(n.uri);
            }

    std::string refSystemId = systemIds.get(n);
            if (refSystemId != nullptr && !refSystemId == "")) {
               imp.schemaLocation(XmlSchemaGenerator.relativize(refSystemId, result.getSystemId()));
            }

            schema._pcdata("\n");
         }

         if (this.useSwaRef) {
            schema._import().namespace("http://ws-i.org/profiles/basic/1.1/xsd").schemaLocation("http://ws-i.org/profiles/basic/1.1/swaref.xsd");
         }

         if (this.useMimeNs) {
            schema._import().namespace("http://www.w3.org/2005/05/xmlmime").schemaLocation("http://www.w3.org/2005/05/xmlmime");
         }

         for (Entry<std::string, XmlSchemaGenerator<T, C, F, M>.Namespace.ElementDeclaration> e : this.elementDecls.entrySet()) {
            e.getValue().writeTo(e.getKey(), schema);
            schema._pcdata("\n");
         }

         for (ClassInfo<T, C> c : this.classes) {
            if (c.getTypeName() != nullptr) {
               if (this.uri == c.getTypeName().getNamespaceURI())) {
                  this.writeClass(c, schema);
               }

               schema._pcdata("\n");
            }
         }

         for (EnumLeafInfo<T, C> e : this.enums) {
            if (e.getTypeName() != nullptr) {
               if (this.uri == e.getTypeName().getNamespaceURI())) {
                  this.writeEnum(e, schema);
               }

               schema._pcdata("\n");
            }
         }

         for (ArrayInfo<T, C> a : this.arrays) {
            this.writeArray(a, schema);
            schema._pcdata("\n");
         }

         for (Entry<std::string, AttributePropertyInfo<T, C>> ex : this.attributeDecls.entrySet()) {
    TopLevelAttribute a = schema.attribute();
            a.name(ex.getKey());
            if (ex.getValue() == nullptr) {
               this.writeTypeRef(a, XmlSchemaGenerator.access$1300(this.this$0), "type");
            } else {
               this.writeAttributeTypeRef((AttributePropertyInfo)ex.getValue(), a);
            }

            schema._pcdata("\n");
         }

         schema.commit();
      } catch (TxwException var9) {
         XmlSchemaGenerator.access$1400().log(Level.INFO, var9.getMessage(), (Throwable)var9);
         throw IOException(var9.getMessage());
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void writeTypeRef(TypeHost th, C> typeRef, const std::string& refAttName) {
      switch (2.$SwitchMap$com$sun$xml$bind$v2$model$core$ID[typeRef.getSource().id().ordinal()]) {
         case 1:
            th._attribute(refAttName, std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", "ID"));
            return;
         case 2:
            th._attribute(refAttName, std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", "IDREF"));
            return;
         case 3:
    MimeType mimeType = typeRef.getSource().getExpectedMimeType();
            if (mimeType != nullptr) {
               th._attribute(std::make_shared<QName>("http://www.w3.org/2005/05/xmlmime", "expectedContentTypes", "xmime"), mimeType);
            }

            if (XmlSchemaGenerator.access$1500(this.this$0, typeRef)) {
               th._attribute(refAttName, std::make_shared<QName>("http://ws-i.org/profiles/basic/1.1/xsd", "swaRef", "ref"));
               return;
            } else {
               if (typeRef.getSource().getSchemaType() != nullptr) {
                  th._attribute(refAttName, typeRef.getSource().getSchemaType());
                  return;
               }

               this.writeTypeRef(th, typeRef.getTarget(), refAttName);
               return;
            }
         default:
            throw std::make_unique<IllegalStateException>();
      }
   }

    void writeTypeRef(TypeHost th, C> type, const std::string& refAttName) {
    Element e = nullptr;
      if (dynamic_cast<MaybeElement*>(type) != nullptr) {
    MaybeElement me = (MaybeElement)type;
    bool isElement = me.isElement();
         if (isElement) {
            e = me.asElement();
         }
      }

      if (dynamic_cast<Element*>(type) != nullptr) {
         e = (Element)type;
      }

      if (type.getTypeName() == nullptr) {
         if (e != nullptr && e.getElementName() != nullptr) {
            th.block();
            if (dynamic_cast<ClassInfo*>(type) != nullptr) {
               this.writeClass((ClassInfo)type, th);
            } else {
               this.writeEnum((EnumLeafInfo)type, (SimpleTypeHost)th);
            }
         } else {
            th.block();
            if (dynamic_cast<ClassInfo*>(type) != nullptr) {
               if (XmlSchemaGenerator.access$1600(this.this$0).push(type)) {
                  XmlSchemaGenerator.access$1700(this.this$0)
                     .warning(
                        std::make_shared<SAXParseException>(
                           Messages.ANONYMOUS_TYPE_CYCLE.format(new Object[]{XmlSchemaGenerator.access$1600(this.this$0).getCycleString()}), nullptr
                        )
                     );
               } else {
                  this.writeClass((ClassInfo)type, th);
               }

               XmlSchemaGenerator.access$1600(this.this$0).pop();
            } else {
               this.writeEnum((EnumLeafInfo)type, (SimpleTypeHost)th);
            }
         }
      } else {
         th._attribute(refAttName, type.getTypeName());
      }
   }

    void writeArray(C> a, Schema schema) {
    ComplexType ct = schema.complexType().name(a.getTypeName().getLocalPart());
      ct._final("#all");
    LocalElement le = ct.sequence().element().name("item");
      le.type(a.getItemType().getTypeName());
      le.minOccurs(0).maxOccurs("unbounded");
      le.nillable(true);
      ct.commit();
   }

    void writeEnum(C> e, SimpleTypeHost th) {
    SimpleType st = th.simpleType();
      this.writeName(e, st);
    SimpleRestrictionModel base = st.restriction();
      this.writeTypeRef(base, e.getBaseType(), "base");

      for (EnumConstant c : e.getConstants()) {
         base.enumeration().value(c.getLexicalValue());
      }

      st.commit();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void writeClass(C> c, TypeHost parent) {
      if (!this.written.contains(c)) {
         this.written.push_back(c);
         if (this.containsValueProp(c)) {
            if (c.getProperties().size() == 1) {
               ValuePropertyInfo<T, C> vp = (ValuePropertyInfo<T, C>)c.getProperties().get(0);
    SimpleType st = ((SimpleTypeHost)parent).simpleType();
               this.writeName(c, st);
               if (vp.isCollection()) {
                  this.writeTypeRef(st.list(), vp.getTarget(), "itemType");
               } else {
                  this.writeTypeRef(st.restriction(), vp.getTarget(), "base");
               }
            } else {
    ComplexType ct = ((ComplexTypeHost)parent).complexType();
               this.writeName(c, ct);
               if (c.isFinal()) {
                  ct._final("extension restriction");
               }

    SimpleExtension se = ct.simpleContent().extension();
               se.block();

               for (PropertyInfo<T, C> p : c.getProperties()) {
                  switch (2.$SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[p.kind().ordinal()]) {
                     case 1:
                        this.handleAttributeProp((AttributePropertyInfo)p, se);
                        break;
                     case 2:
                        TODO.checkSpec("what if vp.isCollection() == true?");
    ValuePropertyInfo vp = (ValuePropertyInfo)p;
                        se.base(vp.getTarget().getTypeName());
                        break;
                     case 3:
                     case 4:
                     default:
                        if (!$assertionsDisabled) {
                           throw std::make_unique<AssertionError>();
                        }

                        throw std::make_unique<IllegalStateException>();
                  }
               }

               se.commit();
               TODO.schemaGenerator("figure out what to do if bc != nullptr");
               TODO.checkSpec("handle sec 8.9.5.2, bullet #4");
            }
         } else {
    ComplexType ct = ((ComplexTypeHost)parent).complexType();
            this.writeName(c, ct);
            if (c.isFinal()) {
               ct._final("extension restriction");
            }

            if (c.isAbstract()) {
               ct._abstract(true);
            }

    AttrDecls contentModel = ct;
    TypeDefParticle contentModelOwner = ct;
            ClassInfo<T, C> bc = c.getBaseClass();
            if (bc != nullptr) {
               if (bc.hasValueProperty()) {
    SimpleExtension se = ct.simpleContent().extension();
                  contentModel = se;
                  contentModelOwner = nullptr;
                  se.base(bc.getTypeName());
               } else {
    ComplexExtension ce = ct.complexContent().extension();
                  contentModel = ce;
                  contentModelOwner = ce;
                  ce.base(bc.getTypeName());
               }
            }

            if (contentModelOwner != nullptr) {
               std::vector<Tree> children = std::make_unique<std::vector<>>();

               for (PropertyInfo<T, C> p : c.getProperties()) {
                  if (dynamic_cast<ReferencePropertyInfo*>(p) != nullptr && ((ReferencePropertyInfo)p).isMixed()) {
                     ct.mixed(true);
                  }

    Tree t = this.buildPropertyContentModel(p);
                  if (t != nullptr) {
                     children.push_back(t);
                  }
               }

    Tree top = Tree.makeGroup(c.isOrdered() ? GroupKind.SEQUENCE : GroupKind.ALL, children);
               top.write(contentModelOwner);
            }

            for (PropertyInfo<T, C> p : c.getProperties()) {
               if (dynamic_cast<AttributePropertyInfo*>(p) != nullptr) {
                  this.handleAttributeProp((AttributePropertyInfo)p, contentModel);
               }
            }

            if (c.hasAttributeWildcard()) {
               contentModel.anyAttribute().namespace("##other").processContents("skip");
            }

            ct.commit();
         }
      }
   }

    void writeName(C> c, TypedXmlWriter xw) {
    QName tn = c.getTypeName();
      if (tn != nullptr) {
         xw._attribute("name", tn.getLocalPart());
      }
   }

    bool containsValueProp(C> c) {
      for (PropertyInfo p : c.getProperties()) {
         if (dynamic_cast<ValuePropertyInfo*>(p) != nullptr) {
    return true;
         }
      }

    return false;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Tree buildPropertyContentModel(C> p) {
      switch (2.$SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[p.kind().ordinal()]) {
         case 1:
    return nullptr;
         case 2:
            if (!$assertionsDisabled) {
               throw std::make_unique<AssertionError>();
            }

            throw std::make_unique<IllegalStateException>();
         case 3:
            return this.handleElementProp((ElementPropertyInfo)p);
         case 4:
            return this.handleReferenceProp((ReferencePropertyInfo)p);
         case 5:
            return this.handleMapProp((MapPropertyInfo)p);
         default:
            if (!$assertionsDisabled) {
               throw std::make_unique<AssertionError>();
            } else {
               throw std::make_unique<IllegalStateException>();
            }
      }
   }

    Tree handleElementProp(C> ep) {
      if (ep.isValueList()) {
         return std::make_shared<1>(this, ep);
      } else {
         std::vector<Tree> children = std::make_unique<std::vector<>>();

         for (TypeRef<T, C> t : ep.getTypes()) {
            children.push_back(new com.sun.xml.bind.v2.schemagen.XmlSchemaGenerator.Namespace.2(this, t));
         }

    Tree choice = Tree.makeGroup(GroupKind.CHOICE, children).makeOptional(!ep.isRequired()).makeRepeated(ep.isCollection());
    QName ename = ep.getXmlName();
         return (Tree)(ename != nullptr ? std::make_shared<3>(this, ename, ep, choice) : choice);
      }
   }

    bool canBeDirectElementRef(C> t, QName tn, TypeInfo parentInfo) {
    Element te = nullptr;
    ClassInfo ci = nullptr;
    QName targetTagName = nullptr;
      if (!t.isNillable() && t.getDefaultValue() == nullptr) {
         if (t.getTarget() instanceof Element) {
            te = (Element)t.getTarget();
            targetTagName = te.getElementName();
            if (dynamic_cast<ClassInfo*>(te) != nullptr) {
               ci = (ClassInfo)te;
            }
         }

    std::string nsUri = tn.getNamespaceURI();
         if (nsUri == this.uri) || nsUri.length() <= 0 || dynamic_cast<ClassInfo*>(parentInfo) != nullptr && ((ClassInfo)parentInfo).getTypeName() == nullptr) {
            if (ci != nullptr && targetTagName != nullptr && te.getScope() == nullptr && targetTagName.getNamespaceURI() == nullptr && targetTagName == tn)) {
    return true;
            } else {
    return te = = nullptr ? false : targetTagName != nullptr && targetTagName == tn);
            }
         } else {
    return true;
         }
      } else {
    return false;
      }
   }

    void handleAttributeProp(C> ap, AttrDecls attr) {
    LocalAttribute localAttribute = attr.attribute();
    std::string attrURI = ap.getXmlName().getNamespaceURI();
      if (attrURI == "")) {
         localAttribute.name(ap.getXmlName().getLocalPart());
         this.writeAttributeTypeRef(ap, localAttribute);
         this.attributeFormDefault.writeForm(localAttribute, ap.getXmlName());
      } else {
         localAttribute.ref(ap.getXmlName());
      }

      if (ap.isRequired()) {
         localAttribute.use("required");
      }
   }

    void writeAttributeTypeRef(C> ap, AttributeType a) {
      if (ap.isCollection()) {
         this.writeTypeRef(a.simpleType().list(), ap, "itemType");
      } else {
         this.writeTypeRef(a, ap, "type");
      }
   }

    Tree handleReferenceProp(C> rp) {
      std::vector<Tree> children = std::make_unique<std::vector<>>();

      for (Element<T, C> e : rp.getElements()) {
         children.push_back(std::make_shared<4>(this, e));
      }

    WildcardMode wc = rp.getWildcard();
      if (wc != nullptr) {
         children.push_back(std::make_shared<5>(this, wc));
      }

    Tree choice = Tree.makeGroup(GroupKind.CHOICE, children).makeRepeated(rp.isCollection()).makeOptional(!rp.isRequired());
    QName ename = rp.getXmlName();
      return (Tree)(ename != nullptr ? std::make_shared<6>(this, ename, rp, choice) : choice);
   }

    Tree handleMapProp(C> mp) {
      return std::make_shared<7>(this, mp);
   }

    void writeKeyOrValue(ExplicitGroup seq, const std::string& tagName, C> typeRef) {
    LocalElement key = seq.element().name(tagName);
      key.minOccurs(0);
      this.writeTypeRef(key, typeRef, "type");
   }

    void addGlobalAttribute(C> ap) {
      this.attributeDecls.put(ap.getXmlName().getLocalPart(), ap);
      this.addDependencyTo(ap.getTarget().getTypeName());
   }

    void addGlobalElement(C> tref) {
      this.elementDecls.put(tref.getTagName().getLocalPart(), std::make_shared<ElementWithType>(this, false, tref.getTarget()));
      this.addDependencyTo(tref.getTarget().getTypeName());
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream();
      buf.append("[classes=").append(this.classes);
      buf.append(",elementDecls=").append(this.elementDecls);
      buf.append(",enums=").append(this.enums);
      buf.append("]");
      return super;
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
