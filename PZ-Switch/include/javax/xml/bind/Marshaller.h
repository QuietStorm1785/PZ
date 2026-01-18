#ifndef JAVAX_XML_BIND_MARSHALLER_H
#define JAVAX_XML_BIND_MARSHALLER_H

#include <string>

namespace javax { namespace xml { namespace bind {

class Marshaller {
public:
 template <typename T>
 void marshal(const T& /*obj*/, const std::string& /*output*/) {}
};

}}} // namespace javax::xml::bind

#endif // JAVAX_XML_BIND_MARSHALLER_H
