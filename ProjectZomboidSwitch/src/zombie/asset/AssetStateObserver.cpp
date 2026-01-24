#include "zombie/asset/AssetStateObserver.h"

namespace zombie {
namespace asset {

void AssetStateObserver::onStateChanged(State var1, State var2, Asset var3) {
    // No-op by default; override in derived classes if needed
}

} // namespace asset
} // namespace zombie
