#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UIElement.java
namespace zombie {
namespace ui {
#include <vector>
#include <algorithm>
#include <algorithm>
#include "GL11.h"
#include "LuaCaller.h"
#include "KahluaTable.h"
#include "GameApplet.h"
#include "IndieGL.h"
#include "LuaManager.h"
#include "Color.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Mouse.h"
#include "IsoCamera.h"
// Referenced classes of package zombie.ui:
//            TextManager, UIFont
class UIElement {
public:
{
    public UIElement()
    {
        capture = false;
        IgnoreLossControl = false;
        clickedValue = nullptr;
        Controls = new Vector();
        defaultDraw = true;
        followGameWorld = false;
        height = 256;
        Parent = nullptr;
        visible = true;
        width = 256;
        x = 0.0F;
        y = 0.0F;
        alwaysOnTop = false;
        bConsumeMouseEvents = true;
        anchorTop = true;
        anchorLeft = true;
        anchorRight = false;
        anchorBottom = false;
        lastheight = -1;
        lastwidth = -1;
        bResizeDirty = false;
    }
    public void setAlwaysOnTop(bool b)
    {
        alwaysOnTop = b;
    }
    public UIElement(KahluaTable table)
    {
        capture = false;
        IgnoreLossControl = false;
        clickedValue = nullptr;
        Controls = new Vector();
        defaultDraw = true;
        followGameWorld = false;
        height = 256;
        Parent = nullptr;
        visible = true;
        width = 256;
        x = 0.0F;
        y = 0.0F;
        alwaysOnTop = false;
        bConsumeMouseEvents = true;
        anchorTop = true;
        anchorLeft = true;
        anchorRight = false;
        anchorBottom = false;
        lastheight = -1;
        lastwidth = -1;
        bResizeDirty = false;
        this.table = table;
    }
    public void AddChild(UIElement el)
    {
        getControls().add(el);
        el.setParent(this);
    }
    public void RemoveChild(UIElement el)
    {
        getControls().remove(el);
        el.setParent(nullptr);
    }
    public void setConsumeMouseEvents(bool bConsume)
    {
        bConsumeMouseEvents = bConsume;
    }
    public void ClearChildren()
    {
        getControls().clear();
    }
    public void ButtonClicked(std::string name)
    {
        setClickedValue(name);
    }
    public void DrawText(std::string text, int x, int y, float r, float g, float b, float alpha)
    {
        TextManager.instance.DrawString(x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawText(UIFont font, std::string text, int x, int y, float r, float g, float b, 
            float alpha)
    {
        TextManager.instance.DrawString(font, x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawTextCentre(std::string text, int x, int y, float r, float g, float b, float alpha)
    {
        TextManager.instance.DrawStringCentre(x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawTextCentre(UIFont font, std::string text, int x, int y, float r, float g, float b, 
            float alpha)
    {
        TextManager.instance.DrawStringCentre(font, x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawTextRight(std::string text, int x, int y, float r, float g, float b, float alpha)
    {
        TextManager.instance.DrawStringRight(x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawTextRight(UIFont font, std::string text, int x, int y, float r, float g, float b, 
            float alpha)
    {
        TextManager.instance.DrawStringRight(font, x + getAbsoluteX(), y + getAbsoluteY(), text, r, g, b, alpha);
    }
    public void DrawTexture(Texture tex, int x, int y, float alpha)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            dx = (int)((float)dx + tex.offsetX);
            dy = (int)((float)dy + tex.offsetY);
            SpriteRenderer.instance.render(tex, dx, dy, tex.getWidth(), tex.getHeight(), 1.0F, 1.0F, 1.0F, alpha);
            return;
        }
    }
    public void DrawTextureCol(Texture tex, int x, int y, Color col)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            SpriteRenderer.instance.render(tex, dx, dy, tex.getWidth(), tex.getHeight(), col.r, col.b, col.g, col.a);
            return;
        }
    }
    public void DrawTextureScaled(Texture tex, int x, int y, int width, int height, float alpha)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            dx = (int)((float)dx + tex.offsetX);
            dy = (int)((float)dy + tex.offsetY);
            SpriteRenderer.instance.render(tex, dx, dy, width, height, 1.0F, 1.0F, 1.0F, alpha);
            return;
        }
    }
    public void DrawTextureScaledCol(Texture tex, int x, int y, int width, int height, Color col)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            SpriteRenderer.instance.render(tex, dx, dy, width, height, col.r, col.g, col.b, col.a);
            return;
        }
    }
    public void DrawTextureScaledColor(Texture tex, int x, int y, int width, int height, float r, float g, 
            float b, float a)
    {
        DrawTextureScaledCol(tex, x, y, width, height, new Color(r, g, b, a));
    }
    public void DrawTextureColor(Texture tex, int x, int y, float r, float g, float b, float a)
    {
        tempcol.r = r;
        tempcol.g = g;
        tempcol.b = b;
        tempcol.a = a;
        DrawTextureCol(tex, x, y, tempcol);
    }
    public void DrawTextureIgnoreOffset(Texture tex, int x, int y, int width, int height, Color col)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            SpriteRenderer.instance.render(tex, dx, dy, width, height, col.r, col.g, col.b, col.a);
            return;
        }
    }
    public void DrawTexture_FlippedX(Texture tex, int x, int y, int width, int height, Color col)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            SpriteRenderer.instance.renderflipped(tex, dx, dy, width, height, col.r, col.g, col.b, col.a);
            return;
        }
    }
    public void DrawTexture_FlippedXIgnoreOffset(Texture tex, int x, int y, int width, int height, Color col)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            int dx = x + getAbsoluteX();
            int dy = y + getAbsoluteY();
            SpriteRenderer.instance.renderflipped(tex, dx, dy, width, height, col.r, col.g, col.b, col.a);
            return;
        }
    }
    public void DrawTextureFlipped(Texture tex, int x, int y, float alpha, bool FlipX, bool FlipY)
    {
        if(!isVisible())
            return;
        int dx = x + getAbsoluteX();
        int dy = y + getAbsoluteY();
        dx = (int)((float)dx + tex.offsetX);
        dy = (int)((float)dy + tex.offsetY);
        GL11.glColor4f(1.0F, 1.0F, 1.0F, alpha);
        Texture.lr = 1.0F;
        Texture.lg = 1.0F;
        Texture.lb = 1.0F;
        Texture.la = alpha;
        tex.bind();
        IndieGL.Begin();
        if(!FlipX && !FlipY)
        {
            GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
            GL11.glVertex2f(dx, dy);
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
            GL11.glVertex2f(dx + tex.getWidth(), dy);
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
            GL11.glVertex2f(dx + tex.getWidth(), dy + tex.getHeight());
            GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
            GL11.glVertex2f(dx, dy + tex.getHeight());
        }
        if(FlipX && !FlipY)
        {
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
            GL11.glVertex2f(dx, dy);
            GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
            GL11.glVertex2f(dx + tex.getWidth(), dy);
            GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
            GL11.glVertex2f(dx + tex.getWidth(), dy + tex.getHeight());
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
            GL11.glVertex2f(dx, dy + tex.getHeight());
        }
        if(!FlipX && FlipY)
        {
            GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
            GL11.glVertex2f(dx, dy);
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
            GL11.glVertex2f(dx + tex.getWidth(), dy);
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
            GL11.glVertex2f(dx + tex.getWidth(), dy + tex.getHeight());
            GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
            GL11.glVertex2f(dx, dy + tex.getHeight());
        }
        if(FlipX && FlipY)
        {
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYEnd());
            GL11.glVertex2f(dx, dy);
            GL11.glTexCoord2f(tex.getXStart(), tex.getYEnd());
            GL11.glVertex2f(dx + tex.getWidth(), dy);
            GL11.glTexCoord2f(tex.getXStart(), tex.getYStart());
            GL11.glVertex2f(dx + tex.getWidth(), dy + tex.getHeight());
            GL11.glTexCoord2f(tex.getXEnd(), tex.getYStart());
            GL11.glVertex2f(dx, dy + tex.getHeight());
        }
        try
        {
            IndieGL.End();
        }
        catch(Exception ex)
        {
            Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, nullptr, ex);
            int n = 0;
        }
    }
    public void DrawUVSliceTexture(Texture tex, int x, int y, int width, int height, Color col, float xStart, 
            float yStart, float xEnd, float yEnd)
    {
        if(!isVisible())
            return;
        int dx = x + getAbsoluteX();
        int dy = y + getAbsoluteY();
        dx = (int)((float)dx + tex.offsetX);
        dy = (int)((float)dy + tex.offsetY);
        if(Texture.lr != col.r || Texture.lg != col.g || Texture.lb != col.b || Texture.la != col.a)
            GL11.glColor4f(col.r, col.g, col.b, col.a);
        Texture.lr = col.r;
        Texture.lg = col.g;
        Texture.lb = col.b;
        Texture.la = col.a;
        float xS = tex.getXStart();
        float yS = tex.getYStart();
        float xE = tex.getXEnd();
        float yE = tex.getYEnd();
        float xTot = xE - xS;
        float yTot = yE - yS;
        float texXTot = xEnd - xStart;
        float texYTot = yEnd - yStart;
        float xDel = texXTot / 1.0F;
        float yDel = texYTot / 1.0F;
        xS += xStart * xTot;
        yS += yStart * yTot;
        xE -= (1.0F - xEnd) * xTot;
        yE -= (1.0F - yEnd) * yTot;
        xS = (float)(int)(xS * 1000F) / 1000F;
        xE = (float)(int)(xE * 1000F) / 1000F;
        yS = (float)(int)(yS * 1000F) / 1000F;
        yE = (float)(int)(yE * 1000F) / 1000F;
        int x2 = dx + width;
        int y2 = dy + height;
        dx = (int)((float)dx + xStart * (float)width);
        dy = (int)((float)dy + yStart * (float)height);
        x2 = (int)((float)x2 - (1.0F - xEnd) * (float)width);
        y2 = (int)((float)y2 - (1.0F - yEnd) * (float)height);
        SpriteRenderer.instance.render(tex, dx, dy, x2 - dx, y2 - dy, col.r, col.g, col.b, col.a, xS, yS, xE, yS, xE, yE, xS, yE);
    }
    public int getAbsoluteX()
    {
        if(getParent() != nullptr)
            return getParent().getAbsoluteX() + (int)getX();
        else
            return (int)getX();
    }
    public int getAbsoluteY()
    {
        if(getParent() != nullptr)
            return getParent().getAbsoluteY() + (int)getY();
        else
            return (int)getY();
    }
    public std::string getClickedValue()
    {
        return clickedValue;
    }
    public bool onMouseDown(int x, int y)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseDown") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseDown"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            if(((float)x > ui.getX() && (float)y > ui.getY() && (float)x < ui.getX() + (float)ui.getWidth() && (float)y < ui.getY() + (float)ui.getHeight() || ui.isCapture()) && ui.onMouseDown(x - (int)ui.getX(), y - (int)ui.getY()))
                return true;
        }
        return false;
    }
    public bool onMouseMove(int dx, int dy)
    {
        int mx = Mouse.getXA();
        int my = Mouse.getYA();
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseMove") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseMove"), new Object[] {
                table, Integer.valueOf(dx), Integer.valueOf(dy)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            if(mx > ui.getAbsoluteX() && my > ui.getAbsoluteY() && mx < ui.getAbsoluteX() + ui.getWidth() && my < ui.getAbsoluteY() + ui.getHeight() || ui.isCapture())
            {
                if(ui.onMouseMove(dx, dy))
                    return bConsumeMouseEvents;
            } else
            {
                ui.onMouseMoveOutside(dx, dy);
            }
        }
        return false;
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        int mx = Mouse.getX();
        int my = Mouse.getY();
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseMoveOutside") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseMoveOutside"), new Object[] {
                table, Integer.valueOf(dx), Integer.valueOf(dy)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            ui.onMouseMoveOutside(dx, dy);
        }
    }
    public bool onMouseUp(int x, int y)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onMouseUp") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onMouseUp"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            if(((float)x > ui.getX() && (float)y > ui.getY() && (float)x < ui.getX() + (float)ui.getWidth() && (float)y < ui.getY() + (float)ui.getHeight() || ui.isCapture()) && ui.onMouseUp(x - (int)ui.getX(), y - (int)ui.getY()))
                return bConsumeMouseEvents;
        }
        return false;
    }
    public void onresize()
    {
    }
    public void onResize()
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onResize") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onResize"), new Object[] {
                table, Integer.valueOf(width), Integer.valueOf(getHeight())
            });
        if(Parent != nullptr && Parent.bResizeDirty)
        {
            int difx = Parent.getWidth() - Parent.lastwidth;
            int dify = Parent.getHeight() - Parent.lastheight;
            if(!anchorTop && anchorBottom)
                setY(getY() + (float)dify);
            if(anchorTop && anchorBottom)
                setHeight(getHeight() + dify);
            if(!anchorLeft && anchorRight)
                setX(getX() + (float)difx);
            if(anchorLeft && anchorRight)
                setWidth(getWidth() + difx);
        }
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            ui.onResize();
        }
        bResizeDirty = false;
    }
    public bool onRightMouseDown(int x, int y)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onRightMouseDown") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onRightMouseDown"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            if(((float)x > ui.getX() && (float)y > ui.getY() && (float)x < ui.getX() + (float)ui.getWidth() && (float)y < ui.getY() + (float)ui.getHeight() || ui.isCapture()) && ui.onRightMouseDown(x - (int)ui.getX(), y - (int)ui.getY()))
                return bConsumeMouseEvents;
        }
        return false;
    }
    public bool onRightMouseUp(int x, int y)
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("onRightMouseUp") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onRightMouseUp"), new Object[] {
                table, Integer.valueOf(x), Integer.valueOf(y)
            });
        for(int i = getControls().size() - 1; i >= 0; i--)
        {
            UIElement ui = (UIElement)getControls().get(i);
            if(((float)x > ui.getX() && (float)y > ui.getY() && (float)x < ui.getX() + (float)ui.getWidth() && (float)y < ui.getY() + (float)ui.getHeight() || ui.isCapture()) && ui.onRightMouseUp(x - (int)ui.getX(), y - (int)ui.getY()))
                return bConsumeMouseEvents;
        }
        return false;
    }
    public void RemoveControl(UIElement el)
    {
        getControls().remove(el);
        el.setParent(nullptr);
    }
    public void render()
    {
        if(!isVisible())
            return;
        Object o[];
        if(getTable() != nullptr && getTable().rawget("prerender") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("prerender"), new Object[] {
                table
            });
        for(int i = 0; i < getControls().size(); i++)
            ((UIElement)getControls().get(i)).render();
        if(getTable() != nullptr && getTable().rawget("render") != nullptr)
            o = ((LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("render"), new Object[] {table})));
    }
    public void update()
    {
        Object o[];
        if(getTable() != nullptr && getTable().rawget("update") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("update"), new Object[] {
                table
            });
        for(int i = 0; i < getControls().size(); i++)
            ((UIElement)getControls().get(i)).update();
        if(isFollowGameWorld())
        {
            setX(getX() - (IsoCamera.getOffX() - IsoCamera.getLastOffX()));
            setY(getY() - (IsoCamera.getOffY() - IsoCamera.getLastOffY()));
        }
        if(bResizeDirty)
        {
            onResize();
            lastwidth = width;
            lastheight = height;
            bResizeDirty = false;
        }
    }
    void BringToTop(UIElement el)
    {
        getControls().remove(el);
        getControls().add(el);
    }
    public bool isCapture()
    {
        return capture;
    }
    public void setCapture(bool capture)
    {
        this.capture = capture;
    }
    public bool isIgnoreLossControl()
    {
        return IgnoreLossControl;
    }
    public void setIgnoreLossControl(bool IgnoreLossControl)
    {
        this.IgnoreLossControl = IgnoreLossControl;
    }
    public void setClickedValue(std::string clickedValue)
    {
        this.clickedValue = clickedValue;
    }
    public Vector getControls()
    {
        return Controls;
    }
    public void setControls(Vector Controls)
    {
        setControls(Controls);
    }
    public bool isDefaultDraw()
    {
        return defaultDraw;
    }
    public void setDefaultDraw(bool defaultDraw)
    {
        this.defaultDraw = defaultDraw;
    }
    public bool isFollowGameWorld()
    {
        return followGameWorld;
    }
    public void setFollowGameWorld(bool followGameWorld)
    {
        this.followGameWorld = followGameWorld;
    }
    public int getHeight()
    {
        return height;
    }
    public UIElement getParent()
    {
        return Parent;
    }
    public void setParent(UIElement Parent)
    {
        this.Parent = Parent;
    }
    public bool isVisible()
    {
        return visible;
    }
    public void setVisible(bool visible)
    {
        this.visible = visible;
    }
    public int getWidth()
    {
        return width;
    }
    public void setWidth(int width)
    {
        lastwidth = this.width;
        this.width = width;
        bResizeDirty = true;
    }
    public float getX()
    {
        return x;
    }
    public void setX(float x)
    {
        this.x = x;
    }
    public float getY()
    {
        return y;
    }
    public void setY(float y)
    {
        this.y = y;
    }
    public KahluaTable getTable()
    {
        return table;
    }
    public void setTable(KahluaTable table)
    {
        this.table = table;
    }
    public void setHeight(int height)
    {
        lastheight = this.height;
        this.height = height;
        bResizeDirty = true;
    }
    public bool isAnchorTop()
    {
        return anchorTop;
    }
    public void setAnchorTop(bool anchorTop)
    {
        this.anchorTop = anchorTop;
    }
    public bool isAnchorLeft()
    {
        return anchorLeft;
    }
    public void setAnchorLeft(bool anchorLeft)
    {
        this.anchorLeft = anchorLeft;
    }
    public bool isAnchorRight()
    {
        return anchorRight;
    }
    public void setAnchorRight(bool anchorRight)
    {
        this.anchorRight = anchorRight;
    }
    public bool isAnchorBottom()
    {
        return anchorBottom;
    }
    public void setAnchorBottom(bool anchorBottom)
    {
        this.anchorBottom = anchorBottom;
    }
    public bool capture;
    public bool IgnoreLossControl;
    public std::string clickedValue;
    public Vector Controls;
    public bool defaultDraw;
    public bool followGameWorld;
    public int height;
    public UIElement Parent;
    public bool visible;
    public int width;
    public float x;
    public float y;
    public KahluaTable table;
    bool alwaysOnTop;
    private bool bConsumeMouseEvents;
    static Color tempcol = new Color(0, 0, 0, 0);
    public bool anchorTop;
    public bool anchorLeft;
    public bool anchorRight;
    public bool anchorBottom;
    int lastheight;
    int lastwidth;
    bool bResizeDirty;
}
} // namespace
