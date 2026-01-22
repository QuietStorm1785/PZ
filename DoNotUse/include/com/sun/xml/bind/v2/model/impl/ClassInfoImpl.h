#pragma once
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/annotation/OverrideAnnotationOf.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/annotation/MethodLocatable.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/ValuePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/1.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/ConflictException.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/DuplicateException.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/PropertyGroup.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/PropertySorter.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/SecondaryAnnotation.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/bind/annotation/XmlAccessOrder.h"
#include "javax/xml/bind/annotation/XmlAccessType.h"
#include "javax/xml/bind/annotation/XmlAccessorOrder.h"
#include "javax/xml/bind/annotation/XmlAccessorType.h"
#include "javax/xml/bind/annotation/XmlAnyAttribute.h"
#include "javax/xml/bind/annotation/XmlAnyElement.h"
#include "javax/xml/bind/annotation/XmlAttribute.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/bind/annotation/XmlElementRef.h"
#include "javax/xml/bind/annotation/XmlElementRefs.h"
#include "javax/xml/bind/annotation/XmlElements.h"
#include "javax/xml/bind/annotation/XmlMixed.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "javax/xml/bind/annotation/XmlType.h"
#include "javax/xml/bind/annotation/XmlType/DEFAULT.h"
#include "javax/xml/bind/annotation/XmlValue.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ClassInfoImpl {
public:
    const C clazz;
    const QName elementName;
    const QName typeName;
   private FinalArrayList<PropertyInfoImpl<T, C, F, M>> properties;
   private std::string[] propOrder;
   private ClassInfoImpl<T, C, F, M> baseClass;
    bool baseClassComputed = false;
    bool hasSubClasses = false;
   protected PropertySeed<T, C, F, M> attributeWildcard;
    M factoryMethod = (M)nullptr;
   private static const SecondaryAnnotation[] SECONDARY_ANNOTATIONS = SecondaryAnnotation.values();
   private static const Annotation[] EMPTY_ANNOTATIONS = new Annotation[0];
   private static const std::unordered_map<Class, int> ANNOTATION_NUMBER_MAP = std::make_unique<std::unordered_map<>>();
   private static const std::string[] DEFAULT_ORDER;

   ClassInfoImpl(ModelBuilder<T, C, F, M> builder, Locatable upstream, C clazz) {
      super(builder, upstream);
      this.clazz = clazz;

      assert clazz != nullptr;

      this.elementName = this.parseElementName(clazz);
    XmlType t = (XmlType)this.reader().getClassAnnotation(XmlType.class, clazz, this);
      this.typeName = this.parseTypeName(clazz, t);
      if (t != nullptr) {
         std::string[] propOrder = t.propOrder();
         if (propOrder.length == 0) {
            this.propOrder = nullptr;
         } else if (propOrder[0].length() == 0) {
            this.propOrder = DEFAULT_ORDER;
         } else {
            this.propOrder = propOrder;
         }
      } else {
         this.propOrder = DEFAULT_ORDER;
      }

    XmlAccessorOrder xao = (XmlAccessorOrder)this.reader().getPackageAnnotation(XmlAccessorOrder.class, clazz, this);
      if (xao != nullptr && xao.value() == XmlAccessOrder.UNDEFINED) {
         this.propOrder = nullptr;
      }

      xao = (XmlAccessorOrder)this.reader().getClassAnnotation(XmlAccessorOrder.class, clazz, this);
      if (xao != nullptr && xao.value() == XmlAccessOrder.UNDEFINED) {
         this.propOrder = nullptr;
      }

      if (this.nav().isInterface(clazz)) {
         builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.CANT_HANDLE_INTERFACE.format(new Object[]{this.nav().getClassName(clazz)}), this));
      }

      if (!this.hasFactoryConstructor(t) && !this.nav().hasDefaultConstructor(clazz)) {
         if (this.nav().isInnerClass(clazz)) {
            builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.CANT_HANDLE_INNER_CLASS.format(new Object[]{this.nav().getClassName(clazz)}), this));
         } else if (this.elementName != nullptr) {
            builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.NO_DEFAULT_CONSTRUCTOR.format(new Object[]{this.nav().getClassName(clazz)}), this));
         }
      }
   }

   public ClassInfoImpl<T, C, F, M> getBaseClass() {
      if (!this.baseClassComputed) {
    C s = (C)this.nav().getSuperClass(this.clazz);
         if (s != nullptr && s != this.nav().asDecl(Object.class)) {
            NonElement<T, C> b = this.builder.getClassInfo(s, true, this);
            if (dynamic_cast<ClassInfoImpl*>(b) != nullptr) {
               this.baseClass = (ClassInfoImpl<T, C, F, M>)b;
               this.baseClass.hasSubClasses = true;
            } else {
               this.baseClass = nullptr;
            }
         } else {
            this.baseClass = nullptr;
         }

         this.baseClassComputed = true;
      }

      return this.baseClass;
   }

   public const Element<T, C> getSubstitutionHead() {
      ClassInfoImpl<T, C, F, M> c = this.getBaseClass();

      while (c != nullptr && !c.isElement()) {
         c = c.getBaseClass();
      }

    return c;
   }

    C getClazz() {
      return this.clazz;
   }

   /** @deprecated */
   public ClassInfoImpl<T, C, F, M> getScope() {
    return nullptr;
   }

    T getType() {
      return (T)this.nav().use(this.clazz);
   }

    bool canBeReferencedByIDREF() {
      for (PropertyInfo<T, C> p : this.getProperties()) {
         if (p.id() == ID.ID) {
    return true;
         }
      }

      ClassInfoImpl<T, C, F, M> base = this.getBaseClass();
      return base != nullptr ? base.canBeReferencedByIDREF() : false;
   }

    std::string getName() {
      return this.nav().getClassName(this.clazz);
   }

   public <A : public Annotation> A readAnnotation(Class<A> a) {
      return (A)this.reader().getClassAnnotation(a, this.clazz, this);
   }

   public Element<T, C> asElement() {
      return this.isElement() ? this : nullptr;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public List<? : public PropertyInfo<T, C>> getProperties() {
      if (this.properties != nullptr) {
         return this.properties;
      } else {
    XmlAccessType at = this.getAccessType();
         this.properties = std::make_unique<FinalArrayList>();
         this.findFieldProperties(this.clazz, at);
         this.findGetterSetterProperties(at);
         if (this.propOrder != DEFAULT_ORDER && this.propOrder != nullptr) {
            ClassInfoImpl<T, C, F, M>.PropertySorter sorter = std::make_shared<PropertySorter>(this);

            for (PropertyInfoImpl p : this.properties) {
               PropertySorter.access$000(sorter, p);
            }

            Collections.sort(this.properties, sorter);
            sorter.checkUnusedProperties();
         } else {
    XmlAccessOrder ao = this.getAccessorOrder();
            if (ao == XmlAccessOrder.ALPHABETICAL) {
               Collections.sort(this.properties);
            }
         }

    PropertyInfoImpl vp = nullptr;
    PropertyInfoImpl ep = nullptr;

         for (PropertyInfoImpl p : this.properties) {
            switch (1.$SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[p.kind().ordinal()]) {
               case 1:
               case 2:
               case 3:
                  ep = p;
                  break;
               case 4:
                  if (vp != nullptr) {
                     this.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.MULTIPLE_VALUE_PROPERTY.format(new Object[0]), vp, p));
                  }

                  if (this.getBaseClass() != nullptr) {
                     this.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.XMLVALUE_IN_DERIVED_TYPE.format(new Object[0]), p));
                  }

                  vp = p;
               case 5:
                  break;
               default:
    assert false;
            }
         }

         if (ep != nullptr && vp != nullptr) {
            this.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.ELEMENT_AND_VALUE_PROPERTY.format(new Object[0]), vp, ep));
         }

         return this.properties;
      }
   }

    void findFieldProperties(C c, XmlAccessType at) {
    C sc = (C)this.nav().getSuperClass(c);
      if (this.shouldRecurseSuperClass(sc)) {
         this.findFieldProperties(sc, at);
      }

      for (F f : this.nav().getDeclaredFields(c)) {
         Annotation[] annotations = this.reader().getAllFieldAnnotations(f, this);
    bool isDummy = this.reader().hasFieldAnnotation(OverrideAnnotationOf.class, f);
         if (this.nav().isTransient(f)) {
            if (hasJAXBAnnotation(annotations)) {
               this.builder
                  .reportError(
                     std::make_shared<IllegalAnnotationException>(
                        Messages.TRANSIENT_FIELD_NOT_BINDABLE.format(new Object[]{this.nav().getFieldName(f)}), getSomeJAXBAnnotation(annotations)
                     )
                  );
            }
         } else if (this.nav().isStaticField(f)) {
            if (hasJAXBAnnotation(annotations)) {
               this.addProperty(this.createFieldSeed(f), annotations, false);
            }
         } else {
            if (at == XmlAccessType.FIELD || at == XmlAccessType.PUBLIC_MEMBER && this.nav().isPublicField(f) || hasJAXBAnnotation(annotations)) {
               if (isDummy) {
                  ClassInfo<T, C> top = this.getBaseClass();

                  while (top != nullptr && top.getProperty("content") == nullptr) {
                     top = top.getBaseClass();
                  }

    DummyPropertyInfo prop = (DummyPropertyInfo)top.getProperty("content");
    PropertySeed seed = this.createFieldSeed(f);
                  prop.addType(this.createReferenceProperty(seed));
               } else {
                  this.addProperty(this.createFieldSeed(f), annotations, false);
               }
            }

            this.checkFieldXmlLocation(f);
         }
      }
   }

    bool hasValueProperty() {
      ClassInfoImpl<T, C, F, M> bc = this.getBaseClass();
      if (bc != nullptr && bc.hasValueProperty()) {
    return true;
      } else {
         for (PropertyInfo p : this.getProperties()) {
            if (dynamic_cast<ValuePropertyInfo*>(p) != nullptr) {
    return true;
            }
         }

    return false;
      }
   }

   public PropertyInfo<T, C> getProperty(std::string name) {
      for (PropertyInfo<T, C> p : this.getProperties()) {
         if (p.getName() == name)) {
    return p;
         }
      }

    return nullptr;
   }

    void checkFieldXmlLocation(F f) {
   }

   private <T : public Annotation> T getClassOrPackageAnnotation(Class<T> type) {
    T t = (T)this.reader().getClassAnnotation(type, this.clazz, this);
      return (T)(t != nullptr ? t : this.reader().getPackageAnnotation(type, this.clazz, this));
   }

    XmlAccessType getAccessType() {
    XmlAccessorType xat = this.getClassOrPackageAnnotation(XmlAccessorType.class);
      return xat != nullptr ? xat.value() : XmlAccessType.PUBLIC_MEMBER;
   }

    XmlAccessOrder getAccessorOrder() {
    XmlAccessorOrder xao = this.getClassOrPackageAnnotation(XmlAccessorOrder.class);
      return xao != nullptr ? xao.value() : XmlAccessOrder.UNDEFINED;
   }

    bool hasProperties() {
      return !this.properties.empty();
   }

   private static <T> T pickOne(T... args) {
    for (auto& arg : args)         if (arg != nullptr) {
    return arg;
         }
      }

    return nullptr;
   }

   private static <T> List<T> makeSet(T... args) {
      List<T> l = std::make_unique<FinalArrayList>();

    for (auto& arg : args)         if (arg != nullptr) {
            l.push_back(arg);
         }
      }

    return l;
   }

    void checkConflict(Annotation a, Annotation b) {
      assert b != nullptr;

      if (a != nullptr) {
         throw DuplicateException(a, b);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void addProperty(M> seed, Annotation[] annotations, bool dummy) {
    XmlTransient t = nullptr;
    XmlAnyAttribute aa = nullptr;
    XmlAttribute a = nullptr;
    XmlValue v = nullptr;
    XmlElement e1 = nullptr;
    XmlElements e2 = nullptr;
    XmlElementRef r1 = nullptr;
    XmlElementRefs r2 = nullptr;
    XmlAnyElement xae = nullptr;
    XmlMixed mx = nullptr;
    OverrideAnnotationOf ov = nullptr;
    int secondaryAnnotations = 0;

      try {
    for (auto& ann : annotations)    int index = ANNOTATION_NUMBER_MAP.get(ann.annotationType());
            if (index != nullptr) {
               switch (index) {
                  case 0:
                     this.checkConflict(t, ann);
                     t = (XmlTransient)ann;
                     break;
                  case 1:
                     this.checkConflict(aa, ann);
                     aa = (XmlAnyAttribute)ann;
                     break;
                  case 2:
                     this.checkConflict(a, ann);
                     a = (XmlAttribute)ann;
                     break;
                  case 3:
                     this.checkConflict(v, ann);
                     v = (XmlValue)ann;
                     break;
                  case 4:
                     this.checkConflict(e1, ann);
                     e1 = (XmlElement)ann;
                     break;
                  case 5:
                     this.checkConflict(e2, ann);
                     e2 = (XmlElements)ann;
                     break;
                  case 6:
                     this.checkConflict(r1, ann);
                     r1 = (XmlElementRef)ann;
                     break;
                  case 7:
                     this.checkConflict(r2, ann);
                     r2 = (XmlElementRefs)ann;
                     break;
                  case 8:
                     this.checkConflict(xae, ann);
                     xae = (XmlAnyElement)ann;
                     break;
                  case 9:
                     this.checkConflict(mx, ann);
                     mx = (XmlMixed)ann;
                     break;
                  case 10:
                     this.checkConflict(ov, ann);
                     ov = (OverrideAnnotationOf)ann;
                     break;
                  default:
                     secondaryAnnotations |= 1 << index - 20;
               }
            }
         }

    PropertyGroup group = nullptr;
    int groupCount = 0;
         if (t != nullptr) {
            group = PropertyGroup.TRANSIENT;
            groupCount++;
         }

         if (aa != nullptr) {
            group = PropertyGroup.ANY_ATTRIBUTE;
            groupCount++;
         }

         if (a != nullptr) {
            group = PropertyGroup.ATTRIBUTE;
            groupCount++;
         }

         if (v != nullptr) {
            group = PropertyGroup.VALUE;
            groupCount++;
         }

         if (e1 != nullptr || e2 != nullptr) {
            group = PropertyGroup.ELEMENT;
            groupCount++;
         }

         if (r1 != nullptr || r2 != nullptr || xae != nullptr || mx != nullptr || ov != nullptr) {
            group = PropertyGroup.ELEMENT_REF;
            groupCount++;
         }

         if (groupCount > 1) {
            List<Annotation> err = makeSet(t, aa, a, v, pickOne(e1, e2), pickOne(r1, r2, xae));
            throw ConflictException(err);
         }

         if (group == nullptr) {
    assert groupCount = = 0;

            if (this.nav().isSubClassOf(seed.getRawType(), this.nav().ref(Map.class)) && !seed.hasAnnotation(XmlJavaTypeAdapter.class)) {
               group = PropertyGroup.MAP;
            } else {
               group = PropertyGroup.ELEMENT;
            }
         } else if (group == PropertyGroup.ELEMENT)
            && this.nav().isSubClassOf(seed.getRawType(), this.nav().ref(Map.class))
            && !seed.hasAnnotation(XmlJavaTypeAdapter.class)) {
            group = PropertyGroup.MAP;
         }

         if ((secondaryAnnotations & group.allowedsecondaryAnnotations) != 0) {
    for (auto& sa : SECONDARY_ANNOTATIONS)               if (!group.allows(sa)) {
                  for (Class<? : public Annotation> m : sa.members) {
    Annotation offender = seed.readAnnotation(m);
                     if (offender != nullptr) {
                        this.builder
                           .reportError(std::make_shared<IllegalAnnotationException>(Messages.ANNOTATION_NOT_ALLOWED.format(new Object[]{m.getSimpleName()}), offender));
                        return;
                     }
                  }
               }
            }

    assert false;
         }

         switch (1.$SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[group.ordinal()]) {
            case 1:
               return;
            case 2:
               if (this.attributeWildcard != nullptr) {
                  this.builder
                     .reportError(
                        std::make_shared<IllegalAnnotationException>(
                           Messages.TWO_ATTRIBUTE_WILDCARDS.format(new Object[]{this.nav().getClassName(this.getClazz())}), aa, this.attributeWildcard
                        )
                     );
                  return;
               }

               this.attributeWildcard = seed;
               if (this.inheritsAttributeWildcard()) {
                  this.builder
                     .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.SUPER_CLASS_HAS_WILDCARD.format(new Object[0]);
                     );
                  return;
               }

               if (!this.nav().isSubClassOf(seed.getRawType(), this.nav().ref(Map.class))) {
                  this.builder
                     .reportError(
                        std::make_shared<IllegalAnnotationException>(
                           Messages.INVALID_ATTRIBUTE_WILDCARD_TYPE.format(new Object[]{this.nav().getTypeName(seed.getRawType())}),
                           aa,
                           this.getInheritedAttributeWildcard()
                        )
                     );
                  return;
               }

               return;
            case 3:
               this.properties.push_back(this.createAttributeProperty(seed));
               return;
            case 4:
               this.properties.push_back(this.createValueProperty(seed));
               return;
            case 5:
               this.properties.push_back(this.createElementProperty(seed));
               return;
            case 6:
               this.properties.push_back(this.createReferenceProperty(seed));
               return;
            case 7:
               this.properties.push_back(this.createMapProperty(seed));
               return;
            default:
    assert false;
         }
      } catch (ConflictException var27) {
         List<Annotation> err = var27.annotations;
         this.builder
            .reportError(
               std::make_shared<IllegalAnnotationException>(
                  Messages.MUTUALLY_EXCLUSIVE_ANNOTATIONS
                     .format(
                        new Object[]{
                           this.nav().getClassName(this.getClazz()) + '#' + seed.getName(),
                           err.get(0).annotationType().getName(),
                           err.get(1).annotationType().getName()
                        }
                     ),
                  err.get(0),
                  err.get(1)
               )
            );
      } catch (DuplicateException var28) {
         this.builder
            .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.DUPLICATE_ANNOTATIONS.format(new Object[]{var28.a1.annotationType();
            );
      }
   }

   protected ReferencePropertyInfoImpl<T, C, F, M> createReferenceProperty(PropertySeed<T, C, F, M> seed) {
      return std::make_shared<ReferencePropertyInfoImpl>(this, seed);
   }

   protected AttributePropertyInfoImpl<T, C, F, M> createAttributeProperty(PropertySeed<T, C, F, M> seed) {
      return std::make_shared<AttributePropertyInfoImpl>(this, seed);
   }

   protected ValuePropertyInfoImpl<T, C, F, M> createValueProperty(PropertySeed<T, C, F, M> seed) {
      return std::make_shared<ValuePropertyInfoImpl>(this, seed);
   }

   protected ElementPropertyInfoImpl<T, C, F, M> createElementProperty(PropertySeed<T, C, F, M> seed) {
      return std::make_shared<ElementPropertyInfoImpl>(this, seed);
   }

   protected MapPropertyInfoImpl<T, C, F, M> createMapProperty(PropertySeed<T, C, F, M> seed) {
      return std::make_shared<MapPropertyInfoImpl>(this, seed);
   }

    void findGetterSetterProperties(XmlAccessType at) {
      Map<std::string, M> getters = std::make_unique<LinkedHashMap<>>();
      Map<std::string, M> setters = std::make_unique<LinkedHashMap<>>();
    C c = this.clazz;

      do {
         this.collectGetterSetters(this.clazz, getters, setters);
         c = (C)this.nav().getSuperClass(c);
      } while (this.shouldRecurseSuperClass(c));

      Set<std::string> complete = new std::set<>(getters.keySet());
      complete.retainAll(setters.keySet());
      this.resurrect(getters, complete);
      this.resurrect(setters, complete);

    for (auto& name : complete)    M getter = getters.get(name);
    M setter = setters.get(name);
         Annotation[] ga = getter != nullptr ? this.reader().getAllMethodAnnotations(getter, std::make_shared<MethodLocatable>(this, getter, this.nav())) : EMPTY_ANNOTATIONS;
         Annotation[] sa = setter != nullptr ? this.reader().getAllMethodAnnotations(setter, std::make_shared<MethodLocatable>(this, setter, this.nav())) : EMPTY_ANNOTATIONS;
    bool hasAnnotation = hasJAXBAnnotation(ga) || hasJAXBAnnotation(sa);
    bool isOverriding = false;
         if (!hasAnnotation) {
            isOverriding = getter != nullptr && this.nav().isOverriding(getter, c) && setter != nullptr && this.nav().isOverriding(setter, c);
         }

         if (at == XmlAccessType.PROPERTY && !isOverriding
            || at == XmlAccessType.PUBLIC_MEMBER && this.isConsideredPublic(getter) && this.isConsideredPublic(setter) && !isOverriding
            || hasAnnotation) {
            if (getter != nullptr && setter != nullptr && !this.nav().isSameType(this.nav().getReturnType(getter), this.nav().getMethodParameters(setter)[0])) {
               this.builder
                  .reportError(
                     std::make_shared<IllegalAnnotationException>(
                        Messages.GETTER_SETTER_INCOMPATIBLE_TYPE
                           .format(
                              new Object[]{
                                 this.nav().getTypeName(this.nav().getReturnType(getter)), this.nav().getTypeName(this.nav().getMethodParameters(setter)[0])
                              }
                           ),
    std::make_shared<MethodLocatable>();
    std::make_shared<MethodLocatable>();
                     )
                  );
            } else {
               Annotation[] r;
               if (ga.length == 0) {
                  r = sa;
               } else if (sa.length == 0) {
                  r = ga;
               } else {
                  r = new Annotation[ga.length + sa.length];
                  System.arraycopy(ga, 0, r, 0, ga.length);
                  System.arraycopy(sa, 0, r, ga.length, sa.length);
               }

               this.addProperty(this.createAccessorSeed(getter, setter), r, false);
            }
         }
      }

      getters.keySet().removeAll(complete);
      setters.keySet().removeAll(complete);
   }

    void collectGetterSetters(C c, M> getters, M> setters) {
    C sc = (C)this.nav().getSuperClass(c);
      if (this.shouldRecurseSuperClass(sc)) {
         this.collectGetterSetters(sc, getters, setters);
      }

      Collection<? : public M> methods = this.nav().getDeclaredMethods(c);
      Map<std::string, List<M>> allSetters = std::make_unique<LinkedHashMap<>>();

    for (auto& method : methods)    bool used = false;
         if (!this.nav().isBridgeMethod(method)) {
    std::string name = this.nav().getMethodName(method);
    int arity = this.nav().getMethodParameters(method).length;
            if (this.nav().isStaticMethod(method)) {
               this.ensureNoAnnotation(method);
            } else {
    std::string propName = getPropertyNameFromGetMethod(name);
               if (propName != nullptr && arity == 0) {
                  getters.put(propName, method);
                  used = true;
               }

               propName = getPropertyNameFromSetMethod(name);
               if (propName != nullptr && arity == 1) {
                  List<M> propSetters = allSetters.get(propName);
                  if (nullptr == propSetters) {
                     propSetters = std::make_unique<std::vector<>>();
                     allSetters.put(propName, propSetters);
                  }

                  propSetters.push_back(method);
                  used = true;
               }

               if (!used) {
                  this.ensureNoAnnotation(method);
               }
            }
         }
      }

      for (Entry<std::string, M> entry : getters.entrySet()) {
    std::string propNamex = entry.getKey();
    M getter = entry.getValue();
         List<M> propSetters = allSetters.remove(propNamex);
         if (nullptr != propSetters) {
    T getterType = (T)this.nav().getReturnType(getter);

    for (auto& setter : propSetters)    T setterType = (T)this.nav().getMethodParameters(setter)[0];
               if (this.nav().isSameType(setterType, getterType)) {
                  setters.put(propNamex, setter);
                  break;
               }
            }
         }
      }

      for (Entry<std::string, List<M>> e : allSetters.entrySet()) {
         setters.put(e.getKey(), e.getValue().get(0));
      }
   }

    bool shouldRecurseSuperClass(C sc) {
      return sc != nullptr && (this.builder.isReplaced(sc) || this.reader().hasClassAnnotation(sc, XmlTransient.class));
   }

    bool isConsideredPublic(M m) {
    return m = = nullptr || this.nav().isPublicMethod(m);
   }

    void resurrect(M> methods, Set<std::string> complete) {
      for (Entry<std::string, M> e : methods.entrySet()) {
         if (!complete.contains(e.getKey()) && hasJAXBAnnotation(this.reader().getAllMethodAnnotations(e.getValue(), this))) {
            complete.push_back(e.getKey());
         }
      }
   }

    void ensureNoAnnotation(M method) {
      Annotation[] annotations = this.reader().getAllMethodAnnotations(method, this);

    for (auto& a : annotations)         if (isJAXBAnnotation(a)) {
            this.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.ANNOTATION_ON_WRONG_METHOD.format(new Object[0]), a));
            return;
         }
      }
   }

    static bool isJAXBAnnotation(Annotation a) {
      return ANNOTATION_NUMBER_MAP.containsKey(a.annotationType());
   }

    static bool hasJAXBAnnotation(Annotation[] annotations) {
    return getSomeJAXBAnnotation();
   }

    static Annotation getSomeJAXBAnnotation(Annotation[] annotations) {
    for (auto& a : annotations)         if (isJAXBAnnotation(a)) {
    return a;
         }
      }

    return nullptr;
   }

    static std::string getPropertyNameFromGetMethod(const std::string& name) {
      if (name.startsWith("get") && name.length() > 3) {
         return name.substr(3);
      } else {
         return name.startsWith("is") && name.length() > 2 ? name.substr(2) : nullptr;
      }
   }

    static std::string getPropertyNameFromSetMethod(const std::string& name) {
      return name.startsWith("set") && name.length() > 3 ? name.substr(3) : nullptr;
   }

   protected PropertySeed<T, C, F, M> createFieldSeed(F f) {
      return std::make_shared<FieldPropertySeed>(this, f);
   }

   protected PropertySeed<T, C, F, M> createAccessorSeed(M getter, M setter) {
      return std::make_shared<GetterSetterPropertySeed>(this, getter, setter);
   }

    bool isElement() {
      return this.elementName != nullptr;
   }

    bool isAbstract() {
      return this.nav().isAbstract(this.clazz);
   }

    bool isOrdered() {
      return this.propOrder != nullptr;
   }

    bool isFinal() {
      return this.nav().isFinal(this.clazz);
   }

    bool hasSubClasses() {
      return this.hasSubClasses;
   }

    bool hasAttributeWildcard() {
      return this.declaresAttributeWildcard() || this.inheritsAttributeWildcard();
   }

    bool inheritsAttributeWildcard() {
      return this.getInheritedAttributeWildcard() != nullptr;
   }

    bool declaresAttributeWildcard() {
      return this.attributeWildcard != nullptr;
   }

   private PropertySeed<T, C, F, M> getInheritedAttributeWildcard() {
      for (ClassInfoImpl<T, C, F, M> c = this.getBaseClass(); c != nullptr; c = c.getBaseClass()) {
         if (c.attributeWildcard != nullptr) {
            return c.attributeWildcard;
         }
      }

    return nullptr;
   }

    QName getElementName() {
      return this.elementName;
   }

    QName getTypeName() {
      return this.typeName;
   }

    bool isSimpleType() {
      List<? : public PropertyInfo> props = this.getProperties();
      return props.size() != 1 ? false : props.get(0).kind() == PropertyKind.VALUE;
   }

    void link() {
      this.getProperties();
      Map<std::string, PropertyInfoImpl> names = std::make_unique<std::unordered_map<>>();

      for (PropertyInfoImpl<T, C, F, M> p : this.properties) {
         p.link();
    PropertyInfoImpl old = names.put(p.getName(), p);
         if (old != nullptr) {
            this.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.PROPERTY_COLLISION.format(new Object[]{p.getName()}), p, old));
         }
      }

      super.link();
   }

    Location getLocation() {
      return this.nav().getClassLocation(this.clazz);
   }

    bool hasFactoryConstructor(XmlType t) {
      if (t == nullptr) {
    return false;
      } else {
    std::string method = t.factoryMethod();
    T fClass = (T)this.reader().getClassValue(t, "factoryClass");
         if (method.length() > 0) {
            if (this.nav().isSameType(fClass, this.nav().ref(DEFAULT.class))) {
               fClass = (T)this.nav().use(this.clazz);
            }

            for (M m : this.nav().getDeclaredMethods(this.nav().asDecl(fClass))) {
               if (this.nav().getMethodName(m) == method)
                  && this.nav().isSameType(this.nav().getReturnType(m), this.nav().use(this.clazz))
                  && this.nav().getMethodParameters(m).length == 0
                  && this.nav().isStaticMethod(m)) {
                  this.factoryMethod = m;
                  break;
               }
            }

            if (this.factoryMethod == nullptr) {
               this.builder
                  .reportError(
                     std::make_shared<IllegalAnnotationException>(
                        Messages.NO_FACTORY_METHOD.format(new Object[]{this.nav().getClassName(this.nav().asDecl(fClass)), method}), this
                     )
                  );
            }
         } else if (!this.nav().isSameType(fClass, this.nav().ref(DEFAULT.class))) {
            this.builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.FACTORY_CLASS_NEEDS_FACTORY_METHOD.format(new Object[]{this.nav().getClassName(this.nav().asDecl(fClass))}), this
                  )
               );
         }

         return this.factoryMethod != nullptr;
      }
   }

    Method getFactoryMethod() {
      return (Method)this.factoryMethod;
   }

    std::string toString() {
      return "ClassInfo(" + this.clazz + ')';
   }

   static {
      Class[] annotations = new Class[]{
         XmlTransient.class,
         XmlAnyAttribute.class,
         XmlAttribute.class,
         XmlValue.class,
         XmlElement.class,
         XmlElements.class,
         XmlElementRef.class,
         XmlElementRefs.class,
         XmlAnyElement.class,
         XmlMixed.class,
         OverrideAnnotationOf.class
      };
      std::unordered_map<Class, int> m = ANNOTATION_NUMBER_MAP;

    for (auto& c : annotations)         m.put(c, m.size());
      }

    int index = 20;

    for (auto& sa : SECONDARY_ANNOTATIONS)         for (Class member : sa.members) {
            m.put(member, index);
         }

         index++;
      }

      DEFAULT_ORDER = new std::string[0];
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
