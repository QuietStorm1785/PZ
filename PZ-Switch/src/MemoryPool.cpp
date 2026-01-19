/**
 * Memory Pool Implementation
 */

#include "MemoryPool.h"
#include <iostream>

namespace jni {
namespace pools {

// Define global pool instances
FixedMemoryPool<64, 2048> small_objects;
FixedMemoryPool<256, 1024> medium_objects;
FixedMemoryPool<1024, 256> large_objects;
ArenaAllocator frame_arena;

void printStats() {
    auto small = small_objects.getStats();
    auto medium = medium_objects.getStats();
    auto large = large_objects.getStats();
    auto arena = frame_arena.getStats();
    
    std::cout << "Memory Pool Statistics:\n";
    std::cout << "  Small Objects (64B):\n";
    std::cout << "    Available: " << small.available << "/" << small.pool_size << "\n";
    std::cout << "    Peak usage: " << small.peak_usage << "\n";
    
    std::cout << "  Medium Objects (256B):\n";
    std::cout << "    Available: " << medium.available << "/" << medium.pool_size << "\n";
    std::cout << "    Peak usage: " << medium.peak_usage << "\n";
    
    std::cout << "  Large Objects (1KB):\n";
    std::cout << "    Available: " << large.available << "/" << large.pool_size << "\n";
    std::cout << "    Peak usage: " << large.peak_usage << "\n";
    
    std::cout << "  Frame Arena:\n";
    std::cout << "    Chunks: " << arena.chunks << "\n";
    std::cout << "    Used: " << arena.used << "/" << arena.total_capacity << " bytes\n";
}

void resetFrame() {
    frame_arena.clear();
}

} // namespace pools
} // namespace jni
