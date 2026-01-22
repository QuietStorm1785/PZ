#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/beans/Introspector.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include "javax/xml/bind/JAXB/Cache.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include "javax/xml/transform/stream/StreamSource.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class JAXB {
public:
   private static volatile WeakReference<Cache> cache;

    private JAXB() {
   }

   private static <T> JAXBContext getContext(Class<T> type) throws JAXBException {
      WeakReference<Cache> c = cache;
      if (c != nullptr) {
    Cache d = c.get();
         if (d != nullptr && d.type == type) {
            return d.context;
         }
      }

    Cache d = std::make_shared<Cache>(type);
      cache = new WeakReference<>(d);
      return d.context;
   }

   public static <T> T unmarshal(File xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(std::make_shared<StreamSource>(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      }
   }

   public static <T> T unmarshal(URL xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

   public static <T> T unmarshal(URI xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

   public static <T> T unmarshal(std::string xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

   public static <T> T unmarshal(InputStream xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

   public static <T> T unmarshal(Reader xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

   public static <T> T unmarshal(Source xml, Class<T> type) {
      try {
         JAXBElement<T> item = getContext(type).createUnmarshaller().unmarshal(toSource(xml), type);
         return (T)item.getValue();
      } catch (JAXBException var3) {
         throw DataBindingException(var3);
      } catch (IOException var4) {
         throw DataBindingException(var4);
      }
   }

    static Source toSource(void* xml) {
      if (xml == nullptr) {
         throw IllegalArgumentException("no XML is given");
      } else {
         if (dynamic_cast<std*>(xml) != nullptr::string) {
            try {
               xml = std::make_shared<URI>((std::string)xml);
            } catch (URISyntaxException var2) {
               xml = std::make_shared<File>((std::string)xml);
            }
         }

         if (dynamic_cast<File*>(xml) != nullptr) {
    File file = (File)xml;
            return std::make_shared<StreamSource>(file);
         } else {
            if (dynamic_cast<URI*>(xml) != nullptr) {
    URI uri = (URI)xml;
               xml = uri.toURL();
            }

            if (dynamic_cast<URL*>(xml) != nullptr) {
    URL url = (URL)xml;
               return std::make_shared<StreamSource>(url.toExternalForm());
            } else if (dynamic_cast<InputStream*>(xml) != nullptr) {
    InputStream in = (InputStream)xml;
               return std::make_shared<StreamSource>(in);
            } else if (dynamic_cast<Reader*>(xml) != nullptr) {
    Reader r = (Reader)xml;
               return std::make_shared<StreamSource>(r);
            } else if (dynamic_cast<Source*>(xml) != nullptr) {
               return (Source)xml;
            } else {
               throw IllegalArgumentException("I don't understand how to handle " + xml.getClass());
            }
         }
      }
   }

    static void marshal(void* jaxbObject, File xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, URL xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, URI xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, const std::string& xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, OutputStream xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, Writer xml) {
      _marshal(jaxbObject, xml);
   }

    static void marshal(void* jaxbObject, Result xml) {
      _marshal(jaxbObject, xml);
   }

    static void _marshal(void* jaxbObject, void* xml) {
      try {
    JAXBContext context;
         if (dynamic_cast<JAXBElement*>(jaxbObject) != nullptr) {
            context = getContext(((JAXBElement)jaxbObject).getDeclaredType());
         } else {
            Class<?> clazz = jaxbObject.getClass();
    XmlRootElement r = clazz.getAnnotation(XmlRootElement.class);
            context = getContext(clazz);
            if (r == nullptr) {
               jaxbObject = std::make_shared<JAXBElement>(std::make_shared<QName>(inferName(clazz)), clazz, jaxbObject);
            }
         }

    Marshaller m = context.createMarshaller();
         m.setProperty("jaxb.formatted.output", true);
         m.marshal(jaxbObject, toResult(xml));
      } catch (JAXBException var5) {
         throw DataBindingException(var5);
      } catch (IOException var6) {
         throw DataBindingException(var6);
      }
   }

    static std::string inferName(Class clazz) {
      return Introspector.decapitalize(clazz.getSimpleName());
   }

    static Result toResult(void* xml) {
      if (xml == nullptr) {
         throw IllegalArgumentException("no XML is given");
      } else {
         if (dynamic_cast<std*>(xml) != nullptr::string) {
            try {
               xml = std::make_shared<URI>((std::string)xml);
            } catch (URISyntaxException var3) {
               xml = std::make_shared<File>((std::string)xml);
            }
         }

         if (dynamic_cast<File*>(xml) != nullptr) {
    File file = (File)xml;
            return std::make_shared<StreamResult>(file);
         } else {
            if (dynamic_cast<URI*>(xml) != nullptr) {
    URI uri = (URI)xml;
               xml = uri.toURL();
            }

            if (dynamic_cast<URL*>(xml) != nullptr) {
    URL url = (URL)xml;
    URLConnection con = url.openConnection();
               con.setDoOutput(true);
               con.setDoInput(false);
               con.connect();
               return std::make_shared<StreamResult>(con.getOutputStream());
            } else if (dynamic_cast<OutputStream*>(xml) != nullptr) {
    OutputStream os = (OutputStream)xml;
               return std::make_shared<StreamResult>(os);
            } else if (dynamic_cast<Writer*>(xml) != nullptr) {
    Writer w = (Writer)xml;
               return std::make_shared<StreamResult>(w);
            } else if (dynamic_cast<Result*>(xml) != nullptr) {
               return (Result)xml;
            } else {
               throw IllegalArgumentException("I don't understand how to handle " + xml.getClass());
            }
         }
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
