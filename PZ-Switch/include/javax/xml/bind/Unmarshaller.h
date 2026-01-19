#pragma once

#include <memory>
#include <stdexcept>

namespace javax {
namespace xml {
namespace bind {

class JAXBException : public std::runtime_error {
public:
 JAXBException(std::string_view message)
 : std::runtime_error(message) {}
};

class Unmarshaller {
public:
 virtual ~Unmarshaller() = default;
 
 // Unmarshalling operations would go here
 // For now, stub implementation
 virtual void* unmarshal(std::string_view source) {
 throw JAXBException("Unmarshaller.unmarshal() not implemented");
 }
};

} // namespace bind
} // namespace xml
} // namespace javax
