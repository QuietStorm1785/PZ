#include <queue>
#include "zombie/core/opengl/RenderContextQueueItem.h"

namespace zombie {
namespace core {
namespace opengl {

private RenderContextQueueItem::RenderContextQueueItem() {
    // TODO: Implement RenderContextQueueItem
    return nullptr;
}

RenderContextQueueItem RenderContextQueueItem::alloc(Runnable var0) {
    // TODO: Implement alloc
    return nullptr;
}

void RenderContextQueueItem::resetInternal() {
    // TODO: Implement resetInternal
}

void RenderContextQueueItem::waitUntilFinished(BooleanSupplier var1) {
    // TODO: Implement waitUntilFinished
}

bool RenderContextQueueItem::isFinished() {
    // TODO: Implement isFinished
    return false;
}

void RenderContextQueueItem::setWaiting() {
    // TODO: Implement setWaiting
}

bool RenderContextQueueItem::isWaiting() {
    // TODO: Implement isWaiting
    return false;
}

void RenderContextQueueItem::invoke() {
    // TODO: Implement invoke
}

std::exception RenderContextQueueItem::getThrown() {
    // TODO: Implement getThrown
    return nullptr;
}

void RenderContextQueueItem::notifyWaitingListeners() {
    // TODO: Implement notifyWaitingListeners
}

} // namespace opengl
} // namespace core
} // namespace zombie
