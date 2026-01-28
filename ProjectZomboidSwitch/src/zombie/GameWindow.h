#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace zombie {

class GameWindow {
public:
    static void MainLoop();
    // ...existing methods...

    class StringUTF {
    public:
        static int encode(const std::string& str);
        static std::string decode(int val);
        static void save(void* byteBuffer, const std::string& str); // Replace void* with ByteBuffer*
        static std::string load(void* byteBuffer); // Replace void* with ByteBuffer*
    };

    class TexturePack {
    public:
        // Add members as needed from Java/C++
    };

    class OSValidator {
    public:
        static bool isWindows();
        static bool isMac();
        static bool isUnix();
        static bool isSolaris();
    };

    class s_performance {
    public:
        // Add members as needed from Java/C++
    };
};

} // namespace zombie
