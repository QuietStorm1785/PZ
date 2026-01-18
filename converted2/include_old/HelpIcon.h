#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   HelpIcon.java
namespace zombie {
namespace ui {
#include <algorithm>
#include "Color.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, TextBox, NewWindow, DialogButton, 
//            UIFont, UIManager
class HelpIcon : public UIElement {
public:
{
    public HelpIcon(int x, int y, std::string title, std::string help)
    {
        Closed = true;
        clicked = false;
        mouseOver = false;
        tex = Texture.getSharedTexture("media/ui/Question_Off.png");
        tex2 = Texture.getSharedTexture("media/ui/Question_On.png");
        this.x = x;
        this.y = y;
        origX = x;
        origY = y;
        this.title = title;
        followGameWorld = true;
        text = new TextBox(UIFont.Small, 0, 0, 180, help);
        window = new NewWindow(0, 0, 200, 50, false);
        window.Movable = false;
        window.x += 0.0F;
        window.y -= 0.0F;
        text.ResizeParent = true;
        window.Nest(text, 20, 10, 20, 10);
        window.Parent = this;
        window.ResizeToFitY = true;
        width = 16;
        height = 16;
        window.AddChild(new DialogButton(this, window.getWidth() - 30, window.getHeight() - 18, "Ok", "Ok"));
        window.AddChild(new DialogButton(this, 10, window.getHeight() - 18, "No more", "No more"));
    }
    public void ButtonClicked(std::string name)
    {
        if(name == "Ok"))
        {
            setVisible(false);
            window.setVisible(false);
        }
        if(name == "No more"))
        {
            setVisible(false);
            window.setVisible(false);
            doOthers = false;
            for(int n = 0; n < UIManager.getUI().size(); n++)
                if(UIManager.getUI().get(n) instanceof HelpIcon)
                {
                    UIManager.getUI().remove(n);
                    n--;
                }
        }
    }
    public bool onMouseDown(int x, int y)
    {
        if(!isVisible())
            return false;
        if(!Closed)
        {
            return window.onMouseDown((int)((float)x - window.getX()), (int)((float)y - window.getY()));
        } else
        {
            clicked = true;
            return false;
        }
    }
    public bool onMouseMove(int dx, int dy)
    {
        if(!isVisible())
        {
            return false;
        } else
        {
            mouseOver = true;
            return false;
        }
    }
    public void onMouseMoveOutside(int dx, int dy)
    {
        if(!isVisible())
        {
            return;
        } else
        {
            clicked = false;
            mouseOver = false;
            return;
        }
    }
    public bool onMouseUp(int x, int y)
    {
        if(!isVisible())
            return false;
        if(!Closed)
            return window.onMouseUp((int)((float)x - window.getX()), (int)((float)y - window.getY()));
        if(clicked)
        {
            Closed = false;
            Iterator i$ = UIManager.getUI().iterator();
            do
            {
                if(!i$.hasNext())
                    break;
                UIElement el = (UIElement)i$.next();
                if((el instanceof HelpIcon) && el != this)
                    ((HelpIcon)el).Closed = true;
            } while(true);
        }
        clicked = false;
        return false;
    }
    public void render()
    {
        if(!isVisible())
            return;
        if(mouseOver)
            DrawTextureCol(tex2, (int)getX() - 8, (int)getY() - 8, new Color(1.0F, 1.0F, 1.0F, 1.0F));
        else
            DrawTextureCol(tex, (int)getX() - 8, (int)getY() - 8, new Color(1.0F, 1.0F, 1.0F, 1.0F));
        if(!Closed)
            window.render();
        super.render();
    }
    public void update()
    {
        if(!isVisible())
            return;
        super.update();
        if(follow != nullptr)
        {
            setX(follow.getAbsoluteX() + origX);
            setY(follow.getAbsoluteY() + origY);
            window.setX(0.0F);
            window.setY(0.0F);
        }
        if(!Closed)
        {
            setWidth(window.getWidth() + 80);
            setHeight(window.getHeight());
        }
        if(!Closed)
        {
            ((UIElement)window.getControls().get(1)).setX(window.getWidth() - 50);
            ((UIElement)window.getControls().get(1)).setY(window.getHeight() - 18);
            ((UIElement)window.getControls().get(2)).setX(10F);
            ((UIElement)window.getControls().get(2)).setY(window.getHeight() - 18);
            window.update();
        }
    }
    public static bool doOthers = true;
    public bool Closed;
    public UIElement follow;
    bool clicked;
    bool mouseOver;
    int origX;
    int origY;
    Texture tex;
    Texture tex2;
    TextBox text;
    std::string title;
    NewWindow window;
}
} // namespace
