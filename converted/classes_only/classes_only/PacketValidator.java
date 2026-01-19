package zombie.network;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;
import java.util.Map.Entry;
import java.util.stream.Collectors;
import zombie.SystemDisabler;
import zombie.characters.Faction;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.characters.SafetySystemManager;
import zombie.commands.PlayerType;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.raknet.UdpConnection;
import zombie.core.utils.UpdateLimit;
import zombie.core.znet.SteamUtils;
import zombie.debug.DebugLog;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoUtils;
import zombie.iso.areas.NonPvpZone;
import zombie.network.PacketValidator.RecipeDetails;
import zombie.network.Userlog.UserlogType;
import zombie.network.packets.hit.Character;
import zombie.network.packets.hit.Hit;
import zombie.network.packets.hit.IMovable;
import zombie.network.packets.hit.IPositional;
import zombie.network.packets.hit.Player;
import zombie.network.packets.hit.Zombie;
import zombie.util.StringUtils;
import zombie.util.Type;

public class PacketValidator {
   private static final int SUSPICIOUS_ACTIVITIES_MAX = 4;
   private final UpdateLimit ulSuspiciousActivity = new UpdateLimit(150000L);
   public final HashMap<String, RecipeDetails> details = new HashMap<>();
   public final HashMap<String, RecipeDetails> detailsFromClient = new HashMap<>();
   private boolean failed = false;
   private static final long USER_LOG_INTERVAL_MS = 1000L;
   private static final int MAX_TYPE_3 = 10;
   private static final int MAX_TYPE_4 = 101;
   private final UdpConnection connection;
   private final UpdateLimit ulTimeMultiplier = new UpdateLimit(this.getTimeMultiplierTimeout());
   private final UpdateLimit ulRecipeChecksumInterval = new UpdateLimit(this.getChecksumInterval());
   private final UpdateLimit ulRecipeChecksumTimeout = new UpdateLimit(this.getChecksumTimeout());
   private int salt;
   private int suspiciousActivityCounter;
   private String suspiciousActivityDescription;

   public PacketValidator(UdpConnection var1) {
      this.connection = var1;
      this.suspiciousActivityCounter = 0;
   }

   public void reset() {
      this.salt = Rand.Next(Integer.MAX_VALUE);
   }

   private boolean isReady() {
      IsoPlayer var1 = GameServer.getPlayerByRealUserName(this.connection.username);
      return this.connection.isFullyConnected()
         && this.connection.isConnectionGraceIntervalTimeout()
         && !GameServer.bFastForward
         && var1 != null
         && var1.isAlive();
   }

   public int getSalt() {
      return this.salt;
   }

