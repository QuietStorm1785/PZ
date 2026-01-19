package zombie.scripting.objects;

import gnu.trove.list.array.TFloatArrayList;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.regex.Pattern;
import org.joml.Vector2f;
import org.joml.Vector2i;
import org.joml.Vector3f;
import org.joml.Vector4f;
import se.krka.kahlua.vm.KahluaTable;
import zombie.SystemDisabler;
import zombie.Lua.LuaManager;
import zombie.core.ImmutableColor;
import zombie.core.math.PZMath;
import zombie.core.physics.Bullet;
import zombie.debug.DebugLog;
import zombie.network.GameServer;
import zombie.scripting.ScriptManager;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.BlockElement;
import zombie.scripting.ScriptParser.Value;
import zombie.scripting.objects.VehicleScript.Anim;
import zombie.scripting.objects.VehicleScript.Area;
import zombie.scripting.objects.VehicleScript.Container;
import zombie.scripting.objects.VehicleScript.Door;
import zombie.scripting.objects.VehicleScript.LightBar;
import zombie.scripting.objects.VehicleScript.Model;
import zombie.scripting.objects.VehicleScript.Part;
import zombie.scripting.objects.VehicleScript.Passenger;
import zombie.scripting.objects.VehicleScript.PhysicsShape;
import zombie.scripting.objects.VehicleScript.Position;
import zombie.scripting.objects.VehicleScript.Skin;
import zombie.scripting.objects.VehicleScript.Sounds;
import zombie.scripting.objects.VehicleScript.Wheel;
import zombie.scripting.objects.VehicleScript.Window;
import zombie.scripting.objects.VehicleScript.Passenger.SwitchSeat;
import zombie.util.StringUtils;
import zombie.vehicles.BaseVehicle;

public final class VehicleScript extends BaseScriptObject {
   private String fileName;
   private String name;
   private final ArrayList<Model> models = new ArrayList<>();
   public final ArrayList<ModelAttachment> m_attachments = new ArrayList<>();
   private float mass = 800.0F;
   private final Vector3f centerOfMassOffset = new Vector3f();
   private float engineForce = 3000.0F;
   private float engineIdleSpeed = 750.0F;
   private float steeringIncrement = 0.04F;
   private float steeringClamp = 0.4F;
   private float steeringClampMax = 0.9F;
   private float wheelFriction = 800.0F;
   private float stoppingMovementForce = 1.0F;
   private float suspensionStiffness = 20.0F;
   private float suspensionDamping = 2.3F;
   private float suspensionCompression = 4.4F;
   private float suspensionRestLength = 0.6F;
   private float maxSuspensionTravelCm = 500.0F;
   private float rollInfluence = 0.1F;
   private final Vector3f extents = new Vector3f(0.75F, 0.5F, 2.0F);
   private final Vector2f shadowExtents = new Vector2f(0.0F, 0.0F);
   private final Vector2f shadowOffset = new Vector2f(0.0F, 0.0F);
   private boolean bHadShadowOExtents = false;
   private boolean bHadShadowOffset = false;
   private final Vector2f extentsOffset = new Vector2f(0.5F, 0.5F);
   private final Vector3f physicsChassisShape = new Vector3f(0.75F, 0.5F, 1.0F);
   private final ArrayList<PhysicsShape> m_physicsShapes = new ArrayList<>();
   private final ArrayList<Wheel> wheels = new ArrayList<>();
   private final ArrayList<Passenger> passengers = new ArrayList<>();
   public float maxSpeed = 20.0F;
   public boolean isSmallVehicle = true;
   public float spawnOffsetY = 0.0F;
   private int frontEndHealth = 100;
   private int rearEndHealth = 100;
   private int storageCapacity = 100;
   private int engineLoudness = 100;
   private int engineQuality = 100;
   private int seats = 2;
   private int mechanicType;
   private int engineRepairLevel;
   private float playerDamageProtection;
   private float forcedHue = -1.0F;
   private float forcedSat = -1.0F;
   private float forcedVal = -1.0F;
   public ImmutableColor leftSirenCol;
   public ImmutableColor rightSirenCol;
   private String engineRPMType = "jeep";
   private float offroadEfficiency = 1.0F;
   private final TFloatArrayList crawlOffsets = new TFloatArrayList();
   public int gearRatioCount = 0;
   public final float[] gearRatio = new float[9];
   private final Skin textures = new Skin();
   private final ArrayList<Skin> skins = new ArrayList<>();
   private final ArrayList<Area> areas = new ArrayList<>();
   private final ArrayList<Part> parts = new ArrayList<>();
   private boolean hasSiren = false;
   private final LightBar lightbar = new LightBar();
   private final Sounds sound = new Sounds();
   public boolean textureMaskEnable = false;
   private static final int PHYSICS_SHAPE_BOX = 1;
   private static final int PHYSICS_SHAPE_SPHERE = 2;

   public VehicleScript() {
      this.gearRatioCount = 4;
      this.gearRatio[0] = 7.09F;
      this.gearRatio[1] = 6.44F;
      this.gearRatio[2] = 4.1F;
      this.gearRatio[3] = 2.29F;
      this.gearRatio[4] = 1.47F;
      this.gearRatio[5] = 1.0F;
   }

   public void Load(String var1, String var2) {
      ScriptManager var3 = ScriptManager.instance;
      this.fileName = var3.currentFileName;
      if (!var3.scriptsWithVehicles.contains(this.fileName)) {
         var3.scriptsWithVehicles.add(this.fileName);
      }

      this.name = var1;
      Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);

