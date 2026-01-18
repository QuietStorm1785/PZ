#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/AccessController.h"
#include "java/security/PrivilegedAction.h"

namespace org {
namespace lwjglx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LWJGLUtil {
public:
 static const int PLATFORM_LINUX = 1;
 static const int PLATFORM_MACOSX = 2;
 static const int PLATFORM_WINDOWS = 3;
 static const std::string PLATFORM_LINUX_NAME = "linux";
 static const std::string PLATFORM_MACOSX_NAME = "macosx";
 static const std::string PLATFORM_WINDOWS_NAME = "windows";
 static const bool DEBUG = getPrivilegedBoolean("org.lwjgl.util.Debug");
 static const bool CHECKS = !getPrivilegedBoolean("org.lwjgl.util.NoChecks");
 static const int PLATFORM;

 static int getPlatform() {
 return PLATFORM;
 }

 static std::string getPlatformName() {
 switch (getPlatform()) {
 case 1:
 return "linux";
 case 2:
 return "macosx";
 case 3:
 return "windows";
 default:
 return "unknown";
 }
 }

 static std::string getPrivilegedProperty( String) {
 return AccessController.doPrivileged(std::make_unique<PrivilegedAction<String>>() {
 std::string run() {
 return System.getProperty(string);
 }
 });
 }

 static bool getPrivilegedBoolean( String) {
 return AccessController.doPrivileged(std::make_unique<PrivilegedAction<Boolean>>() {
 bool run() {
 return Boolean.getBoolean(string);
 }
 });
 }

 static int getPrivilegedInteger( String) {
 return AccessController.doPrivileged(std::make_unique<PrivilegedAction<Integer>>() {
 int run() {
 return Integer.getInteger(string);
 }
 });
 }

 static int getPrivilegedInteger( String, int) {
 return AccessController.doPrivileged(std::make_unique<PrivilegedAction<Integer>>() {
 int run() {
 return Integer.getInteger(string, int0);
 }
 });
 }

 static {
 std::string string = getPrivilegedProperty("os.name");
 if (string.startsWith("Windows")) {
 PLATFORM = 3;
 } else if (!string.startsWith("Linux") && !string.startsWith("FreeBSD") && !string.startsWith("SunOS") && !string.startsWith("Unix")) {
 if (!string.startsWith("Mac OS X") && !string.startsWith("Darwin")) {
 throw LinkageError("Unknown platform: " + string);
 }

 PLATFORM = 2;
 } else {
 PLATFORM = 1;
 }
 }
}
} // namespace lwjglx
} // namespace org