   private long getChecksumDelay() {
      return (long)(1000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

   private long getChecksumInterval() {
      return (long)(4000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

   private long getChecksumTimeout() {
      return (long)(10000.0 * ServerOptions.getInstance().AntiCheatProtectionType22ThresholdMultiplier.getValue());
   }

   public void failChecksum() {
      if (ServerOptions.instance.AntiCheatProtectionType21.getValue() && checkUser(this.connection)) {
         DebugLog.Multiplayer.warn("Checksum fail for \"%s\" (Type21)", new Object[]{this.connection.username});
         this.failed = true;
      }

      this.ulRecipeChecksumTimeout.Reset(this.getChecksumDelay());
   }

   public boolean isFailed() {
      return this.failed;
   }

   private void timeoutChecksum() {
      if (this.failed) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type21", this.getDescription());
      } else {
         if (ServerOptions.instance.AntiCheatProtectionType22.getValue() && checkUser(this.connection)) {
            doKickUser(this.connection, this.getClass().getSimpleName(), "Type22", null);
         }

         this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
      }
   }

   public void successChecksum() {
      this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
   }

   public void sendChecksum(boolean var1, boolean var2, boolean var3) {
      this.salt = Rand.Next(Integer.MAX_VALUE);
      GameServer.sendValidatePacket(this.connection, var1, var2, var3);
      this.ulRecipeChecksumInterval.Reset(this.getChecksumInterval());
   }

   private long getTimeMultiplierTimeout() {
      return (long)(10000.0 * ServerOptions.getInstance().AntiCheatProtectionType24ThresholdMultiplier.getValue());
   }

   public void failTimeMultiplier(float var1) {
      if (ServerOptions.instance.AntiCheatProtectionType23.getValue() && checkUser(this.connection)) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type23", String.valueOf(var1));
      }

      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

   public void timeoutTimeMultiplier() {
      if (ServerOptions.instance.AntiCheatProtectionType24.getValue() && checkUser(this.connection)) {
         doKickUser(this.connection, this.getClass().getSimpleName(), "Type24", null);
      }

      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

   public void successTimeMultiplier() {
      this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
   }

   public void update() {
      if (GameServer.bServer) {
         if (this.ulSuspiciousActivity.Check()) {
            this.updateSuspiciousActivityCounter();
         }

         if (this.isReady()) {
            if (!this.failed && this.ulRecipeChecksumInterval.Check()) {
               this.sendChecksum(false, false, false);
            }

            if (this.ulRecipeChecksumTimeout.Check()) {
               this.timeoutChecksum();
            }

            if (this.ulTimeMultiplier.Check()) {
               this.timeoutTimeMultiplier();
            }
         } else {
            this.ulRecipeChecksumInterval.Reset(this.getChecksumInterval());
            this.ulRecipeChecksumTimeout.Reset(this.getChecksumTimeout());
            this.ulTimeMultiplier.Reset(this.getTimeMultiplierTimeout());
            this.failed = false;
         }
      }
   }

   public static boolean checkPVP(UdpConnection var0, Character var1, Character var2, String var3) {
      boolean var4 = checkPVP(var1.getCharacter(), var2.getCharacter()) || SafetySystemManager.checkUpdateDelay(var1.getCharacter(), var2.getCharacter());
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType1.getValue() && checkUser(var0)) {
         doKickUser(var0, var3, "Type1", null);
      }

      return var4;
   }

   public static boolean checkSpeed(UdpConnection var0, IMovable var1, String var2) {
      float var3 = var1.getSpeed();
      double var4 = var1.isVehicle() ? ServerOptions.instance.SpeedLimit.getValue() : 10.0;
      boolean var6 = var3 <= var4 * ServerOptions.instance.AntiCheatProtectionType2ThresholdMultiplier.getValue();
      if (!var6 && ServerOptions.instance.AntiCheatProtectionType2.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type2", String.valueOf(var3));
      }

      return var6;
   }

   public static boolean checkLongDistance(UdpConnection var0, IPositional var1, IPositional var2, String var3) {
      float var4 = IsoUtils.DistanceTo(var2.getX(), var2.getY(), var1.getX(), var1.getY());
      boolean var5 = var4 <= var0.ReleventRange * 10 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(var0)) {
         if (var0.validator.checkSuspiciousActivity("Type3")) {
            doKickUser(var0, var3, "Type3", String.valueOf(var4));
         } else {
            doLogUser(var0, UserlogType.SuspiciousActivity, var3, "Type3");
         }
      }

      return var5;
   }

   public static boolean checkDamage(UdpConnection var0, Hit var1, String var2) {
      float var3 = var1.getDamage();
      boolean var4 = var3 <= 101.0 * ServerOptions.instance.AntiCheatProtectionType4ThresholdMultiplier.getValue();
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType4.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type4", String.valueOf(var3));
      }

      return var4;
   }

   public static boolean checkOwner(UdpConnection var0, Zombie var1, String var2) {
      IsoZombie var3 = (IsoZombie)var1.getCharacter();
      UdpConnection var4 = var3.authOwner;
      boolean var5 = var4 == var0 && System.currentTimeMillis() - var3.lastChangeOwner > 2000L;
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType5.getValue() && checkUser(var0)) {
         if (var0.validator.checkSuspiciousActivity("Type5")) {
            doKickUser(var0, var2, "Type5", Optional.ofNullable(var4).map(var0x -> var0x.username).orElse(""));
         } else {
            doLogUser(var0, UserlogType.SuspiciousActivity, var2, "Type5");
         }
      }

      return var5;
   }

   public static boolean checkTarget(UdpConnection var0, Player var1, String var2) {
      IsoPlayer var3 = var1.getPlayer();
      boolean var4 = Arrays.stream(var0.players).anyMatch(var1x -> var1x.getOnlineID() == var3.getOnlineID());
      if (!var4 && ServerOptions.instance.AntiCheatProtectionType6.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type6", var3.getUsername());
      }

      return var4;
   }

   public static boolean checkSafehouseAuth(UdpConnection var0, String var1, String var2) {
      boolean var3 = StringUtils.isNullOrEmpty(var1) || var1.equals(var0.username) || var0.accessLevel >= 16;
      if (!var3 && ServerOptions.instance.AntiCheatProtectionType7.getValue() && checkUser(var0)) {
         doKickUser(var0, var2, "Type7", var1);
      }

      return var3;
   }

   public static boolean checkShortDistance(UdpConnection var0, IPositional var1, IPositional var2, String var3) {
      float var4 = IsoUtils.DistanceTo(var2.getX(), var2.getY(), var1.getX(), var1.getY());
      boolean var5 = var4 <= 10.0 * ServerOptions.instance.AntiCheatProtectionType3ThresholdMultiplier.getValue();
      if (!var5 && ServerOptions.instance.AntiCheatProtectionType3.getValue() && checkUser(var0)) {
         doKickUser(var0, var3, "Type3", String.valueOf(var4));
      }

      return var5;
   }

   private static boolean isUntouchable(UdpConnection var0) {
      return !var0.isFullyConnected()
         || PlayerType.isPrivileged(var0.accessLevel)
         || Arrays.stream(var0.players).filter(Objects::nonNull).anyMatch(IsoGameCharacter::isGodMod);
   }

   public static boolean checkUser(UdpConnection var0) {
      return doAntiCheatProtection() && !isUntouchable(var0);
   }

