#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <boost/algorithm/string.hpp>

namespace zombie {
namespace util {

class StringUtils {
public:
    // Check if string is null or empty
    static bool isNullOrEmpty(const std::string& str) {
        return str.empty();
    }
    
    // Check if character is whitespace
    static bool isWhitespace(char c) {
        return std::isspace(static_cast<unsigned char>(c));
    }
    
    // Trim whitespace from both ends (using Boost)
    static std::string trim(const std::string& str) {
        return boost::algorithm::trim_copy(str);
    }
    
    // Convert to lowercase (using Boost)
    static std::string toLowerCase(const std::string& str) {
        return boost::algorithm::to_lower_copy(str);
    }
    
    // Convert to uppercase (using Boost)
    static std::string toUpperCase(const std::string& str) {
        return boost::algorithm::to_upper_copy(str);
    }
    
    // Check if string starts with prefix (using Boost)
    static bool startsWith(const std::string& str, const std::string& prefix) {
        return boost::algorithm::starts_with(str, prefix);
    }
    
    // Check if string ends with suffix (using Boost)
    static bool endsWith(const std::string& str, const std::string& suffix) {
        return boost::algorithm::ends_with(str, suffix);
    }
    
    // Replace all occurrences (using Boost)
    static std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
        return boost::algorithm::replace_all_copy(str, from, to);
    }
};

} // namespace util
} // namespace zombie
