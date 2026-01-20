#include <iostream>
#include <cstdlib>

#ifdef __SWITCH__
#include <switch.h>
#endif

// Include our utility classes
#include "zombie/util/StringUtils_simple.h"
#include "zombie/util/PZCalendar_simple.h"
#include "zombie/util/PZRandom.h"
#include "zombie/util/LocationRNG_simple.h"
#include "zombie/util/SharedStrings_simple.h"
#include "zombie/util/Pool_simple.h"

// Entry point for Project Zomboid converted code
int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    #ifdef __SWITCH__
    // Initialize Switch console for debug output
    consoleInit(NULL);
    
    // Initialize socket for nxlink debugging (optional)
    socketInitializeDefault();
    nxlinkStdio();
    
    // Initialize gamepad
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);
    #endif
    
    std::cout << "Project Zomboid - Convert2Cpp" << std::endl;
    std::cout << "Converted Java-to-C++ codebase" << std::endl;
    std::cout << "Version: 1.0.0" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Testing utility classes..." << std::endl;
    std::cout << "" << std::endl;
    
    // Test StringUtils
    std::string testStr = "  Hello World  ";
    std::cout << "StringUtils:" << std::endl;
    std::cout << "  Trimmed: '" << zombie::util::StringUtils::trim(testStr) << "'" << std::endl;
    
    // Test PZCalendar
    zombie::util::PZCalendar cal;
    std::cout << "Time: " << cal.toString() << std::endl;
    
    // Test Random
    zombie::util::PZRandom rng;
    std::cout << "Random: " << rng.nextInt(100) << std::endl;
    std::cout << "" << std::endl;
    
    // Test LocationRNG
    zombie::util::LocationRNG locRng(12345);
    std::cout << "LocationRNG: " << locRng.nextInt(100) << ", " << locRng.nextFloat() << std::endl;
    std::cout << "  Coord-based: " << locRng.nextInt(10, 20, 5, 100) << std::endl;
    
    // Test SharedStrings
    zombie::util::SharedStrings& sharedStrs = zombie::util::SharedStrings::getInstance();
    std::string s1 = sharedStrs.get("zombie");
    std::string s2 = sharedStrs.get("zombie");
    std::cout << "SharedStrings: stored " << sharedStrs.size() << " unique strings" << std::endl;
    
    // Test Pool
    zombie::util::Pool<int> pool([]() { return std::make_unique<int>(0); }, 10);
    auto obj1 = pool.acquire();
    *obj1 = 42;
    pool.release(std::move(obj1));
    std::cout << "Pool: " << pool.getAvailableCount() << " available, " 
              << pool.getAllocatedCount() << " allocated" << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "All utility classes working!" << std::endl;
    std::cout << "Press + to exit" << std::endl;
    
    #ifdef __SWITCH__
    // Main loop for Switch
    while (appletMainLoop()) {
        // Scan all connected controllers
        padUpdate(&pad);
        
        // Get button states
        u64 kDown = padGetButtonsDown(&pad);
        
        if (kDown & HidNpadButton_Plus) {
            break;  // Exit on Plus button
        }
        
        consoleUpdate(NULL);
    }
    
    // Cleanup
    consoleExit(NULL);
    socketExit();
    #endif
    
    std::cout << "Exiting..." << std::endl;
    return EXIT_SUCCESS;
}
