#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/URL.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class CustomEmoji {
public:
    virtual ~CustomEmoji() = default;
    std::string getId();

    Calendar getCreationDate();

    std::string getName();

    Server getServer();

    bool isManaged();

    bool requiresColons();

   Collection<Role> getRoles();

    std::string getMentionTag();

   Future<byte[]> getEmojiAsByteArray();

   Future<byte[]> getEmojiAsByteArray(FutureCallback<byte[]> var1);

   Future<BufferedImage> getEmoji();

   Future<BufferedImage> getEmoji(FutureCallback<BufferedImage> var1);

    URL getImageUrl();

   Future<Void> delete();
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
