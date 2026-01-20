
#pragma once
#include <cstdint>

namespace fmod {
class SWIGTYPE_p_FMOD_FILE_ASYNCCANCEL_CALLBACK {
public:
   int64_t swigCPtr;

   explicit SWIGTYPE_p_FMOD_FILE_ASYNCCANCEL_CALLBACK(int64_t ptr) : swigCPtr(ptr) {}
   SWIGTYPE_p_FMOD_FILE_ASYNCCANCEL_CALLBACK() : swigCPtr(0) {}

   static int64_t getCPtr(const SWIGTYPE_p_FMOD_FILE_ASYNCCANCEL_CALLBACK* obj) {
      return obj ? obj->swigCPtr : 0;
   }
};
} // namespace fmod
