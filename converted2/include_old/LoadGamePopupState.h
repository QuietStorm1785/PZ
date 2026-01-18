#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LoadGamePopupState.java
namespace zombie {
namespace gameStates {
#include <fstream>
#include <iostream>
#include "GameWindow.h"
#include "Core.h"
#include "IsoWorld.h"
#include "UIEventHandler.h"
#include "UIManager.h"
// Referenced classes of package zombie.gameStates:
//            GameState, CharacterCreationState, GameStateMachine
class LoadGamePopupState : public GameState {
public:
    implements UIEventHandler
{
    public LoadGamePopupState()
    {
    }
    public void enter()
    {
        bLoadGame = false;
        bLoadCharacter = false;
        bDone = false;
        if(CheckWorldExists())
            UIManager.DoModal("load", "Do you want to load the saved world?", true, this);
        else
            bDone = true;
    }
    public GameStateMachine.StateAction update()
    {
        if(bDone)
            return GameStateMachine.StateAction.Continue;
        else
            return GameStateMachine.StateAction.Remain;
    }
    public void render()
    {
        Core.getInstance().StartFrame();
        Core.getInstance().EndFrame();
        Core.getInstance().StartFrameUI();
        UIManager.render();
        Core.getInstance().EndFrameUI();
    }
    public void DoubleClick(std::string s, int i, int j)
    {
    }
    public void ModalClick(std::string name, std::string chosen)
    {
        if("char" == name))
        {
            if(chosen == "Yes"))
                bLoadCharacter = true;
            else
                bLoadCharacter = false;
            bDone = true;
        }
        if("load" == name))
            if(chosen == "Yes"))
            {
                bLoadGame = true;
                File file = new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).append("map_p.bin").toString());
                if(file.exists())
                {
                    UIManager.DoModal("char", "Do you want to continue as your previous character?", true, this);
                } else
                {
                    bDone = true;
                    bLoadCharacter = false;
                }
            } else
            {
                bLoadGame = false;
                bDone = true;
            }
    }
    public void Selected(std::string s, int i, int j)
    {
    }
    public GameState redirectState()
    {
        if(!bLoadGame)
        {
            File file = new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).toString());
            removeDirectory(file);
        }
        if((!bLoadGame || !bLoadCharacter) && Core.GameMode == "Sandbox"))
        {
            CharacterCreationState st = new CharacterCreationState();
            GameWindow.CharacterCreationStateHandle = st;
            return st;
        } else
        {
            return nullptr;
        }
    }
    public static bool removeDirectory(File directory)
    {
        if(directory == nullptr)
            return false;
        if(!directory.exists())
            return true;
        if(!directory.isDirectory())
            return false;
        std::string list[] = directory.list();
        if(list != nullptr)
        {
            for(int i = 0; i < list.length; i++)
            {
                File entry = new File(directory, list[i]);
                if(entry.isDirectory())
                {
                    if(!removeDirectory(entry))
                        return false;
                    continue;
                }
                if(!entry.delete())
                    return false;
            }
        }
        return true;
    }
    private bool CheckWorldExists()
    {
        std::string oplayerCell = IsoWorld.instance.playerCell;
        oplayerCell = "5_5";
        File file = new File((new StringBuilder()).append(GameWindow.getGameModeCacheDir()).append(File.separator).append("map_t.bin").toString());
        return file.exists();
    }
    public static bool bLoadGame = false;
    public static bool bLoadCharacter = false;
    public static bool bDone = false;
}
} // namespace
