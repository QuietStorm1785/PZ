#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"

namespace zombie {
namespace audio {


class FMODParameterList {
public:
   std::vector<std::shared_ptr<FMODParameter>> parameterList;
   std::array<std::shared_ptr<FMODParameter>, 96> parameterArray{};

   void add(const std::shared_ptr<FMODParameter>& param) {
      parameterList.push_back(param);
      if (param && param->getParameterDescription()) {
         size_t idx = param->getParameterDescription()->globalIndex;
         if (idx < parameterArray.size()) {
            parameterArray[idx] = param;
         }
      }
   }

   std::shared_ptr<FMODParameter> get(const FMOD_STUDIO_PARAMETER_DESCRIPTION* desc) {
      if (!desc) return nullptr;
      size_t idx = desc->globalIndex;
      if (idx < parameterArray.size()) {
         return parameterArray[idx];
      }
      return nullptr;
   }

   void update() {
      for (auto& param : parameterList) {
         if (param) param->update();
      }
   }
};
} // namespace audio
} // namespace zombie
