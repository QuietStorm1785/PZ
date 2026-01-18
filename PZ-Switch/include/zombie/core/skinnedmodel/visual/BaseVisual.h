#pragma once
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/scripting/objects/ModelScript.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseVisual {
public:
public
 void save(ByteBuffer output) throws IOException;

public
 void load(ByteBuffer input, int WorldVersion) throws IOException;

public
 Model getModel();

public
 ModelScript getModelScript();

public
 void clear();

public
 void copyFrom(BaseVisual other);

public
 void dressInNamedOutfit(String outfitName, ItemVisuals itemVisuals);
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
