#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {


class FMOD_STUDIO_EVENT_DESCRIPTION {
public:
    const long address;
    const std::string path;
    const FMOD_GUID id;
    const bool bHasSustainPoints;
    const long length;
   public const std::vector<FMOD_STUDIO_PARAMETER_DESCRIPTION> parameters = std::make_unique<std::vector<>>();

    public FMOD_STUDIO_EVENT_DESCRIPTION(long var1, const std::string& var3, FMOD_GUID var4, bool var5, long var6) {
      this.address = var1;
      this.path = var3;
      this.id = var4;
      this.bHasSustainPoints = var5;
      this.length = var6;
   }

    bool hasParameter(FMOD_STUDIO_PARAMETER_DESCRIPTION var1) {
      return this.parameters.contains(var1);
   }
}
} // namespace fmod
} // namespace fmod
