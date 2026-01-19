package zombie.gameStates;

import java.io.File;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Stack;
import org.joml.Vector2f;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.KahluaTableIterator;
import zombie.AmbientStreamManager;
import zombie.FliesSound;
import zombie.VirtualZombieManager;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.chat.ChatElement;
import zombie.config.BooleanConfigOption;
import zombie.config.ConfigFile;
import zombie.config.ConfigOption;
import zombie.core.BoxedStaticValues;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.core.math.PZMath;
import zombie.core.properties.PropertyContainer;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.debug.LineDrawer;
import zombie.erosion.ErosionData.Square;
import zombie.gameStates.DebugChunkState.BooleanDebugOption;
import zombie.gameStates.GameStateMachine.StateAction;
import zombie.input.GameKeyboard;
import zombie.input.Mouse;
import zombie.iso.BuildingDef;
import zombie.iso.IsoCamera;
import zombie.iso.IsoCell;
import zombie.iso.IsoChunk;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoLightSource;
import zombie.iso.IsoObject;
import zombie.iso.IsoObjectPicker;
import zombie.iso.IsoRoomLight;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.NearestWalls;
import zombie.iso.ParticlesFire;
import zombie.iso.IsoMetaGrid.VehicleZone;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.iso.LosUtil.TestResults;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.sprite.IsoSprite;
import zombie.network.GameClient;
import zombie.randomizedWorld.randomizedVehicleStory.RandomizedVehicleStoryBase;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner;
import zombie.ui.TextDrawObject;
import zombie.ui.TextManager;
import zombie.ui.UIElement;
import zombie.ui.UIFont;
import zombie.ui.UIManager;
import zombie.util.Type;
import zombie.vehicles.ClipperOffset;
import zombie.vehicles.EditVehicleState.LuaEnvironment;
import zombie.vehicles.PolygonalMap2.LiangBarsky;

public final class DebugChunkState extends GameState {
   public static DebugChunkState instance;
   private LuaEnvironment m_luaEnv;
   private boolean bExit = false;
   private final ArrayList<UIElement> m_gameUI = new ArrayList<>();
   private final ArrayList<UIElement> m_selfUI = new ArrayList<>();
   private boolean m_bSuspendUI;
   private KahluaTable m_table = null;
   private int m_playerIndex = 0;
   private int m_z = 0;
   private int gridX = -1;
   private int gridY = -1;
   private UIFont FONT = UIFont.DebugConsole;
   private String m_vehicleStory = "Basic Car Crash";
   static boolean keyQpressed = false;
   private static ClipperOffset m_clipperOffset = null;
   private static ByteBuffer m_clipperBuffer;
   private static final int VERSION = 1;
   private final ArrayList<ConfigOption> options = new ArrayList<>();
   private BooleanDebugOption BuildingRect = new BooleanDebugOption(this, "BuildingRect", true);
   private BooleanDebugOption ChunkGrid = new BooleanDebugOption(this, "ChunkGrid", true);
   private BooleanDebugOption ClosestRoomSquare = new BooleanDebugOption(this, "ClosestRoomSquare", true);
   private BooleanDebugOption EmptySquares = new BooleanDebugOption(this, "EmptySquares", true);
   private BooleanDebugOption FlyBuzzEmitters = new BooleanDebugOption(this, "FlyBuzzEmitters", true);
   private BooleanDebugOption LightSquares = new BooleanDebugOption(this, "LightSquares", true);
   private BooleanDebugOption LineClearCollide = new BooleanDebugOption(this, "LineClearCollide", true);
   private BooleanDebugOption NearestWallsOpt = new BooleanDebugOption(this, "NearestWalls", true);
   private BooleanDebugOption ObjectPicker = new BooleanDebugOption(this, "ObjectPicker", true);
   private BooleanDebugOption RoomLightRects = new BooleanDebugOption(this, "RoomLightRects", true);
   private BooleanDebugOption VehicleStory = new BooleanDebugOption(this, "VehicleStory", true);
   private BooleanDebugOption RandomSquareInZone = new BooleanDebugOption(this, "RandomSquareInZone", true);
   private BooleanDebugOption ZoneRect = new BooleanDebugOption(this, "ZoneRect", true);

   public DebugChunkState() {
      instance = this;
   }

   public void enter() {
      instance = this;
      this.load();
      if (this.m_luaEnv == null) {
         this.m_luaEnv = new LuaEnvironment(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         this.m_z = var1 == null ? 0 : (int)var1.z;
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("DebugChunkState_InitUI"), this);
         if (this.m_table != null && this.m_table.getMetatable() != null) {
            this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", Boolean.FALSE);
         }
      } else {
         UIManager.UI.addAll(this.m_selfUI);
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("showUI"), this.m_table);
      }

