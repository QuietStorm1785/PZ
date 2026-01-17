#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TextBox.java
namespace zombie {
namespace ui {
#include <algorithm>
#include <algorithm>
// Referenced classes of package zombie.ui:
//            UIElement, TextManager, UIFont
class TextBox : public UIElement {
public:
{
    public TextBox(UIFont font, int x, int y, int width, std::string text)
    {
        Lines = new Stack();
        Centred = false;
        this.font = font;
        this.x = x;
        this.y = y;
        Text = text;
        this.width = width;
        Paginate();
    }
    public void onresize()
    {
        Paginate();
    }
    public void render()
    {
        if(!isVisible())
            return;
        super.render();
        Paginate();
        int y = 0;
        for(Iterator i$ = Lines.iterator(); i$.hasNext();)
        {
            std::string text = (std::string)i$.next();
            if(Centred)
                TextManager.instance.DrawStringCentre(font, getAbsoluteX() + getWidth() / 2, getAbsoluteY() + y, text, 1.0F, 1.0F, 1.0F, 1.0F);
            else
                TextManager.instance.DrawString(font, getAbsoluteX(), getAbsoluteY() + y, text, 1.0F, 1.0F, 1.0F, 1.0F);
            y += TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0));
        }
        setHeight(y);
    }
    public void update()
    {
        Paginate();
        int y = 0;
        for(Iterator i$ = Lines.iterator(); i$.hasNext();)
        {
            std::string text = (std::string)i$.next();
            y += TextManager.instance.MeasureStringY(font, (std::string)Lines.get(0));
        }
        setHeight(y);
    }
    private void Paginate()
    {
        int n = 0;
        Lines.clear();
        std::string textarr[] = Text.split("<br>");
        std::string arr$[] = textarr;
        int len$ = arr$.length;
label0:
        for(int i$ = 0; i$ < len$; i$++)
        {
            std::string text = arr$[i$];
            if(text.length() == 0)
            {
                Lines.add(" ");
                continue;
            }
            do
            {
                int m = text.indexOf(" ", n + 1);
                int z = m;
                if(z == -1)
                    z = text.length();
                int wid = TextManager.instance.MeasureStringX(font, text.substring(0, z));
                if(wid >= getWidth())
                {
                    std::string sub = text.substring(0, n);
                    text = text.substring(n + 1);
                    Lines.add(sub);
                    m = 0;
                } else
                if(m == -1)
                {
                    std::string sub = text;
                    Lines.add(sub);
                    continue label0;
                }
                n = m;
            } while(text.length() > 0);
        }
    }
    public void SetText(std::string text)
    {
        Text = text;
        Paginate();
    }
    public bool ResizeParent;
    UIFont font;
    Stack Lines;
    std::string Text;
    public bool Centred;
}
} // namespace
