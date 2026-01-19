#pragma once
#include <string>
#include <string_view>
#include <stdexcept>

namespace java {
namespace net {

/**
 * Minimal C++ stub for java.net.URI
 * Provides basic URI string storage and manipulation
 */
class URI {
public:
 URI() = default;
 
 explicit URI(std::string_view uriString) 
 : uri(uriString) {}
 
 URI(std::string_view scheme, std::string_view path)
 : uri(scheme + ":" + path) {}
 
 URI(std::string_view scheme, std::string_view host, std::string_view path)
 : uri(scheme + "://" + host + path) {}
 
 // Copy and move constructors
 URI(const URI&) = default;
 URI(URI&&) = default;
 URI& operator=(const URI&) = default;
 URI& operator=(URI&&) = default;
 
 // Get the complete URI string
 std::string toString() const { return uri; }
 
 // Get scheme (e.g., "file", "http")
 std::string getScheme() const {
 size_t pos = uri.find(':');
 return (pos != std::string::npos) ? uri.substr(0, pos) : "";
 }
 
 // Get path component
 std::string getPath() const {
 size_t schemeEnd = uri.find("://");
 if (schemeEnd != std::string::npos) {
 size_t pathStart = uri.find('/', schemeEnd + 3);
 return (pathStart != std::string::npos) ? uri.substr(pathStart) : "";
 }
 
 size_t colonPos = uri.find(':');
 return (colonPos != std::string::npos) ? uri.substr(colonPos + 1) : uri;
 }
 
 // Get host component
 std::string getHost() const {
 size_t schemeEnd = uri.find("://");
 if (schemeEnd != std::string::npos) {
 size_t hostStart = schemeEnd + 3;
 size_t hostEnd = uri.find('/', hostStart);
 size_t portPos = uri.find(':', hostStart);
 
 if (portPos != std::string::npos && (hostEnd == std::string::npos || portPos < hostEnd) {
 hostEnd = portPos;
 }
 
 if (hostEnd != std::string::npos) {
 return uri.substr(hostStart, hostEnd - hostStart);
 }
 return uri.substr(hostStart);
 }
 return "";
 }
 
 // Get port (returns -1 if not specified)
 int getPort() const {
 size_t schemeEnd = uri.find("://");
 if (schemeEnd != std::string::npos) {
 size_t hostStart = schemeEnd + 3;
 size_t portPos = uri.find(':', hostStart);
 if (portPos != std::string::npos) {
 size_t portEnd = uri.find('/', portPos);
 std::string portStr = (portEnd != std::string::npos) 
 ? uri.substr(portPos + 1, portEnd - portPos - 1)
 : uri.substr(portPos + 1);
 try {
 return std::stoi(portStr);
 } catch (...) {
 return -1;
 }
 }
 }
 return -1;
 }
 
 // Check if this is a file URI
 bool isFile() const {
 return getScheme() == "file";
 }
 
 // Comparison operators
 bool operator==(const URI& other) const {
 return uri == other.uri;
 }
 
 bool operator!=(const URI& other) const {
 return uri != other.uri;
 }
 
 // Static factory method
 static URI create(std::string_view uriString) {
 return URI(uriString);
 }
 
private:
 std::string uri;
};

} // namespace net
} // namespace java
