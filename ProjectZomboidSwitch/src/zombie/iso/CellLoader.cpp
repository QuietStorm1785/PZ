#include <string>
#include <vector>
#include "zombie/iso/CellLoader.h"

namespace zombie {
namespace iso {

void CellLoader::DoTileObjectCreation(IsoSprite var0, IsoObjectType var1, IsoGridSquare var2, IsoCell var3, int var4, int var5, int var6, const std::string& var7) {
    // TODO: Implement DoTileObjectCreation
}

bool CellLoader::LoadCellBinaryChunk(IsoCell var0, int var1, int var2, IsoChunk var3) {
    // TODO: Implement LoadCellBinaryChunk
    return false;
}

IsoCell CellLoader::LoadCellBinaryChunk(IsoSpriteManager var0, int var1, int var2) {
    // TODO: Implement LoadCellBinaryChunk
    return nullptr;
}

void CellLoader::RecurseMultitileObjects(IsoCell var0, IsoGridSquare var1, IsoGridSquare var2, std::vector<IsoPushableObject> var3) {
    // TODO: Implement RecurseMultitileObjects
}

void CellLoader::ConnectMultitileObjects(IsoCell var0) {
    // TODO: Implement ConnectMultitileObjects
}

void CellLoader::AddObject(IsoGridSquare var0, IsoObject var1) {
    // TODO: Implement AddObject
}

void CellLoader::AddSpecialObject(IsoGridSquare var0, IsoObject var1) {
    // TODO: Implement AddSpecialObject
}

} // namespace iso
} // namespace zombie
