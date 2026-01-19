package zombie.vehicles;

import gnu.trove.list.array.TShortArrayList;
import gnu.trove.map.hash.TShortShortHashMap;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import org.joml.Quaternionf;
import org.joml.Vector3f;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.SoundManager;
import zombie.Lua.LuaEventManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.network.ByteBufferWriter;
import zombie.core.physics.Bullet;
import zombie.core.physics.Transform;
import zombie.core.physics.WorldSimulation;
import zombie.core.raknet.UdpConnection;
import zombie.core.utils.UpdateLimit;
import zombie.debug.DebugLog;
import zombie.inventory.InventoryItem;
import zombie.inventory.types.DrainableComboItem;
import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes;
import zombie.network.PacketTypes.PacketType;
import zombie.network.packets.VehicleAuthorizationPacket;
import zombie.network.packets.vehicle.Physics;
import zombie.scripting.objects.VehicleScript.Model;
import zombie.util.Type;
import zombie.vehicles.BaseVehicle.Authorization;
import zombie.vehicles.BaseVehicle.ModelInfo;
import zombie.vehicles.BaseVehicle.ServerVehicleState;
import zombie.vehicles.BaseVehicle.engineStateTypes;
import zombie.vehicles.VehicleManager.1;
import zombie.vehicles.VehicleManager.PosUpdateVars;

public final class VehicleManager {
   public static VehicleManager instance;
   private final VehicleIDMap IDToVehicle = VehicleIDMap.instance;
   private final ArrayList<BaseVehicle> vehicles = new ArrayList<>();
   private boolean idMapDirty = true;
   private final Transform tempTransform = new Transform();
   private final ArrayList<BaseVehicle> sendReliable = new ArrayList<>();
   private final ArrayList<BaseVehicle> sendUnreliable = new ArrayList<>();
   private final TShortArrayList vehiclesWaitUpdates = new TShortArrayList(128);
   private final TShortShortHashMap towedVehicleMap = new TShortShortHashMap();
   public static HashMap<Byte, String> vehiclePacketTypes = new HashMap<>();
   public final UdpConnection[] connected = new UdpConnection[512];
   private final float[] tempFloats = new float[27];
   private final float[] engineSound = new float[2];
   private final PosUpdateVars posUpdateVars = new PosUpdateVars();
   private final UpdateLimit vehiclesWaitUpdatesFrequency = new UpdateLimit(1000L);
   private BaseVehicle tempVehicle;
   private final ArrayList<ModelInfo> oldModels = new ArrayList<>();
   private final ArrayList<ModelInfo> curModels = new ArrayList<>();
   private final UpdateLimit sendRequestGetPositionFrequency = new UpdateLimit(500L);
   private final UpdateLimit VehiclePhysicSyncPacketLimit = new UpdateLimit(500L);

   public void registerVehicle(BaseVehicle var1) {
      this.IDToVehicle.put(var1.VehicleID, var1);
      this.idMapDirty = true;
   }

   public void unregisterVehicle(BaseVehicle var1) {
      this.IDToVehicle.remove(var1.VehicleID);
      this.idMapDirty = true;
   }

   public BaseVehicle getVehicleByID(short var1) {
      return this.IDToVehicle.get(var1);
   }

   public ArrayList<BaseVehicle> getVehicles() {
      if (this.idMapDirty) {
         this.vehicles.clear();
         this.IDToVehicle.toArrayList(this.vehicles);
         this.idMapDirty = false;
      }

      return this.vehicles;
   }

