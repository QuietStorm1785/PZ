#ifndef JAVAX_XML_BIND_MARSHALLER_LISTENER_H
#define JAVAX_XML_BIND_MARSHALLER_LISTENER_H

namespace javax { namespace xml { namespace bind { namespace MarshallerNS {

class Listener {
public:
 virtual ~Listener() = default;
 virtual void beforeMarshal(void* /*source*/) {}
 virtual void afterMarshal(void* /*source*/) {}
};

}}}} // namespace javax::xml::bind::MarshallerNS

#endif // JAVAX_XML_BIND_MARSHALLER_LISTENER_H
