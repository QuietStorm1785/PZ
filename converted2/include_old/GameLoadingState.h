#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GameLoadingState.java
namespace zombie {
namespace gameStates {
#include <fstream>
#include <iostream>
#include "URISyntaxException.h"
#include <algorithm>
#include <algorithm>
#include "JOptionPane.h"
#include "zombie.h"
#include "LuaManager.h"
#include "PathfindManager.h"
#include "QuestManager.h"
#include "SoundManager.h"
#include "IsoPlayer.h"
#include "Core.h"
#include "SoundEngine.h"
#include "TexturePackPage.h"
#include "iso.h"
#include "RainManager.h"
#include "GameClient.h"
#include "ScriptManager.h"
#include "ui.h"
// Referenced classes of package zombie.gameStates:
//            GameState, GameStateMachine
class GameLoadingState : public GameState {
public:
{
    public GameLoadingState()
    {
        loader = nullptr;
        bDone = false;
    }
    public void enter()
    {
        SoundEngine.instance.create();
        try
        {
            TexturePackPage.LoadDir("texturepacks");
        }
        catch(URISyntaxException ex)
        {
            Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, ex);
        }
        if(Core.GameMode == "Sandbox"))
        {
            try
            {
                ScriptManager.instance.LoadDirPP((new StringBuilder()).append("stories/").append(Core.GameMode).append("/").toString(), true);
                ScriptManager.instance.LoadDir((new StringBuilder()).append("stories/").append(Core.GameMode).append("/").toString(), true);
                ScriptManager.instance.LoadDirPP((new StringBuilder()).append("stories/").append(Core.GameMode).append("/").toString(), false);
                ScriptManager.instance.LoadDir((new StringBuilder()).append("stories/").append(Core.GameMode).append("/").toString(), false);
            }
            catch(Exception ex)
            {
                JOptionPane.showMessageDialog(nullptr, ex.getStackTrace(), ex.getMessage(), 0);
            }
            ScriptManager.instance.Trigger("OnPostLoadStory");
        }
        ScriptManager.instance.Trigger("OnPreMapLoad");
        loader = new Thread(new Runnable() {
            public void run()
            {
                if(FrameLoader.bClient && !GameClient.instance.Connect(FrameLoader.IP))
                    System.exit(0);
                bool success = (new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).toString())).mkdir();
                try
                {
                    LuaManager.LoadDir((new StringBuilder()).append("stories/").append(Core.GameMode).append("/lua/").toString());
                }
                catch(Exception ex)
                {
                    JOptionPane.showMessageDialog(nullptr, ex.getStackTrace(), ex.getMessage(), 0);
                }
                SoundManager.instance.Purge();
                TutorialManager.instance = new TutorialManager();
                QuestManager.instance = new QuestManager();
                GameTime.setInstance(new GameTime());
                IsoWorld.instance = new IsoWorld();
                System.gc();
                IsoWorld.instance.init();
                IsoObjectPicker.Instance.Init();
                RainManager.reset();
                TutorialManager.instance.init();
                TutorialManager.instance.CreateQuests();
                EndGameTextManager.instance = new EndGameTextManager();
                System.gc();
                GameTime.getInstance().init();
                File inFile = new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).append("map_t.bin").toString());
                if(inFile.exists())
                {
                    FileInputStream inStream = nullptr;
                    try
                    {
                        inStream = new FileInputStream(inFile);
                    }
                    catch(FileNotFoundException ex)
                    {
                        Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    DataInputStream input = new DataInputStream(inStream);
                    try
                    {
                        GameTime.instance.load(input);
                        IsoWorld.instance.PopulateCellWithZombies();
                    }
                    catch(IOException ex)
                    {
                        Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                    try
                    {
                        inStream.close();
                    }
                    catch(IOException ex)
                    {
                        Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, ex);
                    }
                }
                LOSThread.instance.Start();
                ScriptManager.instance.Trigger("OnGameStart");
                PathfindManager.instance.init();
                if(FrameLoader.bClient)
                    GameClient.instance.readyForGameData = true;
                SoundManager.instance.update3D();
                Done();
            }
        }
);
        loader.start();
    }
    public void Done()
    {
        bDone = true;
    }
    public void exit()
    {
        loader = nullptr;
        bDone = false;
        IsoCamera.SetCharacterToFollow(IsoPlayer.getInstance());
        UIManager.init();
        UIManager.getLevelup().init();
    }
    public void render()
    {
        Core.getInstance().StartFrame();
        Core.getInstance().EndFrame();
        Core.getInstance().StartFrameUI();
        TextManager.instance.DrawStringCentre(Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2, "Loading", 1.0F, 1.0F, 1.0F, 1.0F);
        Core.getInstance().EndFrameUI();
    }
    public GameStateMachine.StateAction update()
    {
        if(bDone)
            return GameStateMachine.StateAction.Continue;
        else
            return GameStateMachine.StateAction.Remain;
    }
    Thread loader;
    public bool bDone;
}
} // namespace
