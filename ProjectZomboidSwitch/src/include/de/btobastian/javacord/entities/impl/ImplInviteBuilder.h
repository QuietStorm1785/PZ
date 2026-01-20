#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/entities/InviteBuilder.h"
#include "de/btobastian/javacord/entities/impl/ImplInviteBuilder/1.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplInviteBuilder {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplInviteBuilder.class);
    const ImplDiscordAPI api;
    const ImplChannel textChannel;
    const ImplVoiceChannel voiceChannel;
    int maxUses = -1;
    uint8_t temporary = -1;
    int maxAge = -1;

    public ImplInviteBuilder(ImplChannel textChannel, ImplDiscordAPI api) {
      this.textChannel = textChannel;
      this.voiceChannel = nullptr;
      this.api = api;
   }

    public ImplInviteBuilder(ImplVoiceChannel voiceChannel, ImplDiscordAPI api) {
      this.textChannel = nullptr;
      this.voiceChannel = voiceChannel;
      this.api = api;
   }

    InviteBuilder setMaxUses(int maxUses) {
      this.maxUses = maxUses;
    return this;
   }

    InviteBuilder setTemporary(bool temporary) {
      this.temporary = (byte)(temporary ? 1 : 0);
    return this;
   }

    InviteBuilder setMaxAge(int maxAge) {
      this.maxAge = maxAge;
    return this;
   }

   public Future<Invite> create() {
      return this.create(nullptr);
   }

   public Future<Invite> create(FutureCallback<Invite> callback) {
      ListenableFuture<Invite> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<1>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