   public void removeFromWorld(BaseVehicle var1) {
      if (var1.VehicleID != -1) {
         DebugLog.Vehicle.trace("removeFromWorld vehicle id=%d", var1.VehicleID);
         this.unregisterVehicle(var1);
         if (GameServer.bServer) {
            for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
               UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
               if (var1.connectionState[var3.index] != null) {
                  ByteBufferWriter var4 = var3.startPacket();
                  PacketType.Vehicles.doPacket(var4);
                  var4.bb.put((byte)8);
                  var4.bb.putShort(var1.VehicleID);
                  PacketType.Vehicles.send(var3);
               }
            }
         }

         if (GameClient.bClient) {
            var1.serverRemovedFromWorld = false;
            if (var1.interpolation != null) {
               var1.interpolation.clear();
            }
         }
      }
   }

   public void serverUpdate() {
      ArrayList var1 = IsoWorld.instance.CurrentCell.getVehicles();

      for (int var2 = 0; var2 < this.connected.length; var2++) {
         if (this.connected[var2] != null && !GameServer.udpEngine.connections.contains(this.connected[var2])) {
            DebugLog.Vehicle.trace("vehicles: dropped connection %d", var2);

            for (int var8 = 0; var8 < var1.size(); var8++) {
               ((BaseVehicle)var1.get(var8)).connectionState[var2] = null;
            }

            this.connected[var2] = null;
         } else {
            for (int var3 = 0; var3 < var1.size(); var3++) {
               if (((BaseVehicle)var1.get(var3)).connectionState[var2] != null) {
                  ServerVehicleState var10000 = ((BaseVehicle)var1.get(var3)).connectionState[var2];
                  var10000.flags = (short)(var10000.flags | ((BaseVehicle)var1.get(var3)).updateFlags);
               }
            }
         }
      }

      for (int var6 = 0; var6 < GameServer.udpEngine.connections.size(); var6++) {
         UdpConnection var9 = (UdpConnection)GameServer.udpEngine.connections.get(var6);
         this.sendVehicles(var9, PacketType.VehiclesUnreliable.getId());
         this.connected[var9.index] = var9;
      }

      for (int var7 = 0; var7 < var1.size(); var7++) {
         BaseVehicle var10 = (BaseVehicle)var1.get(var7);
         if ((var10.updateFlags & 19440) != 0) {
            for (int var4 = 0; var4 < var10.getPartCount(); var4++) {
               VehiclePart var5 = var10.getPartByIndex(var4);
               var5.updateFlags = 0;
            }
         }

         var10.updateFlags = 0;
      }
   }

   private void sendVehicles(UdpConnection var1, short var2) {
      if (var1.isFullyConnected()) {
         this.sendReliable.clear();
         this.sendUnreliable.clear();
         ArrayList var3 = IsoWorld.instance.CurrentCell.getVehicles();

         for (int var4 = 0; var4 < var3.size(); var4++) {
            BaseVehicle var5 = (BaseVehicle)var3.get(var4);
            if (var5.VehicleID == -1) {
               var5.VehicleID = this.IDToVehicle.allocateID();
               this.registerVehicle(var5);
            }

            if (var1.RelevantTo(var5.x, var5.y)) {
               if (var5.connectionState[var1.index] == null) {
                  var5.connectionState[var1.index] = new ServerVehicleState();
               }

               ServerVehicleState var6 = var5.connectionState[var1.index];
               if (var6.shouldSend(var5)) {
                  if (!var5.isReliable && PacketType.Vehicles.getId() != var2) {
                     this.sendUnreliable.add(var5);
                  } else {
                     this.sendReliable.add(var5);
                  }
               }
            }
         }

         this.sendVehiclesInternal(var1, this.sendReliable, PacketType.Vehicles);
         this.sendVehiclesInternal(var1, this.sendUnreliable, PacketType.VehiclesUnreliable);
      }
   }

   private void sendVehiclesInternal(UdpConnection var1, ArrayList<BaseVehicle> var2, PacketType var3) {
      if (!var2.isEmpty()) {
         ByteBufferWriter var4 = var1.startPacket();
         var3.doPacket(var4);

         try {
            ByteBuffer var5 = var4.bb;
            var5.put((byte)5);
            var5.putShort((short)var2.size());

            for (int var6 = 0; var6 < var2.size(); var6++) {
               BaseVehicle var7 = (BaseVehicle)var2.get(var6);
               ServerVehicleState var8 = var7.connectionState[var1.index];
               var5.putShort(var7.VehicleID);
               var5.putShort(var8.flags);
               var5.putFloat(var7.x);
               var5.putFloat(var7.y);
               var5.putFloat(var7.jniTransform.origin.y);
               int var9 = var5.position();
               var5.putShort((short)0);
               int var10 = var5.position();
               boolean var11 = (var8.flags & 1) != 0;
               if (var11) {
                  var8.flags = (short)(var8.flags & -2);
                  var7.netPlayerServerSendAuthorisation(var5);
                  var8.setAuthorization(var7);
                  int var32 = var5.position();
                  var5.putShort((short)0);
                  var7.save(var5);
                  int var40 = var5.position();
                  var5.position(var32);
                  var5.putShort((short)(var40 - var32));
                  var5.position(var40);
                  int var42 = var5.position();
                  int var15 = var5.position() - var10;
                  var5.position(var9);
                  var5.putShort((short)var15);
                  var5.position(var42);
                  this.writePositionOrientation(var5, var7);
                  var8.x = var7.x;
                  var8.y = var7.y;
                  var8.z = var7.jniTransform.origin.y;
                  var8.orient.set(var7.savedRot);
               } else {
                  if ((var8.flags & 2) != 0) {
                     this.writePositionOrientation(var5, var7);
                     var8.x = var7.x;
                     var8.y = var7.y;
                     var8.z = var7.jniTransform.origin.y;
                     var8.orient.set(var7.savedRot);
                  }

                  if ((var8.flags & 4) != 0) {
                     var5.put((byte)var7.engineState.ordinal());
                     var5.putInt(var7.engineLoudness);
                     var5.putInt(var7.enginePower);
                     var5.putInt(var7.engineQuality);
                  }

                  if ((var8.flags & 4096) != 0) {
                     var5.put((byte)(var7.isHotwired() ? 1 : 0));
                     var5.put((byte)(var7.isHotwiredBroken() ? 1 : 0));
                     var5.putFloat(var7.getRegulatorSpeed());
                     var5.put((byte)(var7.isPreviouslyEntered() ? 1 : 0));
                     var5.put((byte)(var7.isKeysInIgnition() ? 1 : 0));
                     var5.put((byte)(var7.isKeyIsOnDoor() ? 1 : 0));
                     InventoryItem var12 = var7.getCurrentKey();
                     if (var12 == null) {
                        var5.put((byte)0);
                     } else {
                        var5.put((byte)1);
                        var12.saveWithSize(var5, false);
                     }

                     var5.putFloat(var7.getRust());
                     var5.putFloat(var7.getBloodIntensity("Front"));
                     var5.putFloat(var7.getBloodIntensity("Rear"));
                     var5.putFloat(var7.getBloodIntensity("Left"));
                     var5.putFloat(var7.getBloodIntensity("Right"));
                     var5.putFloat(var7.getColorHue());
                     var5.putFloat(var7.getColorSaturation());
                     var5.putFloat(var7.getColorValue());
                     var5.putInt(var7.getSkinIndex());
                  }

                  if ((var8.flags & 8) != 0) {
                     var5.put((byte)(var7.getHeadlightsOn() ? 1 : 0));
                     var5.put((byte)(var7.getStoplightsOn() ? 1 : 0));

                     for (int var23 = 0; var23 < var7.getLightCount(); var23++) {
                        var5.put((byte)(var7.getLightByIndex(var23).getLight().getActive() ? 1 : 0));
                     }
                  }

                  if ((var8.flags & 1024) != 0) {
                     var5.put((byte)(var7.soundHornOn ? 1 : 0));
                     var5.put((byte)(var7.soundBackMoveOn ? 1 : 0));
                     var5.put((byte)var7.lightbarLightsMode.get());
                     var5.put((byte)var7.lightbarSirenMode.get());
                  }

                  if ((var8.flags & 2048) != 0) {
                     for (int var24 = 0; var24 < var7.getPartCount(); var24++) {
                        VehiclePart var13 = var7.getPartByIndex(var24);
                        if ((var13.updateFlags & 2048) != 0) {
                           var5.put((byte)var24);
                           var5.putInt(var13.getCondition());
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 16) != 0) {
                     for (int var25 = 0; var25 < var7.getPartCount(); var25++) {
                        VehiclePart var33 = var7.getPartByIndex(var25);
                        if ((var33.updateFlags & 16) != 0) {
                           var5.put((byte)var25);
                           var33.getModData().save(var5);
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 32) != 0) {
                     for (int var26 = 0; var26 < var7.getPartCount(); var26++) {
                        VehiclePart var34 = var7.getPartByIndex(var26);
                        if ((var34.updateFlags & 32) != 0) {
                           InventoryItem var14 = var34.getInventoryItem();
                           if (var14 instanceof DrainableComboItem) {
                              var5.put((byte)var26);
                              var5.putFloat(((DrainableComboItem)var14).getUsedDelta());
                           }
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 128) != 0) {
                     for (int var27 = 0; var27 < var7.getPartCount(); var27++) {
                        VehiclePart var35 = var7.getPartByIndex(var27);
                        if ((var35.updateFlags & 128) != 0) {
                           var5.put((byte)var27);
                           InventoryItem var41 = var35.getInventoryItem();
                           if (var41 == null) {
                              var5.put((byte)0);
                           } else {
                              var5.put((byte)1);

                              try {
                                 var35.getInventoryItem().saveWithSize(var5, false);
                              } catch (Exception var16) {
                                 var16.printStackTrace();
                              }
                           }
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 512) != 0) {
                     for (int var28 = 0; var28 < var7.getPartCount(); var28++) {
                        VehiclePart var36 = var7.getPartByIndex(var28);
                        if ((var36.updateFlags & 512) != 0) {
                           var5.put((byte)var28);
                           var36.getDoor().save(var5);
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 256) != 0) {
                     for (int var29 = 0; var29 < var7.getPartCount(); var29++) {
                        VehiclePart var37 = var7.getPartByIndex(var29);
                        if ((var37.updateFlags & 256) != 0) {
                           var5.put((byte)var29);
                           var37.getWindow().save(var5);
                        }
                     }

                     var5.put((byte)-1);
                  }

                  if ((var8.flags & 64) != 0) {
                     var5.put((byte)var7.models.size());

                     for (int var30 = 0; var30 < var7.models.size(); var30++) {
                        ModelInfo var38 = (ModelInfo)var7.models.get(var30);
                        var5.put((byte)var38.part.getIndex());
                        var5.put((byte)var38.part.getScriptPart().models.indexOf(var38.scriptModel));
                     }
                  }

                  int var31 = var5.position();
                  int var39 = var5.position() - var10;
                  var5.position(var9);
                  var5.putShort((short)var39);
                  var5.position(var31);
               }
            }

            var3.send(var1);
         } catch (Exception var17) {
            var1.cancelPacket();
            var17.printStackTrace();
         }

         for (int var18 = 0; var18 < var2.size(); var18++) {
            BaseVehicle var19 = (BaseVehicle)var2.get(var18);
            ServerVehicleState var20 = var19.connectionState[var1.index];
            if ((var20.flags & 16384) != 0) {
               VehicleAuthorizationPacket var21 = new VehicleAuthorizationPacket();
               var21.set(var19, var1);
               ByteBufferWriter var22 = var1.startPacket();
               PacketType.VehicleAuthorization.doPacket(var22);
               var21.write(var22);
               PacketType.VehicleAuthorization.send(var1);
            }
         }
      }
   }

   public void serverPacket(ByteBuffer var1, UdpConnection var2, short var3) {
      byte var4 = var1.get();
      switch (var4) {
         case 1:
            short var19 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var4), var19);
            byte var27 = var1.get();
            String var34 = GameWindow.ReadString(var1);
            BaseVehicle var41 = this.IDToVehicle.get(var19);
            if (var41 != null) {
               IsoGameCharacter var46 = var41.getCharacter(var27);
               if (var46 != null) {
                  var41.setCharacterPosition(var46, var27, var34);
                  this.sendPassengerPosition(var41, var27, var34, var2);
               }
            }
            break;
         case 2:
            short var18 = var1.getShort();
            short var26 = var1.getShort();
            byte var33 = var1.get();
            DebugLog.Vehicle.trace("Vehicle enter vid=%d pid=%d seat=%d", var18, var26, Integer.valueOf(var33));
            BaseVehicle var40 = this.IDToVehicle.get(var18);
            if (var40 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var18});
            } else {
               IsoPlayer var45 = (IsoPlayer)GameServer.IDToPlayerMap.get(var26);
               if (var45 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var26});
               } else {
                  IsoPlayer var48 = (IsoPlayer)Type.tryCastTo(var40.getCharacter(var33), IsoPlayer.class);
                  if (var48 != null && var48 != var45) {
                     DebugLog.Vehicle.warn(var45.getUsername() + " got in same seat as " + var48.getUsername());
                  } else {
                     var40.enter(var33, var45);
                     if (var33 == 0 && var40.isNetPlayerAuthorization(Authorization.Server)) {
                        var40.authorizationServerOnSeat(var45, true);
                     }

                     this.sendEnter(var40, var45, var33);
                  }
               }
            }
            break;
         case 3:
            short var17 = var1.getShort();
            short var25 = var1.getShort();
            byte var32 = var1.get();
            DebugLog.Vehicle.trace("Vehicle exit vid=%d pid=%d seat=%d", var17, var25, Integer.valueOf(var32));
            BaseVehicle var39 = this.IDToVehicle.get(var17);
            if (var39 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var17});
            } else {
               IsoPlayer var44 = (IsoPlayer)GameServer.IDToPlayerMap.get(var25);
               if (var44 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var25});
               } else {
                  var39.exit(var44);
                  if (var32 == 0) {
                     var39.authorizationServerOnSeat(var44, false);
                  }

                  this.sendExit(var39, var44, var32);
               }
            }
            break;
         case 4:
            short var16 = var1.getShort();
            short var24 = var1.getShort();
            byte var31 = var1.get();
            byte var38 = var1.get();
            DebugLog.Vehicle.trace("Vehicle switch seat vid=%d pid=%d seats=%d=>%d", var16, var24, Integer.valueOf(var31), Integer.valueOf(var38));
            BaseVehicle var43 = this.IDToVehicle.get(var16);
            if (var43 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var16});
            } else {
               IsoPlayer var47 = (IsoPlayer)GameServer.IDToPlayerMap.get(var24);
               if (var47 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var24});
               } else {
                  IsoPlayer var11 = (IsoPlayer)Type.tryCastTo(var43.getCharacter(var38), IsoPlayer.class);
                  if (var11 != null && var11 != var47) {
                     DebugLog.Vehicle.warn(var47.getUsername() + " switched to same seat as " + var11.getUsername());
                  } else {
                     var43.switchSeat(var47, var38);
                     if (var38 == 0 && var43.isNetPlayerAuthorization(Authorization.Server)) {
                        var43.authorizationServerOnSeat(var47, true);
                     } else if (var31 == 0) {
                        var43.authorizationServerOnSeat(var47, false);
                     }

                     this.sendSwitchSeat(var43, var47, var31, var38);
                  }
               }
            }
            break;
         case 5:
         case 6:
         case 7:
         case 8:
         case 10:
         case 13:
         case 14:
         default:
            DebugLog.Vehicle.warn("Unknown vehicle packet %d", new Object[]{var4});
            break;
         case 9:
            Physics var15 = new Physics();
            var15.parse(var1, var2);
            var15.process();

            for (int var23 = 0; var23 < GameServer.udpEngine.connections.size(); var23++) {
               UdpConnection var30 = (UdpConnection)GameServer.udpEngine.connections.get(var23);
               if (var2 != var30 && var15.isRelevant(var30)) {
                  ByteBufferWriter var37 = var30.startPacket();
                  PacketType var42 = (PacketType)PacketTypes.packetTypes.get(var3);
                  var42.doPacket(var37);
                  var37.bb.put((byte)9);
                  var15.write(var37);
                  var42.send(var30);
               }
            }
            break;
         case 11:
            short var14 = var1.getShort();

            for (int var22 = 0; var22 < var14; var22++) {
               short var29 = var1.getShort();
               DebugLog.Vehicle.trace("Vehicle vid=%d full update response ", var29);
               BaseVehicle var36 = this.IDToVehicle.get(var29);
               if (var36 != null) {
                  if (var36.connectionState[var2.index] == null) {
                     var36.connectionState[var2.index] = new ServerVehicleState();
                  }

                  var36.connectionState[var2.index].flags = (short)(var36.connectionState[var2.index].flags | 1);
                  this.sendVehicles(var2, var3);
               }
            }
            break;
         case 12:
            short var13 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var4), var13);
            BaseVehicle var21 = this.IDToVehicle.get(var13);
            if (var21 != null) {
               var21.updateFlags = (short)(var21.updateFlags | 2);
               this.sendVehicles(var2, var3);
            }
            break;
         case 15:
            short var12 = var1.getShort();
            short var20 = var1.getShort();
            boolean var28 = var1.get() == 1;
            DebugLog.Vehicle.trace("%s vid=%d pid=%d %b", vehiclePacketTypes.get(var4), var12, var20, var28);
            BaseVehicle var35 = this.IDToVehicle.get(var12);
            if (var35 != null) {
               var35.authorizationServerCollide(var20, var28);
            }
            break;
         case 16:
            short var5 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var4), var5);
            byte var6 = var1.get();
            BaseVehicle var7 = this.IDToVehicle.get(var5);
            if (var7 != null) {
               for (int var8 = 0; var8 < GameServer.udpEngine.connections.size(); var8++) {
                  UdpConnection var9 = (UdpConnection)GameServer.udpEngine.connections.get(var8);
                  if (var9 != var2) {
                     ByteBufferWriter var10 = var9.startPacket();
                     PacketType.Vehicles.doPacket(var10);
                     var10.bb.put((byte)16);
                     var10.bb.putShort(var7.VehicleID);
                     var10.bb.put(var6);
                     PacketType.Vehicles.send(var9);
                  }
               }
            }
      }
   }

   public void serverSendInitialWorldState(UdpConnection var1) {
      ByteBufferWriter var2 = var1.startPacket();
      PacketType.Vehicles.doPacket(var2);
      var2.bb.put((byte)19);
      var2.bb.putShort((short)this.towedVehicleMap.size());
      this.towedVehicleMap.forEachEntry((var1x, var2x) -> {
         var2.putShort(var1x);
         var2.putShort(var2x);
         return true;
      });
      PacketType.Vehicles.send(var1);
   }

   private void vehiclePosUpdate(BaseVehicle var1, float[] var2) {
      int var3 = 0;
      Transform var4 = this.posUpdateVars.transform;
      Vector3f var5 = this.posUpdateVars.vector3f;
      Quaternionf var6 = this.posUpdateVars.quatf;
      float[] var7 = this.posUpdateVars.wheelSteer;
      float[] var8 = this.posUpdateVars.wheelRotation;
      float[] var9 = this.posUpdateVars.wheelSkidInfo;
      float[] var10 = this.posUpdateVars.wheelSuspensionLength;
      float var11 = var2[var3++] - WorldSimulation.instance.offsetX;
      float var12 = var2[var3++] - WorldSimulation.instance.offsetY;
      float var13 = var2[var3++];
      var4.origin.set(var11, var13, var12);
      float var14 = var2[var3++];
      float var15 = var2[var3++];
      float var16 = var2[var3++];
      float var17 = var2[var3++];
      var6.set(var14, var15, var16, var17);
      var6.normalize();
      var4.setRotation(var6);
      float var18 = var2[var3++];
      float var19 = var2[var3++];
      float var20 = var2[var3++];
      var5.set(var18, var19, var20);
      int var21 = (int)var2[var3++];

      for (int var22 = 0; var22 < var21; var22++) {
         var7[var22] = var2[var3++];
         var8[var22] = var2[var3++];
         var9[var22] = var2[var3++];
         var10[var22] = var2[var3++];
      }

      var1.jniTransform.set(var4);
      var1.jniLinearVelocity.set(var5);
      var1.jniTransform.basis.getScale(var5);
      if (var5.x < 0.99 || var5.y < 0.99 || var5.z < 0.99) {
         var1.jniTransform.basis.scale(1.0F / var5.x, 1.0F / var5.y, 1.0F / var5.z);
      }

      var1.jniSpeed = var1.jniLinearVelocity.length() * 3.6F;
      Vector3f var38 = var1.getForwardVector(BaseVehicle.allocVector3f());
      if (var38.dot(var1.jniLinearVelocity) < 0.0F) {
         var1.jniSpeed *= -1.0F;
      }

      BaseVehicle.releaseVector3f(var38);

      for (int var23 = 0; var23 < 4; var23++) {
         var1.wheelInfo[var23].steering = var7[var23];
         var1.wheelInfo[var23].rotation = var8[var23];
         var1.wheelInfo[var23].skidInfo = var9[var23];
         var1.wheelInfo[var23].suspensionLength = var10[var23];
      }

      var1.polyDirty = true;
   }

   public void clientUpdate() {
      if (this.vehiclesWaitUpdatesFrequency.Check()) {
         if (this.vehiclesWaitUpdates.size() > 0) {
            ByteBufferWriter var1 = GameClient.connection.startPacket();
            PacketType.Vehicles.doPacket(var1);
            var1.bb.put((byte)11);
            var1.bb.putShort((short)this.vehiclesWaitUpdates.size());

            for (int var2 = 0; var2 < this.vehiclesWaitUpdates.size(); var2++) {
               var1.bb.putShort(this.vehiclesWaitUpdates.get(var2));
            }

            PacketType.Vehicles.send(GameClient.connection);
         }

         this.vehiclesWaitUpdates.clear();
      }

      ArrayList var9 = this.getVehicles();

      for (int var10 = 0; var10 < var9.size(); var10++) {
         BaseVehicle var3 = (BaseVehicle)var9.get(var10);
         if (GameClient.bClient) {
            if (var3.isNetPlayerAuthorization(Authorization.Local) || var3.isNetPlayerAuthorization(Authorization.LocalCollide)) {
               var3.interpolation.clear();
               continue;
            }
         } else if (var3.isKeyboardControlled() || var3.getJoypad() != -1) {
            var3.interpolation.clear();
            continue;
         }

         float[] var4 = this.tempFloats;
         if (var3.interpolation.interpolationDataGet(var4, this.engineSound)) {
            if (!var3.isNetPlayerAuthorization(Authorization.Local) && !var3.isNetPlayerAuthorization(Authorization.LocalCollide)) {
               Bullet.setOwnVehiclePhysics(var3.VehicleID, var4);
               float var5 = var4[0];
               float var6 = var4[1];
               float var7 = var4[2];
               IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, 0.0);
               this.clientUpdateVehiclePos(var3, var5, var6, var7, var8);
               var3.limitPhysicValid.BlockCheck();
               if (GameClient.bClient) {
                  this.vehiclePosUpdate(var3, var4);
               }

               var3.engineSpeed = this.engineSound[0];
               var3.throttle = this.engineSound[1];
            }
         } else {
            var3.getController().control_NoControl();
            var3.throttle = 0.0F;
            var3.jniSpeed = 0.0F;
         }
      }
   }

   private void clientUpdateVehiclePos(BaseVehicle var1, float var2, float var3, float var4, IsoGridSquare var5) {
      var1.setX(var2);
      var1.setY(var3);
      var1.setZ(0.0F);
      var1.square = var5;
      var1.setCurrent(var5);
      if (var5 != null) {
         if (var1.chunk != null && var1.chunk != var5.chunk) {
            var1.chunk.vehicles.remove(var1);
         }

         var1.chunk = var1.square.chunk;
         if (!var1.chunk.vehicles.contains(var1)) {
            var1.chunk.vehicles.add(var1);
            IsoChunk.addFromCheckedVehicles(var1);
         }

         if (!var1.addedToWorld) {
            var1.addToWorld();
         }
      } else {
         var1.removeFromWorld();
         var1.removeFromSquare();
      }

      var1.polyDirty = true;
   }

   private void clientReceiveUpdateFull(ByteBuffer var1, short var2, float var3, float var4, float var5) throws IOException {
      Authorization var6 = Authorization.valueOf(var1.get());
      short var7 = var1.getShort();
      short var8 = var1.getShort();
      IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, 0.0);
      if (this.IDToVehicle.containsKey(var2)) {
         BaseVehicle var10 = this.IDToVehicle.get(var2);
         DebugLog.Vehicle.noise("ERROR: got full update for KNOWN vehicle id=%d", var2);
         var1.get();
         var1.get();
         this.tempVehicle.parts.clear();
         this.tempVehicle.load(var1, 195);
         if (var10.physics != null && (var10.getDriver() == null || !var10.getDriver().isLocal())) {
            this.tempTransform.setRotation(this.tempVehicle.savedRot);
            this.tempTransform.origin.set(var3 - WorldSimulation.instance.offsetX, var5, var4 - WorldSimulation.instance.offsetY);
            var10.setWorldTransform(this.tempTransform);
         }

         var10.netPlayerFromServerUpdate(var6, var7);
         this.clientUpdateVehiclePos(var10, var3, var4, var5, var9);
      } else {
         boolean var15 = var1.get() != 0;
         byte var11 = var1.get();
         if (!var15 || var11 != IsoObject.getFactoryVehicle().getClassID()) {
            DebugLog.Vehicle.error("clientReceiveUpdateFull: packet broken");
         }

         BaseVehicle var12 = new BaseVehicle(IsoWorld.instance.CurrentCell);
         var12.VehicleID = var2;
         var12.square = var9;
         var12.setCurrent(var9);
         var12.load(var1, 195);
         if (var9 != null) {
            var12.chunk = var12.square.chunk;
            var12.chunk.vehicles.add(var12);
            var12.addToWorld();
         }

         IsoChunk.addFromCheckedVehicles(var12);
         var12.netPlayerFromServerUpdate(var6, var7);
         this.registerVehicle(var12);

         for (int var13 = 0; var13 < IsoPlayer.numPlayers; var13++) {
            IsoPlayer var14 = IsoPlayer.players[var13];
            if (var14 != null && !var14.isDead() && var14.getVehicle() == null) {
               IsoWorld.instance.CurrentCell.putInVehicle(var14);
            }
         }

         DebugLog.Vehicle.trace("added vehicle id=%d %s", var12.VehicleID, var9 == null ? " (delayed)" : "");
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void clientReceiveUpdate(ByteBuffer var1) throws IOException {
      short var2 = var1.getShort();
      DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get((byte)5), var2);
      short var3 = var1.getShort();
      float var4 = var1.getFloat();
      float var5 = var1.getFloat();
      float var6 = var1.getFloat();
      short var7 = var1.getShort();
      VehicleCache.vehicleUpdate(var2, var4, var5, 0.0F);
      IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, 0.0);
      BaseVehicle var9 = this.IDToVehicle.get(var2);
      if (var9 == null && var8 == null) {
         if (var1.limit() > var1.position() + var7) {
            var1.position(var1.position() + var7);
         }
      } else if (var9 != null && var8 == null) {
         boolean var39 = true;

         for (int var52 = 0; var52 < IsoPlayer.numPlayers; var52++) {
            IsoPlayer var60 = IsoPlayer.players[var52];
            if (var60 != null && var60.getVehicle() == var9) {
               var39 = false;
               var60.setPosition(var4, var5, 0.0F);
               this.sendRequestGetPosition(var2, PacketType.VehiclesUnreliable);
            }
         }

         if (var39) {
            var9.removeFromWorld();
            var9.removeFromSquare();
         }

         if (var1.limit() > var1.position() + var7) {
            var1.position(var1.position() + var7);
         }
      } else if ((var3 & 1) != 0) {
         DebugLog.Vehicle.trace("Vehicle vid=%d full update received", var2);
         this.clientReceiveUpdateFull(var1, var2, var4, var5, var6);
         if (var9 == null) {
            var9 = this.IDToVehicle.get(var2);
         }

         if (!var9.isKeyboardControlled() && var9.getJoypad() == -1) {
            var1.getLong();
            int var30 = 0;
            float[] var51 = this.tempFloats;
            var51[var30++] = var4;
            var51[var30++] = var5;
            var51[var30++] = var6;

            while (var30 < 10) {
               var51[var30++] = var1.getFloat();
            }

            float var59 = var1.getFloat();
            float var65 = var1.getFloat();
            short var66 = var1.getShort();
            var51[var30++] = var66;

            for (int var67 = 0; var67 < var66; var67++) {
               var51[var30++] = var1.getFloat();
               var51[var30++] = var1.getFloat();
               var51[var30++] = var1.getFloat();
               var51[var30++] = var1.getFloat();
            }

            Bullet.setOwnVehiclePhysics(var2, var51);
         } else if (var1.limit() > var1.position() + 102) {
            var1.position(var1.position() + 102);
         }

         int var38 = this.vehiclesWaitUpdates.indexOf(var2);
         if (var38 >= 0) {
            this.vehiclesWaitUpdates.removeAt(var38);
         }
      } else if (var9 == null && var8 != null) {
         this.sendRequestGetFull(var2, PacketType.Vehicles);
         if (var1.limit() > var1.position() + var7) {
            var1.position(var1.position() + var7);
         }
      } else {
         if ((var3 & 2) != 0) {
            if (!var9.isKeyboardControlled() && var9.getJoypad() == -1) {
               var9.interpolation.interpolationDataAdd(var1, var1.getLong(), var4, var5, var6, GameTime.getServerTimeMills());
            } else if (var1.limit() > var1.position() + 102) {
               var1.position(var1.position() + 102);
            }
         }

         if ((var3 & 4) != 0) {
            DebugLog.Vehicle.trace("received update Engine id=%d", var2);
            byte var10 = var1.get();
            if (var10 >= 0 && var10 < engineStateTypes.Values.length) {
               switch (1.$SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.Values[var10].ordinal()]) {
                  case 1:
                     var9.engineDoIdle();
                  case 2:
                  default:
                     break;
                  case 3:
                     var9.engineDoRetryingStarting();
                     break;
                  case 4:
                     var9.engineDoStartingSuccess();
                     break;
                  case 5:
                     var9.engineDoStartingFailed();
                     break;
                  case 6:
                     var9.engineDoStartingFailedNoPower();
                     break;
                  case 7:
                     var9.engineDoRunning();
                     break;
                  case 8:
                     var9.engineDoStalling();
                     break;
                  case 9:
                     var9.engineDoShuttingDown();
               }

               var9.engineLoudness = var1.getInt();
               var9.enginePower = var1.getInt();
               var9.engineQuality = var1.getInt();
            } else {
               DebugLog.Vehicle.error("VehicleManager.clientReceiveUpdate get invalid data");
            }
         }

         if ((var3 & 4096) != 0) {
            DebugLog.Vehicle.trace("received car properties update id=%d", var2);
            var9.setHotwired(var1.get() == 1);
            var9.setHotwiredBroken(var1.get() == 1);
            var9.setRegulatorSpeed(var1.getFloat());
            var9.setPreviouslyEntered(var1.get() == 1);
            boolean var19 = var1.get() == 1;
            boolean var11 = var1.get() == 1;
            InventoryItem var12 = null;
            if (var1.get() == 1) {
               try {
                  var12 = InventoryItem.loadItem(var1, 195);
               } catch (Exception var18) {
                  var18.printStackTrace();
               }
            }

            var9.syncKeyInIgnition(var19, var11, var12);
            var9.setRust(var1.getFloat());
            var9.setBloodIntensity("Front", var1.getFloat());
            var9.setBloodIntensity("Rear", var1.getFloat());
            var9.setBloodIntensity("Left", var1.getFloat());
            var9.setBloodIntensity("Right", var1.getFloat());
            var9.setColorHSV(var1.getFloat(), var1.getFloat(), var1.getFloat());
            var9.setSkinIndex(var1.getInt());
            var9.updateSkin();
         }

         if ((var3 & 8) != 0) {
            DebugLog.Vehicle.trace("received update Lights id=%d", var2);
            var9.setHeadlightsOn(var1.get() == 1);
            var9.setStoplightsOn(var1.get() == 1);

            for (int var20 = 0; var20 < var9.getLightCount(); var20++) {
               boolean var40 = var1.get() == 1;
               var9.getLightByIndex(var20).getLight().setActive(var40);
            }
         }

         if ((var3 & 1024) != 0) {
            DebugLog.Vehicle.trace("received update Sounds id=%d", var2);
            boolean var21 = var1.get() == 1;
            boolean var41 = var1.get() == 1;
            byte var53 = var1.get();
            byte var13 = var1.get();
            if (var21 != var9.soundHornOn) {
               if (var21) {
                  var9.onHornStart();
               } else {
                  var9.onHornStop();
               }
            }

            if (var41 != var9.soundBackMoveOn) {
               if (var41) {
                  var9.onBackMoveSignalStart();
               } else {
                  var9.onBackMoveSignalStop();
               }
            }

            if (var9.lightbarLightsMode.get() != var53) {
               var9.setLightbarLightsMode(var53);
            }

            if (var9.lightbarSirenMode.get() != var13) {
               var9.setLightbarSirenMode(var13);
            }
         }

         if ((var3 & 2048) != 0) {
            for (byte var22 = var1.get(); var22 != -1; var22 = var1.get()) {
               VehiclePart var42 = var9.getPartByIndex(var22);
               DebugLog.Vehicle.trace("received update PartCondition id=%d part=%s", var2, var42.getId());
               var42.updateFlags = (short)(var42.updateFlags | 2048);
               var42.setCondition(var1.getInt());
            }

            var9.doDamageOverlay();
         }

         if ((var3 & 16) != 0) {
            for (byte var23 = var1.get(); var23 != -1; var23 = var1.get()) {
               VehiclePart var43 = var9.getPartByIndex(var23);
               DebugLog.Vehicle.trace("received update PartModData id=%d part=%s", var2, var43.getId());
               var43.getModData().load(var1, 195);
               if (var43.isContainer()) {
                  var43.setContainerContentAmount(var43.getContainerContentAmount());
               }
            }
         }

         if ((var3 & 32) != 0) {
            for (byte var24 = var1.get(); var24 != -1; var24 = var1.get()) {
               float var44 = var1.getFloat();
               VehiclePart var54 = var9.getPartByIndex(var24);
               DebugLog.Vehicle.trace("received update PartUsedDelta id=%d part=%s", var2, var54.getId());
               InventoryItem var61 = var54.getInventoryItem();
               if (var61 instanceof DrainableComboItem) {
                  ((DrainableComboItem)var61).setUsedDelta(var44);
               }
            }
         }

         if ((var3 & 128) != 0) {
            for (byte var25 = var1.get(); var25 != -1; var25 = var1.get()) {
               VehiclePart var45 = var9.getPartByIndex(var25);
               DebugLog.Vehicle.trace("received update PartItem id=%d part=%s", var2, var45.getId());
               var45.updateFlags = (short)(var45.updateFlags | 128);
               boolean var55 = var1.get() != 0;
               if (var55) {
                  InventoryItem var62;
                  try {
                     var62 = InventoryItem.loadItem(var1, 195);
                  } catch (Exception var17) {
                     var17.printStackTrace();
                     return;
                  }

                  if (var62 != null) {
                     var45.setInventoryItem(var62);
                  }
               } else {
                  var45.setInventoryItem(null);
               }

               int var63 = var45.getWheelIndex();
               if (var63 != -1) {
                  var9.setTireRemoved(var63, !var55);
               }

               if (var45.isContainer()) {
                  LuaEventManager.triggerEvent("OnContainerUpdate");
               }
            }
         }

         if ((var3 & 512) != 0) {
            for (byte var26 = var1.get(); var26 != -1; var26 = var1.get()) {
               VehiclePart var46 = var9.getPartByIndex(var26);
               DebugLog.Vehicle.trace("received update PartDoor id=%d part=%s", var2, var46.getId());
               var46.getDoor().load(var1, 195);
            }

            LuaEventManager.triggerEvent("OnContainerUpdate");
            var9.doDamageOverlay();
         }

         if ((var3 & 256) != 0) {
            for (byte var27 = var1.get(); var27 != -1; var27 = var1.get()) {
               VehiclePart var47 = var9.getPartByIndex(var27);
               DebugLog.Vehicle.trace("received update PartWindow id=%d part=%s", var2, var47.getId());
               var47.getWindow().load(var1, 195);
            }

            var9.doDamageOverlay();
         }

         if ((var3 & 64) != 0) {
            this.oldModels.clear();
            this.oldModels.addAll(var9.models);
            this.curModels.clear();
            byte var28 = var1.get();

            for (int var48 = 0; var48 < var28; var48++) {
               byte var56 = var1.get();
               byte var64 = var1.get();
               VehiclePart var14 = var9.getPartByIndex(var56);
               Model var15 = (Model)var14.getScriptPart().models.get(var64);
               ModelInfo var16 = var9.setModelVisible(var14, var15, true);
               this.curModels.add(var16);
            }

            for (int var49 = 0; var49 < this.oldModels.size(); var49++) {
               ModelInfo var57 = this.oldModels.get(var49);
               if (!this.curModels.contains(var57)) {
                  var9.setModelVisible(var57.part, var57.scriptModel, false);
               }
            }

            var9.doDamageOverlay();
         }

         boolean var29 = false;

         for (int var50 = 0; var50 < var9.getPartCount(); var50++) {
            VehiclePart var58 = var9.getPartByIndex(var50);
            if (var58.updateFlags != 0) {
               if ((var58.updateFlags & 2048) != 0 && (var58.updateFlags & 128) == 0) {
                  var58.doInventoryItemStats(var58.getInventoryItem(), var58.getMechanicSkillInstaller());
                  var29 = true;
               }

               var58.updateFlags = 0;
            }
         }

         if (var29) {
            var9.updatePartStats();
            var9.updateBulletStats();
         }
      }
   }

   public void clientPacket(ByteBuffer var1) {
      byte var2 = var1.get();
      switch (var2) {
         case 1:
            short var24 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var2), var24);
            byte var34 = var1.get();
            String var42 = GameWindow.ReadString(var1);
            BaseVehicle var49 = this.IDToVehicle.get(var24);
            if (var49 != null) {
               IsoGameCharacter var54 = var49.getCharacter(var34);
               if (var54 != null) {
                  var49.setCharacterPosition(var54, var34, var42);
               }
            }
            break;
         case 2:
            short var23 = var1.getShort();
            short var33 = var1.getShort();
            byte var41 = var1.get();
            DebugLog.Vehicle.trace("Vehicle enter vid=%d pid=%d seat=%d", var23, var33, Integer.valueOf(var41));
            BaseVehicle var48 = this.IDToVehicle.get(var23);
            if (var48 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var23});
            } else {
               IsoPlayer var53 = (IsoPlayer)GameClient.IDToPlayerMap.get(var33);
               if (var53 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var33});
               } else {
                  IsoPlayer var56 = (IsoPlayer)Type.tryCastTo(var48.getCharacter(var41), IsoPlayer.class);
                  if (var56 != null && var56 != var53) {
                     DebugLog.Vehicle.warn(var53.getUsername() + " got in same seat as " + var56.getUsername());
                  } else {
                     var48.enterRSync(var41, var53, var48);
                  }
               }
            }
            break;
         case 3:
            short var22 = var1.getShort();
            short var32 = var1.getShort();
            byte var40 = var1.get();
            DebugLog.Vehicle.trace("Vehicle exit vid=%d pid=%d seat=%d", var22, var32, Integer.valueOf(var40));
            BaseVehicle var47 = this.IDToVehicle.get(var22);
            if (var47 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var22});
            } else {
               IsoPlayer var52 = (IsoPlayer)GameClient.IDToPlayerMap.get(var32);
               if (var52 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var32});
               } else {
                  var47.exitRSync(var52);
               }
            }
            break;
         case 4:
            short var21 = var1.getShort();
            short var31 = var1.getShort();
            byte var39 = var1.get();
            byte var46 = var1.get();
            DebugLog.Vehicle.trace("Vehicle switch seat vid=%d pid=%d seats=%d=>%d", var21, var31, Integer.valueOf(var39), Integer.valueOf(var46));
            BaseVehicle var51 = this.IDToVehicle.get(var21);
            if (var51 == null) {
               DebugLog.Vehicle.warn("Vehicle vid=%d not found", new Object[]{var21});
            } else {
               IsoPlayer var55 = (IsoPlayer)GameClient.IDToPlayerMap.get(var31);
               if (var55 == null) {
                  DebugLog.Vehicle.warn("Player pid=%d not found", new Object[]{var31});
               } else {
                  IsoPlayer var9 = (IsoPlayer)Type.tryCastTo(var51.getCharacter(var46), IsoPlayer.class);
                  if (var9 != null && var9 != var55) {
                     DebugLog.Vehicle.warn(var55.getUsername() + " switched to same seat as " + var9.getUsername());
                  } else {
                     var51.switchSeat(var55, var46);
                  }
               }
            }
            break;
         case 5:
            if (this.tempVehicle == null || this.tempVehicle.getCell() != IsoWorld.instance.CurrentCell) {
               this.tempVehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
            }

            short var20 = var1.getShort();

            for (int var30 = 0; var30 < var20; var30++) {
               try {
                  this.clientReceiveUpdate(var1);
               } catch (Exception var13) {
                  var13.printStackTrace();
                  return;
               }
            }
            break;
         case 6:
         case 7:
         case 10:
         case 11:
         case 12:
         case 14:
         case 15:
         default:
            DebugLog.Vehicle.warn("Unknown vehicle packet %d", new Object[]{var2});
            break;
         case 8:
            short var19 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var2), var19);
            if (this.IDToVehicle.containsKey(var19)) {
               BaseVehicle var29 = this.IDToVehicle.get(var19);
               var29.serverRemovedFromWorld = true;

               try {
                  var29.removeFromWorld();
                  var29.removeFromSquare();
               } finally {
                  if (this.IDToVehicle.containsKey(var19)) {
                     this.unregisterVehicle(var29);
                  }
               }
            }

            VehicleCache.remove(var19);
            break;
         case 9:
            Physics var18 = new Physics();
            var18.parse(var1, GameClient.connection);
            var18.process();
            break;
         case 13:
            short var17 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var2), var17);
            Vector3f var28 = new Vector3f();
            Vector3f var38 = new Vector3f();
            var28.x = var1.getFloat();
            var28.y = var1.getFloat();
            var28.z = var1.getFloat();
            var38.x = var1.getFloat();
            var38.y = var1.getFloat();
            var38.z = var1.getFloat();
            BaseVehicle var45 = this.IDToVehicle.get(var17);
            if (var45 != null) {
               Bullet.applyCentralForceToVehicle(var45.VehicleID, var28.x, var28.y, var28.z);
               Vector3f var50 = var38.cross(var28);
               Bullet.applyTorqueToVehicle(var45.VehicleID, var50.x, var50.y, var50.z);
            }
            break;
         case 16:
            short var16 = var1.getShort();
            DebugLog.Vehicle.trace("%s vid=%d", vehiclePacketTypes.get(var2), var16);
            byte var27 = var1.get();
            BaseVehicle var37 = this.IDToVehicle.get(var16);
            if (var37 != null) {
               SoundManager.instance.PlayWorldSound("VehicleCrash", var37.square, 1.0F, 20.0F, 1.0F, true);
            }
            break;
         case 17:
            short var15 = var1.getShort();
            short var26 = var1.getShort();
            String var36 = GameWindow.ReadString(var1);
            String var44 = GameWindow.ReadString(var1);
            DebugLog.Vehicle.trace("Vehicle attach A=%d/%s B=%d/%s", var15, var36, var26, var44);
            this.towedVehicleMap.put(var15, var26);
            BaseVehicle var7 = this.IDToVehicle.get(var15);
            BaseVehicle var8 = this.IDToVehicle.get(var26);
            if (var7 != null && var8 != null) {
               var7.addPointConstraint(null, var8, var36, var44);
            }
            break;
         case 18:
            short var14 = var1.getShort();
            short var25 = var1.getShort();
            DebugLog.Vehicle.trace("Vehicle detach A=%d B=%d", var14, var25);
            if (this.towedVehicleMap.containsKey(var14)) {
               this.towedVehicleMap.remove(var14);
            }

            if (this.towedVehicleMap.containsKey(var25)) {
               this.towedVehicleMap.remove(var25);
            }

            BaseVehicle var35 = this.IDToVehicle.get(var14);
            BaseVehicle var43 = this.IDToVehicle.get(var25);
            if (var35 != null) {
               var35.breakConstraint(true, true);
            }

            if (var43 != null) {
               var43.breakConstraint(true, true);
            }
            break;
         case 19:
            short var3 = var1.getShort();

            for (int var4 = 0; var4 < var3; var4++) {
               short var5 = var1.getShort();
               short var6 = var1.getShort();
               this.towedVehicleMap.put(var5, var6);
            }
      }
   }

   public void sendCollide(BaseVehicle var1, IsoGameCharacter var2, boolean var3) {
      short var4 = var2 == null ? -1 : ((IsoPlayer)var2).OnlineID;
      ByteBufferWriter var5 = GameClient.connection.startPacket();
      PacketType.Vehicles.doPacket(var5);
      var5.bb.put((byte)15);
      var5.bb.putShort(var1.VehicleID);
      var5.bb.putShort(var4);
      var5.bb.put((byte)(var3 ? 1 : 0));
      PacketType.Vehicles.send(GameClient.connection);
      DebugLog.Vehicle.trace("vid=%d pid=%d collide=%b", var1.VehicleID, var4, var3);
   }

   public static void sendSound(BaseVehicle var0, byte var1) {
      ByteBufferWriter var2 = GameClient.connection.startPacket();
      PacketType.Vehicles.doPacket(var2);
      var2.bb.put((byte)16);
      var2.bb.putShort(var0.VehicleID);
      var2.bb.put(var1);
      PacketType.Vehicles.send(GameClient.connection);
   }

   public static void sendSoundFromServer(BaseVehicle var0, byte var1) {
      for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
         UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
         ByteBufferWriter var4 = var3.startPacket();
         PacketType.Vehicles.doPacket(var4);
         var4.bb.put((byte)16);
         var4.bb.putShort(var0.VehicleID);
         var4.bb.put(var1);
         PacketType.Vehicles.send(var3);
      }
   }

   public void sendPassengerPosition(BaseVehicle var1, int var2, String var3) {
      ByteBufferWriter var4 = GameClient.connection.startPacket();
      PacketType.Vehicles.doPacket(var4);
      var4.bb.put((byte)1);
      var4.bb.putShort(var1.VehicleID);
      var4.bb.put((byte)var2);
      var4.putUTF(var3);
      PacketType.Vehicles.send(GameClient.connection);
   }

   public void sendPassengerPosition(BaseVehicle var1, int var2, String var3, UdpConnection var4) {
      for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
         UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
         if (var6 != var4) {
            ByteBufferWriter var7 = var6.startPacket();
            PacketType.Vehicles.doPacket(var7);
            var7.bb.put((byte)1);
            var7.bb.putShort(var1.VehicleID);
            var7.bb.put((byte)var2);
            var7.putUTF(var3);
            PacketType.Vehicles.send(var6);
         }
      }
   }

   public void sendRequestGetFull(short var1, PacketType var2) {
      if (!this.vehiclesWaitUpdates.contains(var1)) {
         ByteBufferWriter var3 = GameClient.connection.startPacket();
         PacketType.Vehicles.doPacket(var3);
         var3.bb.put((byte)11);
         var3.bb.putShort((short)1);
         var3.bb.putShort(var1);
         PacketType.Vehicles.send(GameClient.connection);
         this.vehiclesWaitUpdates.add(var1);
      }
   }

   public void sendRequestGetFull(List<VehicleCache> var1) {
      if (var1 != null && !var1.isEmpty()) {
         ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.Vehicles.doPacket(var2);
         var2.bb.put((byte)11);
         var2.bb.putShort((short)var1.size());

         for (int var3 = 0; var3 < var1.size(); var3++) {
            var2.bb.putShort(((VehicleCache)var1.get(var3)).id);
            this.vehiclesWaitUpdates.add(((VehicleCache)var1.get(var3)).id);
         }

         PacketType.Vehicles.send(GameClient.connection);
      }
   }

   public void sendRequestGetPosition(short var1, PacketType var2) {
      if (this.sendRequestGetPositionFrequency.Check()) {
         ByteBufferWriter var3 = GameClient.connection.startPacket();
         var2.doPacket(var3);
         var3.bb.put((byte)12);
         var3.bb.putShort(var1);
         var2.send(GameClient.connection);
         this.vehiclesWaitUpdates.add(var1);
      }
   }

   public void sendAddImpulse(BaseVehicle var1, Vector3f var2, Vector3f var3) {
      UdpConnection var4 = null;

      for (int var5 = 0; var5 < GameServer.udpEngine.connections.size() && var4 == null; var5++) {
         UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);

         for (int var7 = 0; var7 < var6.players.length; var7++) {
            IsoPlayer var8 = var6.players[var7];
            if (var8 != null && var8.getVehicle() != null && var8.getVehicle().VehicleID == var1.VehicleID) {
               var4 = var6;
               break;
            }
         }
      }

      if (var4 != null) {
         ByteBufferWriter var9 = var4.startPacket();
         PacketType.Vehicles.doPacket(var9);
         var9.bb.put((byte)13);
         var9.bb.putShort(var1.VehicleID);
         var9.bb.putFloat(var2.x);
         var9.bb.putFloat(var2.y);
         var9.bb.putFloat(var2.z);
         var9.bb.putFloat(var3.x);
         var9.bb.putFloat(var3.y);
         var9.bb.putFloat(var3.z);
         PacketType.Vehicles.send(var4);
      }
   }

   public void sendSwitchSeat(UdpConnection var1, BaseVehicle var2, IsoGameCharacter var3, int var4, int var5) {
      ByteBufferWriter var6 = var1.startPacket();
      PacketType.Vehicles.doPacket(var6);
      var6.bb.put((byte)4);
      var6.bb.putShort(var2.getId());
      var6.bb.putShort(var3.getOnlineID());
      var6.bb.put((byte)var4);
      var6.bb.put((byte)var5);
      PacketType.Vehicles.send(var1);
   }

   public void sendSwitchSeat(BaseVehicle var1, IsoGameCharacter var2, int var3, int var4) {
      for (UdpConnection var6 : GameServer.udpEngine.connections) {
         this.sendSwitchSeat(var6, var1, var2, var3, var4);
      }
   }

   public void sendEnter(UdpConnection var1, BaseVehicle var2, IsoGameCharacter var3, int var4) {
      ByteBufferWriter var5 = var1.startPacket();
      PacketType.Vehicles.doPacket(var5);
      var5.bb.put((byte)2);
      var5.bb.putShort(var2.getId());
      var5.bb.putShort(var3.getOnlineID());
      var5.bb.put((byte)var4);
      PacketType.Vehicles.send(var1);
   }

   public void sendEnter(BaseVehicle var1, IsoGameCharacter var2, int var3) {
      for (UdpConnection var5 : GameServer.udpEngine.connections) {
         this.sendEnter(var5, var1, var2, var3);
      }
   }

   public void sendExit(UdpConnection var1, BaseVehicle var2, IsoGameCharacter var3, int var4) {
      ByteBufferWriter var5 = var1.startPacket();
      PacketType.Vehicles.doPacket(var5);
      var5.bb.put((byte)3);
      var5.bb.putShort(var2.getId());
      var5.bb.putShort(var3.getOnlineID());
      var5.bb.put((byte)var4);
      PacketType.Vehicles.send(var1);
   }

   public void sendExit(BaseVehicle var1, IsoGameCharacter var2, int var3) {
      for (UdpConnection var5 : GameServer.udpEngine.connections) {
         this.sendExit(var5, var1, var2, (byte)var3);
      }
   }

   public void sendPhysic(BaseVehicle var1) {
      ByteBufferWriter var2 = GameClient.connection.startPacket();
      PacketType var3 = var1.isReliable ? PacketType.Vehicles : PacketType.VehiclesUnreliable;
      var3.doPacket(var2);
      var2.bb.put((byte)9);
      Physics var4 = new Physics();
      if (var4.set(var1)) {
         var4.write(var2);
         var3.send(GameClient.connection);
      } else {
         GameClient.connection.cancelPacket();
      }
   }

   public void sendTowing(UdpConnection var1, BaseVehicle var2, BaseVehicle var3, String var4, String var5) {
      DebugLog.Vehicle.trace("vidA=%d vidB=%d", var2.VehicleID, var3.VehicleID);
      ByteBufferWriter var6 = var1.startPacket();
      PacketType.Vehicles.doPacket(var6);
      var6.bb.put((byte)17);
      var6.bb.putShort(var2.VehicleID);
      var6.bb.putShort(var3.VehicleID);
      GameWindow.WriteString(var6.bb, var4);
      GameWindow.WriteString(var6.bb, var5);
      PacketType.Vehicles.send(var1);
   }

   public void sendTowing(BaseVehicle var1, BaseVehicle var2, String var3, String var4) {
      if (!this.towedVehicleMap.containsKey(var1.VehicleID)) {
         this.towedVehicleMap.put(var1.VehicleID, var2.VehicleID);

         for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
            UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
            this.sendTowing(var6, var1, var2, var3, var4);
         }
      }
   }

   public void sendDetachTowing(UdpConnection var1, BaseVehicle var2, BaseVehicle var3) {
      ByteBufferWriter var4 = var1.startPacket();
      PacketType.Vehicles.doPacket(var4);
      var4.bb.put((byte)18);
      var4.bb.putShort(var2 == null ? -1 : var2.VehicleID);
      var4.bb.putShort(var3 == null ? -1 : var3.VehicleID);
      PacketType.Vehicles.send(var1);
   }

   public void sendDetachTowing(BaseVehicle var1, BaseVehicle var2) {
      if (var1 != null && this.towedVehicleMap.containsKey(var1.VehicleID)) {
         this.towedVehicleMap.remove(var1.VehicleID);
      }

      if (var2 != null && this.towedVehicleMap.containsKey(var2.VehicleID)) {
         this.towedVehicleMap.remove(var2.VehicleID);
      }

      for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
         UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
         this.sendDetachTowing(var4, var1, var2);
      }
   }

   public short getTowedVehicleID(short var1) {
      return this.towedVehicleMap.containsKey(var1) ? this.towedVehicleMap.get(var1) : -1;
   }

   private void writePositionOrientation(ByteBuffer var1, BaseVehicle var2) {
      var1.putLong(WorldSimulation.instance.time);
      Quaternionf var3 = var2.savedRot;
      Transform var4 = var2.getWorldTransform(this.tempTransform);
      var4.getRotation(var3);
      var1.putFloat(var3.x);
      var1.putFloat(var3.y);
      var1.putFloat(var3.z);
      var1.putFloat(var3.w);
      var1.putFloat(var2.jniLinearVelocity.x);
      var1.putFloat(var2.jniLinearVelocity.y);
      var1.putFloat(var2.jniLinearVelocity.z);
      var1.putFloat((float)var2.engineSpeed);
      var1.putFloat(var2.throttle);
      var1.putShort((short)var2.wheelInfo.length);

      for (int var5 = 0; var5 < var2.wheelInfo.length; var5++) {
         var1.putFloat(var2.wheelInfo[var5].steering);
         var1.putFloat(var2.wheelInfo[var5].rotation);
         var1.putFloat(var2.wheelInfo[var5].skidInfo);
         var1.putFloat(var2.wheelInfo[var5].suspensionLength);
      }
   }

   static {
      vehiclePacketTypes.put((byte)1, "PassengerPosition");
      vehiclePacketTypes.put((byte)2, "Enter");
      vehiclePacketTypes.put((byte)3, "Exit");
      vehiclePacketTypes.put((byte)4, "SwitchSeat");
      vehiclePacketTypes.put((byte)5, "Update");
      vehiclePacketTypes.put((byte)8, "Remove");
      vehiclePacketTypes.put((byte)9, "Physic");
      vehiclePacketTypes.put((byte)10, "Config");
      vehiclePacketTypes.put((byte)11, "RequestGetFull");
      vehiclePacketTypes.put((byte)12, "RequestGetPosition");
      vehiclePacketTypes.put((byte)13, "AddImpulse");
      vehiclePacketTypes.put((byte)15, "Collide");
      vehiclePacketTypes.put((byte)16, "Sound");
      vehiclePacketTypes.put((byte)17, "TowingCar");
      vehiclePacketTypes.put((byte)18, "DetachTowingCar");
      vehiclePacketTypes.put((byte)19, "InitialWorldState");
   }
}
