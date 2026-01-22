#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class InviteBuilder {
public:
    virtual ~InviteBuilder() = default;
    InviteBuilder setMaxUses(int var1);

    InviteBuilder setTemporary(bool var1);

    InviteBuilder setMaxAge(int var1);

   Future<Invite> create();

   Future<Invite> create(FutureCallback<Invite> var1);
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
