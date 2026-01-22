#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/scripting/objects/ModelScript.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {


class BaseVisual {
public:
   public abstract void save(ByteBuffer var1) throws IOException;

   public abstract void load(ByteBuffer var1, int var2) throws IOException;

   public abstract Model getModel();

   public abstract ModelScript getModelScript();

   public abstract void clear();

   public abstract void copyFrom(BaseVisual var1);

   public abstract void dressInNamedOutfit(std::string var1, ItemVisuals var2);
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
