#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ModBrowserState.java
namespace zombie {
namespace gameStates {
#include <algorithm>
#include "Core.h"
#include "TexturePackPage.h"
#include "ui.h"
// Referenced classes of package zombie.gameStates:
//            GameState, GameStateMachine
class ModBrowserState : public GameState {
public:
    implements UIEventHandler
{
    public ModBrowserState()
    {
    }
    public void enter()
    {
        TexturePackPage.getPackPage("ui");
        if(Core.bDoubleSize)
            Core.getInstance().doubleSizeToggle();
        float width = (float)Core.getInstance().getOffscreenWidth() * 0.7F;
        float height = (float)Core.getInstance().getOffscreenHeight() * 0.7F;
        UIManager.getUI().clear();
        int x = (int)((float)(Core.getInstance().getOffscreenWidth() / 2) - width / 2.0F);
        int y = (int)((float)(Core.getInstance().getOffscreenHeight() / 2) - height / 2.0F);
        Panel = new ModBrowser(this, x, y, (int)width, (int)height);
        UIManager.getUI().add(Panel);
    }
    public void DoubleClick(std::string s, int i, int j)
    {
    }
    public void Selected(std::string s, int i, int j)
    {
    }
    public GameStateMachine.StateAction update()
    {
        return GameStateMachine.StateAction.Remain;
    }
    public void render()
    {
        Core.getInstance().StartFrame();
        UIManager.render();
        Core.getInstance().EndFrame();
    }
    public void ModalClick(std::string s, std::string s1)
    {
    }
    ModBrowser Panel;
}
} // namespace
