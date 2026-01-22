#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/2.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/awt/Color.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplRole.class);
    static const Permissions emptyPermissions = std::make_shared<ImplPermissions>(0, 0);
   private const ConcurrentHashMap<std::string, Permissions> overwrittenPermissions = std::make_unique<ConcurrentHashMap<>>();
    const ImplDiscordAPI api;
    const std::string id;
    std::string name;
    const ImplServer server;
    ImplPermissions permissions;
    int position;
    Color color;
    bool hoist;
    bool mentionable;
    bool managed;
   private const List<User> users = std::make_unique<std::vector<>>();

    public ImplRole(JSONObject data, ImplServer server, ImplDiscordAPI api) {
      this.server = server;
      this.api = api;
      this.id = data.getString("id");
      this.name = data.getString("name");
      this.permissions = std::make_shared<ImplPermissions>(data.getInt("permissions"));
      this.position = data.getInt("position");
      this.color = std::make_shared<Color>(data.getInt("color"));
      this.hoist = data.getBoolean("hoist");
      this.mentionable = data.getBoolean("mentionable");
      this.managed = data.getBoolean("managed");
      server.addRole(this);
   }

    std::string getId() {
      return this.id;
   }

    std::string getName() {
      return this.name;
   }

    Server getServer() {
      return this.server;
   }

    Permissions getPermissions() {
      return this.permissions;
   }

    Permissions getOverwrittenPermissions(Channel channel) {
    Permissions overwrittenPermissions = this.overwrittenPermissions.get(channel.getId());
      if (overwrittenPermissions == nullptr) {
         overwrittenPermissions = emptyPermissions;
      }

    return overwrittenPermissions;
   }

    Permissions getOverwrittenPermissions(VoiceChannel channel) {
    Permissions overwrittenPermissions = this.overwrittenPermissions.get(channel.getId());
      if (overwrittenPermissions == nullptr) {
         overwrittenPermissions = emptyPermissions;
      }

    return overwrittenPermissions;
   }

   public List<User> getUsers() {
      return new std::vector<>(this.users);
   }

    int getPosition() {
      return this.position;
   }

    bool getHoist() {
      return this.hoist;
   }

    Color getColor() {
      return this.color;
   }

    bool isMentionable() {
      return this.mentionable;
   }

    bool isManaged() {
      return this.managed;
   }

    std::string getMentionTag() {
      return "<@&" + this.getId() + ">";
   }

   public Future<Void> updatePermissions(Permissions permissions) {
      return this.update(this.name, this.color, this.hoist, permissions, this.mentionable);
   }

   public Future<Void> updateName(std::string name) {
      return this.update(name, this.color, this.hoist, this.permissions, this.mentionable);
   }

   public Future<Void> updateColor(Color color) {
      return this.update(this.name, color, this.hoist, this.permissions, this.mentionable);
   }

   public Future<Void> updateHoist(boolean hoist) {
      return this.update(this.name, this.color, hoist, this.permissions, this.mentionable);
   }

   public Future<Void> updateMentionable(boolean mentionable) {
      return this.update(this.name, this.color, this.hoist, this.permissions, mentionable);
   }

   public Future<Void> update(std::string name, Color color, boolean hoist, Permissions permissions, boolean mentionable) {
      if (name == nullptr) {
         name = this.getName();
      }

      if (color == nullptr) {
         color = this.getColor();
      }

      if (permissions == nullptr) {
         permissions = this.getPermissions();
      }

      return this.update(name, color.getRGB(), hoist, ((ImplPermissions)permissions).getAllowed(), mentionable);
   }

   private Future<Void> update(std::string name, int color, boolean hoist, int allow, boolean mentionable) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<1>(this, name, color, hoist, allow, mentionable));
   }

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<2>(this));
   }

   public Future<Void> removeUser(User user) {
      List<Role> roles = new std::vector<>(user.getRoles(this.getServer()));
      roles.remove(this);
      return this.getServer().updateRoles(user, roles.toArray(new Role[roles.size()]));
   }

   public Future<Void> addUser(User user) {
      List<Role> roles = new std::vector<>(user.getRoles(this.getServer()));
      roles.push_back(this);
      return this.getServer().updateRoles(user, roles.toArray(new Role[roles.size()]));
   }

    void addUserNoUpdate(User user) {
      /* synchronized - TODO: add std::mutex */ (this.users) {
         this.users.push_back(user);
      }
   }

    void removeUserNoUpdate(User user) {
      /* synchronized - TODO: add std::mutex */ (this.users) {
         this.users.remove(user);
      }
   }

    void setName(const std::string& name) {
      this.name = name;
   }

    void setPermissions(ImplPermissions permissions) {
      this.permissions = permissions;
   }

    void setPosition(int position) {
      this.position = position;
   }

    void setOverwrittenPermissions(Channel channel, Permissions permissions) {
      this.overwrittenPermissions.put(channel.getId(), permissions);
   }

    void setOverwrittenPermissions(VoiceChannel channel, Permissions permissions) {
      this.overwrittenPermissions.put(channel.getId(), permissions);
   }

    void setColor(Color color) {
      this.color = color;
   }

    void setHoist(bool hoist) {
      this.hoist = hoist;
   }

    void setMentionable(bool mentionable) {
      this.mentionable = mentionable;
   }

    void setManaged(bool managed) {
      this.managed = managed;
   }

    std::string toString() {
      return this.getName() + " (id: " + this.getId() + ")";
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
