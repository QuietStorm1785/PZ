#include "zombie/asset/AssetManagers.h"

namespace zombie {
namespace asset {

AssetManagers::AssetManagers(FileSystem var1)
    : m_file_system(var1), m_managers(std::make_shared<AssetManagerTable>())
{
    // No additional logic needed; members are initialized above.
}
}

AssetManager AssetManagers::get(AssetType var1) {
    return m_managers->get(var1.type);
}
}

void AssetManagers::add(AssetType var1, AssetManager var2) {
    m_managers->put(var1.type, var2);
}
}

FileSystem AssetManagers::getFileSystem() {
    return m_file_system;
}
}

} // namespace asset
} // namespace zombie
