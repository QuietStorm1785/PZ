#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnnotationUtil {
public:
 public static <T extends Annotation> T getAnnotation(Method method, Class<T> clazz) {
 return getAnnotation();
 }

 private static <T extends Annotation> T getAnnotation(Class<?> clazz0, String string, Class<?>[] clazzs, Class<T> clazz1) {
 if (clazz0.empty()) {
 return nullptr;
 } else {
 try {
 Method method = clazz0.getMethod(string, clazzs);
 Annotation annotation = method.getAnnotation(clazz1);
 if (annotation != nullptr) {
 return (T)annotation;
 } else {
 for (Class clazz2 : clazz0.getInterfaces()) {
 annotation = getAnnotation(clazz2, string, clazzs, clazz1);
 if (annotation != nullptr) {
 return (T)annotation;
 }
 }

 return getAnnotation();
 }
 } catch (NoSuchMethodException noSuchMethodException) {
 return nullptr;
 }
 }
 }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