   public boolean checkSuspiciousActivity(String var1) {
      if (this.suspiciousActivityCounter <= 4) {
         this.suspiciousActivityCounter++;
         this.suspiciousActivityDescription = String.format("player=\"%s\" type=\"%s\"", this.connection.username, var1);
         DebugLog.Multiplayer.noise("SuspiciousActivity increase: counter=%d %s", this.suspiciousActivityCounter, this.suspiciousActivityDescription);
      }

      return this.suspiciousActivityCounter > 4;
   }

   public void updateSuspiciousActivityCounter() {
      if (this.suspiciousActivityCounter > 0) {
         this.suspiciousActivityCounter--;
         DebugLog.Multiplayer
            .warn("SuspiciousActivity decrease: counter=%d %s", new Object[]{this.suspiciousActivityCounter, this.suspiciousActivityDescription});
      } else {
         this.suspiciousActivityCounter = 0;
      }
   }

   public static void doLogUser(UdpConnection var0, UserlogType var1, String var2, String var3) {
      long var4 = System.currentTimeMillis();
      DebugLog.Multiplayer.warn("Log: player=\"%s\" type=\"%s\" issuer=\"%s\"", new Object[]{var0.username, var2, var3});
      if (var4 > var0.lastUnauthorizedPacket) {
         var0.lastUnauthorizedPacket = var4 + 1000L;
         ServerWorldDatabase.instance.addUserlog(var0.username, var1, var2, "AntiCheat" + var3, 1);
      }
   }

   public static void doKickUser(UdpConnection var0, String var1, String var2, String var3) {
      ServerWorldDatabase.instance.addUserlog(var0.username, UserlogType.Kicked, var1, "AntiCheat" + var2, 1);
      DebugLog.Multiplayer.warn("Kick: player=\"%s\" type=\"%s\" issuer=\"%s\" description=\"%s\"", new Object[]{var0.username, var1, var2, var3});
      GameServer.kick(var0, "UI_Policy_Kick", var2);
      var0.forceDisconnect(var1);
      GameServer.addDisconnect(var0);
   }

   public static void doBanUser(UdpConnection var0, String var1, String var2) throws Exception {
      ServerWorldDatabase.instance.addUserlog(var0.username, UserlogType.Banned, var1, "AntiCheat" + var2, 1);
      DebugLog.Multiplayer.warn("Ban: player=\"%s\" type=\"%s\" issuer=\"%s\"", new Object[]{var0.username, var1, var2});
      ServerWorldDatabase.instance.banUser(var0.username, true);
      if (SteamUtils.isSteamModeEnabled()) {
         String var3 = SteamUtils.convertSteamIDToString(var0.steamID);
         ServerWorldDatabase.instance.banSteamID(var3, var1, true);
      } else {
         ServerWorldDatabase.instance.banIp(var0.ip, var0.username, var1, true);
      }

      GameServer.kick(var0, "UI_Policy_Ban", var2);
      var0.forceDisconnect(var1);
      GameServer.addDisconnect(var0);
   }

   private static boolean checkPVP(IsoGameCharacter var0, IsoMovingObject var1) {
      IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var0, IsoPlayer.class);
      IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var3 != null) {
         if (var3.isGodMod()
            || !ServerOptions.instance.PVP.getValue()
            || ServerOptions.instance.SafetySystem.getValue() && var0.getSafety().isEnabled() && ((IsoGameCharacter)var1).getSafety().isEnabled()) {
            return false;
         }

         if (NonPvpZone.getNonPvpZone((int)var1.getX(), (int)var1.getY()) != null) {
            return false;
         }

         if (var2 != null && NonPvpZone.getNonPvpZone((int)var0.getX(), (int)var0.getY()) != null) {
            return false;
         }

         if (var2 != null && !var2.factionPvp && !var3.factionPvp) {
            Faction var4 = Faction.getPlayerFaction(var2);
            Faction var5 = Faction.getPlayerFaction(var3);
            if (var5 != null && var4 == var5) {
               return false;
            }
         }
      }

      return true;
   }

   public static boolean doAntiCheatProtection() {
      return !GameServer.bCoop && (!Core.bDebug || SystemDisabler.doKickInDebug);
   }

   public String getDescription() {
      StringBuilder var1 = new StringBuilder("Recipes CRC details");
      if (GameServer.bServer) {
         Set var2 = this.details
            .entrySet()
            .stream()
            .filter(var1x -> this.detailsFromClient.get(var1x.getKey()) != null && this.detailsFromClient.get(var1x.getKey()).crc == var1x.getValue().crc)
            .map(Entry::getKey)
            .collect(Collectors.toSet());
         var2.forEach(var1x -> {
            this.detailsFromClient.remove(var1x);
            this.details.remove(var1x);
         });
         var1.append("\nServer start size=").append(this.details.size());
         this.details.values().forEach(var1x -> var1.append(var1x.getDescription()));
         var1.append("\nServer end\nClient start size=").append(this.detailsFromClient.size());
         this.detailsFromClient.values().forEach(var1x -> var1.append(var1x.getDescription()));
         var1.append("\nClient end");
      }

      return var1.toString();
   }
}
