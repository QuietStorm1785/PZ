# Pathfinding Thread Pool Auto-Detection

**Date:** January 17, 2026  
**Status:** ✅ Implemented and Compiled

## Overview

Implemented intelligent CPU core detection for the pathfinding thread pool to automatically scale performance based on system hardware.

## Implementation Details

### Auto-Detection Logic

```cpp
int PathfindingThreadPool::getOptimalThreadCount() {
    unsigned int hwCores = std::thread::hardware_concurrency();
    
    if (hwCores == 0) {
        return DEFAULT_THREAD_COUNT;  // Fallback to 4
    }
    
    // Use half the cores for pathfinding (leave rest for game logic)
    // Min 2 threads, max 8 threads
    int optimalThreads = std::max(2, std::min(8, static_cast<int>(hwCores) / 2));
    
    return optimalThreads;
}
```

### Scaling Strategy

| CPU Cores | Pathfinding Threads | Game Logic Threads | Rationale |
|-----------|---------------------|-------------------|-----------|
| 2 | 2 | ~1 | Minimum viable (small systems) |
| 4 | 2 | ~2 | Typical dual-core systems |
| 8 | 4 | ~4 | Quad-core systems (balanced) |
| 16 | 8 | ~8 | High-end systems (capped at 8) |
| 32+ | 8 | Rest | Prevents thread overhead |

### Design Rationale

**Why Half the Cores?**
- Game logic needs CPU time for physics, rendering, AI
- Pathfinding is bursty (not always active)
- Prevents thread contention and context switching overhead

**Why Min 2 Threads?**
- Even on 2-core systems, parallel pathfinding helps
- Allows one zombie path while another computes

**Why Max 8 Threads?**
- Diminishing returns beyond 8 pathfinding threads
- Typical gameplay: 5-20 zombies, rarely need >8 concurrent paths
- Reduces memory overhead (each thread has stack)

## Changes Made

### Files Modified

1. **include/PathfindingThreadPool.h**
   - Added `static int getOptimalThreadCount()`
   - Changed `initialize()` default parameter to 0 (auto-detect)

2. **src/PathfindingThreadPool.cpp**
   - Implemented `getOptimalThreadCount()` with `std::thread::hardware_concurrency()`
   - Updated `initialize()` to call auto-detection when threadCount <= 0

3. **src/GameWindow.cpp**
   - Changed initialization to use `getOptimalThreadCount()`
   - Added logging of actual thread count used

## Usage

### Automatic (Recommended)
```cpp
auto* pool = PathfindingThreadPool::getInstance();
pool->initialize();  // Auto-detects optimal thread count
```

### Manual Override
```cpp
auto* pool = PathfindingThreadPool::getInstance();
pool->initialize(6);  // Force 6 threads
```

### Query Before Init
```cpp
int optimal = PathfindingThreadPool::getOptimalThreadCount();
std::cout << "Will use " << optimal << " threads" << std::endl;
pool->initialize(optimal);
```

## Testing Results

### Current System
- **Detected Cores:** 2
- **Optimal Threads:** 2 (max(2, min(8, 2/2)) = max(2, 1) = 2)
- **Compilation:** ✅ Success
- **Runtime:** Ready for testing

### Expected Behavior on Different Systems

**2-Core System (like current):**
```
Pathfinding thread pool initialized with 2 workers
```

**4-Core System:**
```
Pathfinding thread pool initialized with 2 workers
```

**8-Core System:**
```
Pathfinding thread pool initialized with 4 workers
```

**16-Core System:**
```
Pathfinding thread pool initialized with 8 workers
```

## Performance Implications

### Benefits
- **Scalability:** Automatically adapts to system hardware
- **No Configuration Required:** Works out-of-the-box
- **Balanced Resource Usage:** Leaves CPU for other game systems
- **Future-Proof:** Scales with more powerful hardware

### Trade-offs
- **2-Core Systems:** May experience higher CPU usage (50% dedicated to pathfinding)
- **High-End Systems:** Capped at 8 threads (could theoretically use more)
- **Detection Failures:** Falls back to 4 threads (safe default)

## Known Issues & Limitations

### Detection Failure Handling
If `std::thread::hardware_concurrency()` returns 0:
- Falls back to `DEFAULT_THREAD_COUNT = 4`
- Should never happen on modern systems
- Provides safe default for embedded/unusual platforms

### Thread Pool Overhead
- Each thread: ~8MB stack memory (typical)
- 8 threads = ~64MB overhead
- Negligible on modern systems (GB RAM)

### Context Switching
- More threads = more context switches
- Mitigated by capping at 8 threads
- Half-core strategy reduces contention

## Future Enhancements

### Dynamic Adjustment
```cpp
// Adjust thread count at runtime based on workload
if (avgQueueSize > 50) {
    pool->addWorker();  // Not yet implemented
} else if (avgQueueSize < 5) {
    pool->removeWorker();  // Not yet implemented
}
```

### Performance Profiling
- Monitor thread utilization
- Track queue wait times
- Adjust scaling formula based on real-world data

### Configuration File
```json
{
    "pathfinding": {
        "autoDetect": true,
        "manualThreadCount": 4,
        "scalingFactor": 0.5,
        "minThreads": 2,
        "maxThreads": 8
    }
}
```

## Compilation Status

```bash
cd /workspaces/PZ/PZ-Switch/build
make -j4

# Output:
[100%] Built target ProjectZomboidCpp
```

✅ **No errors, ready for runtime testing**

## Recommendations

### For Development
- Use auto-detection (default behavior)
- Monitor console output for thread count
- Profile with different zombie counts

### For Production
- Keep auto-detection enabled
- Add telemetry to track optimal thread counts
- Consider exposing as advanced user setting

### For Low-End Systems
- May want to cap lower (e.g., max 4 threads)
- Consider battery life on laptops
- Add power-saving mode

### For High-End Systems
- Current cap of 8 threads is conservative
- Could increase to 12 or 16 for heavily modded games
- Monitor queue saturation to determine if needed

## Integration with Other Systems

### Visibility System
- Pathfinding can query visibility for smarter paths
- Avoids routing through unexplored areas
- Both systems benefit from multi-core CPUs

### Zombie AI
- Each zombie can request path independently
- Priority system ensures nearby zombies get fast paths
- Thread pool prevents AI bottlenecks

### Performance Monitoring
```cpp
int pendingPaths = pool->getPendingRequestCount();
int completedPaths = pool->getCompletedRequestCount();
float utilization = (float)pendingPaths / (float)threadCount;

if (utilization > 0.9) {
    std::cout << "Warning: Pathfinding thread pool saturated!" << std::endl;
}
```

## Conclusion

The pathfinding thread pool now intelligently scales to system hardware:
- **2-core systems:** Uses 2 threads (efficient for small systems)
- **4-8 core systems:** Uses 2-4 threads (balanced performance)
- **16+ core systems:** Uses 8 threads (maximum benefit)

This ensures optimal performance across a wide range of hardware without requiring manual configuration.

**Next Steps:**
1. Runtime testing with varying zombie counts
2. Performance profiling on different CPU counts
3. Fine-tune scaling formula based on real-world data
