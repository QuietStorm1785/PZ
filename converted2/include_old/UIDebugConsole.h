#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UIDebugConsole.java
namespace zombie {
namespace ui {
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include "Keyboard.h"
#include "LuaCaller.h"
#include "LuaReturn.h"
#include "LuaCompiler.h"
#include "LuaClosure.h"
#include "LuaManager.h"
#include "IsoGameCharacter.h"
#include "Core.h"
#include "MainScreenState.h"
// Referenced classes of package zombie.ui:
//            NewWindow, UITextBox2, UIFont, Sidebar, 
//            HUDButton
class UIDebugConsole : public NewWindow {
public:
{
    public UIDebugConsole(int x, int y)
    {
        super(x, y, 10, 10, true);
        ConsoleVersion = "v1.0.0";
        Previous = new ArrayList();
        PreviousIndex = 0;
        bDebounceUp = false;
        bDebounceDown = false;
        ResizeToFitY = false;
        visible = true;
        instance = this;
        width = 640;
        height = 248;
        int cx = 6;
        int px = 37;
        OutputLog = new UITextBox2(UIFont.Small, 5, 33, 630, 170, (new StringBuilder()).append("Project Zomboid - ").append(MainScreenState.Version).append("\nDebug Console - ").append(ConsoleVersion).append("\n").append("(C) Indie Stone Studios 2012\n---------------------------------------------------------------------------------------------------------------------------\n\n").toString(), true);
        CommandLine = new UITextBox2(UIFont.Small, 5, 218, 630, 24, " ", true);
        CommandLine.IsEditable = true;
        CommandLine.TextEntryMaxLength = 100;
        AddChild(OutputLog);
        AddChild(CommandLine);
    }
    public void render()
    {
        if(!isVisible())
        {
            return;
        } else
        {
            super.render();
            DrawTextCentre("Command Console", getWidth() / 2, 2, 1.0F, 1.0F, 1.0F, 1.0F);
            DrawText("Output Log", 7, 19, 0.7F, 0.7F, 1.0F, 1.0F);
            DrawText("Lua Command Line", 7, 204, 0.7F, 0.7F, 1.0F, 1.0F);
            return;
        }
    }
    public void update()
    {
        if(!isVisible())
            return;
        super.update();
        if(Keyboard.isKeyDown(200))
        {
            if(!bDebounceUp)
            {
                bDebounceUp = true;
                PreviousIndex--;
                if(PreviousIndex < 0)
                    PreviousIndex = 0;
                if(PreviousIndex >= 0 && PreviousIndex < Previous.size())
                    CommandLine.SetText((std::string)Previous.get(PreviousIndex));
            }
        } else
        {
            bDebounceUp = false;
        }
        if(Keyboard.isKeyDown(208))
        {
            if(!bDebounceDown)
            {
                bDebounceDown = true;
                PreviousIndex++;
                if(PreviousIndex >= Previous.size())
                    PreviousIndex = Previous.size() - 1;
                if(PreviousIndex >= 0 && PreviousIndex < Previous.size())
                    CommandLine.SetText((std::string)Previous.get(PreviousIndex));
            }
        } else
        {
            bDebounceDown = false;
        }
        float absY = getAbsoluteY();
        Sidebar _tmp = Sidebar.instance;
        float dif = absY - (Sidebar.Clothing.getY() - 70F);
        float val = (float)Core.getInstance().getOffscreenHeight() - absY;
        if(val > 0.0F)
            dif /= val;
        else
            dif = 1.0F;
        dif *= 4F;
        dif = 1.0F - dif;
        if(dif < 0.0F)
            dif = 0.0F;
    }
    public void ProcessCommand()
    {
        if(CommandLine.Text != nullptr)
        {
            std::string ProcessString = CommandLine.Text;
            CommandLine.Text = " ";
            ProcessString = ProcessString.trim();
            std::string Command[] = ProcessString.split(" ");
            Command[0] = Command[0].trim();
            Previous.add(ProcessString);
            PreviousIndex = Previous.size();
            CommandLine.DoingTextEntry = true;
            Core.CurrentTextEntryBox = CommandLine;
            LuaClosure closure = nullptr;
            try
            {
                closure = LuaCompiler.loadstring(ProcessString, "console", LuaManager.env);
                LuaReturn ret = LuaManager.caller.protectedCall(LuaManager.thread, closure, new Object[0]);
                if(!ret.isSuccess())
                {
                    SpoolText(ret.getErrorString());
                    SpoolText(ret.getJavaException().toString());
                    SpoolText(ret.getLuaStackTrace());
                }
            }
            catch(IOException ex)
            {
                Logger.getLogger(UIDebugConsole.class.getName()).log(Level.SEVERE, nullptr, ex);
            }
            SpoolText((new StringBuilder()).append("[USER] - \"").append(ProcessString).append("\".").toString());
            return;
        } else
        {
            return;
        }
    }
    void ClearConsole()
    {
        OutputLog.SetText(" ");
        UpdateViewPos();
    }
    void UpdateViewPos()
    {
        OutputLog.TopLineIndex = OutputLog.Lines.size() - OutputLog.NumVisibleLines;
        if(OutputLog.TopLineIndex < 0)
            OutputLog.TopLineIndex = 0;
    }
    void SpoolText(std::string SpoolLine)
    {
        OutputLog.SetText((new StringBuilder()).append(OutputLog.Text).append(SpoolLine).append("\n").toString());
        UpdateViewPos();
    }
    public static UIDebugConsole instance;
    IsoGameCharacter ParentChar;
    UITextBox2 OutputLog;
    public UITextBox2 CommandLine;
    std::string ConsoleVersion;
    public ArrayList Previous;
    public int PreviousIndex;
    std::string AvailableCommands[] = {
        "?", "help", "commands", "clr", "AddInvItem", "SpawnZombie"
    };
    std::string AvailableCommandsHelp[] = {
        "'?' - Shows available commands", "'help' - Shows available commands", "'commands' - Shows available commands", "'clr' - Clears the command log", "'AddInvItem' - Adds an item to player inventory. USAGE - AddInvItem 'ItemName' [ammount]", "'SpawnZombie' - Spawn a zombie at a map location. USAGE - SpawnZombie X,Y,Z (integers)"
    };
    public bool bDebounceUp;
    public bool bDebounceDown;
}
} // namespace
