#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GenericButton.java
namespace zombie {
namespace ui {
#include "LuaCaller.h"
#include "KahluaTable.h"
#include "LuaManager.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, UIEventHandler
class GenericButton : public UIElement {
public:
{
    public GenericButton(UIElement messages, int x, int y, int width, int height, std::string name, std::string text, 
            Texture UpTex, Texture DownTex)
    {
        clicked = false;
        mouseOver = false;
        UpTexture = nullptr;
        DownTexture = nullptr;
        MessageTarget2 = nullptr;
        this.x = x;
        this.y = y;
        MessageTarget = messages;
        this.name = name;
        this.text = text;
        this.width = width;
        this.height = height;
        UpTexture = UpTex;
        DownTexture = DownTex;
    }
    public GenericButton(UIEventHandler messages, int x, int y, int width, int height, std::string name, std::string text, 
            Texture UpTex, Texture DownTex)
    {
        clicked = false;
        mouseOver = false;
        UpTexture = nullptr;
        DownTexture = nullptr;
        MessageTarget2 = nullptr;
        this.x = x;
        this.y = y;
        MessageTarget2 = messages;
        this.name = name;
        this.text = text;
        this.width = width;
        this.height = height;
        UpTexture = UpTex;
        DownTexture = DownTex;
    }
    public bool onMouseDown(int x, int y)
    {
        if(!isVisible())
            return false;
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseDown") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseDown"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        clicked = true;
        return true;
    }
    public bool onMouseMove(int dx, int dy)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseMove") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseMove"), new Object[] {
                table, Integer.valueOf(dx), Integer.valueOf(dy)
            });
        mouseOver = true;
        return true;
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseMoveOutside") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseMoveOutside"), new Object[] {
                table, Integer.valueOf(dx), Integer.valueOf(dy)
            });
        clicked = false;
        mouseOver = false;
    }
    public bool onMouseUp(int x, int y)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseUp") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseUp"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        if(clicked)
            if(MessageTarget2 != nullptr)
                MessageTarget2.Selected(name, 0, 0);
            else
                MessageTarget.ButtonClicked(name);
        clicked = false;
        return true;
    }
    public void render()
    {
        if(!isVisible())
            return;
        int dy = 0;
        if(clicked)
        {
            DrawTextureScaled(DownTexture, 0, 0, getWidth(), getHeight(), 1.0F);
            DrawTextCentre(text, getWidth() / 2, 1, 1.0F, 1.0F, 1.0F, 1.0F);
        } else
        {
            DrawTextureScaled(UpTexture, 0, 0, getWidth(), getHeight(), 1.0F);
            DrawTextCentre(text, getWidth() / 2, 1, 1.0F, 1.0F, 1.0F, 1.0F);
        }
        super.render();
    }
    public bool clicked;
    public UIElement MessageTarget;
    public bool mouseOver;
    public std::string name;
    public std::string text;
    Texture UpTexture;
    Texture DownTexture;
    private UIEventHandler MessageTarget2;
}
} // namespace
