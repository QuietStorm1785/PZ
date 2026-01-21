#include "zombie/util/PZXmlUtil$MarshallerAllocator.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace zombie {
namespace util {

// Note: Marshaller functionality replaced with Boost.PropertyTree
// Use boost::property_tree::write_xml() to serialize XML
return PZXmlUtil$MarshallerAllocator::get() {
    // No longer needed with Boost.PropertyTree
    return nullptr;
}

} // namespace util
} // namespace zombie