      for (BlockElement var6 : var4.elements) {
         if (var6.asValue() != null) {
            String[] var14 = var6.asValue().string.split("=");
            String var20 = var14[0].trim();
            String var24 = var14[1].trim();
            if ("extents".equals(var20)) {
               this.LoadVector3f(var24, this.extents);
            } else if ("shadowExtents".equals(var20)) {
               this.LoadVector2f(var24, this.shadowExtents);
               this.bHadShadowOExtents = true;
            } else if ("shadowOffset".equals(var20)) {
               this.LoadVector2f(var24, this.shadowOffset);
               this.bHadShadowOffset = true;
            } else if ("physicsChassisShape".equals(var20)) {
               this.LoadVector3f(var24, this.physicsChassisShape);
            } else if ("extentsOffset".equals(var20)) {
               this.LoadVector2f(var24, this.extentsOffset);
            } else if ("mass".equals(var20)) {
               this.mass = Float.parseFloat(var24);
            } else if ("offRoadEfficiency".equalsIgnoreCase(var20)) {
               this.offroadEfficiency = Float.parseFloat(var24);
            } else if ("centerOfMassOffset".equals(var20)) {
               this.LoadVector3f(var24, this.centerOfMassOffset);
            } else if ("engineForce".equals(var20)) {
               this.engineForce = Float.parseFloat(var24);
            } else if ("engineIdleSpeed".equals(var20)) {
               this.engineIdleSpeed = Float.parseFloat(var24);
            } else if ("gearRatioCount".equals(var20)) {
               this.gearRatioCount = Integer.parseInt(var24);
            } else if ("gearRatioR".equals(var20)) {
               this.gearRatio[0] = Float.parseFloat(var24);
            } else if ("gearRatio1".equals(var20)) {
               this.gearRatio[1] = Float.parseFloat(var24);
            } else if ("gearRatio2".equals(var20)) {
               this.gearRatio[2] = Float.parseFloat(var24);
            } else if ("gearRatio3".equals(var20)) {
               this.gearRatio[3] = Float.parseFloat(var24);
            } else if ("gearRatio4".equals(var20)) {
               this.gearRatio[4] = Float.parseFloat(var24);
            } else if ("gearRatio5".equals(var20)) {
               this.gearRatio[5] = Float.parseFloat(var24);
            } else if ("gearRatio6".equals(var20)) {
               this.gearRatio[6] = Float.parseFloat(var24);
            } else if ("gearRatio7".equals(var20)) {
               this.gearRatio[7] = Float.parseFloat(var24);
            } else if ("gearRatio8".equals(var20)) {
               this.gearRatio[8] = Float.parseFloat(var24);
            } else if ("textureMaskEnable".equals(var20)) {
               this.textureMaskEnable = Boolean.parseBoolean(var24);
            } else if ("textureRust".equals(var20)) {
               this.textures.textureRust = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureMask".equals(var20)) {
               this.textures.textureMask = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureLights".equals(var20)) {
               this.textures.textureLights = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage1Overlay".equals(var20)) {
               this.textures.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage1Shell".equals(var20)) {
               this.textures.textureDamage1Shell = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage2Overlay".equals(var20)) {
               this.textures.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage2Shell".equals(var20)) {
               this.textures.textureDamage2Shell = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureShadow".equals(var20)) {
               this.textures.textureShadow = StringUtils.discardNullOrWhitespace(var24);
            } else if ("rollInfluence".equals(var20)) {
               this.rollInfluence = Float.parseFloat(var24);
            } else if ("steeringIncrement".equals(var20)) {
               this.steeringIncrement = Float.parseFloat(var24);
            } else if ("steeringClamp".equals(var20)) {
               this.steeringClamp = Float.parseFloat(var24);
            } else if ("suspensionStiffness".equals(var20)) {
               this.suspensionStiffness = Float.parseFloat(var24);
            } else if ("suspensionDamping".equals(var20)) {
               this.suspensionDamping = Float.parseFloat(var24);
            } else if ("suspensionCompression".equals(var20)) {
               this.suspensionCompression = Float.parseFloat(var24);
            } else if ("suspensionRestLength".equals(var20)) {
               this.suspensionRestLength = Float.parseFloat(var24);
            } else if ("maxSuspensionTravelCm".equals(var20)) {
               this.maxSuspensionTravelCm = Float.parseFloat(var24);
            } else if ("wheelFriction".equals(var20)) {
               this.wheelFriction = Float.parseFloat(var24);
            } else if ("stoppingMovementForce".equals(var20)) {
               this.stoppingMovementForce = Float.parseFloat(var24);
            } else if ("maxSpeed".equals(var20)) {
               this.maxSpeed = Float.parseFloat(var24);
            } else if ("isSmallVehicle".equals(var20)) {
               this.isSmallVehicle = Boolean.parseBoolean(var24);
            } else if ("spawnOffsetY".equals(var20)) {
               this.spawnOffsetY = Float.parseFloat(var24) - 0.995F;
            } else if ("frontEndDurability".equals(var20)) {
               this.frontEndHealth = Integer.parseInt(var24);
            } else if ("rearEndDurability".equals(var20)) {
               this.rearEndHealth = Integer.parseInt(var24);
            } else if ("storageCapacity".equals(var20)) {
               this.storageCapacity = Integer.parseInt(var24);
            } else if ("engineLoudness".equals(var20)) {
               this.engineLoudness = Integer.parseInt(var24);
            } else if ("engineQuality".equals(var20)) {
               this.engineQuality = Integer.parseInt(var24);
            } else if ("seats".equals(var20)) {
               this.seats = Integer.parseInt(var24);
            } else if ("hasSiren".equals(var20)) {
               this.hasSiren = Boolean.parseBoolean(var24);
            } else if ("mechanicType".equals(var20)) {
               this.mechanicType = Integer.parseInt(var24);
            } else if ("forcedColor".equals(var20)) {
               String[] var28 = var24.split(" ");
               this.setForcedHue(Float.parseFloat(var28[0]));
               this.setForcedSat(Float.parseFloat(var28[1]));
               this.setForcedVal(Float.parseFloat(var28[2]));
            } else if ("engineRPMType".equals(var20)) {
               this.engineRPMType = var24.trim();
            } else if ("template".equals(var20)) {
               this.LoadTemplate(var24);
            } else if ("template!".equals(var20)) {
               VehicleTemplate var30 = ScriptManager.instance.getVehicleTemplate(var24);
               if (var30 == null) {
                  DebugLog.log("ERROR: template \"" + var24 + "\" not found");
               } else {
                  this.Load(var1, var30.body);
               }
            } else if ("engineRepairLevel".equals(var20)) {
               this.engineRepairLevel = Integer.parseInt(var24);
            } else if ("playerDamageProtection".equals(var20)) {
               this.setPlayerDamageProtection(Float.parseFloat(var24));
            }
         } else {
            Block var7 = var6.asBlock();
            if ("area".equals(var7.type)) {
               this.LoadArea(var7);
            } else if ("attachment".equals(var7.type)) {
               this.LoadAttachment(var7);
            } else if ("model".equals(var7.type)) {
               this.LoadModel(var7, this.models);
            } else if ("part".equals(var7.type)) {
               if (var7.id != null && var7.id.contains("*")) {
                  String var19 = var7.id;

                  for (Part var27 : this.parts) {
                     if (this.globMatch(var19, var27.id)) {
                        var7.id = var27.id;
                        this.LoadPart(var7);
                     }
                  }
               } else {
                  this.LoadPart(var7);
               }
            } else if ("passenger".equals(var7.type)) {
               if (var7.id != null && var7.id.contains("*")) {
                  String var18 = var7.id;

                  for (Passenger var26 : this.passengers) {
                     if (this.globMatch(var18, var26.id)) {
                        var7.id = var26.id;
                        this.LoadPassenger(var7);
                     }
                  }
               } else {
                  this.LoadPassenger(var7);
               }
            } else if ("physics".equals(var7.type)) {
               PhysicsShape var17 = this.LoadPhysicsShape(var7);
               if (var17 != null && this.m_physicsShapes.size() < 10) {
                  this.m_physicsShapes.add(var17);
               }
            } else if ("skin".equals(var7.type)) {
               Skin var16 = this.LoadSkin(var7);
               if (!StringUtils.isNullOrWhitespace(var16.texture)) {
                  this.skins.add(var16);
               }
            } else if ("wheel".equals(var7.type)) {
               this.LoadWheel(var7);
            } else if ("lightbar".equals(var7.type)) {
               for (Value var21 : var7.values) {
                  String var25 = var21.getKey().trim();
                  String var29 = var21.getValue().trim();
                  if ("soundSiren".equals(var25)) {
                     this.lightbar.soundSiren0 = var29 + "Yelp";
                     this.lightbar.soundSiren1 = var29 + "Wall";
                     this.lightbar.soundSiren2 = var29 + "Alarm";
                  }

                  if ("soundSiren0".equals(var25)) {
                     this.lightbar.soundSiren0 = var29;
                  }

                  if ("soundSiren1".equals(var25)) {
                     this.lightbar.soundSiren1 = var29;
                  }

                  if ("soundSiren2".equals(var25)) {
                     this.lightbar.soundSiren2 = var29;
                  }

                  if ("leftCol".equals(var25)) {
                     String[] var12 = var29.split(";");
                     this.leftSirenCol = new ImmutableColor(Float.parseFloat(var12[0]), Float.parseFloat(var12[1]), Float.parseFloat(var12[2]));
                  }

                  if ("rightCol".equals(var25)) {
                     String[] var31 = var29.split(";");
                     this.rightSirenCol = new ImmutableColor(Float.parseFloat(var31[0]), Float.parseFloat(var31[1]), Float.parseFloat(var31[2]));
                  }

                  this.lightbar.enable = true;
                  if (this.getPartById("lightbar") == null) {
                     Part var32 = new Part();
                     var32.id = "lightbar";
                     this.parts.add(var32);
                  }
               }
            } else if ("sound".equals(var7.type)) {
               for (Value var9 : var7.values) {
                  String var10 = var9.getKey().trim();
                  String var11 = var9.getValue().trim();
                  if ("backSignal".equals(var10)) {
                     this.sound.backSignal = StringUtils.discardNullOrWhitespace(var11);
                     this.sound.backSignalEnable = this.sound.backSignal != null;
                  } else if ("engine".equals(var10)) {
                     this.sound.engine = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("engineStart".equals(var10)) {
                     this.sound.engineStart = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("engineTurnOff".equals(var10)) {
                     this.sound.engineTurnOff = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("horn".equals(var10)) {
                     this.sound.horn = StringUtils.discardNullOrWhitespace(var11);
                     this.sound.hornEnable = this.sound.horn != null;
                  } else if ("ignitionFail".equals(var10)) {
                     this.sound.ignitionFail = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("ignitionFailNoPower".equals(var10)) {
                     this.sound.ignitionFailNoPower = StringUtils.discardNullOrWhitespace(var11);
                  }
               }
            }
         }
      }
   }

   public String getFileName() {
      return this.fileName;
   }

   public void Loaded() {
      float var1 = this.getModelScale();
      this.extents.mul(var1);
      this.maxSuspensionTravelCm *= var1;
      this.suspensionRestLength *= var1;
      this.centerOfMassOffset.mul(var1);
      this.physicsChassisShape.mul(var1);
      if (this.bHadShadowOExtents) {
         this.shadowExtents.mul(var1);
      } else {
         this.shadowExtents.set(this.extents.x(), this.extents.z());
      }

      if (this.bHadShadowOffset) {
         this.shadowOffset.mul(var1);
      } else {
         this.shadowOffset.set(this.centerOfMassOffset.x(), this.centerOfMassOffset.z());
      }

      for (Model var3 : this.models) {
         var3.offset.mul(var1);
      }

      for (ModelAttachment var12 : this.m_attachments) {
         var12.getOffset().mul(var1);
      }

      for (PhysicsShape var13 : this.m_physicsShapes) {
         var13.offset.mul(var1);
         switch (var13.type) {
            case 1:
               var13.extents.mul(var1);
               break;
            case 2:
               var13.radius *= var1;
         }
      }

      for (Wheel var14 : this.wheels) {
         var14.radius *= var1;
         var14.offset.mul(var1);
      }

      for (Area var15 : this.areas) {
         var15.x *= var1;
         var15.y *= var1;
         var15.w *= var1;
         var15.h *= var1;
      }

      if (!this.extents.equals(this.physicsChassisShape)) {
         DebugLog.Script.warn("vehicle \"" + this.name + "\" extents != physicsChassisShape");
      }

      for (int var10 = 0; var10 < this.passengers.size(); var10++) {
         Passenger var16 = this.passengers.get(var10);

         for (int var4 = 0; var4 < var16.getPositionCount(); var4++) {
            Position var5 = var16.getPosition(var4);
            var5.getOffset().mul(var1);
         }

         for (int var18 = 0; var18 < var16.switchSeats.size(); var18++) {
            SwitchSeat var20 = (SwitchSeat)var16.switchSeats.get(var18);
            var20.seat = this.getPassengerIndex(var20.id);

            assert var20.seat != -1;
         }
      }

      for (int var11 = 0; var11 < this.parts.size(); var11++) {
         Part var17 = this.parts.get(var11);
         if (var17.container != null && var17.container.seatID != null && !var17.container.seatID.isEmpty()) {
            var17.container.seat = this.getPassengerIndex(var17.container.seatID);
         }

         if (var17.specificItem && var17.itemType != null) {
            for (int var19 = 0; var19 < var17.itemType.size(); var19++) {
               var17.itemType.set(var19, (String)var17.itemType.get(var19) + this.mechanicType);
            }
         }
      }

      this.initCrawlOffsets();
      if (!GameServer.bServer) {
         this.toBullet();
      }
   }

   public void toBullet() {
      float[] var1 = new float[200];
      int var2 = 0;
      var1[var2++] = this.getModelScale();
      var1[var2++] = this.extents.x;
      var1[var2++] = this.extents.y;
      var1[var2++] = this.extents.z;
      var1[var2++] = this.physicsChassisShape.x;
      var1[var2++] = this.physicsChassisShape.y;
      var1[var2++] = this.physicsChassisShape.z;
      var1[var2++] = this.mass;
      var1[var2++] = this.centerOfMassOffset.x;
      var1[var2++] = this.centerOfMassOffset.y;
      var1[var2++] = this.centerOfMassOffset.z;
      var1[var2++] = this.rollInfluence;
      var1[var2++] = this.suspensionStiffness;
      var1[var2++] = this.suspensionCompression;
      var1[var2++] = this.suspensionDamping;
      var1[var2++] = this.maxSuspensionTravelCm;
      var1[var2++] = this.suspensionRestLength;
      if (SystemDisabler.getdoHighFriction()) {
         var1[var2++] = this.wheelFriction * 100.0F;
      } else {
         var1[var2++] = this.wheelFriction;
      }

      var1[var2++] = this.stoppingMovementForce;
      var1[var2++] = this.getWheelCount();

      for (int var3 = 0; var3 < this.getWheelCount(); var3++) {
         Wheel var4 = this.getWheel(var3);
         var1[var2++] = var4.front ? 1.0F : 0.0F;
         var1[var2++] = var4.offset.x + this.getModel().offset.x - 0.0F * this.centerOfMassOffset.x;
         var1[var2++] = var4.offset.y + this.getModel().offset.y - 0.0F * this.centerOfMassOffset.y + 1.0F * this.suspensionRestLength;
         var1[var2++] = var4.offset.z + this.getModel().offset.z - 0.0F * this.centerOfMassOffset.z;
         var1[var2++] = var4.radius;
      }

      var1[var2++] = this.m_physicsShapes.size() + 1;
      var1[var2++] = 1.0F;
      var1[var2++] = this.centerOfMassOffset.x;
      var1[var2++] = this.centerOfMassOffset.y;
      var1[var2++] = this.centerOfMassOffset.z;
      var1[var2++] = this.physicsChassisShape.x;
      var1[var2++] = this.physicsChassisShape.y;
      var1[var2++] = this.physicsChassisShape.z;
      var1[var2++] = 0.0F;
      var1[var2++] = 0.0F;
      var1[var2++] = 0.0F;

      for (int var48 = 0; var48 < this.m_physicsShapes.size(); var48++) {
         PhysicsShape var49 = this.m_physicsShapes.get(var48);
         var1[var2++] = var49.type;
         var1[var2++] = var49.offset.x;
         var1[var2++] = var49.offset.y;
         var1[var2++] = var49.offset.z;
         if (var49.type == 1) {
            var1[var2++] = var49.extents.x;
            var1[var2++] = var49.extents.y;
            var1[var2++] = var49.extents.z;
            var1[var2++] = var49.rotate.x;
            var1[var2++] = var49.rotate.y;
            var1[var2++] = var49.rotate.z;
         } else if (var49.type == 2) {
            var1[var2++] = var49.radius;
         }
      }

      Bullet.defineVehicleScript(this.getFullName(), var1);
   }

   private void LoadVector2f(String var1, Vector2f var2) {
      String[] var3 = var1.split(" ");
      var2.set(Float.parseFloat(var3[0]), Float.parseFloat(var3[1]));
   }

   private void LoadVector3f(String var1, Vector3f var2) {
      String[] var3 = var1.split(" ");
      var2.set(Float.parseFloat(var3[0]), Float.parseFloat(var3[1]), Float.parseFloat(var3[2]));
   }

   private void LoadVector4f(String var1, Vector4f var2) {
      String[] var3 = var1.split(" ");
      var2.set(Float.parseFloat(var3[0]), Float.parseFloat(var3[1]), Float.parseFloat(var3[2]), Float.parseFloat(var3[3]));
   }

   private void LoadVector2i(String var1, Vector2i var2) {
      String[] var3 = var1.split(" ");
      var2.set(Integer.parseInt(var3[0]), Integer.parseInt(var3[1]));
   }

   private ModelAttachment LoadAttachment(Block var1) {
      ModelAttachment var2 = this.getAttachmentById(var1.id);
      if (var2 == null) {
         var2 = new ModelAttachment(var1.id);
         this.m_attachments.add(var2);
      }

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("bone".equals(var5)) {
            var2.setBone(var6);
         } else if ("offset".equals(var5)) {
            this.LoadVector3f(var6, var2.getOffset());
         } else if ("rotate".equals(var5)) {
            this.LoadVector3f(var6, var2.getRotate());
         } else if ("canAttach".equals(var5)) {
            var2.setCanAttach(new ArrayList<>(Arrays.asList(var6.split(","))));
         } else if ("zoffset".equals(var5)) {
            var2.setZOffset(Float.parseFloat(var6));
         } else if ("updateconstraint".equals(var5)) {
            var2.setUpdateConstraint(Boolean.parseBoolean(var6));
         }
      }

      return var2;
   }

   private Model LoadModel(Block var1, ArrayList<Model> var2) {
      Model var3 = this.getModelById(var1.id, var2);
      if (var3 == null) {
         var3 = new Model();
         var3.id = var1.id;
         var2.add(var3);
      }

      for (Value var5 : var1.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if ("file".equals(var6)) {
            var3.file = var7;
         } else if ("offset".equals(var6)) {
            this.LoadVector3f(var7, var3.offset);
         } else if ("rotate".equals(var6)) {
            this.LoadVector3f(var7, var3.rotate);
         } else if ("scale".equals(var6)) {
            var3.scale = Float.parseFloat(var7);
         }
      }

      return var3;
   }

   private Skin LoadSkin(Block var1) {
      Skin var2 = new Skin();

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("texture".equals(var5)) {
            var2.texture = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureRust".equals(var5)) {
            var2.textureRust = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureMask".equals(var5)) {
            var2.textureMask = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureLights".equals(var5)) {
            var2.textureLights = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage1Overlay".equals(var5)) {
            var2.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage1Shell".equals(var5)) {
            var2.textureDamage1Shell = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage2Overlay".equals(var5)) {
            var2.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage2Shell".equals(var5)) {
            var2.textureDamage2Shell = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureShadow".equals(var5)) {
            var2.textureShadow = StringUtils.discardNullOrWhitespace(var6);
         }
      }

      return var2;
   }

   private Wheel LoadWheel(Block var1) {
      Wheel var2 = this.getWheelById(var1.id);
      if (var2 == null) {
         var2 = new Wheel();
         var2.id = var1.id;
         this.wheels.add(var2);
      }

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("model".equals(var5)) {
            var2.model = var6;
         } else if ("front".equals(var5)) {
            var2.front = Boolean.parseBoolean(var6);
         } else if ("offset".equals(var5)) {
            this.LoadVector3f(var6, var2.offset);
         } else if ("radius".equals(var5)) {
            var2.radius = Float.parseFloat(var6);
         } else if ("width".equals(var5)) {
            var2.width = Float.parseFloat(var6);
         }
      }

      return var2;
   }

