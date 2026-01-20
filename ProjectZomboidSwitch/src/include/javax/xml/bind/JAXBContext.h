#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/AccessController.h"
#include "javax/xml/bind/JAXBContext/1.h"
#include "org/w3c/dom/Node.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class JAXBContext {
public:
    static const std::string JAXB_CONTEXT_FACTORY = "javax.xml.bind.JAXBContextFactory";

    protected JAXBContext() {
   }

    static JAXBContext newInstance(const std::string& contextPath) {
    return newInstance();
   }

    static JAXBContext newInstance(const std::string& contextPath, ClassLoader classLoader) {
    return newInstance();
   }

    static JAXBContext newInstance(const std::string& contextPath, ClassLoader classLoader, ?> properties) {
      return ContextFinder.find("javax.xml.bind.JAXBContextFactory", contextPath, classLoader, properties);
   }

    static JAXBContext newInstance(Class<?>... classesToBeBound) {
    return newInstance();
   }

    static JAXBContext newInstance(Class<?>[] classesToBeBound, ?> properties) {
      if (classesToBeBound == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         for (int i = classesToBeBound.length - 1; i >= 0; i--) {
            if (classesToBeBound[i] == nullptr) {
               throw std::make_unique<IllegalArgumentException>();
            }
         }

         return ContextFinder.find(classesToBeBound, properties);
      }
   }

   public abstract Unmarshaller createUnmarshaller() throws JAXBException;

   public abstract Marshaller createMarshaller() throws JAXBException;

   public abstract Validator createValidator() throws JAXBException;

   public <T> Binder<T> createBinder(Class<T> domType) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Binder<Node> createBinder() {
      return this.createBinder(Node.class);
   }

    JAXBIntrospector createJAXBIntrospector() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void generateSchema(SchemaOutputResolver outputResolver) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    static ClassLoader getContextClassLoader() {
      return System.getSecurityManager() == nullptr ? Thread.currentThread().getContextClassLoader() : AccessController.doPrivileged(std::make_unique<1>());
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
