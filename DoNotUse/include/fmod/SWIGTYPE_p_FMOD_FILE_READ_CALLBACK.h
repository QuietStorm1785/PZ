
#pragma once
#include <cstdint>

namespace fmod {
class SWIGTYPE_p_FMOD_FILE_READ_CALLBACK {
public:
   int64_t swigCPtr;

   explicit SWIGTYPE_p_FMOD_FILE_READ_CALLBACK(int64_t ptr) : swigCPtr(ptr) {}
   SWIGTYPE_p_FMOD_FILE_READ_CALLBACK() : swigCPtr(0) {}

   static int64_t getCPtr(const SWIGTYPE_p_FMOD_FILE_READ_CALLBACK* obj) {
      return obj ? obj->swigCPtr : 0;
   }
};
} // namespace fmod
