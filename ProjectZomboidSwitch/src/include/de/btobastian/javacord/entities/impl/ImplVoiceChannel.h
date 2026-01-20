#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/InviteBuilder.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/1.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/2.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/3.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/4.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/5.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/6.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/SnowflakeUtil.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplVoiceChannel.class);
    static const Permissions emptyPermissions = std::make_shared<ImplPermissions>(0, 0);
    const ImplDiscordAPI api;
    const std::string id;
    std::string name;
    int position;
    const ImplServer server;
    std::string parentId = nullptr;
   private const ConcurrentHashMap<std::string, Permissions> overwrittenPermissions = std::make_unique<ConcurrentHashMap<>>();
   private Set<User> connectedUsers = std::make_unique<std::unordered_set<>>();

    public ImplVoiceChannel(JSONObject data, ImplServer server, ImplDiscordAPI api) {
      this.api = api;
      this.server = server;
      this.id = data.getString("id");
      this.name = data.getString("name");
      this.position = data.getInt("position");
      if (data.has("parent_id") && !data.isNull("parent_id")) {
         this.parentId = data.getString("parent_id");
      }

    JSONArray permissionOverwrites = data.getJSONArray("permission_overwrites");

      for (int i = 0; i < permissionOverwrites.length(); i++) {
    JSONObject permissionOverwrite = permissionOverwrites.getJSONObject(i);
    std::string id = permissionOverwrite.getString("id");
    int allow = permissionOverwrite.getInt("allow");
    int deny = permissionOverwrite.getInt("deny");
    std::string type = permissionOverwrite.getString("type");
         if (type == "role")) {
    Role role = server.getRoleById(id);
            if (role != nullptr) {
               ((ImplRole)role).setOverwrittenPermissions(this, std::make_shared<ImplPermissions>(allow, deny));
            }
         }

         if (type == "member")) {
            this.overwrittenPermissions.put(id, std::make_shared<ImplPermissions>(allow, deny));
         }
      }

      server.addVoiceChannel(this);
   }

    std::string getId() {
      return this.id;
   }

    Calendar getCreationDate() {
      return SnowflakeUtil.parseDate(this.id);
   }

    std::string getName() {
      return this.name;
   }

    int getPosition() {
      return this.position;
   }

    Server getServer() {
      return this.server;
   }

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<1>(this));
   }

    InviteBuilder getInviteBuilder() {
      return std::make_shared<ImplInviteBuilder>(this, this.api);
   }

    Permissions getOverwrittenPermissions(User user) {
    Permissions permissions = this.overwrittenPermissions.get(user.getId());
    return permissions = = nullptr ? emptyPermissions : permissions;
   }

    Permissions getOverwrittenPermissions(Role role) {
      return role.getOverwrittenPermissions(this);
   }

   public Future<Void> updateOverwrittenPermissions(Role role, Permissions permissions) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<2>(this, role, permissions));
   }

   public Future<Void> updateOverwrittenPermissions(User user, Permissions permissions) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<3>(this, user, permissions));
   }

   public Future<Void> deleteOverwrittenPermissions(Role role) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<4>(this, role));
   }

   public Future<Void> deleteOverwrittenPermissions(User user) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<5>(this, user));
   }

   public Future<Void> updateName(std::string newName) {
      return this.update(newName, this.getPosition());
   }

   public Future<Void> updatePosition(int newPosition) {
      return this.update(this.getName(), newPosition);
   }

   public Future<Void> update(std::string newName, int newPosition) {
    JSONObject params = std::make_shared<JSONObject>().put("name", newName).put("position", newPosition);
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<6>(this, newName, newPosition, params));
   }

    void setName(const std::string& name) {
      this.name = name;
   }

    void setPosition(int position) {
      this.position = position;
   }

    void setOverwrittenPermissions(User user, Permissions permissions) {
      this.overwrittenPermissions.put(user.getId(), permissions);
   }

    void removeOverwrittenPermissions(User user) {
      this.overwrittenPermissions.remove(user.getId());
   }

    void addConnectedUser(User user) {
      this.connectedUsers.push_back(user);
   }

    void removeConnectedUser(User user) {
      this.connectedUsers.remove(user);
   }

    std::string getParentId() {
      return this.parentId;
   }

    void setParentId(const std::string& parentId) {
      this.parentId = parentId;
   }

   public const Set<User> getConnectedUsers() {
      return this.connectedUsers;
   }

    std::string toString() {
      return this.getName() + " (id: " + this.getId() + ")";
   }

    int hashCode() {
      return this.getId().hashCode();
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
