#ifndef ORG_LWJGL_SYSTEM_CONFIGURATION_H
#define ORG_LWJGL_SYSTEM_CONFIGURATION_H

#include <string>

namespace org::lwjgl::system {

class Configuration {
public:
 static bool DEBUG;
 static bool TRACE;
};

// Define static members (default false)
bool Configuration::DEBUG = false;
bool Configuration::TRACE = false;

} // namespace org::lwjgl::system

#endif // ORG_LWJGL_SYSTEM_CONFIGURATION_H
