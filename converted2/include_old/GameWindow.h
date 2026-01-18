#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   GameWindow.java
namespace zombie {
#include "Container.h"
#include <fstream>
#include <iostream>
#include "net.h"
#include "ByteBuffer.h"
#include <vector>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "swing.h"
#include "Sys.h"
#include "Keyboard.h"
#include "AL.h"
#include "opengl.h"
#include "LuaEventManager.h"
#include "LuaManager.h"
#include "ProfessionFactory.h"
#include "PerkFactory.h"
#include "TraitFactory.h"
#include "Core.h"
#include "Rand.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "SoundEngine.h"
#include "AuthenticatingFrame.h"
#include "Texture.h"
#include "TextureID.h"
#include "TexturePackPage.h"
#include "LineDrawer.h"
#include "CharacterCreationState.h"
#include "GameLoadingState.h"
#include "GameStateMachine.h"
#include "IngameState.h"
#include "LoadGamePopupState.h"
#include "LoginState.h"
#include "MainScreenState.h"
#include "Mouse.h"
#include "IsoCell.h"
#include "IsoObjectPicker.h"
#include "IsoWorld.h"
#include "Vector2.h"
#include "SoundStore.h"
#include "ScriptManager.h"
#include "PZConsole.h"
#include "SpeedControls.h"
#include "TextManager.h"
#include "UIManager.h"
// Referenced classes of package zombie:
//            GameApplet, FrameLoader, IndieLogger, SoundManager, 
//            ZomboidGlobals, GameTime
class GameWindow {
public:
{
    public GameWindow()
    {
    }
    public static void DrawDebugLine(int x1, int x2, int y1, int y2)
    {
        debugLine.addLine(x1, y1, x2, y2, 255, 0, 0, "test");
    }
    public static void initApplet()
        throws Exception
    {
        Vector2 temp = new Vector2();
        temp.x = 0.5F;
        temp.y = 1.0F;
        temp.normalize();
        float len = temp.getLength();
        float half = temp.x / 2.0F;
        initShared();
    }
    public static void initShared()
        throws Exception
    {
        std::string path = (new StringBuilder()).append(getCacheDir()).append(File.separator).toString();
        File file = new File(path);
        if(!file.exists())
            file.mkdirs();
        path = (new StringBuilder()).append(path).append("2133243254543.log").toString();
        path = path;
        FrameLoader.makefile = new File(path);
        try
        {
            SwingUtilities.invokeAndWait(new Runnable() {
                public void run()
                {
                    GameWindow.login();
                }
            }
);
        }
        catch(Exception ex) { }
        TexturePackPage.getPackPage("ui");
        TexturePackPage.getPackPage("inventory");
        try
        {
            ScriptManager.instance.LoadDirPP("scripts/", true);
            ScriptManager.instance.LoadDir("scripts/", true);
            ScriptManager.instance.LoadDirPP("scripts/", false);
            ScriptManager.instance.LoadDir("scripts/", false);
        }
        catch(Exception ex)
        {
            JOptionPane.showMessageDialog(nullptr, ex.getStackTrace(), ex.getMessage(), 0);
            Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        IndieLogger.init();
        IndieLogger.Log("PZ Debug Logging started");
        TraitFactory.init();
        ProfessionFactory.init();
        PerkFactory.init();
        Rand.init();
        TexturePackPage.getPackPage("ui");
        TexturePackPage.getPackPage("inventory");
        TextManager.instance.Init();
        IndieLogger.Log("Initialised TextManager");
        System.gc();
        MousePointer = Texture.getSharedTexture("media/ui/mouseArrow.png");
        states.States.add(new LoginState());
        states.States.add(new MainScreenState());
        states.LoopToState = 1;
        states.States.add(new LoadGamePopupState());
        states.States.add(new GameLoadingState());
        states.States.add(new IngameState());
        GameInput.initControllers();
        int counta = GameInput.getControllerCount();
        for(int m = 0; m < counta; m++)
        {
            int count = GameInput.getAxisCount(m);
            if(count <= 1)
                continue;
            ActiveController = m;
            for(int n = 0; n < count; n++)
            {
                std::string name = GameInput.getAxisName(m, n);
                if(name == "X Axis"))
                    XLAxis = n;
                if(name == "Y Axis"))
                    YLAxis = n;
                if(name == "X Rotation"))
                    XRAxis = n;
                if(name == "Y Rotation"))
                    YRAxis = n;
            }
        }
        GL11.glTexParameteri(3553, 10241, 9728);
        GL11.glTexParameteri(3553, 10240, 9728);
        TextureID.UseFiltering = false;
        Texture.getSharedTexture("media/white.png");
        TextureID.UseFiltering = true;
        SpriteRenderer.instance = new SpriteRenderer();
        SpriteRenderer.instance.create();
        int fdsf = 0;
    }
    public static void logic()
    {
        if(SoundEngine.isCreated())
            SoundEngine.tick();
        Mouse.loop();
        debugLine.clear();
        UIManager.update();
        if(ActiveController != -1 && GameInput.isButtonPressed(0, ActiveController))
            ActivatedJoyPad = true;
        SoundManager.instance.Update();
        bool DoUpdate = true;
        if(UIManager.getSpeedControls() != nullptr && UIManager.getSpeedControls().getCurrentGameSpeed() == 0)
            DoUpdate = false;
        if(DoUpdate)
            states.update();
        UIManager.resize();
        if(PauseKeyDebounce == 0)
        {
            if(!PZConsole.instance.isVisible() && Keyboard.isKeyDown(25))
            {
                if(UIManager.getSpeedControls() != nullptr)
                    if(UIManager.getSpeedControls().getCurrentGameSpeed() == 0)
                        UIManager.getSpeedControls().SetCurrentGameSpeed(4);
                    else
                        UIManager.getSpeedControls().SetCurrentGameSpeed(0);
                PauseKeyDebounce = 20;
            }
        } else
        {
            PauseKeyDebounce--;
        }
    }
    public static void render()
    {
        IsoObjectPicker.Instance.StartRender();
        states.render();
    }
    public static void main(std::string args[])
        throws Exception
    {
        LuaManager.init();
        LuaManager.LoadDirBase("media/lua/");
        ZomboidGlobals.Load();
        SoundStore.get().init();
        std::string server = System.getProperty("server");
        std::string client = System.getProperty("client");
        std::string f = System.getProperty("fullscreen");
        std::string debug = System.getProperty("debug");
        std::string xres = System.getProperty("xres");
        std::string yres = System.getProperty("yres");
        if(f != nullptr)
            FrameLoader.bFullscreen = true;
        if(debug != nullptr)
            Core.bDebug = true;
        if(xres != nullptr)
            FrameLoader.FullX = Integer.parseInt(xres);
        if(yres != nullptr)
            FrameLoader.FullY = Integer.parseInt(yres);
        std::string graphiclevel = System.getProperty("graphiclevel");
        if(graphiclevel != nullptr)
            Core.getInstance().nGraphicLevel = Integer.parseInt(graphiclevel);
        if(server != nullptr && server == "true"))
            FrameLoader.bServer = true;
        if(client != nullptr)
        {
            FrameLoader.bClient = true;
            FrameLoader.IP = client;
        }
        if(!FrameLoader.bServer);
        try
        {
            System.setProperty("org.lwjgl.input.Mouse.allowNegativeMouseCoords", "true");
            System.setProperty("sun.java2d.noddraw", "true");
            System.setProperty("sun.java2d.opengl", "false");
            System.setProperty("sun.java2d.d3d", "false");
            System.setProperty("sun.java2d.pmoffscreen", "false");
            System.setProperty("sun.awt.noerasebackground", "true");
        }
        catch(Throwable ignored) { }
        int desktopWidth = Display.getDesktopDisplayMode().getWidth();
        int desktopHeight = Display.getDesktopDisplayMode().getHeight();
        Preferences prefs = Preferences.userNodeForPackage(FrameLoader.class);
        Display.setResizable(true);
        init(false);
        run();
        System.exit(0);
    }
    public static void main(bool fullscreen, int xres, int yres, int graphiclevel)
        throws Exception
    {
        LuaManager.init();
        LuaManager.LoadDirBase("media/lua/");
        ZomboidGlobals.Load();
        SoundStore.get().init();
        Core.getInstance().nGraphicLevel = graphiclevel;
        std::string server = System.getProperty("server");
        std::string client = System.getProperty("client");
        std::string debug = System.getProperty("debug");
        FrameLoader.bFullscreen = fullscreen;
        if(debug != nullptr)
            Core.bDebug = true;
        FrameLoader.FullX = xres;
        FrameLoader.FullY = yres;
        if(server != nullptr && server == "true"))
            FrameLoader.bServer = true;
        if(client != nullptr)
        {
            FrameLoader.bClient = true;
            FrameLoader.IP = client;
        }
        if(!FrameLoader.bServer);
        try
        {
            System.setProperty("org.lwjgl.input.Mouse.allowNegativeMouseCoords", "true");
            System.setProperty("sun.java2d.noddraw", "true");
            System.setProperty("sun.java2d.opengl", "false");
            System.setProperty("sun.java2d.d3d", "false");
            System.setProperty("sun.java2d.pmoffscreen", "false");
            System.setProperty("sun.awt.noerasebackground", "true");
        }
        catch(Throwable ignored) { }
        int desktopWidth = Display.getDesktopDisplayMode().getWidth();
        int desktopHeight = Display.getDesktopDisplayMode().getHeight();
        Preferences prefs = Preferences.userNodeForPackage(FrameLoader.class);
        Display.setResizable(true);
        init(false);
        run();
        System.exit(0);
    }
    public static long getTime()
    {
        return (Sys.getTime() * 1000L) / Sys.getTimerResolution();
    }
    public int getDelta()
    {
        long time = getTime();
        int delta = (int)(time - lastFrame);
        lastFrame = time;
        return delta;
    }
    public static void start()
    {
        lastFPS = getTime();
    }
    public static void updateFPS()
    {
        long dif = getTime() - last;
        last = getTime();
        float dif2 = 1000F / (float)dif;
        last10[last10index++] = (long)dif2;
        if(last10index >= 10)
            last10index = 0;
        average10 = 0.0F;
        int div = 0;
        float lowest = 11110F;
        float hightest = -11110F;
        for(int n = 0; n < 10; n++)
        {
            if(last10[n] == 0.0F || last10[n] <= 1.0F)
                continue;
            div++;
            average10 += last10[n];
            if(last10[n] < lowest)
                lowest = last10[n];
            if(last10[n] > hightest)
                hightest = last10[n];
        }
        if(div > 0)
            average10 /= div;
        else
            average10 = 60F;
        GameTime.instance.FPSMultiplier = 60F / average10;
        if(getTime() - lastFPS > 1000L)
        {
            fps = 0L;
            lastFPS += 1000L;
        }
        fps++;
    }
    public static void run()
    {
    	/*  640 */     LuaEventManager.TriggerEvent("OnGameBoot");
    	/*      */     try {
    	/*  642 */       initApplet();
    	/*      */     } catch (Exception ex) {
    	/*  644 */       Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, null, ex);
    	/*      */     }
    	/*  646 */     start();
    	/*      */     while (  (!Display.isCloseRequested()) && (!closeRequested)    ) {
    	/*      */         try
    	/*      */         {
    	/*  658 */           Display.update();
    	/*      */ 
    	/*  665 */           logic();
    	/*  666 */           updateFPS();
    	/*      */ 
    	/*  669 */           Core.getInstance().setScreenSize(Display.getWidth(), Display.getHeight());
    	/*      */ 
    	/*  673 */           render();
    	/*      */ 
    	/*  678 */           Display.sync(60);
    	/*      */         }
    	/*      */         catch (Exception ex)
    	/*      */         {
    	/*  703 */           JOptionPane.showMessageDialog(null, ex.getStackTrace(), "Error: " + ex.getMessage(), 0);
    	/*  704 */           Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, null, ex);
    	/*      */         }
    	/*      */       
    	/*      */     }
    	/*      */ 
    	/*      */     try
    	/*      */     {
    	/*  711 */       save(true);
    	/*      */     } catch (FileNotFoundException ex) {
    	/*  713 */       Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, null, ex);
    	/*      */     } catch (IOException ex) {
    	/*  715 */       Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, null, ex);
    	/*      */     }
    	/*      */ 
    	/*  718 */     Display.destroy();
    	/*      */ 
    	/*  720 */     System.exit(0);
    }
    private static void cleanup()
    {
        Display.destroy();
        AL.destroy();
    }
    private static void init(bool fullscreen)
        throws Exception
    {
        Display.setResizable(true);
        Display.setTitle("Project Zomboid");
        Display.setFullscreen(fullscreen);
        Core.getInstance().init(FrameLoader.FullX, FrameLoader.FullY);
        std::string path = (new StringBuilder()).append(getCacheDir()).append(File.separator).toString();
        File file = new File(path);
        if(!file.exists())
            file.mkdirs();
        path = (new StringBuilder()).append(path).append("2133243254543.log").toString();
        path = path;
        File makefile = new File(path);
        try
        {
            SwingUtilities.invokeAndWait(new Runnable() {
                public void run()
                {
                    GameWindow.login();
                }
            }
);
        }
        catch(Exception ex) { }
    }
    public static void save(bool bDoChars)
        throws FileNotFoundException, IOException
    {
        LuaEventManager.TriggerEvent("OnSave");
        if(IsoWorld.instance.CurrentCell == nullptr)
            return;
        if(DoFrame)
        {
            Core.getInstance().StartFrame();
            IsoWorld.instance.render();
            Core.getInstance().EndFrame();
            Core.getInstance().StartFrameUI();
            TextManager.instance.DrawStringCentre(Core.getInstance().getOffscreenWidth() / 2, Core.getInstance().getOffscreenHeight() / 2, "Saving", 1.0F, 1.0F, 1.0F, 1.0F);
            Core.getInstance().EndFrameUI();
            Display.update();
        }
        try
        {
            File outFile = new File((new StringBuilder()).append(getGameModeCacheDir()).append(File.separator).append(IsoWorld.instance.playerCell).append("map.bin").toString());
            FileOutputStream outStream = new FileOutputStream(outFile);
            DataOutputStream output = new DataOutputStream(outStream);
            IsoWorld.instance.CurrentCell.save(output, bDoChars);
            outStream.close();
        }
        catch(Exception ex)
        {
            Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        try
        {
            File outFile = new File((new StringBuilder()).append(getGameModeCacheDir()).append(File.separator).append("pc.bin").toString());
            FileOutputStream outStream = new FileOutputStream(outFile);
            DataOutputStream output = new DataOutputStream(outStream);
            output.writeInt(IsoWorld.instance.x);
            output.writeInt(IsoWorld.instance.y);
            WriteString(output, IsoWorld.instance.playerCell);
            outStream.close();
        }
        catch(Exception ex)
        {
            Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
    }
    static void login()
    {
        AuthenticatingFrame f;
        if(FrameLoader.makefile.exists())
        {
            FileInputStream dis = nullptr;
            try
            {
                dis = new FileInputStream(FrameLoader.makefile);
            }
            catch(FileNotFoundException ex)
            {
                Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
            DataInputStream in = new DataInputStream(dis);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            try
            {
                std::string inputLine = nullptr;
                do
                {
                    if((inputLine = br.readLine()) == nullptr)
                        break;
                    if(inputLine.contains("username:"))
                    {
                        inputLine = inputLine.replace("username:", "");
                        lastU = inputLine;
                    }
                    if(inputLine.contains("password:"))
                    {
                        inputLine = inputLine.replace("password:", "");
                        lastP = inputLine;
                    }
                    if(inputLine.contains("key:"))
                    {
                        inputLine = inputLine.replace("key:", "");
                        lastK = inputLine;
                    }
                } while(true);
            }
            catch(IOException ex)
            {
                Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
            f = new AuthenticatingFrame(lastU, lastP, lastK) {
                public bool allow(std::string username, char pw[], std::string key)
                {
                    try
                    {
                        return GameWindow.validateUser(username, new std::string(pw), key);
                    }
                    catch(MalformedURLException ex)
                    {
                        Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    catch(IOException ex)
                    {
                        Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    return false;
                }
            }
;
        } else
        {
            f = new AuthenticatingFrame() {
                public bool allow(std::string username, char pw[], std::string key)
                {
                    try
                    {
                        return GameWindow.validateUser(username, new std::string(pw), key);
                    }
                    catch(MalformedURLException ex)
                    {
                        Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    catch(IOException ex)
                    {
                        Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    return false;
                }
            }
;
        }
        f.setGui();
        f.getContentPane().add(new JLabel("n!"));
        f.pack();
        f.setVisible(true);
        f.setAlwaysOnTop(true);
        f.setLocationRelativeTo(FrameLoader.canvas);
    }
    private static bool validateUser(std::string usr, std::string pwd, std::string key)
        throws MalformedURLException, IOException
    {
label0:
        {
            std::string str = nullptr;
            BufferedReader in;
            try
            {
                URL yahoo = new URL("http://127.0.0.1/external/games/projectzomboid.php");
                URLConnection yc2 = yahoo.openConnection();
                InputStream strw = yc2.getInputStream();
                byte b[] = new byte[7];
                strw.read(b);
                if(b[0] != 115 || b[1] != 117 || b[2] != 99 || b[3] != 99 || b[4] != 101)
                    throw new NullPointerException(str);
                strw.close();
                break label0;
            }
            catch(Exception ex)
            {
                if(usr != nullptr && !usr.isEmpty())
                    str = (new StringBuilder()).append("http://www.desura.com/external/games/projectzomboid.php?username=").append(usr).append("&password=").append(pwd).toString();
                else
                    str = (new StringBuilder()).append("http://www.desura.com/external/games/projectzomboid.php?cdkey=").append(key).toString();
                URL yahoo = new URL(str);
                URLConnection yc = yahoo.openConnection();
                in = new BufferedReader(new InputStreamReader(yc.getInputStream()));
            }
            std::string inputLine;
            do
                if((inputLine = in.readLine()) == nullptr)
                    break label0;
            while(!inputLine.contains("success"));
            return true;
        }
        return false;
    }
    public static std::string getCacheDir()
    {
        std::string cacheDir = System.getProperty("deployment.user.cachedir");
        if(cacheDir == nullptr || System.getProperty("os.name").startsWith("Win"))
            cacheDir = System.getProperty("user.home");
        return (new StringBuilder()).append(cacheDir).append(File.separator).append("Zomboid").toString();
    }
    public static void WriteString(ByteBuffer output, std::string str)
    {
        if(str == nullptr)
        {
            output.putInt(0);
            return;
        }
        output.putInt(str.length());
        if(str != nullptr && str.length() >= 0)
        {
            for(int n = 0; n < str.length(); n++)
                output.putChar(str.charAt(n));
        }
    }
    public static void WriteString(DataOutputStream output, std::string str)
        throws IOException
    {
        if(str == nullptr)
        {
            output.writeInt(0);
            return;
        }
        output.writeInt(str.length());
        if(str != nullptr && str.length() >= 0)
            output.writeChars(str);
    }
    public static std::string ReadString(ByteBuffer input)
    {
        int len = input.getInt();
        if(len == 0)
            return "";
        std::string className = "";
        for(int n = 0; n < len; n++)
            className = (new StringBuilder()).append(className).append(input.getChar()).toString();
        return className;
    }
    public static std::string ReadString(DataInputStream input)
        throws IOException
    {
        int len = input.readInt();
        if(len == 0)
            return "";
        std::string className = "";
        for(int n = 0; n < len; n++)
            className = (new StringBuilder()).append(className).append(input.readChar()).toString();
        return className;
    }
    public static std::string getGameModeCacheDir()
    {
        std::string cacheDir = System.getProperty("deployment.user.cachedir");
        if(cacheDir == nullptr || System.getProperty("os.name").startsWith("Win"))
            cacheDir = System.getProperty("user.home");
        return (new StringBuilder()).append(cacheDir).append(File.separator).append("Zomboid").append(File.separator).append(Core.GameMode).toString();
    }
    public static Input GameInput = new Input(1);
    static int PauseKeyDebounce = 0;
    public static int ActiveController = -1;
    public static int XLAxis = 0;
    public static int YLAxis = 0;
    public static int XRAxis = 0;
    public static int YRAxis = 0;
    private static final int FRAMERATE = 30;
    public static std::string lastU = nullptr;
    public static std::string lastP = nullptr;
    public static std::string lastK = nullptr;
    public static final std::string GAME_TITLE = "Project Zomboid";
    public static GameStateMachine states = new GameStateMachine();
    public static CharacterCreationState CharacterCreationStateHandle = nullptr;
    public static LineDrawer debugLine = new LineDrawer();
    public static bool bDrawMouse = true;
    static Texture MousePointer;
    private static bool finished;
    static bool keyDown;
    public static bool ActivatedJoyPad = false;
    public static bool DoFrame = true;
    public static std::string version = "0.2.0q";
    public static SoundEngine SoundEngine = new SoundEngine();
    static long lastFrame = 0L;
    static long lastFPS = 0L;
    public static float average10 = 0.0F;
    static float total10 = 0.0F;
    static float last10[] = new float[100];
    static int last10index = 0;
    static long fps = 0L;
    static long last = 0L;
    public static volatile bool closeRequested;
}} // namespace
