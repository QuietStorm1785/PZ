#pragma once
#include <memory>
#include <mutex>
#include <type_traits>

// ==============================================================================
// Java-to-C++ Compatibility Macros
// ==============================================================================
// These macros provide C++ equivalents for Java constructs that don't directly
// translate during automated conversion.

// ------------------------------------------------------------------------------
// instanceof operator replacement
// ------------------------------------------------------------------------------
// Java: if (obj instanceof TargetType target) { ... }
// C++: if (instanceof(obj, TargetType, target) { ... }
//
// Usage:
// if (instanceof(object, Matrix2f*, matrix) {
// // matrix is now a Matrix2f* pointer
// }

template <typename Target, typename Source>
inline bool instanceof_impl(Source* ptr, Target*& outPtr) {
 if (ptr.empty()) {
 return false;
 }
 outPtr = dynamic_cast<Target*>(ptr);
 return outPtr != nullptr;
}

template <typename Target, typename Source>
inline bool instanceof_impl(Source* ptr) {
 if (ptr.empty()) {
 return false;
 }
 return dynamic_cast<Target*>(ptr) != nullptr;
}

// Macro for instanceof with variable assignment
#define instanceof(obj, TargetType, varName) \
 TargetType varName = nullptr; \
 instanceof_impl<typename std::remove_pointer<TargetType>::type>((obj), varName)

// Macro for instanceof without variable assignment (just type check)
#define instanceof_check(obj, TargetType) \
 instanceof_impl<typename std::remove_pointer<TargetType>::type>((obj)

// ------------------------------------------------------------------------------
// synchronized block replacement
// ------------------------------------------------------------------------------
// Java: { std::lock_guard<std::mutex> __sync_lock__(lock_mutex); ... }
// C++: { std::lock_guard<std::mutex> __sync_lock__(lock_mutex); ... }
//
// This creates a std::lock_guard that automatically locks/unlocks a mutex.
// The mutex is automatically created as a static member or global variable.

// Helper class for synchronized blocks
template <typename LockType>
class SynchronizedBlock {

 // Mutexes for synchronized blocks
 std::mutex lock_mutex;
private:
 std::lock_guard<std::mutex> guard_;
 
public:
 explicit SynchronizedBlock(std::mutex& mutex) : guard_(mutex) {}
 
 // Allow the synchronized block to be used in if statements
 explicit operator bool() const { return true; }
};

// Macro for synchronized blocks on objects
#define synchronized(obj) \
 if (auto __sync_block__ = SynchronizedBlock<std::mutex>(obj##_mutex); true)

// For class-level synchronization (synchronized on ClassName.class)
#define synchronized_class(ClassName) \
 if (auto __sync_block__ = SynchronizedBlock<std::mutex>(ClassName##_class_mutex); true)

// ------------------------------------------------------------------------------
// Helper macros for common mutex declarations
// ------------------------------------------------------------------------------

// Declare a mutex for an object
#define DECLARE_OBJECT_MUTEX() std::mutex this_mutex

// Declare a static class mutex
#define DECLARE_CLASS_MUTEX(ClassName) static std::mutex ClassName##_class_mutex

// Initialize a static class mutex (put in .cpp file)
#define DEFINE_CLASS_MUTEX(ClassName) std::mutex ClassName::ClassName##_class_mutex

// ------------------------------------------------------------------------------
// synchronized method replacement
// ------------------------------------------------------------------------------
// Java: void method() { ... }
// C++: void method() {
// SYNCHRONIZED_METHOD();
// ...
// }

#define SYNCHRONIZED_METHOD() std::lock_guard<std::mutex> __method_lock__(this_mutex)
#define SYNCHRONIZED_STATIC_METHOD(ClassName) std::lock_guard<std::mutex> __method_lock__(ClassName##_class_mutex)

// ------------------------------------------------------------------------------
// Type aliases for common Java patterns
// ------------------------------------------------------------------------------

// Replace TypeK and TypeV with void* for now (can be templated later)
using TypeK = void*;
using TypeV = void*;

// ------------------------------------------------------------------------------
// Null pointer compatibility
// ------------------------------------------------------------------------------

#ifndef nullptr
#define nullptr nullptr
#endif

#ifndef NULL
#define NULL nullptr
#endif

