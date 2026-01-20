#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/validation/Schema.h"

namespace javax {
namespace xml {
namespace bind {


class Binder {
public:
   public abstract Object unmarshal(XmlNode var1) throws JAXBException;

   public abstract <T> JAXBElement<T> unmarshal(XmlNode var1, Class<T> var2) throws JAXBException;

   public abstract void marshal(Object var1, XmlNode var2) throws JAXBException;

   public abstract XmlNode getXMLNode(Object var1);

   public abstract Object getJAXBNode(XmlNode var1);

   public abstract XmlNode updateXML(Object var1) throws JAXBException;

   public abstract XmlNode updateXML(Object var1, XmlNode var2) throws JAXBException;

   public abstract Object updateJAXB(XmlNode var1) throws JAXBException;

   public abstract void setSchema(Schema var1);

   public abstract Schema getSchema();

   public abstract void setEventHandler(ValidationEventHandler var1) throws JAXBException;

   public abstract ValidationEventHandler getEventHandler() throws JAXBException;

   public abstract void setProperty(std::string var1, Object var2) throws PropertyException;

   public abstract Object getProperty(std::string var1) throws PropertyException;
}
} // namespace bind
} // namespace xml
} // namespace javax
