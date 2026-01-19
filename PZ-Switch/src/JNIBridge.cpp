#include "JNIBridge.h"
#include <codecvt>
#include <locale>

namespace jni {
namespace string {

std::u16string utf8ToUtf16(const std::string& utf8Str) {
    try {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        return converter.from_bytes(utf8Str);
    } catch (const std::exception& e) {
        throw JavaException(std::string("UTF-8 to UTF-16 conversion failed: ") + e.what());
    }
}

std::string utf16ToUtf8(const std::u16string& utf16Str) {
    try {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        return converter.to_bytes(utf16Str);
    } catch (const std::exception& e) {
        throw JavaException(std::string("UTF-16 to UTF-8 conversion failed: ") + e.what());
    }
}

} // namespace string
} // namespace jni
