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
  abstract void save(ByteBuffer output) throws IOException;

public
  abstract void load(ByteBuffer input, int WorldVersion) throws IOException;

public
  abstract Model getModel();

public
  abstract ModelScript getModelScript();

public
  abstract void clear();

public
  abstract void copyFrom(BaseVisual other);

public
  abstract void dressInNamedOutfit(String outfitName, ItemVisuals itemVisuals);
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