      this.bExit = false;
   }

   public void yield() {
      this.restoreGameUI();
   }

   public void reenter() {
      this.saveGameUI();
   }

   public void exit() {
      this.save();
      this.restoreGameUI();

      for (int var1 = 0; var1 < IsoCamera.cameras.length; var1++) {
         IsoCamera.cameras[var1].DeferedX = IsoCamera.cameras[var1].DeferedY = 0.0F;
      }
   }

   public void render() {
      IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
      IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
      boolean var1 = true;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (var2 != this.m_playerIndex && IsoPlayer.players[var2] != null) {
            Core.getInstance().StartFrame(var2, var1);
            Core.getInstance().EndFrame(var2);
            var1 = false;
         }
      }

      Core.getInstance().StartFrame(this.m_playerIndex, var1);
      this.renderScene();
      Core.getInstance().EndFrame(this.m_playerIndex);
      Core.getInstance().RenderOffScreenBuffer();

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         TextDrawObject.NoRender(var3);
         ChatElement.NoRender(var3);
      }

      if (Core.getInstance().StartFrameUI()) {
         this.renderUI();
      }

      Core.getInstance().EndFrameUI();
   }

   public StateAction update() {
      return !this.bExit && !GameKeyboard.isKeyPressed(60) ? this.updateScene() : StateAction.Continue;
   }

   public static DebugChunkState checkInstance() {
      instance = null;
      if (instance != null) {
         if (instance.m_table != null && instance.m_table.getMetatable() != null) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == null) {
               instance = null;
            }
         } else {
            instance = null;
         }
      }

      return instance == null ? new DebugChunkState() : instance;
   }

   public void renderScene() {
      IsoCamera.frameState.set(this.m_playerIndex);
      SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
      SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
      SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
      IsoSprite.globalOffsetX = -1.0F;
      IsoWorld.instance.CurrentCell.render();
      if (this.ChunkGrid.getValue()) {
         this.drawGrid();
      }

      this.drawCursor();
      if (this.LightSquares.getValue()) {
         Stack var1 = IsoWorld.instance.getCell().getLamppostPositions();

         for (int var2 = 0; var2 < var1.size(); var2++) {
            IsoLightSource var3 = (IsoLightSource)var1.get(var2);
            if (var3.z == this.m_z) {
               this.paintSquare(var3.x, var3.y, var3.z, 1.0F, 1.0F, 0.0F, 0.5F);
            }
         }
      }

      if (this.ZoneRect.getValue()) {
         this.drawZones();
      }

      if (this.BuildingRect.getValue()) {
         IsoGridSquare var5 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, this.m_z);
         if (var5 != null && var5.getBuilding() != null) {
            BuildingDef var9 = var5.getBuilding().getDef();
            this.DrawIsoLine(var9.getX(), var9.getY(), var9.getX2(), var9.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX2(), var9.getY(), var9.getX2(), var9.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX2(), var9.getY2(), var9.getX(), var9.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX(), var9.getY2(), var9.getX(), var9.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
         }
      }

      if (this.RoomLightRects.getValue()) {
         ArrayList var6 = IsoWorld.instance.CurrentCell.roomLights;

         for (int var10 = 0; var10 < var6.size(); var10++) {
            IsoRoomLight var12 = (IsoRoomLight)var6.get(var10);
            if (var12.z == this.m_z) {
               this.DrawIsoRect(var12.x, var12.y, var12.width, var12.height, 0.0F, 1.0F, 1.0F, 1.0F, 1);
            }
         }
      }

      if (this.FlyBuzzEmitters.getValue()) {
         FliesSound.instance.render();
      }

      if (this.ClosestRoomSquare.getValue()) {
         float var7 = IsoPlayer.players[this.m_playerIndex].getX();
         float var11 = IsoPlayer.players[this.m_playerIndex].getY();
         Vector2f var13 = new Vector2f();
         BuildingDef var4 = ((AmbientStreamManager)AmbientStreamManager.getInstance()).getNearestBuilding(var7, var11, var13);
         if (var4 != null) {
            this.DrawIsoLine(var7, var11, var13.x, var13.y, 1.0F, 1.0F, 1.0F, 1.0F, 1);
         }
      }

      if (this.m_table != null && this.m_table.rawget("selectedSquare") != null) {
         IsoGridSquare var8 = (IsoGridSquare)Type.tryCastTo(this.m_table.rawget("selectedSquare"), IsoGridSquare.class);
         if (var8 != null) {
            this.DrawIsoRect(var8.x, var8.y, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 2);
         }
      }

      LineDrawer.render();
      LineDrawer.clear();
   }

   private void renderUI() {
      int var1 = this.m_playerIndex;
      Stack var2 = IsoWorld.instance.getCell().getLamppostPositions();
      int var3 = 0;

      for (int var4 = 0; var4 < var2.size(); var4++) {
         IsoLightSource var5 = (IsoLightSource)var2.get(var4);
         if (var5.bActive) {
            var3++;
         }
      }

      UIManager.render();
   }

   public void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

   public StateAction updateScene() {
      IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
      IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
      UIManager.setPicked(IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA()));
      IsoObject var1 = UIManager.getPicked() == null ? null : UIManager.getPicked().tile;
      UIManager.setLastPicked(var1);
      if (GameKeyboard.isKeyDown(16)) {
         if (!keyQpressed) {
            IsoGridSquare var2 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, 0);
            if (var2 != null) {
               GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(var2.chunk);
               DebugLog.General.debugln("Requesting sync IsoChunk %s", var2.chunk);
            }

            keyQpressed = true;
         }
      } else {
         keyQpressed = false;
      }

      if (GameKeyboard.isKeyDown(19)) {
         if (!keyQpressed) {
            DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(true);
            keyQpressed = true;
            DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
         }
      } else {
         keyQpressed = false;
      }

      if (GameKeyboard.isKeyDown(20)) {
         if (!keyQpressed) {
            DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(false);
            keyQpressed = true;
            DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
         }
      } else {
         keyQpressed = false;
      }

      if (GameKeyboard.isKeyDown(31)) {
         if (!keyQpressed) {
            ParticlesFire.getInstance().reloadShader();
            keyQpressed = true;
            DebugLog.General.debugln("ParticlesFire.reloadShader");
         }
      } else {
         keyQpressed = false;
      }

      IsoCamera.update();
      this.updateCursor();
      return StateAction.Remain;
   }

   private void saveGameUI() {
      this.m_gameUI.clear();
      this.m_gameUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      this.m_bSuspendUI = UIManager.bSuspend;
      UIManager.bSuspend = false;
      UIManager.setShowPausedMessage(false);
      UIManager.defaultthread = this.m_luaEnv.thread;
   }

   private void restoreGameUI() {
      this.m_selfUI.clear();
      this.m_selfUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      UIManager.UI.addAll(this.m_gameUI);
      UIManager.bSuspend = this.m_bSuspendUI;
      UIManager.setShowPausedMessage(true);
      UIManager.defaultthread = LuaManager.thread;
   }

   public Object fromLua0(String var1) {
      switch (var1) {
         case "exit":
            this.bExit = true;
            return null;
         case "getCameraDragX":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedX);
         case "getCameraDragY":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedY);
         case "getPlayerIndex":
            return BoxedStaticValues.toDouble(this.m_playerIndex);
         case "getVehicleStory":
            return this.m_vehicleStory;
         case "getZ":
            return BoxedStaticValues.toDouble(this.m_z);
         default:
            throw new IllegalArgumentException(String.format("unhandled \"%s\"", var1));
      }
   }

   public Object fromLua1(String var1, Object var2) {
      switch (var1) {
         case "getCameraDragX":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedX);
         case "getCameraDragY":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedY);
         case "setPlayerIndex":
            this.m_playerIndex = PZMath.clamp(((Double)var2).intValue(), 0, 3);
            return null;
         case "setVehicleStory":
            this.m_vehicleStory = (String)var2;
            return null;
         case "setZ":
            this.m_z = PZMath.clamp(((Double)var2).intValue(), 0, 7);
            return null;
         default:
            throw new IllegalArgumentException(String.format("unhandled \"%s\" \"%s\"", var1, var2));
      }
   }

   public Object fromLua2(String var1, Object var2, Object var3) {
      byte var5 = -1;
      switch (var1.hashCode()) {
         case -1879300743:
            if (var1.equals("dragCamera")) {
               var5 = 0;
            }
         default:
            switch (var5) {
               case 0:
                  float var6 = ((Double)var2).floatValue();
                  float var7 = ((Double)var3).floatValue();
                  IsoCamera.cameras[this.m_playerIndex].DeferedX = -var6;
                  IsoCamera.cameras[this.m_playerIndex].DeferedY = -var7;
                  return null;
               default:
                  throw new IllegalArgumentException(String.format("unhandled \"%s\" \"%s\" \\\"%s\\\"", var1, var2, var3));
            }
      }
   }

   private void updateCursor() {
      int var1 = this.m_playerIndex;
      int var2 = Core.TileScale;
      float var3 = Mouse.getXA();
      float var4 = Mouse.getYA();
      var3 -= IsoCamera.getScreenLeft(var1);
      var4 -= IsoCamera.getScreenTop(var1);
      var3 *= Core.getInstance().getZoom(var1);
      var4 *= Core.getInstance().getZoom(var1);
      int var5 = this.m_z;
      this.gridX = (int)IsoUtils.XToIso(var3, var4, var5);
      this.gridY = (int)IsoUtils.YToIso(var3, var4, var5);
   }

   private void DrawIsoLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
      float var10 = this.m_z;
      float var11 = IsoUtils.XToScreenExact(var1, var2, var10, 0);
      float var12 = IsoUtils.YToScreenExact(var1, var2, var10, 0);
      float var13 = IsoUtils.XToScreenExact(var3, var4, var10, 0);
      float var14 = IsoUtils.YToScreenExact(var3, var4, var10, 0);
      LineDrawer.drawLine(var11, var12, var13, var14, var5, var6, var7, var8, var9);
   }

   private void DrawIsoRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
      this.DrawIsoLine(var1, var2, var1 + var3, var2, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1 + var3, var2, var1 + var3, var2 + var4, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1 + var3, var2 + var4, var1, var2 + var4, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1, var2 + var4, var1, var2, var5, var6, var7, var8, var9);
   }

   private void drawGrid() {
      int var1 = this.m_playerIndex;
      float var2 = IsoUtils.XToIso(-128.0F, -256.0F, 0.0F);
      float var3 = IsoUtils.YToIso(Core.getInstance().getOffscreenWidth(var1) + 128, -256.0F, 0.0F);
      float var4 = IsoUtils.XToIso(Core.getInstance().getOffscreenWidth(var1) + 128, Core.getInstance().getOffscreenHeight(var1) + 256, 6.0F);
      float var5 = IsoUtils.YToIso(-128.0F, Core.getInstance().getOffscreenHeight(var1) + 256, 6.0F);
      int var7 = (int)var3;
      int var9 = (int)var5;
      int var6 = (int)var2;
      int var8 = (int)var4;
      var6 -= 2;
      var7 -= 2;

      for (int var10 = var7; var10 <= var9; var10++) {
         if (var10 % 10 == 0) {
            this.DrawIsoLine(var6, var10, var8, var10, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         }
      }

      for (int var13 = var6; var13 <= var8; var13++) {
         if (var13 % 10 == 0) {
            this.DrawIsoLine(var13, var7, var13, var9, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         }
      }

      for (int var14 = var7; var14 <= var9; var14++) {
         if (var14 % 300 == 0) {
            this.DrawIsoLine(var6, var14, var8, var14, 0.0F, 1.0F, 0.0F, 0.5F, 1);
         }
      }

      for (int var15 = var6; var15 <= var8; var15++) {
         if (var15 % 300 == 0) {
            this.DrawIsoLine(var15, var7, var15, var9, 0.0F, 1.0F, 0.0F, 0.5F, 1);
         }
      }

      if (GameClient.bClient) {
         for (int var16 = var7; var16 <= var9; var16++) {
            if (var16 % 50 == 0) {
               this.DrawIsoLine(var6, var16, var8, var16, 1.0F, 0.0F, 0.0F, 0.5F, 1);
            }
         }

         for (int var17 = var6; var17 <= var8; var17++) {
            if (var17 % 50 == 0) {
               this.DrawIsoLine(var17, var7, var17, var9, 1.0F, 0.0F, 0.0F, 0.5F, 1);
            }
         }
      }
   }

   private void drawCursor() {
      int var1 = this.m_playerIndex;
      int var2 = Core.TileScale;
      float var3 = this.m_z;
      int var4 = (int)IsoUtils.XToScreenExact(this.gridX, this.gridY + 1, var3, 0);
      int var5 = (int)IsoUtils.YToScreenExact(this.gridX, this.gridY + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var4, var5, var4 + 32 * var2, var5 - 16 * var2, var4 + 64 * var2, var5, var4 + 32 * var2, var5 + 16 * var2, 0.0F, 0.0F, 1.0F, 0.5F);
      IsoChunkMap var6 = IsoWorld.instance.getCell().ChunkMap[var1];

      for (int var7 = var6.getWorldYMinTiles(); var7 < var6.getWorldYMaxTiles(); var7++) {
         for (int var8 = var6.getWorldXMinTiles(); var8 < var6.getWorldXMaxTiles(); var8++) {
            IsoGridSquare var9 = IsoWorld.instance.getCell().getGridSquare(var8, var7, var3);
            if (var9 != null) {
               if (var9 != var6.getGridSquare(var8, var7, (int)var3)) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.8F);
               }

               if (var9 == null
                  || var9.getX() != var8
                  || var9.getY() != var7
                  || var9.getZ() != var3
                  || var9.e != null && var9.e.w != null && var9.e.w != var9
                  || var9.w != null && var9.w.e != null && var9.w.e != var9
                  || var9.n != null && var9.n.s != null && var9.n.s != var9
                  || var9.s != null && var9.s.n != null && var9.s.n != var9
                  || var9.nw != null && var9.nw.se != null && var9.nw.se != var9
                  || var9.se != null && var9.se.nw != null && var9.se.nw != var9) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
               }

               if (var9 != null) {
                  IsoGridSquare var10 = var9.testPathFindAdjacent(null, -1, 0, 0) ? null : var9.nav[IsoDirections.W.index()];
                  IsoGridSquare var11 = var9.testPathFindAdjacent(null, 0, -1, 0) ? null : var9.nav[IsoDirections.N.index()];
                  IsoGridSquare var12 = var9.testPathFindAdjacent(null, 1, 0, 0) ? null : var9.nav[IsoDirections.E.index()];
                  IsoGridSquare var13 = var9.testPathFindAdjacent(null, 0, 1, 0) ? null : var9.nav[IsoDirections.S.index()];
                  IsoGridSquare var14 = var9.testPathFindAdjacent(null, -1, -1, 0) ? null : var9.nav[IsoDirections.NW.index()];
                  IsoGridSquare var15 = var9.testPathFindAdjacent(null, 1, -1, 0) ? null : var9.nav[IsoDirections.NE.index()];
                  IsoGridSquare var16 = var9.testPathFindAdjacent(null, -1, 1, 0) ? null : var9.nav[IsoDirections.SW.index()];
                  IsoGridSquare var17 = var9.testPathFindAdjacent(null, 1, 1, 0) ? null : var9.nav[IsoDirections.SE.index()];
                  if (var10 != var9.w
                     || var11 != var9.n
                     || var12 != var9.e
                     || var13 != var9.s
                     || var14 != var9.nw
                     || var15 != var9.ne
                     || var16 != var9.sw
                     || var17 != var9.se) {
                     this.paintSquare(var8, var7, (int)var3, 1.0F, 0.0F, 0.0F, 0.5F);
                  }
               }

               if (var9 != null
                  && (
                     var9.nav[IsoDirections.NW.index()] != null && var9.nav[IsoDirections.NW.index()].nav[IsoDirections.SE.index()] != var9
                        || var9.nav[IsoDirections.NE.index()] != null && var9.nav[IsoDirections.NE.index()].nav[IsoDirections.SW.index()] != var9
                        || var9.nav[IsoDirections.SW.index()] != null && var9.nav[IsoDirections.SW.index()].nav[IsoDirections.NE.index()] != var9
                        || var9.nav[IsoDirections.SE.index()] != null && var9.nav[IsoDirections.SE.index()].nav[IsoDirections.NW.index()] != var9
                        || var9.nav[IsoDirections.N.index()] != null && var9.nav[IsoDirections.N.index()].nav[IsoDirections.S.index()] != var9
                        || var9.nav[IsoDirections.S.index()] != null && var9.nav[IsoDirections.S.index()].nav[IsoDirections.N.index()] != var9
                        || var9.nav[IsoDirections.W.index()] != null && var9.nav[IsoDirections.W.index()].nav[IsoDirections.E.index()] != var9
                        || var9.nav[IsoDirections.E.index()] != null && var9.nav[IsoDirections.E.index()].nav[IsoDirections.W.index()] != var9
                  )) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
               }

               if (this.EmptySquares.getValue() && var9.getObjects().isEmpty()) {
                  this.paintSquare(var8, var7, (int)var3, 1.0F, 1.0F, 0.0F, 0.5F);
               }

               if (var9.getRoom() != null && var9.isFree(false) && !VirtualZombieManager.instance.canSpawnAt(var8, var7, (int)var3)) {
                  this.paintSquare(var8, var7, (int)var3, 1.0F, 1.0F, 1.0F, 1.0F);
               }

               if (var9.roofHideBuilding != null) {
                  this.paintSquare(var8, var7, (int)var3, 0.0F, 0.0F, 1.0F, 0.25F);
               }
            }
         }
      }

      if (IsoCamera.CamCharacter.getCurrentSquare() != null
         && Math.abs(this.gridX - (int)IsoCamera.CamCharacter.x) <= 1
         && Math.abs(this.gridY - (int)IsoCamera.CamCharacter.y) <= 1) {
         IsoGridSquare var24 = IsoWorld.instance.CurrentCell.getGridSquare(this.gridX, this.gridY, this.m_z);
         IsoObject var25 = IsoCamera.CamCharacter.getCurrentSquare().testCollideSpecialObjects(var24);
         if (var25 != null) {
            var25.getSprite().RenderGhostTileRed((int)var25.getX(), (int)var25.getY(), (int)var25.getZ());
         }
      }

      if (this.LineClearCollide.getValue()) {
         this.lineClearCached(
            IsoWorld.instance.CurrentCell,
            this.gridX,
            this.gridY,
            (int)var3,
            (int)IsoCamera.CamCharacter.getX(),
            (int)IsoCamera.CamCharacter.getY(),
            this.m_z,
            false
         );
      }

      if (this.NearestWallsOpt.getValue()) {
         NearestWalls.render(this.gridX, this.gridY, this.m_z);
      }

      if (this.VehicleStory.getValue()) {
         this.drawVehicleStory();
      }
   }

   private void drawZones() {
      ArrayList var1 = IsoWorld.instance.MetaGrid.getZonesAt(this.gridX, this.gridY, this.m_z, new ArrayList());
      Zone var2 = null;

      for (int var3 = 0; var3 < var1.size(); var3++) {
         Zone var4 = (Zone)var1.get(var3);
         if (var4.isPreferredZoneForSquare) {
            var2 = var4;
         }

         if (!var4.isPolyline()) {
            if (!var4.points.isEmpty()) {
               for (byte var5 = 0; var5 < var4.points.size(); var5 += 2) {
                  int var6 = var4.points.get(var5);
                  int var7 = var4.points.get(var5 + 1);
                  int var8 = var4.points.get((var5 + 2) % var4.points.size());
                  int var9 = var4.points.get((var5 + 3) % var4.points.size());
                  this.DrawIsoLine(var6, var7, var8, var9, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            } else {
               this.DrawIsoLine(var4.x, var4.y, var4.x + var4.w, var4.y, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x, var4.y + var4.h, var4.x + var4.w, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x, var4.y, var4.x, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x + var4.w, var4.y, var4.x + var4.w, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }
         }
      }

      var1 = IsoWorld.instance.MetaGrid.getZonesIntersecting(this.gridX - 1, this.gridY - 1, this.m_z, 3, 3, new ArrayList());
      LiangBarsky var18 = new LiangBarsky();
      double[] var19 = new double[2];
      IsoChunk var20 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this.gridX, this.gridY, this.m_z);

      for (int var21 = 0; var21 < var1.size(); var21++) {
         Zone var23 = (Zone)var1.get(var21);
         if (var23 != null && var23.isPolyline() && !var23.points.isEmpty()) {
            for (byte var26 = 0; var26 < var23.points.size() - 2; var26 += 2) {
               int var29 = var23.points.get(var26);
               int var10 = var23.points.get(var26 + 1);
               int var11 = var23.points.get(var26 + 2);
               int var12 = var23.points.get(var26 + 3);
               this.DrawIsoLine(var29, var10, var11, var12, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               float var13 = var11 - var29;
               float var14 = var12 - var10;
               if (var20 != null
                  && var18.lineRectIntersect(var29, var10, var13, var14, var20.wx * 10, var20.wy * 10, var20.wx * 10 + 10, var20.wy * 10 + 10, var19)) {
                  this.DrawIsoLine(
                     var29 + (float)var19[0] * var13,
                     var10 + (float)var19[0] * var14,
                     var29 + (float)var19[1] * var13,
                     var10 + (float)var19[1] * var14,
                     0.0F,
                     1.0F,
                     0.0F,
                     1.0F,
                     1
                  );
               }
            }

            if (var23.polylineOutlinePoints != null) {
               float[] var27 = var23.polylineOutlinePoints;

               for (byte var30 = 0; var30 < var27.length; var30 += 2) {
                  float var32 = var27[var30];
                  float var34 = var27[var30 + 1];
                  float var38 = var27[(var30 + 2) % var27.length];
                  float var42 = var27[(var30 + 3) % var27.length];
                  this.DrawIsoLine(var32, var34, var38, var42, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            }
         }
      }

      VehicleZone var22 = IsoWorld.instance.MetaGrid.getVehicleZoneAt(this.gridX, this.gridY, this.m_z);
      if (var22 != null) {
         float var24 = 0.5F;
         float var28 = 1.0F;
         float var31 = 0.5F;
         float var33 = 1.0F;
         if (var22.isPolygon()) {
            for (byte var35 = 0; var35 < var22.points.size(); var35 += 2) {
               int var39 = var22.points.get(var35);
               int var43 = var22.points.get(var35 + 1);
               int var46 = var22.points.get((var35 + 2) % var22.points.size());
               int var15 = var22.points.get((var35 + 3) % var22.points.size());
               this.DrawIsoLine(var39, var43, var46, var15, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }
         } else if (var22.isPolyline()) {
            for (byte var36 = 0; var36 < var22.points.size() - 2; var36 += 2) {
               int var40 = var22.points.get(var36);
               int var44 = var22.points.get(var36 + 1);
               int var47 = var22.points.get(var36 + 2);
               int var49 = var22.points.get(var36 + 3);
               this.DrawIsoLine(var40, var44, var47, var49, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }

            if (var22.polylineOutlinePoints != null) {
               float[] var37 = var22.polylineOutlinePoints;

               for (byte var41 = 0; var41 < var37.length; var41 += 2) {
                  float var45 = var37[var41];
                  float var48 = var37[var41 + 1];
                  float var50 = var37[(var41 + 2) % var37.length];
                  float var16 = var37[(var41 + 3) % var37.length];
                  this.DrawIsoLine(var45, var48, var50, var16, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            }
         } else {
            this.DrawIsoLine(var22.x, var22.y, var22.x + var22.w, var22.y, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x, var22.y + var22.h, var22.x + var22.w, var22.y + var22.h, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x, var22.y, var22.x, var22.y + var22.h, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x + var22.w, var22.y, var22.x + var22.w, var22.y + var22.h, var24, var28, var31, var33, 1);
         }
      }

      if (this.RandomSquareInZone.getValue() && var2 != null) {
         IsoGridSquare var25 = var2.getRandomSquareInZone();
         if (var25 != null) {
            this.paintSquare(var25.x, var25.y, var25.z, 0.0F, 1.0F, 0.0F, 0.5F);
         }
      }
   }

   private void drawVehicleStory() {
      ArrayList var1 = IsoWorld.instance.MetaGrid.getZonesIntersecting(this.gridX - 1, this.gridY - 1, this.m_z, 3, 3, new ArrayList());
      if (!var1.isEmpty()) {
         IsoChunk var2 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this.gridX, this.gridY, this.m_z);
         if (var2 != null) {
            for (int var3 = 0; var3 < var1.size(); var3++) {
               Zone var4 = (Zone)var1.get(var3);
               if ("Nav".equals(var4.type)) {
                  VehicleStorySpawner var5 = VehicleStorySpawner.getInstance();
                  RandomizedVehicleStoryBase var6 = IsoWorld.instance.getRandomizedVehicleStoryByName(this.m_vehicleStory);
                  if (var6 != null && var6.isValid(var4, var2, true) && var6.initVehicleStorySpawner(var4, var2, true)) {
                     int var7 = var6.getMinZoneWidth();
                     int var8 = var6.getMinZoneHeight();
                     float[] var9 = new float[3];
                     if (var6.getSpawnPoint(var4, var2, var9)) {
                        float var10 = var9[0];
                        float var11 = var9[1];
                        float var12 = var9[2] + (float) (Math.PI / 2);
                        var5.spawn(var10, var11, 0.0F, var12, (var0, var1x) -> {});
                        var5.render(var10, var11, 0.0F, var7, var8, var9[2]);
                     }
                  }
               }
            }
         }
      }
   }

   private void DrawBehindStuff() {
      this.IsBehindStuff(IsoCamera.CamCharacter.getCurrentSquare());
   }

   private boolean IsBehindStuff(IsoGridSquare var1) {
      for (int var2 = 1; var2 < 8 && var1.getZ() + var2 < 8; var2++) {
         for (int var3 = -5; var3 <= 6; var3++) {
            for (int var4 = -5; var4 <= 6; var4++) {
               if (var4 >= var3 - 5 && var4 <= var3 + 5) {
                  this.paintSquare(var1.getX() + var4 + var2 * 3, var1.getY() + var3 + var2 * 3, var1.getZ() + var2, 1.0F, 1.0F, 0.0F, 0.25F);
               }
            }
         }
      }

      return true;
   }

   private boolean IsBehindStuffRecY(int var1, int var2, int var3) {
      IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
         return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecY(var1, var2 + 1, var3 + 1);
      }
   }

   private boolean IsBehindStuffRecXY(int var1, int var2, int var3, int var4) {
      IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
         return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecXY(var1 + var4, var2 + var4, var3 + 1, var4);
      }
   }

   private boolean IsBehindStuffRecX(int var1, int var2, int var3) {
      IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
         return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecX(var1 + 1, var2, var3 + 1);
      }
   }

   private void paintSquare(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      int var8 = Core.TileScale;
      int var9 = (int)IsoUtils.XToScreenExact(var1, var2 + 1, var3, 0);
      int var10 = (int)IsoUtils.YToScreenExact(var1, var2 + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var9, var10, var9 + 32 * var8, var10 - 16 * var8, var9 + 64 * var8, var10, var9 + 32 * var8, var10 + 16 * var8, var4, var5, var6, var7);
   }

   void drawModData() {
      int var1 = this.m_z;
      IsoGridSquare var2 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, var1);
      int var3 = Core.getInstance().getScreenWidth() - 250;
      int var4 = 10;
      int var5 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
      if (var2 != null && var2.getModData() != null) {
         KahluaTable var6 = var2.getModData();
         int var12;
         this.DrawString(var3, var12 = var4 + var5, "MOD DATA x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
         KahluaTableIterator var7 = var6.iterator();

         while (var7.advance()) {
            this.DrawString(var3, var12 += var5, var7.getKey().toString() + " = " + var7.getValue().toString());
            if (var7.getValue() instanceof KahluaTable) {
               KahluaTableIterator var8 = ((KahluaTable)var7.getValue()).iterator();

               while (var8.advance()) {
                  this.DrawString(var3 + 8, var12 += var5, var8.getKey().toString() + " = " + var8.getValue().toString());
               }
            }
         }

         var4 = var12 + var5;
      }

      if (var2 != null) {
         PropertyContainer var18 = var2.getProperties();
         ArrayList var20 = var18.getPropertyNames();
         if (!var20.isEmpty()) {
            this.DrawString(var3, var4 += var5, "PROPERTIES x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
            Collections.sort(var20);

            for (String var9 : var20) {
               this.DrawString(var3, var4 += var5, var9 + " = \"" + var18.Val(var9) + "\"");
            }
         }

         for (IsoFlagType var11 : IsoFlagType.values()) {
            if (var18.Is(var11)) {
               this.DrawString(var3, var4 += var5, var11.toString());
            }
         }
      }

      if (var2 != null) {
         Square var19 = var2.getErosionData();
         if (var19 != null) {
            var4 += var5;
            int var14;
            this.DrawString(var3, var14 = var4 + var5, "EROSION x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
            this.DrawString(var3, var4 = var14 + var5, "init=" + var19.init);
            int var16;
            this.DrawString(var3, var16 = var4 + var5, "doNothing=" + var19.doNothing);
            this.DrawString(var3, var4 = var16 + var5, "chunk.init=" + var2.chunk.getErosionData().init);
         }
      }
   }

   void drawPlayerInfo() {
      int var1 = Core.getInstance().getScreenWidth() - 250;
      int var2 = Core.getInstance().getScreenHeight() / 2;
      int var3 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
      IsoGameCharacter var4 = IsoCamera.CamCharacter;
      int var5;
      this.DrawString(var1, var5 = var2 + var3, "bored = " + var4.getBodyDamage().getBoredomLevel());
      this.DrawString(var1, var2 = var5 + var3, "endurance = " + var4.getStats().endurance);
      int var7;
      this.DrawString(var1, var7 = var2 + var3, "fatigue = " + var4.getStats().fatigue);
      this.DrawString(var1, var2 = var7 + var3, "hunger = " + var4.getStats().hunger);
      int var9;
      this.DrawString(var1, var9 = var2 + var3, "pain = " + var4.getStats().Pain);
      this.DrawString(var1, var2 = var9 + var3, "panic = " + var4.getStats().Panic);
      int var11;
      this.DrawString(var1, var11 = var2 + var3, "stress = " + var4.getStats().getStress());
      this.DrawString(var1, var2 = var11 + var3, "clothingTemp = " + ((IsoPlayer)var4).getPlayerClothingTemperature());
      int var13;
      this.DrawString(var1, var13 = var2 + var3, "temperature = " + var4.getTemperature());
      this.DrawString(var1, var2 = var13 + var3, "thirst = " + var4.getStats().thirst);
      int var15;
      this.DrawString(var1, var15 = var2 + var3, "foodPoison = " + var4.getBodyDamage().getFoodSicknessLevel());
      this.DrawString(var1, var2 = var15 + var3, "poison = " + var4.getBodyDamage().getPoisonLevel());
      int var17;
      this.DrawString(var1, var17 = var2 + var3, "unhappy = " + var4.getBodyDamage().getUnhappynessLevel());
      this.DrawString(var1, var2 = var17 + var3, "infected = " + var4.getBodyDamage().isInfected());
      int var19;
      this.DrawString(var1, var19 = var2 + var3, "InfectionLevel = " + var4.getBodyDamage().getInfectionLevel());
      this.DrawString(var1, var2 = var19 + var3, "FakeInfectionLevel = " + var4.getBodyDamage().getFakeInfectionLevel());
      var2 += var3;
      int var22;
      this.DrawString(var1, var22 = var2 + var3, "WORLD");
      this.DrawString(var1, var2 = var22 + var3, "globalTemperature = " + IsoWorld.instance.getGlobalTemperature());
   }

   public TestResults lineClearCached(IsoCell var1, int var2, int var3, int var4, int var5, int var6, int var7, boolean var8) {
      int var12 = var3 - var6;
      int var13 = var2 - var5;
      int var14 = var4 - var7;
      int var15 = var13 + 100;
      int var16 = var12 + 100;
      int var17 = var14 + 16;
      if (var15 >= 0 && var16 >= 0 && var17 >= 0 && var15 < 200 && var16 < 200) {
         TestResults var18 = TestResults.Clear;
         byte var19 = 1;
         float var20 = 0.5F;
         float var21 = 0.5F;
         IsoGridSquare var25 = var1.getGridSquare(var5, var6, var7);
         if (Math.abs(var13) > Math.abs(var12) && Math.abs(var13) > Math.abs(var14)) {
            float var44 = (float)var12 / var13;
            float var49 = (float)var14 / var13;
            var20 += var6;
            var21 += var7;
            var13 = var13 < 0 ? -1 : 1;
            var44 *= var13;
            var49 *= var13;

            while (var5 != var2) {
               var5 += var13;
               var20 += var44;
               var21 += var49;
               IsoGridSquare var52 = var1.getGridSquare(var5, (int)var20, (int)var21);
               this.paintSquare(var5, (int)var20, (int)var21, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var52 != null
                  && var25 != null
                  && var52.testVisionAdjacent(var25.getX() - var52.getX(), var25.getY() - var52.getY(), var25.getZ() - var52.getZ(), true, var8)
                     == TestResults.Blocked) {
                  this.paintSquare(var5, (int)var20, (int)var21, 1.0F, 0.0F, 0.0F, 0.5F);
                  this.paintSquare(var25.getX(), var25.getY(), var25.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
                  var19 = 4;
               }

               var25 = var52;
               int var39 = (int)var20;
               int var40 = (int)var21;
            }
         } else if (Math.abs(var12) >= Math.abs(var13) && Math.abs(var12) > Math.abs(var14)) {
            float var42 = (float)var13 / var12;
            float var47 = (float)var14 / var12;
            var20 += var5;
            var21 += var7;
            var12 = var12 < 0 ? -1 : 1;
            var42 *= var12;
            var47 *= var12;

            while (var6 != var3) {
               var6 += var12;
               var20 += var42;
               var21 += var47;
               IsoGridSquare var51 = var1.getGridSquare((int)var20, var6, (int)var21);
               this.paintSquare((int)var20, var6, (int)var21, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var51 != null
                  && var25 != null
                  && var51.testVisionAdjacent(var25.getX() - var51.getX(), var25.getY() - var51.getY(), var25.getZ() - var51.getZ(), true, var8)
                     == TestResults.Blocked) {
                  this.paintSquare((int)var20, var6, (int)var21, 1.0F, 0.0F, 0.0F, 0.5F);
                  this.paintSquare(var25.getX(), var25.getY(), var25.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
                  var19 = 4;
               }

               var25 = var51;
               int var38 = (int)var20;
               int var24 = (int)var21;
            }
         } else {
            float var26 = (float)var13 / var14;
            float var27 = (float)var12 / var14;
            var20 += var5;
            var21 += var6;
            var14 = var14 < 0 ? -1 : 1;
            var26 *= var14;
            var27 *= var14;

            while (var7 != var4) {
               var7 += var14;
               var20 += var26;
               var21 += var27;
               IsoGridSquare var28 = var1.getGridSquare((int)var20, (int)var21, var7);
               this.paintSquare((int)var20, (int)var21, var7, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var28 != null
                  && var25 != null
                  && var28.testVisionAdjacent(var25.getX() - var28.getX(), var25.getY() - var28.getY(), var25.getZ() - var28.getZ(), true, var8)
                     == TestResults.Blocked) {
                  var19 = 4;
               }

               var25 = var28;
               int var22 = (int)var20;
               int var23 = (int)var21;
            }
         }

         if (var19 == 1) {
            return TestResults.Clear;
         } else if (var19 == 2) {
            return TestResults.ClearThroughOpenDoor;
         } else if (var19 == 3) {
            return TestResults.ClearThroughWindow;
         } else {
            return var19 == 4 ? TestResults.Blocked : TestResults.Blocked;
         }
      } else {
         return TestResults.Blocked;
      }
   }

   private void DrawString(int var1, int var2, String var3) {
      int var4 = TextManager.instance.MeasureStringX(this.FONT, var3);
      int var5 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
      SpriteRenderer.instance.renderi(null, var1 - 1, var2, var4 + 2, var5, 0.0F, 0.0F, 0.0F, 0.8F, null);
      TextManager.instance.DrawString(this.FONT, var1, var2, var3, 1.0, 1.0, 1.0, 1.0);
   }

   public ConfigOption getOptionByName(String var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
         ConfigOption var3 = this.options.get(var2);
         if (var3.getName().equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int getOptionCount() {
      return this.options.size();
   }

   public ConfigOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

   public void setBoolean(String var1, boolean var2) {
      ConfigOption var3 = this.getOptionByName(var1);
      if (var3 instanceof BooleanConfigOption) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

   public boolean getBoolean(String var1) {
      ConfigOption var2 = this.getOptionByName(var1);
      return var2 instanceof BooleanConfigOption ? ((BooleanConfigOption)var2).getValue() : false;
   }

   public void save() {
      String var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
      ConfigFile var2 = new ConfigFile();
      var2.write(var1, 1, this.options);
   }

   public void load() {
      String var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
      ConfigFile var2 = new ConfigFile();
      if (var2.read(var1)) {
         for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
            ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
            ConfigOption var5 = this.getOptionByName(var4.getName());
            if (var5 != null) {
               var5.parse(var4.getValueAsString());
            }
         }
      }
   }
}
