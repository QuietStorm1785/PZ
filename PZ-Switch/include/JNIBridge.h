#pragma once

/**
 * JNI Bridge - C++ Integration Layer for Decompiled Java Code
 * 
 * This header provides compatibility and integration between the converted
 * Java-to-C++ code and the existing PZ-Switch C++ codebase.
 * 
 * Features:
 * - Java type mapping and compatibility
 * - Memory management utilities
 * - Thread-safety mechanisms
 * - Exception handling
 * - String/Object conversion
 * - Standard library integration
 */

#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cstdint>
#include <mutex>
#include "MemoryPool.h"

namespace jni {

// ============================================================================
// Java Type Compatibility Mappings
// ============================================================================

// Primitive type aliases
using jint = int32_t;
using jlong = int64_t;
using jfloat = float;
using jdouble = double;
using jboolean = bool;
using jbyte = int8_t;
using jchar = char16_t;
using jshort = int16_t;

// Reference types
using jstring = std::shared_ptr<std::string>;
using jobject = std::shared_ptr<void>;

// ============================================================================
// Java Exception Compatibility
// ============================================================================

class JavaException : public std::runtime_error {
public:
    explicit JavaException(std::string_view message) 
        : std::runtime_error(message) {}
    
    virtual const char* what() const noexcept override {
        return std::runtime_error::what();
    }
};

// ============================================================================
// String Utilities - Java <-> C++
// ============================================================================

namespace string {
    
    /**
     * Convert Java String (std::string) to C++ std::string
     */
    inline std::string toString(std::string_view javaStr) {
        return javaStr;
    }
    
    /**
     * Convert C++ std::string to Java String
     */
    inline jstring toJavaString(std::string_view cppStr) {
        return std::make_shared<std::string>(cppStr);
    }
    
    /**
     * UTF-8 to UTF-16 conversion for char arrays
     */
    std::u16string utf8ToUtf16(std::string_view utf8Str);
    
    /**
     * UTF-16 to UTF-8 conversion
     */
    std::string utf16ToUtf8(const std::u16string& utf16Str);
    
} // namespace string

// ============================================================================
// Memory Management - Smart Pointer Utilities
// ============================================================================

namespace memory {
    
    /**
     * Create a Java-compatible object wrapper
     */
    template<typename T>
    jobject wrapObject(T* ptr) {
        return std::shared_ptr<void>(static_cast<void*>(ptr));
    }
    
    /**
     * Unwrap a Java object back to native type
     */
    template<typename T>
    T* unwrapObject(const jobject& obj) {
        return static_cast<T*>(obj.get());
    }
    
    /**
     * Safe delete wrapper for Java-compatible cleanup
     */
    template<typename T>
    void safeDelete(T*& ptr) {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    
} // namespace memory

// ============================================================================
// Collection Compatibility - Java Collections to STL
// ============================================================================

namespace collections {
    
    /**
     * ArrayList compatibility wrapper
     */
    template<typename T>
    using ArrayList = std::vector<T>;
    
    /**
     * HashMap compatibility wrapper
     */
    template<typename K, typename V>
    using HashMap = std::unordered_map<K, V>;
    
    /**
     * Convert ArrayList to std::vector
     */
    template<typename T>
    std::vector<T> arrayListToVector(const ArrayList<T>& list) {
        return std::vector<T>(list.begin(), list.end());
    }
    
} // namespace collections

// ============================================================================
// Null Safety Utilities
// ============================================================================

namespace null_safety {
    
    /**
     * Java null pointer check
     */
    template<typename T>
    bool isNull(const std::shared_ptr<T>& ptr) {
        return ptr == nullptr;
    }
    
    /**
     * Java not-null assertion
     */
    template<typename T>
    void requireNonNull(const std::shared_ptr<T>& ptr, std::string_view message = "") {
        if (ptr == nullptr) {
            throw JavaException("NullPointerException: " + message);
        }
    }
    
} // namespace null_safety

// ============================================================================
// Legacy Java Code Support
// ============================================================================

namespace legacy {
    
    /**
     * Support for Java's "synchronized" blocks using mutex
     */
    class Synchronized {
    private:
        std::mutex mtx;
    public:
        template<typename Func>
        void execute(Func&& func) {
            std::lock_guard<std::mutex> lock(mtx);
            func();
        }
    };
    
    /**
     * Support for Java's instanceof checks
     */
    template<typename TargetType, typename ObjectType>
    bool instanceof(const std::shared_ptr<ObjectType>& obj) {
        return dynamic_cast<TargetType*>(obj.get()) != nullptr;
    }
    
} // namespace legacy

// ============================================================================
// Conversions and Casting
// ============================================================================

namespace casting {
    
    /**
     * Safe numeric casting with bounds checking
     */
    template<typename Target, typename Source>
    Target safeCast(Source value) {
        if (value > std::numeric_limits<Target>::max() || 
            value < std::numeric_limits<Target>::lowest()) {
            throw JavaException("Numeric overflow in cast");
        }
        return static_cast<Target>(value);
    }
    
