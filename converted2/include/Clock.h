#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Clock.java
namespace zombie {
namespace ui {
#include "GameTime.h"
#include "Texture.h"
#include "TexturePackPage.h"
// Referenced classes of package zombie.ui:
//            UIElement
class Clock : public UIElement {
public:
{
    public Clock(int x, int y)
    {
        texture = nullptr;
        slash = nullptr;
        colon = nullptr;
        this.x = x;
        this.y = y;
    }
    public void render()
    {
        float time = GameTime.getInstance().getTimeOfDay();
        float minutes = time - (float)(int)time;
        minutes *= 60F;
        int hours = (int)time;
        Integer mindig1 = Integer.valueOf((int)(minutes / 10F));
        Integer mindig2 = Integer.valueOf((int)(minutes % 10F));
        Integer hourdig1 = Integer.valueOf(0);
        Integer hourdig2 = Integer.valueOf(0);
        if(hours > 9)
            hourdig1 = Integer.valueOf(hours / 10);
        hourdig2 = Integer.valueOf(hours % 10);
        int ux = 0;
        ux += 14;
        ux += 14;
        ux += 14;
        ux += 14;
        ux += 14;
        if(texture == nullptr)
            texture = Texture.getSharedTexture("media/ui/ClockBackground.png");
        DrawTexture(texture, 0, 0, 0.75F);
        if(digits == nullptr)
        {
            digits = new Texture[20];
            for(int n = 0; n < 10; n++)
            {
                digits[n] = TexturePackPage.getTexture((new StringBuilder()).append("media/ui/ClockDigit_").append(n).append(".png").toString());
                digits[n + 10] = TexturePackPage.getTexture((new StringBuilder()).append("media/ui/ClockDigitTiny_").append(n).append(".png").toString());
            }
        }
        std::string dateStr = (new Integer(GameTime.getInstance().getDay() + 1)).toString();
        if(GameTime.getInstance().getDay() == 0)
            dateStr = (new StringBuilder()).append(dateStr).append("st").toString();
        if(GameTime.getInstance().getDay() == 1)
            dateStr = (new StringBuilder()).append(dateStr).append("nd").toString();
        if(GameTime.getInstance().getDay() == 2)
            dateStr = (new StringBuilder()).append(dateStr).append("rd").toString();
        if(GameTime.getInstance().getDay() > 2)
            dateStr = (new StringBuilder()).append(dateStr).append("th").toString();
        int charA = 0;
        int charB = 0;
        int monthCharA = 0;
        int monthCharB = 0;
        if(GameTime.getInstance().getDay() + 1 > 9)
        {
            charA = (GameTime.getInstance().getDay() + 1) / 10;
            charB = (GameTime.getInstance().getDay() + 1) % 10;
        } else
        {
            charB = GameTime.getInstance().getDay() + 1;
        }
        if(GameTime.getInstance().getMonth() + 1 > 9)
        {
            monthCharA = (GameTime.getInstance().getMonth() + 1) / 10;
            monthCharB = (GameTime.getInstance().getMonth() + 1) % 10;
        } else
        {
            monthCharB = GameTime.getInstance().getMonth() + 1;
        }
        if(slash == nullptr)
            slash = TexturePackPage.getTexture("media/ui/ClockDigitTiny_Slash.png");
        if(colon == nullptr)
            colon = TexturePackPage.getTexture("media/ui/ClockDigit_Colon.png");
        ux = 5;
        int uy = 5;
        DrawTexture(digits[hourdig1.intValue()], ux, uy, 1.0F);
        ux += 11;
        DrawTexture(digits[hourdig2.intValue()], ux, uy, 1.0F);
        ux += 11;
        DrawTexture(colon, ux, uy, 1.0F);
        ux += 11;
        DrawTexture(digits[mindig1.intValue()], ux, uy, 1.0F);
        ux += 11;
        DrawTexture(digits[0], ux, uy, 1.0F);
        ux += 16;
        DrawTexture(digits[charA + 10], ux, uy, 1.0F);
        ux += 5;
        DrawTexture(digits[charB + 10], ux, uy, 1.0F);
        ux += 5;
        DrawTexture(slash, ux, uy, 1.0F);
        ux += 5;
        DrawTexture(digits[monthCharA + 10], ux, uy, 1.0F);
        ux += 5;
        DrawTexture(digits[monthCharB + 10], ux, uy, 1.0F);
        super.render();
    }
    Texture digits[];
    Texture texture;
    Texture slash;
    Texture colon;
}
} // namespace
