#include "zombie/core/profiling/AbstractPerformanceProfileProbe.h"

namespace zombie {
namespace core {
namespace profiling {

protected
AbstractPerformanceProfileProbe::AbstractPerformanceProfileProbe(
    const std::string &string) {
  // TODO: Implement AbstractPerformanceProfileProbe
  return nullptr;
}

void AbstractPerformanceProfileProbe::start() {
  // TODO: Implement start
}

bool AbstractPerformanceProfileProbe::isEnabled() {
  // TODO: Implement isEnabled
  return false;
}

void AbstractPerformanceProfileProbe::setEnabled(bool boolean0) {
  // TODO: Implement setEnabled
}

void AbstractPerformanceProfileProbe::end() {
  // TODO: Implement end
}

void AbstractPerformanceProfileProbe::invokeAndMeasure(Runnable runnable) {
  // TODO: Implement invokeAndMeasure
}

} // namespace profiling
} // namespace core
} // namespace zombie
