#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {

class Version {
public:
    static void main(std::string[] args) {
      System.out.println(getVersion());
   }

    static std::string getVersion() {
    std::string version = Version.class.getPackage().getImplementationVersion();
      return version != nullptr ? "trove4j version " + version : "Sorry no Implementation-Version manifest attribute available";
   }
}
} // namespace trove
} // namespace gnu
