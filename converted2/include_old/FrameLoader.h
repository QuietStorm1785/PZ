#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:44
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   FrameLoader.java
namespace zombie {
#include "Canvas.h"
#include "Cursor.h"
#include "Dimension.h"
#include "Frame.h"
#include "ComponentAdapter.h"
#include "ComponentEvent.h"
#include "WindowAdapter.h"
#include "WindowEvent.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "JOptionPane.h"
#include "SwingUtilities.h"
#include "LWJGLException.h"
#include "LWJGLUtil.h"
#include "Display.h"
#include "DisplayMode.h"
#include "LuaEventManager.h"
#include "LuaManager.h"
#include "Core.h"
#include "MainScreenState.h"
#include "GameServer.h"
#include "SoundStore.h"
// Referenced classes of package zombie:
//            GameApplet, GameWindow, ZomboidGlobals
class FrameLoader : public Frame {
public:
{
    public FrameLoader()
    {
        super((new StringBuilder()).append("Project Zomboid Alpha ").append(MainScreenState.Version).toString());
        canvas = new Canvas();
        canvas.addComponentListener(new ComponentAdapter() {
            public void componentResized(ComponentEvent e)
            {
                newCanvasSize.set(FrameLoader.canvas.getSize());
            }
        }
);
        add(canvas, "Center");
        std::string path = (new StringBuilder()).append(GameWindow.getCacheDir()).append(File.separator).toString();
        File file = new File(path);
        if(!file.exists())
            file.mkdirs();
        path = (new StringBuilder()).append(path).append("2133243254543.log").toString();
        path = path;
        makefile = new File(path);
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
        if(LWJGLUtil.getPlatform() == 3)
            addWindowFocusListener(new WindowAdapter() {
                public void windowGainedFocus(WindowEvent e)
                {
                    FrameLoader.canvas.requestFocusInWindow();
                }
            }
);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e)
            {
                FrameLoader.closeRequested = true;
            }
        }
);
        setIgnoreRepaint(true);
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
            bFullscreen = true;
        if(debug != nullptr)
            Core.bDebug = true;
        if(xres != nullptr)
            FullX = Integer.parseInt(xres);
        if(yres != nullptr)
            FullY = Integer.parseInt(yres);
        std::string graphiclevel = System.getProperty("graphiclevel");
        if(graphiclevel != nullptr)
            Core.getInstance().nGraphicLevel = Integer.parseInt(graphiclevel);
        if(server != nullptr && server == "true"))
            bServer = true;
        if(client != nullptr)
        {
            bClient = true;
            IP = client;
        }
        if(!bServer);
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
        final Preferences prefs = Preferences.userNodeForPackage(FrameLoader.class);
        int width = Math.max(400, Math.min(desktopWidth, prefs.getInt("mainwindow.width", (desktopWidth * 4) / 5)));
        int height = Math.max(300, Math.min(desktopHeight, prefs.getInt("mainwindow.height", (desktopHeight * 4) / 5)));
        final FrameLoader main = new FrameLoader();
        main.setSize(width, height);
        std::string strX = prefs.get("mainwindow.x", nullptr);
        std::string strY = prefs.get("mainwindow.y", nullptr);
        if(strX != nullptr && strY != nullptr)
            try
            {
                int x = Math.max(0, Math.min(desktopWidth - width, Integer.parseInt(strX)));
                int y = Math.max(0, Math.min(desktopHeight - height, Integer.parseInt(strY)));
                main.setLocation(x, y);
            }
            catch(Throwable ex)
            {
                main.setLocationRelativeTo(nullptr);
            }
        else
            main.setLocationRelativeTo(nullptr);
        main.addComponentListener(
        		new ComponentAdapter() {
            public void componentResized(ComponentEvent e)
            {
                prefs.putInt("mainwindow.width", main.getWidth());
                prefs.putInt("mainwindow.height", main.getHeight());
            }
            public void componentMoved(ComponentEvent e)
            {
                prefs.putInt("mainwindow.x", main.getX());
                prefs.putInt("mainwindow.y", main.getY());
            }});
        cur = Cursor.getPredefinedCursor(0);
        main.setVisible(true);
        main.run();
        main.dispose();
        System.exit(0);
    }
    void run()
    {
    	try
    	/*     */     {
    	/* 291 */       bool usesSWGL = false;
    	/*     */ 
    	/* 293 */       canvas.setIgnoreRepaint(true);
    	/*     */ 
    	/* 295 */       if (!bFullscreen) {
    	/* 296 */         Display.setParent(canvas);
    	/*     */       }
    	/*     */ 
    	/* 299 */       if (!bServer) {
    	/*     */         try
    	/*     */         {
    	/* 302 */           if (bFullscreen)
    	/* 303 */             Core.getInstance().init(FullX, FullY);
    	/*     */           else {
    	/* 305 */             Core.getInstance().init(canvas.getWidth(), canvas.getHeight());
    	/*     */           }
    	/*     */         }
    	/*     */         catch (LWJGLException ex)
    	/*     */         {
    	/* 310 */           if (ex.getMessage().equals("Pixel format not accelerated")) {
    	/*     */             try {
    	/* 312 */               System.setProperty("org.lwjgl.opengl.Display.allowSoftwareOpenGL", "true");
    	/* 313 */               Core.getInstance().init(canvas.getWidth(), canvas.getHeight());
    	/* 314 */               usesSWGL = true;
    	/*     */             } catch (LWJGLException ex2) {
    	/* 316 */               throw ex2;
    	/*     */             }
    	/*     */             catch (SecurityException ex2) {
    	/* 319 */               throw ex;
    	/*     */             }
    	/*     */           }
    	/*     */           else {
    	/* 323 */             throw ex;
    	/*     */           }
    	/*     */ 
    	/*     */         }
    	/*     */ 
    	/*     */       }
    	/*     */ 
    	/* 330 */       if (!bServer)
    	/*     */       {
    	/* 332 */         GameWindow.initApplet();
    	/*     */       }
    	/*     */ 
    	/*     */     }
    	/*     */     catch (Exception ex)
    	/*     */     {
    	/* 338 */       Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, null, ex);
    	/*     */     }
    	/*     */ 
    	/* 341 */     if (bServer)
    	/*     */     {
    	/* 343 */       GameServer.instance.run();
    	/* 344 */       System.exit(0);
    	/* 345 */       return;
    	/*     */     }
    	/*     */ 
    	/* 348 */     LuaEventManager.TriggerEvent("OnGameBoot");
    	/*     */     while ((!Display.isCloseRequested()) && (!closeRequested))
    	/*     */     {
    	/* 352 */      
    	/*     */         try
    	/*     */         {
    	/* 362 */           setCursor(cur);
    	/*     */ 
    	/* 364 */           Dimension newDim = (Dimension)this.newCanvasSize.getAndSet(null);
    	/* 365 */           if (newDim != null) {
    	/* 366 */             Core.getInstance().setScreenSize(newDim.width, newDim.height);
    	/*     */           }
    	/*     */ 
    	/* 371 */           Display.update();
    	/*     */ 
    	/* 378 */           Display.sync(60);
    	/*     */ 
    	/* 385 */           GameWindow.logic();
    	/*     */         }
    	/*     */         catch (Exception ex)
    	/*     */         {
    	/* 408 */           JOptionPane.showMessageDialog(null, ex.getStackTrace(), "Error: " + ex.getMessage(), 0);
    	/* 409 */           Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, null, ex);
    	/*     */         }
    	/*     */       
    	/*     */     }
    	/*     */ 
    	/*     */     try
    	/*     */     {
    	/* 416 */       GameWindow.save(true);
    	/*     */     } catch (FileNotFoundException ex) {
    	/* 418 */       Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, null, ex);
    	/*     */     } catch (IOException ex) {
    	/* 420 */       Logger.getLogger(FrameLoader.class.getName()).log(Level.SEVERE, null, ex);
    	/*     */     }
    	/*     */ 
    	/* 423 */     Display.destroy();
    	/*     */ 
    	/* 425 */     System.exit(0);
    }
    public static void restartApplication(Runnable runBeforeRestart)
        throws IOException
    { try
    /*     */     {
    	/* 435 */       std::string java = System.getProperty("java.home") + "/bin/java";
    	/*     */ 
    	/* 437 */       List<std::string> vmArguments = ManagementFactory.getRuntimeMXBean().getInputArguments();
    	/* 438 */       StringBuffer vmArgsOneLine = new StringBuffer();
    	/* 439 */       for (std::string arg : vmArguments)
    	/*     */       {
    	/* 442 */         if (!arg.contains("-agentlib")) {
    	/* 443 */           vmArgsOneLine.append(arg);
    	/* 444 */           vmArgsOneLine.append(" ");
    	/*     */         }
    	/*     */       }
    	/*     */ 
    	/* 448 */       final StringBuffer cmd = new StringBuffer("\"" + java + "\" " + vmArgsOneLine);
    	/*     */ 
    	/* 451 */       std::string[] mainCommand = System.getProperty("sun.java.command").split(" ");
    	/*     */ 
    	/* 453 */       if (mainCommand[0].endsWith(".jar"))
    	/*     */       {
    	/* 455 */         cmd.append("-jar " + new File(mainCommand[0]).getPath());
    	/*     */       }
    	/*     */       else {
    	/* 458 */         cmd.append("-cp \"" + System.getProperty("java.class.path") + "\" " + mainCommand[0]);
    	/*     */       }
    	/*     */ 
    	/* 461 */       for (int i = 1; i < mainCommand.length; i++) {
    	/* 462 */         cmd.append(" ");
    	/* 463 */         cmd.append(mainCommand[i]);
    	/*     */       }
    	/*     */ 
    	/* 467 */       Runtime.getRuntime().addShutdownHook(
    			new Thread()
    	/*     */       {
    	/*     */         public void run() {
    	/*     */           try {
    	/* 471 */             Runtime.getRuntime().exec(cmd.toString());
    	/*     */           } catch (IOException e) {
    	/* 473 */             e.printStackTrace();
    	/*     */           }
    	/*     */         }
    	/*     */       });
    	/* 478 */       if (runBeforeRestart != null) {
    	/* 479 */         runBeforeRestart.run();
    	/*     */       }
    	/*     */ 
    	/* 482 */       Display.destroy();
    	/* 483 */       System.exit(0);
    	/*     */     }
    	/*     */     catch (Exception e)
    	/*     */     {
    	/* 488 */       e.printStackTrace();
    	/* 489 */       throw new IOException("Error while trying to restart the application", e);
    	/*     */     }
    }
    private static final std::string KEY_MAINWINDOW_X = "mainwindow.x";
    private static final std::string KEY_MAINWINDOW_Y = "mainwindow.y";
    private static final std::string KEY_MAINWINDOW_WIDTH = "mainwindow.width";
    private static final std::string KEY_MAINWINDOW_HEIGHT = "mainwindow.height";
    public static Canvas canvas;
    public static std::string IP;
    final AtomicReference newCanvasSize = new AtomicReference();
    public static volatile bool closeRequested;
    public static File makefile = nullptr;
    public static bool bServer = false;
    public static bool bClient = false;
    public static bool bFullscreen = false;
    public static int FullX = 1024;
    public static int FullY = 768;
    static Cursor cur;
    public static final std::string SUN_JAVA_COMMAND = "sun.java.command";
}} // namespace
