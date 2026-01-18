#include <string>
#ifndef JAVAX_XML_BIND_ANNOTATION_XMLROOTELEMENT_H
#define JAVAX_XML_BIND_ANNOTATION_XMLROOTELEMENT_H

// C++ adaptation of javax.xml.bind.annotation.XmlRootElement
// Purpose: map a top-level class or enum type to an XML element when serialized.
// In Java, @XmlRootElement can be combined with @XmlType, @XmlEnum,
// @XmlAccessorType, and @XmlAccessorOrder. Here we provide lightweight
// metadata storage so converted code can represent the element name/namespace
// (and optional factory info) without runtime binding logic.

namespace javax {
namespace xml {
namespace bind {
namespace annotation {

class XmlRootElement {
public:
 XmlRootElement() = default;

 XmlRootElement(const std::string& name,
 const std::string& namespace_uri = "",
 const std::string& factory_class = "",
 const std::string& factory_method = "")
 : name_(name), namespace_(namespace_uri),
 factory_class_(factory_class), factory_method_(factory_method) {}

 const std::string& name() const { return name_; }
 const std::string& namespace_uri() const { return namespace_; }
 const std::string& factory_class() const { return factory_class_; }
 const std::string& factory_method() const { return factory_method_; }

private:
 std::string name_{}; // XML element local name
 std::string namespace_{}; // XML namespace URI
 std::string factory_class_{}; // optional factoryClass
 std::string factory_method_{}; // optional factoryMethod
};

} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax

#endif // JAVAX_XML_BIND_ANNOTATION_XMLROOTELEMENT_H
