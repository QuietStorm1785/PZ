#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMOD_STUDIO_EVENT_DESCRIPTION {
public:
  const long address;
  const std::string path;
  const FMOD_GUID id;
  const bool bHasSustainPoints;
  const long length;
public
  final ArrayList<FMOD_STUDIO_PARAMETER_DESCRIPTION> parameters =
      std::make_unique<ArrayList<>>();

public
  FMOD_STUDIO_EVENT_DESCRIPTION(long arg0, const std::string &arg1,
                                FMOD_GUID arg2, bool arg3, long arg4) {
    this.address = arg0;
    this.path = arg1;
    this.id = arg2;
    this.bHasSustainPoints = arg3;
    this.length = arg4;
  }

  bool hasParameter(FMOD_STUDIO_PARAMETER_DESCRIPTION arg0) {
    return this.parameters.contains(arg0);
  }
}
} // namespace fmod
} // namespace fmod
