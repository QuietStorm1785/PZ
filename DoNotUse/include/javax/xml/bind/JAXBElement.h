#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBElement/GlobalScope.h"
#include "javax/xml/namespace/QName.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class JAXBElement {
public:
    const QName name;
   protected const Class<T> declaredType;
    const Class scope;
    T value;
    bool nil = false;
    static const long serialVersionUID = 1L;

    public JAXBElement(QName name, Class<T> declaredType, Class scope, T value) {
      if (declaredType != nullptr && name != nullptr) {
         this.declaredType = declaredType;
         if (scope == nullptr) {
            scope = GlobalScope.class;
         }

         this.scope = scope;
         this.name = name;
         this.setValue(value);
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    public JAXBElement(QName name, Class<T> declaredType, T value) {
      this(name, declaredType, GlobalScope.class, value);
   }

   public Class<T> getDeclaredType() {
      return this.declaredType;
   }

    QName getName() {
      return this.name;
   }

    void setValue(T t) {
      this.value = t;
   }

    T getValue() {
      return this.value;
   }

    Class getScope() {
      return this.scope;
   }

    bool isNil() {
      return this.value == nullptr || this.nil;
   }

    void setNil(bool value) {
      this.nil = value;
   }

    bool isGlobalScope() {
      return this.scope == GlobalScope.class;
   }

    bool isTypeSubstituted() {
      return this.value == nullptr ? false : this.value.getClass() != this.declaredType;
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