   private Passenger LoadPassenger(Block var1) {
      Passenger var2 = this.getPassengerById(var1.id);
      if (var2 == null) {
         var2 = new Passenger();
         var2.id = var1.id;
         this.passengers.add(var2);
      }

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("area".equals(var5)) {
            var2.area = var6;
         } else if ("door".equals(var5)) {
            var2.door = var6;
         } else if ("door2".equals(var5)) {
            var2.door2 = var6;
         } else if ("hasRoof".equals(var5)) {
            var2.hasRoof = Boolean.parseBoolean(var6);
         } else if ("showPassenger".equals(var5)) {
            var2.showPassenger = Boolean.parseBoolean(var6);
         }
      }

      for (Block var8 : var1.children) {
         if ("anim".equals(var8.type)) {
            this.LoadAnim(var8, var2.anims);
         } else if ("position".equals(var8.type)) {
            this.LoadPosition(var8, var2.positions);
         } else if ("switchSeat".equals(var8.type)) {
            this.LoadPassengerSwitchSeat(var8, var2);
         }
      }

      return var2;
   }

   private Anim LoadAnim(Block var1, ArrayList<Anim> var2) {
      Anim var3 = this.getAnimationById(var1.id, var2);
      if (var3 == null) {
         var3 = new Anim();
         var3.id = var1.id;
         var2.add(var3);
      }

      for (Value var5 : var1.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if ("angle".equals(var6)) {
            this.LoadVector3f(var7, var3.angle);
         } else if ("anim".equals(var6)) {
            var3.anim = var7;
         } else if ("animate".equals(var6)) {
            var3.bAnimate = Boolean.parseBoolean(var7);
         } else if ("loop".equals(var6)) {
            var3.bLoop = Boolean.parseBoolean(var7);
         } else if ("reverse".equals(var6)) {
            var3.bReverse = Boolean.parseBoolean(var7);
         } else if ("rate".equals(var6)) {
            var3.rate = Float.parseFloat(var7);
         } else if ("offset".equals(var6)) {
            this.LoadVector3f(var7, var3.offset);
         } else if ("sound".equals(var6)) {
            var3.sound = var7;
         }
      }

      return var3;
   }

   private SwitchSeat LoadPassengerSwitchSeat(Block var1, Passenger var2) {
      SwitchSeat var3 = var2.getSwitchSeatById(var1.id);
      if (var1.isEmpty()) {
         if (var3 != null) {
            var2.switchSeats.remove(var3);
         }

         return null;
      } else {
         if (var3 == null) {
            var3 = new SwitchSeat();
            var3.id = var1.id;
            var2.switchSeats.add(var3);
         }

         for (Value var5 : var1.values) {
            String var6 = var5.getKey().trim();
            String var7 = var5.getValue().trim();
            if ("anim".equals(var6)) {
               var3.anim = var7;
            } else if ("rate".equals(var6)) {
               var3.rate = Float.parseFloat(var7);
            } else if ("sound".equals(var6)) {
               var3.sound = var7.isEmpty() ? null : var7;
            }
         }

         return var3;
      }
   }

   private Area LoadArea(Block var1) {
      Area var2 = this.getAreaById(var1.id);
      if (var2 == null) {
         var2 = new Area();
         var2.id = var1.id;
         this.areas.add(var2);
      }

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("xywh".equals(var5)) {
            String[] var7 = var6.split(" ");
            var2.x = Float.parseFloat(var7[0]);
            var2.y = Float.parseFloat(var7[1]);
            var2.w = Float.parseFloat(var7[2]);
            var2.h = Float.parseFloat(var7[3]);
         }
      }

      return var2;
   }

   private Part LoadPart(Block var1) {
      Part var2 = this.getPartById(var1.id);
      if (var2 == null) {
         var2 = new Part();
         var2.id = var1.id;
         this.parts.add(var2);
      }

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("area".equals(var5)) {
            var2.area = var6.isEmpty() ? null : var6;
         } else if ("itemType".equals(var5)) {
            var2.itemType = new ArrayList();
            String[] var7 = var6.split(";");

            for (String var11 : var7) {
               var2.itemType.add(var11);
            }
         } else if ("parent".equals(var5)) {
            var2.parent = var6.isEmpty() ? null : var6;
         } else if ("mechanicRequireKey".equals(var5)) {
            var2.mechanicRequireKey = Boolean.parseBoolean(var6);
         } else if ("repairMechanic".equals(var5)) {
            var2.setRepairMechanic(Boolean.parseBoolean(var6));
         } else if ("setAllModelsVisible".equals(var5)) {
            var2.bSetAllModelsVisible = Boolean.parseBoolean(var6);
         } else if ("wheel".equals(var5)) {
            var2.wheel = var6;
         } else if ("category".equals(var5)) {
            var2.category = var6;
         } else if ("specificItem".equals(var5)) {
            var2.specificItem = Boolean.parseBoolean(var6);
         } else if ("hasLightsRear".equals(var5)) {
            var2.hasLightsRear = Boolean.parseBoolean(var6);
         }
      }

      for (Block var13 : var1.children) {
         if ("anim".equals(var13.type)) {
            if (var2.anims == null) {
               var2.anims = new ArrayList();
            }

            this.LoadAnim(var13, var2.anims);
         } else if ("container".equals(var13.type)) {
            var2.container = this.LoadContainer(var13, var2.container);
         } else if ("door".equals(var13.type)) {
            var2.door = this.LoadDoor(var13);
         } else if ("lua".equals(var13.type)) {
            var2.luaFunctions = this.LoadLuaFunctions(var13);
         } else if ("model".equals(var13.type)) {
            if (var2.models == null) {
               var2.models = new ArrayList();
            }

            this.LoadModel(var13, var2.models);
         } else if ("table".equals(var13.type)) {
            Object var14 = var2.tables == null ? null : var2.tables.get(var13.id);
            KahluaTable var15 = this.LoadTable(var13, var14 instanceof KahluaTable ? (KahluaTable)var14 : null);
            if (var2.tables == null) {
               var2.tables = new HashMap();
            }

            var2.tables.put(var13.id, var15);
         } else if ("window".equals(var13.type)) {
            var2.window = this.LoadWindow(var13);
         }
      }

      return var2;
   }

   private PhysicsShape LoadPhysicsShape(Block var1) {
      byte var2 = -1;
      String var3 = var1.id;
      switch (var3) {
         case "box":
            var2 = 1;
            break;
         case "sphere":
            var2 = 2;
            break;
         default:
            return null;
      }

      PhysicsShape var9 = new PhysicsShape();
      var9.type = var2;

      for (Value var5 : var1.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if ("extents".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.extents);
         } else if ("offset".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.offset);
         } else if ("radius".equalsIgnoreCase(var6)) {
            var9.radius = Float.parseFloat(var7);
         } else if ("rotate".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.rotate);
         }
      }

      switch (var9.type) {
         case 1:
            if (var9.extents.x() <= 0.0F || var9.extents.y() <= 0.0F || var9.extents.z() <= 0.0F) {
               return null;
            }
            break;
         case 2:
            if (var9.radius <= 0.0F) {
               return null;
            }
      }

      return var9;
   }

   private Door LoadDoor(Block var1) {
      Door var2 = new Door();

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
      }

      return var2;
   }

   private Window LoadWindow(Block var1) {
      Window var2 = new Window();

      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("openable".equals(var5)) {
            var2.openable = Boolean.parseBoolean(var6);
         }
      }

      return var2;
   }

   private Container LoadContainer(Block var1, Container var2) {
      Container var3 = var2 == null ? new Container() : var2;

      for (Value var5 : var1.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if ("capacity".equals(var6)) {
            var3.capacity = Integer.parseInt(var7);
         } else if ("conditionAffectsCapacity".equals(var6)) {
            var3.conditionAffectsCapacity = Boolean.parseBoolean(var7);
         } else if ("contentType".equals(var6)) {
            var3.contentType = var7;
         } else if ("seat".equals(var6)) {
            var3.seatID = var7;
         } else if ("test".equals(var6)) {
            var3.luaTest = var7;
         }
      }

      return var3;
   }

   private HashMap<String, String> LoadLuaFunctions(Block var1) {
      HashMap var2 = new HashMap();

      for (Value var4 : var1.values) {
         if (var4.string.indexOf(61) == -1) {
            throw new RuntimeException("expected \"key = value\", got \"" + var4.string.trim() + "\" in " + this.getFullName());
         }

         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         var2.put(var5, var6);
      }

      return var2;
   }

   private Object checkIntegerKey(Object var1) {
      if (!(var1 instanceof String var2)) {
         return var1;
      } else {
         for (int var3 = 0; var3 < var2.length(); var3++) {
            if (!Character.isDigit(var2.charAt(var3))) {
               return var1;
            }
         }

         return Double.valueOf(var2);
      }
   }

   private KahluaTable LoadTable(Block var1, KahluaTable var2) {
      KahluaTable var3 = var2 == null ? LuaManager.platform.newTable() : var2;

      for (Value var5 : var1.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if (var7.isEmpty()) {
            var7 = null;
         }

         var3.rawset(this.checkIntegerKey(var6), var7);
      }

      for (Block var9 : var1.children) {
         Object var10 = var3.rawget(var9.type);
         KahluaTable var11 = this.LoadTable(var9, var10 instanceof KahluaTable ? (KahluaTable)var10 : null);
         var3.rawset(this.checkIntegerKey(var9.type), var11);
      }

      return var3;
   }

   private void LoadTemplate(String var1) {
      if (var1.contains("/")) {
         String[] var2 = var1.split("/");
         if (var2.length == 0 || var2.length > 3) {
            DebugLog.log("ERROR: template \"" + var1 + "\"");
            return;
         }

         for (int var3 = 0; var3 < var2.length; var3++) {
            var2[var3] = var2[var3].trim();
            if (var2[var3].isEmpty()) {
               DebugLog.log("ERROR: template \"" + var1 + "\"");
               return;
            }
         }

         String var9 = var2[0];
         VehicleTemplate var4 = ScriptManager.instance.getVehicleTemplate(var9);
         if (var4 == null) {
            DebugLog.log("ERROR: template \"" + var1 + "\" not found");
            return;
         }

         VehicleScript var5 = var4.getScript();
         String var6 = var2[1];
         switch (var6) {
            case "area":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyAreasFrom(var5, var2[2]);
               break;
            case "part":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyPartsFrom(var5, var2[2]);
               break;
            case "passenger":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyPassengersFrom(var5, var2[2]);
               break;
            case "wheel":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyWheelsFrom(var5, var2[2]);
               break;
            default:
               DebugLog.log("ERROR: template \"" + var1 + "\"");
               return;
         }
      } else {
         String var8 = var1.trim();
         VehicleTemplate var10 = ScriptManager.instance.getVehicleTemplate(var8);
         if (var10 == null) {
            DebugLog.log("ERROR: template \"" + var1 + "\" not found");
            return;
         }

         VehicleScript var11 = var10.getScript();
         this.copyAreasFrom(var11, "*");
         this.copyPartsFrom(var11, "*");
         this.copyPassengersFrom(var11, "*");
         this.copyWheelsFrom(var11, "*");
      }
   }

   public void copyAreasFrom(VehicleScript var1, String var2) {
      if ("*".equals(var2)) {
         for (int var3 = 0; var3 < var1.getAreaCount(); var3++) {
            Area var4 = var1.getArea(var3);
            int var5 = this.getIndexOfAreaById(var4.id);
            if (var5 == -1) {
               this.areas.add(var4.makeCopy());
            } else {
               this.areas.set(var5, var4.makeCopy());
            }
         }
      } else {
         Area var6 = var1.getAreaById(var2);
         if (var6 == null) {
            DebugLog.log("ERROR: area \"" + var2 + "\" not found");
            return;
         }

         int var7 = this.getIndexOfAreaById(var6.id);
         if (var7 == -1) {
            this.areas.add(var6.makeCopy());
         } else {
            this.areas.set(var7, var6.makeCopy());
         }
      }
   }

   public void copyPartsFrom(VehicleScript var1, String var2) {
      if ("*".equals(var2)) {
         for (int var3 = 0; var3 < var1.getPartCount(); var3++) {
            Part var4 = var1.getPart(var3);
            int var5 = this.getIndexOfPartById(var4.id);
            if (var5 == -1) {
               this.parts.add(var4.makeCopy());
            } else {
               this.parts.set(var5, var4.makeCopy());
            }
         }
      } else {
         Part var6 = var1.getPartById(var2);
         if (var6 == null) {
            DebugLog.log("ERROR: part \"" + var2 + "\" not found");
            return;
         }

         int var7 = this.getIndexOfPartById(var6.id);
         if (var7 == -1) {
            this.parts.add(var6.makeCopy());
         } else {
            this.parts.set(var7, var6.makeCopy());
         }
      }
   }

   public void copyPassengersFrom(VehicleScript var1, String var2) {
      if ("*".equals(var2)) {
         for (int var3 = 0; var3 < var1.getPassengerCount(); var3++) {
            Passenger var4 = var1.getPassenger(var3);
            int var5 = this.getPassengerIndex(var4.id);
            if (var5 == -1) {
               this.passengers.add(var4.makeCopy());
            } else {
               this.passengers.set(var5, var4.makeCopy());
            }
         }
      } else {
         Passenger var6 = var1.getPassengerById(var2);
         if (var6 == null) {
            DebugLog.log("ERROR: passenger \"" + var2 + "\" not found");
            return;
         }

         int var7 = this.getPassengerIndex(var6.id);
         if (var7 == -1) {
            this.passengers.add(var6.makeCopy());
         } else {
            this.passengers.set(var7, var6.makeCopy());
         }
      }
   }

   public void copyWheelsFrom(VehicleScript var1, String var2) {
      if ("*".equals(var2)) {
         for (int var3 = 0; var3 < var1.getWheelCount(); var3++) {
            Wheel var4 = var1.getWheel(var3);
            int var5 = this.getIndexOfWheelById(var4.id);
            if (var5 == -1) {
               this.wheels.add(var4.makeCopy());
            } else {
               this.wheels.set(var5, var4.makeCopy());
            }
         }
      } else {
         Wheel var6 = var1.getWheelById(var2);
         if (var6 == null) {
            DebugLog.log("ERROR: wheel \"" + var2 + "\" not found");
            return;
         }

         int var7 = this.getIndexOfWheelById(var6.id);
         if (var7 == -1) {
            this.wheels.add(var6.makeCopy());
         } else {
            this.wheels.set(var7, var6.makeCopy());
         }
      }
   }

   private Position LoadPosition(Block var1, ArrayList<Position> var2) {
      Position var3 = this.getPositionById(var1.id, var2);
      if (var1.isEmpty()) {
         if (var3 != null) {
            var2.remove(var3);
         }

         return null;
      } else {
         if (var3 == null) {
            var3 = new Position();
            var3.id = var1.id;
            var2.add(var3);
         }

         for (Value var5 : var1.values) {
            String var6 = var5.getKey().trim();
            String var7 = var5.getValue().trim();
            if ("rotate".equals(var6)) {
               this.LoadVector3f(var7, var3.rotate);
            } else if ("offset".equals(var6)) {
               this.LoadVector3f(var7, var3.offset);
            } else if ("area".equals(var6)) {
               var3.area = var7.isEmpty() ? null : var7;
            }
         }

         return var3;
      }
   }

   private void initCrawlOffsets() {
      for (int var1 = 0; var1 < this.getWheelCount(); var1++) {
         Wheel var2 = this.getWheel(var1);
         if (var2.id.contains("Left")) {
            this.initCrawlOffsets(var2);
         }
      }

      float var6 = this.extents.z + BaseVehicle.PLUS_RADIUS * 2.0F;

      for (int var7 = 0; var7 < this.crawlOffsets.size(); var7++) {
         this.crawlOffsets.set(var7, (this.extents.z / 2.0F + BaseVehicle.PLUS_RADIUS + this.crawlOffsets.get(var7) - this.centerOfMassOffset.z) / var6);
      }

      this.crawlOffsets.sort();

      for (int var8 = 0; var8 < this.crawlOffsets.size(); var8++) {
         float var3 = this.crawlOffsets.get(var8);

         for (int var4 = var8 + 1; var4 < this.crawlOffsets.size(); var4++) {
            float var5 = this.crawlOffsets.get(var4);
            if ((var5 - var3) * var6 < 0.15F) {
               this.crawlOffsets.removeAt(var4--);
            }
         }
      }
   }

   private void initCrawlOffsets(Wheel var1) {
      float var2 = 0.3F;
      float var3 = this.getModel() == null ? 0.0F : this.getModel().getOffset().z;
      float var4 = this.centerOfMassOffset.z + this.extents.z / 2.0F;
      float var5 = this.centerOfMassOffset.z - this.extents.z / 2.0F;

      for (int var6 = 0; var6 < 10; var6++) {
         float var7 = var3 + var1.offset.z + var1.radius + var2 + var2 * var6;
         if (var7 + var2 <= var4 && !this.isOverlappingWheel(var7)) {
            this.crawlOffsets.add(var7);
         }

         var7 = var3 + var1.offset.z - var1.radius - var2 - var2 * var6;
         if (var7 - var2 >= var5 && !this.isOverlappingWheel(var7)) {
            this.crawlOffsets.add(var7);
         }
      }
   }

   private boolean isOverlappingWheel(float var1) {
      float var2 = 0.3F;
      float var3 = this.getModel() == null ? 0.0F : this.getModel().getOffset().z;

      for (int var4 = 0; var4 < this.getWheelCount(); var4++) {
         Wheel var5 = this.getWheel(var4);
         if (var5.id.contains("Left") && Math.abs(var3 + var5.offset.z - var1) < (var5.radius + var2) * 0.99F) {
            return true;
         }
      }

      return false;
   }

   public String getName() {
      return this.name;
   }

   public String getFullName() {
      return this.getModule().getName() + "." + this.getName();
   }

   public Model getModel() {
      return this.models.isEmpty() ? null : this.models.get(0);
   }

   public Vector3f getModelOffset() {
      return this.getModel() == null ? null : this.getModel().getOffset();
   }

   public float getModelScale() {
      return this.getModel() == null ? 1.0F : this.getModel().scale;
   }

   public void setModelScale(float var1) {
      Model var2 = this.getModel();
      if (var2 != null) {
         float var3 = var2.scale;
         var2.scale = 1.0F / var3;
         this.Loaded();
         var2.scale = PZMath.clamp(var1, 0.01F, 100.0F);
         this.Loaded();
      }
   }

   public int getModelCount() {
      return this.models.size();
   }

   public Model getModelByIndex(int var1) {
      return this.models.get(var1);
   }

   public Model getModelById(String var1, ArrayList<Model> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
         Model var4 = (Model)var2.get(var3);
         if (StringUtils.isNullOrWhitespace(var4.id) && StringUtils.isNullOrWhitespace(var1)) {
            return var4;
         }

         if (var4.id != null && var4.id.equals(var1)) {
            return var4;
         }
      }

      return null;
   }

   public Model getModelById(String var1) {
      return this.getModelById(var1, this.models);
   }

   public int getAttachmentCount() {
      return this.m_attachments.size();
   }

   public ModelAttachment getAttachment(int var1) {
      return this.m_attachments.get(var1);
   }

   public ModelAttachment getAttachmentById(String var1) {
      for (int var2 = 0; var2 < this.m_attachments.size(); var2++) {
         ModelAttachment var3 = this.m_attachments.get(var2);
         if (var3.getId().equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public ModelAttachment addAttachment(ModelAttachment var1) {
      this.m_attachments.add(var1);
      return var1;
   }

   public ModelAttachment removeAttachment(ModelAttachment var1) {
      this.m_attachments.remove(var1);
      return var1;
   }

   public ModelAttachment addAttachmentAt(int var1, ModelAttachment var2) {
      this.m_attachments.add(var1, var2);
      return var2;
   }

   public ModelAttachment removeAttachment(int var1) {
      return this.m_attachments.remove(var1);
   }

   public LightBar getLightbar() {
      return this.lightbar;
   }

   public Sounds getSounds() {
      return this.sound;
   }

   public boolean getHasSiren() {
      return this.hasSiren;
   }

   public Vector3f getExtents() {
      return this.extents;
   }

   public Vector3f getPhysicsChassisShape() {
      return this.physicsChassisShape;
   }

   public Vector2f getShadowExtents() {
      return this.shadowExtents;
   }

   public Vector2f getShadowOffset() {
      return this.shadowOffset;
   }

   public Vector2f getExtentsOffset() {
      return this.extentsOffset;
   }

   public float getMass() {
      return this.mass;
   }

   public Vector3f getCenterOfMassOffset() {
      return this.centerOfMassOffset;
   }

   public float getEngineForce() {
      return this.engineForce;
   }

   public float getEngineIdleSpeed() {
      return this.engineIdleSpeed;
   }

   public int getEngineQuality() {
      return this.engineQuality;
   }

   public int getEngineLoudness() {
      return this.engineLoudness;
   }

   public float getRollInfluence() {
      return this.rollInfluence;
   }

   public float getSteeringIncrement() {
      return this.steeringIncrement;
   }

   public float getSteeringClamp(float var1) {
      var1 = Math.abs(var1);
      float var2 = var1 / this.maxSpeed;
      if (var2 > 1.0F) {
         var2 = 1.0F;
      }

      var2 = 1.0F - var2;
      return (this.steeringClampMax - this.steeringClamp) * var2 + this.steeringClamp;
   }

   public float getSuspensionStiffness() {
      return this.suspensionStiffness;
   }

   public float getSuspensionDamping() {
      return this.suspensionDamping;
   }

   public float getSuspensionCompression() {
      return this.suspensionCompression;
   }

   public float getSuspensionRestLength() {
      return this.suspensionRestLength;
   }

   public float getSuspensionTravel() {
      return this.maxSuspensionTravelCm;
   }

   public float getWheelFriction() {
      return this.wheelFriction;
   }

   public int getWheelCount() {
      return this.wheels.size();
   }

   public Wheel getWheel(int var1) {
      return this.wheels.get(var1);
   }

   public Wheel getWheelById(String var1) {
      for (int var2 = 0; var2 < this.wheels.size(); var2++) {
         Wheel var3 = this.wheels.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int getIndexOfWheelById(String var1) {
      for (int var2 = 0; var2 < this.wheels.size(); var2++) {
         Wheel var3 = this.wheels.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var2;
         }
      }

      return -1;
   }

   public int getPassengerCount() {
      return this.passengers.size();
   }

   public Passenger getPassenger(int var1) {
      return this.passengers.get(var1);
   }

   public Passenger getPassengerById(String var1) {
      for (int var2 = 0; var2 < this.passengers.size(); var2++) {
         Passenger var3 = this.passengers.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int getPassengerIndex(String var1) {
      for (int var2 = 0; var2 < this.passengers.size(); var2++) {
         Passenger var3 = this.passengers.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var2;
         }
      }

      return -1;
   }

   public int getPhysicsShapeCount() {
      return this.m_physicsShapes.size();
   }

   public PhysicsShape getPhysicsShape(int var1) {
      return var1 >= 0 && var1 < this.m_physicsShapes.size() ? this.m_physicsShapes.get(var1) : null;
   }

   public int getFrontEndHealth() {
      return this.frontEndHealth;
   }

   public int getRearEndHealth() {
      return this.rearEndHealth;
   }

   public int getStorageCapacity() {
      return this.storageCapacity;
   }

   public Skin getTextures() {
      return this.textures;
   }

   public int getSkinCount() {
      return this.skins.size();
   }

   public Skin getSkin(int var1) {
      return this.skins.get(var1);
   }

   public int getAreaCount() {
      return this.areas.size();
   }

   public Area getArea(int var1) {
      return this.areas.get(var1);
   }

   public Area getAreaById(String var1) {
      for (int var2 = 0; var2 < this.areas.size(); var2++) {
         Area var3 = this.areas.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int getIndexOfAreaById(String var1) {
      for (int var2 = 0; var2 < this.areas.size(); var2++) {
         Area var3 = this.areas.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var2;
         }
      }

      return -1;
   }

   public int getPartCount() {
      return this.parts.size();
   }

   public Part getPart(int var1) {
      return this.parts.get(var1);
   }

   public Part getPartById(String var1) {
      for (int var2 = 0; var2 < this.parts.size(); var2++) {
         Part var3 = this.parts.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int getIndexOfPartById(String var1) {
      for (int var2 = 0; var2 < this.parts.size(); var2++) {
         Part var3 = this.parts.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var2;
         }
      }

      return -1;
   }

   private Anim getAnimationById(String var1, ArrayList<Anim> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
         Anim var4 = (Anim)var2.get(var3);
         if (var4.id != null && var4.id.equals(var1)) {
            return var4;
         }
      }

      return null;
   }

   private Position getPositionById(String var1, ArrayList<Position> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
         Position var4 = (Position)var2.get(var3);
         if (var4.id != null && var4.id.equals(var1)) {
            return var4;
         }
      }

      return null;
   }

   public boolean globMatch(String var1, String var2) {
      Pattern var3 = Pattern.compile(var1.replaceAll("\\*", ".*"));
      return var3.matcher(var2).matches();
   }

   public int getGearRatioCount() {
      return this.gearRatioCount;
   }

   public int getSeats() {
      return this.seats;
   }

   public void setSeats(int var1) {
      this.seats = var1;
   }

   public int getMechanicType() {
      return this.mechanicType;
   }

   public void setMechanicType(int var1) {
      this.mechanicType = var1;
   }

   public int getEngineRepairLevel() {
      return this.engineRepairLevel;
   }

   public int getHeadlightConfigLevel() {
      return 2;
   }

   public void setEngineRepairLevel(int var1) {
      this.engineRepairLevel = var1;
   }

   public float getPlayerDamageProtection() {
      return this.playerDamageProtection;
   }

   public void setPlayerDamageProtection(float var1) {
      this.playerDamageProtection = var1;
   }

   public float getForcedHue() {
      return this.forcedHue;
   }

   public void setForcedHue(float var1) {
      this.forcedHue = var1;
   }

   public float getForcedSat() {
      return this.forcedSat;
   }

   public void setForcedSat(float var1) {
      this.forcedSat = var1;
   }

   public float getForcedVal() {
      return this.forcedVal;
   }

   public void setForcedVal(float var1) {
      this.forcedVal = var1;
   }

   public String getEngineRPMType() {
      return this.engineRPMType;
   }

   public void setEngineRPMType(String var1) {
      this.engineRPMType = var1;
   }

   public float getOffroadEfficiency() {
      return this.offroadEfficiency;
   }

   public void setOffroadEfficiency(float var1) {
      this.offroadEfficiency = var1;
   }

   public TFloatArrayList getCrawlOffsets() {
      return this.crawlOffsets;
   }
}
