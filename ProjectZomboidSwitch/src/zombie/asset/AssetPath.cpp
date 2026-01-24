#include <string>
#include "zombie/asset/AssetPath.h"

namespace zombie {
namespace asset {

AssetPath::AssetPath(const std::string& var1)
    : m_path(var1)
{
    // No additional logic needed; m_path is initialized above.
}
}

bool AssetPath::isValid() {
    return !m_path.empty();
}
}

int AssetPath::getHash() {
    // Match Java's String.hashCode() for cross-language consistency
    int hash = 0;
    for (char c : m_path) {
        hash = 31 * hash + static_cast<unsigned char>(c);
    }
    return hash;
}
}

std::string AssetPath::getPath() {
    return m_path;
}
}

std::string AssetPath::toString() {
    return std::string("AssetPath{ \"") + m_path + "\" }";
}
}

} // namespace asset
} // namespace zombie
