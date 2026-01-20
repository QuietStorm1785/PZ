#pragma once
#include <string>
#include <memory>
#include <boost/unordered_map.hpp>

namespace zombie {
namespace util {

// String interning/pooling to reduce memory usage for duplicate strings (using Boost)
class SharedStrings {
private:
    boost::unordered_map<std::string, std::shared_ptr<std::string>> strings;

public:
    // Get or create shared string
    std::string get(const std::string& str) {
        auto it = strings.find(str);
        if (it != strings.end()) {
            return *(it->second);
        }
        
        // Insert new shared string
        auto sharedStr = std::make_shared<std::string>(str);
        strings[str] = sharedStr;
        return *sharedStr;
    }
    
    // Get shared pointer to string
    std::shared_ptr<std::string> getShared(const std::string& str) {
        auto it = strings.find(str);
        if (it != strings.end()) {
            return it->second;
        }
        
        auto sharedStr = std::make_shared<std::string>(str);
        strings[str] = sharedStr;
        return sharedStr;
    }
    
    // Clear all shared strings
    void clear() {
        strings.clear();
    }
    
    // Get count of unique strings
    size_t size() const {
        return strings.size();
    }
    
    // Check if string exists
    bool contains(const std::string& str) const {
        return strings.find(str) != strings.end();
    }
    
    // Global instance
    static SharedStrings& getInstance() {
        static SharedStrings instance;
        return instance;
    }
};

} // namespace util
} // namespace zombie