    /**
     * Reinterpret bits (similar to Java's Float.floatToIntBits)
     */
    inline int32_t floatToIntBits(float f) {
        int32_t result;
        std::memcpy(&result, &f, sizeof(f));
        return result;
    }
    
    /**
     * Reinterpret bits (similar to Java's Float.intBitsToFloat)
     */
    inline float intBitsToFloat(int32_t i) {
        float result;
        std::memcpy(&result, &i, sizeof(i));
        return result;
    }
    
} // namespace casting

// ============================================================================
// Integration Macros for Common Java Patterns
// ============================================================================

/**
 * Macro for getter compatibility
 */
#define JAVA_GETTER(FieldType, FieldName, methodName) \
    FieldType get##methodName() const { \
        return FieldName; \
    }

/**
 * Macro for setter compatibility
 */
#define JAVA_SETTER(FieldType, FieldName, methodName) \
    void set##methodName(FieldType value) { \
        FieldName = value; \
    }

/**
 * Macro for toString implementation
 */
#define JAVA_TOSTRING(ClassName) \
    std::string toString() const { \
        return std::string(#ClassName) + "@" + std::to_string(reinterpret_cast<uintptr_t>(this)); \
    }

} // namespace jni

// ============================================================================
// Include converted namespaces for convenience
// ============================================================================

// ============================================================================
// Thread Safety Utilities - Critical for Game Engine
// ============================================================================

namespace threading {
    
    // Marker class for thread-safe operations
    class ThreadSafe {};
    
    // Marker class for operations that must be called from main thread
    class MainThreadOnly {};
    
    // RAII lock guard with scope tracking
    template<typename Mutex>
    class ScopedLock {
    private:
        Mutex& m_mutex;
        bool m_locked;
        
    public:
        explicit ScopedLock(Mutex& mutex) : m_mutex(mutex), m_locked(false) {
            m_mutex.lock();
            m_locked = true;
        }
        
        ~ScopedLock() {
            if (m_locked) {
                m_mutex.unlock();
            }
        }
        
        // Prevent copying
        ScopedLock(const ScopedLock&) = delete;
        ScopedLock& operator=(const ScopedLock&) = delete;
        
        // Allow moving
        ScopedLock(ScopedLock&& other) noexcept 
            : m_mutex(other.m_mutex), m_locked(other.m_locked) {
            other.m_locked = false;
        }
    };
    
    // Thread-safe wrapper for shared data
    template<typename T>
    class ThreadSafeValue {
    private:
        T m_value;
        mutable std::mutex m_mutex;
        
    public:
        ThreadSafeValue() = default;
        explicit ThreadSafeValue(const T& initial) : m_value(initial) {}
        
        // Get a copy of the value
        T get() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_value;
        }
        
        // Set a new value
        void set(const T& newValue) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_value = newValue;
        }
        
        // Atomic update with callback
        template<typename Callback>
        void update(Callback&& cb) {
            std::lock_guard<std::mutex> lock(m_mutex);
            cb(m_value);
        }
        
        // Prevent copying
        ThreadSafeValue(const ThreadSafeValue&) = delete;
        ThreadSafeValue& operator=(const ThreadSafeValue&) = delete;
    };
    
    // Thread-safe container wrapper for common operations
    template<typename Container>
    class ThreadSafeContainer {
    private:
        Container m_container;
        mutable std::mutex m_mutex;
        
    public:
        ThreadSafeContainer() = default;
        
        // Push/add element
        template<typename T>
        void push(const T& value) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if constexpr (requires { m_container.push_back(value); }) {
                m_container.push_back(value);
            } else if constexpr (requires { m_container.insert(value); }) {
                m_container.insert(value);
            }
        }
        
        // Get size
        size_t size() const {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_container.size();
        }
        
        // Clear container
        void clear() {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_container.clear();
        }
        
        // Execute callback with locked access
        template<typename Callback>
        void withLock(Callback&& cb) {
            std::lock_guard<std::mutex> lock(m_mutex);
            cb(m_container);
        }
        
        // Prevent copying
        ThreadSafeContainer(const ThreadSafeContainer&) = delete;
        ThreadSafeContainer& operator=(const ThreadSafeContainer&) = delete;
    };
    
} // namespace threading

// ============================================================================
// Synchronized/Locked Method Helpers for Converted Java Code
// ============================================================================

// Macro for marking thread-safe synchronized blocks
#define JNI_SYNCHRONIZED_BLOCK(lock) \
    for (jni::threading::ScopedLock<decltype(lock)> __guard__(lock); true; )

// Macro for simplified thread-safe access
#define JNI_THREAD_SAFE(expr) \
    do { \
        static thread_local std::mutex __expr_lock__; \
        std::lock_guard<std::mutex> __expr_guard__(__expr_lock__); \
        expr; \
    } while(0)

// Commonly used converted namespaces
namespace zombie {
    // Forward declarations for zombie module classes
    // Will be populated as integration continues
}

#endif // JNI_BRIDGE_H
