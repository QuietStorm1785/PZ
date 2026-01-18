#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   NewWindow.java
namespace zombie {
namespace ui {
#include <algorithm>
#include "Rectangle.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, HUDButton, MovementBlender
class NewWindow : public UIElement {
public:
{
    public NewWindow(int x, int y, int width, int height, bool bHasClose)
    {
        clickX = 0;
        clickY = 0;
        clientH = 0;
        clientW = 0;
        Movable = true;
        moving = false;
        ncclientH = 0;
        ncclientW = 0;
        nestedItems = new Stack();
        ResizeToFitY = true;
        alpha = 1.0F;
        dialogBottomLeft = nullptr;
        dialogBottomMiddle = nullptr;
        dialogBottomRight = nullptr;
        dialogLeft = nullptr;
        dialogMiddle = nullptr;
        dialogRight = nullptr;
        titleCloseIcon = nullptr;
        titleLeft = nullptr;
        titleMiddle = nullptr;
        titleRight = nullptr;
        closeButton = nullptr;
        this.x = x;
        this.y = y;
        if(width < 156)
            width = 156;
        if(height < 78)
            height = 78;
        this.width = width;
        this.height = height;
        titleLeft = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Left.png");
        titleMiddle = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Middle.png");
        titleRight = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Right.png");
        dialogLeft = Texture.getSharedTexture("media/ui/Dialog_Left.png");
        dialogMiddle = Texture.getSharedTexture("media/ui/Dialog_Middle.png");
        dialogRight = Texture.getSharedTexture("media/ui/Dialog_Right.png");
        dialogBottomLeft = Texture.getSharedTexture("media/ui/Dialog_Bottom_Left.png");
        dialogBottomMiddle = Texture.getSharedTexture("media/ui/Dialog_Bottom_Middle.png");
        dialogBottomRight = Texture.getSharedTexture("media/ui/Dialog_Bottom_Right.png");
        if(bHasClose)
        {
            closeButton = new HUDButton("close", width - 16, 2, "media/ui/Dialog_Titlebar_CloseIcon.png", "media/ui/Dialog_Titlebar_CloseIcon.png", "media/ui/Dialog_Titlebar_CloseIcon.png", this);
            AddChild(closeButton);
        }
        clientW = width;
        clientH = height;
    }
    public void Nest(UIElement el, int t, int r, int b, int l)
    {
        AddChild(el);
        nestedItems.add(new Rectangle(l, t, r, b));
        el.setX(l);
        el.setY(t);
        el.update();
    }
    public void ButtonClicked(std::string name)
    {
        super.ButtonClicked(name);
        if(name == "close"))
            setVisible(false);
    }
    public bool onMouseDown(int x, int y)
    {
        if(!isVisible())
            return false;
        super.onMouseDown(x, y);
        if(y < 18)
        {
            clickX = x;
            clickY = y;
            if(Movable)
                moving = true;
            setCapture(true);
        }
        return true;
    }
    public void setMovable(bool bMoveable)
    {
        Movable = bMoveable;
    }
    public bool onMouseMove(int dx, int dy)
    {
        if(!isVisible())
            return false;
        super.onMouseMove(dx, dy);
        if(moving)
            if(getParent() instanceof MovementBlender)
            {
                getParent().setX(getParent().getX() + (float)dx);
                getParent().setY(getParent().getY() + (float)dy);
            } else
            {
                setX(getX() + (float)dx);
                setY(getY() + (float)dy);
            }
        return false;
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        if(!isVisible())
            return;
        super.onMouseMoveOutside(dx, dy);
        if(moving)
            if(getParent() instanceof MovementBlender)
            {
                getParent().setX(getParent().getX() + (float)dx);
                getParent().setY(getParent().getY() + (float)dy);
            } else
            {
                setX(getX() + (float)dx);
                setY(getY() + (float)dy);
            }
    }
    public bool onMouseUp(int x, int y)
    {
        if(!isVisible())
        {
            return false;
        } else
        {
            super.onMouseUp(x, y);
            moving = false;
            setCapture(false);
            return true;
        }
    }
    public void render()
    {
        float alpha = 0.8F * this.alpha;
        int x = 0;
        int y = 0;
        DrawTexture(titleLeft, x, y, alpha);
        DrawTexture(titleRight, getWidth() - titleRight.getWidth(), y, alpha);
        DrawTextureScaled(titleMiddle, titleLeft.getWidth(), y, getWidth() - titleLeft.getWidth() * 2, titleMiddle.getHeight(), alpha);
        y += titleRight.getHeight();
        DrawTextureScaled(dialogLeft, x, y, dialogLeft.getWidth(), getHeight() - titleLeft.getHeight() - dialogBottomLeft.getHeight(), alpha);
        DrawTextureScaled(dialogMiddle, dialogLeft.getWidth(), y, getWidth() - dialogRight.getWidth() * 2, getHeight() - titleLeft.getHeight() - dialogBottomLeft.getHeight(), alpha);
        DrawTextureScaled(dialogRight, getWidth() - dialogRight.getWidth(), y, dialogLeft.getWidth(), getHeight() - titleLeft.getHeight() - dialogBottomLeft.getHeight(), alpha);
        y += getHeight() - titleLeft.getHeight() - dialogBottomLeft.getHeight();
        DrawTextureScaled(dialogBottomMiddle, dialogBottomLeft.getWidth(), y, getWidth() - dialogBottomLeft.getWidth() * 2, dialogBottomMiddle.getHeight(), alpha);
        DrawTexture(dialogBottomLeft, x, y, alpha);
        DrawTexture(dialogBottomRight, getWidth() - dialogBottomRight.getWidth(), y, alpha);
        super.render();
    }
    public void update()
    {
        super.update();
        if(closeButton != nullptr)
        {
            closeButton.setX(getWidth() - 17);
            closeButton.setY(3F);
        }
        int n = 0;
        if(!ResizeToFitY)
        {
            Iterator i$ = nestedItems.iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                Rectangle rect = (Rectangle)i$.next();
                UIElement con = (UIElement)getControls().get(n);
                if(con != closeButton)
                {
                    con.setX(rect.getX());
                    con.setY(rect.getY());
                    con.setWidth(clientW - (rect.getX() + rect.getWidth()));
                    con.setHeight(clientH - (rect.getY() + rect.getHeight()));
                    con.onresize();
                    n++;
                }
            } while(true);
        } else
        {
            int x = 0x186a0;
            int y = 0x186a0;
            int width = 0;
            int height = 0;
            Iterator i$ = nestedItems.iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                Rectangle rect = (Rectangle)i$.next();
                UIElement con = (UIElement)getControls().get(n);
                if(con != closeButton)
                {
                    if(x > con.getAbsoluteX())
                        x = con.getAbsoluteX();
                    if(y > con.getAbsoluteX())
                        y = con.getAbsoluteX();
                    if(width < con.getWidth())
                        width = con.getWidth();
                    if(height < con.getHeight())
                        height = con.getHeight();
                    n++;
                }
            } while(true);
            height += 50;
            this.height = height;
        }
    }
    public int clickX;
    public int clickY;
    public int clientH;
    public int clientW;
    public bool Movable;
    public bool moving;
    public int ncclientH;
    public int ncclientW;
    public Stack nestedItems;
    public bool ResizeToFitY;
    float alpha;
    Texture dialogBottomLeft;
    Texture dialogBottomMiddle;
    Texture dialogBottomRight;
    Texture dialogLeft;
    Texture dialogMiddle;
    Texture dialogRight;
    Texture titleCloseIcon;
    Texture titleLeft;
    Texture titleMiddle;
    Texture titleRight;
    HUDButton closeButton;
}
} // namespace
