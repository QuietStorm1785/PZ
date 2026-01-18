//#pragma once
#pragma once
#include <string>

namespace org { namespace lwjglx {

class LWJGLUtil {
public:
	static constexpr int PLATFORM_LINUX = 1;
	static constexpr int PLATFORM_MACOSX = 2;
	static constexpr int PLATFORM_WINDOWS = 3;

	static int getPlatform() { return platformCached; }

	static std::string getPlatformName() {
		switch (getPlatform()) {
			case PLATFORM_LINUX: return "linux";
			case PLATFORM_MACOSX: return "macosx";
			case PLATFORM_WINDOWS: return "windows";
			default: return "unknown";
		}
	}

	static bool getPrivilegedBoolean(const std::string& /*name*/) { return false; }
	static std::string getPrivilegedProperty(const std::string& /*name*/) { return ""; }
	static int getPrivilegedInteger(const std::string& /*name*/, int defaultValue = 0) { return defaultValue; }

private:
	static int platformCached;
};

// Default to Linux platform in this environment
int LWJGLUtil::platformCached = LWJGLUtil::PLATFORM_LINUX;

}} // namespace org::lwjglx
