#include <vector>
#include "zombie/ai/KnownBlockedEdges.h"

namespace zombie {
namespace ai {

KnownBlockedEdges KnownBlockedEdges::init(KnownBlockedEdges var1) {
    return init(var1.x, var1.y, var1.z, var1.w, var1.n);
}

KnownBlockedEdges KnownBlockedEdges::init(int var1, int var2, int var3) {
    return init(var1, var2, var3, false, false);
}

KnownBlockedEdges KnownBlockedEdges::init(int var1, int var2, int var3, bool var4, bool var5) {
    x = var1;
    y = var2;
    z = var3;
    w = var4;
    n = var5;
    return *this;
}

bool KnownBlockedEdges::isBlocked(int var1, int var2) {
    // Ported from Java: return this.x > var1 && this.w ? true : this.y > var2 && this.n;
    if (x > var1 && w) return true;
    if (y > var2 && n) return true;
    return false;
}

KnownBlockedEdges KnownBlockedEdges::alloc() {
    // Match Java: assert server or main thread, then allocate from pool
    // NOTE: This assumes ObjectPool is implemented similarly in C++
    assert(GameServer::bServer || GameWindow::GameThread == std::this_thread::get_id());
    return pool.alloc();
}

void KnownBlockedEdges::releaseAll(std::vector<KnownBlockedEdges> &var0) {
    var0.clear();
}

void KnownBlockedEdges::release() {
    x = y = z = 0;
    w = n = false;
}

} // namespace ai
} // namespace zombie
